/*!
 * \file 
 * \brief 16x9 Click example
 * 
 * # Description
 * Demo application is used to shows basic controls 16x9 click
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Set basic images and characters to be drawn on the screen.
 * 
 * ## Application Task  
 * Display character, image and rectangle every 1 second.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c16x9.h"

// ------------------------------------------------------------------ VARIABLES

static c16x9_t c16x9;
static log_t logger;

c16x9_image_t image_on;
c16x9_image_t image_off;
c16x9_char_t  data_char;
c16x9_rectangle_t rectangle;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c16x9_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c16x9_cfg_setup( &cfg );
    C16X9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c16x9_init( &c16x9, &cfg );

    // Image ON

    image_on.buf[ 0 ] = 0x0000;
    image_on.buf[ 1 ] = 0xC630;
    image_on.buf[ 2 ] = 0x6318;
    image_on.buf[ 3 ] = 0x318C;
    image_on.buf[ 4 ] = 0x18C6;
    image_on.buf[ 5 ] = 0x318C;
    image_on.buf[ 6 ] = 0x6318;
    image_on.buf[ 7 ] = 0xC630;
    image_on.buf[ 8 ] = 0x0000;

    image_on.frame = C16X9_FRAME_1;
    image_on.pwm = 250;

    // Image OFF

    image_off.buf[ 0 ] = 0xFFFF;
    image_off.buf[ 1 ] = 0x39CF;
    image_off.buf[ 2 ] = 0x9CE7;
    image_off.buf[ 3 ] = 0xCE73;
    image_off.buf[ 4 ] = 0xE739;
    image_off.buf[ 5 ] = 0xCE73;
    image_off.buf[ 6 ] = 0x9CE7;
    image_off.buf[ 7 ] = 0x39CF;
    image_off.buf[ 8 ] = 0xFFFF;

    image_off.frame = C16X9_FRAME_1;
    image_off.pwm = 250;

    // Char

    data_char.character = 'G';
    data_char.frame = C16X9_FRAME_1;
    data_char.pwm = 250;

    // Rectangle

    rectangle.x = 1;
    rectangle.y = 4;
    rectangle.width = 6;
    rectangle.height = 4;
    rectangle.frame = C16X9_FRAME_1;
    rectangle.pwm = 250;
}

void application_task ( void )
{
    //  Task implementation.

    c16x9_display_refresh( &c16x9 );
    c16x9_display_byte( &c16x9, &data_char );
    Delay_ms( 2000 );

    c16x9_display_refresh( &c16x9 );
    c16x9_display_image( &c16x9, &image_on );
    Delay_ms( 2000 );

    c16x9_display_refresh( &c16x9 );
    c16x9_display_image( &c16x9, &image_off );
    Delay_ms( 2000 );

    c16x9_display_refresh( &c16x9 );
    c16x9_draw_rectangle( &c16x9, &rectangle );
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
