/*!
 * @file main.c
 * @brief MCP251863 Click example
 *
 * # Description
 * This example demonstrates the use of an MCP251863 click board by showing
 * the communication between the two click boards configured as a receiver and transmitter.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, performs the click default configuration and 
 * displays the selected application mode.
 *
 * ## Application Task
 * Depending on the selected mode, it sends a desired message using CAN protocol or
 * reads all the received data and displays them on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mcp251863.h"

// #define DEMO_APP_TRANSMITTER    // Uncomment this line to switch to the transmitter mode

#define DEMO_TEXT_MESSAGE   "MikroE"

static mcp251863_t mcp251863;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mcp251863_cfg_t mcp251863_cfg;  /**< Click config object. */

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
    mcp251863_cfg_setup( &mcp251863_cfg );
    MCP251863_MAP_MIKROBUS( mcp251863_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mcp251863_init( &mcp251863, &mcp251863_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MCP251863_ERROR == mcp251863_default_cfg ( &mcp251863 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    if ( MCP251863_OK == mcp251863_transmit_message( &mcp251863, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " The message \"%s\" has been sent!\r\n", ( char * ) DEMO_TEXT_MESSAGE );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    uint8_t data_buf[ 256 ] = { 0 };
    uint16_t data_len = 0;
    if ( MCP251863_OK == mcp251863_receive_message( &mcp251863, data_buf, &data_len ) )
    {
        log_printf( &logger, " A new message has received: \"" );
        for ( uint16_t cnt = 0; cnt < data_len; cnt++ )
        {
            log_printf( &logger, "%c", data_buf[ cnt ] );
        }
        log_printf( &logger, "\"\r\n" );
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
