/*!
 * \file 
 * \brief C3dHall2 Click example
 * 
 * # Description
 * 
 * This application reads X/Y/Z hall axis and temperature data and converts it to
 * human readable format.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and configuration chip
 * 
 * ## Application Task  
 * Reads X/Y/Z hall axis and Temperature data.
 * All data logs on the USBUART every 3 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c3dhall2.h"

// ------------------------------------------------------------------ VARIABLES

static c3dhall2_t c3dhall2;
static log_t logger;
float xyz_axis[ 3 ];
float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c3dhall2_cfg_setup( &cfg );
    C3DHALL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall2_init( &c3dhall2, &cfg );
    c3dhall2_default_cfg( &c3dhall2 );

}

void application_task ( void )
{
    c3dhall2_get_axis_temp_data( &c3dhall2, &xyz_axis[ 0 ], &temperature );

    log_printf( &logger, " Axis X: %.2f mT\r\n", xyz_axis[ 0 ] );
    log_printf( &logger, " Axis Y: %.2f mT\r\n", xyz_axis[ 1 ] );
    log_printf( &logger, " Axis Z: %.2f mT\r\n", xyz_axis[ 2 ] );

    log_printf( &logger, " Temperature: %.2f C\r\n", temperature );

    Delay_ms( 2000 );
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
