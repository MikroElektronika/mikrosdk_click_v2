/*!
 * @file main.c
 * @brief Ambient17 Click example
 *
 * # Description
 * This example demonstrates the use of Ambient 17 Click board by measuring 
 * the ambient light level in Lux.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then reads the ambient light level in Lux
 * and displays the results on the USB UART. By default, the data ready interrupt triggers 
 * upon every ADC cycle which will be performed every 200ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient17.h"

static ambient17_t ambient17;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient17_cfg_t ambient17_cfg;  /**< Click config object. */

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
    ambient17_cfg_setup( &ambient17_cfg );
    AMBIENT17_MAP_MIKROBUS( ambient17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient17_init( &ambient17, &ambient17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT17_ERROR == ambient17_default_cfg ( &ambient17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( !ambient17_get_int_pin ( &ambient17 ) )
    {
        uint16_t lux;
        if ( AMBIENT17_OK == ambient17_measure_light_level ( &ambient17, &lux ) )
        {
            log_printf ( &logger, " Ambient light level [Lux]: %u\r\n\n", lux );
        }
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
