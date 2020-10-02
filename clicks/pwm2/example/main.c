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
 * PWMCK signal is set to 15mhz and to give a 50% duty
 * cycle. The PWM2 click channels are initialized to 75% duty cycle,
 * and the phase shift is toggled on.
 * 
 * ## Application Task  
 * The first 10 PWM2 click channels are
 * switched back and forth from 25% duty cycle to 100% duty cycle every second.
 *
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pwm2.h"

// ------------------------------------------------------------------ VARIABLES

static pwm2_t pwm2;
static log_t logger;

static float duty_cycle = 0.5;
static uint8_t duty_mode;
 
void application_init ( void )
{
    uint8_t i;

    log_cfg_t log_cfg;
    pwm2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pwm2_cfg_setup( &cfg );
    PWM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwm2_init( &pwm2, &cfg );
    
    pwm2_set_duty_cycle( &pwm2, duty_cycle );
    pwm2_pwm_start( &pwm2 );
    duty_mode=1;

    pwm2_inits( &pwm2 );
    //setting all 48 PWM2 channels  on the PWM2 click to 75% duty
    for( i = 1; i < 49; i++ ) 
    {
        pwm2_set_channel( &pwm2, i, PWM2_75_PERCENT_DUTY, PWM2_NO_CORRECTION );
    }
    pwm2_toggle_phase_shift( &pwm2 );
}

void application_task ( void )
{
         uint8_t i;
    //  Task implementation.
    
    if ( duty_cycle > 1 )
    {
        duty_cycle = 0.1;
    }

    for ( i = 1; i < 10; i++ )
    { 
        if ( duty_mode != 0 )
        {
            pwm2_set_channel( &pwm2, i, PWM2_25_PERCENT_DUTY, PWM2_NO_CORRECTION );
            duty_mode = 0;
        }
        else
        {
            pwm2_set_channel( &pwm2, i, PWM2_100_PERCENT_DUTY, PWM2_NO_CORRECTION );
            duty_mode = 1;
        }
    }
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
