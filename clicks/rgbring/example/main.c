/*!
 * @file main.c
 * @brief RGB Ring Click Example.
 *
 * # Description
 * This example demonstrates the use of RGB Ring Click board by controling an RGB ring 
 * by cycling through a set of predefined colors. Each color is displayed by lighting up 
 * the LEDs in sequence around the ring. After the last LED is lit, the code waits for
 * a button press before moving on to the next color in the sequence. 
 * The button press triggers the transition to the next color in the array.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which sets
 * the color to black (all LEDs off).
 *
 * ## Application Task
 * Controls an LED ring by cycling through colors and waits for user input to change
 * the ring's color. The button press is required to move to the next color in the sequence.
 * The current color's name and RGB value are logged to the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rgbring.h"
#include "rgbring_delays.h"

static rgbring_t rgbring;   /**< RGB Ring Click driver object. */
static log_t logger;    /**< Logger object. */

static rgbring_color_t color[ RGBRING_NUM_COLORS ] = 
{ 
    { RGBRING_COLOR_BLACK, "BLACK" },
    { RGBRING_COLOR_WHITE, "WHITE" },
    { RGBRING_COLOR_RED, "RED" },
    { RGBRING_COLOR_LIME, "LIME" },
    { RGBRING_COLOR_BLUE, "BLUE" },
    { RGBRING_COLOR_YELLOW, "YELLOW" },
    { RGBRING_COLOR_CYAN, "CYAN" },
    { RGBRING_COLOR_MAGENTA, "MAGENTA" },
    { RGBRING_COLOR_SILVER, "SILVER" },
    { RGBRING_COLOR_GRAY, "GRAY" },
    { RGBRING_COLOR_MAROON, "MAROON" },
    { RGBRING_COLOR_OLIVE, "OLIVE" },
    { RGBRING_COLOR_GREEN, "GREEN" },
    { RGBRING_COLOR_PURPLE, "PURPLE" },
    { RGBRING_COLOR_TEAL, "TEAL" },
    { RGBRING_COLOR_NAVY, "NAVY" }
};

/**
 * @brief RGB Ring logic zero function.
 * @details This function toggles the data pin with exact high and low time pulse for logic zero.
 * @return None.
 * @note None.
 */
static void rgbring_logic_zero ( void );

/**
 * @brief RGB Ring logic one function.
 * @details This function toggles the data pin with exact high and low time pulse for logic one.
 * @return None.
 * @note None.
 */
static void rgbring_logic_one ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rgbring_cfg_t rgbring_cfg;  /**< Click config object. */

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
    rgbring_cfg_setup( &rgbring_cfg );
    RGBRING_MAP_MIKROBUS( rgbring_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == 
         rgbring_init( &rgbring, &rgbring_logic_zero, &rgbring_logic_one, &rgbring_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( RGBRING_ERROR == rgbring_default_cfg ( &rgbring ) )
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

    log_printf( &logger, " Color: %s [%.6LX]\r\n", color[ color_num ].name, color[ color_num ].rgb );
    Delay_ms ( 100 );
    for ( led_cnt = RGBRING_LED_7; led_cnt >= RGBRING_LED_0; led_cnt-- )
    {
        rgbring_set_led_color ( &rgbring, led_cnt, color[ color_num ].rgb );
        rgbring_write_led_matrix ( &rgbring );
        Delay_ms ( 100 );
    }
    if ( ++color_num >= RGBRING_NUM_COLORS )
    {
        color_num = 0;
    }

    log_printf ( &logger, " Press button to change ring color\r\n\n" );
    while ( RGBRING_BUTTON_RELESED == rgbring_get_int_pin ( &rgbring ) );
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

static void rgbring_logic_zero ( void )
{
    hal_ll_gpio_set_pin_output( &rgbring.din.pin );
    DELAY_TOH;
    hal_ll_gpio_clear_pin_output( &rgbring.din.pin );
    DELAY_TOL;
}

static void rgbring_logic_one ( void )
{
    hal_ll_gpio_set_pin_output( &rgbring.din.pin );
    DELAY_T1H;
    hal_ll_gpio_clear_pin_output( &rgbring.din.pin );
    DELAY_T1L;
}

// ------------------------------------------------------------------------ END
