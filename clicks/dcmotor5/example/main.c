/*!
 * \file 
 * \brief DcMotor5 Click example
 * 
 * # Description
 * This application enables usage of brushed DC motor gate driver.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO, PWM and logger and enables the click board.
 * 
 * ## Application Task  
 * This function drives the motor in both directions increasing and decreasing the speed of the motor.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor5.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor5_t dcmotor5;
static log_t logger;

static float duty_cycle = 0.1;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void high_z ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " * Motor disconnected ( High-Z ) *\r\n" );
    dcmotor5_stop( &dcmotor5 );
    Delay_1sec( );
    Delay_1sec( );
}

static void pull_brake ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " * Pull break *\r\n" );
    dcmotor5_short_brake( &dcmotor5 );
    Delay_1sec( );
    Delay_1sec( );
}

static void clockwise ( )
{
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " * Clockwise *\r\n" );
    dcmotor5_clockwise( &dcmotor5 );

    for ( duty_cycle = 1.0; duty_cycle > 0; duty_cycle -= 0.1 )
    {
        dcmotor5_set_duty_cycle ( &dcmotor5, duty_cycle );
        log_printf( &logger," > " );
        Delay_ms( 200 );
    }
    
    log_printf( &logger, "\r\n" );
    
    for ( duty_cycle = 0.1; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        dcmotor5_set_duty_cycle ( &dcmotor5, duty_cycle );
        log_printf( &logger," < " );
        Delay_ms( 200 );
    }
}

static void counter_clockwise ( )
{
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " * Counter clockwise *\r\n" );
    dcmotor5_counter_clockwise( &dcmotor5 );
    
    for ( duty_cycle = 0.1; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        dcmotor5_set_duty_cycle ( &dcmotor5, duty_cycle );
        log_printf( &logger," > " );
        Delay_ms( 200 );
    }
    
    log_printf( &logger, "\r\n" );
    
    for ( duty_cycle = 1.0; duty_cycle > 0; duty_cycle -= 0.1 )
    {
        dcmotor5_set_duty_cycle ( &dcmotor5, duty_cycle );
        log_printf( &logger," < " );
        Delay_ms( 200 );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor5_cfg_setup( &cfg );
    DCMOTOR5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor5_init( &dcmotor5, &cfg );

    dcmotor5_pwm_start( &dcmotor5 );

    dcmotor5_enable( &dcmotor5 );

    Delay_1sec( );
}

void application_task ( void )
{
    clockwise( );
    pull_brake( );
    counter_clockwise( );
    high_z( );
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
