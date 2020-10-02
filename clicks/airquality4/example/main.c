/*!
 * \file 
 * \brief AirQuality4 Click example
 * 
 * # Description
 * This application measures the amount of substances in air and air quality and logs the results.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * nitializes click driver and gets ID data.
 * 
 * ## Application Task  
 * Performs measurements of air concentracion for H2, EthOH, CO2 and TVOC data.
 * Results of measurement shows on USBUART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "airquality4.h"

// ------------------------------------------------------------------ VARIABLES

static airquality4_t airquality4;
static log_t logger;
static uint8_t buffer_data[ 6 ];
static uint16_t data_buffer[ 2 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    airquality4_cfg_setup( &cfg );
    AIRQUALITY4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality4_init( &airquality4, &cfg );
    airquality4_default_cfg( &airquality4 );
}

void application_task ( void )
{
    air_quality4_get_h2_and_ethon( &airquality4, data_buffer);

    log_printf( &logger, "H2 value is: %u\n", data_buffer[ 0 ] );
    log_printf( &logger, "EthOH value is:  %u\n", data_buffer[ 1 ] );

    air_quality4_set_baseline( &airquality4 );
    air_quality4_get_co2_and_tvoc( &airquality4, &data_buffer[ 0 ] );
    
    log_printf( &logger, "CO2 value is: %u\n", data_buffer[ 0 ] );
    log_printf( &logger, "TVOC value is: %u\n\n", data_buffer[ 1 ] );

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
