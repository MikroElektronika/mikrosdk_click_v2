/*!
 * @file main.c
 * @brief Battery Source Click Example.
 *
 * # Description
 * This example demonstrates the use of Battery Source Click board, 
 * by changing state of the output.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and disables the output.
 *
 * ## Application Task
 * Enabling output for 5 seconds, then disabling it for 5 seconds.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "batterysource.h"

static batterysource_t batterysource;   /**< Battery Source Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    batterysource_cfg_t batterysource_cfg;  /**< Click config object. */

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
    batterysource_cfg_setup( &batterysource_cfg );
    BATTERYSOURCE_MAP_MIKROBUS( batterysource_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == batterysource_init( &batterysource, &batterysource_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    batterysource_set_output( &batterysource, BATTERYSOURCE_DISABLE_OUTPUT );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Output is enabled \r\n" );
    batterysource_set_output( &batterysource, BATTERYSOURCE_ENABLE_OUTPUT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Output is disabled \r\n" );
    batterysource_set_output( &batterysource, BATTERYSOURCE_DISABLE_OUTPUT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
