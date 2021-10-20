/*!
 * \file 
 * \brief Relay 3 Click example
 * 
 * # Description
 * This example starts off with the initialization and configuration of the click and logger
 * modules and later on showcases how to turn specified relays ON/OFF using the output pins. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initialises and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function turns on the 1st and the 2nd relay and then turns them both off.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "relay3.h"

// ------------------------------------------------------------------ VARIABLES

static relay3_t relay3;
static log_t logger;

static int case1_switch = 0;
static int case2_switch = 0;
static int case3_switch = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void case_1 ( )
{
    if ( case1_switch == 0 )
    {
        relay3_relay_on( &relay3, RELAY3_RELAY_1 );
        log_printf( &logger, "   Relay_1 ON.   \r\n" );

        case1_switch++;
    }
    else if ( case1_switch == 1 )
    {
        relay3_relay_off( &relay3, RELAY3_RELAY_1 );
        log_printf( &logger, "   Relay_1 OFF.   \r\n" );

        case1_switch--;
    }
}

static void case_2 ( )
{
    if ( case2_switch == 0 )
    {
        relay3_relay_on( &relay3, RELAY3_RELAY_2 );
        log_printf( &logger, "   Relay_2 ON.   \r\n" );
        
        case2_switch++;
    }
    else if ( case2_switch == 1 )
    {
        relay3_relay_off( &relay3, RELAY3_RELAY_2 );
        log_printf( &logger, "   Relay_2 OFF.   \r\n" );

        case2_switch--;
    }
}

static void case_3 ( ) 
{
    if ( case3_switch == 0 )
    {
        relay3_relay_on( &relay3, RELAY3_BOTH_RELAYS );
        log_printf( &logger, "   Both relays ON.   \r\n" );

        case3_switch++;
    }
    else if ( case3_switch == 1 )
    {
        relay3_relay_off( &relay3, RELAY3_BOTH_RELAYS );
        log_printf( &logger, "   Both relays OFF.   \r\n" );

        case3_switch--;
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    relay3_cfg_t cfg;

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

    relay3_cfg_setup( &cfg );
    RELAY3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    relay3_init( &relay3, &cfg );
}

void application_task ( )
{
    case_1( );
    Delay_ms( 1000 );

    case_2( );
    Delay_ms( 1000 );

    case_3( );
    Delay_ms( 1000 );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
