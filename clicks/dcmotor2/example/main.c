/*!
 * \file 
 * \brief DcMotor2 Click example
 * 
 * # Description
 * This example showcases how to initialize and use the DC Motor 2 click. The click contains a 
 * Driver IC for DC motors which can spin the motor clockwise, counter-clockwise, break it and
 * completely stop the motor. The example needs a DC motor and a power supply in order to work.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function breaks the motor, starts spinning it clockwise and changes the rotation speed 
 * from min to max, breaks the motor again and spins it counter clockwise from max speed to min.
 * It waits for one second after each action. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor2.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor2_t dcmotor2;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void pull_brake ( )
{
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " * Pull break *\r\n" );
    dcmotor2_pull_brake( &dcmotor2 );
    Delay_1sec( );
}

static void clockwise ( )
{
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " * Clockwise *\r\n" );
    dcmotor2_spin_clockwise( &dcmotor2 );
    Delay_1sec( );

    for( duty_cycle = 500; duty_cycle < dcmotor2.pwm_period; duty_cycle += 250 )
    {
        dcmotor2_set_duty_cycle( &dcmotor2, duty_cycle );
        log_printf( &logger, "  >>>\r\n" );
        Delay_1sec( );
    }
}

static void counter_clockwise ( )
{
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " * Counter clockwise *\r\n" );
    dcmotor2_spin_counter_clockwise( &dcmotor2 );
    Delay_1sec( );

    for( duty_cycle = dcmotor2.pwm_period; duty_cycle > 500; duty_cycle -= 250 )
    {
        dcmotor2_set_duty_cycle( &dcmotor2, duty_cycle );
        log_printf( &logger, "  <<<\r\n" );
        Delay_1sec( );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    dcmotor2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_100ms( );

    //  Click initialization.

    dcmotor2_cfg_setup( &cfg );
    DCMOTOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_100ms( );
    dcmotor2_init( &dcmotor2, &cfg );
    dcmotor2_pwm_start( &dcmotor2 );
    Delay_1sec( );
}

void application_task ( )
{    
    if ( duty_cycle > dcmotor2.pwm_period )
    {
        duty_cycle = 0;
    }
    
    dcmotor2_enable_motor( &dcmotor2 );
    Delay_1sec( );
    
    pull_brake( );
    clockwise( );
    pull_brake( );
    counter_clockwise( );
    
    dcmotor2_stop_motor( &dcmotor2 );
    Delay_1sec( );
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
