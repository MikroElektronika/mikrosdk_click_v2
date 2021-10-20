/*!
 * \file 
 * \brief DHT22 Click example
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
 * \author Nemanja Medakovic
 *
 */

#include "board.h"
#include "log.h"
#include "dht22.h"

static dht22_t dht22;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    dht22_cfg_t dht22_cfg;

    //  Click initialization.

    dht22_cfg_setup( &dht22_cfg );
    DHT22_MAP_MIKROBUS( dht22_cfg, MIKROBUS_1 );

    if ( dht22_init( &dht22, &dht22_cfg ) == DHT22_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init done. ----" );
}

void application_task ( void )
{
    uint8_t resp_stat = DHT22_RESP_NOT_READY;
    uint32_t sens_meas = 0;
    float dht22_temp = 0;
    float dht22_hum = 0;
    
    dht22_init_sda_output( &dht22 );
    
    if ( dht22_start_signal( &dht22 ) == DHT22_OK )
    {
        dht22_init_sda_input( &dht22 );
        
        if ( dht22_check_sensor_response( &dht22, &resp_stat ) == DHT22_OK )
        {
            if ( resp_stat == DHT22_RESP_READY )
            {
                if ( dht22_get_sensor_data( &dht22, &sens_meas ) == DHT22_OK )
                {
                    dht22_temp = dht22_calculate_temperature( &dht22, sens_meas );
                    dht22_hum = dht22_calculate_humidity( &dht22, sens_meas );

                    log_printf( &logger, " Humidity : %.2f %%\r\n", dht22_hum );
                    log_printf( &logger, " Temperature : %.2f degC\r\n", dht22_temp );
                    log_printf( &logger, " ---------------------------\r\n", dht22_temp );
                    Delay_ms( 1000 );
                }
                
            }
        }
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
