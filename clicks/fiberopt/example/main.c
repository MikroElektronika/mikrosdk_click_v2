/*!
 * \file 
 * \brief Fiber Opt Click example
 * 
 * # Description
 * This example demonstrates the use of an Fiber Opt click board by showing
 * the communication between the two click boards.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes device and makes an initial log.
 * 
 * ## Application Task
 * Depending on the selected application mode, it reads all the received data or 
 * sends the desired text message with the message counter once per second.
 * 
 * \author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "fiberopt.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

// Text message to send in the transmitter application mode
#define DEMO_TEXT_MESSAGE           "MIKROE - Fiber Opt click board\r\n\0"

static fiberopt_t fiberopt;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    fiberopt_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    fiberopt_cfg_setup( &cfg );
    FIBEROPT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fiberopt_init( &fiberopt, &cfg );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    fiberopt_generic_write( &fiberopt, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms( 1000 ); 
#else
    uint8_t rx_byte = 0;
    if ( 1 == fiberopt_generic_read( &fiberopt, &rx_byte, 1 ) )
    {
       log_printf( &logger, "%c", rx_byte );
    }
#endif
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
