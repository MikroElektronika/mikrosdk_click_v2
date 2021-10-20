/*!
 * @file main.c
 * @brief VibroMotor Click example
 *
 * # Description
 * This application contorl the speed of vibro motor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver and PWM.
 * Configures PWM to 5kHz frequency, calculates maximum duty ratio and starts PWM 
 * with duty ratio value 0.
 * 
 * ## Application Task  
 * Allows user to enter desired command to control
 * Vibro Motor Click board.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "vibromotor.h"


static vibromotor_t vibromotor;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    vibromotor_cfg_t vibromotor_cfg;  /**< Click config object. */

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

    vibromotor_cfg_setup( &vibromotor_cfg );
    VIBROMOTOR_MAP_MIKROBUS( vibromotor_cfg, MIKROBUS_1 );
    err_t init_flag  = vibromotor_init( &vibromotor, &vibromotor_cfg );
    if ( PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    vibromotor_set_duty_cycle ( &vibromotor, 0.0 );
    vibromotor_pwm_start( &vibromotor );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    vibromotor_set_duty_cycle ( &vibromotor, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms( 500 );
    
    if ( 10 == duty_cnt ) {
        duty_inc = -1;
    } else if ( 0 == duty_cnt ) {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
