/*!
 * @file main.c
 * @brief 4x4 RGB 2 Click example
 *
 * # Description
 * This example demonstrates the use of 4x4 RGB 2 click board by setting all 16 LEDs
 * to different colors and changing the LEDs color every 500 milliseconds. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets
 * the LEDs brightness to level 1 and the color to black (all LEDs off).
 *
 * ## Application Task
 * Sets all 16 LEDs to a different colors and changes their color every 500 milliseconds.
 * All data is displayed on the USB UART where you can track their changes.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c4x4rgb2.h"

static c4x4rgb2_t c4x4rgb2;
static log_t logger;

static c4x4rgb2_color_t color[ C4X4RGB2_NUM_COLORS ] = 
{ 
    { C4X4RGB2_COLOR_BLACK, "BLACK" },
    { C4X4RGB2_COLOR_WHITE, "WHITE" },
    { C4X4RGB2_COLOR_RED, "RED" },
    { C4X4RGB2_COLOR_LIME, "LIME" },
    { C4X4RGB2_COLOR_BLUE, "BLUE" },
    { C4X4RGB2_COLOR_YELLOW, "YELLOW" },
    { C4X4RGB2_COLOR_CYAN, "CYAN" },
    { C4X4RGB2_COLOR_MAGENTA, "MAGENTA" },
    { C4X4RGB2_COLOR_SILVER, "SILVER" },
    { C4X4RGB2_COLOR_GRAY, "GRAY" },
    { C4X4RGB2_COLOR_MAROON, "MAROON" },
    { C4X4RGB2_COLOR_OLIVE, "OLIVE" },
    { C4X4RGB2_COLOR_GREEN, "GREEN" },
    { C4X4RGB2_COLOR_PURPLE, "PURPLE" },
    { C4X4RGB2_COLOR_TEAL, "TEAL" },
    { C4X4RGB2_COLOR_NAVY, "NAVY" }
};

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c4x4rgb2_cfg_t c4x4rgb2_cfg;  /**< Click config object. */

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
    c4x4rgb2_cfg_setup( &c4x4rgb2_cfg );
    C4X4RGB2_MAP_MIKROBUS( c4x4rgb2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c4x4rgb2_init( &c4x4rgb2, &c4x4rgb2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C4X4RGB2_ERROR == c4x4rgb2_default_cfg ( &c4x4rgb2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t color_num = 0;
    for ( uint8_t led_cnt = C4X4RGB2_LED_0; led_cnt <= C4X4RGB2_LED_15; led_cnt++ )
    {
        c4x4rgb2_set_led_color ( &c4x4rgb2, led_cnt, 
                                 color[ ( led_cnt + color_num ) % C4X4RGB2_NUM_COLORS ].rgb );
        log_printf( &logger, " LED %u Color: %s - %.6LX\r\n", ( uint16_t ) led_cnt, 
                    color[ ( led_cnt + color_num ) % C4X4RGB2_NUM_COLORS ].name, 
                    color[ ( led_cnt + color_num ) % C4X4RGB2_NUM_COLORS ].rgb );
    }
    if ( C4X4RGB2_OK == c4x4rgb2_write_led_matrix ( &c4x4rgb2 ) )
    {
        log_printf( &logger, " Write LED Matrix\r\n\n" );
        Delay_ms ( 500 );
    }
    if ( ++color_num >= C4X4RGB2_NUM_COLORS )
    {
        color_num = 0;
    }
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
