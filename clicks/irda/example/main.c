/*!
 * \file main.c
 * \brief IrDA Click example
 *
 * # Description
 * This example demonstrates the use of IrDA Click board.
 * The example can perform both roles, transceiver and receiver.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes UART driver and all used control pins.
 * Also clears the response buffer.
 *
 * ## Application Task
 * Demonstrates the use of IrDA click which can be used as transceiver or
 * receiver. A message bytes can be send and receive all at once or byte to
 * byte.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include <string.h>
#include "board.h"
#include "log.h"
#include "irda.h"

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER_1
//#define DEMO_APP_RECEIVER_2
//#define DEMO_APP_TRANSCEIVER_1
#define DEMO_APP_TRANSCEIVER_2

static irda_t irda;
static log_t console;

static const char tx_message[ 19 ] = { 'M', 'i', 'k', 'r', 'o', 'E',
'l', 'e', 'k', 't', 'r', 'o', 'n', 'i', 'k', 'a', '\r', '\n', '\0' };
static char rx_message[ 20 ];
static uint8_t idx;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    irda_cfg_t irda_cfg;
    log_cfg_t console_cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( console_cfg );
    console_cfg.level = LOG_LEVEL_DEBUG;
    console_cfg.baud = 57600;
    log_init( &console, &console_cfg );
    log_printf( &console, "***  IrDA initialization done  ***\r\n" );
    log_printf( &console, "**********************************\r\n" );

    //  Click initialization.
    irda_cfg_setup( &irda_cfg );
    IRDA_MAP_MIKROBUS( irda_cfg, MIKROBUS_1 );
    irda_init( &irda, &irda_cfg );
    irda_default_cfg( &irda );
    irda_reset( &irda );

    //  Clear response.
    memset( rx_message, 0, sizeof( rx_message ) );
}

void application_task( void )
{

#ifdef DEMO_APP_RECEIVER_1

    rx_message[ 0 ] = irda_generic_single_receive( &irda );

    log_printf( &console, "%c", ( char ) rx_message[ 0 ] );
    Delay_ms( 100 );

#endif

#ifdef DEMO_APP_RECEIVER_2

    irda_generic_multiple_receive( &irda, rx_message, '\n' );

    log_printf( &console, "RECEIVED MESSAGE : " );
    log_printf( &console, "%s\r\n", rx_message );
    Delay_ms( 100 );

#endif
    
#ifdef DEMO_APP_TRANSCEIVER_1

    irda_generic_multiple_send( &irda, tx_message );

    log_printf( &console, "MESSAGE SENT\r\n" );
    Delay_ms( 2000 );

#endif
    
#ifdef DEMO_APP_TRANSCEIVER_2

    idx = 0;

    while ( tx_message[ idx ] != '\0' )
    {
        irda_generic_single_send( &irda, tx_message[ idx++ ] );
    }

    log_printf( &console, "MESSAGE SENT\r\n" );
    Delay_ms( 2000 );

#endif

}

void main( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
