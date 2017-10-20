#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, iv))
    handleErrors();

  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}

int main (int argc, char *argv[])
{
  if ( argc != 2 )
        {
                printf("Usage: <process> <file>\n");
                exit(0);
        }

  /* A 256 bit key */
  unsigned char *key = (unsigned char *)"key";

  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"iv";

  //unsigned char key[32] = (unsigned char *) "key";
  //unsigned char iv[16] = (unsigned char *)"iv";


  unsigned char ciphertext[128] = "", base64_in[128] = "", base64_out[128] = "";

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[128]="";

  int decryptedtext_len, ciphertext_len;

  /* Initialise the library */
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();
  OPENSSL_config(NULL);

  /* Encrypt the plaintext */
  char fileBuffer[128] = "";
  ifstream infile (argv[1], ios::binary);
  infile.getline(fileBuffer, sizeof(fileBuffer));
  infile.close(); 

  strcpy((char *)base64_in, fileBuffer);
  ciphertext_len =  (strlen(reinterpret_cast<const char *>(base64_in)));
  printf("%d %s\n",ciphertext_len, base64_in);

  int length = EVP_DecodeBlock(base64_out, base64_in, ciphertext_len);
  while(base64_in[--ciphertext_len] == '=') length--;
  printf("%d %s\n", length,base64_out);

  BIO_dump_fp (stdout, (const char *)base64_out, length);

  decryptedtext_len = decrypt(base64_out, length, key, iv,
   decryptedtext);

  /* Add a NULL terminator. We are expecting printable text */
  decryptedtext[decryptedtext_len] = '\0';

  /* Show the decrypted text */
  printf("Decrypted text is:\n");
  printf("%d %s\n", decryptedtext_len ,decryptedtext);

  /* Clean up */
  EVP_cleanup();
  ERR_free_strings();

  return 0;
}