/*!
 * \file 
 * \brief LcdMono Click example
 * 
 * # Description
 * This application sets text on lcd displey.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver initialization - Starting LCD Mono display. Print text to the display by changing font size ...
 * 
 * ## Application Task  
 * Drawing an image to the display every 3 second.
 * 
 * *note:* 
 * - Create Image:
 *     Save the image in resolution of 128x128 px with the extension (monochrome bmp) ...
 *     Upload the image to Image2Lcd program
 *     Set parameters to:
 *            1. Output file type : C array
 *            2. Scan Mode : Horisontal scan
 *            3. Bits Pixel : monochrome
 *            4. Max width and height : 128x128
 *            5. Check only MSB first
 *            6. Check Reverse color and adjust Normal type
 * The image to be generated should contain about 2048 bytes ...
 * Insert the image into the file lcdmono_image.h
 *
 * - Create Font:
 *     Close existing project, open a new VTFT project
 *     Add label and adjust text font
 *     Generate source code
 *     Copy the font from resource.c file to this project in file lcdmono_font.h
 * 
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lcdmono.h"
#include "lcdmono_font.h"
#include "lcdmono_image.h"

// ------------------------------------------------------------------ VARIABLES

static lcdmono_t lcdmono;

static const char demo_text_lcd[ 4 ] = { 'L', 'C', 'D', 0 };
static const char demo_text_mono[ 5 ] = { 'M', 'o', 'n', 'o', 0 };
static const char demo_text_128x128px[ 10 ] = { '1', '2', '8', 'x', '1', '2', '8', 'p', 'x', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    lcdmono_cfg_t cfg;
    lcdmono_text_settings_t tx_set;
    lcdmono_font_t font_cfg;

    //  Click initialization.
    lcdmono_cfg_setup( &cfg );
    LCDMONO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lcdmono_init( &lcdmono, &cfg );

    lcdmono_display_reset( &lcdmono );
    lcdmono_clear( &lcdmono );

    // Background color for all text
    tx_set.bg_color = LCDMONO_COLOR_WHITE;
    // Display text
    font_cfg.this_font = lcdmono_font_tahoma_16;
    lcdmono_set_font( &lcdmono, &font_cfg );

    tx_set.len = 3;
    tx_set.start_cord_x = 25;
    tx_set.start_cord_y = 15;
    lcdmono_draw_text( &lcdmono, demo_text_lcd, &tx_set, LCDMONO_REFRESH_TEXT_BUFFER | 
                                                         LCDMONO_CHECK_NEW_TEXT );

    font_cfg.this_font = lcdmono_font_tahoma_8;
    lcdmono_set_font( &lcdmono, &font_cfg );

    tx_set.len = 4;
    tx_set.start_cord_x = 60;
    tx_set.start_cord_y = 50;
    lcdmono_draw_text( &lcdmono, demo_text_mono, &tx_set, LCDMONO_CHECK_NEW_TEXT );

    tx_set.len = 9;
    tx_set.start_cord_x = 10;
    tx_set.start_cord_y = 80;
    lcdmono_draw_text( &lcdmono, demo_text_128x128px, &tx_set, LCDMONO_REFRESH_DISPLAY_END );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    lcdmono_clear( &lcdmono );
}

void application_task ( void )
{
    lcdmono_draw_frame( &lcdmono, demo_img_mikroe_light );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    lcdmono_draw_frame( &lcdmono, demo_img_mikroe );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    lcdmono_draw_frame( &lcdmono, demo_img_logo_light );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    lcdmono_draw_frame( &lcdmono, demo_img_logo );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
