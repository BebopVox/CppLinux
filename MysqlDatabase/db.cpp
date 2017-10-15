#include "db.h"

DB::DB(){}

// set esmtp hostname
void DB::ServerHost(string serverHost = "localhost.loc"){
	ServerHostname = serverHost;
}

// Connect to database
bool DB::Connect(string host = "localhost", string user = "root", string pass = "toor", string db = "BreakermindSMTP", string port = "3306"){
	try{
		// init mysql		 		  	
		connect=mysql_init(NULL);		
		mysql_options(connect, MYSQL_SET_CHARSET_NAME, "utf8mb4");
	  	mysql_options(connect, MYSQL_INIT_COMMAND, "SET NAMES utf8mb4");
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
			cout << "[ERROR_MYSQL_CONN] MySQL Connection failed (Restart application)\n";
			return 0;
		}			
	} catch (std::exception &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        //cout << "# ERR: " << e.what();        
        return 0;
    }
}

// Select messages to send
vector<vector<string>> DB::getMessagesToSendX(int limit){
	// Current mysql thread ID
	int trID = 0; // unsigned long
	trID =  (int)mysql_thread_id(connect);	

	// vectors
	vector<vector<string>> messages;
	// select
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	try{
		// Select messages to send change threadid
		char query[500];
		sprintf (query, "UPDATE messages SET threadid=%i WHERE threadid = 0 LIMIT %i;", trID, limit);
		// cout << "Query: " << query << endl;			
		int err = mysql_query (connect,query);	
		
		// mysql_autocommit(connect, false);
		// mysql_query (connect,"BEGIN;");
		// lock tables
		// mysql_query (connect,"LOCK TABLES messages WRITE;");	

		char que[500];
		sprintf(que, "SELECT id,email_from,email_to,email_replyto,email_subject,email_content,threadid FROM messages WHERE threadid > 0 AND threadid = %i AND send > 0 AND send < 100 AND resendtime < NOW() LIMIT %i;", trID, limit+limit);
		err = mysql_query (connect,que);
		if(err){
	      fprintf(stderr, "%s\n", mysql_error(connect));
	      // mysql_close(con);
	      // exit(1);
	  	}
		unsigned int i =0;
		res_set = mysql_store_result(connect);
		// unsigned int numrows = mysql_num_rows(res_set);
		// int num_fields = mysql_num_fields(res_set);
	
		while (((row = mysql_fetch_row(res_set)) !=NULL )){
			cout << "\n" << currentDateTimeSMTP() <<" MySQL Thread ID " << trID << endl;
			cout << limit << " " << row[i] << " " << row[i+1] << " " << row[i+2] << " " << row[i+3] << " " << row[i+4] << " trID " << row[i+6] << endl;

			char query[500];
			sprintf (query, "UPDATE messages SET send=send+1,resendtime=DATE_ADD(NOW(), INTERVAL 60 MINUTE) WHERE id=%i;", atoi(row[i]));			
			cout << "Query: " << query << endl;			
			int err = mysql_query (connect,query);
			if(err){
		      fprintf(stderr, "%s\n", mysql_error(connect));
		      // mysql_close(con);
		      // exit(1);
		  	}
			// add single row to vector string
			vector<string> msg;
			msg.push_back(row[i]);
			msg.push_back(row[i+1]);
			msg.push_back(row[i+2]);
			msg.push_back(row[i+3]);
			msg.push_back(row[i+4]);
			msg.push_back(row[i+5]);
			// add to messages
			messages.push_back(msg);
		}		
	}catch(std::exception &e){
		cout << "Error mysql class " << endl;
		return messages;
	}
	// lock tables end
	// mysql_query (connect,"UNLOCK TABLES;");
	//mysql_query (connect,"COMMIT;");
	mysql_free_result(res_set);	
	// return messages
	return messages;
}

// Select messages to send
vector<vector<string>> DB::getMessagesToSend(int limit){
	// vectors
	vector<vector<string>> messages;
	// select
	MYSQL_RES *res_set;
	MYSQL_ROW row;
	mysql_autocommit(connect, false);
	//mysql_query (connect,"BEGIN;");
	// lock tables
	mysql_query (connect,"LOCK TABLES messages WRITE;");
	unsigned long trID =  (unsigned long)mysql_thread_id(connect);
	cout << "MySQL Thread ID " << trID << endl;
	char que[500];
	sprintf(que, "SELECT id,email_from,email_to,email_replyto,email_subject,email_content FROM messages WHERE send > 0 AND send < 100 AND resendtime < NOW() LIMIT %i;",limit);
	int err = mysql_query (connect,que);
	if(err){
      fprintf(stderr, "%s\n", mysql_error(connect));
      // mysql_close(con);
      // exit(1);
  	}
	unsigned int i =0;
	res_set = mysql_store_result(connect);
	// unsigned int numrows = mysql_num_rows(res_set);
	// int num_fields = mysql_num_fields(res_set);
	try{
		while (((row = mysql_fetch_row(res_set)) !=NULL )){
			cout << limit << " " << row[i] << " " << row[i+1] << " " << row[i+2] << " " << row[i+3] << " " << row[i+4] << endl;

			char query[500];
			sprintf (query, "UPDATE messages SET send=send+1,resendtime=DATE_ADD(NOW(), INTERVAL 60 MINUTE) WHERE id=%i;", atoi(row[i]));			
			// cout << "Query: " << query << endl;			
			cout << "MessageID: " << row[i] << endl;
			int err = mysql_query (connect,query);
			if(err){
		      fprintf(stderr, "%s\n", mysql_error(connect));
		      // mysql_close(con);
		      // exit(1);
		  	}
			// add single row to vector string
			vector<string> msg;
			msg.push_back(row[i]);
			msg.push_back(row[i+1]);
			msg.push_back(row[i+2]);
			msg.push_back(row[i+3]);
			msg.push_back(row[i+4]);
			msg.push_back(row[i+5]);
			// add to messages
			messages.push_back(msg);
		}		
	}catch(std::exception &e){
		cout << "Error mysql class " << endl;
		return messages;
	}
	// lock tables end
	mysql_query (connect,"UNLOCK TABLES;");
	//mysql_query (connect,"COMMIT;");
	mysql_free_result(res_set);	
	// return messages
	return messages;
}

void DB::SendMessages(int treadLimit){
	try{
		// vector<vector<string>> list = getMessagesToSend(treadLimit);     
		vector<vector<string>> list = getMessagesToSendX(treadLimit);   		
		if(list.size() > 0){
			cout << "Wiadomości do wysłania " << list.size() << endl;
	        for (unsigned int i = 0; i < list.size(); i++)
	        {
	            std::vector<string> message = list.at(i);
	            cout << "\n[Thread]" << " " << message.at(2) << " email to send " << endl;
	            // Get data from row            
	            int email_id = std::atoi(message.at(0).c_str());
	            string email_from = message.at(1);
	            string email_to = message.at(2);
	            string email_content = message.at(5);           

	            // Get mx from dns
	            sslsmtpEx ex = sslsmtpEx("",0);
	            vector<string> mx = ex.getMX(email_to,0,0);
	            int mailsend = 0;        
	            for(unsigned int i = 0; i < mx.size(); i++){
	                if(mailsend==0){
	                    cout << "SEND TO MX " << mx.at(i) << endl;                                
	                    // Send to each host from mx dns                                
	                    sslsmtpEx smtp = sslsmtpEx(mx.at(i), 25);
	                    // .append("\r\n.\r\n")
	                    mailsend = smtp.SendMIME(email_from, email_to, email_content, ServerHostname, email_id);                        
	                    if(mailsend){
	                    	// Oznacz wiadomość jako wysłaną
	                        // changeMessageStatus(email_id);
	                        cout << "Thread: " << mailsend << " !!!!!! EMAIL HAS BEEN SENT FROM MX HOST !!!!!!" << endl;
	                    }
	                }else{
	                    cout << "Thread: "<< "EMAIL HAS BEEN SENT." << endl;
	                }
	            }
	        }// for end        
	    }  	
	} catch (std::exception &e) {
        cout << "# ERR: SendException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();                
    }
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
        cout << "# ERR: SQLException in " << __FILE__;
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
std::string DB::currentDateTime() {
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
   return dt;
}
