/*!
 * \file 
 * \brief Signal Realy Click example
 * 
 * # Description
 * Demo application is used to shows basic controls Signal Relay Click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the Click in the default configuration.
 * 
 * ## Application Task  
 * Alternately sets relays to ON-OFF state...
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "signalrelay.h"

// ------------------------------------------------------------------ VARIABLES

static signalrelay_t signalrelay;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    signalrelay_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----");

    //  Click initialization.

    signalrelay_cfg_setup( &cfg );
    SIGNALRELAY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    signalrelay_init( &signalrelay, &cfg );

    signalrelay_default_cfg ( &signalrelay );
}

void application_task ( void )
{
    uint8_t cnt;

    //  Task implementation.

    for ( cnt = 1; cnt <= 4; cnt++ )
    {
        log_info( &logger, " *** Relay [ %d ] ON ", cnt );
        signalrelay_relay_state( &signalrelay, cnt, SIGNALRELAY_STATE_ON );
        Delay_ms ( 200 );
        log_info( &logger, " *** Relay [ %d ] OFF ", cnt );
        signalrelay_relay_state( &signalrelay, cnt, SIGNALRELAY_STATE_OFF );
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
