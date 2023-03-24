/*!
 * \file
 * \brief Relay Click example
 *
 * # Description
 * Demo application is used to shows basic controls Relay click
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
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
#include "relay.h"

// ------------------------------------------------------------------ VARIABLES

static relay_t relay;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    relay_cfg_t cfg;

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

    relay_cfg_setup( &cfg );
    RELAY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    relay_init( &relay, &cfg );

    relay_default_cfg ( &relay );
    Delay_ms( 1500 );
}

void application_task ( void )
{
    uint8_t cnt;

    //  Task implementation.

    for ( cnt = 1; cnt <= 2; cnt++)
    {
        log_info( &logger, "*** Relay %d state is ON \r\n", (uint16_t)cnt);
        relay_set_state( &relay, cnt, RELAY_STATE_ON );
        Delay_ms ( 1000 );
        log_info( &logger, "*** Relay %d state is OFF \r\n", (uint16_t)cnt);
        relay_set_state( &relay, cnt, RELAY_STATE_OFF );
        Delay_ms ( 200 );
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
