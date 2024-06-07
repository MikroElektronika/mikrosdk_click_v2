/*!
 * @file main.c
 * @brief Relay 6 Click example
 *
 * # Description
 * This example demonstrates the use of Relay 6 click board by toggling the relays state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Switches all relays state every second and displays the state on the USB UART.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "relay6.h"

static relay6_t relay6;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    relay6_cfg_t relay6_cfg;  /**< Click config object. */

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
    relay6_cfg_setup( &relay6_cfg );
    RELAY6_MAP_MIKROBUS( relay6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == relay6_init( &relay6, &relay6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RELAY6_ERROR == relay6_default_cfg ( &relay6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t relay_data;
    relay_data = RELAY6_RELAY1_PIN;

    log_printf( &logger, " Turning on only Relay 1 \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = \r\n" );
    relay6_set_relay( &relay6, relay_data, ~relay_data );
    relay_data <<= 1;
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning on only Relay 2 \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = \r\n" );
    relay6_set_relay( &relay6, relay_data, ~relay_data );
    relay_data <<= 1;
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning on only Relay 3 \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = \r\n" );
    relay6_set_relay( &relay6, relay_data, ~relay_data );
    relay_data <<= 1;
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning on only Relay 4 \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = \r\n" );
    relay6_set_relay( &relay6, relay_data, ~relay_data );
    relay_data <<= 1;
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
