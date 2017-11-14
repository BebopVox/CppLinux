/*
* Breakermind Server (breakermind.com)
* Author: Marcin Łukaszewski
* Contact: hello@breakermind.com
* 2017 All rights reserver
* Copyrights 2017
*/

#include "db.h"

#include <sstream>
#include <regex>

DB::DB(){}

// set esmtp hostname
void DB::ServerHost(string serverHost = "localhost.loc"){
	ServerHostname = serverHost;
}

// Connect to database
bool DB::Connect(string host = "localhost", string port = "3306", string user = "root", string pass = "toor", string db = "breakermindsmtp"){
	try{
		//MYSQL *connect = NULL;
		//connect = mysql_init(connect);
		// init mysql		 		  	
		connect=mysql_init(NULL);		
		mysql_options(connect, MYSQL_SET_CHARSET_NAME, "utf8mb4");
	  	mysql_options(connect, MYSQL_INIT_COMMAND, "SET NAMES utf8mb4");
	  	// Allow reconnections
	  	my_bool recon=true;
	  	mysql_options(connect, MYSQL_OPT_RECONNECT, &recon);
	  	// Connection time out
	  	// mysql_options(connect, MYSQL_OPT_CONNECT_TIMEOUT, "60");
		if (!connect){
		    cout << "[ERROR_MYSQL_INIT] MySQL Initialization failed" << std::strerror(errno) << endl;
		    return 0;
		}
		connect=mysql_real_connect(connect, host.c_str(), user.c_str(), pass.c_str(), db.c_str(), atoi(port.c_str()),NULL,0);
		if (connect){		
			cout << "[NOTICE] MySQL Connection Succeeded\n";		
			//mysql_query(connect, "set global max_connections = 1000;");
			return 1;
		}else{
			cout << "[ERROR_MYSQL_CONN] MySQL Connection failed (Restarting threads...wait)\n";
			return 0;
		}			
	} catch (std::exception &e) {
        cout << "# ERR: Mysql Exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();        
        return 0;
    }
}

// check if ip address exists for this mailbox
bool DB::validAuthIP(string email, std::string ip){
    try {
    	MYSQL_RES *res_set;
		MYSQL_ROW row;

		// Select user
		char query[500];
		sprintf (query, "SELECT COUNT(id) > 0 as cntall FROM allowedip WHERE email = '%s' AND ip_addr = '0.0.0.0' OR email = '%s' AND ip_addr = '%s';", email.c_str(), email.c_str(), ip.c_str());
		int err = mysql_query(connect,query);	
		if(err){
	      cout << mysql_error(connect);
	      return 0;	      
	  	}		
		res_set = mysql_store_result(connect);
		while (((row = mysql_fetch_row(res_set)) !=NULL )){
			return std::stoi(row[0]);
		}
        return 0;
    } catch (std::exception &e) {        
        cout << "# ERR: Mysql in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;  
        cout << mysql_error(connect) << endl;           
        return 0;
    }
}

unsigned long long  DB::userID(string email){
    try {
    	MYSQL_RES *res_set;
		MYSQL_ROW row;

		// Select user
		char query[500];
		sprintf (query, "SELECT id,email FROM mailbox WHERE email = '%s' AND active = 1 AND ban = 0;", email.c_str());
		int err = mysql_query(connect,query);	
		if(err){
			cout << mysql_error(connect);
			return 0;      
	  	}
		res_set = mysql_store_result(connect);
		while (((row = mysql_fetch_row(res_set)) !=NULL )){
			return std::stoi(row[0]);
		}
        return 0;
    } catch (std::exception &e) {        
        cout << "# ERR: Mysql in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;  
        cout << mysql_error(connect) << endl;           
        return 0;
    }	    
}

bool DB::isMailboxExists(string email){
    try {
    	MYSQL_RES *res_set;
		MYSQL_ROW row;

		// Select user
		char query[500];
		sprintf (query, "SELECT COUNT(id) > 0 as cntall FROM mailbox WHERE email = '%s' AND active = 1 AND ban = 0;", email.c_str());
		int err = mysql_query(connect,query);	
		if(err){
			cout << mysql_error(connect);
			return 0;      
	  	}
		res_set = mysql_store_result(connect);
		while (((row = mysql_fetch_row(res_set)) !=NULL )){
			return std::stoi(row[0]);
		}
        return 0;
    } catch (std::exception &e) {        
        cout << "# ERR: Mysql in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;  
        cout << mysql_error(connect) << endl;           
        return 0;
    }	    
}

bool DB::isLocalDomain(string email){
    try {
    	MYSQL_RES *res_set;
		MYSQL_ROW row;
	
		vector<string> ema = splitDelimiter(email,"@");
		if(ema.size() != 2){ return 0; }
        string domain = ema.at(ema.size()-1);		

		// Select user
		char query[500];
		sprintf (query, "SELECT COUNT(id) > 0 as cntall FROM domains WHERE domainname = '%s' AND active = 1 AND ban = 0;", domain.c_str());
		int err = mysql_query(connect,query);	
		if(err){
			cout << mysql_error(connect);
			return 0;      
	  	}		
		res_set = mysql_store_result(connect);
		while (((row = mysql_fetch_row(res_set)) !=NULL )){
			return std::stoi(row[0]);
		}        
    } catch (std::exception &e) {        
        cout << "# ERR: Mysql in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;  
        cout << mysql_error(connect) << endl;           
        return 0;
    }	 
    return 0;   
}

// validate user credentials
bool DB::isAuthenticate(string email, string pass){
    try {
    	MYSQL_RES *res_set;
		MYSQL_ROW row;

		// Select user
		char query[500];
		sprintf (query, "SELECT COUNT(id) > 0 as cntall FROM mailbox WHERE email = '%s' AND pass = '%s' AND active = 1 AND ban = 0;", email.c_str(), pass.c_str());
		int err = mysql_query(connect,query);	
		if(err){
			cout << "Error : " << mysql_error(connect);
			return 0;      
	  	}
		res_set = mysql_store_result(connect);
		while (((row = mysql_fetch_row(res_set)) !=NULL )){
			return std::stoi(row[0]);
		}
        return 0;
    } catch (std::exception &e) {        
        cout << "# ERR: Mysql in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;  
        cout << mysql_error(connect) << endl;           
        return 0;
    }	    
}

bool DB::checkBanIpLimit(int limit, int minutes, string ip_address){
    try {
    	MYSQL_RES *res_set;
		MYSQL_ROW row;

		// Select user
		char query[500];
		sprintf (query, "SELECT COUNT(id) > %i as cntall FROM banip WHERE ip_address = '%s' AND time > NOW() - INTERVAL %i MINUTE;", limit, ip_address.c_str(), minutes);
		int err = mysql_query(connect,query);	
		if(err){
			cout << mysql_error(connect);
			return 0;      
	  	}
		res_set = mysql_store_result(connect);
		while (((row = mysql_fetch_row(res_set)) !=NULL )){
			return std::stoi(row[0]); // cntall
		}
        return 0;
    } catch (std::exception &e) {        
        cout << "# ERR: Mysql in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;  
        cout << mysql_error(connect) << endl;           
        return 0;
    }
}

// cout if distinct ip limit reached
bool DB::checkDDOSLimit(int iplimit, int minutes){
    try {
    	MYSQL_RES *res_set;
		MYSQL_ROW row;

		// Select user
		char query[500];
		sprintf (query, "SELECT DISTINCT COUNT(id) >= %i as cntall FROM banip WHERE time > NOW() - INTERVAL %i MINUTE;", iplimit, minutes);
		int err = mysql_query(connect,query);	
		if(err){
			cout << mysql_error(connect);
			return 0;      
	  	}
		res_set = mysql_store_result(connect);
		while (((row = mysql_fetch_row(res_set)) !=NULL )){
			return std::stoi(row[0]); // cntall
		}
        return 0;
    } catch (std::exception &e) {        
        cout << "# ERR: Mysql in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;  
        cout << mysql_error(connect) << endl;           
        return 0;
    }	
}

unsigned long long DB::LastInsertID(){

    try {
    	MYSQL_RES *res_set;
		MYSQL_ROW row;
		// Select id
		int err = mysql_query(connect,"SELECT LAST_INSERT_ID() as id");	
		if(err){
			cout << mysql_error(connect);
			return 0;      
	  	}
		res_set = mysql_store_result(connect);
		while (((row = mysql_fetch_row(res_set)) !=NULL )){
			return (unsigned long long) std::stoi(row[0]); // cntall
		}
        return 0;
    } catch (std::exception &e) {        
        cout << "# ERR: Mysql in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;  
        cout << mysql_error(connect) << endl;           
        return 0;
    }	
}

unsigned long long DB::InsertBanIP(string ip){
	try{
		// update	
		char sql[200];
		sprintf(sql,"INSERT INTO banip(ip_address) VALUES('%s');",ip.c_str());
		int err = mysql_query(connect,sql);	
		if(err){
			cout << mysql_error(connect);
			return 0;      
	  	}
	  	unsigned long long id = LastInsertID();
        return id;
	} catch (std::exception &e) {
        cout << "# ERR: Mysql Exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();        
        return 0;
    }
}

unsigned long long DB::InsertMsg(string efrom, string efromname, string subject, string html){
    try{
		unsigned long long id = 0;		
		// stream
		std::ostringstream sql;
		sql << "INSERT INTO messages(efrom,efromname,subject,message,seen) VALUES('";		
		sql << Quotes(efrom) << "','";
		sql << Quotes(efromname) << "','";		
		sql << Quotes(subject) << "','";
		sql << Quotes(html) << "','";
		sql << "0);";
		//cout << "Query 0x... " << sql << " txt " << reQuotes(sql.str()) << endl;		
		int err = mysql_query(connect,(sql.str().c_str()));	
		if(err){
			cout << mysql_error(connect);
			return 0;      
	  	}
	  	id = LastInsertID();
        return id;
	} catch (std::exception &e) {
        cout << "# ERR: Mysql Exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();        
        return 0;
    } catch (...) {
        cout << "# ERR: (...) " << __FILE__<< " " << __FUNCTION__ << ") on line " << __LINE__ << endl;          
        return 0;
    }
}

unsigned long long DB::InsertMsgSingle(string efrom, string efromname, string eto, string etoname, string subject, long long msgId){
    try{
		unsigned long long id = 0;		
		// stream
		std::ostringstream sql;
		sql << "INSERT INTO messages_single(efrom,efromname,eto,etoname,subject,seen) VALUES('";		
		sql << Quotes(efrom) << "','";
		sql << Quotes(efromname) << "','";		
		sql << Quotes(eto) << "','";
		sql << Quotes(etoname) << "','";		
		sql << Quotes(subject) << "','";
		sql << msgId << "','";
		sql << "0);";
		//cout << "Query 0x... " << sql << " txt " << reQuotes(sql.str()) << endl;		
		int err = mysql_query(connect,(sql.str().c_str()));	
		if(err){
			cout << mysql_error(connect);
			return 0;      
	  	}
	  	id = LastInsertID();
        return id;
	} catch (std::exception &e) {
        cout << "# ERR: Mysql Exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();        
        return 0;
    } catch (...) {
        cout << "# ERR: (...) " << __FILE__<< " " << __FUNCTION__ << ") on line " << __LINE__ << endl;          
        return 0;
    }
}

// efrom,efromname,eto,etoname,subject,seen
// Select messages to send
vector<vector<string>> DB::getMessages(string fromEmail, string toEmail, int limit){
	
	vector<vector<string>> messages;
	
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	try{
		ostringstream que;
		que << "SELECT messages_single.id,messages_single.efrom,messages_single.efromname,messages_single.eto,messages_single.etoname,messages_single.subject,messages_single.active,messages_single.seen,messages.message FROM messages_single LEFT JOIN messages ON messages_single.messageid=messages.id WHERE messages_single.efrom = '"<< fromEmail <<"' AND messages_single.eto = '"<< toEmail <<"' AND messages_single.hide_from = 0 AND messages_single.active = 1 LIMIT " << limit;

		cout << que.str() << endl;
		string q = que.str();

		int err = mysql_query (connect,q.c_str());
		if(err){
	      fprintf(stderr, "%s\n", mysql_error(connect));
	  	}
		unsigned int i =0;
		res_set = mysql_store_result(connect);
		// unsigned int numrows = mysql_num_rows(res_set);
		// int num_fields = mysql_num_fields(res_set);
	
		while (((row = mysql_fetch_row(res_set)) !=NULL )){			

			cout << "Valid sender/recipient (send message) " << validEmail(row[i+2]) << "/" << validEmail(row[i+3]) << endl;
		  	if(validEmail(row[i+1]) && validEmail(row[i+3])){
				// add single row to vector string
				vector<string> msg;
				msg.push_back(reQuotes(row[i]));
				msg.push_back(reQuotes(row[i+1]));
				msg.push_back(reQuotes(row[i+2]));
				msg.push_back(reQuotes(row[i+3]));
				msg.push_back(reQuotes(row[i+4]));
				msg.push_back(reQuotes(row[i+5]));
				msg.push_back(reQuotes(row[i+6]));
				msg.push_back(reQuotes(row[i+7]));
				msg.push_back(reQuotes(row[i+8]));
				// add to messages
				messages.push_back(msg);
			}else{
				cout << "[INVALID_EXTERNAL_MSG_FORMAT!!!!]"<<endl;				
			}

			char query[500];
			sprintf (query, "UPDATE messages SET seen = 1 WHERE id=%i;", atoi(row[i]));			
			// cout << "Query: " << query << endl;			
			err = mysql_query (connect,query);
			if(err){
		      fprintf(stderr, "%s\n", mysql_error(connect));
		  	}		  	
		}		
		//mysql_free_result(res_set);
	}catch(std::exception &e){
		cout << "Error mysql class " << e.what() << endl;
		return messages;
	}		
	return messages;
}

string DB::Quotes(string s) {	
	/*
	std::size_t n = s.length();
    std::string escaped;
    escaped.reserve(n * 2);        // pessimistic preallocation
    for (std::size_t i = 0; i < n; ++i) {
        if (s[i] == '\\' || s[i] == '\'')
            escaped += '\\';
        if (s[i] == '\\' || s[i] == '\"')
            escaped += '\\';
        escaped += s[i];
    }    
    return escaped;    
    */
    return entitiesEncode(s);
}

string DB::reQuotes(string s) {
    return entitiesDecode(s);
    //return s;
}

string DB::entitiesDecode(string str) {	
	string subs[] = {"#semi#", "#amp#", "#quot#", "#apos#", "#lt#", "#gt#", "#colon#", "#equals#", "#excl#", "#slash#"};
	string reps[] = {";", "&", "\"", "'", "<", ">", ":", "=", "!", "\\"};	
	size_t found;
	for(int j = 0; j < 9; j++) {
		do {
			found = str.find(subs[j]);
	  		if (found != string::npos){
		    	str.replace(found,subs[j].length(),reps[j]);
		    }
    	} while (found != string::npos);
  	}  	
	return str;
}

string DB::entitiesEncode(string str) {	
	string subs[] = {";", "&", "\"", "'", "<", ">", ":", "=", "!", "\\"};	
	string reps[] = {"#semi#", "#amp#", "#quot#", "#apos#", "#lt#", "#gt#", "#colon#", "#equals#", "#excl#", "#slash#"};
	size_t found;
	for(int j = 0; j < 9; j++) {
		do {
			found = str.find(subs[j]);
	  		if (found != string::npos){
		    	str.replace(found,subs[j].length(),reps[j]);
		    }
    	} while (found != string::npos);
  	}
	return str;
}

bool DB::validEmail(std::string email){
   //std::regex pattern("(((\\w+([-\\._])+)+|())\\w+@(\\w+([-\\.])+)+\\w+)"); 
   //return std::regex_match(email, pattern);
	return 1;
}


// Update messages status
int DB::changeMessageStatus(int deliveredID){
	try{
		// update	
		char sql[100];
		sprintf(sql,"UPDATE messages SET send=send+100,resendtime=DATE_ADD(NOW(), INTERVAL 1 MINUTE) WHERE id=%i;",deliveredID);
		int err = mysql_query(connect,sql);	
		return err;
	} catch (std::exception &e) {
        cout << "# ERR: Mysql Exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();        
        return 0;
    }
}

// Update messages status
int DB::changeMessageStatusError(int deliveredID){
	try{
		// update	
		char sql[100];
		sprintf(sql,"UPDATE messages SET send=-9,resendtime=DATE_ADD(NOW(), INTERVAL 366 DAY) WHERE id=%i;",deliveredID);
		int err = mysql_query(connect,sql);	
		return err;
	} catch (std::exception &e) {
        cout << "# ERR: Mysql Exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();        
        return 0;
    }
}

// Close connection
void DB::Close(){
	mysql_close(connect);	
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
std::string DB::currentDateTime(){
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

// Date time like smtp date
char * DB::currentDateTimeSMTP(){
	// current date/time based on current system
   time_t now = time(0);   
   // convert now to string form
   char* dt = ctime(&now);   
   dt[strlen(dt)-1] = '\0';
   return dt;
}

// string delimiter
vector<string> DB::splitDelimiter(string str, string delim){
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
        // cout << token << endl;
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

void DB::CreateTables(){
    try{
        int err = mysql_query(connect,"CREATE DATABASE IF NOT EXISTS `breakermindsmtp` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;");
        if(err){ cout << mysql_error(connect);	}
    } catch (std::exception &e) {
      cout << " MySQL code: " << e.what();
    }

    try{
        int err = mysql_query(connect,"CREATE TABLE IF NOT EXISTS domains (id bigint NOT NULL AUTO_INCREMENT,domainname varchar(180) NOT NULL,description varchar(255) DEFAULT '',active int DEFAULT 1,ban int DEFAULT 0,time DATETIME DEFAULT CURRENT_TIMESTAMP, dkim_key TEXT, dkim_selector varchar(250) NOT NULL DEFAULT '', dkim_active int(1) DEFAULT 1, PRIMARY KEY (id),UNIQUE KEY `domainname` (`domainname`))ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 DEFAULT COLLATE utf8mb4_unicode_ci;");
        if(err){ cout << mysql_error(connect);	}
    } catch (std::exception &e) {
      cout << " MySQL code: " << e.what();
    }

    try{
        int err = mysql_query(connect,"CREATE TABLE IF NOT EXISTS mailbox (id bigint NOT NULL AUTO_INCREMENT,email varchar(180) NOT NULL,pass varchar(250) NOT NULL,name varchar(250) DEFAULT '',active int DEFAULT 1,ban int DEFAULT 0,time DATETIME DEFAULT CURRENT_TIMESTAMP, size bigint DEFAULT 0, admin int DEFAULT 0, phone varchar(250) DEFAULT '', PRIMARY KEY (id),UNIQUE KEY `email` (`email`))ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 DEFAULT COLLATE utf8mb4_unicode_ci;");
        if(err){ cout << mysql_error(connect);	}
    } catch (std::exception &e) {
      cout << " MySQL code: " << e.what();
    }

    try{
        int err = mysql_query(connect,"CREATE TABLE IF NOT EXISTS messages (id bigint NOT NULL AUTO_INCREMENT,uid bigint NOT NULL DEFAULT '0',email_from varchar(255) NOT NULL,email_to varchar(255) NOT NULL,email_to_name varchar(255) NOT NULL DEFAULT '',email_replyto varchar(255) NOT NULL DEFAULT '',email_bcc varchar(255) NOT NULL DEFAULT '',email_cc varchar(255) NOT NULL DEFAULT '',email_subject varchar(255) NOT NULL DEFAULT '',email_head text,email_html text,email_content longtext,email_files mediumtext,email_file text,folder int DEFAULT 1,flaged int DEFAULT 0,favorite int DEFAULT 0,seen int DEFAULT 0,send int DEFAULT 0,active int DEFAULT 1,ban int DEFAULT 0,threadid int DEFAULT 0,time DATETIME DEFAULT CURRENT_TIMESTAMP,resendtime DATETIME DEFAULT CURRENT_TIMESTAMP,spf int DEFAULT 0,size bigint(21) DEFAULT 0,spam int DEFAULT 0,answer int DEFAULT 0, PRIMARY KEY (id))ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 DEFAULT COLLATE utf8mb4_unicode_ci;");
        if(err){ cout << mysql_error(connect);	}
    } catch (std::exception &e) {
      cout << " MySQL code: " << e.what();
    }

    try{
        int err = mysql_query(connect,"CREATE TABLE IF NOT EXISTS banip (id bigint NOT NULL AUTO_INCREMENT,ip_address text,time DATETIME DEFAULT CURRENT_TIMESTAMP,PRIMARY KEY (id))ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 DEFAULT COLLATE utf8mb4_unicode_ci;");
        if(err){ cout << mysql_error(connect);	}
    } catch (std::exception &e) {
      cout << " MySQL code: " << e.what();
    }

    try{
        int err = mysql_query(connect,"CREATE TABLE IF NOT EXISTS contacts (id bigint NOT NULL AUTO_INCREMENT,mailboxid bigint NOT NULL DEFAULT 0,name varchar(250) NOT NULL,email varchar(250) NOT NULL,description text,time DATETIME DEFAULT CURRENT_TIMESTAMP,PRIMARY KEY (id))ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 DEFAULT COLLATE utf8mb4_unicode_ci;");
        if(err){ cout << mysql_error(connect);	}
    } catch (std::exception &e) {
      cout << " MySQL code: " << e.what();
    }

    try{
        int err = mysql_query(connect,"CREATE TABLE IF NOT EXISTS allowedip (id bigint NOT NULL AUTO_INCREMENT,email varchar(250) NOT NULL, ip_addr varchar(250) NOT NULL,time DATETIME DEFAULT CURRENT_TIMESTAMP,PRIMARY KEY (id))ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 DEFAULT COLLATE utf8mb4_unicode_ci;");
        if(err){ cout << mysql_error(connect);	}
    } catch (std::exception &e) {
      cout << " MySQL code: " << e.what();
    }

    try{
        int err = mysql_query(connect,"CREATE TABLE IF NOT EXISTS mxports (id bigint NOT NULL AUTO_INCREMENT,hostname varchar(250) NOT NULL, port int(11) NOT NULL DEFAULT 25,time DATETIME DEFAULT CURRENT_TIMESTAMP,PRIMARY KEY (id))ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 DEFAULT COLLATE utf8mb4_unicode_ci;");
        if(err){ cout << mysql_error(connect);	}
    } catch (std::exception &e) {
      cout << " MySQL code: " << e.what();
    }

    try{
        int err = mysql_query(connect,"CREATE TABLE IF NOT EXISTS folders (id bigint NOT NULL AUTO_INCREMENT,name varchar(250) NOT NULL,folderid bigint(21) NOT NULL DEFAULT 0, mailboxid bigint(21) NOT NULL DEFAULT 0,time DATETIME DEFAULT CURRENT_TIMESTAMP,PRIMARY KEY (id),UNIQUE KEY `mailbox` (`mailboxid`, `folderid`))ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 DEFAULT COLLATE utf8mb4_unicode_ci;");
        if(err){ cout << mysql_error(connect);	}
    } catch (std::exception &e) {
      cout << " MySQL code: " << e.what();
    }
}