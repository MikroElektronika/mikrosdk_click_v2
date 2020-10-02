/*!
 * \file 
 * \brief VibroMotor Click example
 * 
 * # Description
 * This application contorl the speed of vibro motor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver and PWM.
 * Configures PWM to 20kHz frequency, calculates maximum duty ratio and starts PWM 
 * with duty ratio value 0.
 * 
 * ## Application Task  
 * Allows user to enter desired command to control
 * Vibro Motor Click board.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "vibromotor.h"

// ------------------------------------------------------------------ VARIABLES

static vibromotor_t vibromotor;
static log_t logger;

static float duty_cycle = 0.1;

void application_init ( void )
{
    log_cfg_t log_cfg;
    vibromotor_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    vibromotor_cfg_setup( &cfg );
    VIBROMOTOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vibromotor_init( &vibromotor, &cfg );

    vibromotor_pwm_start( &vibromotor );
}

void application_task ( void )
{
    //  Task implementation.
    
    if ( duty_cycle > 1 )
    {
        duty_cycle = 0;
    }
    
    vibromotor_set_duty_cycle ( &vibromotor, duty_cycle );
    duty_cycle += 0.1;
    Delay_100ms();
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
