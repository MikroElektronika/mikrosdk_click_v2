/*!
 * @file main.c
 * @brief Expand 19 Click example
 *
 * # Description
 * This example demonstrates the use of Expand 19 Click board by setting and
 * reading the port state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which sets 
 * the pins 0-3 as output and others as input with pull-up enabled.
 *
 * ## Application Task
 * Sets the output pins and then reads the status of all pins and 
 * displays the results on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "expand19.h"

static expand19_t expand19;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand19_cfg_t expand19_cfg;  /**< Click config object. */

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
    expand19_cfg_setup( &expand19_cfg );
    EXPAND19_MAP_MIKROBUS( expand19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand19_init( &expand19, &expand19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND19_ERROR == expand19_default_cfg ( &expand19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t port_value = 0;
    for ( uint16_t pin_num = EXPAND19_PIN_0_MASK; pin_num <= EXPAND19_PIN_3_MASK; pin_num <<= 1 )
    {
        expand19_set_all_pins_value( &expand19, pin_num );
        
        expand19_read_port_value( &expand19, &port_value );
        log_printf( &logger, " Port status: 0x%.2X\r\n", ( uint16_t ) port_value );
        
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
