/*!
 * @file main.c
 * @brief RS Transceiver Click example
 *
 * # Description
 * This example reads and processes data from RS Transceiver Click board™.
 * The library also includes a function for selecting the desired operating mode, 
 * enabling/disabling the receiver or driver and data writing or reading.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C and UART module and log UART.
 * After driver initialization, default settings turn on the device.
 *
 * ## Application Task
 * This example demonstrates the use of the RS Transceiver Click board™.
 * The app shows the device configured in loopback mode,
 * sends a "MikroE" message, reads the received data and parses it.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rstransceiver.h"

#define DEMO_MESSAGE "\r\nMikroE\r\n"
#define PROCESS_BUFFER_SIZE 20

static rstransceiver_t rstransceiver;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rstransceiver_cfg_t rstransceiver_cfg;  /**< Click config object. */

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
    rstransceiver_cfg_setup( &rstransceiver_cfg );
    RSTRANSCEIVER_MAP_MIKROBUS( rstransceiver_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rstransceiver_init( &rstransceiver, &rstransceiver_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( RSTRANSCEIVER_ERROR == rstransceiver_default_cfg ( &rstransceiver ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    if ( 0 < rstransceiver_generic_write( &rstransceiver, DEMO_MESSAGE, strlen( DEMO_MESSAGE ) ) )
    {
        if ( 0 < rstransceiver_generic_read( &rstransceiver, app_buf, strlen( DEMO_MESSAGE ) ) )
        {
            log_printf( &logger, "%s", app_buf );
            memset( app_buf, 0, PROCESS_BUFFER_SIZE );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
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
