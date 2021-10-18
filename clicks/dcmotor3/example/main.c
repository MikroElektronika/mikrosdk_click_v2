/*!
 * \file 
 * \brief DcMotor3 Click example
 * 
 * # Description
 * This click  has four operating modes: clockwise, counter-clockwise, short brake and stop. 
 * The operating mode is configured through IN1 and IN2 pins.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO,
 * PWM initialization, set PWM duty cycle and PWM frequency, start PWM, enable the engine, and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of DC Motor 3 Click board.
 * DC Motor 3 Click communicates with register via PWM interface.
 * It shows moving in the clockwise direction of rotation from slow to fast speed
 * and moving in the counter clockwise direction of rotation from fast to slow speed.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor3.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor3_t dcmotor3;
static log_t logger;

static float duty_cycle = 0.1;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor3_cfg_t cfg;

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

    //  Click initialization.

    dcmotor3_cfg_setup( &cfg );
    DCMOTOR3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor3_init( &dcmotor3, &cfg );

    dcmotor3_pwm_start( &dcmotor3 );
    Delay_1sec( );
    dcmotor3_enable( &dcmotor3 );
    Delay_1sec( );
}

void application_task ( void )
{
    log_printf( &logger, "   Brake the engine  \r\n" );
    dcmotor3_short_brake( &dcmotor3 );
    Delay_1sec();

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "      Clockwise      \r\n" );
    dcmotor3_clockwise( &dcmotor3 );
    Delay_1sec();

    for ( duty_cycle = 0.1; duty_cycle <  1; duty_cycle += 0.1 )
    {
        dcmotor3_set_duty_cycle ( &dcmotor3, duty_cycle );
        log_printf( &logger, " >" );
        Delay_1sec( );
    }

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   Brake the engine  \r\n" );
    dcmotor3_short_brake( &dcmotor3 );
    Delay_1sec( );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Counter Clockwise  \r\n" );
    dcmotor3_counter_clockwise( &dcmotor3 );
    Delay_1sec();

    for ( duty_cycle = 0.1; duty_cycle > 1; duty_cycle -= 0.1 )
    {
        dcmotor3_set_duty_cycle ( &dcmotor3, duty_cycle );
        log_printf( &logger, " <" );
        Delay_1sec( );
    }

    log_printf( &logger, "\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    dcmotor3_stop( &dcmotor3 );
    Delay_1sec();
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
