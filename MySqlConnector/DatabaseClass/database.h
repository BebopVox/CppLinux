#ifndef DATABASE_H
#define DATABASE_H

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

class Database
{
private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement  *prep_stmt;

public:
    Database(string Hostname, string Port, string User, string Pass);
    void Connect();
    void InsertMsg();
    unsigned long long LastInsertID();
};

#endif // DATABASE_H
