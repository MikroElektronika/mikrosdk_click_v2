/*!
 * \file 
 * \brief OOK RX Click example
 * 
 * # Description
 * This example showcases how to initialize and use the OOK RX click. The click decrypts information
 * embedded in a 433 MHz frequency radio signal. In order for the OOK communication to work a receiver
 * click needs to be used. OOK TX plays that role - it encrypts, embeds and sends the data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function waits for the transmitter to send the data and then reads and displays it in
 * the console using the UART communication.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ookrx.h"

#define BYTE_RECEIVE
// #define DATA_RECEIVE

#define PREABLE_WORD 0xCE35

// ------------------------------------------------------------------ VARIABLES

static ookrx_t ookrx;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    ookrx_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info(&logger, "Application Init");

    //  Click initialization.

    ookrx_cfg_setup( &cfg );
    OOKRX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ookrx_init( &ookrx, &cfg );
    Delay_ms( 100 );
    
#ifdef BYTE_RECEIVE
    log_info(&logger, "Application Task\r\n BYTE TRANSMIT DEMO");
#endif
    
#ifdef DATA_RECEIVE
    log_info(&logger, "Application Task\r\n DATA TRANSMIT DEMO");
#endif
}

void application_task ( )
{
#ifdef BYTE_RECEIVE
    uint8_t received_byte;

    if ( ! ( ookrx_receive_data( &ookrx, PREABLE_WORD, &received_byte, 1 ) ) )
    {
        log_printf( &logger, "%c", received_byte );
    }
#endif
#ifdef DATA_RECEIVE
    uint8_t received_package[ 10 ] = { 0 };

    if ( ! ( ookrx_receive_data( &ookrx, PREABLE_WORD, received_package, 6 ) ) )
    {
        log_printf( &logger, " * Received packet: %s\r\n", received_package );
    }
#endif
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
