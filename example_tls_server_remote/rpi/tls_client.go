package main

import (
    "crypto/tls"
    "crypto/x509"
    "fmt"
    "io"
    "log"
)

func main() {
    cert, err := tls.LoadX509KeyPair("credential/client.cert.pem", "credential/client.secretkey.pem")
    if err != nil {
        log.Fatalf("server: loadkeys: %s", err)
    }
    config := tls.Config{Certificates: []tls.Certificate{cert}, InsecureSkipVerify: true}
config.CipherSuites = []uint16{
          tls.TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,
          tls.TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256}
    conn, err := tls.Dial("tcp", "127.0.0.1:9000", &config)
    if err != nil {
        log.Fatalf("client: dial: %s", err)
    }
    defer conn.Close()
    log.Println("client: connected to: ", conn.RemoteAddr())

    state := conn.ConnectionState()
    for _, v := range state.PeerCertificates {
		log.Println("Server Cert Public Key: ")
	fmt.Println(x509.MarshalPKIXPublicKey(v.PublicKey))
	log.Println("Server Cert Serial Number: ")
	fmt.Printf("%x\n", v.SerialNumber)
	log.Println("Server Cert Subject: ")
        fmt.Println(v.Subject)
    }
    log.Println("Client: handshake: ", state.HandshakeComplete)
    log.Println("Client: mutual: ", state.NegotiatedProtocolIsMutual)

    message := "Hello Test Message\n"
    n, err := io.WriteString(conn, message)
    if err != nil {
        log.Fatalf("client: write: %s", err)
    }
    log.Printf("client: wrote %q (%d bytes)", message, n)

    reply := make([]byte, 256)
    n, err = conn.Read(reply)
    log.Printf("client: read %q (%d bytes)", string(reply[:n]), n)
    log.Print("client: exiting")
}
