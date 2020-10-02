/*!
 * \file 
 * \brief DotMatrixR Click example
 * 
 * # Description
 * This demo application show data on display.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuration device
 * 
 * ## Application Task  
 * Display shows 3 different data in span of 1 second
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dotmatrixr.h"

// ------------------------------------------------------------------ VARIABLES

static dotmatrixr_t dotmatrixr;
static log_t logger;

char demo_t1[ 6 ] = "####";
char demo_t2[ 6 ] = "____";
char demo_t3[ 6 ] = "DotR";

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dotmatrixr_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dotmatrixr_cfg_setup( &cfg );
    DOTMATRIXR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dotmatrixr_init( &dotmatrixr, &cfg );

    Delay_ms( 100 );
    dotmatrixr_restart( &dotmatrixr );
    Delay_ms( 500 );
    
    dotmatrixr_set_bl_pin_state( &dotmatrixr, 0 );
    dotmatrixr_set_rs_pin_state( &dotmatrixr, 0 );

    dotmatrixr_ctrl_1( &dotmatrixr, DOTMATRIXR_CTRL_BYTE_1_OSC_PRESCALER_1 |
                       DOTMATRIXR_CTRL_BYTE_1_DOUT_DIN );
    dotmatrixr_ctrl_0( &dotmatrixr, DOTMATRIXR_CTRL_BYTE_0_BRIGHTNESS_30 |
                       DOTMATRIXR_CTRL_BYTE_0_PIXEL_PEAK_CURRENT_9p3mA |
                       DOTMATRIXR_CTRL_BYTE_0_MODE_NORMAL );
}

void application_task ( void )
{
    dotmatrixr_write_ascii( &dotmatrixr, &demo_t1[ 0 ] );
    Delay_ms( 1000 );
    dotmatrixr_write_ascii( &dotmatrixr, &demo_t2[ 0 ] );
    Delay_ms( 1000 );
    dotmatrixr_write_ascii( &dotmatrixr, &demo_t3[ 0 ] );
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
