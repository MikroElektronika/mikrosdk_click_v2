/*!
 * @file main.c
 * @brief MCP2003B Click Example.
 *
 * # Description
 * This example demonstrates the use of an MCP2003B Click board by showing
 * the communication between the two Click board configured as a receiver and transmitter.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and displays the selected application mode.
 *
 * ## Application Task
 * Depending on the selected mode, it reads all the received data or 
 * sends the desired message every 3 seconds.
 *
 * @note
 * The Click boards should be connected as follows: VBB->VBB, LBUS->LBUS, GND->GND.
 * The communication power supply voltage provided on VBB pin should be in range from 5.5V to 30V.
 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mcp2003b.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

#define DEMO_TEXT_MESSAGE   "MIKROE - MCP2003B Click board\r\n"

static mcp2003b_t mcp2003b;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mcp2003b_cfg_t mcp2003b_cfg;  /**< Click config object. */

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
    mcp2003b_cfg_setup( &mcp2003b_cfg );
    MCP2003B_MAP_MIKROBUS( mcp2003b_cfg, MIKROBUS_1 );
    if ( UART_ERROR == mcp2003b_init( &mcp2003b, &mcp2003b_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
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
    mcp2003b_generic_write( &mcp2003b, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 ); 
#else
    uint8_t rx_data = 0;
    if ( mcp2003b_generic_read( &mcp2003b, &rx_data, 1 ) > 0 )
    {
        log_printf( &logger, "%c", rx_data );
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
