/*!
 * \file 
 * \brief VToHz2 Click example
 * 
 * # Description
 * This appliaction enables usage of a converter for analog voltage input signal into a pulse wave signal of a certain frequency.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and enables the click board.
 * 
 * ## Application Task  
 * Sets the output frequency by incrementing the pwm duty cycle from 0 to 100% in an infinite loop.
 * Results are being sent to USB UART terminal.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "vtohz2.h"

// ------------------------------------------------------------------ VARIABLES

static vtohz2_t vtohz2;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    vtohz2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    vtohz2_cfg_setup( &cfg );
    VTOHZ2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vtohz2_init( &vtohz2, &cfg );

    vtohz2_enable( &vtohz2, VTOHZ2_ENABLE );
    vtohz2_pwm_start( &vtohz2 );
}

void application_task ( void )
{
    for ( duty_cycle = 0; duty_cycle <= 1.0; duty_cycle += 0.01 )
    {
        vtohz2_set_duty_cycle ( &vtohz2, duty_cycle );
        log_printf( &logger," PWM Duty: %.2f%%\r\n", duty_cycle * 100 );
        Delay_ms( 100 );
    }
    log_printf( &logger, "------------------------------\r\n" );
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


