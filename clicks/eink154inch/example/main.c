/*!
 * \file 
 * \brief Eink154Inch Click example
 * 
 * # Description
 * This application demonstrates the use of eINK Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the Click board for 1.54 inch eINK display.
 * After that, if the TEXT mode is supported, shows a desired text messages on the display.
 * 
 * ## Application Task  
 * Draws two demo images to the display with a one-second delay between each drawing.
 *  
 * @note 
 * Due to insuficient RAM memory, only the IMAGE mode is supported with 8-bit PIC and AVR microcontrollers.
 * 
 * Here is the procedure for creating an Image or Font arrays:
 * 
 * - Create Image:
 *    Save the image in resolution of 200x200 px with the extension (monochrome bmp) ...
 *    Upload the image to Image2Lcd program
 *    Set parameters to:
 *           1. Output file type : C array
 *           2. Scan Mode : Horizon scan
 *           3. Bits Pixel : monochrome
 *           4. Max Width and Height : 200x200
 *           5. Select only MSB first checkmark
 *           6. Check Reverse color and adjust Normal type
 *    The image to be generated should contain about 5000 bytes ...
 *    Insert the image into the file eink154inch_image.h
 * 
 * - Create Font:
 *    Create a new VisualTFT project
 *    Add label and adjust text font
 *    Generate source code
 *    Copy the font array from resource.c file and paste it to eink154inch_font.h file
 * 
 * *** Changing the LUT table can lead to loss of display performance ....
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "eink154inch.h"
#include "eink154inch_image.h"
#ifndef IMAGE_MODE_ONLY
#include "eink154inch_font.h"
#endif

// ------------------------------------------------------------------ VARIABLES

static eink154inch_t eink154inch;

const uint8_t eink154inch_lut_table[ 30 ] =
{
    0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22,
    0x66, 0x69, 0x69, 0x59, 0x58, 0x99, 0x99, 0x88,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xB4, 0x13, 0x51,
    0x35, 0x51, 0x51, 0x19, 0x01, 0x00
};

uint8_t demo_text[ 5 ] = { 'e', 'I', 'N', 'K' , 0 };
uint8_t demo_text1[ 8 ] = { 'D', 'i', 's', 'p', 'l', 'a', 'y', 0 };
uint8_t demo_text2[ 10 ] = { '1', '.', '5', '4', 'i', 'n', 'c', 'h', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    eink154inch_cfg_t cfg;   
    eink154inch_font_t cfg_font;
    eink154inch_text_set_t text_set;

    //  Click initialization.
    eink154inch_cfg_setup( &cfg );
    EINK154INCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eink154inch_init( &eink154inch, &cfg );

    eink154inch_start_config( &eink154inch );
    eink154inch_set_lut( &eink154inch, eink154inch_lut_table, 30 );
    Delay_ms ( 1000 );
    
#ifndef IMAGE_MODE_ONLY
    cfg_font.p_font = &guiFont_Tahoma_18_Regular[ 0 ];
    cfg_font.color = EINK154INCH_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK154INCH_FO_HORIZONTAL;  
    
    eink154inch_set_font( &eink154inch, &cfg_font );
    text_set.n_char = 4;
    text_set.text_x = 10;
    text_set.text_y = 50;
    eink154inch_text( &eink154inch, &demo_text[ 0 ], &text_set );
    text_set.n_char = 7;
    text_set.text_x = 10;
    text_set.text_y = 90;
    eink154inch_text( &eink154inch, &demo_text1[ 0 ], &text_set );
    text_set.n_char = 8;
    text_set.text_x = 10;
    text_set.text_y = 130;
    eink154inch_text( &eink154inch, &demo_text2[ 0 ], &text_set ); 
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
}

void application_task ( void )
{
    eink154inch_image( &eink154inch, &demoImage_light[ 0 ] );
    Delay_1sec( );
    eink154inch_image( &eink154inch, &demoImage_dark[ 0 ] );
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
