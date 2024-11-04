/*!
 * @file main.c
 * @brief IrDA 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of IrDA 4 Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and disables the transmitter shutdown.
 *
 * ## Application Task
 * Demonstrates the use of IrDA 4 clicks which can be used as transmitter or receiver. 
 * - TRANSMITTER : Device is sending tx_message data. 
 * - RECEIVER    : Device is reading a message that is being transmitted and 
 *                 logs it on the UART terminal. 
 *  
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "irda4.h"

// To configure the driver into receiver mode comment out the line below.
#define DEMO_APP_TRANSMITTER

static irda4_t irda4;
static log_t logger;

static uint8_t tx_message[ 8 ] = { 'M', 'i', 'k', 'r', 'o', 'E', '\r', '\n' };
static uint8_t rx_message;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irda4_cfg_t irda4_cfg;  /**< Click config object. */

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
    irda4_cfg_setup( &irda4_cfg );
    IRDA4_MAP_MIKROBUS( irda4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == irda4_init( &irda4, &irda4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    irda4_set_tx_shutdown( &irda4, IRDA4_SHUTDOWN_DISABLED );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#if defined( DEMO_APP_TRANSMITTER )
    for ( uint8_t n_cnt = 0; n_cnt < 8; n_cnt++ )
    {
        irda4_generic_write( &irda4, &tx_message[ n_cnt ], 1 );
        Delay_ms ( 500 );
    }
    log_printf( &logger, "Message sent \r\n" );
#else
    if ( 1 == irda4_generic_read( &irda4, &rx_message, 1 ) )
    {
        log_printf( &logger, "%c", rx_message );
    }
#endif
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
