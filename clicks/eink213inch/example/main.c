/*!
 * \file 
 * \brief eInk213Inch Click example
 * 
 * # Description
 * This application write a text and draw an image on eINK display.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver initialization - basic procedure for starting e-ink display.
 * Start the display settings and write LUT table.
 * Print text to the display by changing font size ...
 * 
 * ## Application Task  
 * Drawing an image to the display every 1 second.
 * 
 * *note:* 
 * - Create Image:
 *    Save the image in resolution of 128x250 px with the extension (monochrome bmp) ...
 *    Upload the image to Image2Lcd program
 *    Set parameters to:
 *           1. Output file type : C array
 *           2. Scan Mode : Vertical scan
 *           3. Bits Pixel : monochrome
 *           4. Max width and height : 250x128
 *           5. Check only MSB first
 *           6. Check Reverse color and adjust Mirror Left-Right
 *    The image to be generated should contain about 4000 bytes ...
 *    Insert the image into the file eINK_213_display_image.h  
 *
 * - Create Font:
 *    Close existing project, open a new VTFT project
 *    Add label and adjust text font
 *    Generate source code
 *    Copy the font from resource.c file to this project in file eINK_213_display_font.h  
 *
 * - Create new functions:
 *    At the beginning of your new function, set eink213_setMemoryArea and eink213_setMemoryPointer
 *    Create new pixels and create a new image buffer
 *    Send command to write to RAM (_EINK213_CMD_WRITE_RAM)
 *    Forward 4000 data bytes ..
 *        1. By using the eink213_sendData function (sending one by one byte)
 *    Finally call the eink213_updateDisplay function to see the image on the display  
 *
 * *** Changing the LUT table can lead to loss of display performance ....
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "eink_213inch.h"
#include "eINK_213_display_font.h"
#include "eINK_213_display_image.h"

// ------------------------------------------------------------------ VARIABLES

static eink_213inch_t eink_213inch;
static log_t logger;
char demo_text[ 5 ] = { 'e', 'I', 'N', 'K', 0 };
char demo_text1[ 8 ] = { 'D', 'i', 's', 'p', 'l', 'a', 'y', 0 };
char demo_text2[ 10 ] = { '2', '.', '1', '3', 'i', 'n', 'c', 'h', 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

const uint8_t EINK213_BIG_LUT_TABLE[70]=
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
    log_cfg_t log_cfg;
    eink_213inch_cfg_t cfg;
    eink_213inch_font_t cfg_font;
    eink_213inch_set_text_t set_text;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    eink_213inch_cfg_setup( &cfg );
    EINK213INCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eink_213inch_init( &eink_213inch, &cfg );

    eink_213_start_config( &eink_213inch );
    eink_213_set_lut( &eink_213inch, &EINK213_BIG_LUT_TABLE[ 0 ], 70 );

    cfg_font.p_font = &guiFont_Tahoma_18_Regular[ 0 ]; 
    cfg_font.color = EINK213_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK213_FO_HORIZONTAL;  
    eink_213_set_font( &eink_213inch, &cfg_font );

    set_text.n_char = 4;
    set_text.text_x = 7;
    set_text.text_y = 50;
    eink_213_text( &eink_213inch, &demo_text[ 0 ], &set_text );
    
    cfg_font.p_font = &guiFont_Tahoma_10_Regular[ 0 ]; 
    cfg_font.color = EINK213_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK213_FO_HORIZONTAL; 
    eink_213_set_font( &eink_213inch, &cfg_font );

    set_text.n_char = 7;
    set_text.text_x = 12;
    set_text.text_y = 90;
    eink_213_text( &eink_213inch, &demo_text1[ 0 ], &set_text );
    
    cfg_font.p_font = &guiFont_Tahoma_8_Regular[ 0 ]; 
    cfg_font.color = EINK213_SCREEN_COLOR_WHITE;
    cfg_font.orientation = EINK213_FO_HORIZONTAL; 
    eink_213_set_font( &eink_213inch, &cfg_font );

    set_text.n_char = 9;
    set_text.text_x = 12;
    set_text.text_y = 120;
    eink_213_text( &eink_213inch, &demo_text2[ 0 ], &set_text );
    
    Delay_ms( 1000 );
}

void application_task ( void )
{
    eink_213_display_image( &eink_213inch, &demoImage_light[ 0 ] );
    Delay_1sec( );
    eink_213_display_image( &eink_213inch, &demoImage_dark[ 0 ] );
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
