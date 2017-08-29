# CppLinux
C++ linux

<br>
# Install openssl on linux
apt-get install openssl libssl-dev 

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

# Linux proccess max limit 
### Set linux max proccess limit (1 per MB) 2GB
ulimit -u 2044
### Show limits
ulimit -a
<br>ulimit -u
<br>http://rudametw.github.io/blog/posts/2014.04.10/not-enough-threads.html
