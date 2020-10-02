/*!
 * \file 
 * \brief DHT22 Click example
 * 
 * # Description
 * It’s a low cost reliable solution that communicates with the target board microcontroller through a single Serial Data Line.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of DHT22 Click board.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dht22.h"

// ------------------------------------------------------------------ VARIABLES

static dht22_t dht22;
static log_t logger;
static dht22_cfg_t cfg;

static uint16_t humidity;
static uint16_t temperature;
static uint32_t sensor_data;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void dht22_display_temp_hum ( )
{
    log_printf( &logger, " Humidity   %d", humidity / 10 );
    
    log_printf( &logger, ".%d", humidity % 10 );
    log_printf( &logger, " %% \r\n"  );

    log_printf( &logger, " Temperature: %d", temperature / 10 );
    
    log_printf( &logger, ".%d", temperature % 10 );
    log_printf( &logger, " C\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    dht22_cfg_setup( &cfg );
    DHT22_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dht22_init( &dht22, &cfg );
}

void application_task ( void )
{
    cs_output( &dht22, &cfg );

    dht22_start_signal( &dht22 );

    
    cs_input( &dht22, &cfg );

    if ( dht22_check_sensor_response( &dht22 ) )
    {
        sensor_data = dht22_get_sensor_data( &dht22 );

        if ( sensor_data != 0 )
        {
            temperature = dht22_calculate_temperature( &dht22, sensor_data );

            humidity = dht22_calculate_humidity( &dht22, sensor_data );

            dht22_display_temp_hum( );
        }
    }
    Delay_1sec( );
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
