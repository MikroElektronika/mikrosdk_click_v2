/*!
 * \file 
 * \brief Brushless Click example
 * 
 * # Description
 * This example showcases how to initialize and use the Brushless click. The click has a bru-
 * shless motor driver which controls the work of the motor through the BLDC terminal. In order
 * for this example to work a motor and a power supply are needed. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function drives the motor in both directions increasing and decreasing the speed of the motor.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless.h"

// ------------------------------------------------------------------ VARIABLES

static brushless_t brushless;
static log_t logger;

static float duty_cycle;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void clockwise ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " * Clockwise *\r\n" );
    brushless_spin_clockwise( &brushless );
    Delay_1sec( );
    
    for( duty_cycle = 0.3; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        brushless_set_duty_cycle( &brushless, duty_cycle );
        log_printf( &logger, "  > " );
        Delay_1sec( );
    }
    log_printf( &logger, "\r\n" );
    
    for( duty_cycle = 1.0; duty_cycle > 0.2; duty_cycle -= 0.1 )
    {
        brushless_set_duty_cycle( &brushless, duty_cycle );
        log_printf( &logger, "  < " );
        Delay_1sec( );
    }
}

static void counter_clockwise ( )
{
    log_printf( &logger, "\r\n------------------------------\r\n" );
    log_printf( &logger, " * Counter clockwise *\r\n" );
    brushless_spin_counter_clockwise( &brushless );
    Delay_1sec( );

    for( duty_cycle = 0.3; duty_cycle <= 1.0; duty_cycle += 0.1 )
    {
        brushless_set_duty_cycle( &brushless, duty_cycle );
        log_printf( &logger, "  > " );
        Delay_1sec( );
    }
    log_printf( &logger, "\r\n" );
    
    for( duty_cycle = 1.0; duty_cycle > 0.2; duty_cycle -= 0.1 )
    {
        brushless_set_duty_cycle( &brushless, duty_cycle );
        log_printf( &logger, "  < " );
        Delay_1sec( );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    brushless_cfg_t cfg;

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
    Delay_100ms( );

    //  Click initialization.

    brushless_cfg_setup( &cfg );
    BRUSHLESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    Delay_100ms( );
    brushless_init( &brushless, &cfg );
    brushless_pwm_start( &brushless );
    Delay_1sec( );
}

void application_task ( )
{    
    clockwise( );
    counter_clockwise( );
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
