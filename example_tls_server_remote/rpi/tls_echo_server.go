/*
 * Amazon FreeRTOS TLS Echo Server V1.1.1
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

package main

import (
	"crypto/rand"
	"crypto/tls"
	"crypto/x509"
	"io"
	"io/ioutil"
	"log"
	"net"
	"time"
        "fmt"
	"os"
)

//************** CONFIG SECTION *************//
//Folder were certs are put
const sCertPath string = "credential/"
const sServerCert string = "server.cert.pem"
const sServerKey string = "server.secretkey.pem"
const sEchoPort string = "9000"
const xReadTimeoutSeconds = 300

var sRootCA string
var arg string 

func main() {

	// load certificates
	xServerCert, xStatus := tls.LoadX509KeyPair(sCertPath+sServerCert, sCertPath+sServerKey)
	if xStatus != nil {
		log.Printf("Error %s while loading server certificate", xStatus)
		return
	}

	xServerCA, xStatus := ioutil.ReadFile(sCertPath + sServerCert)
	xServerCAPool := x509.NewCertPool()
	xServerCAPool.AppendCertsFromPEM(xServerCA)

	//argsWithProg := os.Args
	//argsWithoutProg := os.Args[1:]
	if len(os.Args) != 2 {
		sRootCA = "credential/client.cert.pem"
		arg="default"
	}else{
		arg = os.Args[1]
	}
	fmt.Println(len(os.Args))
	//fmt.Println(argsWithoutProg)
	//fmt.Println(arg)

	//Setup client trust anchor
	if arg=="ifx"{
		sRootCA = "credential/Infineon_OPTIGA_TrustM_CA_101.pem"
	}else{
		sRootCA="credential/client.cert.pem"
	}

	log.Printf("Root CA: %s",sRootCA)
	clientCertPEM, err:= ioutil.ReadFile(sRootCA)


	if err != nil {
		panic("failed to read Client CA")
	}

	roots := x509.NewCertPool()
	ok:=roots.AppendCertsFromPEM(clientCertPEM)
	if !ok{
		panic ("failed to parse root certificate")
	}

	//Configure TLS

	xTLSconfig := tls.Config{Certificates: []tls.Certificate{xServerCert},
		MinVersion: tls.VersionTLS12,
		RootCAs:    xServerCAPool,
		//ClientAuth: tls.RequireAnyClientCert,
		ClientAuth: tls.RequireAndVerifyClientCert,
                ClientCAs: roots,
	}
	xTLSconfig.Rand = rand.Reader

	sService := ":" + sEchoPort
	xEchoServer, xStatus := tls.Listen("tcp", sService, &xTLSconfig)
	if xStatus != nil {
		log.Printf("Error %s while trying to listen", xStatus)
	}
	log.Print("Listening to port " + sEchoPort)

	defer xEchoServer.Close()

	i := 0

	for {

		xConnection, xStatus := xEchoServer.Accept()
		if xStatus != nil {
			log.Printf("Error %s while trying to connect", xStatus)
		} else {
			i++
			log.Printf("%d: %v <-> %v\n", i, xConnection.LocalAddr(), xConnection.RemoteAddr())
			go echoServerThread(xConnection)
		}
	}
}

func echoServerThread(xConnection net.Conn) {
	defer xConnection.Close()

	xDataBuffer := make([]byte, 4096)

	for {
		xConnection.SetReadDeadline(time.Now().Add(xReadTimeoutSeconds * time.Second))
		xNbBytes, xStatus := xConnection.Read(xDataBuffer)
		if xStatus != nil {
			//EOF mean end of connection
			if xStatus != io.EOF {
				//If not EOF then it is an error
			}
			break
		}

		xNbBytes, xStatus = xConnection.Write(xDataBuffer[:xNbBytes])
		if xStatus != nil {
			log.Printf("Error %s while sending data", xStatus)
			break
		}else{
			log.Printf("Echo Out: %s", xDataBuffer[:xNbBytes])
		}
	}
}
