## Mysql connector example

# Install this files in debian mysql connector!!!!
apt-get install libmysqlcppconn-dev 

# Inslatt openssl and lib ssl and lib crypto
apt-get install openssl libssl-dev

# Install  mysql not connector and g++
apt-get install libmysql++ libmysql++-dev libmysql++-doc build-essentials

# Compile examples
g++ -lmysqlcppconn -std=c++11 -L. <br>
g++ -lmysqlcppconn -lssl -lcrypto -pthread -lresolv -std=c++11
  
  // examples  
  https://stackoverflow.com/questions/15995319/c-mysql-connector-undefined-reference-to-get-driver-instance-already-tri
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-1.html
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-results.html
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-prepared-statements.html
  https://dev.mysql.com/doc/connector-cpp/en/connector-cpp-examples-complete-example-2.html

  https://r3dux.org/2010/11/how-to-use-mysql-connectorc-to-connect-to-a-mysql-database-in-windows/
  https://stackoverflow.com/questions/16424828/how-to-connect-mysql-database-using-c
  
 # download connector c++ 
 https://dev.mysql.com/downloads/connector/cpp/
  
  and copy folders to /usr
  <br> folders:  /usr/include and:  /usr/lib files
  
<br>
Compile:
g++ -lmysqlcppconn -std=c++11 -L. <br>
<br> or create makefile
<br> make
<br> Run <br>
./output
