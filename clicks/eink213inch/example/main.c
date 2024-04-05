/*!
 * \file 
 * \brief eInk213Inch Click example
 * 
 * # Description
 * This application demonstrates the use of eINK click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the click board for 2.13 inch eINK display.
 * After that, if the TEXT mode is supported, shows a desired text messages on the display.
 * 
 * ## Application Task  
 * Draws four demo images to the display with a one-second delay between each drawing.
 * 
 * @note
 * Due to insuficient RAM memory, only the IMAGE mode is supported with 8-bit PIC and AVR microcontrollers.
 * 
 * - Create Image:
 *    Save the image in resolution of 128x250 px with the extension (monochrome bmp) ...
 *    Upload the image to Image2Lcd program
 *    Set parameters to:
 *           1. Output file type : C array
 *           2. Scan Mode : Vertical scan
 *           3. Bits Pixel : monochrome
 *           4. Max Width and Height : 250x128
 *           5. Select only MSB first checkmark
 *           6. Check Reverse color and adjust Mirror Left-Right
 *    The image to be generated should contain about 4000 bytes ...
 *    Insert the image into the file eink213inch_image.h  
 *
 * - Create Font:
 *    Create a new VisualTFT project
 *    Add label and adjust text font
 *    Generate source code
 *    Copy the font from resource.c file and paste it to eink213inch_font.h file
 *
 * *** Changing the LUT table can lead to loss of display performance ....
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "eink213inch.h"
#include "eink213inch_image.h"
#ifndef IMAGE_MODE_ONLY
#include "eink213inch_font.h"
#endif

// ------------------------------------------------------------------ VARIABLES

static eink213inch_t eink213inch;

uint8_t demo_text[ 5 ] = { 'e', 'I', 'N', 'K', 0 };
uint8_t demo_text1[ 8 ] = { 'D', 'i', 's', 'p', 'l', 'a', 'y', 0 };
uint8_t demo_text2[ 10 ] = { '2', '.', '1', '3', 'i', 'n', 'c', 'h', 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

const uint8_t eink213inch_lut_table[70]=
{
    0xA0,0x90,0x50,0x00,0x00,0x00,0x00,
    0x50,0x90,0xA0,0x00,0x00,0x00,0x00,
    0xA0,0x90,0x50,0x00,0x00,0x00,0x00,
    0x50,0x90,0xA0,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x0F,0x0F,0x0F,0x0F,0x02,0x10,0x10,
    0x0A,0x0A,0x03,0x08,0x08,0x09,0x43,
    0x07,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    eink213inch_cfg_t cfg;
    eink213inch_font_t cfg_font;
    eink213inch_set_text_t set_text;

    //  Click initialization.
    eink213inch_cfg_setup( &cfg );
    EINK213INCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eink213inch_init( &eink213inch, &cfg );

    eink213inch_start_config( &eink213inch );
    eink213inch_set_lut( &eink213inch, &eink213inch_lut_table[ 0 ], 70 );
    Delay_ms ( 1000 );

#ifndef IMAGE_MODE_ONLY
    cfg_font.p_font = &guiFont_Tahoma_18_Regular[ 0 ]; 
    cfg_font.color = EINK213INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK213INCH_FO_HORIZONTAL;  
    eink213inch_set_font( &eink213inch, &cfg_font );

    set_text.n_char = 4;
    set_text.text_x = 5;
    set_text.text_y = 50;
    eink213inch_text( &eink213inch, &demo_text[ 0 ], &set_text );
    
    cfg_font.p_font = &guiFont_Tahoma_10_Regular[ 0 ]; 
    cfg_font.color = EINK213INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK213INCH_FO_HORIZONTAL; 
    eink213inch_set_font( &eink213inch, &cfg_font );

    set_text.n_char = 7;
    set_text.text_x = 5;
    set_text.text_y = 90;
    eink213inch_text( &eink213inch, &demo_text1[ 0 ], &set_text );
    
    cfg_font.p_font = &guiFont_Tahoma_8_Regular[ 0 ]; 
    cfg_font.color = EINK213INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK213INCH_FO_HORIZONTAL; 
    eink213inch_set_font( &eink213inch, &cfg_font );

    set_text.n_char = 9;
    set_text.text_x = 5;
    set_text.text_y = 120;
    eink213inch_text( &eink213inch, &demo_text2[ 0 ], &set_text );
#endif
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    eink213inch_display_image( &eink213inch, &demoImage_light[ 0 ] );
    Delay_1sec( );
    eink213inch_display_image( &eink213inch, &demoImage_dark[ 0 ] );
    Delay_1sec( );
    eink213inch_display_image( &eink213inch, &demoImage_light_180[ 0 ] );
    Delay_1sec( );
    eink213inch_display_image( &eink213inch, &demoImage_dark_180[ 0 ] );
    Delay_1sec( );
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
