#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

#include "optiga/optiga_util.h"
#include "optiga/pal/pal_os_event.h"
#include "optiga/ifx_i2c/ifx_i2c_config.h"
#include "mbedtls/base64.h"
#include "trustm_chipinfo.h"

/* PKCS#11 includes. */
#include "aws_pkcs11.h"

/* Key provisioning includes. */
#include "aws_dev_mode_key_provisioning.h"

/* OPTIGA Trust M defines. */
#define mainTrustM_TASK_STACK_SIZE     		( configMINIMAL_STACK_SIZE * 8 )

static TimerHandle_t xTrustMInitTimer;
SemaphoreHandle_t xTrustMSemaphoreHandle; /**< OPTIGA™ Trust M module semaphore. */
const TickType_t xTrustMSemaphoreWaitTicks = pdMS_TO_TICKS( 60000 );

extern optiga_lib_status_t trustm_OpenApp(void);
extern optiga_lib_status_t trustm_CloseApp(void);

#define SHOW_TRUSTM_PATH            0

///size of end entity certificate of OPTIGA™ Trust M
#define LENGTH_OPTIGA_CERT          512

extern uint8_t TrustM_device_cert[480];
extern size_t TrustM_Cert_Len;

extern void vStartTCPEchoClientTasks_SingleTasks( void );
extern optiga_lib_status_t read_chip_cert(uint16_t cert_oid, uint8_t* p_cert, uint16_t* p_cert_size);
/*************************************************************************
*  Global
*************************************************************************/
TaskHandle_t xHandle = NULL;

/*************************************************************************
*  Global
*************************************************************************/
optiga_util_t * util_handler;
uint16_t trustm_open_app_flag = 0;

optiga_lib_status_t open_app_status;
/* Callback when for Open Application operation
*/
static void optiga_util_app_callback(void * context, optiga_lib_status_t return_status)
{
	open_app_status = return_status;
   if (NULL != context)
   {
       // callback to upper layer here
   }
}

/**********************************************************************
* trustm_OpenApp()
**********************************************************************/
optiga_lib_status_t trustm_OpenApp(void)
{
	uint16_t i;
    optiga_lib_status_t return_status;
    const TickType_t xDelay = 50 / portTICK_PERIOD_MS;

#if (SHOW_TRUSTM_PATH == 1)
    configPRINTF( ( ">trustm_OpenApp()\r\n" ) );
#endif

    if(trustm_open_app_flag == 1)
    {
    	configPRINTF( ( "Warning: TrustM already opened\r\n" ) );
    	return OPTIGA_LIB_SUCCESS;
    }

    do
    {
        //Create an util handler to open the application on TrustM.
    	util_handler = optiga_util_create(0, optiga_util_app_callback, NULL);
        if (NULL == util_handler)
        {
        	configPRINTF( ( "Error: Create util handler failed. status=0x%x\r\n", util_handler ) );
            break;
        }

        /**
         * Open the application on TrustM which is a precondition to perform any other operations
         * using optiga_util_open_application
         */
		open_app_status = OPTIGA_LIB_BUSY;
        return_status = optiga_util_open_application(util_handler, 0);

        if (OPTIGA_LIB_SUCCESS != return_status)
        {
        	configPRINTF( ( "Error: Queue open App cmd failed. status=0x%x\r\n", return_status) );
            break;
        }

        //Wait until the optiga_util_open_application is completed
		i=0;
        while (open_app_status == OPTIGA_LIB_BUSY)
		{
			i++;
			vTaskDelay(xDelay);
			if (i == 50)
				break;
		}

        if (OPTIGA_LIB_SUCCESS != open_app_status)
        {
			configPRINTF( ( "Error: Open App failed. status=0x%x i=%d\r\n",open_app_status, i ) );
			return_status = open_app_status;
            break;
        }

        trustm_open_app_flag = 1;
        configPRINTF( ( "Open TrustM App Ok.\r\n") );

    }while(FALSE);

#if (SHOW_TRUSTM_PATH == 1)
    configPRINTF( ( "<trustm_OpenApp()\r\n" ) );
#endif
	return return_status;
}

/**********************************************************************
* trustm_CloseApp()
**********************************************************************/
optiga_lib_status_t trustm_CloseApp(void)
{
	uint16_t i;
    optiga_lib_status_t return_status;
    const TickType_t xDelay = 50 / portTICK_PERIOD_MS;

#if (SHOW_TRUSTM_PATH == 1)
    configPRINTF( ( ">trustm_CloseApp()\r\n" ) );
#endif

	do{
		if (trustm_open_app_flag == 0)
		{
			configPRINTF(("Warning: Cannot close TrustsM App because it is not open.\r\n"));
			break;
		}

		open_app_status = OPTIGA_LIB_BUSY;
        //++ty++ OPTIGA_COMMS_PROTECTION_MANAGE_CONTEXT(me_util, OPTIGA_COMMS_SESSION_CONTEXT_NONE);
        return_status = optiga_util_close_application(util_handler, 0);

        if (OPTIGA_LIB_SUCCESS != return_status)
        {
        	configPRINTF(("Error: Close TrustM App failed. status=0x%x\r\n",return_status));
            break;
        }

        //Wait until the optiga_util_open_application is completed
       	i=0;
        while (open_app_status == OPTIGA_LIB_BUSY)
        {
        	i++;
			vTaskDelay(xDelay);
			if (i == 50)
				break;
        }

        if (OPTIGA_LIB_SUCCESS != open_app_status)
        {
        	configPRINTF(("Error: Close TrustM App failed. status=0x%x i=%d\r\n", open_app_status, i ));
			return_status = open_app_status;
            break;
        }

        trustm_open_app_flag = 0;
		configPRINTF( ( "TrustM App closed Ok.\r\n" ) );

	}while(FALSE);

    // destroy util handler
    if (util_handler != NULL)
		optiga_util_destroy(util_handler);

#ifdef WORKAROUND
	pal_os_event_disarm();
#endif

#if (SHOW_TRUSTM_PATH == 1)
	configPRINTF( ( "<trustm_CloseApp()\r\n" ) );
#endif

	return return_status;
}

void vTrustMInitCallback( TimerHandle_t xTimer )
{
#if (SHOW_TRUSTM_PATH == 1)
	configPRINTF( ( ">vTrustMInitCallback(): Give Semaphore\r\n") );
#endif
	xSemaphoreGive(xTrustMSemaphoreHandle);
}

void vTrustMTaskCallbackHandler( void * pvParameters )
{
	//optiga_lib_status_t status = OPTIGA_DEVICE_ERROR;
#if (SHOW_TRUSTM_PATH == 1)
	configPRINTF( ( ">vTrustMTaskCallbackHandler()\r\n") );
#endif

	if ( xSemaphoreTake(xTrustMSemaphoreHandle, xTrustMSemaphoreWaitTicks) == pdTRUE )
	{
#if (SHOW_TRUSTM_PATH == 1)
		configPRINTF( ( "Take Semaphore..\r\n") );
#endif

		optiga_lib_status_t open_app_status = trustm_OpenApp();
		if (open_app_status != OPTIGA_LIB_SUCCESS)
		{
			configPRINTF( ( "vTrustMTaskCallbackHandler(): Error: Open TrustM App failed. status=0x%x\r\n",open_app_status) );
			goto cleanup;

		}else
		{
			configPRINTF( ( "vTrustMTaskCallbackHandler(): Open TrustM App Ok\r\n") );
		}

		uint16_t OID=0xE0E0;


		uint8_t p_cert[LENGTH_OPTIGA_CERT];
		uint16_t p_cert_size=LENGTH_OPTIGA_CERT;
		optiga_lib_status_t read_chip_cert_status = read_chip_cert(OID, p_cert, &p_cert_size);

		if(OPTIGA_LIB_SUCCESS != read_chip_cert_status )
		{
			configPRINTF( ( "vTrustMTaskCallbackHandler(): Read Chip Cert error 0x%x\r\n", read_chip_cert_status) );
			goto cleanup;
		}else
		{
			configPRINTF( ( "vTrustMTaskCallbackHandler(): Chip Cert size %d\r\n", p_cert_size) );
			TrustM_Cert_Len = p_cert_size;
		}

		memcpy(TrustM_device_cert, p_cert, p_cert_size);

		//Provisioning here
		vDevModeKeyProvisioning();

	    configPRINTF( ( "Start DEMO_RUNNER_RunDemos()\r\n") );

	    vStartTCPEchoClientTasks_SingleTasks();
	}

cleanup:
	configPRINTF( ( "Task vTrustMTaskCallbackHandler is killed.\r\n") );

	vTaskDelete(xHandle);
}

void OPTIGA_TRUST_M_Init(void)
{

#if (SHOW_TRUSTM_PATH == 1)
	configPRINTF( ( ">OPTIGA_TRUST_M_Init()\r\n" ) );
#endif

	/* Create the handler for the callbacks. */
	xTaskCreate( vTrustMTaskCallbackHandler,       /* Function that implements the task. */
				"MTask",          /* Text name for the task. */
				configMINIMAL_STACK_SIZE*8,      /* Stack size in words, not bytes. */
				NULL,    /* Parameter passed into the task. */
				tskIDLE_PRIORITY,/* Priority at which the task is created. */
				&xHandle );      /* Used to pass out the created task's handle. */

    xTrustMSemaphoreHandle = xSemaphoreCreateBinary();

	xTrustMInitTimer = xTimerCreate("TrustM_init_timer",        /* Just a text name, not used by the kernel. */
									pdMS_TO_TICKS(1),    /* The timer period in ticks. */
									pdFALSE,         /* The timers will auto-reload themselves when they expire. */
									( void * )NULL,   /* Assign each timer a unique id equal to its array index. */
									vTrustMInitCallback  /* Each timer calls the same callback when it expires. */
									);
	if( xTrustMInitTimer == NULL )
	{
		// The timer was not created.
	}
	else
	{
		// Start the timer.  No block time is specified, and even if one was
		// it would be ignored because the scheduler has not yet been
		// started.
		if( xTimerStart( xTrustMInitTimer, 0 ) != pdPASS )
		{
		    // The timer could not be set into the Active state.
		}
	}
#if (SHOW_TRUSTM_PATH == 1)
	configPRINTF( ( "<OPTIGA_TRUST_M_Init()\r\n" ) );
#endif
}

