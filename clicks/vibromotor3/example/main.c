/*!
 * @file main.c
 * @brief VibroMotor3 Click example
 *
 * # Description
 * This example shows the capabilities of the Vibro Motor 3 Click board 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes I2C driver, PWM driver and configures Vibro Motor 3 Click board.
 *
 * ## Application Task
 * Changing duty cycle applied in order to get different vibrations.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "vibromotor3.h"

static vibromotor3_t vibromotor3;
static log_t logger;

static float pwm_max_duty = 1;
static float pwm_duty_cycle = 0;


void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    vibromotor3_cfg_t vibromotor3_cfg;  /**< Click config object. */

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
    vibromotor3_cfg_setup( &vibromotor3_cfg );
    VIBROMOTOR3_MAP_MIKROBUS( vibromotor3_cfg, MIKROBUS_1 );
    err_t init_flag = vibromotor3_init( &vibromotor3, &vibromotor3_cfg );
    if ( I2C_MASTER_ERROR == init_flag || PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    vibromotor3_enable( &vibromotor3, VIBROMOTOR3_PROPERTY_ENABLE );
    Delay_ms ( 100 );
    
    vibromotor3_soft_rst( &vibromotor3 );
    Delay_ms ( 100 );

    vibromotor3_default_cfg( &vibromotor3 );
    Delay_ms ( 100 );

    vibromotor3_set_duty_cycle( &vibromotor3, 0.0 );
    vibromotor3_pwm_start( &vibromotor3 );
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) {
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    vibromotor3_set_duty_cycle ( &vibromotor3, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );

    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) {
        duty_inc = -1;
    } else if ( 0 == duty_cnt ) {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
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
