## Mysql connector example

Include directly the different  headers from cppconn/ and mysql_driver.h + mysql_util.h (and mysql_connection.h). This will reduce your build time!

  // examples  
  https://stackoverflow.com/questions/15995319/c-mysql-connector-undefined-reference-to-get-driver-instance-already-tri
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-1.html
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-results.html
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-prepared-statements.html
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-2.html

  https://r3dux.org/2010/11/how-to-use-mysql-connectorc-to-connect-to-a-mysql-database-in-windows/
  https://stackoverflow.com/questions/16424828/how-to-connect-mysql-database-using-c
  
  // Install this files in debian !!!!
  apt-get install  libmysqlcppconn-dev
  
  // And if needed
  apt-get install libmysql++ libmysql++-dev g++ build-essentials

  // download connector c++ 
  // https://dev.mysql.com/downloads/connector/cpp/
  
  // and copy folders to   /usr
  // folders:  /usr/include and:  /usr/lib files
  
<br>
Compile:
<br> make
<br> Run <br>
./output
