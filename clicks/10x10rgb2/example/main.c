/*!
 * @file main.c
 * @brief 10x10 RGB 2 Click example
 *
 * # Description
 * This example demonstrates the use of the 10x10 RGB 2 Click board by showing
 * a practical example of using the implemented functions.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Displays digits 0-9 first, then writes RGB chars and demonstrates the rotation of characters.
 * After that, scrolls the text, displays the MIKROE logo image, and showcases a rainbow demo.
 * All data is logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c10x10rgb2.h"
#include "c10x10rgb2_resources.h"

static c10x10rgb2_t c10x10rgb2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c10x10rgb2_cfg_t c10x10rgb2_cfg;  /**< Click config object. */

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
    c10x10rgb2_cfg_setup( &c10x10rgb2_cfg );
    C10X10RGB2_MAP_MIKROBUS( c10x10rgb2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c10x10rgb2_init( &c10x10rgb2, &c10x10rgb2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C10X10RGB2_ERROR == c10x10rgb2_default_cfg ( &c10x10rgb2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    log_printf( &logger, " Writing digits\r\n\n" );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_MAROON, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    for ( uint8_t digit = '0'; digit <= '9'; digit++ )
    {
        c10x10rgb2_write_char ( &c10x10rgb2, digit );
        Delay_ms ( 500 );
    }

    log_printf( &logger, " Writing RGB chars\r\n\n" );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_RED, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 1000 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_BLACK, C10X10RGB2_COLOR_GREEN, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'G' );
    Delay_ms ( 1000 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_BLUE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'B' );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Rotating char\r\n\n" );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_PURPLE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 500 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_PURPLE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_H_180 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 500 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_PURPLE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_180 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 500 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_PURPLE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_H_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 500 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_PURPLE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 500 );
    
    log_printf( &logger, " Writing text\r\n\n" );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_OLIVE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_string ( &c10x10rgb2, "MIKROE 10x10 RGB 2", 50 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Drawing MIKROE logo\r\n\n" );
    c10x10rgb2_draw_picture ( &c10x10rgb2, c10x10rgb_img_mikroe );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Rainbow demo\r\n\n" );
    c10x10rgb2_demo_rainbow ( &c10x10rgb2, 10, 10, 500 );
    Delay_ms ( 500 );
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
