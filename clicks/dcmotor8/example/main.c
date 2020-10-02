/*!
 * \file 
 * \brief DcMotor8 Click example
 * 
 * # Description
 * This click can drive simple DC motors with brushes, providing them with a significant amount 
 * of current and voltage up to 40V. The click has one control input, that uses the PWM signal 
 * from the host MCU. It uses the half-bridge topology to regulate the speed of the motor 
 * rotation, employs advanced dead-time circuitry that monitors the output stage, providing 
 * maximum switching efficiency and features an advanced technique to avoid shoot-through 
 * currents.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes click driver.
 * 
 * ## Application Task  
 * Sets frequency and current duty of PWM Timer and decides will motor be stoped
 * and when. Also makes decide when motor will be started again.
 * 
 * ## Additional Functions :
 * - void set_freq ( uint16_t _freq, uint16_t _step )  
 *     @description: Function sets frequency and current duty for PWM Timer.
 *
 * - void start_motor ( uint16_t delay_time_stop, uint16_t delay_time_stop, uint8_t stop_enable )
 *     @description: Function sets delay time witch decides when motor will be stoped and started
 *              again. If stop_enable is 1 the motor will be stoped, and if 0 will be not stoped.
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dcmotor8.h"

// ------------------------------------------------------------------ VARIABLES

static dcmotor8_t dcmotor8;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void set_freq ( uint16_t freq, float step )
{
    pwm_set_freq( &dcmotor8.pwm, freq );
    
    if ( duty_cycle > 1 )
    {
        duty_cycle = 0.1;
    }
    
    dcmotor8_set_duty_cycle ( &dcmotor8, duty_cycle );
    duty_cycle += step;
}

void start_motor ( uint16_t delay_time_stop, uint16_t delay_time_start, uint8_t stop_enable )
{
    uint8_t i;

    dcmotor8_pwm_start( &dcmotor8 );
    if ( stop_enable == 1 )
    {
        for ( i = 0; i < delay_time_stop; i++ )
        {
            Delay_ms( 2000 );
        }
                
        dcmotor8_pwm_stop( &dcmotor8 );
        for ( i = 0; i < delay_time_start; i++ )
        {
            Delay_ms( 2000 );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor8_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor8_cfg_setup( &cfg );
    DCMOTOR8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor8_init( &dcmotor8, &cfg );

    dcmotor8_pwm_start( &dcmotor8 );
}

void application_task ( void )
{
    set_freq( DCMOTOR8_20KHZ, 0.1 );

    start_motor( DCMOTOR8_DELAY_20SEC, DCMOTOR8_DELAY_4SEC, DCMOTOR8_STOP_ENABLE );

    log_printf( &logger, "Maximal motor duty ratio is: %f \r\n", duty_cycle );
    
    Delay_ms( 100 );
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
