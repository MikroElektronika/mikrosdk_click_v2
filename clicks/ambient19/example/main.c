/*!
 * @file main.c
 * @brief Ambient19 Click example
 *
 * # Description
 * This example demonstrates the use of Ambient 19 click board by measuring 
 * the ambient light level in Lux.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then reads the ambient light level in Lux as well as 
 * the raw proximity data of PS and IR leds and displays the results on the USB UART. 
 * By default, the data ready interrupt triggers upon every ADC cycle which will be 
 * performed every 500ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient19.h"

static ambient19_t ambient19;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient19_cfg_t ambient19_cfg;  /**< Click config object. */

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
    ambient19_cfg_setup( &ambient19_cfg );
    AMBIENT19_MAP_MIKROBUS( ambient19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient19_init( &ambient19, &ambient19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT19_ERROR == ambient19_default_cfg ( &ambient19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( !ambient19_get_int_pin ( &ambient19 ) )
    {
        uint16_t lux, ps_data, ir_data;
        if ( AMBIENT19_OK == ambient19_measure_light_level ( &ambient19, &lux ) )
        {
            log_printf ( &logger, "\r\n Ambient light level [Lux]: %u\r\n", lux );
        }
        if ( AMBIENT19_OK == ambient19_read_raw_proximity ( &ambient19, &ps_data, &ir_data ) )
        {
            log_printf ( &logger, " PS data: %u\r\n", ps_data );
            log_printf ( &logger, " IR data: %u\r\n", ir_data );
        }
        ambient19_clear_interrupts ( &ambient19 );
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
