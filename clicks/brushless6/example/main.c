/*!
 * \file 
 * \brief Brushless6 Click example
 * 
 * # Description
 * Brushless 6 click is designed to drive a three-phase sensorless.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and the click board.
 * 
 * ## Application Task  
 * This function drives the motor in both directions increasing and decreasing the speed of the motor.
 * 
 * ## NOTE
 * The maximal PWM Clock frequency for this click board is 500 Hz. 
 * So, the user will need to decrease the MCU's main clock frequency in MCU Settings in order to get up-to 500 Hz PWM clock frequency.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless6.h"

// ------------------------------------------------------------------ VARIABLES

static brushless6_t brushless6;
static log_t logger;

static float duty_cycle;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void brushless6_calibration( )
{
    brushless6_pwm_start( &brushless6 );

    brushless6_set_duty_cycle( &brushless6, BRUSHLESS6_MIN_PWM_DC );
    Delay_1sec( );
    Delay_1sec( );
}

void brushless6_setings( )
{
    brushless6_set_duty_cycle( &brushless6, BRUSHLESS6_INIT_DC );
    Delay_1sec( );
    Delay_1sec( );
}

static void clockwise ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " * Clockwise *\r\n" );
    Delay_1sec( );
    
    for( duty_cycle = BRUSHLESS6_INIT_DC; duty_cycle > BRUSHLESS6_1MS_DC; duty_cycle -= BRUSHLESS6_PERIOD )
    {
        brushless6_set_duty_cycle( &brushless6, duty_cycle );
        log_printf( &logger, "  > " );
        Delay_1sec( );
    }
        
    log_printf( &logger, "\r\n" );
    
    for( duty_cycle = BRUSHLESS6_1MS_DC; duty_cycle < BRUSHLESS6_INIT_DC; duty_cycle += BRUSHLESS6_PERIOD )
    {
        brushless6_set_duty_cycle( &brushless6, duty_cycle );
        log_printf( &logger, "  < " );
        Delay_1sec( );
    }
}

static void counter_clockwise ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " * Counter clockwise *\r\n" );
    Delay_1sec( );

    for( duty_cycle = BRUSHLESS6_INIT_DC; duty_cycle < BRUSHLESS6_2MS_DC - BRUSHLESS6_PERIOD; duty_cycle += BRUSHLESS6_PERIOD )
    {
        brushless6_set_duty_cycle( &brushless6, duty_cycle );
        log_printf( &logger, "  > " );
        Delay_1sec( );
    }
    log_printf( &logger, "\r\n" );
    
    for( duty_cycle = BRUSHLESS6_2MS_DC - BRUSHLESS6_PERIOD; duty_cycle > BRUSHLESS6_INIT_DC; duty_cycle -= BRUSHLESS6_PERIOD )
    {
        brushless6_set_duty_cycle( &brushless6, duty_cycle );
        log_printf( &logger, "  < " );
        Delay_1sec( );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless6_cfg_t cfg;

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

    brushless6_cfg_setup( &cfg );
    BRUSHLESS6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless6_init( &brushless6, &cfg );
    brushless6_calibration( );
    brushless6_setings( );
}

void application_task ( void )
{
    clockwise( );
    counter_clockwise( );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
