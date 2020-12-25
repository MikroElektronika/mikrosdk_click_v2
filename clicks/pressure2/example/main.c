/*!
 * \file 
 * \brief Pressure2 Click example
 * 
 * # Description
 * This application measures pressure in range from 0 to 14 bars (with a resolution of up to 0.2 mbars), 
 * but because of the stainless steel cap enclosure, the sensor can withstand up to 30 bars of pressure.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and chip init.
 * 
 * ## Application Task  
 * Reads sensor and logs to USBUART pressure and temperature every second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure2.h"

// ------------------------------------------------------------------ VARIABLES

static pressure2_t pressure2;
static log_t logger;

static float pressure_p;
static float pressure_t;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure2_cfg_t pressure2_cfg;
    float pressure_res;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pressure2_cfg_setup( &pressure2_cfg );
    PRESSURE2_MAP_MIKROBUS( pressure2_cfg, MIKROBUS_1 );
    pressure2_init( &pressure2, &pressure2_cfg );
    pressure2_default_cfg ( &pressure2 );
}

void application_task ( void )
{
    pressure2_read_sensor( &pressure2, &pressure_p, &pressure_t );
    
    log_printf( &logger,"Pressure: %.2f\r\n", pressure_p );
    log_printf( &logger,"Temperature: %.2f\r\n", pressure_t );

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
