/*!
 * \file 
 * \brief Ut7Seg Click example
 * 
 * # Description
 * The demo application shows basic usage of the UT 7 SEG display.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Draws numbers from 0 to 99 on the screen.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ut7seg.h"

// ------------------------------------------------------------------ VARIABLES

static ut7seg_t ut7seg;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ut7seg_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ut7seg_cfg_setup( &cfg );
    UT7SEG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ut7seg_init( &ut7seg, &cfg );

    ut7seg_default_cfg( &ut7seg );
}

void application_task ( void )
{
    uint8_t cnt;

    //  Task implementation.

    log_info( &logger, "---- Number counter ----" );

    for ( cnt = 0; cnt < 100; cnt++ )
    {
        utl7segr_display_number( &ut7seg, cnt, UT7SEG_DOT_LEFT_RIGHT );
        Delay_ms( 500 );
    }
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
