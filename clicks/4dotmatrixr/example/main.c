/*!
 * \file 
 * \brief c4dotmatrixr Click example
 * 
 * # Description
 * This module has a 5x7 dot matrix, with very closely spaced, bright red pixel elements.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Click driver init and setting mBus pins to appropriate logic levels.
 * 
 * ## Application Task  
 * Text MikroElektronika slides from left to right and then numbers from -20 to 20 are displayed on 4 Dot Matrix click
 *  
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c4dotmatrixr.h"

// ------------------------------------------------------------------ VARIABLES

static c4dotmatrixr_t c4dotmatrixr;
static log_t logger;

static uint8_t text[23] = { ' ',' ',' ','M', 'i', 'k', 'r', 'o', 'E','l','e','k','t','r','o','n','i','k','a',' ',' ',' ',' '};

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c4dotmatrixr_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c4dotmatrixr_cfg_setup( &cfg );
    log_info( &logger, "---- Configuration Setup ----" );
    C4DOTMATRIXR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    log_info( &logger, "---- MAP Setup ----" );
    c4dotmatrixr_init( &c4dotmatrixr, &cfg );
    log_info( &logger, "---- Chip Init ----" );
    c4dotmatrixr_default_cfg ( &c4dotmatrixr );
    log_info( &logger, "---- Chip Configuration ----" );
}

void application_task ( void )
{
    int8_t i;
    
    for ( i = 0; i < 21; i++ )
    {
        c4dot_write_text(  &c4dotmatrixr, text + i );
        Delay_ms( 150 );
    }
        
        // Clear and delay.
    c4dot_clear_display( &c4dotmatrixr );
    Delay_ms( 500 );
        
        // Write some numbers on the display.
    for ( i = -20; i <= 20; i++ )
    {
        c4dot_write_int_dec( &c4dotmatrixr, i );
        Delay_ms( 150 );
    }

    // Clear and delay.
    c4dot_clear_display( &c4dotmatrixr );
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
