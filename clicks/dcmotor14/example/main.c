/*!
 * \file 
 * \brief DC MOTOR 14 Click example
 * 
 * # Description
 * This example demonstrates the use of DC Motor 14 Click board. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and makes an initial log.
 * 
 * ## Application Task  
 * Drives the motor in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
 * and after that drives it in the reverse direction for 5 seconds, and finally, 
 * disconnects the motor for 2 seconds. Each step will be logged on the USB UART where
 * you can track the program flow.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor14.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor14_t dcmotor14;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor14_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    dcmotor14_cfg_setup( &cfg );
    DCMOTOR14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor14_init( &dcmotor14, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, "The motor turns forward! \r\n" );
    dcmotor14_forward( &dcmotor14 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "Pull brake! \r\n" );
    dcmotor14_brake( &dcmotor14 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor turns in reverse! \r\n" );
    dcmotor14_reverse( &dcmotor14 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "The motor is disconnected (High-Z)!  \r\n" );
    dcmotor14_stop( &dcmotor14 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
