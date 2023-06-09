/*!
 * @file main.c
 * @brief Power MUX Click Example.
 *
 * # Description
 * This Click features power multiplexer that enables transition between two power supplies, 
 * each operating at 2.8V to 5.5V and delivering up to 2A current depending on the package.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Enables GPIO and starts write log.
 *
 * ## Application Task
 * Changes power inputs every 3 seconds and displays the currently set mode on the USB UART.
 *
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "powermux.h"

static powermux_t powermux;   /**< Power MUX Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;
    powermux_cfg_t powermux_cfg;

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
    powermux_cfg_setup( &powermux_cfg );
    POWERMUX_MAP_MIKROBUS( powermux_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == powermux_init( &powermux, &powermux_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    powermux_default_cfg ( &powermux );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " OUTPUT : IN1\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_1_ON );
    Delay_ms ( 3000 );
    log_printf( &logger, " OUTPUT : IN2\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_2_ON );
    Delay_ms ( 3000 );
    log_printf( &logger, " OUTPUT : OFF\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_OFF );
    Delay_ms ( 3000 );
    log_printf( &logger, " OUTPUT : AUTO\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_AUTO );
    Delay_ms ( 3000 );
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
