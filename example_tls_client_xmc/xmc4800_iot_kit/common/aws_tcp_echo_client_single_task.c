/*
 * Amazon FreeRTOS V1.4.7
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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


/*
 * A set of tasks are created that send TCP echo requests to the standard echo
 * port (port 7) on the IP address set by the configECHO_SERVER_ADDR0 to
 * configECHO_SERVER_ADDR3 constants, then wait for and verify the reply
 * (another demo is available that demonstrates the reception being performed in
 * a task other than that from with the request was made).
 *
 * See the following web page for essential demo usage and configuration
 * details:
 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Echo_Clients.html
 */

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* TCP/IP abstraction includes. */
#include "aws_secure_sockets.h"

/* Demo configuration */
//#include "aws_demo_config.h"

#include "optiga/optiga_util.h"
#include "optiga/pal/pal_os_event.h"
#include "optiga/pal/pal_logger.h"
#include "optiga/ifx_i2c/ifx_i2c_config.h"
#include "mbedtls/base64.h"
#include "trustm_chipinfo.h"
#include "threading_alt.h"

extern optiga_lib_status_t trustm_OpenApp(void);
extern optiga_lib_status_t trustm_CloseApp(void);

extern void example_optiga_util_read_uid(void);
extern optiga_lib_status_t  example_authenticate_chip(void);

extern void example_optiga_crypt_ecc_generate_keypair(void);
extern void example_optiga_crypt_ecdh(void);
extern void example_optiga_crypt_ecdsa_sign(void);
extern void example_optiga_crypt_ecdsa_verify(void);
extern void example_optiga_crypt_hash(void);
extern void example_optiga_crypt_random(void);
extern void example_optiga_crypt_rsa_decrypt_and_export(void);
extern void example_optiga_crypt_rsa_encrypt_message(void);
extern void example_optiga_crypt_rsa_encrypt_session(void);
extern void example_optiga_crypt_rsa_generate_keypair(void);
extern void example_optiga_crypt_rsa_sign(void);
extern void example_optiga_crypt_rsa_verify(void);
extern void example_optiga_crypt_tls_prf_sha256(void);
extern void example_optiga_util_protected_update(void);
extern void example_optiga_util_read_data(void);
extern void example_optiga_util_update_count(void);
extern void example_optiga_util_write_data(void);

extern pal_status_t pal_os_event_init(void);

extern void example_mbedtls_optiga_crypt_rsa_sign(void);
extern void example_mbedtls_optiga_crypt_rsa_verify(void);
extern void example_mbedtls_optiga_crypt_rsa_encrypt(void);
extern void example_mbedtls_optiga_crypt_rsa_decrypt(void);

extern void example_pair_host_and_optiga_using_pre_shared_secret(void);

extern int example_mbedtls_optiga_crypt_ecc_extendedcurve_genkeypair();
extern int example_mbedtls_optiga_crypt_ecc_extendedcurve_calsign();
extern int example_mbedtls_optiga_crypt_ecc_extendedcurve_verify();
extern int example_mbedtls_optiga_crypt_ecc_extendedcurve_calcssec();

extern void aws_mbedtls_mutex_init( mbedtls_threading_mutex_t * mutex );
extern void aws_mbedtls_mutex_free( mbedtls_threading_mutex_t * mutex );
extern int aws_mbedtls_mutex_lock( mbedtls_threading_mutex_t * mutex );
extern int aws_mbedtls_mutex_unlock( mbedtls_threading_mutex_t * mutex );

extern void vStartTCPEchoClientTasks_SingleTasks( void );

/* TCP Echo Client tasks single example parameters. */
#define democonfigTCP_ECHO_TASKS_SINGLE_TASK_STACK_SIZE    ( configMINIMAL_STACK_SIZE * 4 )
#define democonfigTCP_ECHO_TASKS_SINGLE_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1 )


#define SHOW_ECHO_TASK_PATH         0

/* Dimensions the buffer used to generate the task name. */
#define echoMAX_TASK_NAME_LENGTH    8

/* Sanity check the configuration constants required by this demo are
 * present. */
#if !defined( configECHO_SERVER_ADDR0 ) || !defined( configECHO_SERVER_ADDR1 ) || !defined( configECHO_SERVER_ADDR2 ) || !defined( configECHO_SERVER_ADDR3 )
    #error configECHO_SERVER_ADDR0 to configECHO_SERVER_ADDR3 must be defined in FreeRTOSConfig.h to specify the IP address of the echo server.
#endif

/* The echo tasks create a socket, send out a number of echo requests, listen
 * for the echo reply, then close the socket again before starting over.  This
 * delay is used between each iteration to ensure the network does not get too
 * congested. */
#define echoLOOP_DELAY    ( ( TickType_t ) 150 / portTICK_PERIOD_MS )

/* The echo server is assumed to be on port 7, which is the standard echo
 * protocol port. */
#if !defined( configTCP_ECHO_CLIENT_PORT ) && !defined( configTCP_ECHO_SECURE_CLIENT_PORT )
    #define echoECHO_PORT    ( 7 )
#else
    //#define echoECHO_PORT    ( configTCP_ECHO_CLIENT_PORT )
    #define echoECHO_PORT    ( configTCP_ECHO_SECURE_CLIENT_PORT)
#endif

/* The size of the buffers is a multiple of the MSS - the length of the data
 * sent is a pseudo random size between 20 and echoBUFFER_SIZES. */
#define echoBUFFER_SIZE_MULTIPLIER    ( 2 )
#define echoBUFFER_SIZES              ( 2000 ) /*_RB_ Want to be a multiple of the MSS but there is no MSS constant in the bastraction. */

/* The number of instances of the echo client task to create. */
#define echoNUM_ECHO_CLIENTS          ( 1 )

/* If ipconfigUSE_TCP_WIN is 1 then the Tx socket will use a buffer size set by
 * ipconfigTCP_TX_BUFFER_LENGTH, and the Tx window size will be
 * configECHO_CLIENT_TX_WINDOW_SIZE times the buffer size.  Note
 * ipconfigTCP_TX_BUFFER_LENGTH is set in FreeRTOSIPConfig.h as it is a standard TCP/IP
 * stack constant, whereas configECHO_CLIENT_TX_WINDOW_SIZE is set in
 * FreeRTOSConfig.h as it is a demo application constant. */
#ifndef configECHO_CLIENT_TX_WINDOW_SIZE
    #define configECHO_CLIENT_TX_WINDOW_SIZE    2
#endif

/* If ipconfigUSE_TCP_WIN is 1 then the Rx socket will use a buffer size set by
 * ipconfigTCP_RX_BUFFER_LENGTH, and the Rx window size will be
 * configECHO_CLIENT_RX_WINDOW_SIZE times the buffer size.  Note
 * ipconfigTCP_RX_BUFFER_LENGTH is set in FreeRTOSIPConfig.h as it is a standard TCP/IP
 * stack constant, whereas configECHO_CLIENT_RX_WINDOW_SIZE is set in
 * FreeRTOSConfig.h as it is a demo application constant. */
#ifndef configECHO_CLIENT_RX_WINDOW_SIZE
    #define configECHO_CLIENT_RX_WINDOW_SIZE    2
#endif

/* The flag that turns on TLS for secure socket */
#define configTCP_ECHO_TASKS_SINGLE_TASK_TLS_ENABLED    ( 1 )

/*
 * PEM-encoded server certificate
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#if ( configTCP_ECHO_TASKS_SINGLE_TASK_TLS_ENABLED == 1 )


static const char cTlsECHO_SERVER_CERTIFICATE_PEM[] =
"-----BEGIN CERTIFICATE-----\n"
"MIICbzCCAdgCEQCIiIiIiIiIiIiIiIiIiIiIMA0GCSqGSIb3DQEBCwUAMHgxCzAJ\n"
"BgNVBAYTAlNHMRIwEAYDVQQIDAlCYW5nYWxvcmUxEjAQBgNVBAcMCUJhbmdhbG9y\n"
"ZTEeMBwGA1UECgwVSW5maW5lb24gVGVjaG5vbG9naWVzMQwwCgYDVQQLDANEU1Mx\n"
"EzARBgNVBAMMClRMU19TZXJ2ZXIwHhcNMTkwOTMwMTA1NjE3WhcNMjkwOTI3MTA1\n"
"NjE3WjB4MQswCQYDVQQGEwJTRzESMBAGA1UECAwJQmFuZ2Fsb3JlMRIwEAYDVQQH\n"
"DAlCYW5nYWxvcmUxHjAcBgNVBAoMFUluZmluZW9uIFRlY2hub2xvZ2llczEMMAoG\n"
"A1UECwwDRFNTMRMwEQYDVQQDDApUTFNfU2VydmVyMIGfMA0GCSqGSIb3DQEBAQUA\n"
"A4GNADCBiQKBgQChaEfsQ6u0K9H3VIK1VexdB6nfhDCGRh0QaUnmSTFtJtk+05PT\n"
"8UZ3iHQwqCxAM7HpfFrct1EUlhQEgmzFif6iptjru2GO6fWlfQl/L33xiKgYBpCT\n"
"2v2r7ZEKnz20AnbUE4FjseHiIr9kZ05UiWkYc0te2dc7uKiA2ICqL8ipWwIDAQAB\n"
"MA0GCSqGSIb3DQEBCwUAA4GBACIFn5zFtCR9LUMo/smIbNSDrOV4zUzMpp1p3xFu\n"
"Nkjq8WpJKJDVoIWRVU/J1Ll9dubc4+LB2EtETx+ibBXHdnRPGJqzGWkyFQ9RBOSO\n"
"YV/juDh5qbIdkrInxYv9JZFULryHvOz9DcxB+AuLHVzUhikK2Kfr93SawEs++HdU\n"
"6Xr/\n"
"-----END CERTIFICATE-----\n";

    static const uint32_t ulTlsECHO_SERVER_CERTIFICATE_LENGTH = sizeof( cTlsECHO_SERVER_CERTIFICATE_PEM );
#endif

/*-----------------------------------------------------------*/

/*
 * Uses a socket to send data to, then receive data from, the standard echo
 * port number 7.
 */
static void prvEchoClientTask( void * pvParameters );

/*
 * Creates a pseudo random sized buffer of data to send to the echo server.
 */
static BaseType_t prvCreateTxData( char * ucBuffer,
                                   uint32_t ulBufferLength );

/*-----------------------------------------------------------*/

/* Rx and Tx time outs are used to ensure the sockets do not wait too long for
 * missing data. */
static const TickType_t xReceiveTimeOut = pdMS_TO_TICKS( 2000 );
static const TickType_t xSendTimeOut = pdMS_TO_TICKS( 2000 );

/* Counters for each created task - for inspection only. */
static uint32_t ulTxRxCycles[ echoNUM_ECHO_CLIENTS ] = { 0 },
                ulTxRxFailures[ echoNUM_ECHO_CLIENTS ] = { 0 },
                ulConnections[ echoNUM_ECHO_CLIENTS ] = { 0 };

/* Rx and Tx buffers for each created task. */
static char cTxBuffers[ echoNUM_ECHO_CLIENTS ][ echoBUFFER_SIZES ],
            cRxBuffers[ echoNUM_ECHO_CLIENTS ][ echoBUFFER_SIZES ];

/*-----------------------------------------------------------*/

void vStartTCPEchoClientTasks_SingleTasks( void )
{
    BaseType_t xX;
    char cNameBuffer[ echoMAX_TASK_NAME_LENGTH ];

    /* Create the echo client tasks. */
    for( xX = 0; xX < echoNUM_ECHO_CLIENTS; xX++ )
    {
        snprintf( cNameBuffer, echoMAX_TASK_NAME_LENGTH, "Echo%ld", xX );
        xTaskCreate( prvEchoClientTask,                               /* The function that implements the task. */
                     cNameBuffer,                                     /* Just a text name for the task to aid debugging. */
                     democonfigTCP_ECHO_TASKS_SINGLE_TASK_STACK_SIZE, /* The stack size is defined in FreeRTOSIPConfig.h. */
                     ( void * ) xX,                                   /* The task parameter, not used in this case. */
                     //democonfigTCP_ECHO_TASKS_SINGLE_TASK_PRIORITY,   /* The priority assigned to the task is defined in FreeRTOSConfig.h. */
					 tskIDLE_PRIORITY,
                     NULL );                                          /* The task handle is not used. */
    }
}
/*-----------------------------------------------------------*/

//Test define macros
#define ENABLE_TRUSTM           1

#define READ_UID_TEST           0
int TRUSTM_UID_LOOP_COUNT =1;

#define AUTH_TEST               0
int TRUSTM_AUTH_LOOP_COUNT=1;

#define EXAMPLE_UNIT_TESTS      0
int TRUSTM_UNIT_TEST_LOOP_COUNT=1;

#define TRUSTM_RSA_TEST         0

#define TRUSTM_ECC_EXTENDED_TEST 0

static void prvEchoClientTask( void * pvParameters )
{
    Socket_t xSocket;
/*_RB_ struct convention is for this not to be typedef'ed, so 'struct' is required. */ SocketsSockaddr_t xEchoServerAddress;
    int32_t lLoopCount = 0UL;
    const int32_t lMaxLoopCount = 100;
    volatile uint32_t ulTxCount = 0UL;
    BaseType_t xReceivedBytes, xReturned, xInstance;
    BaseType_t xTransmitted, xStringLength;
    char * pcTransmittedString;
    char * pcReceivedString;
    TickType_t xTimeOnEntering;
    const int CONNECT_COUNT = 1;

#if (SHOW_ECHO_TASK_PATH == 1)
	configPRINTF( ( ">prvEchoClientTask()\r\n") );
#endif

    #if ( ipconfigUSE_TCP_WIN == 1 )
        {
            WinProperties_t xWinProps;

            /* Fill in the buffer and window sizes that will be used by the socket. */
            xWinProps.lTxBufSize = ipconfigTCP_TX_BUFFER_LENGTH;
            xWinProps.lTxWinSize = configECHO_CLIENT_TX_WINDOW_SIZE;
            xWinProps.lRxBufSize = ipconfigTCP_RX_BUFFER_LENGTH;
            xWinProps.lRxWinSize = configECHO_CLIENT_RX_WINDOW_SIZE;
        }
    #endif /* ipconfigUSE_TCP_WIN */

    /* This task can be created a number of times.  Each instance is numbered
     * to enable each instance to use a different Rx and Tx buffer.  The number is
     * passed in as the task's parameter. */
    xInstance = ( BaseType_t ) pvParameters;

    /* Point to the buffers to be used by this instance of this task. */
    pcTransmittedString = &( cTxBuffers[ xInstance ][ 0 ] );
    pcReceivedString = &( cRxBuffers[ xInstance ][ 0 ] );

#if defined(TLS_SECRET_IN_TRUSTM)
#if ( ENABLE_TRUSTM == 1 )
	optiga_lib_status_t open_app_status = trustm_OpenApp();
	if (open_app_status != OPTIGA_LIB_SUCCESS)
	{
		configPRINTF( ( "TCPCLient(): Error: Open TrustM App failed. status=0x%x\r\n",open_app_status) );
		goto cleanup;
	}else
	{
		configPRINTF( ( "TCPCLient(): Open TrustM App Ok\r\n") );
	}
	configPRINTF( ( "TCPCLient(): Pairing of host and OPTIGA \r\n") );
	//example_pair_host_and_optiga_using_pre_shared_secret();

#if ( READ_UID_TEST == 1 )
	do{
		configPRINTF( ( "+++++Read UID Test:+++++\r\n") );
		example_optiga_util_read_uid();
		configPRINTF( ( "Read UID done count=%d\r\n",TRUSTM_UID_LOOP_COUNT-- ) );
	}while(TRUSTM_UID_LOOP_COUNT);
	configPRINTF( ( "+++++Read UID Test Completed+++++\r\n") );
#endif

#if ( AUTH_TEST == 1 )
	do{
		configPRINTF( ( "+++++Authentication Test+++++\r\n") );
		example_authenticate_chip();
		configPRINTF( ( "Auth done count=%d\r\n",TRUSTM_AUTH_LOOP_COUNT-- ) );
	}while(TRUSTM_AUTH_LOOP_COUNT);
	configPRINTF( ( "+++++Auth Test Completed+++++\r\n") );
#endif

#if (EXAMPLE_UNIT_TESTS==1)
	    do
	    {
	    	configPRINTF( ( "+++++Unit Tests+++++\r\n") );
			example_optiga_crypt_ecc_generate_keypair();
			example_optiga_crypt_ecdsa_sign();
			example_optiga_crypt_ecdsa_verify();
			example_optiga_crypt_hash();
			example_optiga_crypt_random();

			example_optiga_crypt_rsa_encrypt_message();

			example_optiga_crypt_rsa_generate_keypair();
			example_optiga_crypt_rsa_sign();
			example_optiga_crypt_rsa_verify();
			example_optiga_util_protected_update();
			example_optiga_util_read_data();
			example_optiga_util_update_count();
			example_optiga_util_write_data();
			example_optiga_crypt_tls_prf_sha256();
			example_optiga_crypt_ecdh();
			example_optiga_crypt_rsa_encrypt_session();
			example_optiga_crypt_rsa_decrypt_and_export();

			configPRINTF( ( "Example unit tests loop count=%d\r\n",TRUSTM_UNIT_TEST_LOOP_COUNT--) );
	    }while(TRUSTM_UNIT_TEST_LOOP_COUNT);
	    configPRINTF( ( "+++++Unit Tests Completed+++++\r\n") );
#endif

#if (TRUSTM_RSA_TEST == 1)
	do{
		configPRINTF( ( "+++++TrustM pre shared secret Test+++++\r\n") );
	    example_pair_host_and_optiga_using_pre_shared_secret();
		configPRINTF( ( "+++++TrustM pre shared secret Test Completed+++++\r\n") );

		configPRINTF( ( "+++++TrustM RSA Verify Test+++++\r\n") );
		example_mbedtls_optiga_crypt_rsa_verify();
		configPRINTF( ( "+++++TrustM RSA Verify Test Completed+++++\r\n") );

		configPRINTF( ( "+++++TrustM RSA Sign Test+++++\r\n") );
		example_mbedtls_optiga_crypt_rsa_sign();
		configPRINTF( ( "+++++TrustM RSA Sign Test Completed+++++\r\n") );

		configPRINTF( ( "+++++TrustM RSA Encrypt Test+++++\r\n") );
		example_mbedtls_optiga_crypt_rsa_encrypt();
		configPRINTF( ( "+++++TrustM RSA Encrypt Test Completed+++++\r\n") );

		configPRINTF( ( "+++++TrustM RSA Decrypt Test+++++\r\n") );
		example_mbedtls_optiga_crypt_rsa_decrypt();
		configPRINTF( ( "+++++TrustM RSA Decrypt Test Completed+++++\r\n") );
	} while(FALSE);

#endif

#if (TRUSTM_ECC_EXTENDED_TEST == 1)
	do{
		mbedtls_threading_set_alt( aws_mbedtls_mutex_init,
		                                   aws_mbedtls_mutex_free,
		                                   aws_mbedtls_mutex_lock,
		                                   aws_mbedtls_mutex_unlock );

		configPRINTF( ( "ECC Extended curve examples\r\n") );
		if(0 != example_mbedtls_optiga_crypt_ecc_extendedcurve_genkeypair())
		{
			configPRINTF( ( "Genkey pair example test failed\n") );
			break;
		}

		configPRINTF( ( "ECC Extended curve Genkey pair example executed successfully\r\n") );

		if(0 != example_mbedtls_optiga_crypt_ecc_extendedcurve_calsign())
		{
			configPRINTF( ( "CalSign example test failed\n") );
			break;
		}

		configPRINTF( ( "ECC Extended curve CalSign examples executed successfully\r\n") );

		if(0 != example_mbedtls_optiga_crypt_ecc_extendedcurve_verify())
		{
			configPRINTF( ( "VerifySign example test failed\n") );
			break;
		}

		configPRINTF( ( "ECC Extended curve VerifySign examples executed successfully\r\n") );

		if(0 != example_mbedtls_optiga_crypt_ecc_extendedcurve_calcssec())
		{
			configPRINTF( ( "CalSSec example test failed\n") );
			break;
		}

		configPRINTF( ( "ECC Extended curve CalSSec examples executed successfully\n") );

		configPRINTF( ( "ECC Extended curve example successful\n") );

	} while(FALSE);

#endif

#endif
#endif


    /* Echo requests are sent to the echo server.  The address of the echo
     * server is configured by the constants configECHO_SERVER_ADDR0 to
     * configECHO_SERVER_ADDR3 in FreeRTOSConfig.h. */
    xEchoServerAddress.usPort = SOCKETS_htons( echoECHO_PORT );
    xEchoServerAddress.ulAddress = SOCKETS_inet_addr_quick( configECHO_SERVER_ADDR0,
                                                            configECHO_SERVER_ADDR1,
                                                            configECHO_SERVER_ADDR2,
                                                            configECHO_SERVER_ADDR3 );


    for( int i=0; i<CONNECT_COUNT;i++ )
    {
    	 configPRINTF( ( "================= TCP Client Connect count=%d ===================\r\n", i ) );

        /* Create a TCP socket. */
        xSocket = SOCKETS_Socket( SOCKETS_AF_INET, SOCKETS_SOCK_STREAM, SOCKETS_IPPROTO_TCP );
        configASSERT( xSocket != SOCKETS_INVALID_SOCKET );

        /* Set a time out so a missing reply does not cause the task to block
         * indefinitely. */
        SOCKETS_SetSockOpt( xSocket, 0, SOCKETS_SO_RCVTIMEO, &xReceiveTimeOut, sizeof( xReceiveTimeOut ) );
        SOCKETS_SetSockOpt( xSocket, 0, SOCKETS_SO_SNDTIMEO, &xSendTimeOut, sizeof( xSendTimeOut ) );

        #if ( ipconfigUSE_TCP_WIN == 1 )
            {
                /* Set the window and buffer sizes. */
                SOCKETS_SetSockOpt( xSocket, 0, FREERTOS_SO_WIN_PROPERTIES, ( void * ) &xWinProps, sizeof( xWinProps ) );
            }
        #endif /* ipconfigUSE_TCP_WIN */

        #if ( configTCP_ECHO_TASKS_SINGLE_TASK_TLS_ENABLED == 1 )
            {
                /* Set the socket to use TLS. */
                SOCKETS_SetSockOpt( xSocket, 0, SOCKETS_SO_REQUIRE_TLS, NULL, ( size_t ) 0 );
                SOCKETS_SetSockOpt( xSocket, 0, SOCKETS_SO_TRUSTED_SERVER_CERTIFICATE, cTlsECHO_SERVER_CERTIFICATE_PEM, ulTlsECHO_SERVER_CERTIFICATE_LENGTH );
            }
        #endif /* configTCP_ECHO_TASKS_SINGLE_TASK_TLS_ENABLED */

        /* Connect to the echo server. */
        configPRINTF( ( "Connecting to echo server port=%d\r\n", echoECHO_PORT ) );

        if( SOCKETS_Connect( xSocket, &xEchoServerAddress, sizeof( xEchoServerAddress ) ) == 0 )
        {
            configPRINTF( ( "Connected to echo server (IP=%d.%d.%d.%d)\r\n",configECHO_SERVER_ADDR0, configECHO_SERVER_ADDR1, configECHO_SERVER_ADDR2, configECHO_SERVER_ADDR3 ) );
            ulConnections[ xInstance ]++;

            /* Send a number of echo requests. */
            for( lLoopCount = 0; lLoopCount < lMaxLoopCount; lLoopCount++ )
            {
                /* Create the string that is sent to the echo server. */
                xStringLength = prvCreateTxData( pcTransmittedString, echoBUFFER_SIZES );

                /* Add in some unique text at the front of the string. */
                sprintf( pcTransmittedString, "TxRx message number %u", ( unsigned ) ulTxCount );
                ulTxCount++;

                /* Send the string to the socket. */
                xTransmitted = SOCKETS_Send( xSocket,                        /* The socket being sent to. */
                                             ( void * ) pcTransmittedString, /* The data being sent. */
                                             xStringLength,                  /* The length of the data being sent. */
                                             0 );                            /* No flags. */

                configPRINTF( ( "Sending %s of length %d to echo server\r\n", pcTransmittedString, xStringLength ) );

                if( xTransmitted < 0 )
                {
                    /* Error? */
                    configPRINTF( ( "ERROR - Failed to send to echo server\r\n", pcTransmittedString ) );
                    break;
                }

                /* Clear the buffer into which the echoed string will be
                 * placed. */
                memset( ( void * ) pcReceivedString, 0x00, echoBUFFER_SIZES );
                xReceivedBytes = 0;

                /* Receive data echoed back to the socket. */
                while( xReceivedBytes < xTransmitted )
                {
                    xReturned = SOCKETS_Recv( xSocket,                                 /* The socket being received from. */
                                              &( pcReceivedString[ xReceivedBytes ] ), /* The buffer into which the received data will be written. */
                                              xStringLength - xReceivedBytes,          /* The size of the buffer provided to receive the data. */
                                              0 );                                     /* No flags. */

                    if( xReturned < 0 )
                    {
                        /* Error occurred.  Latch it so it can be detected
                         * below. */
                        xReceivedBytes = xReturned;
                        break;
                    }
                    else if( xReturned == 0 )
                    {
                        /* Timed out. */
                        configPRINTF( ( "Timed out receiving from echo server\r\n" ) );
                        break;
                    }
                    else
                    {
                        /* Keep a count of the bytes received so far. */
                        xReceivedBytes += xReturned;
                    }
                }

                /* If an error occurred it will be latched in xReceivedBytes,
                 * otherwise xReceived bytes will be just that - the number of
                 * bytes received from the echo server. */
                if( xReceivedBytes > 0 )
                {
                    /* Compare the transmitted string to the received string. */
                    configASSERT( strncmp( pcReceivedString, pcTransmittedString, xTransmitted ) == 0 );

                    if( strncmp( pcReceivedString, pcTransmittedString, xTransmitted ) == 0 )
                    {
                        /* The echo reply was received without error. */
                        ulTxRxCycles[ xInstance ]++;
                        configPRINTF( ( "Received correct string from echo server.\r\n" ) );
                    }
                    else
                    {
                        /* The received string did not match the transmitted
                         * string. */
                        ulTxRxFailures[ xInstance ]++;
                        configPRINTF( ( "ERROR - Received incorrect string from echo server.\r\n" ) );
                        break;
                    }
                }
                else if( xReceivedBytes < 0 )
                {
                    /* SOCKETS_Recv() returned an error. */
                    break;
                }
                else
                {
                    /* Timed out without receiving anything? */
                    break;
                }
            }

            /* Finished using the connected socket, initiate a graceful close:
             * FIN, FIN+ACK, ACK. */
            configPRINTF( ( "Shutting down connection to echo server.\r\n" ) );
            SOCKETS_Shutdown( xSocket, SOCKETS_SHUT_RDWR );

            /* Expect SOCKETS_Recv() to return an error once the shutdown is
             * complete. */
            xTimeOnEntering = xTaskGetTickCount();

            do
            {
                xReturned = SOCKETS_Recv( xSocket,                    /* The socket being received from. */
                                          &( pcReceivedString[ 0 ] ), /* The buffer into which the received data will be written. */
                                          echoBUFFER_SIZES,           /* The size of the buffer provided to receive the data. */
                                          0 );

                if( xReturned < 0 )
                {
                    break;
                }
            }
            while( ( xTaskGetTickCount() - xTimeOnEntering ) < xReceiveTimeOut );
        }
        else
        {
            configPRINTF( ( "Echo demo failed to connect to echo server %d.%d.%d.%d.\r\n",
                            configECHO_SERVER_ADDR0,
                            configECHO_SERVER_ADDR1,
                            configECHO_SERVER_ADDR2,
                            configECHO_SERVER_ADDR3 ) );
        }

        /* Close this socket before looping back to create another. */
        xReturned = SOCKETS_Close( xSocket );
        configASSERT( xReturned == SOCKETS_ERROR_NONE );

cleanup:
#if defined(TLS_SECRET_IN_TRUSTM)
#if (ENABLE_TRUSTM==1)
        trustm_CloseApp();
        configPRINTF( ("TCPCLient(): TrustM App closed.\r\n" ) );
#endif
#endif
        /* Pause for a short while to ensure the network is not too
         * congested. */
        vTaskDelay( echoLOOP_DELAY );
    }

    configPRINTF( ("TCPCLient(): ================= End of Connect===================\r\n" ) );

#if (SHOW_ECHO_TASK_PATH == 1)
    configPRINTF( ( "<prvEchoClientTask()\r\n") );
#endif
	while(1){}

}
/*-----------------------------------------------------------*/

static BaseType_t prvCreateTxData( char * cBuffer,
                                   uint32_t ulBufferLength )
{
    static uint32_t ulCharactersToAdd = 0UL;
    uint32_t ulCharacter;
    static char cChar = '0';

    /* Fill the buffer with an additional character for each time this
     * function is called, up to a maximum, at which time reset to 1 character. */
    ulCharactersToAdd++;

    if( ulCharactersToAdd > ulBufferLength )
    {
        ulCharactersToAdd = 1UL;
    }

    for( ulCharacter = 0; ulCharacter < ulCharactersToAdd; ulCharacter++ )
    {
        cBuffer[ ulCharacter ] = cChar;
        cChar++;

        if( cChar > '~' )
        {
            cChar = '0';
        }
    }

    return ulCharactersToAdd;
}
/*-----------------------------------------------------------*/

BaseType_t xAreSingleTaskTCPEchoClientsStillRunning( void )
{
    static uint32_t ulLastEchoSocketCount[ echoNUM_ECHO_CLIENTS ] = { 0 }, ulLastConnections[ echoNUM_ECHO_CLIENTS ] = { 0 };
    BaseType_t xReturn = pdPASS, x;

    /* Return fail is the number of cycles does not increment between
     * consecutive calls. */
    for( x = 0; x < echoNUM_ECHO_CLIENTS; x++ )
    {
        if( ulTxRxCycles[ x ] == ulLastEchoSocketCount[ x ] )
        {
            xReturn = pdFAIL;
        }
        else
        {
            ulLastEchoSocketCount[ x ] = ulTxRxCycles[ x ];
        }

        if( ulConnections[ x ] == ulLastConnections[ x ] )
        {
            xReturn = pdFAIL;
        }
        else
        {
            ulConnections[ x ] = ulLastConnections[ x ];
        }
    }

    return xReturn;
}
