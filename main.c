////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////    main.c
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <avr/io.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* serial interface include file. */
#include "serial.h"


/*-----------------------------------------------------------*/
/* Create a handle for the serial port. */
extern xComPortHandle xSerialPort;

// Main Arduino Mega 2560, Freetronics EtherMega (Red) LED Blink

/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/

static void enableRed(int yes) {
	if (yes != 0) {
		avrSerialPrint_P(PSTR("\r\nred on!\r\n"));
		PORTH |= _BV(PORTH3);
	} else {
		avrSerialPrint_P(PSTR("\r\nred off!\r\n"));
		PORTH &= ~_BV(PORTH3);
	}
}

static void enableGreen(int yes) {
	if (yes != 0) {
		avrSerialPrint_P(PSTR("\r\ngreen on!\r\n"));
		PORTE |= _BV(PORTE3);
	} else {
		avrSerialPrint_P(PSTR("\r\ngreen off!\r\n"));
		PORTE &= ~_BV(PORTE3);
	}
}

static void enableBlue(int yes) {
	if (yes != 0) {
		avrSerialPrint_P(PSTR("\r\nblue on!\r\n"));
		PORTE |= _BV(PORTE5);
	} else {
		avrSerialPrint_P(PSTR("\r\nblue off!\r\n"));
		PORTE &= ~_BV(PORTE5);
	}
}


static void TaskBlinkGreenLED(void *pvParameters) // Main Red LED Flash
{
	(void) pvParameters;
	TickType_t xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialised with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = 0 / portTICK_PERIOD_MS;

	DDRE |= _BV(DDE3);
	enableGreen(0);

	while(1)
	{
		avrSerialPrint_P(PSTR("\r\ngreen: step 1!\r\n"));
		enableGreen(1);

		vTaskDelayUntil( &xLastWakeTime, ( 333 / portTICK_PERIOD_MS ) );

		avrSerialPrint_P(PSTR("\r\ngreen: step 2!\r\n"));
		enableGreen(0);

		vTaskDelayUntil( &xLastWakeTime, ( 333 / portTICK_PERIOD_MS ) );

		avrSerialPrint_P(PSTR("\r\ngreen: step 3!\r\n"));
		enableGreen(0);
		vTaskDelayUntil( &xLastWakeTime, ( 333 / portTICK_PERIOD_MS ) );

	}
}


static void TaskBlinkRedLED(void *pvParameters) // Main Red LED Flash
{
    (void) pvParameters;
    TickType_t xLastWakeTime;
    /* The xLastWakeTime variable needs to be initialised with the current tick
    count.  Note that this is the only time we access this variable.  From this
    point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
    API function. */
    xLastWakeTime = 0 / portTICK_PERIOD_MS;


    DDRH |= _BV(DDH3);

	enableRed(0);
    while(1)
    {

    	avrSerialPrint_P(PSTR("\r\nred: step 1!\r\n"));
    	enableRed(0);

		vTaskDelayUntil( &xLastWakeTime , ( 333 / portTICK_PERIOD_MS ) );

		avrSerialPrint_P(PSTR("\r\nred: step 2!\r\n"));
		enableRed(1);

		vTaskDelayUntil( &xLastWakeTime , ( 333 / portTICK_PERIOD_MS ) );

		avrSerialPrint_P(PSTR("\r\nred: step 3!\r\n"));
    	enableRed(0);

		vTaskDelayUntil( &xLastWakeTime , ( 333 / portTICK_PERIOD_MS ) );
    }
}

static void TaskBlinkBlueLED(void *pvParameters) // Main Red LED Flash
{
	(void) pvParameters;
	TickType_t xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialised with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = 0 / portTICK_PERIOD_MS;

	DDRE |= _BV(DDE3);
	enableBlue(0);

	while(1)
	{
		avrSerialPrint_P(PSTR("\r\nblue: step 1!\r\n"));
		enableBlue(0);

		vTaskDelayUntil( &xLastWakeTime, ( 333 / portTICK_PERIOD_MS ) );

		avrSerialPrint_P(PSTR("\r\nblue: step 2!\r\n"));
		enableBlue(0);

		vTaskDelayUntil( &xLastWakeTime, ( 333 / portTICK_PERIOD_MS ) );

		avrSerialPrint_P(PSTR("\r\nblue: step 3!\r\n"));
		enableBlue(1);

		vTaskDelayUntil( &xLastWakeTime, ( 333 / portTICK_PERIOD_MS ) );

	}
}


/*-----------------------------------------------------------*/


/* Main program loop */
int main(void) __attribute__((OS_main));

int main(void)
{

    // turn on the serial port for debugging or for other USART reasons.
    xSerialPort = xSerialPortInitMinimal( USART0, 115200, portSERIAL_BUFFER_TX, portSERIAL_BUFFER_RX); //  serial port: WantedBaud, TxQueueLength, RxQueueLength (8n1)

    avrSerialPrint_P(PSTR("\r\n\n\nHello World!\r\n")); // Ok, so we're alive...

    xTaskCreate(
        TaskBlinkRedLED
        ,  (const portCHAR *)"RedLED"
        ,  256
        ,  NULL
        ,  3
        ,  NULL );

    xTaskCreate(
		 TaskBlinkGreenLED
		,  (const portCHAR *)"GreenLED"
		,  256
		,  NULL
		,  3
		,  NULL ); // */

    xTaskCreate(
		 TaskBlinkBlueLED
		,  (const portCHAR *)"BlueLED"
		,  256
		,  NULL
		,  3
		,  NULL ); // */

    avrSerialPrintf_P(PSTR("\r\n\nFree Heap Size: %u\r\n"),xPortGetFreeHeapSize() ); // needs heap_1 or heap_2 for this function to succeed.

    vTaskStartScheduler();

    avrSerialPrint_P(PSTR("\r\n\n\nGoodbye... no space for idle task!\r\n")); // Doh, so we're dead...

}


/*-----------------------------------------------------------*/


void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    portCHAR *pcTaskName )
{

    DDRB  |= _BV(DDB7);
    PORTB |= _BV(PORTB7);       // main (red PB7) LED on. Mega main LED on and die.
    while(1);
}

/*-----------------------------------------------------------*/
