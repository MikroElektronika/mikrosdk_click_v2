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
 * Controls the motor speed in both directions and logs all data on UART.
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

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void clockwise ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " *  Clockwise *\r\n" );
    stspin250_set_ph( &stspin250, 1 );
    Delay_1sec( );

    for ( duty_cycle = 0.1; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        stspin250_set_duty_cycle ( &stspin250, duty_cycle );
        log_printf( &logger," > " );
        Delay_ms( 500 );
    }
    log_printf( &logger,"\r\n" );
    
    for ( duty_cycle = 1.0; duty_cycle > 0; duty_cycle -= 0.1 )
    {
        stspin250_set_duty_cycle ( &stspin250, duty_cycle );
        log_printf( &logger," < " );
        Delay_ms( 500 );
    }
}

static void counter_clockwise ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " * Counter clockwise *\r\n" );
    stspin250_set_ph( &stspin250, 0 );
    Delay_1sec( );

    for ( duty_cycle = 0.1; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        stspin250_set_duty_cycle ( &stspin250, duty_cycle );
        log_printf( &logger," > " );
        Delay_ms( 500 );
    }
    log_printf( &logger,"\r\n" );
    
    for ( duty_cycle = 1.0; duty_cycle > 0; duty_cycle -= 0.1 )
    {
        stspin250_set_duty_cycle ( &stspin250, duty_cycle );
        log_printf( &logger," < " );
        Delay_ms( 500 );
    }
}

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
    clockwise( );
    
    counter_clockwise( );
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
