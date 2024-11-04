/*!
 * @file main.c
 * @brief Light 2 Click example
 *
 * # Description
 * This example demonstrates the use of Light 2 Click board by measuring 
 * the ambient light level in Lux.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the ADC voltage and then calculates the illuminance from it.
 * The calculated value of illuminance in lux is being displayed on the USB UART approximately once per second. 
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "light2.h"

static light2_t light2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light2_cfg_t light2_cfg;  /**< Click config object. */

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
    light2_cfg_setup( &light2_cfg );
    LIGHT2_MAP_MIKROBUS( light2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == light2_init( &light2, &light2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT2_ERROR == light2_default_cfg ( &light2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float lux_data = 0;

    light2_get_light_data( &light2, &lux_data );
    log_printf( &logger, " LUX data: %.2f LUX \r\n", lux_data );

    Delay_ms ( 1000 );
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
