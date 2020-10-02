/*!
 * \file 
 * \brief Thermo4 Click example
 * 
 * # Description
 * This demo example returns temperature values in three different format.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver and makes an initial log.
 * 
 * ## Application Task  
 * Returns temperature values from the sensor.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo4.h"

// ------------------------------------------------------------------ VARIABLES

static thermo4_t thermo4;
static log_t logger;
static float temp_in_celsius;
static float temp_in_faren;
static float temp_in_kelvin;
static char txt [ 50 ];
static uint16_t inter_temp_data;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void log_display( float value )
{
    inter_temp_data = ( uint16_t ) value;

    log_printf(&logger, "%s .", txt);

    inter_temp_data = ( uint16_t ) ( value * 100.0 );

    log_printf(&logger, "%s", txt);
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    
    //  Click initialization.
    
    thermo4_cfg_setup( &cfg );
    THERMO4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo4_init( &thermo4, &cfg );
    log_info( &logger, "---- Application Init ----" );
}

void application_task ( void )
{
    temp_in_celsius = thermo4_read_temperature_c( &thermo4 );
    temp_in_faren = thermo4_read_temperature_f( &thermo4 );
    temp_in_kelvin = thermo4_read_temperature_k( &thermo4 );
    
    log_printf( &logger, " Temperature celsius : %f C\r\n ", temp_in_celsius );
    log_printf( &logger, " Temperature farenheit : %f F\r\n ", temp_in_faren );
    log_printf( &logger, " Temperature kelvin : %f K\r\n ", temp_in_kelvin );

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
