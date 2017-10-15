# C++ Mysql

#### Install mysql library
apt-get install libmysql++ <br>
apt-get install libmysql++-dev <br>

#### Compile:
g++ -o start main.cpp -Wall -Wextra -pedantic -std=c++11 -pthread -lmysqlclient -L/usr/include/mysql -I/usr/include/mysql -L. -I.

#### Change mysql database connection limit:
mysql -u root -p <br>
set global max_connections = 10000; <br>

#### Prevent sql injection (%i, %s, %f, %u, %c) #include string.h, string
string data = "text"; <br>
int nr = 5; <br>
sprintf(query, "SELECT id,name,time FROM messages WHERE id > %i AND data LIKE ('%s') ...", nr, data); <br>
