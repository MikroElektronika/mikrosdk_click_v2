/*!
 * \file 
 * \brief Stspin250 Click example
 * 
 * # Description
 * This application enables usage of brushed DC motor driver with the current limiting and current sensing.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init, PWM init and enable device
 * 
 * ## Application Task  
 * Changes the PWM dutyCycle and controls the motor speed.
 * You can change the direction of the motor rotation by setting PH to 0 or 1.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "stspin250.h"

// ------------------------------------------------------------------ VARIABLES

static stspin250_t stspin250;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    stspin250_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    stspin250_cfg_setup( &cfg );
    STSPIN250_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stspin250_init( &stspin250, &cfg );

    stspin250_enable( &stspin250, STSPIN250_DEVICE_ENABLE );
    stspin250_set_duty_cycle ( &stspin250, duty_cycle );

    stspin250_pwm_start( &stspin250 );
}

void application_task ( void )
{
    //  Task implementation.

    duty_cycle += 0.1;
    stspin250_set_ph( &stspin250 ,0 );
    stspin250_set_duty_cycle ( &stspin250, duty_cycle );
    if ( duty_cycle > 1 )
    {
        duty_cycle = 0.1;
        stspin250_pwm_stop( &stspin250 );
        Delay_ms( 2000 );
        stspin250_pwm_start( &stspin250 );
    }
	stspin250_set_ph( &stspin250 ,1 );
    Delay_ms( 200 );

    Delay_100ms( );
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
