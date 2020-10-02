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
 * Initializes LOG, PWM pin as output, RST pin as input and CS pin as output
 * and initializes GPIO driver and ADC and PWM functionalities.
 *
 * ## Application Task
 * Performs PWM1 duty ratio changing and reads AN voltage value and print it via
 * USB UART terminal.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor9.h"

#define DCMOTOR9_PWM_DUTY_STEP  0.1

// ------------------------------------------------------------------ VARIABLES

static dcmotor9_t dcmotor9;
static log_t logger;

static float dcmotor9_duty_cycle;
static float dcmotor9_an_voltage;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor9_cfg_t dcmotor9_cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
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
    log_info( &logger, "---- Application Init Done ----" );

    dcmotor9_device_power_on( &dcmotor9 );
    dcmotor9_an_voltage = 0;

    Delay_ms( 1000 );
    log_info( &logger, "---- Application Program Running... ----" );
}

void application_task ( void )
{
    dcmotor9_pwm1_start( &dcmotor9 );
    dcmotor9_duty_cycle = DCMOTOR9_PWM_DUTY_PERCENT_10;

    log_printf( &logger, "\n PWM1 Duty Ratio Rising :\r\n\n" );

    while ( dcmotor9_duty_cycle <= DCMOTOR9_PWM_DUTY_PERCENT_100 )
    {
        dcmotor9_pwm1_set_duty_cycle( &dcmotor9, dcmotor9_duty_cycle );
        dcmotor9_duty_cycle += DCMOTOR9_PWM_DUTY_STEP;
        Delay_ms( 2000 );

        dcmotor9_read_an_voltage( &dcmotor9, &dcmotor9_an_voltage );
        log_printf( &logger, " AN Voltage [V] : %.2f\r\n", dcmotor9_an_voltage );
        Delay_ms( 1000 );
    }

    log_printf( &logger, "\n PWM1 Stopped :\r\n\n" );

    dcmotor9_pwm1_stop( &dcmotor9 );
    Delay_ms( 2000 );

    dcmotor9_read_an_voltage( &dcmotor9, &dcmotor9_an_voltage );
    log_printf( &logger, " AN Voltage [V] : %.2f\r\n", dcmotor9_an_voltage );
    Delay_ms( 1000 );
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
