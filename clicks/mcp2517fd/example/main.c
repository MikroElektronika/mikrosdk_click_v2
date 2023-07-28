/*!
 * @file main.c
 * @brief MCP2517FD Click example
 *
 * # Description
 * This example demonstrates the use of an MCP2517FD click board by showing
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
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "mcp2517fd.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

// Text message to send in the transmitter application mode
#define DEMO_TEXT_MESSAGE           "MIKROE\0"

static mcp2517fd_t mcp2517fd;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mcp2517fd_cfg_t mcp2517fd_cfg;  /**< Click config object. */

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
    mcp2517fd_cfg_setup( &mcp2517fd_cfg );
    MCP2517FD_MAP_MIKROBUS( mcp2517fd_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mcp2517fd_init( &mcp2517fd, &mcp2517fd_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MCP2517FD_ERROR == mcp2517fd_default_cfg ( &mcp2517fd ) )
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
    if ( MCP2517FD_OK == mcp2517fd_transmit_message( &mcp2517fd, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " The message \"%s\" has been sent!\r\n", ( char * ) DEMO_TEXT_MESSAGE );
    }
    Delay_ms( 2000 );
#else
    uint8_t data_buf[ 256 ] = { 0 };
    uint16_t data_len = 0;
    if ( MCP2517FD_OK == mcp2517fd_receive_message( &mcp2517fd, data_buf, &data_len ) )
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

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
