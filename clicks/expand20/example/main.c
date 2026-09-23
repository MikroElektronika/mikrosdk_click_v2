/*!
 * @file main.c
 * @brief Expand 20 Click example
 *
 * # Description
 * This example demonstrates the use of Expand 20 Click board by setting and
 * reading port 0 and port 1 states.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which sets
 * port 0 pins as output and port 1 pins as input.
 *
 * ## Application Task
 * Walks a single high level across all Port 0 output pins, then reads back the
 * state of both Port 0 and Port 1 and displays the results on the USB UART
 * approximately once per second.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "expand20.h"

#ifndef MIKROBUS_POSITION_EXPAND20
    #define MIKROBUS_POSITION_EXPAND20 MIKROBUS_1
#endif

static expand20_t expand20;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand20_cfg_t expand20_cfg;  /**< Click config object. */

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
    expand20_cfg_setup( &expand20_cfg );
    EXPAND20_MAP_MIKROBUS( expand20_cfg, MIKROBUS_POSITION_EXPAND20 );
    if ( I2C_MASTER_ERROR == expand20_init( &expand20, &expand20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND20_ERROR == expand20_default_cfg ( &expand20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t port_0_value = 0;
    uint8_t port_1_value = 0;

    for ( uint16_t pin_num = EXPAND20_PIN_0_MASK; pin_num <= EXPAND20_PIN_7_MASK; pin_num <<= 1 )
    {
        expand20_set_port_value( &expand20, EXPAND20_PORT_0, ( uint8_t ) pin_num );
        
        expand20_read_port_value( &expand20, EXPAND20_PORT_0, &port_0_value );
        expand20_read_port_value( &expand20, EXPAND20_PORT_1, &port_1_value );

        log_printf( &logger, " Port 0 ( output ): 0x%.2X\r\n", ( uint16_t ) port_0_value );
        log_printf( &logger, " Port 1 ( input ) : 0x%.2X\r\n\n", ( uint16_t ) port_1_value );

        Delay_ms( 1000 );
    }
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
