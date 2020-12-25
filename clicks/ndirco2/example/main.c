/*!
 * \file 
 * \brief NDIRCO2 Click example
 * 
 * # Description
 * This application measures absolute CO2 concetration.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver and performs driver reset and determines
 * number of averaging measurements.
 * 
 * ## Application Task  
 * Reads CO2 concentration data in ppm unit after each completed measurement.
 * One measurement is finished after 300 ms, and period between two measurements is 2 seconds.
 * Results of measurements logs on USBUART.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ndirco2.h"

// ------------------------------------------------------------------ VARIABLES

static ndirco2_t ndirco2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ndirco2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ndirco2_cfg_setup( &cfg );
    NDIRCO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ndirco2_init( &ndirco2, &cfg );

    Delay_ms( 300 );

    ndirco2_reset( &ndirco2 );
    ndirco2_write_register( &ndirco2, NDIRCO2_AVERAGING_COUNT_REG, 0x03 );
    ndirco2_set_mode( &ndirco2, NDIRCO2_CONTINUOUS_OP_MODE );
    log_printf( &logger, "NDIR CO2 is initialized \r\n" );
    Delay_ms( 200 );
}

void application_task ( )
{
    uint16_t co2_data;

    ndirco2_read_co2( &ndirco2, NDIRCO2_CHECK_EACH_MEASURE, &co2_data );
    log_printf( &logger, "CO2 concentration is: %d ppm \r\n", co2_data );
    Delay_ms(1000);
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
