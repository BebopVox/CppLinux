#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#include <iostream>
#include <cstring>

#define MAX_PACKET_SIZE 10000

int main() {

        BIO * bio;
        SSL * ssl;
        SSL_CTX * ctx;

        /* Initializing OpenSSL */

        SSL_load_error_strings();
        ERR_load_BIO_strings();
        OpenSSL_add_all_algorithms();

        SSL_library_init(); //mandatory and missing from some examples
        ctx = SSL_CTX_new(SSLv23_client_method());

        if (ctx == NULL) {
                std::cout << "Ctx is null" << std::endl;
                ERR_print_errors_fp(stderr);
        }

	//using a store from examples
        if(! SSL_CTX_load_verify_locations(ctx, "/home/user/c++/server/certificate.pem", NULL))
        {
            /* Handle failed load here */
                std::cout << "Faild load verify locations" << std::endl;

        }

        bio = BIO_new_ssl_connect(ctx);
        BIO_get_ssl(bio, & ssl);
        SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

        //replace with your own test server
	    BIO_set_conn_hostname(bio, "127.0.0.1:666");

        if(BIO_do_connect(bio) <= 0)
        {
                std::cout<<"Failed connection" << std::endl;
                /* Handle failed connection */
        } else {
                std::cout<<"Connected" << std::endl;
        }

        if(SSL_get_verify_result(ssl) != X509_V_OK)
        {
            /* Handle the failed verification */
            std::cout << "Failed get verify result " << std::endl;

            fprintf(stderr, "Certificate verification error: %i\n", SSL_get_verify_result(ssl));
	    //do not exit here (but some more verification would not hurt) because if you are using a self-signed certificate you will receive 18
	    //18 X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT which is not an error
        }

        char write_buf[] = "GET / HTTP/1.1\r\nHost: www.nemesisit.ro\r\n\r\n";

        if(BIO_write(bio, write_buf, strlen(write_buf)) <= 0)
        {
                if(! BIO_should_retry(bio))
                {
                        /* Handle failed write here */
                }
            /* Do something to handle the retry */
                std::cout << "Failed write" << std::endl;
        }

        char buf[MAX_PACKET_SIZE];

        int p;
        char r[1024];
        for(;;)
        {
                p = BIO_read(bio, r, 1023);
                if(p <= 0) break;
                r[p] = 0;
                printf("%s", r);
        }

        std::cout << "Done reading" << std::endl;

        /* To free it from memory, use this line */

        ERR_print_errors_fp(stderr);
        BIO_free_all(bio);

        return 0;
}