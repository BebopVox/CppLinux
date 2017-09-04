#include "database.h"
#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "mysql_error.h"

// usr/include/cppconn
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

Database::Database()
{

}

void Database::Connect(){
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
      /* Connect to the MySQL database */
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
}

void Database::InsertMsg(){
    try{
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect("tcp://localhost:3306", "mysql", "pass");
        /* Connect to the MySQL database */
        con->setSchema("BreakermindSMTP");

        sql::PreparedStatement  *prep_stmt;
        prep_stmt = con->prepareStatement("INSERT INTO test(label) VALUES (?)");

        //prep_stmt->setInt(1, 1);
        prep_stmt->setString(1, "hello");
        prep_stmt->execute();

        //prep_stmt->setInt(1, 2);
        prep_stmt->setString(1, "benku");
        prep_stmt->execute();

        stmt = con->createStatement();
        // res = stmt->executeQuery("SELECT @@identity AS id");
        res = stmt->executeQuery("SELECT LAST_INSERT_ID() as id");
        res->next();
        unsigned long long retVal = res->getInt64("id");
        cout << "!!!!!!!!!! Last id: " << retVal;
    } catch (sql::SQLException &e) {
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

}

