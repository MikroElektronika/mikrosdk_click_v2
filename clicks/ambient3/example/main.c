/*!
 * \file 
 * \brief Ambient3 Click example
 * 
 * # Description
 * This application is calibrated XYZ chromatic smart lighting director, 
 * providing the measurement data in digital format over the I2C interface.
 * Initializes I2C module and sets INT pin as INPUT and RST pin as OUTPUT
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver init and reset chip
 * 
 * ## Application Task  
 * Reads the device temperature, daylight at LUX and logs data to USBUART every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ambient3.h"

// ------------------------------------------------------------------ VARIABLES

static ambient3_t ambient3;
static log_t logger;

static uint8_t temperature;
static float data_lux;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ambient3_cfg_setup( &cfg );
    AMBIENT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient3_init( &ambient3, &cfg );
    ambient3_default_cfg( &ambient3 );
}

void application_task ( )
{
    temperature = ambient3_get_device_temperature( &ambient3 );
    log_printf( &logger, " - Device temperature : %d\r\n", temperature );

    data_lux = ambient3_get_data_in_lux( &ambient3 );
    log_printf( &logger, " - Light in LUX : %.2f\r\n", data_lux );
    
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
