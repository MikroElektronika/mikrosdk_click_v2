/*!
 * \file 
 * \brief DcMotor5 Click example
 * 
 * # Description
 * This applciation enables usage of brushed DC motor gate driver.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO,
 * PWM initialization, set PWM duty cycle and PWM frequency, start PWM, enable the engine, and start write log.
 * 
 * ## Application Task  
 *  This is a example which demonstrates the use of DC Motor 5 Click board. 
 *  DC Motor 5 Click communicates with register via PWM interface. 
 *  It shows moving in the clockwise direction of rotation from slow to fast speed
 *  and moving in the counter clockwise direction of rotation from fast to slow speed.
 *  Results are being sent to the Usart Terminal where you can track their changes.
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

    log_printf( &logger, "---------------------\r\n" );

    log_printf( &logger, "  Enable the engine  \r\n" );

    dcmotor5_enable( &dcmotor5 );

   Delay_ms( 1000);

    log_printf( &logger, "---------------------\r\n" );
}

void application_task ( void )
{
    //  Task implementation.
  
    log_printf( &logger, "   Brake the engine  \r\n" );
    dcmotor5_short_brake( &dcmotor5 );
    Delay_ms( 1000);

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "      Clockwise      \r\n" );
    dcmotor5_clockwise( &dcmotor5 );
    Delay_ms( 1000);

    for ( duty_cycle = 0.1; duty_cycle < 1; duty_cycle += 0.1 )
    {
        dcmotor5_set_duty_cycle( &dcmotor5, duty_cycle );
        log_printf( &logger, " >" );
        Delay_ms( 1000);
    }

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   Brake the engine  \r\n" );
    dcmotor5_short_brake( &dcmotor5 );
    Delay_ms( 1000);

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Counter Clockwise  \r\n" );
    dcmotor5_counter_clockwise( &dcmotor5 );
    Delay_ms( 1000);

    for ( duty_cycle = 1; duty_cycle >0.1; duty_cycle -= 0.1 )
    {
        dcmotor5_set_duty_cycle( &dcmotor5, duty_cycle );
        log_printf( &logger, " <" );
        Delay_ms( 1000);
    }

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    dcmotor5_stop( &dcmotor5 );
   Delay_ms( 1000);

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
