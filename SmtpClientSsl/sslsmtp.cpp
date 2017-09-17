#include "sslsmtp.h"

SslSMTP::SslSMTP(int port = 0)
{
    if(port > 0){
        Port = port;
    }
}

bool SslSMTP::Send(string hostnameMX, string from, string to, string mimedata)
{
     try{
        SSL_CTX *ctx;
        int server;
        SSL *ssl;
        char buf[1024];
        int bytes;
        char *hostname, *portnum;

        hostname = (char*)hostnameMX.c_str();
        portnum = "587";

        ctx = InitCTX();
        server = OpenConnection(hostname, atoi(portnum));
        ssl = SSL_new(ctx);						// create new SSL connection
        SSL_set_fd(ssl, server);				// attach the socket descriptor

        cout << "Connection....smtp";

        if ( SSL_connect(ssl) == FAIL ){
            ERR_print_errors_fp(stderr);
            return 0;
        } else {
            //char *msg = "{\"from\":[{\"name\":\"Zenobiusz\",\"email\":\"email@eee.ddf\"}]}";
            printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
            ShowCerts(ssl);

            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("Received from server: %s\n", buf);

            char *helo = "HELO breakermind.com\r\n";
            SSL_write(ssl, helo, strlen(helo));
            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("1 Received from server: %s\n", buf);

            char *from = "mail from: <hello@breakermind.com>\r\n";
            SSL_write(ssl, from, strlen(from));
            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("2 Received from server: %s\n", buf);

            // char *rcpt = "rcpt to: <email@gmail.com>\r\n";
            char *rcpt = "rcpt to: <email@qflash.pl>\r\n";
            SSL_write(ssl, rcpt, strlen(rcpt));
            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("3 Received from server: %s\n", buf);

            char *data = "DATA\r\n";
            SSL_write(ssl, data, strlen(data));
            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("4 Received from server: %s\n", buf);


            char *mdata = "From: <hello@qflash.pl>\r\n"
                    "To: Breakermind <email@gmail.com>\r\n"
                    "Subject: =?iso-8859-2?Q?Hello111111=2C_czy_um=F3wisz_si=EA_ze_mn=B1=3F?=\r\n"
                    "Reply-To: m <email@qflash.pl>\r\n"
                    "Return-Path: <email@qflash.pl>\r\n"
                    "Date: Sat, 30 Apr 2017 19:28:29 -0300\r\n"
                    "MIME-Version: 1.0\r\n"
                    "Content-Type: multipart/mixed; boundary=\"ToJestSeparator0000\"\r\n\r\n"
                    "--ToJestSeparator0000\r\n"
                    "Content-Type: multipart/alternative; boundary=\"ToJestSeparatorZagniezdzony1111\"\r\n\r\n"
                    "--ToJestSeparatorZagniezdzony1111\r\n"
                    "Content-Type: text/plain; charset=\"iso-8859-2\"\r\n"
                    "Content-Transfer-Encoding: quoted-printable\r\n\r\n"
                    "To jest tre=B6=E6 wiadomo=B6ci.\r\n\r\n"
                    "--ToJestSeparatorZagniezdzony1111\r\n"
                    "Content-Type: text/html; charset=\"iso-8859-2\"\r\n"
                    "Content-Transfer-Encoding: quoted-printable\r\n\r\n"
                    "<BODY><FONT face=3DArial size=3D2><h1 style=\"color: #ff2222\">Co za buraki pastewniaki. HTML part color To jest tre=B6=E6 wiadomo=B6ci.</h1></FONT></BODY></HTML>\r\n\r\n"
                    "--ToJestSeparatorZagniezdzony1111--\r\n"
                    "--ToJestSeparator0000\r\n"
                    "Content-Type: image/jpeg; name=\"plik.jpg\"\r\n"
                    "Content-Transfer-Encoding: base64\r\n"
                    "Content-Disposition: attachment; filename=\"plik.jpg\"\r\n\r\n"
                    "/9j/4AAQSkZJRgABAQEASABIAAD/4gxYSUNDX1BST0ZJTEUAAQEAAAxITGlubwIQAABtbnRyUkdCIFhZWiAHzgACAAkABgAxAABhY3NwTVNGVAAAAABJRUMgc1JHQgAAAAAAAAAAAAAAAAAA9tYAAQAAAADTLUhQICAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABFjcHJ0AAABUAAAADNkZXNjAAABhAAAAGx3dHB0AAAB8AAAABRia3B0AAACBAAAABRyWFlaAAACGAAAABRnWFlaAAACLAAAABRiWFlaAAACQAAAABRkbW5kAAACVAAAAHBkbWRkAAACxAAAAIh2dWVkAAADTAAAAIZ2aWV3AAAD1AAAACRsdW1pAAAD+AAAABRtZWFzAAAEDAAAACR0ZWNoAAAEMAAAAAxyVFJDAAAEPAAACAxnVFJDAAAEPAAACAxiVFJDAAAEPAAACAx0ZXh0AAAAAENvcHlyaWdodCAoYykgMTk5OCBIZXdsZXR0LVBhY2thcmQgQ29tcGFueQAAZGVzYwAAAAAAAAASc1JHQiBJRUM2MTk2Ni0yLjEAAAAAAAAAAAAAABJzUkdCIElFQzYxOTY2LTIuMQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAWFlaIAAAAAAAAPNRAAEAAAABFsxYWVogAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAABvogAAOPUAAAOQWFlaIAAAAAAAAGKZAAC3hQAAGNpYWVogAAAAAAAAJKAAAA+EAAC2z2Rlc2MAAAAAAAAAFklFQyBodHRwOi8vd3d3LmllYy5jaAAAAAAAAAAAAAAAFklFQyBodHRwOi8vd3d3LmllYy5jaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABkZXNjAAAAAAAAAC5JRUMgNjE5NjYtMi4xIERlZmF1bHQgUkdCIGNvbG91ciBzcGFjZSAtIHNSR0IAAAAAAAAAAAAAAC5JRUMgNjE5NjYtMi4xIERlZmF1bHQgUkdCIGNvbG91ciBzcGFjZSAtIHNSR0IAAAAAAAAAAAAAAAAAAAAAAAAAAAAAZGVzYwAAAAAAAAAsUmVmZXJlbmNlIFZpZXdpbmcgQ29uZGl0aW9uIGluIElFQzYxOTY2LTIuMQAAAAAAAAAAAAAALFJlZmVyZW5jZSBWaWV3aW5nIENvbmRpdGlvbiBpbiBJRUM2MTk2Ni0yLjEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHZpZXcAAAAAABOk/gAUXy4AEM8UAAPtzAAEEwsAA1yeAAAAAVhZWiAAAAAAAEwJVgBQAAAAVx/nbWVhcwAAAAAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAo8AAAACc2lnIAAAAABDUlQgY3VydgAAAAAAAAQAAAAABQAKAA8AFAAZAB4AIwAoAC0AMgA3ADsAQABFAEoATwBUAFkAXgBjAGgAbQByAHcAfACBAIYAiwCQAJUAmgCfAKQAqQCuALIAtwC8AMEAxgDLANAA1QDbAOAA5QDrAPAA9gD7AQEBBwENARMBGQEfASUBKwEyATgBPgFFAUwBUgFZAWABZwFuAXUBfAGDAYsBkgGaAaEBqQGxAbkBwQHJAdEB2QHhAekB8gH6AgMCDAIUAh0CJgIvAjgCQQJLAlQCXQJnAnECegKEAo4CmAKiAqwCtgLBAssC1QLgAusC9QMAAwsDFgMhAy0DOANDA08DWgNmA3IDfgOKA5YDogOuA7oDxwPTA+AD7AP5BAYEEwQgBC0EOwRIBFUEYwRxBH4EjASaBKgEtgTEBNME4QTwBP4FDQUcBSsFOgVJBVgFZwV3BYYFlgWmBbUFxQXVBeUF9gYGBhYGJwY3BkgGWQZqBnsGjAadBq8GwAbRBuMG9QcHBxkHKwc9B08HYQd0B4YHmQesB78H0gflB/gICwgfCDIIRghaCG4IggiWCKoIvgjSCOcI+wkQCSUJOglPCWQJeQmPCaQJugnPCeUJ+woRCicKPQpUCmoKgQqYCq4KxQrcCvMLCwsiCzkLUQtpC4ALmAuwC8gL4Qv5DBIMKgxDDFwMdQyODKcMwAzZDPMNDQ0mDUANWg10DY4NqQ3DDd4N+A4TDi4OSQ5kDn8Omw62DtIO7g8JDyUPQQ9eD3oPlg+zD88P7BAJECYQQxBhEH4QmxC5ENcQ9RETETERTxFtEYwRqhHJEegSBxImEkUSZBKEEqMSwxLjEwMTIxNDE2MTgxOkE8UT5RQGFCcUSRRqFIsUrRTOFPAVEhU0FVYVeBWbFb0V4BYDFiYWSRZsFo8WshbWFvoXHRdBF2UXiReuF9IX9xgbGEAYZRiKGK8Y1Rj6GSAZRRlrGZEZtxndGgQaKhpRGncanhrFGuwbFBs7G2MbihuyG9ocAhwqHFIcexyjHMwc9R0eHUcdcB2ZHcMd7B4WHkAeah6UHr4e6R8THz4faR+UH78f6iAVIEEgbCCYIMQg8CEcIUghdSGhIc4h+yInIlUigiKvIt0jCiM4I2YjlCPCI/AkHyRNJHwkqyTaJQklOCVoJZclxyX3JicmVyaHJrcm6CcYJ0kneierJ9woDSg/KHEooijUKQYpOClrKZ0p0CoCKjUqaCqbKs8rAis2K2krnSvRLAUsOSxuLKIs1y0MLUEtdi2rLeEuFi5MLoIuty7uLyQvWi+RL8cv/jA1MGwwpDDbMRIxSjGCMbox8jIqMmMymzLUMw0zRjN/M7gz8TQrNGU0njTYNRM1TTWHNcI1/TY3NnI2rjbpNyQ3YDecN9c4FDhQOIw4yDkFOUI5fzm8Ofk6Njp0OrI67zstO2s7qjvoPCc8ZTykPOM9Ij1hPaE94D4gPmA+oD7gPyE/YT+iP+JAI0BkQKZA50EpQWpBrEHuQjBCckK1QvdDOkN9Q8BEA0RHRIpEzkUSRVVFmkXeRiJGZ0arRvBHNUd7R8BIBUhLSJFI10kdSWNJqUnwSjdKfUrESwxLU0uaS+JMKkxyTLpNAk1KTZNN3E4lTm5Ot08AT0lPk0/dUCdQcVC7UQZRUFGbUeZSMVJ8UsdTE1NfU6pT9lRCVI9U21UoVXVVwlYPVlxWqVb3V0RXklfgWC9YfVjLWRpZaVm4WgdaVlqmWvVbRVuVW+VcNVyGXNZdJ114XcleGl5sXr1fD19hX7NgBWBXYKpg/GFPYaJh9WJJYpxi8GNDY5dj62RAZJRk6WU9ZZJl52Y9ZpJm6Gc9Z5Nn6Wg/aJZo7GlDaZpp8WpIap9q92tPa6dr/2xXbK9tCG1gbbluEm5rbsRvHm94b9FwK3CGcOBxOnGVcfByS3KmcwFzXXO4dBR0cHTMdSh1hXXhdj52m3b4d1Z3s3gReG54zHkqeYl553pGeqV7BHtje8J8IXyBfOF9QX2hfgF+Yn7CfyN/hH/lgEeAqIEKgWuBzYIwgpKC9INXg7qEHYSAhOOFR4Wrhg6GcobXhzuHn4gEiGmIzokziZmJ/opkisqLMIuWi/yMY4zKjTGNmI3/jmaOzo82j56QBpBukNaRP5GokhGSepLjk02TtpQglIqU9JVflcmWNJaflwqXdZfgmEyYuJkkmZCZ/JpomtWbQpuvnByciZz3nWSd0p5Anq6fHZ+Ln/qgaaDYoUehtqImopajBqN2o+akVqTHpTilqaYapoum/adup+CoUqjEqTepqaocqo+rAqt1q+msXKzQrUStuK4trqGvFq+LsACwdbDqsWCx1rJLssKzOLOutCW0nLUTtYq2AbZ5tvC3aLfguFm40blKucK6O7q1uy67p7whvJu9Fb2Pvgq+hL7/v3q/9cBwwOzBZ8Hjwl/C28NYw9TEUcTOxUvFyMZGxsPHQce/yD3IvMk6ybnKOMq3yzbLtsw1zLXNNc21zjbOts83z7jQOdC60TzRvtI/0sHTRNPG1EnUy9VO1dHWVdbY11zX4Nhk2OjZbNnx2nba+9uA3AXcit0Q3ZbeHN6i3ynfr+A24L3hROHM4lPi2+Nj4+vkc+T85YTmDeaW5x/nqegy6LzpRunQ6lvq5etw6/vshu0R7ZzuKO6070DvzPBY8OXxcvH/8ozzGfOn9DT0wvVQ9d72bfb794r4Gfio+Tj5x/pX+uf7d/wH/Jj9Kf26/kv+3P9t////2wBDAAMCAgMCAgMDAwMEAwMEBQgFBQQEBQoHBwYIDAoMDAsKCwsNDhIQDQ4RDgsLEBYQERMUFRUVDA8XGBYUGBIUFRT/2wBDAQMEBAUEBQkFBQkUDQsNFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBT/wgARCAAKAAoDAREAAhEBAxEB/8QAFgABAQEAAAAAAAAAAAAAAAAAAAEI/8QAFgEBAQEAAAAAAAAAAAAAAAAAAAQB/9oADAMBAAIQAxAAAAHOFs4ap//EABQQAQAAAAAAAAAAAAAAAAAAACD/2gAIAQEAAQUCH//EABQRAQAAAAAAAAAAAAAAAAAAACD/2gAIAQMBAT8BH//EABQRAQAAAAAAAAAAAAAAAAAAACD/2gAIAQIBAT8BH//EABQQAQAAAAAAAAAAAAAAAAAAACD/2gAIAQEABj8CH//EABgQAAIDAAAAAAAAAAAAAAAAAAABECFB/9oACAEBAAE/IWWbH//aAAwDAQACAAMAAAAQSS//xAAUEQEAAAAAAAAAAAAAAAAAAAAg/9oACAEDAQE/EB//xAAUEQEAAAAAAAAAAAAAAAAAAAAg/9oACAECAQE/EB//xAAZEAADAQEBAAAAAAAAAAAAAAAAAREhMXH/2gAIAQEAAT8Qp5npRSkpw//Z\r\n\r\n"
                    "--ToJestSeparator0000--\r\n\r\n"
                    ".\r\n";

            SSL_write(ssl, mdata, strlen(mdata));
            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("5 Received from server: %s\n", buf);

            SSL_free(ssl);
            return 1;
        }
        close(server);
        SSL_CTX_free(ctx);
    }catch(std::exception &e){
        return 0;
    }
}

int SslSMTP::OpenConnection(const char *hostname, int port)
{   int sd;
    struct hostent *host;
    struct sockaddr_in addr;

    if ( (host = gethostbyname(hostname)) == NULL )
    {
        perror(hostname);
        abort();
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
        addr.sin_addr.s_addr = *(long*)(host->h_addr);
        if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
        {
            close(sd);
            perror(hostname);
            abort();
        }
        return sd;
}

// InitCTX - initialize the SSL engine.
SSL_CTX* SslSMTP::InitCTX(void)
{   const SSL_METHOD *method;
    SSL_CTX *ctx;

    SSL_library_init();
    SSL_load_error_strings();			// Bring in and register error messages
    OpenSSL_add_all_algorithms();		// Load cryptos

    method = SSLv23_client_method();	// Create new client-method instance
    ctx = SSL_CTX_new(method);			// Create new context
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

// ShowCerts - print out the certificates.
void SslSMTP::ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);	// get the server's certificate
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);							// free the malloc'ed string
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);							// free the malloc'ed string
        X509_free(cert);					// free the malloc'ed certificate copy
    } else {
        printf("No certificates.\n");
    }
}

void SslSMTP::quoted(string str){
    std::stringstream ss;
        std::string in = "String with spaces, and embedded \"quotes\" too";
        if(str.length() > 0){
            in = str;
        }
        std::string out;

        ss << std::quoted(in);
        std::cout << "read in     [" << in << "]\n"
                  << "stored as   [" << ss.str() << "]\n";

        ss >> std::quoted(out);
        std::cout << "written out [" << out << "]\n";
}
