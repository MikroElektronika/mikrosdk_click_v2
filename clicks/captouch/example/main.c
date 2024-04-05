/*!
 * \file 
 * \brief Cap Touch Click example
 * 
 * # Description
 * Demo application is used to shows basic controls Cap Touch click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 *  Checks for a new touch event. If so, prints the message to USBUART.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "captouch.h"

// ------------------------------------------------------------------ VARIABLES

static captouch_t captouch;
static log_t logger;
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    captouch_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    captouch_cfg_setup( &cfg );
    CAPTOUCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    captouch_init( &captouch, &cfg );

    captouch_default_cfg( &captouch );
}

void application_task ( void )
{
    uint8_t touch;

    //  Task implementation.

    touch = captouch_get_touch( &captouch );
    if ( touch != 0 )
    {
        log_printf( &logger, "-- New Touch\r\n" );
        Delay_ms ( 200 );
    }
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
