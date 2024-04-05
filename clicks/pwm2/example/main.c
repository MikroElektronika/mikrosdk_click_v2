/*!
 * \file 
 * \brief Pwm2 Click example
 * 
 * # Description
 * This application send the PWM signal in one or more outputs.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configures the click board and sets all PWM channels on the click board to
 * 50% duty cycle with the phase shift enabled.
 * 
 * ## Application Task  
 * The first 10 PWM channels of PWM2 Click board are switched back and forth 
 * from 25% duty cycle to 75% duty cycle every 10 seconds.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "pwm2.h"

// ------------------------------------------------------------------ VARIABLES

static pwm2_t pwm2;
 
void application_init ( void )
{
    pwm2_cfg_t cfg;

    //  Click initialization.

    pwm2_cfg_setup( &cfg );
    PWM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwm2_init( &pwm2, &cfg );
    
    pwm2_set_duty_cycle( &pwm2, 0.5 );
    pwm2_pwm_start( &pwm2 );

    pwm2_default_cfg( &pwm2 );
    pwm2_toggle_phase_shift( &pwm2 );

    //setting all 48 PWM channels of the PWM2 click to 50% duty
    for( uint8_t cnt = 1; cnt < 49; cnt++ ) 
    {
        pwm2_set_channel( &pwm2, cnt, PWM2_50_PERCENT_DUTY, PWM2_NO_CORRECTION );
    }
}

void application_task ( void )
{
    for ( uint8_t cnt = 1; cnt < 10; cnt++ )
    { 
        pwm2_set_channel( &pwm2, cnt, PWM2_25_PERCENT_DUTY, PWM2_NO_CORRECTION );
    }
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    for ( uint8_t cnt = 1; cnt < 10; cnt++ )
    { 
        pwm2_set_channel( &pwm2, cnt, PWM2_75_PERCENT_DUTY, PWM2_NO_CORRECTION );
    }
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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


// ------------------------------------------------------------------------ END
