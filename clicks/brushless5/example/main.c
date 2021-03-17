/*!
 * \file 
 * \brief Brushless5 Click example
 * 
 * # Description
 * This application demonstrates the use of Brushless 5 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the GPIO driver and configures the PWM peripheral for 
 * controlling the speed of the motor.
 * 
 * ## Application Task  
 * Increases and decreases the speed of the motor demonstrating the speed control.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless5.h"

// ------------------------------------------------------------------ VARIABLES

static brushless5_t brushless5;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    brushless5_cfg_setup( &cfg );
    BRUSHLESS5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless5_init( &brushless5, &cfg );

    brushless5_pwm_start( &brushless5 );
}

void application_task ( void )
{    
    log_printf( &logger, " Increasing the motor speed... \r\n" );
    
    for ( duty_cycle = 0.1; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        brushless5_set_duty_cycle ( &brushless5, duty_cycle );
        log_printf( &logger," > " );
        Delay_ms( 500 );
    }

    log_printf( &logger,  "\r\n ---------------------- \r\n" ); 
    log_printf( &logger, " Slowing down... \r\n" );
    
    for ( duty_cycle = 1.0; duty_cycle > 0.09; duty_cycle -= 0.1 )
    {
        brushless5_set_duty_cycle ( &brushless5, duty_cycle );
        log_printf( &logger," < " );
        Delay_ms( 500 );
    }
    log_printf( &logger,  "\r\n ---------------------- \r\n" ); 
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
