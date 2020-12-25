/*!
 * \file 
 * \brief Ambient11 Click example
 * 
 * # Description
 * < The devices resolution depends on settings applied.
 *  User should consult the datasheet and choose resolution value 
 *  that corresponds to the settings applied. >
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * < Initalizes I2C driver, applies low sensitiviti settings
 * ( GAIN = 0, DG = 0, SENS = 1 and IT = 100ms ) and 
 * makes an initial log.>
 * 
 * ## Application Task  
 * < This example shows the capabilities of the Ambient 11 click
 *  by measuring ambiental illumination and displaying calculated value
 * via USART terminal in luxes.>
 * 
 * *note:* 
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ambient11.h"

// ------------------------------------------------------------------ VARIABLES

static ambient11_t ambient11;
static log_t logger;
float lx_val;
float resolution = 0.1024;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient11_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ambient11_cfg_setup( &cfg );
    AMBIENT11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient11_init( &ambient11, &cfg );
    ambient11_default_cfg ( &ambient11 );
}

void application_task ( void )
{
    lx_val = ambient11_calc_illumination( &ambient11, resolution );
    log_printf( &logger, "Illumination : %.2f lx \r\n", lx_val );
    log_printf( &logger, "-------------------------\r\n" );
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
