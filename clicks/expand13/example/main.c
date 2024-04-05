/*!
 * @file main.c
 * @brief Expand13 Click example
 *
 * # Description
 * This example demonstrates the use of Expand 13 click board, 
 * by writing data to all six ports and then reading back the status of the ports. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the click board.
 *
 * ## Application Task
 * Sets the pins of all ports and then reads and displays their status on the 
 * USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "expand13.h"

static expand13_t expand13;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand13_cfg_t expand13_cfg;  /**< Click config object. */

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
    expand13_cfg_setup( &expand13_cfg );
    EXPAND13_MAP_MIKROBUS( expand13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand13_init( &expand13, &expand13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    expand13_enable_device ( &expand13 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t port_value[ 6 ] = { 0 };
    uint16_t pin_num = 0;
  
    for ( pin_num = EXPAND13_PIN_0_MASK; pin_num <= EXPAND13_PIN_7_MASK; pin_num <<= 1 )
    {
        if ( !expand13_get_int_pin ( &expand13 ) )
        {
            log_printf( &logger, " External input has occurred.\r\n" );
        }
        
        memset ( port_value, pin_num, 6 );
        expand13_write_all_ports( &expand13, port_value );
        
        expand13_read_all_ports( &expand13, port_value );
        for ( uint8_t cnt = EXPAND13_PORT_0; cnt <= EXPAND13_PORT_5; cnt++ )
        {
            log_printf( &logger, " Status port %d : 0x%.2X\r\n", ( uint16_t ) cnt, ( uint16_t ) port_value[ cnt ] );
        }
        log_printf( &logger, "\n" );
        Delay_ms ( 1000 );
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
