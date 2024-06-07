/*!
 * @file main.c
 * @brief Rotary RGB Click Example.
 *
 * # Description
 * This library contains the API for the Rotary RGB Click driver 
 * to control LEDs states and a rotary encoder position readings.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module and log UART.
 * After the driver init, the app turn off all LEDs.
 *
 * ## Application Task
 * This example demonstrates the use of the Rotary RGB Click board.
 * The demo example shows the functionality of a rotary encoder used to control RGB LEDs.
 * The switch controls the application of the colors,
 * and the encoder mechanism controls the state of the LEDs.
 *
 * ## Additional Function
 * - static void rotaryrgb_logic_zero ( void )
 * - static void rotaryrgb_logic_one ( void )
 * - static void rotaryrgb_switch_detection ( void )
 * - static void rotaryrgb_encoder_mechanism ( void )
 *
 * @note
 * Make sure the logic delays are defined for your system in the rotaryrgb_delays.h file.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rotaryrgb.h"
#include "rotaryrgb_delays.h"

static rotaryrgb_t rotaryrgb;   /**< Rotary RGB Click driver object. */
static log_t logger;            /**< Logger object. */

static uint8_t start_rot_status = 0;
static uint8_t led_color_sel = 0;
static uint8_t old_state = 0;
static uint8_t new_state = 1;
static uint8_t old_rot_state = 0;
static uint8_t new_rot_state = 1;
static uint16_t led_pos = 1;
static uint32_t demo_color_table[ 8 ] = 
{ 
    ROTARYRGB_COLOR_WHITE_50, 
    ROTARYRGB_COLOR_RED_50, 
    ROTARYRGB_COLOR_GREEN_50, 
    ROTARYRGB_COLOR_BLUE_50, 
    ROTARYRGB_COLOR_LIGHT_BLUE_50, 
    ROTARYRGB_COLOR_YELLOW_50, 
    ROTARYRGB_COLOR_PURPLE_50, 
    ROTARYRGB_COLOR_OFF 
};

/**
 * @brief Rotary RGB logic zero function.
 * @details This function generates a logic zero sequence char 
 * to control the LED light source.
 * @return Nothing.
 */
static void rotaryrgb_logic_zero ( void );

/**
 * @brief Rotary RGB logic one function.
 * @details This function generates a logic one sequence char 
 * to control the LED light source.
 * @return Nothing.
 */
static void rotaryrgb_logic_one ( void );

/**
 * @brief Rotary RGB switch detection function.
 * @details This function is used for the switch state detection.
 * @return Nothing.
 */
static void rotaryrgb_switch_detection ( void );

/**
 * @brief Rotary RGB encoder mechanism function.
 * @details This function is used to control the state of the LEDs 
 * by detecting the rotation direction of the rotary encoder.
 * @return Nothing.
 */
static void rotaryrgb_encoder_mechanism ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryrgb_cfg_t rotaryrgb_cfg;  /**< Click config object. */

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
    rotaryrgb_cfg_setup( &rotaryrgb_cfg, &rotaryrgb_logic_zero, &rotaryrgb_logic_one );
    ROTARYRGB_MAP_MIKROBUS( rotaryrgb_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == rotaryrgb_init( &rotaryrgb, &rotaryrgb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    rotaryrgb_set_all_led_color( &rotaryrgb, ROTARYRGB_COLOR_OFF );
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    rotaryrgb_set_led_pos_color( &rotaryrgb, led_pos % 17, demo_color_table[ led_color_sel ] );
    rotaryrgb_switch_detection( );
    rotaryrgb_encoder_mechanism( );
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

static void rotaryrgb_logic_zero ( void )
{
    hal_ll_gpio_set_pin_output( &rotaryrgb.di_pin.pin );
    DELAY_TOH;
    hal_ll_gpio_clear_pin_output( &rotaryrgb.di_pin.pin );
    DELAY_TOL;
}

static void rotaryrgb_logic_one ( void )
{
    hal_ll_gpio_set_pin_output( &rotaryrgb.di_pin.pin );
    DELAY_T1H;
    hal_ll_gpio_clear_pin_output( &rotaryrgb.di_pin.pin );
    DELAY_T1L;
}

static void rotaryrgb_switch_detection ( void )
{
    if ( rotaryrgb_get_state_switch( &rotaryrgb ) ) 
    {
        new_state = 1;
        if ( ( 1 == new_state ) && ( 0 == old_state ) ) 
        {
            old_state = 1;
            led_color_sel++;
            if ( 7 < led_color_sel ) 
            {
                led_color_sel = 0;
            }
        }
    }
    else 
    {
        old_state = 0;
    }
}

static void rotaryrgb_encoder_mechanism ( void )
{
    if ( rotaryrgb_get_state_enb( &rotaryrgb ) == rotaryrgb_get_state_ena( &rotaryrgb ) ) 
    {
        old_rot_state = 0;
        start_rot_status = rotaryrgb_get_state_enb( &rotaryrgb ) && rotaryrgb_get_state_ena( &rotaryrgb );
    }
    else 
    {
        new_rot_state = 1;
        if ( new_rot_state != old_rot_state ) 
        {
            old_rot_state = 1;
            if ( start_rot_status != rotaryrgb_get_state_enb( &rotaryrgb ) ) 
            {
                led_pos++;
            }
            else 
            {
                led_pos--;
            }

            if ( 0 == led_pos % 17 )
            {
                Delay_ms ( 1 );
                rotaryrgb_set_all_led_color( &rotaryrgb, ROTARYRGB_COLOR_OFF );
            }
        }
    }
}

// ------------------------------------------------------------------------ END
