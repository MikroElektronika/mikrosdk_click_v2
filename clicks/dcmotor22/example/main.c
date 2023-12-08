/*!
 * @file main.c
 * @brief DC Motor 22 Click Example.
 *
 * # Description
 * This example demonstrates the use of DC Motor 22 click board by controlling the speed
 * of both motors over PWM duty cycle as well as displaying the motors current consumption.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Controls the motor speed by changing the PWM duty cycle every 5 seconds, and displays
 * the motors current consumption. The duty cycle ranges from -100% to +100%. 
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor22.h"

static dcmotor22_t dcmotor22;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor22_cfg_t dcmotor22_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    dcmotor22_cfg_setup( &dcmotor22_cfg );
    DCMOTOR22_MAP_MIKROBUS( dcmotor22_cfg, MIKROBUS_1 );
    if ( UART_ERROR == dcmotor22_init( &dcmotor22, &dcmotor22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR22_ERROR == dcmotor22_default_cfg ( &dcmotor22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static int16_t pwm_duty = 0;
    static int8_t pwm_duty_step = 50;
    float current;
    log_printf ( &logger, " Motor A\r\n" );
    if ( DCMOTOR22_OK == dcmotor22_set_motor_pwm ( &dcmotor22, DCMOTOR22_MOTOR_A, pwm_duty ) )
    {
        log_printf ( &logger, " PWM duty: %d\r\n", pwm_duty );
    }
    Delay_ms ( 2000 );
    if ( DCMOTOR22_OK == dcmotor22_get_motor_current ( &dcmotor22, DCMOTOR22_MOTOR_A, &current ) )
    {
        log_printf ( &logger, " Current: %.3f A\r\n\n", current );
    }
    Delay_ms ( 500 );
    log_printf ( &logger, " Motor B\r\n" );
    if ( DCMOTOR22_OK == dcmotor22_set_motor_pwm ( &dcmotor22, DCMOTOR22_MOTOR_B, pwm_duty ) )
    {
        log_printf ( &logger, " PWM duty: %d\r\n", pwm_duty );
    }
    Delay_ms ( 2000 );
    if ( DCMOTOR22_OK == dcmotor22_get_motor_current ( &dcmotor22, DCMOTOR22_MOTOR_B, &current ) )
    {
        log_printf ( &logger, " Current: %.3f A\r\n\n", current );
    }
    Delay_ms ( 500 );
    
    if ( ( ( pwm_duty + pwm_duty_step ) > DCMOTOR22_MAX_PWM ) || ( ( pwm_duty + pwm_duty_step ) < DCMOTOR22_MIN_PWM ) ) 
    {
        pwm_duty_step = -pwm_duty_step;
    }
    pwm_duty += pwm_duty_step;
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
