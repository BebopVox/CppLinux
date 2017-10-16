#### C++ daemon

### Compile
g++ -o daemonix main.cpp daemonize.cpp

### Search process
ps -xj | grep daemonix

### Syslog
/var/log/syslog

## Or run app in background from terminal (root user)
nohup ./CppAppName > cppappname.log 2>&1 &

## Show jobs in background
jobs <br>
jobs -l <br>
jobs -p

## Back from backgroung
fg {JOB-PID}

## kill process PID
kill -9 {JOB-PID} <br>
kill -15 {JOB-PID} <br>
killall -9 CppAppName <br>
killall -15 CppAppName <br>

#### References
http://shahmirj.com/blog/beginners-guide-to-creating-a-daemon-in-linux
