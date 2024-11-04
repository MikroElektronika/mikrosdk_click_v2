/*!
 * @file main.c
 * @brief Brushless23 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 23 Click board by driving the 
 * motor in both directions at different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Controls the motor speed by changing the PWM duty cycle every 2 seconds.
 * The duty cycle ranges from 20% to 80%. At the minimal speed, the motor switches direction.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless23.h"

static brushless23_t brushless23;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless23_cfg_t brushless23_cfg;  /**< Click config object. */

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
    brushless23_cfg_setup( &brushless23_cfg );
    BRUSHLESS23_MAP_MIKROBUS( brushless23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless23_init( &brushless23, &brushless23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS23_ERROR == brushless23_default_cfg ( &brushless23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 2;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    brushless23_pwm_set_duty_cycle ( &brushless23, duty );
    log_printf( &logger, "\r\n Duty cycle: %u%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
    float motor_speed_hz = 0;
    if ( BRUSHLESS23_OK == brushless23_get_motor_speed ( &brushless23, &motor_speed_hz ) )
    {
        log_printf( &logger, " Speed: %.1f Hz\r\n", motor_speed_hz );
    }
    duty_cnt += duty_inc;
    if ( duty_cnt > 8 ) 
    {
        duty_cnt = 7;
        duty_inc = -1;
    }
    else if ( duty_cnt < 2 ) 
    {
        duty_cnt = 2;
        duty_inc = 1;
        log_printf( &logger, "\r\n Switch direction\r\n" );
        brushless23_pwm_set_duty_cycle ( &brushless23, BRUSHLESS23_DUTY_CYCLE_MIN_PCT );
        Delay_ms ( 500 );
        brushless23_switch_direction ( &brushless23 );
    }
    Delay_ms ( 500 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
