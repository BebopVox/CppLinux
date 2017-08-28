## Qt C++ Linux

<br>

# Add library to .pro file
<br>LIBS += -lssl -lcrypto


# Install openssl on linux
<br> apt-get install openssl libssl-dev 

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
