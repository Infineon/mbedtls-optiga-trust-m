#!/bin/bash

#Create the credential folder is not exists
if [ ! -d credential ]; then
  mkdir -p credential;
fi

echo "Make TLS Server cert"

echo "Create server public and secret key"
openssl ecparam -genkey -name prime256v1 -out credential/server.secretkey.pem

echo "Create CSR using server private key"
openssl req -new -key credential/server.secretkey.pem -out credential/server.csr.pem -subj "/C=SG/ST=Singapore/L=Singapore/O=Infineon Technologies/OU=DSS/CN=TLS_Server"

echo "Create a PEM (Base64 encoded ASCII) format server certificate signed by CA"
openssl x509 -req -days 3650 -in credential/server.csr.pem -set_serial 0x88888888888888888888888888888888 -signkey credential/server.secretkey.pem -out credential/server.cert.pem

echo "Display the server certificate"
openssl x509 -noout -text -in credential/server.cert.pem

echo "Make TLS client cert"
openssl ecparam -genkey -name prime256v1 -out credential/client.secretkey.pem

echo "Create CSR using client private key"
openssl req -new -key credential/client.secretkey.pem -out credential/client.csr.pem -subj "/C=SG/ST=Singapore/L=Singapore/O=Infineon Technologies/OU=DSS/CN=TLS_Client"

echo "Create a PEM (Base64 encoded ASCII) format client certificate"
openssl x509 -req -days 3650 -in credential/client.csr.pem -set_serial 0x77777777777777777777777777777777 -signkey credential/client.secretkey.pem -out credential/client.cert.pem

echo "Display the client certificate"
openssl x509 -noout -text -in credential/client.cert.pem


