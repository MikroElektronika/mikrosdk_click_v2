/*!
 * \file 
 * \brief 7-SEG RGB Click example
 * 
 * # Description
 * This click shows all ten digits on a full-color single 7 segment digit display. 
 * Each segment has R, G, B LEDs that can be adjusted in 255 steps and 
 * the ability to control the brightness of all the LED.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - GPIO.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of 7-SEG RGB Click board.
 * This simple example shows all ten digits in different colors on 7-SEG RGB click.
 * 
 * @note 
 * <pre>
 * Additional Functions :
 * void logic_one ( )  - Generic logic one function.
 * void logic_zero ( ) - Generic logic zero function.
 * </pre>
 * 
 * - segments layout
 *       _0_
 *     5|   |1
 *      |_6_|
 *     4|   |2
 *      |_3_|.7
 * 
 * Timing sequence chart:
 *          -----------|     T0L
 *              T0H    |______________
 * Logic 0: 
 *          T0H: 400ns (+/-150ns)
 *          T0L: 850ns (+/-150ns)
 * 
 *          -----------|     T1L
 *              T1H    |______________
 * Logic 1: 
 *          T1H: 850ns (+/-150ns)
 *          T1L: 400ns (+/-150ns)
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "c7segrgb.h"

// Delay adjustment for specific systems.
#ifdef __MIKROC_AI__
    #ifdef STM32F407ZG
        /*< Adjusted for STM32F407ZG */
        #define DELAY_TOH Delay_Cyc( 5 );   // ~400ns
        #define DELAY_TOL Delay_Cyc( 8 );   // ~850ns
        #define DELAY_T1H Delay_Cyc( 12 );  // ~820ns
        #define DELAY_T1L                   // ~420ns
    #elif MK64FN1M0VDC12
        /*< Adjusted for MK64FN1M0VDC12 */
        #define DELAY_TOH Delay_Cyc( 3 );   // ~370ns
        #define DELAY_TOL Delay_Cyc( 5 );   // ~860ns
        #define DELAY_T1H Delay_Cyc( 8 );   // ~790ns
        #define DELAY_T1L                   // ~460ns
    #elif TM4C129XNCZAD
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop;                // ~390ns
        #define DELAY_TOL                   // ~870ns
        #define DELAY_T1H Delay_Cyc( 6 );   // ~850ns
        #define DELAY_T1L                   // ~860ns
    #elif PIC32MX795F512L
        /*< Adjusted for PIC32MX795F512L */
        #define DELAY_TOH  \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop; \
                    asm nop;                // ~390ns
        #define DELAY_TOL                   // ~1.03us
        #define DELAY_T1H Delay_Cyc( 4 );   // ~870ns
        #define DELAY_T1L                   // ~1.03us
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
                    asm("nop");             // ~410ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~810ns
        #define DELAY_T1H Delay_Cyc( 7 );   // ~810ns
        #define DELAY_T1L                   // ~460ns
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
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~380ns
        #define DELAY_TOL Delay_Cyc( 2 );   // ~910ns
        #define DELAY_T1H Delay_Cyc( 10 );  // ~790ns
        #define DELAY_T1L                   // ~570ns
    #elif TM4C129
        /*< Adjusted for TM4C129XNCZAD */
        #define DELAY_TOH \
                    asm("nop"); \
                    asm("nop");             // ~410ns
        #define DELAY_TOL                   // ~930ns
        #define DELAY_T1H Delay_Cyc( 2 );   // ~950ns
        #define DELAY_T1L                   // ~980ns
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
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~390ns
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
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop"); \
                    asm("nop");             // ~810ns
        #define DELAY_T1H Delay_Cyc( 4 );   // ~910ns
        #define DELAY_T1L                   // ~630ns
    #else
        #error "Logic delays are not defined for the selected MCU"
    #endif
#else
    #error "Logic delays are not defined for the selected toolchain"
#endif

// ------------------------------------------------------------------ VARIABLES

static c7segrgb_t c7segrgb;

static uint8_t CHARACTER_TABLE[ 10 ] = 
{
    0x3F, // '0'
    0x06, // '1'    _a_
    0x5B, // '2'  f|   |b
    0x4F, // '3'   |_g_|
    0x66, // '4'  e|   |c
    0x6D, // '5'   |_d_|.dp
    0x7D, // '6'
    0x07, // '7'
    0x7F, // '8'
    0x6F  // '9'
};
                                       
static c7segrgb_segment_t segments_data[ 8 ] = 
{
    { true, 40, 0, 0 },
    { true, 0, 40, 0 },
    { true, 0, 0, 40 },
    { true, 10, 40, 40 },
    { true, 40, 10, 40 },
    { true, 40, 40, 10 },
    { true, 10, 20, 30 },
    { true, 30, 20, 10 }
};

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void logic_one ( void )
{
    hal_ll_gpio_set_pin_output( &c7segrgb.pwm.pin );
    DELAY_T1H;
    hal_ll_gpio_clear_pin_output( &c7segrgb.pwm.pin );
    DELAY_T1L;
}

void logic_zero ( void )
{
    hal_ll_gpio_set_pin_output( &c7segrgb.pwm.pin );
    DELAY_TOH;
    hal_ll_gpio_clear_pin_output( &c7segrgb.pwm.pin );
    DELAY_TOL;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    c7segrgb_cfg_t cfg;

    //  Click initialization.
    c7segrgb_cfg_setup( &cfg );
    cfg.logic_one = &logic_one;
    cfg.logic_zero = &logic_zero;
    C7SEGRGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c7segrgb_init( &c7segrgb, &cfg );
    
    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        c7segrgb.segments[ cnt ] = segments_data[ cnt ];
    }
    c7segrgb_set_seven_seg( &c7segrgb );
    Delay_ms( 3000 );
}

void application_task ( void )
{
    for ( uint8_t cnt_i = 0; cnt_i < 10; cnt_i++ )
    {
        for ( uint8_t cnt_j = 10; cnt_j > 0; cnt_j-- )
        {
            c7segrgb_set_num( &c7segrgb, CHARACTER_TABLE[ cnt_i ], 4 * cnt_i, 4 * cnt_j, cnt_i * cnt_j );
            Delay_ms( 100 );
        }
    }
    
    c7segrgb_set_num( &c7segrgb, C7SEGRGB_POINT, 10, 10, 10 );
    Delay_ms( 1000 );
    
    c7segrgb_set_num( &c7segrgb, C7SEGRGB_ZERO, 40, 40, 40 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_ONE, 40, 0, 0 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_TWO, 0, 40, 0 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_THREE, 0, 0, 40 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_FOUR, 40, 0, 40 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_FIVE, 0, 40, 40 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_SIX, 40, 40, 0 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_SEVEN, 20, 30, 40 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_EIGHT, 40, 15, 31 );
    Delay_ms( 1000 );

    c7segrgb_set_num( &c7segrgb, C7SEGRGB_NINE, 20, 10, 30 );
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
