/*!
 * \file 
 * \brief Brushless6 Click example
 * 
 * # Description
 * Brushless 6 click is designed to drive a three-phase sensorless.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Intializes PWM module but also and Brushless click by executing intialization prodecure.
 * 
 * ## Application Task  
 * Periodicaly changes the motor speed using PWM module but also log current setting to UART.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless6.h"

// ------------------------------------------------------------------ VARIABLES

static brushless6_t brushless6;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void brushless6_calibration( )
{
    brushless6_pwm_start( &brushless6 );
    brushless6_set_duty_cycle( &brushless6, BRUSHLESS6_MAX_PWM_DC );
    Delay_ms( 2000 );

    brushless6_set_duty_cycle( &brushless6, BRUSHLESS6_MIN_PWM_DC );
    Delay_ms( 2000 );
}

void brushless6_setings( )
{
    brushless6_set_duty_cycle( &brushless6, BRUSHLESS6_INIT );
    Delay_ms( 2000 );
}

void brushless6_set_motor( const uint16_t setting )
{
    brushless6_set_duty_cycle( &brushless6, setting );
    Delay_ms( 100 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    brushless6_cfg_setup( &cfg );
    BRUSHLESS6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless6_init( &brushless6, &cfg );

    brushless6_pwm_start( &brushless6 );

}

void application_task ( void )
{
    //  Task implementation.
    
    if ( duty_cycle > brushless6.pwm_period )
    {
        duty_cycle = 100;
    }
    
    brushless6_set_duty_cycle ( &brushless6, duty_cycle );
    duty_cycle += 50;
    Delay_100ms();

    brushless6_set_motor( BRUSHLESS6_SPEED1 );
    log_printf( &logger, " Speed 1 \r\n" );
    log_printf( &logger, " 13 \r\n" );
    log_printf( &logger, " 10 \r\n" );
    Delay_ms( 1000 );
  

    brushless6_set_motor( BRUSHLESS6_CCW );
    log_printf( &logger, "Direction change \r\n" );
    log_printf( &logger, "13 \r\n" );
    log_printf( &logger, "10 \r\n" );
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
