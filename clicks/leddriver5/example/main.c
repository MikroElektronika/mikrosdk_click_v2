/*!
 * \file 
 * \brief LedDriver5 Click example
 * 
 * # Description
 * The application is a capable of driving an array of high-power LEDs. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and pwm init
 * 
 * ## Application Task  
 * Controls the brightness of the LED using PWM
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "leddriver5.h"

// ------------------------------------------------------------------ VARIABLES

static leddriver5_t leddriver5;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    leddriver5_cfg_setup( &cfg );
    LEDDRIVER5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver5_init( &leddriver5, &cfg );

    leddriver5_pwm_start( &leddriver5 );
}

void application_task ( void )
{
    for ( duty_cycle = 0.1; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        leddriver5_set_duty_cycle ( &leddriver5, duty_cycle );
        Delay_ms( 500 );
    }
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
