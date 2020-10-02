/*!
 * \file 
 * \brief 8x8 Click example
 * 
 * # Description
 * This demo example shows a drawing of Image, new create string and character on the screen.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Shows one byte, then scrolls the string and image, every 1 sec.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c8x8.h"

// ------------------------------------------------------------------ VARIABLES

static c8x8_t c8x8;
static log_t logger;

uint8_t demo_string[ 11 ] = { ' ', '-', 'M', 'i', 'k', 'r', 'o', 'E', '-', ' ', 0 };
uint8_t demo_img_on [ 8 ] = { 0x08, 0x1c, 0x36, 0x22, 0x08, 0x1c, 0x36, 0x22 };
uint8_t demo_img_off[ 8 ] = { 0xf7, 0xe3, 0xc9, 0xdd, 0xf7, 0xe3, 0xc9, 0xdd };
char demo_char = 'A';

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c8x8_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c8x8_cfg_setup( &cfg );
    C8X8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c8x8_init( &c8x8, &cfg );

    log_info( &logger, "---- Default matrix config ----" );
    c8x8_default_cfg( &c8x8 );
    Delay_1sec( );
}

void application_task ( void )
{
    //  Task implementation.

    log_info( &logger, "> Display Character ..." );
    c8x8_display_byte( &c8x8, demo_char );
    Delay_ms( 1000 );

    log_info( &logger, "> Display String ..." );
    c8x8_display_string( &c8x8, &demo_string[ 0 ] );
    Delay_ms( 1000 );

    log_info( &logger, "> Display Image ON ..." );
    c8x8_display_image( &c8x8, &demo_img_on[ 0 ] );
    Delay_ms( 500 );

    log_info( &logger, "> Display Image OFF ..." );
    c8x8_display_image( &c8x8, &demo_img_off[ 0 ] );
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
