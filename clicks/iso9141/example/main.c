/*!
 * @file main.c
 * @brief ISO 9141 Click Example.
 *
 * # Description
 * This example demonstrates the use of an ISO 9141 click board by showing
 * the communication between the two click boards.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes device and makes an initial log.
 * 
 * ## Application Task
 * Depending on the selected application mode, it reads all the received data or 
 * sends the desired text message once per second.
 *
 * @author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "iso9141.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

// Text message to send in the transmitter application mode
#define DEMO_TEXT_MESSAGE           "MIKROE - ISO 9141 click board\r\n\0"

static iso9141_t iso9141;
static log_t logger;

void application_init ( void )
{
    iso9141_cfg_t iso9141_cfg;
    log_cfg_t logger_cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( logger_cfg );
    log_init( &logger, &logger_cfg );
    log_info( &logger, " Application Init " );
    
    // Click initialization.
    iso9141_cfg_setup( &iso9141_cfg );
    ISO9141_MAP_MIKROBUS( iso9141_cfg, MIKROBUS_1 );
    if ( UART_ERROR == iso9141_init( &iso9141, &iso9141_cfg ) ) 
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
    iso9141_generic_write( &iso9141, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms( 1000 ); 
#else
    uint8_t rx_byte = 0;
    if ( 1 == iso9141_generic_read( &iso9141, &rx_byte, 1 ) )
    {
       log_printf( &logger, "%c", rx_byte );
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
