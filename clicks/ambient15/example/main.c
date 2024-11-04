/*!
 * @file main.c
 * @brief Ambient15 Click example
 *
 * # Description
 * This example demonstrates the use of Ambient 15 Click board by measuring 
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
#include "ambient15.h"

static ambient15_t ambient15;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient15_cfg_t ambient15_cfg;  /**< Click config object. */

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
    ambient15_cfg_setup( &ambient15_cfg );
    AMBIENT15_MAP_MIKROBUS( ambient15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient15_init( &ambient15, &ambient15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT15_ERROR == ambient15_default_cfg ( &ambient15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( !ambient15_get_int_pin ( &ambient15 ) )
    {
        uint16_t lux;
        if ( AMBIENT15_OK == ambient15_measure_light_level ( &ambient15, &lux ) )
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
