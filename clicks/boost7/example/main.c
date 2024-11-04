/*!
 * @file main.c
 * @brief Boost 7 Click Example.
 *
 * # Description
 * This example demonstrates the use of Boost 7 Click board by controlling
 * the V- and V+ outputs state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Toggles the V- and V+ outputs state every 5 seconds and displays their state
 * on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "boost7.h"

static boost7_t boost7;   /**< Boost 7 Click driver object. */
static log_t logger;      /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost7_cfg_t boost7_cfg;  /**< Click config object. */

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
    boost7_cfg_setup( &boost7_cfg );
    BOOST7_MAP_MIKROBUS( boost7_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == boost7_init( &boost7, &boost7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " OUT1 (V-) : ENABLED\r\n" );
    log_printf( &logger, " OUT2 (V+) : DISABLED\r\n\n" );
    boost7_enable_out1 ( &boost7 );
    boost7_disable_out2 ( &boost7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " OUT1 (V-) : DISABLED\r\n" );
    log_printf( &logger, " OUT2 (V+) : ENABLED\r\n\n" );
    boost7_disable_out1 ( &boost7 );
    boost7_enable_out2 ( &boost7 );
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
