/*!
 * \file 
 * \brief Cap Extend 3 Click example
 * 
 * # Description
 * This application features four capacitive sensor pads, that can sense touch through a variety of different materials.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize GPIO Driver
 * 
 * ## Application Task  
 * In depending witch button will be touched the usb uart
 * will show number of button witch is touched.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "capextend3.h"

// ------------------------------------------------------------------ VARIABLES

static capextend3_t capextend3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    capextend3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    capextend3_cfg_setup( &cfg );
    CAPEXTEND3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    capextend3_init( &capextend3, &cfg );
}

void application_task ( void )
{
    uint8_t touch_0;
    uint8_t touch_1;
    uint8_t touch_3;
    uint8_t touch_4;

    touch_0 = capextend3_touch_0( &capextend3 );
    touch_1 = capextend3_touch_1( &capextend3 );
    touch_3 = capextend3_touch_3( &capextend3 );
    touch_4 = capextend3_touch_4( &capextend3 );

    if ( touch_0 == 0 )
    {
       log_printf( &logger, "Touch 0 \r\n" ); 
    }
    if ( touch_1 == 0 )
    {
       log_printf( &logger, "Touch 1 \r\n" ); 
    }
    if ( touch_3 == 0 )
    {
       log_printf( &logger, "Touch 3 \r\n" ); 
    }
    if ( touch_4 == 0 )
    {
       log_printf( &logger, "Touch 4 \r\n" ); 
    }
    Delay_ms( 100 );
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
