/*!
 * \file 
 * \brief Buzz Click example
 * 
 * # Description
 * Application demonstrates the use of  BUZZ Click board and SDK 2 on the exemple 
 * using two additional functions that are coded to play different melodies.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO and LOG structures, set PWM pin as ouput and start write log
 * Initialization driver enable's - GPIO and configures the appropriate MCU pin for sound generation
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of BUZZ Click board
 * 
 * # Additional Functions
 * melody1_play( void ) - first demo melody
 * melody2_play( void ) - second demo melody
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buzz.h"

// ------------------------------------------------------------------ VARIABLES

static buzz_t buzz;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void melody1_play( void )
{
    uint16_t melody[ 12 ] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, a, C };
    uint8_t beats[ 12 ]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 };
    int i;
     
    for ( i=0; i < 12; i++ )
    {
        buzz_play_sound( &buzz, melody[ i ], 1, beats[ i ] / 2 );
         Delay_ms( 50 );
    }     
}

void melody2_play( void )
{
    uint16_t melody[ 26 ] = { e, e, e, e, e, e, e, g, c, d, e, R, f, f, f, f, f, e, e, e, e, d, d, e, d, g };
    uint8_t beats[ 26 ] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2 };
    int i;
    
    for ( i=0; i < 12; i++ )
    {
        buzz_play_sound( &buzz, melody[ i ], 1, beats[ i ] * 2 );
         Delay_ms( 50 );
    }    
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buzz_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buzz_cfg_setup( &cfg );
    BUZZ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buzz_init( &buzz, &cfg );

    buzz_pwm_start( &buzz );
}

void application_task ( void )
{
   melody1_play( ); 
   Delay_1sec( );
   melody2_play( ); 
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
        Delay_1sec( );
    }
}


// ------------------------------------------------------------------------ END
