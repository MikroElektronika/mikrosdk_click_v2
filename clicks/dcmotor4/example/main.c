/*!
 * \file 
 * \brief DcMotor4 Click example
 * 
 * # Description
 * The click is designed to run on either 3.3V or 5V power supply.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO,
   set the direction-control of the motor forward movement, PWM initialization,
   set PWM duty cycle and PWM frequency, enable the motor, start PWM.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of DC Motor 4 Click board.
   DC Motor 4 Click communicates with register via PWM.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor4.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor4_t dcmotor4;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void clockwise ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " * Clockwise *\r\n" );
    dcmotor4_run_clockwise( &dcmotor4 );
    Delay_1sec( );

    for ( duty_cycle = 0.1; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        dcmotor4_set_duty_cycle ( &dcmotor4, duty_cycle );
        log_printf( &logger," > " );
        Delay_ms( 500 );
    }
}

static void counter_clockwise ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " * Counter clockwise *\r\n" );
    dcmotor4_run_counter_clockwise( &dcmotor4 );
    Delay_1sec( );

    for ( duty_cycle = 1.0; duty_cycle > 0; duty_cycle -= 0.1 )
    {
        dcmotor4_set_duty_cycle ( &dcmotor4, duty_cycle );
        log_printf( &logger," < " );
        Delay_ms( 500 );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    dcmotor4_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_100ms();

    //  Click initialization.

    dcmotor4_cfg_setup( &cfg );
    DCMOTOR4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_100ms();
    dcmotor4_init( &dcmotor4, &cfg );
    dcmotor4_pwm_start( &dcmotor4 );
}

void application_task ( )
{  
    counter_clockwise( );
    
    clockwise( );
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
