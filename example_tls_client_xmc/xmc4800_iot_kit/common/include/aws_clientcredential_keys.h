#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

#include <stdint.h>

/*
 * PEM-encoded client certificate
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */

#if defined(TLS_SECRET_IN_FLASH)
//This certificate (public key) is used for local TLS connectivity
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIB5zCCAY0CEHd3d3d3d3d3d3d3d3d3d3cwCgYIKoZIzj0EAwIweDELMAkGA1UE\n"\
"BhMCU0cxEjAQBgNVBAgMCVNpbmdhcG9yZTESMBAGA1UEBwwJU2luZ2Fwb3JlMR4w\n"\
"HAYDVQQKDBVJbmZpbmVvbiBUZWNobm9sb2dpZXMxDDAKBgNVBAsMA0RTUzETMBEG\n"\
"A1UEAwwKVExTX0NsaWVudDAeFw0xOTA3MTUwMjM1MjVaFw0yOTA3MTIwMjM1MjVa\n"\
"MHgxCzAJBgNVBAYTAlNHMRIwEAYDVQQIDAlTaW5nYXBvcmUxEjAQBgNVBAcMCVNp\n"\
"bmdhcG9yZTEeMBwGA1UECgwVSW5maW5lb24gVGVjaG5vbG9naWVzMQwwCgYDVQQL\n"\
"DANEU1MxEzARBgNVBAMMClRMU19DbGllbnQwWTATBgcqhkjOPQIBBggqhkjOPQMB\n"\
"BwNCAARHTd7EABscxNplI+o2zjFk4oiql92fuGWjoLv19gyaTjf2yS+zZVeGS6Xw\n"\
"T3UTzbXjucyjZVrUBrswmzyYEe3zMAoGCCqGSM49BAMCA0gAMEUCIHSf/xDsBm7o\n"\
"PlykA7lk1m9p1VL4HrZmvu9ZeE7Mo90QAiEAj4sGEBnUK9iCFFB3vjEZE2/iCUf8\n"\
"dqHqFMcq4ulHDtQ=\n"\
"-----END CERTIFICATE-----";

#endif

#if defined(TLS_SECRET_IN_TRUSTM)
//This certificate (public key) is stored in 0xe0e0.

#define keyCLIENT_CERTIFICATE_PEM \
	"-----BEGIN CERTIFICATE-----\n"\
	"-----END CERTIFICATE-----;"
#endif

/*
 * PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 * This is required if you're using JITR, since the issuer (Certificate
 * Authority) of the client certificate is used by the server for routing the
 * device's initial request. (The device client certificate must always be
 * sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html,
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set below to NULL.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM    NULL

/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */


#if defined(TLS_SECRET_IN_FLASH)
//This private key is used for local TLS connectivity
/*
"-----BEGIN EC PARAMETERS-----\n"\
"BggqhkjOPQMBBw==\n"\
"-----END EC PARAMETERS-----\n"\
*/
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN EC PRIVATE KEY-----\n"\
"MHcCAQEEIJqtXjc/P++Ikb0+XsMvf9xowjOP1sScq3CPc8n8A8lPoAoGCCqGSM49\n"\
"AwEHoUQDQgAER03exAAbHMTaZSPqNs4xZOKIqpfdn7hlo6C79fYMmk439skvs2VX\n"\
"hkul8E91E82147nMo2Va1Aa7MJs8mBHt8w==\n"\
"-----END EC PRIVATE KEY-----"
#endif

#if defined(TLS_SECRET_IN_TRUSTM)
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN EC PRIVATE KEY-----\n"\
"MHcCAQEEIJqtXjc/P++Ikb0+XsMvf9xowjOP1sScq3CPc8n8A8lPoAoGCCqGSM49\n"\
"AwEHoUQDQgAER03exAAbHMTaZSPqNs4xZOKIqpfdn7hlo6C79fYMmk439skvs2VX\n"\
"hkul8E91E82147nMo2Va1Aa7MJs8mBHt8w==\n"\
"-----END EC PRIVATE KEY-----"
#endif


/* The constants above are set to const char * pointers defined in aws_dev_mode_key_provisioning.c,
 * and externed here for use in C files.  NOTE!  THIS IS DONE FOR CONVENIENCE
 * DURING AN EVALUATION PHASE AND IS NOT GOOD PRACTICE FOR PRODUCTION SYSTEMS
 * WHICH MUST STORE KEYS SECURELY. */
extern const char clientcredentialCLIENT_CERTIFICATE_PEM[];
extern const char * clientcredentialJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM;
extern const char clientcredentialCLIENT_PRIVATE_KEY_PEM[];
extern const uint32_t clientcredentialCLIENT_CERTIFICATE_LENGTH;
extern const uint32_t clientcredentialCLIENT_PRIVATE_KEY_LENGTH;

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
