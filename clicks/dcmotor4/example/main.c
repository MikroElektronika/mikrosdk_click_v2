/*!
 * \file 
 * \brief DcMotor4 Click example
 * 
 * # Description
 * The click is designed to run on either 3.3V or 5V power supply.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO,
   set the direction-control of the motor forward movement, PWM initialization,
   set PWM duty cycle and PWM frequency, enable the motor, start PWM.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of DC Motor 4 Click board.
   DC Motor 4 Click communicates with register via PWM.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor4.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor4_t dcmotor4;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void clockwise ( )
{
    dcmotor4_enable_motor( &dcmotor4 );

    log_printf( &logger, " Run: Clockwise -> \r\n " );
    dcmotor4_run_clockwise( &dcmotor4 );

    for ( duty_cycle = 0; duty_cycle < dcmotor4.pwm_period; duty_cycle += 250 )
    {
        dcmotor4_set_duty_cycle( &dcmotor4, duty_cycle );
        log_printf( &logger, "  >  \r\n " );
        Delay_1sec();
    }

    dcmotor4_disable_motor( &dcmotor4 );
}

static void counter_clockwise ( )
{
    dcmotor4_enable_motor( &dcmotor4 );

    log_printf( &logger, " Run: Clockwise <- \r\n " );
    dcmotor4_run_counter_clockwise( &dcmotor4 );

    for ( duty_cycle = dcmotor4.pwm_period; duty_cycle > 0; duty_cycle -= 250 )
    {
        dcmotor4_set_duty_cycle( &dcmotor4, duty_cycle );
        log_printf( &logger, "  <  \r\n " );
        Delay_1sec();
    }

    dcmotor4_disable_motor( &dcmotor4 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    dcmotor4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_100ms();

    //  Click initialization.

    dcmotor4_cfg_setup( &cfg );
    DCMOTOR4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_100ms();
    dcmotor4_init( &dcmotor4, &cfg );

    dcmotor4_pwm_start( &dcmotor4 );
}

void application_task ( )
{  
    if ( duty_cycle > dcmotor4.pwm_period )
    {
        duty_cycle = 100;
    }
    
    clockwise( );

    counter_clockwise( );

    Delay_100ms( );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
