# 1 Generate private key
openssl genrsa -out private_key.pem 2048

# Generate public key
openssl rsa -in private_key.pem -out public_key.pem -outform PEM -pubout

# create file
echo "Welcome in my worls." > file.txt
cat encrypt.txt

# Encrypt file with pub.key
openssl rsautl -encrypt -inkey public_key.pem -pubin -in encrypt.txt -out encrypt.dat

# Decrypt file with priv.key
openssl rsautl -decrypt -inkey private_key.pem -in encrypt.dat -out new_encrypt.txt

# Show new file content
cat new_encrypt.txt



# 2 Generate keys
openssl req -x509 -nodes -days 100000 -newkey rsa:2048  -keyout privatekey.pem  -out publickey.pem  -subj '/'

# Encrypt Large Files
openssl  smime  -encrypt -aes256  -in  my_large_file.bin  -binary  -outform DEM  -out  my_large_file_encrypted.bin  publickey.pem

#Decrypt Large Files
openssl  smime -decrypt  -in  my_large_file.bin  -binary -inform DEM -inkey privatekey.pem  -out  my_large_file.bin

