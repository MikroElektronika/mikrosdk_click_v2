/*!
 * \file 
 * \brief Barometer Click example
 * 
 * # Description
 * This application measures temperature and pressure data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C, set default configuration and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Barometer Click board.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "barometer.h"

// ------------------------------------------------------------------ VARIABLES

static barometer_t barometer;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    barometer_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    barometer_cfg_setup( &cfg );
    BAROMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barometer_init( &barometer, &cfg );

    barometer_default_cfg( &barometer );

    // Check sensor id
    if ( barometer_check_id( &barometer ) != BAROMETER_DEVICE_ID )
    {
        log_printf( &logger, "   ERROR  \r\n " );
    }
    else
    {
        log_printf( &logger, "   Initialization  \r\n" );
    }
        
    log_printf( &logger, "-------------------------------- \r\n" );
    Delay_100ms( );
}

void application_task ( void )
{
    float temperature_c;
    float pressure;

    temperature_c = barometer_get_temperature_c( &barometer );
    Delay_100ms( );

    pressure = barometer_get_pressure( &barometer );
    Delay_100ms( );

    log_printf( &logger, " Temperature : %.2f \r\n", temperature_c );

    log_printf( &logger, " Pressure    : %.2f\r\n", pressure );
    log_printf( &logger, "-------------------------------- \r\n" );

    Delay_1sec( );
    Delay_1sec( );
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
