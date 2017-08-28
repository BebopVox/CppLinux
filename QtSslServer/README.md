## Qt C++ Linux

<br>

# Add library to .pro file
<br>LIBS += -lssl -lcrypto


# Install openssl on linux
<br> apt-get install openssl libssl-dev 

# On debian when using QSSLSocket you need install openssl 1.0 
apt install libssl1.0-dev libyaml-dev libarchive-dev libssl-dev
<br> https://stackoverflow.com/questions/42094214/why-is-qsslsocket-working-with-qt-5-3-but-not-qt-5-7-on-debian-stretch
<br>https://doc.qt.io/QtApplicationManager/installation.html#multi-vs-single-process
<br>qDebug()<<"SSL version use for build: "<<QSslSocket::sslLibraryBuildVersionString();
<br>qDebug()<<"SSL version use for run-time: "<<QSslSocket::sslLibraryVersionNumber();
<br>qDebug()<<QCoreApplication::libraryPaths();

# Connect to server
openssl s_client -connect 127.0.0.1:3333
<br>telnet-ssl -z ssl 127.0.0.1 3333

# Z ca_bundle.crt
openssl s_client -connect qflash.pl:3333 -CAfile /home/user/c++/server/ca_bundle.crt
<br>openssl s_client -connect 127.0.0.1:3333 -CAfile /etc/ssl/certs/ca-certificates.crt

# Show certs
echo "" | openssl s_client -showcerts -connect 127.0.0.1:3333 -CAfile /home/user/c++/server/ca_bundle.crt

# In wireshark need set TLS ports in settings
https://ask.wireshark.org/questions/34075/why-wireshark-cannot-display-tlsssl
