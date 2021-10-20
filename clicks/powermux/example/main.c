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
 * Waits for user input in order to change input mode of the Power MUX Click. 
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
    powermux_cfg_t cfg;

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
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == powermux_init( &powermux, &powermux_cfg ) ) {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    powermux_default_cfg ( &powermux );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n " );
    log_printf( &logger, "      Select mode:           \r\n " );
    log_printf( &logger, "-----------------------------\r\n " );
    log_printf( &logger, " 1. Input from channel 1.    \r\n " );
    log_printf( &logger, " 2. Input from channel 2.    \r\n " );
    log_printf( &logger, " 3. Input OFF.               \r\n " );
    log_printf( &logger, " 3. Auto mode.               \r\n " );
    log_printf( &logger, "-----------------------------\r\n " );
}

void application_task ( void ) 
{
    char uart_char;
    if ( log_read( &logger, &uart_char, 1 ) ) {
        switch ( uart_char ) {
            case '1' : {
                log_printf( &logger, " Output mode : Input channel 1 \r\n " );
                powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_1_ON );
                log_printf( &logger, "-----------------------------\r\n " );
                break;
            }
            case '2' : {
                log_printf( &logger, " Output mode : Input channel 2 \r\n " );
                powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_2_ON );
                log_printf( &logger, "-----------------------------\r\n " );
                break;
            }
            case '3' : {
                log_printf( &logger, " Output mode : Input channels OFF \r\n " );
                powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_OFF );
                log_printf( &logger, "-----------------------------\r\n " );
                break;
            }
            case '4' : {
                log_printf( &logger, " Output mode : AUTO \r\n " );
                powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_AUTO );
                log_printf( &logger, "-----------------------------\r\n " );
                break;
            }
            default : {
                log_printf( &logger, "      Select mode: \r\n " );
                log_printf( &logger, "-----------------------------\r\n " );
                log_printf( &logger, " 1. Input from channel 1. \r\n " );
                log_printf( &logger, " 2. Input from channel 2. \r\n " );
                log_printf( &logger, " 3. Input OFF. \r\n " );
                log_printf( &logger, " 3. Auto mode. \r\n " );
                log_printf( &logger, "-----------------------------\r\n " );
                break;
            }
        }
    }
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
