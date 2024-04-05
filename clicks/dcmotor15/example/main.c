/*!
 * @file main.c
 * @brief DC Motor 15 Click Example.
 *
 * # Description
 * This example demonstrates the use of DC Motor 15 click board. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and makes an initial log.
 *
 * ## Application Task
 * Drives the motor in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
 * and after that drives it in the reverse direction for 5 seconds, and finally, 
 * disconnects the motor for 2 seconds. It will also calculates and displays the motor current consumption.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor15.h"

// Number of ADC conversions that will be performed for a single current measurement.
#define NUM_OF_ADC_CONVERSATIONS        1000  

// Time period for forward and reverse modes in seconds.  
#define RUN_PERIOD                      6  

// Time period for brake and stop modes in seconds.               
#define IDLE_PERIOD                     3     

static dcmotor15_t dcmotor15;   /**< DC Motor 15 Click driver object. */
static log_t logger;            /**< Logger object. */

void display_current ( dcmotor15_t *ctx, uint16_t delay )
{
    float current = 0;
    for ( uint8_t cnt = 0; cnt < delay; cnt++ ) 
    {  
        Delay_ms ( 1000 );
        current = dcmotor15_get_current ( &dcmotor15, NUM_OF_ADC_CONVERSATIONS );
        log_printf( &logger, " Current : %.3f [A]\r\n", current ); 
    }
    log_printf( &logger, " ------------------------------\r\n" );   
}

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    dcmotor15_cfg_t dcmotor15_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dcmotor15_cfg_setup( &dcmotor15_cfg );
    DCMOTOR15_MAP_MIKROBUS( dcmotor15_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == dcmotor15_init( &dcmotor15, &dcmotor15_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    dcmotor15_default_cfg ( &dcmotor15 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " The motor turns forward! \r\n" );
    dcmotor15_forward( &dcmotor15 );
    display_current ( &dcmotor15, RUN_PERIOD );
    log_printf( &logger, " Pull brake! \r\n" );
    dcmotor15_brake( &dcmotor15 );
    display_current ( &dcmotor15, IDLE_PERIOD );
    log_printf( &logger, " The motor turns in reverse! \r\n" );
    dcmotor15_reverse( &dcmotor15 );
    display_current ( &dcmotor15, RUN_PERIOD );
    log_printf( &logger, " The motor is disconnected (High-Z)!  \r\n" );
    dcmotor15_stop( &dcmotor15 );
    display_current ( &dcmotor15, IDLE_PERIOD );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
