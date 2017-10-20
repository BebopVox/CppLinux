# generate ssl certs with password
openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365 -sha256
# generate ssl certs no password
openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365 -nodes -sha256

# Options
-subj "/C=US/ST=Oregon/L=Portland/O=Company Name/OU=Org/CN=www.example.com"
-subj '/CN=localhost'
-nodes

# How to create a self-signed SSL Certificate
# Generate a Private Key
openssl genrsa -des3 -out server.key 2048

#Generate a CSR (Certificate Signing Request)
openssl req -new -key server.key -out server.csr

# Remove Passphrase from Key
cp server.key server.key.org
openssl rsa -in server.key.org -out server.key

# Generate self signed cert
openssl x509 -req -days 365 -in server.csr -signkey server.key -out server.crt

# Installing the Private Key and Certificate
cp server.crt /usr/local/apache/conf/ssl.crt
cp server.key /usr/local/apache/conf/ssl.key

# Enable Virtual Hosts
SSLEngine on
SSLCertificateFile /usr/local/apache/conf/ssl.crt/server.crt
SSLCertificateKeyFile /usr/local/apache/conf/ssl.key/server.key
SetEnvIf User-Agent ".*MSIE.*" nokeepalive ssl-unclean-shutdown
CustomLog logs/ssl_request_log \
   "%t %h %{SSL_PROTOCOL}x %{SSL_CIPHER}x \"%r\" %b"

# Restart apache2
/etc/init.d/httpd stop
/etc/init.d/httpd start
/etc/init.d/httpd restart