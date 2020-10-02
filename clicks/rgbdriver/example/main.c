/*!
 * \file 
 * \brief RgbDriver Click example
 * 
 * # Description
 * This app sets the brightness over rgb value.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver initialize.
 * 
 * ## Application Task  
 * Sets the brightness over rgb value,
 * Red value sets from 0x60 to 0x7F,
 * Green value sets from 0x80 to 0x9F and
 * Blue value sets from 0x40 to 0x5F.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rgbdriver.h"

// ------------------------------------------------------------------ VARIABLES

static rgbdriver_t rgbdriver;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rgbdriver_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rgbdriver_cfg_setup( &cfg );
    RGBDRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rgbdriver_init( &rgbdriver, &cfg );
}

void application_task ( void )
{
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_RED );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_YELLOW );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_BLUE );
    Delay_1sec( );
    rgbdriver_set_rgb_color( &rgbdriver, 0x40, 0x9F, 0x60 );
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
