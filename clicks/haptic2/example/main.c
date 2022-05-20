/*!
 * @file main.c
 * @brief Haptic2 Click example
 *
 * # Description
 * This app shows some of the functions that Haptic 2 click has.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - PWM,
 * PWM signal is set to 8000 HZ and to give a 0% duty cycle
 * and start PWM module.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Haptic 2 Click board.
 * In this example, we switched PWM signal back and forth 
 * from 10% duty cycle to 90% duty cycle every 500 milliseconds.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nikola Peric
 *
 */

#include "board.h"
#include "log.h"
#include "haptic2.h"


static haptic2_t haptic2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    haptic2_cfg_t haptic2_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    haptic2_cfg_setup( &haptic2_cfg );
    HAPTIC2_MAP_MIKROBUS( haptic2_cfg, MIKROBUS_1 );
    err_t init_flag  = haptic2_init( &haptic2, &haptic2_cfg );
    if ( init_flag == PWM_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    haptic2_default_cfg ( &haptic2 );

    haptic2_set_duty_cycle ( &haptic2, 0.0 );
    haptic2_pwm_start( &haptic2 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    haptic2_set_duty_cycle ( &haptic2, duty );
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

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
