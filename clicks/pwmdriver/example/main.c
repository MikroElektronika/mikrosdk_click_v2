/*!
 * \file 
 * \brief PwmDriver Click example
 * 
 * # Description
 * This application is controls the speed DC motors.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - GPIO, PWM initialization set PWM duty cycle and PWM frequency, start PWM, enable the engine, and start to write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of PWM driver Click board.
 * 
 * *note:* 
 * <NOTE>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pwmdriver.h"

// ------------------------------------------------------------------ VARIABLES

static pwmdriver_t pwmdriver;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwmdriver_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pwmdriver_cfg_setup( &cfg );
    PWMDRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwmdriver_init( &pwmdriver, &cfg );

    pwmdriver_pwm_start( &pwmdriver );

    Delay_100ms( );
    
    log_printf( &logger, "   Initialization PWM  \r\n  " );
    pwmdriver_set_duty_cycle( &pwmdriver, duty_cycle );
    pwmdriver_pwm_start( &pwmdriver );
    Delay_1sec( );
    log_printf( &logger, "------------------------- \r\n  " );
}

void application_task ( void )
{
    //  Task implementation.
    
    if ( duty_cycle > 1 )
    {
        duty_cycle = 0.1;
    }
    
    pwmdriver_set_duty_cycle ( &pwmdriver, duty_cycle );
    duty_cycle += 0.1;
    Delay_100ms();

    log_printf( &logger," Light Intensity Rising  \r\n  " );
    Delay_1sec( );

    for ( duty_cycle = 5; duty_cycle < 255; duty_cycle += 25 )
    {
        pwmdriver_set_duty_cycle( &pwmdriver,duty_cycle );
        log_printf( &logger," >  \r\n " );
        Delay_1sec( );
    }

    log_printf( &logger,"-------------------------  \r\n " );
    log_printf( &logger," Light Intensity Falling  \r\n " );
    Delay_1sec( );

    for ( duty_cycle = 255; duty_cycle > 5; duty_cycle -= 25 )
    {
        pwmdriver_set_duty_cycle( &pwmdriver,duty_cycle );
        log_printf( &logger," <  \r\n " );
        Delay_1sec( );
    }

    log_printf( &logger,"   \r\n " );
    log_printf( &logger,"---------------------  \r\n " );
    Delay_1sec( );

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
