/*!
 * \file 
 * \brief Brushless 4 Click example
 * 
 * # Description
 * This click has many features for driving a wide range of small to medium BLDC motors.
 * It provides the rotor position digital output, via the FG pin, routed to the mikroBUS INT pin. 
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the GPIO driver 
 * and configures the PWM peripheral for controlling the speed of the motor.
 * 
 * ## Application Task  
 * Increases and decreases the speed of the motor
 * demonstrating the speed controll.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless4.h"

// ------------------------------------------------------------------ VARIABLES

static brushless4_t brushless4;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void set_speed ( uint16_t speed )
{
    brushless4_set_duty_cycle( &brushless4, duty_cycle );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    brushless4_cfg_setup( &cfg );
    BRUSHLESS4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless4_init( &brushless4, &cfg );

    brushless4_pwm_start( &brushless4 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    for ( duty_cycle = 0; duty_cycle < brushless4.pwm_period;  )
    {
        brushless4_set_duty_cycle( &brushless4, duty_cycle );
        Delay_ms( 20 );
        if ( duty_cycle > ( brushless4.pwm_period - 10 ) )
        {
            break;
        }
        else
        {
            duty_cycle += 10;
        }
    }

    for ( duty_cycle = brushless4.pwm_period; duty_cycle > 0;  )
    {
        brushless4_set_duty_cycle( &brushless4, duty_cycle );
        Delay_ms( 20 );
        if ( duty_cycle < 10 )
        {
            break;
        }
        else
        {
            duty_cycle -= 10;
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
