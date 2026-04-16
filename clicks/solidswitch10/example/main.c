/*!
 * @file main.c
 * @brief SolidSwitch 10 Click example
 *
 * # Description
 * This example demonstrates the use of the SolidSwitch 10 Click board for
 * controlling a low-side solid-state output channel. The application periodically
 * enables and disables the output, allowing verification of switching
 * behavior through the connected load.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and SolidSwitch 10 Click driver and applies the
 * default device configuration.
 *
 * ## Application Task
 * Toggles the output state by enabling and disabling low-side switch output
 * at fixed time intervals and logs the current action to the serial terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "solidswitch10.h"

#ifndef MIKROBUS_POSITION_SOLIDSWITCH10
    #define MIKROBUS_POSITION_SOLIDSWITCH10 MIKROBUS_1
#endif

static solidswitch10_t solidswitch10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch10_cfg_t solidswitch10_cfg;  /**< Click config object. */

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
    solidswitch10_cfg_setup( &solidswitch10_cfg );
    SOLIDSWITCH10_MAP_MIKROBUS( solidswitch10_cfg, MIKROBUS_POSITION_SOLIDSWITCH10 );
    if ( I2C_MASTER_ERROR == solidswitch10_init( &solidswitch10, &solidswitch10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLIDSWITCH10_ERROR == solidswitch10_default_cfg ( &solidswitch10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Enable OUT\r\n\n" );
    solidswitch10_enable_output ( &solidswitch10 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Disable OUT\r\n\n" );
    solidswitch10_disable_output ( &solidswitch10 );
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
