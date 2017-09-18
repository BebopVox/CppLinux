#include "sslsmtp.h"
#include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <cstring>
// #include <cstdio>
// #include <algorithm>

// BreakermindLib base64
#include "BreakermindLib/breakermind.h"


const char SslSMTP::MimeTypes[][2][128] =
{
    {"***",    "application/octet-stream"},
    {"csv",    "text/csv"},
    {"tsv",    "text/tab-separated-values"},
    {"tab",    "text/tab-separated-values"},
    {"html",    "text/html"},
    {"htm",    "text/html"},
    {"doc",    "application/msword"},
    {"docx",    "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
    {"ods",    "application/x-vnd.oasis.opendocument.spreadsheet"},
    {"odt",    "application/vnd.oasis.opendocument.text"},
    {"rtf",    "application/rtf"},
    {"sxw",    "application/vnd.sun.xml.writer"},
    {"txt",    "text/plain"},
    {"xls",    "application/vnd.ms-excel"},
    {"xlsx",    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
    {"pdf",    "application/pdf"},
    {"ppt",    "application/vnd.ms-powerpoint"},
    {"pps",    "application/vnd.ms-powerpoint"},
    {"pptx",    "application/vnd.openxmlformats-officedocument.presentationml.presentation"},
    {"wmf",    "image/x-wmf"},
    {"atom",    "application/atom+xml"},
    {"xml",    "application/xml"},
    {"json",    "application/json"},
    {"js",    "application/javascript"},
    {"ogg",    "application/ogg"},
    {"ps",    "application/postscript"},
    {"woff",    "application/x-woff"},
    {"xhtml","application/xhtml+xml"},
    {"xht",    "application/xhtml+xml"},
    {"zip",    "application/zip"},
    {"gz",    "application/x-gzip"},
    {"rar",    "application/rar"},
    {"rm",    "application/vnd.rn-realmedia"},
    {"rmvb",    "application/vnd.rn-realmedia-vbr"},
    {"swf",    "application/x-shockwave-flash"},
    {"au",        "audio/basic"},
    {"snd",    "audio/basic"},
    {"mid",    "audio/mid"},
    {"rmi",        "audio/mid"},
    {"mp3",    "audio/mpeg"},
    {"aif",    "audio/x-aiff"},
    {"aifc",    "audio/x-aiff"},
    {"aiff",    "audio/x-aiff"},
    {"m3u",    "audio/x-mpegurl"},
    {"ra",    "audio/vnd.rn-realaudio"},
    {"ram",    "audio/vnd.rn-realaudio"},
    {"wav",    "audio/x-wave"},
    {"wma",    "audio/x-ms-wma"},
    {"m4a",    "audio/x-m4a"},
    {"bmp",    "image/bmp"},
    {"gif",    "image/gif"},
    {"jpe",    "image/jpeg"},
    {"jpeg",    "image/jpeg"},
    {"jpg",    "image/jpeg"},
    {"jfif",    "image/jpeg"},
    {"png",    "image/png"},
    {"svg",    "image/svg+xml"},
    {"tif",    "image/tiff"},
    {"tiff",    "image/tiff"},
    {"ico",    "image/vnd.microsoft.icon"},
    {"css",    "text/css"},
    {"bas",    "text/plain"},
    {"c",        "text/plain"},
    {"h",        "text/plain"},
    {"rtx",    "text/richtext"},
    {"mp2",    "video/mpeg"},
    {"mpa",    "video/mpeg"},
    {"mpe",    "video/mpeg"},
    {"mpeg",    "video/mpeg"},
    {"mpg",    "video/mpeg"},
    {"mpv2",    "video/mpeg"},
    {"mov",    "video/quicktime"},
    {"qt",    "video/quicktime"},
    {"lsf",    "video/x-la-asf"},
    {"lsx",    "video/x-la-asf"},
    {"asf",    "video/x-ms-asf"},
    {"asr",    "video/x-ms-asf"},
    {"asx",    "video/x-ms-asf"},
    {"avi",    "video/x-msvideo"},
    {"3gp",    "video/3gpp"},
    {"3gpp",    "video/3gpp"},
    {"3g2",    "video/3gpp2"},
    {"movie","video/x-sgi-movie"},
    {"mp4",    "video/mp4"},
    {"wmv",    "video/x-ms-wmv"},
    {"webm","video/webm"},
    {"m4v",    "video/x-m4v"},
    {"flv",    "video/x-flv"}
};

SslSMTP::SslSMTP(std::string hostnameMX, int port = 0)
{
    if(port > 0){
        Port = port;
    }
    HostnameMX = hostnameMX;
}

bool SslSMTP::Send(string from, string to, string replyto, string subject, string msg, string msghtml, vector<string> files)
{
     try{
        SSL_CTX *ctx;
        int server;
        SSL *ssl;
        char buf[1024];
        int bytes;
        char *hostname, *portnum;
        //cout << "PORT " << Port;

        // SMTP hostname and port number
        hostname = (char*)HostnameMX.c_str();
        portnum = (char*)std::to_string(Port).c_str();

        ctx = InitCTX();
        server = OpenConnection(hostname, atoi(portnum));
        ssl = SSL_new(ctx);						// create new SSL connection
        SSL_set_fd(ssl, server);				// attach the socket descriptor

        cout << "Connection....smtp";

        if ( SSL_connect(ssl) == FAIL ){
            ERR_print_errors_fp(stderr);
            return 0;
        } else {
            // char *msg = (char*)"{\"from\":[{\"name\":\"Zenobiusz\",\"email\":\"email@eee.ddf\"}]}";
            printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
            ShowCerts(ssl);

            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("Received from server: %s\n", buf);

            std::ostringstream f0;
            f0 << "HELO localhost\r\n";
            std::string f00 = f0.str();
            char *helo = (char*)f00.c_str();
            SSL_write(ssl, helo, strlen(helo));
            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("1 Received from server: %s\n", buf);
            if(!Contain(std::string(buf), "250"))return 0;

            std::ostringstream f1;
            f1 << "mail from: " << from << "\r\n";
            std::string f11 = f1.str();
            char *fromemail = (char*)f11.c_str();
            SSL_write(ssl, fromemail, strlen(fromemail));
            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("2 Received from server: %s\n", buf);
            if(!Contain(std::string(buf), "250"))return 0;

            std::ostringstream f2;
            f2 << "rcpt to: " << to << "\r\n";
            std::string f22 = f2.str();
            char *rcpt = (char*)f22.c_str();
            SSL_write(ssl, rcpt, strlen(rcpt));
            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("3 Received from server: %s\n", buf);
            if(!Contain(std::string(buf), "250"))return 0;

            char *data = (char*)"DATA\r\n";
            SSL_write(ssl, data, strlen(data));
            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("4 Received from server: %s\n", buf);
            if(!Contain(std::string(buf), "354"))return 0;

            std::string Encoding = "iso-8859-2"; // charset: utf-8, utf-16, iso-8859-2, iso-8859-1

            std::ostringstream m;
             m << "From: " << from << "\r\n";
             m << "To: " << to << "\r\n";
             m << "Subject: =?" << Encoding << "?Q?"<< subject << "\r\n";
             m << "Reply-To: " << from << "\r\n";
             m << "Return-Path: " << from << "\r\n";
             m << "Date: "<< Date(1) << "\r\n";
             m << "MIME-Version: 1.0\r\n";
             m << "Content-Type: multipart/mixed; boundary=\"ToJestSeparator0000\"\r\n\r\n";
             m << "--ToJestSeparator0000\r\n";
             m << "Content-Type: multipart/alternative; boundary=\"ToJestSeparatorZagniezdzony1111\"\r\n\r\n";
             m << "--ToJestSeparatorZagniezdzony1111\r\n";
             m << "Content-Type: text/plain; charset=\"" << Encoding << "\"\r\n";
             m << "Content-Transfer-Encoding: quoted-printable\r\n\r\n";
             m << msg << "\r\n\r\n";
             m << "--ToJestSeparatorZagniezdzony1111\r\n";
             m << "Content-Type: text/html; charset=\"" << Encoding << "\"\r\n";
             m << "Content-Transfer-Encoding: quoted-printable\r\n\r\n";
             m << msghtml << "\r\n\r\n";
             m << "--ToJestSeparatorZagniezdzony1111--\r\n";
             // add atachments
             if(files.size() > 0){
                for(int i = 0;i < files.size();i++){
                    std::string path = files.at(i);
                    std::string filename = fileBasename(path);
                    std::string fc = base64_encode(get_file_contents(filename.c_str()));
                    std::string extension = GetFileExtension(filename);
                    const char *mimetype = GetMimeTypeFromFileName((char*)extension.c_str());
                    // cout << "MIME " << mimetype << endl << extension << endl;
                    // cout << "FILE CONTENT " << fc << endl;
                    m << "--ToJestSeparator0000\r\n";
                    m << "Content-Type: " << mimetype << "; name=\"" << filename << "\"\r\n";
                    m << "Content-Transfer-Encoding: base64\r\n";
                    m << "Content-Disposition: attachment; filename=\"" << filename << "\"\r\n\r\n";
                    m << fc <<"\r\n\r\n";
                    // m << "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\r\n\r\n";
                }
             }
             m << "--ToJestSeparator0000--\r\n\r\n";
             m << ".\r\n";

             // create mime message string
             std::string mimemsg = m.str();
             // cout << mimemsg;

            char * mdata = (char*)mimemsg.c_str();
            SSL_write(ssl, mdata, strlen(mdata));
            bytes = SSL_read(ssl, buf, sizeof(buf));
            buf[bytes] = 0;
            printf("5 Received from server: %s\n", buf);
            if(!Contain(std::string(buf), "250"))return 0;

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
    // socket time out
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    if (setsockopt (sd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                sizeof(timeout)) < 0)
        cout << "setsockopt failed\n";

    if (setsockopt (sd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                sizeof(timeout)) < 0)
        cout << "setsockopt failed\n";

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

string SslSMTP::Date(bool utc){
    time_t now = time(0);
    char* dt = ctime(&now);
    if(utc){
        tm *gmtm = gmtime(&now);
        dt = asctime(gmtm);
    }
    return std::string(dt);
}

string SslSMTP::fileBasename(string path){
    std::string filename = path.substr(path.find_last_of("/\\") + 1);
    return filename;
    // without extension
    // std::string::size_type const p(base_filename.find_last_of('.'));
    // std::string file_without_extension = base_filename.substr(0, p);
}

std::string SslSMTP::getFileContent(const std::string& path)
{
  //std::ifstream file(path);
  //std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  //return content;
}

std::string SslSMTP::get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

bool SslSMTP::Contain(std::string str, std::string search){
    std::size_t found = str.find(search);
    if (found!=std::string::npos){
        return 1;
    }
    return 0;
}

std::string SslSMTP::GetFileExtension(const std::string& FileName)
{
    if(FileName.find_last_of(".") != std::string::npos)
        return FileName.substr(FileName.find_last_of(".")+1);
    return "";
}

const char* SslSMTP::GetMimeTypeFromFileName( char* szFileExt)
{
    // cout << "EXT " << szFileExt;
    for (int i = 0; i < sizeof (MimeTypes) / sizeof (MimeTypes[0]); i++)
    {
        if (strcmp(MimeTypes[i][0],szFileExt) == 0)
        {
            return MimeTypes[i][1];
        }
    }
    return MimeTypes[0][1];   //if does not match any,  "application/octet-stream" is returned
}


/*
 char *mdata = (char*)"From: <hello@qflash.pl>\r\n"
                    "To: Breakermind <fxstareu@gmail.com>\r\n"
                    "Subject: =?iso-8859-2?Q?Hello111111=2C_czy_um=F3wisz_si=EA_ze_mn=B1=3F?=\r\n"
                    "Reply-To: m <hello@qflash.pl>\r\n"
                    "Return-Path: <hello@qflash.pl>\r\n"
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
                    "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\r\n\r\n"
                    "--ToJestSeparator0000\r\n"
                    "Content-Type: image/jpeg; name=\"plik2.jpg\"\r\n"
                    "Content-Transfer-Encoding: base64\r\n"
                    "Content-Disposition: attachment; filename=\"plik2.jpg\"\r\n\r\n"
                    "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\r\n\r\n"
                    "--ToJestSeparator0000--\r\n\r\n"
                    ".\r\n";
*/
