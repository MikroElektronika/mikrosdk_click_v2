/*!
 * \file 
 * \brief Brushless Click example
 * 
 * # Description
 * This example showcases how to initialize and use the Brushless click. The click has a bru-
 * shless motor driver which controls the work of the motor through the BLDC terminal. In order
 * for this example to work a motor and a power supply are needed. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function drives the motor clockwise, starting from a low speed and slowly building up
 * towards the max duty cycle and after that drives it in a counter clockwise direction star-
 * ting at max speed and slowing down towards a slower pace. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless.h"

// ------------------------------------------------------------------ VARIABLES

static brushless_t brushless;
static log_t logger;

static float duty_cycle;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void clockwise ( )
{
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " * Clockwise *\r\n" );
    brushless_spin_clockwise( &brushless );
    Delay_1sec( );

    for( duty_cycle = 0.5; duty_cycle < 1; duty_cycle += 0.1 )
    {
        brushless_set_duty_cycle( &brushless, duty_cycle );
        log_printf( &logger, "  >>>\r\n" );
        Delay_1sec( );
    }
}

static void counter_clockwise ( )
{
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " * Counter clockwise *\r\n" );
    brushless_spin_counter_clockwise( &brushless );
    Delay_1sec( );

    for( duty_cycle = 1; duty_cycle > 0.5; duty_cycle -= 0.1 )
    {
        brushless_set_duty_cycle( &brushless, duty_cycle );
        log_printf( &logger, "  <<<\r\n" );
        Delay_1sec( );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    brushless_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_100ms( );

    //  Click initialization.

    brushless_cfg_setup( &cfg );
    BRUSHLESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_100ms( );
    brushless_init( &brushless, &cfg );
    brushless_pwm_start( &brushless );
    Delay_1sec( );
}

void application_task ( )
{    
    if ( duty_cycle > 1 )
    {
        duty_cycle = 0;
    }

    clockwise( );
    counter_clockwise( );
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
