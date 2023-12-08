/*!
 * @file main.c
 * @brief Expand10 Click example
 *
 * # Description
 * This example demonstrates the use of Expand 10 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets the first two ports
 * as output and the third port as input with pull-down enabled.
 *
 * ## Application Task
 * Sets the pins of the first two ports and then reads and displays the status of 
 * all ports on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "expand10.h"

static expand10_t expand10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    expand10_cfg_t expand10_cfg;  /**< Click config object. */

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
    expand10_cfg_setup( &expand10_cfg );
    EXPAND10_MAP_MIKROBUS( expand10_cfg, MIKROBUS_1 );
    err_t init_flag = expand10_init( &expand10, &expand10_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    init_flag = expand10_default_cfg ( &expand10 );
    if ( EXPAND10_ERROR == init_flag ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t port_value = 0;
  
    for ( uint16_t pin_num = EXPAND10_PIN_0_MASK; pin_num <= EXPAND10_PIN_7_MASK; pin_num <<= 1 )
    {
        expand10_set_all_pins_value( &expand10, pin_num );
        
        expand10_read_port_value( &expand10, EXPAND10_PORT_0, &port_value );
        log_printf( &logger, " Status P0 (output): 0x%.2X\r\n", ( uint16_t ) port_value );
        
        expand10_read_port_value( &expand10, EXPAND10_PORT_1, &port_value );
        log_printf( &logger, " Status P1 (output): 0x%.2X\r\n", ( uint16_t ) port_value );
        
        expand10_read_port_value( &expand10, EXPAND10_PORT_2, &port_value );
        log_printf( &logger, " Status P2 (input) : 0x%.2X\r\n\r\n", ( uint16_t ) port_value );
        Delay_ms( 1000 );
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
