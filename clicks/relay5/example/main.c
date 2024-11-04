/*!
 * @file main.c
 * @brief Relay 5 Click example
 *
 * # Description
 * This example demonstrates the use of Relay 5 Click board by toggling the relays state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Switches all relays state every 5 seconds and displays the state on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "relay5.h"

static relay5_t relay5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    relay5_cfg_t relay5_cfg;  /**< Click config object. */

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
    relay5_cfg_setup( &relay5_cfg );
    RELAY5_MAP_MIKROBUS( relay5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == relay5_init( &relay5, &relay5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RELAY5_ERROR == relay5_default_cfg ( &relay5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    relay5_set_relay1_open ( &relay5 );
    log_printf( &logger, " Relay 1 set to normally open state\r\n" );
    relay5_set_relay2_close ( &relay5 );
    log_printf( &logger, " Relay 2 set to normally close state\r\n" );
    relay5_set_relay3_open ( &relay5 );
    log_printf( &logger, " Relay 3 set to normally open state\r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    relay5_set_relay1_close ( &relay5 );
    log_printf( &logger, " Relay 1 set to normally close state\r\n" );
    relay5_set_relay2_open ( &relay5 );
    log_printf( &logger, " Relay 2 set to normally open state\r\n" );
    relay5_set_relay3_close ( &relay5 );
    log_printf( &logger, " Relay 3 set to normally close state\r\n\n" );
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
