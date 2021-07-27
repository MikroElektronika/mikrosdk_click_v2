/*!
 * \file 
 * \brief 10x10 RGB Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the 10x10 RGB click moduel. The
 * click has a 10 by 10 RGB LED matrix which can be programmed to show different colors or even
 * images. LED elements that form the matrix communicate by a single line with the host MCU.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function first displays 3 bytes { R, G, B }, the string "Mikroe", the company logo and
 * a rainbow in the end.
 * 
 * @note
 * Timeing sequence chart:
 *          -----------|     T0L
 *              T0H    |______________
 * Logic 0: 
 *          T0H ~ 200-400ns
 *          T0L ~ 600-1000ns
 * 
 *          -----------|     T1L
 *              T1H    |______________
 * Logic 1: 
 *          T1H ~ 600-1000ns
 *          T1L ~ 600-1000ns
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "c10x10rgb.h"

#if defined __MIKROC_AI_FOR_ARM__
#define D_S    2
#define D_L    4

#define DELAY_SHORT( void ) \
    Delay_Cyc( D_S );
    
#define DELAY_LONG( void ) \
    Delay_Cyc( D_L );
#endif
#if defined __MIKROC_AI_FOR_PIC32__

#define D_L    4
    
#define DELAY_SHORT( void ) \
    asm nop
    
#define DELAY_LONG( void ) \
    Delay_Cyc( D_L );
#endif
#if !defined(__MIKROC_AI_FOR_ARM__) && !defined(__MIKROC_AI_FOR_PIC32__)
#define D_S    1
#define D_L    2

#define DELAY_SHORT( void ) \
    Delay_Cyc( D_S );
    
#define DELAY_LONG( void ) \
    Delay_Cyc( D_L );
#endif

// ------------------------------------------------------------------ VARIABLES

static c10x10rgb_t c10x10rgb;

static uint32_t MIKROE_IMAGE[ 100 ] =
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
    digital_out_write( &c10x10rgb.di_pin, C10X10RGB_CTRL_PIN_HIGH );
    DELAY_SHORT( );
    digital_out_write( &c10x10rgb.di_pin, C10X10RGB_CTRL_PIN_LOW );
    DELAY_LONG( );
}

static void logic_one ( void )
{
    digital_out_write( &c10x10rgb.di_pin, C10X10RGB_CTRL_PIN_HIGH );
    DELAY_LONG( );
    digital_out_write( &c10x10rgb.di_pin, C10X10RGB_CTRL_PIN_LOW );
    DELAY_LONG( );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    c10x10rgb_cfg_t cfg;

    //  Click initialization.

    c10x10rgb_cfg_setup( &cfg, &logic_zero, &logic_one );
    c10X10RGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
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

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
