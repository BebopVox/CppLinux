/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different  headers from cppconn/ and mysql_driver.h + mysql_util.h (and mysql_connection.h). This will reduce your build time!

  // examples  
  https://stackoverflow.com/questions/15995319/c-mysql-connector-undefined-reference-to-get-driver-instance-already-tri
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-1.html
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-results.html
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-prepared-statements.html
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-2.html

  https://r3dux.org/2010/11/how-to-use-mysql-connectorc-to-connect-to-a-mysql-database-in-windows/
  https://stackoverflow.com/questions/16424828/how-to-connect-mysql-database-using-c
  
  // Install this files in debian 
  apt-get install  libmysqlcppconn-dev
  // And if needed
  apt-get install libmysql++ libmysql++-dev  

  // download connector c++ 
  // https://dev.mysql.com/downloads/connector/cpp/
  // and copy folders to   /usr
  // folders:  /usr/include and:  /usr/lib files
*/

// -L/home/user/c++/mysqlconnector/include/cppconn
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "mysql_error.h"

// usr/include/cppconn
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main(void)
{
cout << endl;
cout << "Running mysql connector" << endl;

try {
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;

  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect("tcp://localhost:3306", "mysql", "pass");
  /* Connect to the MySQL test database */
  con->setSchema("BreakermindSMTP");

  stmt = con->createStatement();
  res = stmt->executeQuery("SELECT * FROM mailbox;");
  while (res->next()) {
    cout << "\t... MySQL replies: ";
    /* Access column data by alias or column name */
    cout << res->getString("email") << endl;
    cout << "\t... MySQL says it again:" << endl;
    /* Access column data by numeric offset, 1 is the first column */
    cout << res->getString(1) << endl;
  }
  delete res;
  delete stmt;
  delete con;

} catch (sql::SQLException &e) {
  cout << "# ERR: SQLException in " << __FILE__;
  cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
  cout << "# ERR: " << e.what();
  cout << " (MySQL error code: " << e.getErrorCode();
  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}

cout << endl;

return EXIT_SUCCESS;
}