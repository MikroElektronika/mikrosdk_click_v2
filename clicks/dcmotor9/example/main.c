/*!
 * \file main.c
 * \brief DC Motor 9 Click Example
 *
 * # Description
 * DC Motor 9 Click is a brushed DC motor driver with the current limiting and
 * current sensing. It can be operated by two logic signals, allowing to drive
 * the connected motor in two different ways:
 * it can use fixed logic levels for the direction control,
 * or it can be controlled by a PWM signal, offering an additional speed control
 * option.
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
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor9.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor9_t dcmotor9;
static log_t logger;

static float dcmotor9_duty_cycle;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void high_z ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " * Motor disconnected ( High-Z ) *\r\n" );
    dcmotor9_stop( &dcmotor9 );
    Delay_1sec( );
    Delay_1sec( );
}

static void pull_brake ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " * Pull break *\r\n" );
    dcmotor9_short_brake( &dcmotor9 );
    Delay_1sec( );
    Delay_1sec( );
}

static void clockwise ( )
{
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " * Clockwise *\r\n" );
    dcmotor9_clockwise( &dcmotor9 );

    for ( dcmotor9_duty_cycle = 1.0; dcmotor9_duty_cycle > 0; dcmotor9_duty_cycle -= 0.1 )
    {
        dcmotor9_set_duty_cycle ( &dcmotor9, dcmotor9_duty_cycle );
        log_printf( &logger," > " );
        Delay_ms( 200 );
    }
    
    log_printf( &logger, "\r\n" );
    
    for ( dcmotor9_duty_cycle = 0.1; dcmotor9_duty_cycle <= 1.0; dcmotor9_duty_cycle += 0.1 )
    {
        dcmotor9_set_duty_cycle ( &dcmotor9, dcmotor9_duty_cycle );
        log_printf( &logger," < " );
        Delay_ms( 200 );
    }
}

static void counter_clockwise ( )
{
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " * Counter clockwise *\r\n" );
    dcmotor9_counter_clockwise( &dcmotor9 );
    
    for ( dcmotor9_duty_cycle = 0.1; dcmotor9_duty_cycle <= 1.0; dcmotor9_duty_cycle += 0.1 )
    {
        dcmotor9_set_duty_cycle ( &dcmotor9, dcmotor9_duty_cycle );
        log_printf( &logger," > " );
        Delay_ms( 200 );
    }
    
    log_printf( &logger, "\r\n" );
    
    for ( dcmotor9_duty_cycle = 1.0; dcmotor9_duty_cycle > 0; dcmotor9_duty_cycle -= 0.1 )
    {
        dcmotor9_set_duty_cycle ( &dcmotor9, dcmotor9_duty_cycle );
        log_printf( &logger," < " );
        Delay_ms( 200 );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor9_cfg_t dcmotor9_cfg;

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

    dcmotor9_cfg_setup( &dcmotor9_cfg );
    DCMOTOR9_MAP_MIKROBUS( dcmotor9_cfg, MIKROBUS_1 );
    if ( dcmotor9_init( &dcmotor9, &dcmotor9_cfg ) == PWM_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }

    dcmotor9_pwm_start( &dcmotor9 );

    dcmotor9_enable( &dcmotor9 );
    Delay_ms( 1000 );
    log_info( &logger, "---- Application Init Done ----" );
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
