/*!
 * \file 
 * \brief DHT22 Click example
 *
 * # Description
 * It’s a low cost reliable solution that communicates with the target board
 * microcontroller through a single Serial Data Line.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the SDA data pin depending on the selected GPIO pin (SDA1/SDA2)
 * and log module.
 *
 * ## Application Task
 * This is a example which demonstrates the use of DHT22 Click board by
 * measuring temperature and relative humidity.
 *
 * \author Nemanja Medakovic
 *
 */

#include "board.h"
#include "log.h"
#include "dht22.h"

static dht22_t dht22;
static log_t logger;

static void application_display_results ( float temp, float hum )
{
    log_printf( &logger, " Humidity [RH] : %.2f %%\r\n", hum );
    log_printf( &logger, " Temperature [T] : %.2f degC\r\n\n", temp );
    Delay_ms( 1000 );
}

void application_init ( void )
{
    log_cfg_t log_cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
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

    log_info( &logger, "---- Application Init Done. ----" );
    log_info( &logger, "---- Application Running... ----\n" );
}

void application_task ( void )
{
    dht22_init_sda_output( &dht22 );

    if ( dht22_start_signal( &dht22 ) == DHT22_OK )
    {
        dht22_init_sda_input( &dht22 );

        uint8_t resp_stat = DHT22_RESP_NOT_READY;

        if ( dht22_check_sensor_response( &dht22, &resp_stat ) == DHT22_OK )
        {
            if ( resp_stat )
            {
                uint32_t sens_meas = 0;

                if ( dht22_get_sensor_data( &dht22, &sens_meas ) == DHT22_OK )
                {
                    float dht22_temp = dht22_calculate_temperature( &dht22, sens_meas );
                    float dht22_hum = dht22_calculate_humidity( &dht22, sens_meas );

                    application_display_results( dht22_temp, dht22_hum );
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
