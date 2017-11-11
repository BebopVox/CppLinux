#include "loop.h"

#include <cstring> // strlen
#include <string>
#include <vector>

using namespace std;

//string Loop::from = "";
//string Loop::subject = "";

Loop::Loop(){}
// Loop::~loop(){}

string Loop::getAccountInfo(long long id){
    return "Account info|userID:1234567890|Username:Zenek";
}

string Loop::getAds(long long id){
    return "<h1>Reklama produktu w HTML</h1>";
}

bool Loop::validEmail(string email){
    cout << "[VALIDATE_EMAIL] " << email << endl;
    return 1;
}

bool Loop::banIP(string IP){
    return 0;
}

string Loop::replaceAll( string s, string search, string replace ) {
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s.find( search, pos );
        if( pos == string::npos ) break;
        // Replace by erasing and inserting
        s.erase( pos, search.length() );
        s.insert( pos, replace );
    }
    return s;
}

bool Loop::Contain(std::string str, std::string search){
    std::size_t found = str.find(search);
    if (found!=std::string::npos){
        return 1;
    }
    return 0;
}

vector<string> Loop::split(string s, char delim) {
    vector<string> v;
    auto i = 0;
    auto pos = s.find(delim);
    while (pos != string::npos) {
      v.push_back(s.substr(i, pos-i));
      i = ++pos;
      pos = s.find(delim, pos);

      if (pos == string::npos)
         v.push_back(s.substr(i, s.length()));
    }
    return v;
}

bool Loop::sslError(SSL *ssl, int received){
    const int err = SSL_get_error(ssl, received);
    // const int st = ERR_get_error();
    if (err == SSL_ERROR_NONE) {
        // OK send
        // std::cout << "[SSL_OK] " << err << endl;
    } else if (err == SSL_ERROR_WANT_READ ) {
        SSL_shutdown(ssl);
        return 1;
        //kill(getpid(), SIGKILL);
    } else if (err == SSL_ERROR_SYSCALL) {
        cout << "SYSCALL"<<endl;
        SSL_shutdown(ssl);
        return 1;
        //kill(getpid(), SIGKILL);
    } else if (err == SSL_ERROR_ZERO_RETURN) {
        cout << "SYSCALL"<<endl;
        SSL_shutdown(ssl);
        return 1;
        //kill(getpid(), SIGKILL);
    } else if (err == SSL_ERROR_SSL) {
        cout << "SYSCALL"<<endl;
        SSL_shutdown(ssl);
        return 1;
        //kill(getpid(), SIGKILL);
    } else {
        cout << "SYSCALL"<<endl;
        SSL_shutdown(ssl);
        return 1;
        //kill(getpid(), SIGKILL);
    }
}

string Loop::getCMD(string buff){
	if(Contain(buff,"|") && strlen((const char*)buff.c_str()) > 3){   
        vector<string> cmd = split(buff,'|');
        if(cmd.size() > 0){
            return cmd.at(0);
        }else{
            return "error";
        }
    }	
}

bool Loop::sendMsg(string msg, SSL *ssl){
    // Message
    char * reply = (char *)msg.c_str();
    // Send message
    int received = SSL_write(ssl, reply, strlen(reply));
    return received;
    // get error
    // end = sslError(ssl, received);
    // if(end > 0){ break;}
}

// Validate user credentials
bool Loop::Authenticate(string email, string pass){        
    // check in db if user exists
    if (email == "user" && pass == "pass"){     
        // User id in db
        long long userID = 123;   
        return 1;
    }
    return 0;
}

bool Loop::Auth(string buff, SSL *ssl, string ipAddress){

    if(Contain(buff,"|") && strlen((const char*)buff.c_str()) > 3){
        buff = replaceAll(buff,"\\r\\n","");    
        vector<string> cmd = split(buff,'|');        
        string c = cmd.at(0);        
        string mail = "";
        string pass = "";        

        if(cmd.size() >= 3 && cmd.size() < 5){
            mail = cmd.at(1);
            pass = cmd.at(2);
        }else{
            return 0;
        }

        // CMD      
        cout << "[AUTH_CMD] " << c << endl;  
        cout << "[AUTH_CMD] " << buff << " size: " << cmd.size() <<  endl;

        if (c == "auth"){
            cout << "[AUTH_CMD]" << endl;
            cout << "[AUTH_EMAIL] " << mail << endl;
            cout << "[AUTH_PASS] " << pass << endl;
            cout << "[AUTH] " << Authenticate(mail,pass) << endl;
            // validate user credentials
            return Authenticate(mail,pass);
        }
       
    }else{
        cout << "[ERROR_CMD] " << buff << " IP " << ipAddress << endl;        
    }    
    return 0;
}

int Loop::getCmdAll(string buff, SSL *ssl){
    cmdCnt += 1;
    if(Contain(buff,"|") && strlen((const char*)buff.c_str()) > 3 && cmdCnt <= cmdLimit){   
        buff = replaceAll(buff,"\\r\\n","");     
        vector<string> cmd = split(buff,'|');        
        string c = cmd.at(0);
        string n1 = "";
        string n2 = "";
        string n3 = "";

        if(cmd.size() >= 2 && cmd.size() <= 5){            
            n1 = cmd.at(1);
        }else if(cmd.size() >= 3 && cmd.size() <= 5){            
            n1 = cmd.at(1);
            n2 = cmd.at(2);
        }else{
            return 0;        
        }
        
        // CMD      
        cout << "[CMD] " << c << endl;  
        cout << "[CMD] " << buff << " size: " << cmd.size() <<  endl;

        if (c == "from"){
            cout << "[FROM_CMD]" << endl;
            cout << "[FROM_EMAIL] " << n1 << endl;
            cout << "[FROM_NAME] " << n2 << endl;
            if(validEmail(n1)){
                from = buff;                
                return 1;
            }
        }
        if (c == "to"){
            cout << "[TO_CMD]" << endl;
            cout << "[TO_EMAIL] " << n1 << endl;
            cout << "[TO_NAME] " << n2 << endl;
            // validate user email
            if(validEmail(n1)){
                to.push_back(buff);
                return 1;
            }
        }
        if (c == "bcc"){
            cout << "[BCC_CMD]" << endl;
            cout << "[BCC_EMAIL] " << n1 << endl;
            cout << "[BCC_NAME] " << n2 << endl;
            bcc.push_back(buff);
            return 1;
        }
        if (c == "subject"){
            cout << "[SUB_CMD]" << endl;
            cout << "[SUB_TEXT] " << n1 << endl;            
            subject = n1;
            return 1;
        }
        if (c == "data"){
            cout << "[DATA_CMD]" << endl;
            cout << "[DATA_TEXT] " << n1 << endl;

            // Message
            char reply[] = "100|Send html/txt message\r\n";
            // Send message
            int received = SSL_write(ssl, reply, strlen(reply));

            // Total size
            long long TotalReceived = 0;

            // buffer
            const int readSize = 8192;
            char buffer[readSize];

            while(1){
                // clear buffer 
                memset(buffer, 0, sizeof buffer);
                buffer[0] = '\0';

                // Read from client
                int received = SSL_read (ssl, buffer, sizeof(buffer));
                TotalReceived += received;

                // get error                
                if(sslError(ssl, received) > 0){ 
                    return 3;
                }

                data.push_back(buffer);

                if(Contain(buffer, "[END].[END]") || Contain(buffer, "\\r\\n.\\r\\n")){
                    cout << "[DATA_SIZE] " << TotalReceived << endl;                    
                    return 1;
                }
            }            
            return 0;
        }    
        if (c == "file"){
            cout << "[FILE_CMD]" << endl;
            cout << "[FILE_NAME] " << n1 << endl;
            cout << "[FILE_ID] " << n2 << endl;            

            n1 = replaceAll(cmd.at(1)," ", "");
            n2 = replaceAll(cmd.at(2)," ", "");

            if (strlen(n1.c_str()) == 0 && strlen(n2.c_str()) == 0){
                return 0;
            }
            // Message
            char reply[] = "100|Send file content (base64)\r\n";

            // Send message
            int received = SSL_write(ssl, reply, strlen(reply));

            // Total size
            long long TotalReceived = 0;

            // buffer
            const int readSize = 8192;
            char buffer[readSize];

            // file 
            vector<string> file;

            while(1){
                // clear buffer 
                memset(buffer, 0, sizeof buffer);
                buffer[0] = '\0';

                // Read from client
                int received = SSL_read (ssl, buffer, sizeof(buffer));
                TotalReceived += received;

                // get error                
                if(sslError(ssl, received) > 0){ 
                    return 3;
                }
                // Single file
                file.push_back(buffer);

                if(Contain(buffer, "[END].[END]") || Contain(buffer, "\r\n.\r\n")){
                    // Add to all files
                    files.push_back(file);
                    cout << "[FILE_SIZE] " << TotalReceived << endl;
                    return 1;
                }
            }            
            return 0;
        }          
        if (c == "send"){
            cout << "[SEND_CMD]" << endl;            
            return 2;
        }    
        return 0;
    }
}