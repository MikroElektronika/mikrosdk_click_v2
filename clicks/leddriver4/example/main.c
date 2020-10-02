/*!
 * \file 
 * \brief LedDriver4 Click example
 * 
 * # Description
 * This click has the ability to dim the connected LED array, without producing any noise on the output.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the GPIO driver and
 * configures the PWM peripheral for controlling the LED array intensity.
 * 
 * ## Application Task  
 * Increases and decreases LED array intensity
 * ( firts increases light intensity to the maximum and than decreases to the minimum ).
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "leddriver4.h"

// ------------------------------------------------------------------ VARIABLES

static leddriver4_t leddriver4;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    leddriver4_cfg_setup( &cfg );
    LEDDRIVER4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver4_init( &leddriver4, &cfg );

    leddriver4_pwm_start( &leddriver4 );
}

void application_task ( void )
{
    for ( duty_cycle = 0; duty_cycle < leddriver4.pwm_period;  )
    {
        leddriver4_set_duty_cycle( &leddriver4, duty_cycle );
        Delay_ms( 20 );
        if ( duty_cycle > ( leddriver4.pwm_period - 10 ) )
        {
            break;
        }
        else
        {
            duty_cycle += 50;
        }
    }

    for ( duty_cycle = leddriver4.pwm_period; duty_cycle > 0;  )
    {
        leddriver4_set_duty_cycle( &leddriver4, duty_cycle );
        Delay_ms( 20 );
        if ( duty_cycle < 10 )
        {
            break;
        }
        else
        {
            duty_cycle -= 50;
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
