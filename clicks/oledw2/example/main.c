/*!
 * @file main.c
 * @brief OLED W 2 Click example
 *
 * # Description
 * This example demonstrates the use of the OLED W 2 Click board by showing
 * images, writing text in different fonts and display rotation, adjusting
 * display contrast, and performing horizontal and diagonal scrolling operations.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and OLED W 2 Click driver and performs default 
 * device configuration.
 *
 * ## Application Task
 * Demonstrates drawing images, rotating the display, text rendering with 
 * various fonts, contrast fading, and several scroll modes.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "oledw2.h"
#include "oledw2_resources.h"

#ifndef MIKROBUS_POSITION_OLEDW2
    #define MIKROBUS_POSITION_OLEDW2 MIKROBUS_1
#endif

static oledw2_t oledw2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    oledw2_cfg_t oledw2_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    oledw2_cfg_setup( &oledw2_cfg );
    OLEDW2_MAP_MIKROBUS( oledw2_cfg, MIKROBUS_POSITION_OLEDW2 );
    if ( SPI_MASTER_ERROR == oledw2_init( &oledw2, &oledw2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( OLEDW2_ERROR == oledw2_default_cfg ( &oledw2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf( &logger, " Drawing MIKROE logo with rotation and invert\r\n\n" );
    oledw2_clear_screen( &oledw2 );
    oledw2_set_rotation( &oledw2, OLEDW2_ROTATION_180 );
    oledw2_draw_picture( &oledw2, oledw2_img_mikroe );
    Delay_ms ( 1000 );
    oledw2_set_rotation( &oledw2, OLEDW2_ROTATION_0 );
    oledw2_draw_picture( &oledw2, oledw2_img_mikroe );
    Delay_ms ( 1000 );
    oledw2_write_cmd( &oledw2, OLEDW2_CMD_SET_INVERT_DISPLAY );
    Delay_ms ( 500 );
    oledw2_write_cmd( &oledw2, OLEDW2_CMD_SET_NORMAL_DISPLAY );
    Delay_ms ( 500 );
    oledw2_write_cmd( &oledw2, OLEDW2_CMD_SET_INVERT_DISPLAY );
    Delay_ms ( 500 );
    oledw2_write_cmd( &oledw2, OLEDW2_CMD_SET_NORMAL_DISPLAY );
    Delay_ms ( 500 );

    log_printf( &logger, " Writing text with contrast change\r\n\n" );
    oledw2_clear_screen( &oledw2 );
    oledw2_set_font( &oledw2, OLEDW2_FONT_6X8 );
    oledw2_set_rotation( &oledw2, OLEDW2_ROTATION_0 );
    oledw2_write_string( &oledw2, 0, 0, "        MIKROE       " );
    oledw2_write_string( &oledw2, 1, 0, "    OLED W 2 Click   " );
    oledw2_write_string( &oledw2, 2, 0, "     with SSD1306    " );
    oledw2_write_string( &oledw2, 3, 0, "       ontroller     " );
    for ( int16_t contrast = OLEDW2_CONTRAST_MAX; contrast >= OLEDW2_CONTRAST_MIN; contrast-- ) 
    {
        oledw2_set_contrast( &oledw2, contrast );
        Delay_ms ( 10 );
    }
    for ( int16_t contrast = OLEDW2_CONTRAST_MIN; contrast <= OLEDW2_CONTRAST_MAX; contrast++ ) 
    {
        oledw2_set_contrast( &oledw2, contrast );
        Delay_ms ( 10 );
    }
    oledw2_set_contrast( &oledw2, OLEDW2_CONTRAST_DEFAULT );

    log_printf( &logger, " Scrolling\r\n\n" );
    oledw2_scroll_left( &oledw2, OLEDW2_POS_PAGE_MIN, OLEDW2_POS_PAGE_MAX, OLEDW2_SCROLL_FRAMES_5 );
    Delay_ms ( 1000 );
    oledw2_stop_scroll( &oledw2 );

    oledw2_scroll_right( &oledw2, OLEDW2_POS_PAGE_MIN, OLEDW2_POS_PAGE_MAX, OLEDW2_SCROLL_FRAMES_5 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    oledw2_stop_scroll( &oledw2 );
    
    oledw2_scroll_left( &oledw2, OLEDW2_POS_PAGE_MIN, OLEDW2_POS_PAGE_MAX, OLEDW2_SCROLL_FRAMES_5 );
    Delay_ms ( 1000 );
    oledw2_stop_scroll( &oledw2 );
    
    oledw2_scroll_diag_left( &oledw2, OLEDW2_POS_PAGE_MIN, OLEDW2_POS_PAGE_MAX, 
                             OLEDW2_SCROLL_FRAMES_5, OLEDW2_SCROLL_VERT_OFFSET_MIN );
    Delay_ms ( 1000 );
    oledw2_stop_scroll( &oledw2 );
    
    oledw2_scroll_diag_right( &oledw2, OLEDW2_POS_PAGE_MIN, OLEDW2_POS_PAGE_MAX, 
                              OLEDW2_SCROLL_FRAMES_5, OLEDW2_SCROLL_VERT_OFFSET_MIN );
    Delay_ms ( 1000 );
    oledw2_stop_scroll( &oledw2 );

    log_printf( &logger, " Changing text font and rotation\r\n\n" );
    oledw2_clear_screen( &oledw2 );
    oledw2_set_rotation( &oledw2, OLEDW2_ROTATION_180 );
    oledw2_set_font( &oledw2, OLEDW2_FONT_8X16 );
    oledw2_write_string( &oledw2, 0, 0, "8x16 font size" );
    oledw2_set_font( &oledw2, OLEDW2_FONT_6X8 );
    oledw2_write_string( &oledw2, 2, 0, "6x8 font size" );
    oledw2_set_font( &oledw2, OLEDW2_FONT_5X7 );
    oledw2_write_string( &oledw2, 3, 0, "5x7 font size" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    oledw2_clear_screen( &oledw2 );
    oledw2_set_rotation( &oledw2, OLEDW2_ROTATION_0 );
    oledw2_set_font( &oledw2, OLEDW2_FONT_8X16 );
    oledw2_write_string( &oledw2, 0, 0, "8x16 font size" );
    oledw2_set_font( &oledw2, OLEDW2_FONT_6X8 );
    oledw2_write_string( &oledw2, 2, 0, "6x8 font size" );
    oledw2_set_font( &oledw2, OLEDW2_FONT_5X7 );
    oledw2_write_string( &oledw2, 3, 0, "5x7 font size" );
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
