/*!
 * @file main.c
 * @brief VibroMotor4 Click example
 *
 * # Description
 * This library contains API for Vibro Motor 4 Click driver.
 * The library initializes and defines the I2C bus drivers
 * to write and read data from registers and PWM module.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C and PWM module, log UART, and additional pins.
 * After successful driver init, executes a default configuration
 * and configures Vibro Motor 4 Click board™.
 *
 * ## Application Task
 * This is an example that shows the use of a Vibro Motor 4 Click board™.
 * Changing duty cycle results in different vibrations.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "vibromotor4.h"

static vibromotor4_t vibromotor4;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    vibromotor4_cfg_t vibromotor4_cfg;  /**< Click config object. */

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
    vibromotor4_cfg_setup( &vibromotor4_cfg );
    VIBROMOTOR4_MAP_MIKROBUS( vibromotor4_cfg, MIKROBUS_1 );
    err_t init_flag = vibromotor4_init( &vibromotor4, &vibromotor4_cfg );
    if ( I2C_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    vibromotor4_enable( &vibromotor4, VIBROMOTOR4_PROPERTY_ENABLE );
    Delay_ms( 100 );

    vibromotor4_soft_rst( &vibromotor4 );
    Delay_ms( 100 );

    vibromotor4_default_cfg ( &vibromotor4 );
    Delay_ms( 100 );

    vibromotor4_set_duty_cycle( &vibromotor4, 0.0 );
    Delay_ms( 100 );

    vibromotor4_pwm_start( &vibromotor4 );
    Delay_ms( 100 );

    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void )
{
    static int8_t duty_cnt = 0;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    vibromotor4_set_duty_cycle ( &vibromotor4, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );

    Delay_ms( 1000 );

    if ( 5 == duty_cnt ) {
        duty_inc = -1;
    } else if ( 0 == duty_cnt ) {
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
