/*!
 * @file main.c
 * @brief Expand12 Click example
 *
 * # Description
 * This example demonstrates the use of Expand 12 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets 
 * the first three ports (pins 4-23) as output and the fourth port (pins 24-31) as input with pull-ups.
 *
 * ## Application Task
 * Sets the pins of the first three ports and then reads the status of all pins and 
 * displays the result on the USB UART approximately every 100 miliseconds.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "expand12.h"

static expand12_t expand12;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand12_cfg_t expand12_cfg;  /**< Click config object. */

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
    expand12_cfg_setup( &expand12_cfg );
    EXPAND12_MAP_MIKROBUS( expand12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand12_init( &expand12, &expand12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND12_ERROR == expand12_default_cfg ( &expand12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t port_value = 0;
    static uint32_t pins_status = 0;
    
    expand12_set_port_value( &expand12, EXPAND12_PORT_4_7, EXPAND12_ALL_PINS, port_value );
    expand12_set_port_value( &expand12, EXPAND12_PORT_8_15, EXPAND12_ALL_PINS, port_value );
    expand12_set_port_value( &expand12, EXPAND12_PORT_16_23, EXPAND12_ALL_PINS, port_value++ );
        
    expand12_read_all_pins_value( &expand12, &pins_status );
    log_printf( &logger, " Pins status (32-bit) : 0x%.8LX\r\n\n", pins_status );
    Delay_ms( 100 );
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
