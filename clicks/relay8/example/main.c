/*!
 * @file main.c
 * @brief Relay 8 Click Example.
 *
 * # Description
 * This example demonstrates the use of Relay 8 Click board by switching
 * the relay output between the on and the off state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Turns the relay on and off using the set and the reset control lines, then
 * turns it on and off again using the toggle control line, and displays the
 * relay state on the USB UART. Each state is held for 2 seconds.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "relay8.h"

#ifndef MIKROBUS_POSITION_RELAY8
    #define MIKROBUS_POSITION_RELAY8 MIKROBUS_1
#endif

static relay8_t relay8;   /**< Relay 8 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    relay8_cfg_t relay8_cfg;  /**< Click config object. */

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
    relay8_cfg_setup( &relay8_cfg );
    RELAY8_MAP_MIKROBUS( relay8_cfg, MIKROBUS_POSITION_RELAY8 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == relay8_init( &relay8, &relay8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    relay8_set_relay ( &relay8 );
    log_printf( &logger, " Relay ON - set\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    relay8_reset_relay ( &relay8 );
    log_printf( &logger, " Relay OFF - reset\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    relay8_toggle_relay ( &relay8 );
    log_printf( &logger, " Relay ON - toggle\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    relay8_toggle_relay ( &relay8 );
    log_printf( &logger, " Relay OFF - toggle\r\n\n" );
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
