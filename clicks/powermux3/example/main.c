/*!
 * @file main.c
 * @brief Power MUX 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Power MUX 3 Click board. It enables automatic 
 * selection between three power sources, selecting the highest voltage as the input source. 
 * The demo toggles the output ON and OFF at regular intervals, allowing observation of
 * the output control functionality.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Power MUX 3 Click driver, then enables the device.
 *
 * ## Application Task
 * Alternates enabling and disabling the output in 5-second intervals while logging the status.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "powermux3.h"

static powermux3_t powermux3;   /**< Power MUX 3 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    powermux3_cfg_t powermux3_cfg;  /**< Click config object. */

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
    powermux3_cfg_setup( &powermux3_cfg );
    POWERMUX3_MAP_MIKROBUS( powermux3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == powermux3_init( &powermux3, &powermux3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    powermux3_enable_device ( &powermux3 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Output enabled\r\n\n" );
    powermux3_enable_output ( &powermux3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Output disabled\r\n\n" );
    powermux3_disable_output ( &powermux3 );
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
