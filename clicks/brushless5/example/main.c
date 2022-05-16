/*!
 * @file 
 * @brief Brushless5 Click example
 * 
 * # Description
 * This library contains an API for the Brushless5 Click driver.
 * This example showcases how to initialize and use the Brushless 5 click. 
 * The click has a brushless 5 motor driver which controls the work 
 * of the motor through the BLDC terminal. 
 * In order for this example to work a motor and a power supply are needed.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the GPIO driver and configures the PWM peripheral for 
 * controlling the speed of the motor.
 * 
 * ## Application Task
 * This is an example that demonstrates the use of a Brushless 5 Click board.
 * Brushless 5 Click communicates with the register via the PWM interface.  
 * Increases and decreasing the speed of the motor demonstrate speed control.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless5.h"

// ------------------------------------------------------------------ VARIABLES

static brushless5_t brushless5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless5_cfg_t cfg;

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
    Delay_ms( 100 );

    //  Click initialization.

    brushless5_cfg_setup( &cfg );
    BRUSHLESS5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless5_init( &brushless5, &cfg );
    Delay_ms( 100 );
    
    brushless5_set_duty_cycle ( &brushless5, 0.0 );
    brushless5_pwm_start( &brushless5 );
    log_info( &logger, "---- Application Task ----" );
    Delay_ms( 1000 );
}

void application_task ( void )
{    
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    brushless5_set_duty_cycle ( &brushless5, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
        log_printf( &logger, " Slowing down... \r\n" );
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        log_printf( &logger, " Increasing the motor speed... \r\n" );
    }
    duty_cnt += duty_inc;
    Delay_ms( 500 );
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
