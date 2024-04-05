/*!
 * @file main.c
 * @brief DHT22 Click Example.
 *
 * # Description
 * This is a example which demonstrates the use of DHT22 Click board by
 * measuring temperature and relative humidity.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the SDA data pin depending on the selected GPIO pin (SDA1/SDA2)
 * and log module.
 *
 * ## Application Task
 * Reads the temperature and humidity from the sensor and 
 * displays the values on the USB UART.
 *
 * @author Mikroe Team
 *
 */


#include "board.h"
#include "log.h"
#include "dht22.h"

static dht22_t dht22;   /**< DHT22 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dht22_cfg_t dht22_cfg;  /**< Click config object. */

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
    dht22_cfg_setup( &dht22_cfg );
    DHT22_MAP_MIKROBUS( dht22_cfg, MIKROBUS_1 );

   if ( DIGITAL_OUT_UNSUPPORTED_PIN == dht22_init( &dht22, &dht22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, "---- Application Init done. ----" );
}

void application_task ( void )
{
    static float temperature = 0;
    static float humidity = 0;
    
    dht22_init_sda_output( &dht22 );
    if ( DHT22_OK == dht22_start_signal( &dht22 ) )
    {
        dht22_init_sda_input( &dht22 );
        if ( DHT22_OK == dht22_check_sensor_response( &dht22 ) )
        {
            if ( DHT22_OK == dht22_get_measurement_data( &dht22, &humidity, &temperature ) )
            {
                log_printf( &logger, " Humidity : %.2f %%\r\n", humidity );
                log_printf( &logger, " Temperature : %.2f degC\r\n", temperature );
                log_printf( &logger, " ---------------------------\r\n" );
                Delay_ms ( 1000 );
            }
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
