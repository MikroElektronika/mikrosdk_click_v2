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
 * This function initializes and configures the click board.
 * 
 * ## Application Task  
 * This function first displays 3 chars { R, G, B }, the string "MIKROE", the company logo and
 * a rainbow in the end.
 * 
 * @note
 * Timing sequence chart:
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

// Delay adjustment for specific systems.
#ifdef __MIKROC_AI__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH Delay_Cyc( 3 );   // ~280ns
        #define DELAY_TOL Delay_Cyc( 7 );   // ~790ns
        #define DELAY_T1H Delay_Cyc( 12 );  // ~820ns
        #define DELAY_T1L Delay_Cyc( 8 );   // ~840ns
    #elif MK64FN1M0VDC12
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop;                // ~280ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~880ns
        #define DELAY_T1H Delay_Cyc( 8 );   // ~800ns
        #define DELAY_T1L Delay_Cyc( 2 );   // ~800ns
    #elif TM4C129XNCZAD
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH                   // ~320ns
        #define DELAY_TOL asm nop;          // ~780ns
        #define DELAY_T1H Delay_Cyc( 6 );   // ~860ns
        #define DELAY_T1L                   // ~800ns
    #elif PIC32MX795F512L
        /*< Adjusted for PIC32MX795F512L */
        #define DELAY_TOH                   // ~300ns
        #define DELAY_TOL                   // ~940ns
        #define DELAY_T1H Delay_Cyc( 3 );   // ~780ns
        #define DELAY_T1L                   // ~940ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#elif __GNUC__ 
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~300ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~840ns
        #define DELAY_T1H Delay_Cyc( 7 );   // ~810ns
        #define DELAY_T1L Delay_Cyc( 2 );   // ~830ns
    #elif MK64
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~300ns
        #define DELAY_TOL  \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~720ns
        #define DELAY_T1H Delay_Cyc( 7 );   // ~780ns
        #define DELAY_T1L Delay_Cyc( 2 );   // ~900ns
    #elif TM4C129
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH                   // ~350ns
        #define DELAY_TOL                   // ~900ns
        #define DELAY_T1H Delay_Cyc( 2 );   // ~880ns
        #define DELAY_T1L                   // ~900ns
    #elif GD32VF103VBT6
        /*< Adjusted for GD32VF103VBT6 */
        #define DELAY_TOH \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~290ns
        #define DELAY_TOL \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~690ns
        #define DELAY_T1H Delay_Cyc( 2 );   // ~730ns
        #define DELAY_T1L \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");            // ~680ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#else
    #error "Logic delays are not defined for the selected toolchain"
#endif

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

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
