/*!
 * @file main.c
 * @brief 2x4 RGB Click Example.
 *
 * # Description
 * This example demonstrates the use of 2x4 RGB click board by cycling through
 * a set of colors, gradually increasing the brightness of each LED in a sequence,
 * and then decreasing the brightness before moving on to the next color in the array.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets
 * the LEDs brightness and current gain to a minimum and the color to black (all LEDs off).
 *
 * ## Application Task
 * Cycles through a set of colors, gradually increases the brightness of each LED
 * in a sequence, and then decreases the brightness before moving on to the next
 * color in the array. The current color's name and RGB value are logged to the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c2x4rgb.h"
#include "c2x4rgb_delays.h"

static c2x4rgb_t c2x4rgb;   /**< 2x4 RGB Click driver object. */
static log_t logger;    /**< Logger object. */

static c2x4rgb_color_t color[ C2X4RGB_NUM_COLORS ] = 
{ 
    { C2X4RGB_COLOR_BLACK, "BLACK" },
    { C2X4RGB_COLOR_WHITE, "WHITE" },
    { C2X4RGB_COLOR_RED, "RED" },
    { C2X4RGB_COLOR_LIME, "LIME" },
    { C2X4RGB_COLOR_BLUE, "BLUE" },
    { C2X4RGB_COLOR_YELLOW, "YELLOW" },
    { C2X4RGB_COLOR_CYAN, "CYAN" },
    { C2X4RGB_COLOR_MAGENTA, "MAGENTA" },
    { C2X4RGB_COLOR_SILVER, "SILVER" },
    { C2X4RGB_COLOR_GRAY, "GRAY" },
    { C2X4RGB_COLOR_MAROON, "MAROON" },
    { C2X4RGB_COLOR_OLIVE, "OLIVE" },
    { C2X4RGB_COLOR_GREEN, "GREEN" },
    { C2X4RGB_COLOR_PURPLE, "PURPLE" },
    { C2X4RGB_COLOR_TEAL, "TEAL" },
    { C2X4RGB_COLOR_NAVY, "NAVY" }
};

/**
 * @brief 2x4 RGB logic zero function.
 * @details This function toggles the data pin with exact high and low time pulse for logic zero.
 * @return None.
 * @note None.
 */
static void c2x4rgb_logic_zero ( void );

/**
 * @brief 2x4 RGB logic one function.
 * @details This function toggles the data pin with exact high and low time pulse for logic one.
 * @return None.
 * @note None.
 */
static void c2x4rgb_logic_one ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c2x4rgb_cfg_t c2x4rgb_cfg;  /**< Click config object. */

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
    c2x4rgb_cfg_setup( &c2x4rgb_cfg );
    C2X4RGB_MAP_MIKROBUS( c2x4rgb_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == 
         c2x4rgb_init( &c2x4rgb, &c2x4rgb_logic_zero, &c2x4rgb_logic_one, &c2x4rgb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( C2X4RGB_ERROR == c2x4rgb_default_cfg ( &c2x4rgb ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint32_t color_num = 0;
    static int8_t led_cnt = 0;
    static int8_t brightness = 0;
    log_printf( &logger, " Color: %s [%.6LX]\r\n\n", color[ color_num ].name, color[ color_num ].rgb );
    Delay_ms ( 100 );
    c2x4rgb_set_leds_intensity ( &c2x4rgb, C2X4RGB_LED_BRIGHTNESS_MIN, C2X4RGB_LED_CURRENT_GAIN_DEFAULT );
    for ( led_cnt = C2X4RGB_LED_7; led_cnt >= C2X4RGB_LED_0; led_cnt-- )
    {
        c2x4rgb_set_led_color ( &c2x4rgb, led_cnt, color[ color_num ].rgb );
        c2x4rgb_write_led_matrix ( &c2x4rgb );
        Delay_ms ( 100 );
    }
    for ( brightness = C2X4RGB_LED_BRIGHTNESS_MIN; brightness < C2X4RGB_LED_BRIGHTNESS_MAX; brightness++ )
    {
        c2x4rgb_set_leds_intensity ( &c2x4rgb, brightness, C2X4RGB_LED_CURRENT_GAIN_DEFAULT );
        c2x4rgb_write_led_matrix ( &c2x4rgb );
        Delay_ms ( 50 );
    }
    for ( brightness = C2X4RGB_LED_BRIGHTNESS_MAX; brightness >= C2X4RGB_LED_BRIGHTNESS_MIN; brightness-- )
    {
        c2x4rgb_set_leds_intensity ( &c2x4rgb, brightness, C2X4RGB_LED_CURRENT_GAIN_DEFAULT );
        c2x4rgb_write_led_matrix ( &c2x4rgb );
        Delay_ms ( 50 );
    }
    if ( ++color_num >= C2X4RGB_NUM_COLORS )
    {
        color_num = 0;
    }
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

static void c2x4rgb_logic_zero ( void )
{
    hal_ll_gpio_set_pin_output( &c2x4rgb.din.pin );
    DELAY_TOH;
    hal_ll_gpio_clear_pin_output( &c2x4rgb.din.pin );
    DELAY_TOL;
}

static void c2x4rgb_logic_one ( void )
{
    hal_ll_gpio_set_pin_output( &c2x4rgb.din.pin );
    DELAY_T1H;
    hal_ll_gpio_clear_pin_output( &c2x4rgb.din.pin );
    DELAY_T1L;
}

// ------------------------------------------------------------------------ END
