// Example program in c++
// mysql connection, save to file, create class, method with string and make file
// Example program in c++

/* 
	// change to root
	su
	
	// add: main contrib non-free in /etc/apt/sources.list and install
	apt-get update & upgrade
	apt-get install libmysql++-dev
	apt-get install libmysql++
	apt-get install libmysqlcppconn-dev

	// Complie with
	g++ -o mysql mysql.cpp -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql

	// Compile with class Breakermind.h/Breakermind.cpp in separate file
	g++ -o mysql mysql.cpp Breakermind.cpp -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql

	// Create Mysql user 
	CREATE USER 'mysql'@'localhost' IDENTIFIED BY 'pass';
	GRANT ALL PRIVILEGES ON * . * TO 'mysql'@'localhost';
	FLUSH PRIVILEGES;

	// Tutorial	
	// https://sandeepghai.wordpress.com/2011/08/07/linking-of-mysql-database-with-c-on-linux-machine/
	// http://www.cplusplus.com/doc/tutorial/files/
	// http://www.cplusplus.com/reference/ostream/ostream/write/
	// http://cpp0x.pl/kursy/Kurs-C++/Biblioteka-time-h/321
	// https://stackoverflow.com/questions/6012663/get-unix-timestamp-with-c
	// Makefile
	// https://www.youtube.com/watch?v=_r7i5X0rXJk
*/

#include <iostream>
#include <mysql.h>
#include <stdio.h>
#include <string>
#include <sstream>
// timestamp
#include <ctime>
// file
#include <fstream>
// my class
#include "Breakermind.h"

using namespace std;

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "toor"
#define DATABASE "BreakermindSMTP"

// Save to file function
int saveFile(string txt){
	ofstream myfile;
  	// myfile.open ("email.txt", ios::out | ios::app | ios::binary);
  	myfile.open ("m1.txt", ios::out | ios::app );
  	myfile << txt << "Writing this to a file.\n";
  	myfile.close();
  	cout << "Writing this to a file.\n";
  	return 1;
};

// Main function
int main()
{
	// Class example
	Breakermind boom;
	// method example
	boom.SaveToFile("Booomer");
	// return 1;

	// Mysql connection
	MYSQL *connect;
	connect=mysql_init(NULL);

	if (!connect)
	{
		cout<<"MySQL Initialization failed";
		return 1;
	}
	// Connect mysql server
	connect=mysql_real_connect(connect, "localhost", "root", "toor", "BreakermindSMTP",0,NULL,0);
	if (connect)
	{
		cout<<"connection Succeeded\n";
	}else{
		cout<<"connection failed\n";
	}

	MYSQL_RES *res_set;
	MYSQL_ROW row;

	// time
	std::time_t result = std::time(nullptr);
	std::cout << std::asctime(std::localtime(&result)) << result << " seconds since the Epoch\n";

	for (int j = 0; j < 5; j++)
	{	
		// Save to file function
		saveFile(std::to_string(j));
		cout<< j << "Show table mailbox: \n ";	
		
		// Select from table
		mysql_query(connect,"select * from mailbox;");
		unsigned int i =0;
		res_set = mysql_store_result(connect);
		unsigned int numrows = mysql_num_rows(res_set);

		// Show rows from table
		while (((row= mysql_fetch_row(res_set)) !=NULL ))
		{ //cout<<" %s\n",row[i] !=NULL?row[i] : "NULL";

		 	cout <<"\t | \t" << row[i] << "\t | \t";
		 	cout <<  row[i+1] <<  "\t |"<< endl;
		}	

		// Insert to mysql table
		std::string value1 = "xx''''x@xxx.com";  // As a string
		std::string value2 = "xxx@xxx.com";  // As a string
		std::string value3 = "xxx@xxx.com";  // As a string
		std::string s1 = static_cast<std::ostringstream*>( &(std::ostringstream() << value1) )->str();
		std::string s2 = static_cast<std::ostringstream*>( &(std::ostringstream() << value2) )->str();
		std::string s3 = static_cast<std::ostringstream*>( &(std::ostringstream() << value3) )->str();
		std::string query = "INSERT INTO mailbox(email,pass,name) VALUES('"+s1+"','"+s2+"','"+s3+"');";

		char v1[] = "ddd@ddd.ddd";
		char v2[] = "ddd@ddd.ddd";
		char v3[] = "ddd@ddd.ddd";		
		char sd[1000] = "";
		sprintf(sd, "INSERT INTO mailbox(email,pass,name) VALUES('%s','%s','%s');", v1, v2, v3);
		cout << sd << endl;
		query = sd;

		mysql_query(connect, query.c_str());
		cout << "Mysql insert record !!! " << endl; 

	}
	mysql_close (connect);
	// end time
	std::time_t result1 = std::time(nullptr);
	std::cout << std::asctime(std::localtime(&result1)) << "-" << std::asctime(std::localtime(&result)) << (int)result1 << "-" << result << " seconds since the Epoch\n";
	int x = (int)result1 - (int)result;
	cout << x;
	return 0;
}
