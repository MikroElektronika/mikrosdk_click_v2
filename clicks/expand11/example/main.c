/*!
 * @file main.c
 * @brief Expand 11 Click example
 *
 * # Description
 * This example demonstrates the use of Expand 11 click board by setting and
 * reading the port state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets 
 * the pins P0-P1 as output and P2-P3 as input.
 *
 * ## Application Task
 * Toggles all output pins and then reads the status of the whole port and 
 * displays the results on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "expand11.h"

static expand11_t expand11;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand11_cfg_t expand11_cfg;  /**< Click config object. */

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
    expand11_cfg_setup( &expand11_cfg );
    EXPAND11_MAP_MIKROBUS( expand11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand11_init( &expand11, &expand11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND11_ERROR == expand11_default_cfg ( &expand11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint16_t pin_num = EXPAND11_PIN_0_MASK;
    uint8_t port_value = 0;
    if ( EXPAND11_OK == expand11_set_all_pins_value( &expand11, pin_num ) )
    {
        if ( EXPAND11_OK == expand11_read_port_value( &expand11, &port_value ) )
        {
            log_printf( &logger, " PORT STATUS \r\n" );
            log_printf( &logger, "  P0: %u\r\n", ( uint16_t ) ( port_value & EXPAND11_PIN_0_MASK ) );
            log_printf( &logger, "  P1: %u\r\n", ( uint16_t ) ( ( port_value & EXPAND11_PIN_1_MASK ) >> 1 ) );
            log_printf( &logger, "  P2: %u\r\n", ( uint16_t ) ( ( port_value & EXPAND11_PIN_2_MASK ) >> 2 ) );
            log_printf( &logger, "  P3: %u\r\n\n", ( uint16_t ) ( ( port_value & EXPAND11_PIN_3_MASK ) >> 3 ) );
            pin_num = ( ~pin_num ) & EXPAND11_ALL_PINS_MASK;
        }
    }
    Delay_ms( 1000 );
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
