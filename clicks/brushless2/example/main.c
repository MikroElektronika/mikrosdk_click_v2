/*!
 * \file 
 * \brief Brushless2 Click example
 * 
 * # Description
 * This application controlled speed motor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO,
 * PWM initialization, set PWM duty cycle and PWM frequency, start PWM, enable the engine, 
 * and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Brushless 2 Click board.
 * Brushless 2 Click communicates with register via PWM interface.
 * It acceleration and slowing down in the counter clockwise direction of rotation ( CCW ).
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless2.h"

// ------------------------------------------------------------------ VARIABLES

static brushless2_t brushless2;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    brushless2_cfg_setup( &cfg );
    BRUSHLESS2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless2_init( &brushless2, &cfg );

    brushless2_set_duty_cycle( &brushless2, duty_cycle );
    brushless2_pwm_start( &brushless2 );
    Delay_1sec( );
    log_printf( &logger, "--------------------- \r\n" );
}

void application_task ( void )
{
    int32_t temp;
    
    brushless2_counter_clockwise( &brushless2 );

    log_printf( &logger, "  Counterclockwise    \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
    log_printf( &logger, "    acceleration      \r\n" );
    Delay_1sec( );
    
    for ( duty_cycle = 10; duty_cycle < brushless2.pwm_period; duty_cycle += 50 )
    {
        brushless2_set_duty_cycle ( &brushless2, duty_cycle );
        log_printf( &logger," > \r\n" );
        //Delay_1sec( );
        //Delay_1sec( );
        //Delay_1sec( );
    }

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    slowing down     \r\n" );
    Delay_1sec( );

    temp = brushless2.pwm_period;
    
    for ( duty_cycle = temp; duty_cycle > 10; duty_cycle -= 50 )
    {
        brushless2_set_duty_cycle ( &brushless2, duty_cycle );
        log_printf( &logger," < \r\n" );
        //Delay_1sec( );
        //Delay_1sec( );
        //Delay_1sec( );
    }

    log_printf( &logger,  "--------------------- \r\n" ); 
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
