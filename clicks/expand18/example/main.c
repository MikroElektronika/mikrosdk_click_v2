/*!
 * @file main.c
 * @brief Expand 18 Click example
 *
 * # Description
 * This example demonstrates the use of Expand 18 Click board by setting and reading 
 * the ports state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which sets 
 * the port 0 as output and the port 1 as input with pull-down enabled.
 *
 * ## Application Task
 * Sets the pins of the port 0 and then reads the status of both ports and 
 * displays the results on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "expand18.h"

static expand18_t expand18;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand18_cfg_t expand18_cfg;  /**< Click config object. */

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
    expand18_cfg_setup( &expand18_cfg );
    EXPAND18_MAP_MIKROBUS( expand18_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == expand18_init( &expand18, &expand18_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND18_ERROR == expand18_default_cfg ( &expand18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t port_value = 0;
    for ( uint16_t pin_num = EXPAND18_PIN_0_MASK; pin_num <= EXPAND18_PIN_7_MASK; pin_num <<= 1 )
    {
        expand18_set_all_pins_value( &expand18, pin_num );
        
        expand18_read_port_value( &expand18, EXPAND18_PORT_0, &port_value );
        log_printf( &logger, " Status port 0 (output): 0x%.2X\r\n", ( uint16_t ) port_value );
        
        expand18_read_port_value( &expand18, EXPAND18_PORT_1, &port_value );
        log_printf( &logger, " Status port 1 (input) : 0x%.2X\r\n\n", ( uint16_t ) port_value );
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
