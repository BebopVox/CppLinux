#include "loop.h"

#include <cstring> // strlen
#include <string>
#include <vector>

using namespace std;

// string Loop::from = "";
// string Loop::subject = "";

Loop::Loop(){
    logi << "###[" << time(0) << "]###" << endl;
    // random hash divider
    newHash();
}
// Loop::~loop(){}

unsigned long Loop::getMicrotime(){  
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000; 
    // cout << ms << " microseconds " << endl;
    return ms;
}

string Loop::currentDateTimeSMTP(){
    // current date/time based on current system
   time_t now = time(0);   
   // convert now to string form
   char* dt = ctime(&now);   
   dt[strlen(dt)-1] = '\0';
   return std::string(dt);
}

string Loop::getOnlineUsers(){
    vector<string> users;
    users.push_back("123"); 
    users.push_back("555"); 
    users.push_back("654"); 
    ostringstream list;
    for (int i = 0; i < users.size(); i++){
        list << users.at(i) << "|";
    }
    return list.str();
}

string Loop::newHash(){    
    ostringstream h;
    h << "-----[XXX" << getMicrotime() << "ZZZ]-----";
    this->hash = h.str();
    return this->hash;
}

string Loop::getAccountInfo(){
    cout << "[ACCOUNT_ID] " << this->userID << endl;
    return "Account info|userID:1234567890|Username:Zenek";
}

string Loop::getAds(long long id){
    return "<h1>Reklama produktu w HTML</h1>";
}

bool Loop::validEmail(string email){
    logi << "[VALIDATE_EMAIL] " << email << endl;
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
        // std::logi << "[SSL_OK] " << err << endl;
    } else if (err == SSL_ERROR_WANT_READ ) {
        SSL_shutdown(ssl);
        return 1;
        //kill(getpid(), SIGKILL);
    } else if (err == SSL_ERROR_SYSCALL) {
        logi << "SYSCALL"<<endl;
        SSL_shutdown(ssl);
        return 1;
        //kill(getpid(), SIGKILL);
    } else if (err == SSL_ERROR_ZERO_RETURN) {
        logi << "SYSCALL"<<endl;
        SSL_shutdown(ssl);
        return 1;
        //kill(getpid(), SIGKILL);
    } else if (err == SSL_ERROR_SSL) {
        logi << "SYSCALL"<<endl;
        SSL_shutdown(ssl);
        return 1;
        //kill(getpid(), SIGKILL);
    } else {
        logi << "SYSCALL"<<endl;
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
        userID = 123;   
        cout << "[USER_ID] " << userID << endl;
        return 1;
    }
    return 0;
}

bool Loop::Auth(string buff, SSL *ssl, string ipAddress){
    this->cmdCnt += 1;
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
        logi << "[AUTH_CMD] " << c << endl;  
        logi << "[AUTH_CMD] " << buff << " size: " << cmd.size() <<  endl;

        if (c == "auth"){
            logi << "[AUTH_CMD]" << endl;
            logi << "[AUTH_EMAIL] " << mail << endl;
            // logi << "[AUTH_PASS] " << pass << endl;
            int isauth = Authenticate(mail,pass);
            logi << "[AUTH] " << isauth << endl;
            // validate user credentials
            return isauth;
        }
       
    }else{
        logi << "[ERROR_CMD] " << buff << " IP " << ipAddress << endl;        
    }    
    return 0;
}

int Loop::getCmdAll(string buff, SSL *ssl){
    this->cmdCnt += 1;
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
        logi << "[CMD] " << c << endl;  
        logi << "[CMD] " << buff << " size: " << cmd.size() <<  endl;

        if (c == "from"){
            logi << "[FROM_CMD]" << endl;
            logi << "[FROM_EMAIL] " << n1 << endl;
            logi << "[FROM_NAME] " << n2 << endl;
            if(validEmail(n1)){
                from = buff;                
                return 1;
            }
        }
        if (c == "to"){
            logi << "[TO_CMD]" << endl;
            logi << "[TO_EMAIL] " << n1 << endl;
            logi << "[TO_NAME] " << n2 << endl;
            // validate user email
            if(validEmail(n1)){
                to.push_back(buff);
                return 1;
            }
        }
        if (c == "bcc"){
            logi << "[BCC_CMD]" << endl;
            logi << "[BCC_EMAIL] " << n1 << endl;
            logi << "[BCC_NAME] " << n2 << endl;
            bcc.push_back(buff);
            return 1;
        }
        if (c == "subject"){
            logi << "[SUB_CMD]" << endl;
            logi << "[SUB_TEXT] " << n1 << endl;            
            subject = n1;
            return 1;
        }
        if (c == "data"){
            logi << "[DATA_CMD]" << endl;
            logi << "[DATA_TEXT] " << n1 << endl;

            // Message
            char reply[] = "100|Send html/txt message\r\n";
            // Send message
            int received = SSL_write(ssl, reply, strlen(reply));

            // Total size
            long long TotalReceived = 0;

            // buffer
            const int readSize = 8192;
            char buffer[readSize];

            // Add hash divider
            data.push_back(hash);

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
                    logi << "[DATA_SIZE] " << TotalReceived << endl;                                   
                    return 1;
                }
            }            
            return 0;
        }    
        if (c == "file" && disableFiles == 0){
            logi << "[FILE_CMD]" << endl;
            logi << "[FILE_NAME] " << n1 << endl;
            logi << "[FILE_ID] " << n2 << endl;            

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

            // hash divider
            vector<string> file;
            file.push_back(hash);
            file.push_back(n1);
            file.push_back(n2);
            file.push_back("\r\n");

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
                    logi << "[FILE_SIZE] " << TotalReceived << endl;
                    return 1;
                }
            }            
            return 0;
        }          
        if (c == "send"){
            logi << "[SEND_CMD]" << endl;            
            return 2;
        }
        // INFO CHANEL
        if (c == "account"){                       
            // User account info
            string account = getAccountInfo();       
            logi << "[ACCOUNT_CMD] " << account << endl; 
            // Message
            ostringstream ms;
            ms << "100|" << account << "|";
            string out = ms.str().append("\r\n");
            char *r2 = (char *)out.c_str();
            // Send message
            int received = SSL_write(ssl, r2, strlen(r2));
            // get error                
            if(sslError(ssl, received) > 0){                 
                return 3;
            }  
            return 4;
        }
        if (c == "ads"){
            logi << "[ADS_CMD]" << endl;  
            logi << "[ADS_ID] " << n1 << endl;          
            // Ads id
            long long adsID = atoll(n1.c_str());            
            // User account info
            string ads_html_b64 = getAds(adsID);
            // Message
            ostringstream ms;
            ms << "100|" << ads_html_b64 << "|";
            string out = ms.str().append("\r\n");
            char *r3 = (char *)out.c_str();
            // Send message
            int received = SSL_write(ssl, r3, strlen(r3));
            // get error                
            if(sslError(ssl, received) > 0){                 
                return 3;
            }            
            return 4;
        }
        if (c == "online"){
            logi << "[ONLINE_CMD]" << endl;
            // User account info
            string online = getOnlineUsers();
            // Message
            ostringstream ms;
            ms << "100|" << online << "|";
            string out = ms.str().append("\r\n");
            char *r3 = (char *)out.c_str();
            // Send message
            int received = SSL_write(ssl, r3, strlen(r3));
            // get error                
            if(sslError(ssl, received) > 0){                 
                return 3;
            }            
            return 4;
        }
        return 0;
    }
    return 0;
}