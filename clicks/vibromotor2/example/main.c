/*!
 * @file main.c
 * @brief VibroMotor2 Click example
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
#include "vibromotor2.h"


static vibromotor2_t vibromotor2;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    vibromotor2_cfg_t vibromotor2_cfg;  /**< Click config object. */

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

    vibromotor2_cfg_setup( &vibromotor2_cfg );
    VIBROMOTOR2_MAP_MIKROBUS( vibromotor2_cfg, MIKROBUS_1 );
    err_t init_flag  = vibromotor2_init( &vibromotor2, &vibromotor2_cfg );
    if ( PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    vibromotor2_set_duty_cycle ( &vibromotor2, 0.0 );
    vibromotor2_pwm_start( &vibromotor2 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    vibromotor2_set_duty_cycle ( &vibromotor2, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms( 500 );
    
    if ( 10 == duty_cnt ) {
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
