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
 * Insert the image into the file Click_LCD_Mono_image.h
 *
 * - Create Font:
 *     Close existing project, open a new VTFT project
 *     Add label and adjust text font
 *     Generate source code
 *     Copy the font from resource.c file to this project in file Click_LCD_Mono_font.h
 * 
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lcdmono.h"

// Resources
#include "click_lcd_mono_image.h"
#include "click_lcd_mono_font.h"

// ------------------------------------------------------------------ VARIABLES

static lcdmono_t lcdmono;
static log_t logger;

static const char demo_text_lcd[ 4 ] = { 'L', 'C', 'D', 0 };
static const char demo_text_mono[ 5 ] = { 'M', 'o', 'n', 'o', 0 };
static const char demo_text_128x128px[ 10 ] = { '1', '2', '8', 'x', '1', '2', '8', 'p', 'x', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lcdmono_cfg_t cfg;
    lcdmono_text_settings_t tx_set;
    lcdmono_font_t font_cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init... ----" );

    //  Click initialization.

    lcdmono_cfg_setup( &cfg );
    LCDMONO_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    if ( lcdmono_init( &lcdmono, &cfg ) == LCDMONO_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );
    log_info( &logger, "---- Application Running... ----\n" );

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
    tx_set.text_color = LCDMONO_COLOR_BLACK;
    lcdmono_draw_text( &lcdmono, demo_text_lcd, &tx_set, LCDMONO_REFRESH_TEXT_BUFFER | 
                                                         LCDMONO_CHECK_NEW_TEXT );

    font_cfg.this_font = lcdmono_font_tahoma_8;
    lcdmono_set_font( &lcdmono, &font_cfg );

    tx_set.len = 4;
    tx_set.start_cord_x = 60;
    tx_set.start_cord_y = 50;
    tx_set.text_color = LCDMONO_COLOR_BLACK;
    lcdmono_draw_text( &lcdmono, demo_text_mono, &tx_set, LCDMONO_CHECK_NEW_TEXT );

    tx_set.len = 9;
    tx_set.start_cord_x = 10;
    tx_set.start_cord_y = 80;
    tx_set.text_color = LCDMONO_COLOR_BLACK;
    lcdmono_draw_text( &lcdmono, demo_text_128x128px, &tx_set, LCDMONO_REFRESH_DISPLAY_END );

    Delay_ms( 5000 );
    lcdmono_clear( &lcdmono );
}

void application_task ( void )
{
    lcdmono_draw_frame( &lcdmono, demo_img_mikroe_light );
    Delay_ms( 3000 );
    lcdmono_draw_frame( &lcdmono, demo_img_mikroe );
    Delay_ms( 3000 );
    lcdmono_draw_frame( &lcdmono, demo_img_logo_light );
    Delay_ms( 3000 );
    lcdmono_draw_frame( &lcdmono, demo_img_logo );
    Delay_ms( 3000 );
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
