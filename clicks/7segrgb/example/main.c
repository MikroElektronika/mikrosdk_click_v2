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
 * *note:* 
 * <pre>
 * Additional Functions :
 * void logic_one ( )  - Generic logic one function.
 * void logic_zero ( ) - Generic logic zero function.
 * void set_color ( uint8_t green, uint8_t red, uint8_t blue ) 
 *                     - Set the color of the  LSB segment of the display function.
 * void set_seven_segment ( uint8_t  character, uint8_t green_brightness, uint8_t red_brightness, uint8_t blue_brightness )
 *                     - Set whole character and color function.
 * </pre>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c7segrgb.h"

// ------------------------------------------------------------------ VARIABLES

static c7segrgb_t c7segrgb;
static log_t logger;

static sbit CS_BIT           at GPIOA_ODR.B4;
static sbit RGB_CONTROL_BIT  at GPIOD_ODR.B12;

static uint8_t CHARACTER_TABLE[ 10 ] = {
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

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void logic_one ( )
{
    RGB_CONTROL_BIT = 1;
    Delay_Cyc( c7segrgb_get_delay_value ( 5 ) );
    
    RGB_CONTROL_BIT = 0;
    Delay_Cyc( c7segrgb_get_delay_value ( 2 ) );
}

void logic_zero ( )
{
    RGB_CONTROL_BIT = 1;
    Delay_Cyc( c7segrgb_get_delay_value ( 2 ) );
    
    RGB_CONTROL_BIT = 0;
    Delay_Cyc( c7segrgb_get_delay_value ( 5 ) );
}

void set_color ( uint8_t green, uint8_t red, uint8_t blue )
{
    uint8_t tmp;
    int8_t cnt;

    for ( cnt = 7; cnt > -1; cnt-- )
    {
        tmp  = green >> cnt & 1;
        
        if ( tmp )
        {
            logic_one( );
        }
        else
        {
            logic_zero( );
        }
    }

    for ( cnt = 7; cnt > -1; cnt--  )
    {
        tmp = red >> cnt & 1;
        
        if ( tmp )
        {
            logic_one( );
        }
        else
        {
            logic_zero( );
        }
    }

    for ( cnt = 7; cnt > -1; cnt--  )
    {
        tmp = blue >> cnt & 1;
        
        if ( tmp )
        {
            logic_one( );
        }
        else
        {
            logic_zero( );
        }
    }
}

void set_seven_segment ( uint8_t  character, uint8_t green_brightness, uint8_t red_brightness, uint8_t blue_brightness )
{
    uint8_t tmp;
    uint8_t cnt;

    for ( cnt = 0; cnt < 8; cnt++ )
    {
        tmp = character >> cnt & 1;

        if ( tmp )
        {
            set_color( green_brightness, red_brightness, blue_brightness );
        }
        else
        {
            set_color( 0, 0, 0 );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c7segrgb_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c7segrgb_cfg_setup( &cfg );
    C7SEGRGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c7segrgb_init( &c7segrgb, &cfg );

    Delay_ms( 100 );
    RGB_CONTROL_BIT = 0;
    CS_BIT = 0;
}

void application_task ( void )
{
    uint8_t cnt_i;
    uint8_t cnt_j;
    
    for ( cnt_i = 0; cnt_i < 10; cnt_i++ )
    {
        for ( cnt_j = 10; cnt_j > 0; cnt_j-- )
        {
            set_seven_segment( CHARACTER_TABLE[ cnt_i ], 4 * cnt_i, 4 * cnt_j, cnt_i * cnt_j );
            Delay_ms( 100 );
        }
    }
    
    set_seven_segment( C7SEGRGB_POINT, 10, 10, 10 );
    Delay_ms( 1000 );
    
    set_seven_segment( C7SEGRGB_ZERO, 40, 40, 40 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_ONE, 40, 0, 0 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_TWO, 0, 40, 0 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_THREE, 0, 0, 40 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_FOUR, 40, 0, 40 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_FIVE, 0, 40, 40 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_SIX, 40, 40, 0 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_SEVEN, 20, 30, 40 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_EIGHT, 40, 15, 31 );
    Delay_ms( 1000 );

    set_seven_segment( C7SEGRGB_NINE, 20, 10, 30 );
    Delay_ms( 1000 );
     
    RGB_CONTROL_BIT = 0;
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
