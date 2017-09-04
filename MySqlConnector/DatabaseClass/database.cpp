#include "database.h"

Database::Database(string Hostname, string Port, string User, string Pass)
{
    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://"+Hostname+":"+Port, User, Pass);
    /* Connect to the MySQL database */
    con->setSchema("BreakermindSMTP");
}

void Database::Connect(){
    cout << endl;
    cout << "Running mysql connector" << endl;

    try {
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
        prep_stmt = con->prepareStatement("INSERT INTO test(label) VALUES (?)");

        //prep_stmt->setInt(1, 1);
        prep_stmt->setString(1, "hello");
        prep_stmt->execute();

        //prep_stmt->setInt(1, 2);
        prep_stmt->setString(1, "benku");
        prep_stmt->execute();

        unsigned long long id = LastInsertID();
        cout << "!!!!!!!!!! Last id: " << id << endl;

    } catch (sql::SQLException &e) {
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

unsigned long long Database::LastInsertID(){
    try{
        stmt = con->createStatement();
        // res = stmt->executeQuery("SELECT @@identity AS id");
        res = stmt->executeQuery("SELECT LAST_INSERT_ID() as id");
        res->next();
        unsigned long long retVal = res->getInt64("id");
        // cout << "!!!!!!!!!! Last id: " << retVal;
        return retVal;
    } catch (sql::SQLException &e) {
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
      return 0;
    }
}

