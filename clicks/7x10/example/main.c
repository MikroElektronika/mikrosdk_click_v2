/*!
 * \file
 * \brief 7x10 Click example
 *
 * # Description
 * This demo example shows a drawing of pixels, characters and a number on the screen.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configuring the click board.
 *
 * ## Application Task
 * Draws characters, numbers, and pixels to the display.
 *
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "c7x10.h"

// ------------------------------------------------------------------ VARIABLES

static c7x10_t c7x10;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    c7x10_cfg_t cfg;

    //  Click initialization.

    c7x10_cfg_setup( &cfg );
    C7X10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c7x10_init( &c7x10, &cfg );
}

void application_task ( void )
{
    c7x10_pixel_t pixel;
    uint8_t cnt;
    uint8_t cnt_x;
    uint8_t cnt_y;
    
    // CHAR PROCEDURE
    for ( cnt = 'A'; cnt < 'Z'; cnt+=2 )
    {
        c7x10_draw_char( &c7x10, cnt, C7X10_DISPLAY_LEFT, C7X10_DISPLAY_DELAY_50MS );
        c7x10_draw_char( &c7x10, cnt + 1, C7X10_DISPLAY_RIGHT |
                                          C7X10_DISPLAY_REFRESH,
                                          C7X10_DISPLAY_DELAY_50MS );
        Delay_ms( 1000 );
    }

    // COUNTER PROCEDURE
    for ( cnt = 0; cnt < 15; cnt++ )
    {
        c7x10_draw_number( &c7x10, cnt, C7X10_DISPLAY_DELAY_50MS );
        Delay_ms( 500 );
    }
    
    // PIXELS PROCEDURE
    for ( cnt_x = 0; cnt_x <= 7; cnt_x++ )
    {
        for ( cnt_y = 0; cnt_y <= 10; cnt_y++ )
        {
            pixel.cord_x = cnt_x;
            pixel.cord_y = cnt_y;
            c7x10_draw_pixel( &c7x10, &pixel, C7X10_DISPLAY_PIXEL_STORAGE,
                                              C7X10_DISPLAY_DELAY_20MS );

            pixel.cord_x = cnt_x;
            pixel.cord_y = cnt_y + 1;
            c7x10_draw_pixel( &c7x10, &pixel, C7X10_DISPLAY_PIXEL_REFRESH,
                                              C7X10_DISPLAY_DELAY_20MS );
        }
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
