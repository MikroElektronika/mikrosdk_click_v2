/*!
 * \file 
 * \brief TempHum8 Click example
 * 
 * # Description
 * This demo-app shows the temperature measurement procedure using Temp&Hum 8 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects. 
 * Setting the click in the default configuration to start the measurement, 
 * and before that call function software_reset().
 * 
 * ## Application Task  
 * Reads ambient temperature data and Relative Huminidy data, 
 * this data logs to USBUART every 1500ms.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum8.h"

// ------------------------------------------------------------------ VARIABLES

static temphum8_t temphum8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum8_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum8_cfg_setup( &cfg );
    TEMPHUM8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum8_init( &temphum8, &cfg );

    temphum8_software_reset( &temphum8 );
    temphum8_default_cfg( &temphum8 ); 
}

void application_task ( void )
{
    float temperature;
    float humidity;

    //  Task implementation.
    
    log_printf( &logger, "\r\n ---- Ambient data ----\r\n" );

    temperature = temphum8_get_temperature_data( &temphum8, TEMPHUM8_TEMPERATURE_IN_CELSIUS );
    log_printf( &logger, "** Temperature: %.2f °C \r\n", temperature );
    
    humidity = temphum8_get_humidity_data( &temphum8 );
    log_printf( &logger, "** Humidity: %.2f %%RH \r\n", humidity );

    Delay_ms( 1500 );
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
