/*!
 * \file 
 * \brief TempHum5 Click example
 * 
 * # Description
 * This application measures temperature and humidity.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device init
 * 
 * ## Application Task  
 * Reads Temperature and Humidity data and this data logs to USBUART every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum5.h"

// ------------------------------------------------------------------ VARIABLES

static temphum5_t temphum5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum5_cfg_setup( &cfg );
    TEMPHUM5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum5_init( &temphum5, &cfg );
}

void application_task ( )
{
    float temperature;
    float humidity;
    
    temphum5_start_measurement( &temphum5 );

    temperature = temphum5_get_temperature( &temphum5, TEMPHUM5_TEMP_DATA_IN_CELSIUS );
    log_printf( &logger, "Temperature: %.2f C \r\n ", temperature );
     
    humidity = temphum5_get_humidity ( &temphum5 );
    log_printf( &logger, "Humidity: %.0f RH \r\n ", humidity );
    
    log_printf( &logger, "------------------------ \r\n " );
    Delay_ms( 1000 );
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
