/*!
 * @file main.c
 * @brief Relay 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of Relay 4 Click board by toggling the relays state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Switches the relays 1 and 2 state every 5 seconds and displays the state on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "relay4.h"

static relay4_t relay4;   /**< Relay 4 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    relay4_cfg_t relay4_cfg;  /**< Click config object. */

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
    relay4_cfg_setup( &relay4_cfg );
    RELAY4_MAP_MIKROBUS( relay4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == relay4_init( &relay4, &relay4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    relay4_set_relay1_open ( &relay4 );
    log_printf( &logger, " Relay 1 set to normally open state\r\n" );
    relay4_set_relay2_close ( &relay4 );
    log_printf( &logger, " Relay 2 set to normally close state\r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    relay4_set_relay1_close ( &relay4 );
    log_printf( &logger, " Relay 1 set to normally close state\r\n" );
    relay4_set_relay2_open ( &relay4 );
    log_printf( &logger, " Relay 2 set to normally open state\r\n\n" );
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
