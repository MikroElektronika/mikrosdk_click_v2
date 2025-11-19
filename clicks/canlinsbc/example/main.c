/*!
 * @file main.c
 * @brief CAN-LIN SBC Click example
 *
 * # Description
 * This example demonstrates the use of an CAN-LIN SBC Click board by showing
 * the communication between the two Click boards.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and performs the Click default configuration.
 *
 * ## Application Task
 * Depending on the selected application mode, it reads all the received data or 
 * sends the desired message once per second.
 *
 * @note
 * Ensure the two Click boards are connected properly using an RS232 cable and 
 * a 12V external power supply is provided to the VEXT pin.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "canlinsbc.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

#define DEMO_TEXT_MESSAGE   "MIKROE - CAN-LIN SBC Click board\r\n"

static canlinsbc_t canlinsbc;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    canlinsbc_cfg_t canlinsbc_cfg;  /**< Click config object. */

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
    canlinsbc_cfg_setup( &canlinsbc_cfg );
    CANLINSBC_MAP_MIKROBUS( canlinsbc_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == canlinsbc_init( &canlinsbc, &canlinsbc_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CANLINSBC_ERROR == canlinsbc_default_cfg ( &canlinsbc ) )
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
    canlinsbc_generic_write( &canlinsbc, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms( 1000 );
#else
    uint8_t rx_data = 0;
    if ( canlinsbc_generic_read( &canlinsbc, &rx_data, 1 ) > 0 )
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
