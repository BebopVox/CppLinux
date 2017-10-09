#### C++ daemon

### Compile
g++ -o daemonix main.cpp daemonize.cpp

### Search process
ps -xj | grep daemonix

### Syslog
/var/log/syslog

## Or run app in background from terminal (root user)
nohup ./CppAppName > cppappname.log 2>&1 &

