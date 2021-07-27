/*!
 * \file 
 * \brief Eink290Inch Click example
 * 
 * # Description
 * This application demonstrates the use of eINK click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the click board for 2.90 inch eINK display.
 * After that, if the TEXT mode is supported, shows a desired text messages on the display.
 * 
 * ## Application Task  
 * Draws four demo images to the display with a one-second delay between each drawing.
 *  
 * @note 
 * Due to insuficient RAM memory, only the IMAGE mode is supported with 8-bit PIC microcontrollers.
 * 
 * - Create Image:
 *    Save the image in resolution of 128x296 px with the extension (monochrome bmp) ...
 *    Upload the image to Image2Lcd program
 *    Set parameters to:
 *           1. Output file type : C array
 *           2. Scan Mode : Horizon scan
 *           3. Bits Pixel : monochrome
 *           4. Max width and height : 128x296
 *           5. Select only MSB first checkmark
 *           6. Check Reverse color and adjust Normal type
 *    The image to be generated should contain about 5000 bytes ...
 *    Insert the image into the file eINK_290_display_image.h
 * 
 * - Create Font:
 *    Create a new VisualTFT project
 *    Add label and adjust text font
 *    Generate source code
 *    Copy the font array from resource.c file and paste it to eINK_290_display_font.h file
 * 
 * *** Changing the LUT table can lead to loss of display performance ....
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "eink_290inch.h"
#include "eINK_290_display_image.h"
#include "eINK_290_display_font.h"

// ------------------------------------------------------------------ VARIABLES

static eink_290inch_t eink_290inch;

char demo_text[ 5 ] = { 'e', 'I', 'N', 'K' , 0 };
char demo_text1[ 8 ] = { 'D', 'i', 's', 'p', 'l', 'a', 'y', 0 };
char demo_text2[ 10 ] = { '2', '.', '9', '0', 'i', 'n', 'c', 'h', 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

const uint8_t EINK290_LUT_TABLE_1[70]=
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
    eink_290inch_cfg_t cfg;
    eink_290inch_font_t cfg_font;
    eink_290inch_set_text_t text_set;

    //  Click initialization.

    eink_290inch_cfg_setup( &cfg );
    EINK290INCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eink_290inch_init( &eink_290inch, &cfg );

    eink_290_start_config( &eink_290inch );
    eink_290_set_lut( &eink_290inch, EINK290_LUT_TABLE_1, 70 );
    Delay_ms( 1000 );
    
#ifndef IMAGE_MODE_ONLY
    cfg_font.p_font = &guiFont_Tahoma_18_Regular[ 0 ];
    cfg_font.color = EINK290_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK290_FO_HORIZONTAL;  
    eink_290_set_font( &eink_290inch, &cfg_font );
    text_set.n_char = 4;
    text_set.text_x = 5;
    text_set.text_y = 50;
    eink_290_text( &eink_290inch, &demo_text[ 0 ], &text_set );
    Delay_ms( 1000 );
    
    cfg_font.p_font = &guiFont_Tahoma_10_Regular[ 0 ];
    cfg_font.color = EINK290_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK290_FO_HORIZONTAL; 
    eink_290_set_font( &eink_290inch, &cfg_font );
    text_set.n_char = 7;
    text_set.text_x = 5;
    text_set.text_y = 90;
    eink_290_text( &eink_290inch, &demo_text1[ 0 ], &text_set );
    Delay_ms( 1000 );
    
    cfg_font.p_font = &guiFont_Tahoma_8_Regular[ 0 ];
    cfg_font.color = EINK290_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK290_FO_HORIZONTAL; 
    eink_290_set_font( &eink_290inch, &cfg_font );
    text_set.n_char = 9;
    text_set.text_x = 5;
    text_set.text_y = 120;
    eink_290_text( &eink_290inch, &demo_text2[ 0 ], &text_set ); 
    Delay_ms( 1000 );
#endif
}

void application_task ( void )
{
    eink_290_display_image( &eink_290inch, &demoImage_light[ 0 ] );
    Delay_1sec( );
    eink_290_display_image( &eink_290inch, &demoImage_dark[ 0 ] );
    Delay_1sec( );
    eink_290_display_image( &eink_290inch, &demoImage_light_180[ 0 ] );
    Delay_1sec( );
    eink_290_display_image( &eink_290inch, &demoImage_dark_180[ 0 ] );
    Delay_1sec( );
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
