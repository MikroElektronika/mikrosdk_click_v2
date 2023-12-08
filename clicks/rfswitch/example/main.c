/*!
 * @file main.c
 * @brief RF Switch Click Example.
 *
 * # Description
 * This is an example that demonstrates the use of the RF Switch Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enable's - GPIO, also write log and powers on device.
 *
 * ## Application Task
 * Waiting for valid user input and executes functions based on set of valid commands.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "rfswitch.h"

static rfswitch_t rfswitch;   /**< RF Switch Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rfswitch_cfg_t rfswitch_cfg;  /**< Click config object. */

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
    rfswitch_cfg_setup( &rfswitch_cfg );
    RFSWITCH_MAP_MIKROBUS( rfswitch_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == rfswitch_init( &rfswitch, &rfswitch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "   Powering device on   \r\n" );
    rfswitch_power_on( &rfswitch );
    Delay_ms( 100 );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "   Select option to     \r\n" );
    log_printf( &logger, "    select channel      \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, " 1. Channel 1 selected  \r\n" );
    log_printf( &logger, " 2. Channel 2 selected  \r\n" );
    log_printf( &logger, " 3. Switching channel   \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}

void application_task ( void ) 
{
    uint8_t tx_buf;
    if ( log_read( &logger, &tx_buf, 1 ) ) {
        switch ( tx_buf ) {
            case '1' : {
                rfswitch_select_channel( &rfswitch, RFSWITCH_SELECT_CHANNEL_1 );
                log_printf( &logger, " Switching to RF port 1 \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                break;
            }
            case '2' : {
                rfswitch_select_channel( &rfswitch, RFSWITCH_SELECT_CHANNEL_2 );
                log_printf( &logger, " Switching to RF port 2 \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                break;
            }
            case '3' : {
                rfswitch_switch_channel( &rfswitch );
                log_printf( &logger, "   Switching RF port    \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                break;
            }
            default : {
                log_printf( &logger, "   Select option to     \r\n" );
                log_printf( &logger, "    select channel      \r\n" );
                log_printf( &logger, "------------------------\r\n" );
                log_printf( &logger, " 1. Channel 1 selected  \r\n" );
                log_printf( &logger, " 2. Channel 2 selected  \r\n" );
                log_printf( &logger, " 3. Switching channel   \r\n" );
                log_printf( &logger, "------------------------\r\n" );
            }
        }
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
