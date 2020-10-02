/*!
 * \file 
 * \brief RF Switch Click example
 * 
 * # Description
 * This Click is a switch between small signal components such as filter banks, single-band LNAs,
 * converters, etc. It can be used for low power, low loss requirements in all systems operating
 * up to 3 GHz, including PCS, GSM, DCS, Bluetooth, and other receive chain applications. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO, sets CS and PWM pins as output 
 * and initializes write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of RF Switch Click board.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rfswitch.h"

// ------------------------------------------------------------------ VARIABLES

static rfswitch_t rfswitch;
static log_t logger;

static uint8_t selected_port;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rfswitch_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    rfswitch_cfg_setup( &cfg );
    RFSWITCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rfswitch_init( &rfswitch, &cfg );

    selected_port = 1;
}

void application_task ( void )
{
    if ( selected_port == 1 ) 
    {
        rfswitch_select_channel( &rfswitch, RFSWITCH_SELECT_CHANNEL_1 );
        log_printf( &logger, "  Switch to RF Port 1  \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
    }
    else if ( selected_port == 2 ) 
    {
        rfswitch_select_channel(  &rfswitch, RFSWITCH_SELECT_CHANNEL_2 );
        log_printf( &logger, "  Switch to RF Port 2  \r\n" );
        log_printf( &logger, "-----------------------\r\n" );
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
