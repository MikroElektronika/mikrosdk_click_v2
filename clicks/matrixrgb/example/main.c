/*!
 * \file 
 * \brief MatrixRGB Click example
 * 
 * # Description
 * This application is used for powering 16x32 RGB LED matrices.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, reset device and initializes
 * firmware depend on pattern used alongside with fonts
 * 
 * ## Application Task  
 * Test of panel brightnes, draws red cross on
 * the panel using pixel write function, writes text on panel using
 * write text function and finaly displays image on the panel.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "matrixrgb.h"
#include "matrixrgb_fonts.h"
#include "matrixrgb_images.h"

// ------------------------------------------------------------------ VARIABLES

static matrixrgb_t matrixrgb;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    matrixrgb_cfg_t cfg;
    matrixrgb_font_t font_cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    matrixrgb_cfg_setup( &cfg );
    MATRIXRGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    matrixrgb_init( &matrixrgb, &cfg );

    matrixrgb_device_reset( &matrixrgb );

    matrixrgb_pattern_settings ( &matrixrgb, MATRIXRGB_PATTERN_1_MAP_5MM, 1000 );
    matrixrgb_set_power( &matrixrgb, 1 );
    Delay_ms( 1000 );
    
    font_cfg.p_font       = Arial9x9;
    font_cfg.color        = 0xFFFF;
    font_cfg.orientation  = MATRIXRGB_FONT_HORIZONTAL;
    
    matrixrgb_set_font ( &matrixrgb, &font_cfg );
    
    matrixrgb_fill_screen( &matrixrgb, 0xFFFF );
    Delay_ms( 1000 );
}

void application_task ( )
{
    uint16_t test;

    // Brightness Test
    for ( test = 5; test < 50; test++ )
    {
        matrixrgb_set_brightness( &matrixrgb, test );
        Delay_ms( 50 );
    }

    for ( test = 50; test > 5; test-- )
    {
        matrixrgb_set_brightness( &matrixrgb, test );
        Delay_ms( 50 );
    }

    // Pixel Write Test
    matrixrgb_fill_screen( &matrixrgb, 0x0000 );
    for ( test = 0; test < 32; test++ )
    {
        matrixrgb_write_pixel( &matrixrgb, test, test, 0xF100 );
        Delay_ms( 100 );
    }
    for ( test = 32; test > 0; test-- )
    {
        matrixrgb_write_pixel( &matrixrgb, 31 - test, test, 0xF100 );
        Delay_ms( 100 );
    }
    Delay_ms( 2000 );
    

    //Text Write Test
    matrixrgb_fill_screen( &matrixrgb, 0x0000 );
    matrixrgb_write_text( &matrixrgb, "RGB", 6, 5 );
    matrixrgb_write_text( &matrixrgb, "Demo", 4, 20 );
    Delay_ms( 5000 );
    
    // Image Test
    matrixrgb_draw_image( &matrixrgb, mikroe_logo_32x32_bmp );
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
