#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <openssl/aes.h>
using namespace std;

void main()
{

// Buffers
unsigned char inbuffer[1024];
unsigned char encryptedbuffer[1024];
unsigned char outbuffer[1024];


// CODE FOR ENCRYPTION
//--------------------
unsigned char oneKey[] = "abc";
AES_KEY key; 

AES_set_encrypt_key(oneKey,128,&key);
AES_set_decrypt_key(oneKey,128,&key);

//--------------------


string straa("hello world\n");
memcpy((char*)inbuffer,straa.c_str(),13);


printf("%s",inbuffer);
//this prints out fine

AES_encrypt(inbuffer,encryptedbuffer,&key);
//printf("%s",encryptedbuffer);
//this is expected to pring out rubbish, so is commented

AES_decrypt(encryptedbuffer,outbuffer,&key);
printf("%s",outbuffer);
//this is not pringint "hello world"

getchar();

}