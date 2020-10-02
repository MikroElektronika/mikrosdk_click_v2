/*!
 * \file 
 * \brief 4x4 RGB Click example
 * 
 * # Description
 * This application is used for powering 4x4 RGB LED matrices.
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
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c4x4rgb.h"

// ------------------------------------------------------------------ VARIABLES

static c4x4rgb_t c4x4rgb;
static log_t logger;
static uint8_t s_speed;
static uint32_t diode_array[ 16 ];
static uint32_t temp_color;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void c4x4rgb_init_diode ( uint32_t a_rgb_color, uint32_t *a_diode_array )
{
    *a_diode_array = ( a_rgb_color & 0x000000FF ) | ( ( a_rgb_color >> 16 ) << 8 ) | ( ( a_rgb_color >> 8 ) << 16 );
}

void c4x4rgb_set_color ( uint32_t *a_diode_array )
{
    int8_t cnt_i;
    uint32_t tmp;

    tmp = 1;

    for ( cnt_i = 23; cnt_i >= 0; cnt_i-- )
    {
        if ( ( ( *a_diode_array ) & ( tmp << cnt_i ) ) == 0 )
        {
            c4x4rgb_logic_zero( &c4x4rgb );
        }
        else
        {
            c4x4rgb_logic_one( &c4x4rgb );
        }
    }
}

void c4x4rgb_set_diode ( int8_t a_num, uint32_t a_color, uint32_t *a_diode_array )
{
    int8_t cnt_i;

    for ( cnt_i = 0; cnt_i < 16; cnt_i++ )
    {
        if ( cnt_i == ( a_num - 1 ) )
        {
            c4x4rgb_init_diode( a_color, &a_diode_array[ cnt_i ] );
            c4x4rgb_set_color( &a_diode_array[ cnt_i ] );
        }
        else
        {
            c4x4rgb_set_color( &a_diode_array[ cnt_i ] );
        }
    }

    c4x4rgb_delay( 60, 'm' ); // reset delay
}

void c4x4rgb_delay_time ( )
{
    uint16_t cnt_j;

    for ( cnt_j=1; cnt_j <= s_speed; cnt_j++ )
    {
        Delay_ms( 5 );
    }
}

void c4x4rgb_snake ( )
{
    c4x4rgb_set_diode( 4, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 3, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 2, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 1, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 5, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 9, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 13, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 14, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 15, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 16, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 12, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 8, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 7, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 6, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 10, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 11, temp_color, diode_array );
}

void c4x4rgb_snake_return ( )
{
    c4x4rgb_set_diode( 11, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 10, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 6, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 7, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 8, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 12, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 16, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 15, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 14, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 13, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 9, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 5, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 1, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 2, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 3, temp_color, diode_array );
    c4x4rgb_delay_time( );
    c4x4rgb_set_diode( 4, temp_color, diode_array );
    c4x4rgb_delay_time( );
}

void c4x4rgb_fill_screen ( )
{
    int8_t cnt_i;

    for ( cnt_i = 1 ; cnt_i <= 16; cnt_i++ )
    {
        c4x4rgb_set_diode( cnt_i, temp_color, diode_array );
        c4x4rgb_delay_time( );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c4x4rgb_cfg_t cfg;
    
    unsigned long clk;
    float one_cyc;
    uint8_t tmp;
    float first_delay;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    c4x4rgb_cfg_setup( &cfg );
    C4X4RGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4x4rgb_init( &c4x4rgb, &cfg );

    log_printf( &logger, "  GPIO Driver Init   \r\n" );
    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, " Fill Screen speed:  \r\n" );
    log_printf( &logger, "  25 x 5 ms = 125 ms \r\n" );
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "      ~ White ~      \r\n" );
    
    s_speed = 25;
    temp_color = C4X4RGB_COLOR_WHITE;
    c4x4rgb_fill_screen( );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    log_printf( &logger, "   Set snake speed:  \r\n" );
    log_printf( &logger, "  20 x 5 ms = 100 ms \r\n" );
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "      ~ Blue ~      \r\n" );
    s_speed = 20;
    temp_color = C4X4RGB_COLOR_BLUE;
    c4x4rgb_snake( );
    log_printf( &logger, "---------------------\r\n" );
    
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "   ~ Light Blue ~    \r\n" );
    temp_color = C4X4RGB_COLOR_LIGHT_BLUE;
    c4x4rgb_snake_return( );
    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, "   Set snake speed:  \r\n" );
    log_printf( &logger, "  15 x 5 ms = 75 ms  \r\n" );
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "      ~ Green ~      \r\n" );
    s_speed = 15;
    temp_color = C4X4RGB_COLOR_GREEN;
    c4x4rgb_snake( );
    log_printf( &logger, "---------------------\r\n" );
    
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "     ~ Yellow ~      \r\n" );
    temp_color = C4X4RGB_COLOR_YELLOW;
    c4x4rgb_snake_return( );
    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, "   Set snake speed:  \r\n" );
    log_printf( &logger, "  10 x 5 ms = 50 ms  \r\n" );
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "       ~ Red ~       \r\n" );
    s_speed = 10;
    temp_color = C4X4RGB_COLOR_RED;
    c4x4rgb_snake( );
    log_printf( &logger, "---------------------\r\n" );
    
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "     ~ Purpule ~     \r\n" );
    temp_color = C4X4RGB_COLOR_PURPLE;
    c4x4rgb_snake_return( );
    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, " Fill Screen speed:  \r\n" );
    log_printf( &logger, "  5 x 5 ms = 25 ms   \r\n" );
    log_printf( &logger, "   Set diode color   \r\n" );
    log_printf( &logger, "      ~ White ~      \r\n" );
    s_speed = 5;
    temp_color = C4X4RGB_COLOR_WHITE;
    c4x4rgb_fill_screen( );
    log_printf( &logger, "---------------------\r\n" );
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
