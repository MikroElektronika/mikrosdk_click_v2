/*!
 * \file 
 * \brief LedDriver3 Click example
 * 
 * # Description
 * This app changes color and intensity of light.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver initialize.
 * 
 * ## Application Task  
 * Changes color and intensity of light.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "leddriver3.h"

// ------------------------------------------------------------------ VARIABLES

static leddriver3_t leddriver3;
static log_t logger;
static leddriver3_rgb_t rgb;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    leddriver3_cfg_setup( &cfg );
    LEDDRIVER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    if ( LEDDRIVER3_INIT_ERROR == leddriver3_init( &leddriver3, &cfg ) )
    {
        log_info( &logger, "---- Init Error ----\r\n" );
        log_info( &logger, "---- Run program again ----\r\n" );

        for ( ; ; );
    }

    log_info( &logger, "---- Init Done ----\r\n" );
}

void application_task ( void )
{
    rgb.red = 0x40;
    rgb.green = 0x7F;
    rgb.blue = 0x80;

    leddriver3_set_intensity( &leddriver3, LEDDRIVER3_INCREMENT | LEDDRIVER3_INTENSITY_8 );
    leddriver3_set_timer( &leddriver3, LEDDRIVER3_TIMER_8ms | LEDDRIVER3_TIMER_16ms );
    leddriver3_set_color( &leddriver3, LEDDRIVER3_COLOR_RED );
    Delay_ms( 1000 );

    leddriver3_set_intensity( &leddriver3, LEDDRIVER3_CONSTANT | LEDDRIVER3_INTENSITY_16 );
    leddriver3_set_color( &leddriver3, LEDDRIVER3_COLOR_PURPLE );
    Delay_ms( 1000 );
    leddriver3_set_color( &leddriver3, LEDDRIVER3_COLOR_BLUE );
    Delay_ms( 1000 );

    leddriver3_set_rgb_color( &leddriver3, &rgb );
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
