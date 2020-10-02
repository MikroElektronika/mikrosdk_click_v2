/*!
 * \file 
 * \brief Pressure11 Click example
 * 
 * # Description
 * This sensor offers many benefits, including low power consumption,
 *  high resolution of the pressure data, embedded thermal compensation,
 *  FIFO buffer with several operating modes, temperature measurement, etc.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI driver and checks chip ID
 * 
 * ## Application Task  
 * Reads Pressure and Temperature values and displays it on UART LOG
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure11.h"

// ------------------------------------------------------------------ VARIABLES

static pressure11_t pressure11;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure11_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pressure11_cfg_setup( &cfg );
    PRESSURE11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure11_init( &pressure11, &cfg );
}

void application_task ( void )
{
    float temperature;
    float pressure;
        
    temperature = pressure11_get_temperature( &pressure11 );
    log_printf( &logger, "Temperature: %.2f \r\n", temperature );
    log_printf( &logger, " C" );
 
    pressure = pressure11_get_pressure( &pressure11 );
    log_printf( &logger, "Pressure:  %.2f \r\n", pressure );
    log_printf( &logger, "   hPa (mBar)" );
 
    Delay_ms( 500 );
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
