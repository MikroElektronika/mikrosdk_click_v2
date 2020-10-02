/*!
 * \file 
 * \brief IrBeacon Click example
 * 
 * # Description
 * This application sets the brightness on Leds.
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Enables GPIO and PWM, sets the frequency and duty cycle and enables PWM.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of IR Beacon Click board.
 * It shows how to enable the device and gradualy increase the duty cycle.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irbeacon.h"

// ------------------------------------------------------------------ VARIABLES

static irbeacon_t irbeacon;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    irbeacon_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    irbeacon_cfg_setup( &cfg );
    IRBEACON_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irbeacon_init( &irbeacon, &cfg );

    irbeacon_set_duty_cycle( &irbeacon, duty_cycle );
    irbeacon_pwm_start( &irbeacon );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    irbeacon_enable_mod( &irbeacon );
    
    for ( duty_cycle = 250; duty_cycle < 3000; duty_cycle += 250 )
    {
        irbeacon_set_duty_cycle( &irbeacon, duty_cycle );
        Delay_ms( 500 );
    }
    
    irbeacon_disable_mod( &irbeacon );
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
