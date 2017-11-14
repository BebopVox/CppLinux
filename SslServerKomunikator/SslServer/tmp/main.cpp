/*
* Breakermind Server (breakermind.com)
* Author: Marcin Łukaszewski
* Contact: hello@breakermind.com
* 2017 All rights reserver
* Copyrights 2017
*/

// thread example
// g++ main.cpp  -std=c++11 -pthread 
// sslsmtpex.h sslsmtpex.cpp db.h db.cpp
// mysql 
// apt-get install libmysql++
// apt-get install libmysql++-dev
// apt-get install openssl libssl-dev g++
// no exceptions
// -fno-exceptions
// sprintf(query, "SELECT Id FROM audiencia WHERE data LIKE ('%s') ...", data); 
// %i, %s, %f, %u, %c
// Add in mysql database:
// set global max_connections = 1000;
// compile:
// g++ -o start main.cpp -std=c++11 -pthread -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql -Wall -Wextra -pedantic -std=c++14 db.h db.cpp sslsmtpex.h sslsmtpex.cpp dnsspf.cpp dnsspf.h -lssl -lcrypto -lresolv md5.cpp md5.h base64.cpp base64.h breakermindsslserver.cpp breakermindsslserver.h dkim.cpp dkim.h -L. -I. libpdkim1.a pdkim1.h

#include <iostream>       // std::cout
#include <thread>         // std::thread
// sleep
#include <unistd.h>
// mysql
#include <mysql.h>
// vector
#include <vector>
// string
#include <string>
#include <string.h>
// db.h
#include "db.h"
#include "dnsspf.h"
#include "breakermindsslserver.h"

// time
#include <stdio.h>
#include <time.h>
// signals, abort
#include <signal.h>
// regex
#include <sys/types.h>
#include <sys/stat.h>
#include <regex>

#include <stdio.h>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <sstream>


using namespace std;

string settings[100];

bool SaveToFile(string filename, string text){
    try{
        // save to file
        std::ofstream outfile;
        mkdir("files", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        outfile.open("files/" + filename + ".log", std::ios_base::app);
        if(outfile.good() && outfile.is_open()) outfile << text << endl;
        outfile.close();
        return 1;
    }catch(const std::exception &exc){
        return 0;
    }
}

// thread worker function
void boo(int x, string serverHost, int sendLimit, string mysqlhost, string mysqlport, string mysqluser, string mysqlpass, string mysqldb)
{
	while(1){
		try{
			int j = 0; // counter
			time_t now = time(NULL);
			string ct = std::string(ctime(&now));			
			ct[strlen(ct.c_str())-1] = '\0';
			cout << "[" << ct << "] Starting thread loop " << x << endl;
			//usleep(10000000); // microsec
			sleep(10); // seconds

			DB db = DB();
			try{	
			    cout << "[STARTING_THREAD] " << x << " " << db.currentDateTime() << endl;
			    int ok = db.Connect(mysqlhost,mysqlport,mysqluser,mysqlpass,mysqldb);		
			    while(ok){    			    	
				    // vector<vector<string>> list = db.getMessagesToSend(5);
				    db.ServerHost(serverHost);
				    db.SendMessages(sendLimit);
				    sleep(1);
				    // counter
				    if(j > 300){
				    	cout << time(0) << "[NOTICE] Thread " << x << " working " << " " << db.currentDateTime() << endl;
				    	// validate email
				    	// cout << db.validEmail("helo.al-jon_ek@ddd.tttt-yyyy.com") << endl;
				    	j = 0;
				    }
				    j++;
				}		    
			}catch (std::exception &e) {
			    cout << "# ERR: ThreadException in " << __FILE__;
			    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			    cout << "# ERR: " << e.what();
			    continue;
			}
			db.Close();			
		}catch (std::exception &e) {
		    cout << "# ERR: ThreadDBException in " << __FILE__;
		    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		    cout << "# ERR: " << e.what();
		    continue;
		}
	}
}

// Custom error prevent disable app
extern "C" void handle_aborts(int signal)
{
    // cout << "ErrorSignal " << std::strerror(signal) << " " << __FILE__ << " " << __FUNCTION__ << " line: " << __LINE__ << endl;
    cout << "ErrorSignal " << std::strerror(signal) << " " << __FUNCTION__ << " line: " << __LINE__ << endl;
    throw std::runtime_error("!!!!! Error setting up signal handlers !!!!!");
}

vector<string> split(string s, char delim) {
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

// // time microseconds
unsigned long microtime(){	
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;	
	// cout << ms << " microseconds " << endl;
	return ms;
}

vector<string> findCc(string string)
{
    vector<std::string> ve;
    ve.clear();   
    try{
	    // single email: /^(\w+)(\.|_|-)?(\w*)@(\w+)(\.(\w+))$/ig
	   // const std::regex pattern("(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+");
	   std::regex pattern("((CC:).*)", regex_constants::icase);
	   std::sregex_iterator iter(string.begin(), string.end(), pattern);
	   std::sregex_iterator end;
	   while(iter != end) {       
	       for(unsigned i = 0; i < iter->size(); i++){           
	           ve.push_back((*iter)[i]);
	           break;
	       }
	       ++iter;
	   }
   }catch(...) {	    
		cout << "Regex error findCc()" << endl;
		return ve;
	}
   return ve;
}

vector<string> findBcc(string string)
{
    vector<std::string> ve;
    ve.clear();   
    try{
	    // single email: /^(\w+)(\.|_|-)?(\w*)@(\w+)(\.(\w+))$/ig
	   // const std::regex pattern("(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+");
	   std::regex pattern("((BCC:).*)", regex_constants::icase);
	   std::sregex_iterator iter(string.begin(), string.end(), pattern);
	   std::sregex_iterator end;
	   while(iter != end) {       
	       for(unsigned i = 0; i < iter->size(); i++){           
	           ve.push_back((*iter)[i]);
	           break;
	       }
	       ++iter;
	   }
   }catch(...) {	    
		cout << "Regex error findBcc()" << endl;
		return ve;
	}
   return ve;
}

std::string getStringBetween(const std::string s, const std::string start_delim, const std::string &stop_delim){
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find_first_of(stop_delim, end_pos_of_first_delim);
    return s.substr(end_pos_of_first_delim, last_delim_pos - end_pos_of_first_delim);
}

std::string replaceAll( string s1, string search, string replace ) {
    for( size_t pos = 0; ; pos += replace.length() ) {
        // Locate the substring to replace
        pos = s1.find( search, pos );
        if( pos == string::npos ) break;
        // Replace by erasing and inserting
        s1.erase( pos, search.length() );
        s1.insert( pos, replace );
    }
    return s1;
}

std::string ReplaceString(std::string subject, const std::string& search,const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

vector<std::string> searchEmail(std::string string){
    vector<std::string> ve;
    ve.clear();   
    // single email: /^(\w+)(\.|_|-)?(\w*)@(\w+)(\.(\w+))$/ig
   // const std::regex pattern("(\\w+)(\\.|_|-)?(\\w*)@(\\w+)(\\.(\\w+))+");
   std::regex pattern("(((\\w+([-\\._])+)+|())\\w+@(\\w+([-\\.])+)+\\w+)");   
   std::sregex_iterator iter(string.begin(), string.end(), pattern);
   std::sregex_iterator end;
   while(iter != end){       
       for(unsigned i = 0; i < iter->size(); ++i){
           ve.push_back((*iter)[0]);
       }
       ++iter;
   }
   sort(ve.begin(),ve.end());
   ve.erase(unique(ve.begin(),ve.end()), ve.end());
   return ve;
}

string removeBcc(string s){
    std::regex reg("((BCC:)(.*))", regex_constants::icase);   // matches words beginning by "sub"	
	return std::regex_replace (s,reg,"");
}

vector<string> getCcEmails(string mimieheader){	
	// cut all bcc: (ukryte do wiadomości - blind carbon copy)
	vector<string> bcc = findBcc(mimieheader);		
	for (unsigned int i = 0; i < bcc.size(); ++i) {	
		mimieheader = replaceAll(mimieheader,std::string(bcc.at(i)), "");
		// mimieheader = ReplaceString(mimieheader,std::string(bcc.at(i)), "");				    	    
	}	
	// cout << "MIME " << mimieheader << endl;
	// Cut all CC: (do wiadomości DW - carbon copy)
	vector<string> emails;
	vector<string> cc = findCc(mimieheader);	
	for (unsigned int i = 0; i < cc.size(); i++) {
		// cout << "Emails ALL " << cc.at(i) << endl;
		vector<string> e = searchEmail(cc.at(i));	
		for (unsigned int j = 0; j < e.size(); j++){
			cout << e.at(j) << endl;
			emails.push_back(e.at(j));
		}	
		//break;
	}
	sort(emails.begin(),emails.end());
   	emails.erase(unique(emails.begin(),emails.end()),emails.end());
	return emails;
}

vector<string> getBccEmails(string mimieheader){	
	vector<string> emails;
	vector<string> cc = findBcc(mimieheader);	
	for (unsigned int i = 0; i < cc.size(); i++) {
		// cout << "Emails ALL " << cc.at(0) << endl;
		vector<string> e = searchEmail(cc.at(i));	
		for (unsigned int j = 0; j < e.size(); j++){
			cout << e.at(j) << endl;
			emails.push_back(e.at(j));
		}	
		break;
	}
	sort(emails.begin(),emails.end());
   	emails.erase(unique(emails.begin(),emails.end()),emails.end());
	return emails;
}

int main() {	

	// Default settings file if not exists create default
    BreakermindSslServer setdef;
    char * file = (char*)std::string("settings.cnf").c_str();
    setdef.createDefaultSettings(file);

    // load settings from file
    string line;
    ifstream myfile ("settings.cnf"); // run server folder
    if (myfile.is_open()) {
        int ii = 0;
        while (getline(myfile,line)){
            try{
                // cout << line << '\n';
                vector<string> set = BreakermindSslServer::splitDelimiter(line, "=");
                settings[ii++] = set.at(1);
                // std::cout << std::string(set.at(0)) << " " << std::string(set.at(1));
            }catch(std::exception &e){
                cout << "Loading setings...";
            }
        }
        myfile.close();
    }else{
        cout << "Unable to open file: " + std::string(get_current_dir_name()) + "/settings.cnf \n";
        return 0;
    }

	while(1){	
		
		try{
			cout << "MYSQL " << settings[1] << " " << settings[2] << " " << settings[3] << " " << settings[4] << endl;
			// database load settings		    
			DB db = DB();
		    db.Connect(settings[1],settings[2],settings[3],settings[4],"breakermindsmtp");
		    // Create database and tables
		    db.CreateTables();
		    db.Close();
		}catch(...){
			cout << "[CREATE_DATABASE_ER]" << endl;			
		}		    

		try{
			// signals, abort ...
			signal(SIGABRT, &handle_aborts);
			signal(SIGFPE, &handle_aborts);

			string serverHost = std::string(settings[6]); // hostname ESMPT
			// ile wiadomości na sekundę z tredu (Wiadomości na sekundę = liczba tredów * sendLimit)			
			int sendLimit = atoi(settings[19].c_str()); // Thread message limit
			// run thread in array
			static const int num_threads = atoi(settings[20].c_str()); // Threads number
			// Threads array (ile tredów)
			std::thread t[num_threads];
			//Launch a group of threads with server host name		
			for (int i = 0; i < num_threads; i++) { 
				// Run new thread
				t[i] = std::thread(boo,i,serverHost,sendLimit,settings[1],settings[2],settings[3],settings[4],"breakermindsmtp"); 
			}
			cout << "Main, thread now execute concurrently...\n" << endl;
			// synchronize threads:
			// for (int i = 0; i < num_threads; ++i) { t[i].join(); }
			
			int ServerPort = atoi(settings[14].c_str());
			if(ServerPort < 0){
				ServerPort = 25;
			}
			// Server starts here
			BreakermindSslServer boom;		    
		    boom.Info();		    		    
		    boom.Start(ServerPort,"certificate.pem", "private.key");

			/*
			while(1){
				time_t now = time(0);
				cout << "### Main thread looooop " << ctime(&now) << endl;
				sleep(5);
			} 
			*/ 				
		}catch (const std::runtime_error &ee) {
		    // błąd runtime 
		    // std::cerr << "Runtime error: " << ee.what() << std::endl;
		    cout << "Runtime error: " << ee.what() << std::endl;
		    continue;
		}catch (std::bad_alloc &e) {
        	// std::bad_alloc::what
        	cout << "Allocation error " << e.what() << endl; 
        	continue;
    	}catch (std::exception &e) {
		    cout << "# ERR: MainErrorException in " << __FILE__;
		    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		    cout << "# ERR: " << e.what() << endl;
		    continue;
		}catch(...) {
		    // nieznany błąd
    		cout << "Unknown failure occurred. Possible memory corruption" << std::endl;
    		continue;
		}
	}
}



/*
// replace all
string input = "hello\r\nco u was\r\n";
std::string::size_type pos = 0;
while ((pos = input.find("\r\n", pos)) != std::string::npos){
     input.replace(pos, 1, "\n");
}
cout << input << endl;
*/

/*
	// signal(SIGILL, &handle_aborts);
	// signal(SIGINT, &handle_aborts);
	// signal(SIGSEGV, &handle_aborts);
	// signal(SIGTERM, &handle_aborts);

	// std::thread t1 (boo,1);  // spawn new thread that calls boo(1)
	// std::thread t2 (boo,2);  
	// std::cout << "main, boo now execute concurrently...\n" << endl;
	// synchronize threads:
	//t1.join();                // pauses until first finishes
	//t2.join();               // pauses until second finishes

*/

/*
	vector<string> spflist1 = dns.getDnsSPF("qflash.pl");
	for (unsigned int i = 0; i < spflist1.size(); ++i)
	{
		cout << "Validate mx host " << spflist1.at(i) << endl;
		vector<string> redirects;
		cout << "DNS IP is (qflash): " << dns.validSpfIP("92.222.7.98", "qflash.pl", spflist1.at(i), redirects) << endl;
	}
	
	// Show spf records "gmail.com", "_netblocks.google.com", "_spf.google.com"
	vector<string> spflist = dns.getDnsSPF("gmail.com");
	for (unsigned int i = 0; i < spflist.size(); ++i)
	{
		cout << "Validate mx host " << spflist.at(i) << endl;
		vector<string> redirects;
		cout << "DNS IP is: " << dns.validSpfIP("173.194.0.123", "gmail.com", spflist.at(i), redirects) << endl;
	}
*/

/* 
// Replace empty lines
// while ( mimieheader.find ("\r\n") != string::npos ) {
	// mimieheader.erase ( mimieheader.find ("\r\n"), 2 );
	// mimieheader.erase(std::remove(mimieheader.begin(), mimieheader.end(), '\n'), mimieheader.end());
// }
*/