/*!
 * @file main.c
 * @brief DIGI Isolator 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of an DIGI Isolator 3 Click board by showing
 * the communication between the two Click board configured as a receiver and transmitter.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and displays the selected application mode.
 *
 * ## Application Task
 * Depending on the selected mode, it reads all the received data or sends the desired
 * message every 2 seconds.
 *
 * @note
 * Make sure to provide a power supply voltage to the isolated VIN connector in a range
 * from 2.25V to 5.5V.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "digiisolator3.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

#define DEMO_TEXT_MESSAGE   "MIKROE - DIGI Isolator 3 Click board\r\n"

static digiisolator3_t digiisolator3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiisolator3_cfg_t digiisolator3_cfg;  /**< Click config object. */

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
    digiisolator3_cfg_setup( &digiisolator3_cfg );
    DIGIISOLATOR3_MAP_MIKROBUS( digiisolator3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == digiisolator3_init( &digiisolator3, &digiisolator3_cfg ) ) 
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
    digiisolator3_generic_write( &digiisolator3, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms( 1000 );
    Delay_ms( 1000 );
#else
    uint8_t rx_data = 0;
    if ( digiisolator3_generic_read( &digiisolator3, &rx_data, 1 ) > 0 )
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
