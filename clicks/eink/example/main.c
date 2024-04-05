/*!
 * \file 
 * \brief Eink Click example
 * 
 * # Description
 * This application demonstrates the use of eINK click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the click board for 2.00 inch eINK display.
 * After that, if the TEXT mode is supported, shows a desired text messages on the display.
 * 
 * ## Application Task  
 * Draws two demo images to the display with a one-second delay between each drawing.
 *  
 * @note 
 * Due to insuficient RAM memory, only the IMAGE mode is supported with 8-bit PIC microcontrollers.
 * 
 * Here is the procedure for creating an Image or Font arrays:
 * 
 * - Create Image:
 *    Save the image in resolution of 172x72 px with the extension (jpg) ...
 *    Upload the image to Image2Lcd program
 *    Set parameters to:
 *           1. Output file type : C array
 *           2. Scan Mode : Vertical scan
 *           3. Bits Pixel : 4 Color
 *           4. Max Width and Height : 172x72
 *           5. Select only MSB first checkmark
 *           6. Check Reverse color and adjust Normal type
 *    The image to be generated should contain exact 3096 bytes ...
 *    Insert the image into the file eink_display_image.h
 * 
 * - Create Font:
 *    Create a new VisualTFT project
 *    Add label and adjust text font
 *    Generate source code
 *    Copy the font array from resource.c file and paste it to eink200inch_font.h file
 * 
 * *** Changing the LUT table can lead to loss of display performance ....
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "eink.h"
#include "eink200inch_image.h"
#ifndef IMAGE_MODE_ONLY
#include "eink200inch_font.h"
#endif

// ------------------------------------------------------------------ VARIABLES

static eink_t eink;

const uint8_t eink_lut_table[ 90 ] =
{
    0x82, 0x00, 0x00, 0x00, 0xAA, 0x00, 0x00, 0x00,
    0xAA, 0xAA, 0x00, 0x00, 0xAA, 0xAA, 0xAA, 0x00,
    0x55, 0xAA, 0xAA, 0x00, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
    0xAA, 0xAA, 0xAA, 0xAA, 0x15, 0x15, 0x15, 0x15,
    0x05, 0x05, 0x05, 0x05, 0x01, 0x01, 0x01, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x41, 0x45, 0xF1, 0xFF, 0x5F, 0x55, 0x01, 0x00,
    0x00, 0x00

};

uint8_t demo_text[ 5 ] = { 'e', 'I', 'N', 'K' , 0 };
uint8_t demo_text1[ 8 ] = { 'D', 'i', 's', 'p', 'l', 'a', 'y', 0 };
uint8_t demo_text2[ 10 ] = { '2', '.', '0', '0', 'i', 'n', 'c', 'h', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    eink_cfg_t cfg;   
    eink200inch_font_t cfg_font;
    eink_text_set_t text_set;

    //  Click initialization.
    eink_cfg_setup( &cfg );
    EINK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eink_init( &eink, &cfg );

    eink_start_config( &eink );
    eink_set_lut( &eink, eink_lut_table, 90 );
    Delay_ms ( 1000 );

#ifndef IMAGE_MODE_ONLY
    cfg_font.p_font = &guiFont_Tahoma_10_Regular[ 0 ];
    cfg_font.color = EINK_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK_FO_HORIZONTAL;  
    eink_set_font( &eink, &cfg_font );
    
    text_set.n_char = 4;
    text_set.text_x = 10;
    text_set.text_y = 50;
    eink_text( &eink, &demo_text[ 0 ], &text_set );
    text_set.n_char = 7;
    text_set.text_x = 10;
    text_set.text_y = 90;
    eink_text( &eink, &demo_text1[ 0 ], &text_set );
    text_set.n_char = 8;
    text_set.text_x = 10;
    text_set.text_y = 130;
    eink_text( &eink, &demo_text2[ 0 ], &text_set ); 
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
}

void application_task ( void )
{
    eink_display_image ( &eink, demo_image_black );
    Delay_1sec( );
    eink_display_image ( &eink, demo_image_white );
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
