/*!
 * @file 
 * @brief PwmDriver Click example
 * 
 * # Description
 * This application is controls the speed DC motors.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - GPIO, PWM initialization set PWM duty cycle and PWM frequency,
 * start PWM, enable the engine, and start to write log.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the PWM driver Click board.
 * This example shows the automatic control of PWM,
 * the first increases duty cycle and then the duty cycle is falling.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * *note:* 
 * EXT PWR 3-30VDC
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pwmdriver.h"

// ------------------------------------------------------------------ VARIABLES

static pwmdriver_t pwmdriver;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pwmdriver_cfg_t cfg;

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

    pwmdriver_cfg_setup( &cfg );
    PWMDRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pwmdriver_init( &pwmdriver, &cfg );
    Delay_ms( 100 );
    
    log_printf( &logger, "   Initialization PWM  \r\n  " );
    pwmdriver_set_duty_cycle( &pwmdriver, 0.0 );
    pwmdriver_pwm_start( &pwmdriver );
    Delay_ms( 1000 );
    log_info( &logger, "---- Application Task ----" );
}

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    pwmdriver_set_duty_cycle ( &pwmdriver, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
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
