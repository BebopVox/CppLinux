#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <assert.h>

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, iv))
    handleErrors();

  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int main (int argc, char *argv[])
{
  if ( argc != 2 )
    {
        printf("Usage: <process> <file>\n");
        exit(0);
    }
  /* A 256 bit key */
  //unsigned char *key = (unsigned char *) "key";

  /* A 128 bit IV  Should be hardcoded in both encrypt and decrypt. */
  //unsigned char *iv = (unsigned char *)"iv";

  unsigned char key[32] = (unsigned char *) "key";
  unsigned char iv[16] = (unsigned char *)"iv";

  /* Message to be encrypted */
  unsigned char *plaintext = (unsigned char *)"Password";

  unsigned char ciphertext[128],base64[128];

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[128];

  int decryptedtext_len, ciphertext_len;

  /* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);

  /* Encrypt the plaintext */
  ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, iv, ciphertext);

  /* Do something useful with the ciphertext here */
  printf("Ciphertext is:\n");
  BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);

  printf("%d %s\n", ciphertext_len, ciphertext);
  int encode_str_size = EVP_EncodeBlock(base64, ciphertext, ciphertext_len);
    printf("%d %s\n", encode_str_size, base64);

  std::ofstream outFile (argv[1]);
  outFile << base64;
  outFile.close();

  /* Clean up */
  EVP_cleanup();
  ERR_free_strings();

  return 0;
}