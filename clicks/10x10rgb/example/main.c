/*!
 * \file 
 * \brief 10x10 RGB Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the 10x10 RGB click module. The
 * click has a 10 by 10 RGB LED matrix which can be programmed to show different colors or even
 * images. LED elements that form the matrix communicate by a single line with the host MCU.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click board.
 * 
 * ## Application Task  
 * This function first displays 3 chars { R, G, B }, the string "MIKROE", the company logo and
 * a rainbow in the end.
 * 
 * @note
 * Make sure the logic delays are defined for your system in the c10x10rgb_delays.h file.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "c10x10rgb.h"
#include "c10x10rgb_delays.h"

// ------------------------------------------------------------------ VARIABLES

static c10x10rgb_t c10x10rgb;

const uint32_t MIKROE_IMAGE[ 100 ] =
{
    0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x181800,0x181800,0x181800,0x181800,0x181800,0x181800,0x181800,0x000000,
    0x000000,0x181800,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,
    0x000000,0x181800,0x181800,0x181800,0x181800,0x181800,0x181800,0x181800,0x181800,0x000000,
    0x000000,0x181800,0x181800,0x181800,0x181800,0x181800,0x181800,0x181800,0x181800,0x000000,
    0x000000,0x181800,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x181800,0x181800,0x181800,0x181800,0x181800,0x181800,0x181800,0x000000,
    0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,
    0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000
};

static c10x10rgb_byte_t scroll_data_obj[ 6 ] =
{
    { 'M', C10X10RGB_COLOR_OFF, C10X10RGB_COLOR_YELLOW_25, C10X10RGB_SCROLL_ROTATE_V },
    { 'I', C10X10RGB_COLOR_OFF, C10X10RGB_COLOR_YELLOW_25, C10X10RGB_SCROLL_ROTATE_V },
    { 'K', C10X10RGB_COLOR_OFF, C10X10RGB_COLOR_YELLOW_25, C10X10RGB_SCROLL_ROTATE_V },
    { 'R', C10X10RGB_COLOR_OFF, C10X10RGB_COLOR_YELLOW_25, C10X10RGB_SCROLL_ROTATE_V },
    { 'O', C10X10RGB_COLOR_OFF, C10X10RGB_COLOR_YELLOW_25, C10X10RGB_SCROLL_ROTATE_V },
    { 'E', C10X10RGB_COLOR_YELLOW_25, C10X10RGB_COLOR_OFF, C10X10RGB_SCROLL_ROTATE_V }
};

static uint16_t scroll_speed_ms = 100;
static uint8_t scroll_data_len = 6;

static c10x10rgb_byte_t rgb_data_byte[ 3 ] =
{
    { 'R', C10X10RGB_COLOR_RED_25, C10X10RGB_COLOR_OFF, C10X10RGB_BYTE_ROTATE_H_UP },
    { 'G', C10X10RGB_COLOR_OFF, C10X10RGB_COLOR_GREEN_25, C10X10RGB_BYTE_ROTATE_H_UP },
    { 'B', C10X10RGB_COLOR_BLUE_25, C10X10RGB_COLOR_OFF, C10X10RGB_BYTE_ROTATE_H_UP }
};

static uint8_t rainbow_brightness = 10;
static uint16_t rainbow_speed_ms = 20;                                                 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void logic_zero ( void )
{
    hal_ll_gpio_set_pin_output( &c10x10rgb.di_pin.pin );
    DELAY_TOH;
    hal_ll_gpio_clear_pin_output( &c10x10rgb.di_pin.pin );
    DELAY_TOL;
}

static void logic_one ( void )
{
    hal_ll_gpio_set_pin_output( &c10x10rgb.di_pin.pin );
    DELAY_T1H;
    hal_ll_gpio_clear_pin_output( &c10x10rgb.di_pin.pin );
    DELAY_T1L;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    c10x10rgb_cfg_t cfg;

    //  Click initialization.
    c10x10rgb_cfg_setup( &cfg, &logic_zero, &logic_one );
    C10X10RGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c10x10rgb_init( &c10x10rgb, &cfg );

    c10x10rgb_fill_screen( &c10x10rgb, C10X10RGB_COLOR_OFF );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    c10x10rgb_display_byte ( &c10x10rgb, &rgb_data_byte[ 0 ] );
    Delay_ms( 1000 );
    c10x10rgb_display_byte ( &c10x10rgb, &rgb_data_byte[ 1 ] );
    Delay_ms( 1000 );
    c10x10rgb_display_byte ( &c10x10rgb, &rgb_data_byte[ 2 ] );
    Delay_ms( 2000 );
    
    c10x10rgb_display_string( &c10x10rgb, &scroll_data_obj, scroll_data_len, scroll_speed_ms );
    Delay_ms( 1000 );
    c10x10rgb_display_image( &c10x10rgb, &MIKROE_IMAGE[ 0 ] );
    Delay_ms( 3000 );
    c10x10rgb_demo_rainbow( &c10x10rgb, rainbow_brightness, rainbow_speed_ms );
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
