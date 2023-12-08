/*!
 * \file 
 * \brief 4x4 RGB Click example
 * 
 * # Description
 * This application is used for powering 4x4 RGB LED matrix.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - GPIO.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of 4x4 RGB Click board.
 * This simple example shows all ten numbers in different colors on 4x4 RGB click.
 * The 4x4 RGB click carries a matrix of 16 RGB LEDs and an MCP1826 low dropout regulator.
 * These LEDs actually consist of three single colored LEDs ( Red, Green and Blue ) in a single package.
 * Various colors can be reproduced by mixing the intensity of each LED.
 * 
 * @note
 * **Diodes layout:**
 * ----------------------
 * | 13 | 14 | 15 | 16  |
 * |--------------------|
 * |  9 | 10 | 11 | 12  |
 * |--------------------|
 * |  5 |  6 |  7 |  8  |
 * |--------------------|
 * |  1 |  2 |  3 |  4  |
 * ----------------------
 * 
 * Timing sequence chart:
 *          -----------|     T0L
 *              T0H    |______________
 * Logic 0: 
 *          T0H: 350ns (+/-150ns)
 *          T0L: 800ns (+/-150ns)
 * 
 *          -----------|     T1L
 *              T1H    |______________
 * Logic 1: 
 *          T1H: 700ns (+/-150ns)
 *          T1L: 600ns (+/-150ns)
 * 
 * \author MikroE Team
 *
 */
#include "board.h"
#include "c4x4rgb.h"

// Delay adjustment for specific systems.
#ifdef __MIKROC_AI__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH Delay_Cyc( 4 );   // ~340ns
        #define DELAY_TOL Delay_Cyc( 6 );   // ~800ns
        #define DELAY_T1H Delay_Cyc( 10 );  // ~700ns
        #define DELAY_T1L Delay_Cyc( 3 );   // ~620ns
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
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop;                // ~310ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~860ns
        #define DELAY_T1H Delay_Cyc( 7 );   // ~710ns
        #define DELAY_T1L \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop;                // ~580ns
    #elif TM4C129XNCZAD
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH asm nop;          // ~330ns
        #define DELAY_TOL                   // ~890ns
        #define DELAY_T1H Delay_Cyc( 4 );   // ~720ns
        #define DELAY_T1L                   // ~920ns
    #elif PIC32MX795F512L
        /*< Adjusted for PIC32MX795F512L */
        #define DELAY_TOH  \
                    asm nop; \
                    asm nop;                // ~340ns
        #define DELAY_TOL                   // ~1.06us
        #define DELAY_T1H Delay_Cyc( 3 );   // ~750ns
        #define DELAY_T1L                   // ~1.07us
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
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~330ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~850ns
        #define DELAY_T1H Delay_Cyc( 5 );   // ~710ns
        #define DELAY_T1L  \
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
                    asm("nop");             // ~600ns
    #elif MK64
        /*< Adjusted for MK64FN1M0VDC12 */
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
                    asm("nop");            // ~350ns
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
                    asm("nop");             // ~810ns
        #define DELAY_T1H Delay_Cyc( 7 );   // ~700ns
        #define DELAY_T1L                   // ~600ns
    #elif TM4C129
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH                   // ~430ns
        #define DELAY_TOL                   // ~910ns
        #define DELAY_T1H Delay_Cyc( 2 );   // ~900ns
        #define DELAY_T1L                   // ~930ns
    #elif GD32VF103VBT6
        /*< Adjusted for GD32VF103VBT6 */
        #define DELAY_TOH \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~330ns
        #define DELAY_TOL \
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
                    asm("nop");             // ~770ns
        #define DELAY_T1H Delay_Cyc( 2 );   // ~680ns
        #define DELAY_T1L                   // ~630ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#else
    #error "Logic delays are not defined for the selected toolchain"
#endif

#define SNAKE_DELAY     50
#define MASH_DELAY      100

static c4x4rgb_t c4x4rgb;

static void c4x4rgb_logic_zero ( void );

static void c4x4rgb_logic_one ( void );

static void c4x4rgb_color_mash ( void );

static void c4x4rgb_snake ( uint32_t snake_color );

static void c4x4rgb_snake_return ( uint32_t snake_color );

void application_init ( void )
{
    c4x4rgb_cfg_t cfg;

    //  Click initialization.
    c4x4rgb_cfg_setup( &cfg, &c4x4rgb_logic_zero, &c4x4rgb_logic_one, C4X4RGB_CTRL_PIN_IN1 );
    C4X4RGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4x4rgb_init( &c4x4rgb, &cfg );
    
    c4x4rgb_fill_screen( &c4x4rgb, C4X4RGB_COLOR_WHITE );
    Delay_ms( 100 ); 
    
    c4x4rgb_color_mash();
    Delay_ms( 2000 );
}

void application_task ( void )
{
    c4x4rgb_snake( C4X4RGB_COLOR_BLUE );
    Delay_ms( 500 ); 
    
    c4x4rgb_snake_return( C4X4RGB_COLOR_LIGHT_BLUE );
    Delay_ms( 1000 ); 
    
    c4x4rgb_snake(  C4X4RGB_COLOR_GREEN );
    Delay_ms( 500 ); 
    
    c4x4rgb_snake_return( C4X4RGB_COLOR_YELLOW );
    Delay_ms( 1000 ); 
    
    c4x4rgb_snake( C4X4RGB_COLOR_RED );
    Delay_ms( 500 ); 
    
    c4x4rgb_snake_return( C4X4RGB_COLOR_PURPLE );
    Delay_ms( 1000 ); 
    
    c4x4rgb_fill_screen( &c4x4rgb, C4X4RGB_COLOR_WHITE );
    Delay_ms( 100 ); 
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


static void c4x4rgb_logic_zero ( void )
{
    hal_ll_gpio_set_pin_output( &c4x4rgb.ctrl_pin.pin );
    DELAY_TOH;
    hal_ll_gpio_clear_pin_output( &c4x4rgb.ctrl_pin.pin );
    DELAY_TOL;
}

static void c4x4rgb_logic_one ( void )
{
    hal_ll_gpio_set_pin_output( &c4x4rgb.ctrl_pin.pin );
    DELAY_T1H;
    hal_ll_gpio_clear_pin_output( &c4x4rgb.ctrl_pin.pin );
    DELAY_T1L;
}

static void c4x4rgb_color_mash ( void )
{
    c4x4rgb_set_diode( &c4x4rgb, 1, C4X4RGB_COLOR_BLUE );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 2, C4X4RGB_COLOR_YELLOW );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 3, C4X4RGB_COLOR_LIGHT_BLUE );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 4, C4X4RGB_COLOR_WHITE );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 5, C4X4RGB_COLOR_PURPLE );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 6, C4X4RGB_COLOR_GREEN );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 7, C4X4RGB_COLOR_RED );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 8, C4X4RGB_COLOR_BLUE );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 9, C4X4RGB_COLOR_YELLOW );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 10, C4X4RGB_COLOR_LIGHT_BLUE );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 11, C4X4RGB_COLOR_WHITE );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 12, C4X4RGB_COLOR_PURPLE );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 13, C4X4RGB_COLOR_GREEN );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 14, C4X4RGB_COLOR_RED );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 15, C4X4RGB_COLOR_BLUE );
    Delay_ms( MASH_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 16, C4X4RGB_COLOR_RED );
    Delay_ms( MASH_DELAY );
}

static void c4x4rgb_snake ( uint32_t snake_color )
{
    c4x4rgb_set_diode( &c4x4rgb, 4, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 3, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 2, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 1, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 5, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 9, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 13, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 14, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 15, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 16, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 12, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 8, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 7, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 6, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 10, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 11, snake_color );
}

static void c4x4rgb_snake_return ( uint32_t snake_color )
{
    c4x4rgb_set_diode( &c4x4rgb, 11, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 10, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 6, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 7, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 8, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 12, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 16, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 15, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 14, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 13, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 9, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 5, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 1, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 2, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 3, snake_color );
    Delay_ms( SNAKE_DELAY );
    c4x4rgb_set_diode( &c4x4rgb, 4, snake_color );
    Delay_ms( SNAKE_DELAY );
}

// ------------------------------------------------------------------------ END
