/*!
 * @file main.c
 * @brief LED Driver 18 Click example
 *
 * # Description
 * This library contains API for LED Driver 18 Click driver. 
 * The library initializes and defines the I2C bus drivers to 
 * write and read data for setting constant current output, 
 * as well as the default configuration for a PWM output value 
 * of the OUT pins.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs default configuration and sets 
 * the device in output enabled mode.
 *
 * ## Application Task
 * This example demonstrates the use of the LED Driver 18 Click board by 
 * changing PWM values for all output from a minimum value to 
 * maximum value and back to minimum controlling the brightness of the 
 * LEDs in the process.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver18.h"

static leddriver18_t leddriver18;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver18_cfg_t leddriver18_cfg;  /**< Click config object. */

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
    leddriver18_cfg_setup( &leddriver18_cfg );
    LEDDRIVER18_MAP_MIKROBUS( leddriver18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == leddriver18_init( &leddriver18, &leddriver18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER18_ERROR == leddriver18_default_cfg ( &leddriver18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float pwm_val;

    for ( int8_t  n_cnt = 0; n_cnt <= 100; n_cnt += 10 )
    {
        for ( uint8_t out_cnt = 0; out_cnt < LEDDRIVER18_MAX_OUTPUT_NUM; out_cnt++ )
        {
            leddriver18_set_output_pwm( out_cnt, n_cnt );
        }
        pwm_val = leddriver18_get_output_pwm( 0 );
        log_printf( &logger, " PWM value: %.2f \r\n", pwm_val );
        leddriver18_write_config( &leddriver18 );
        Delay_ms( 200 );
    }
    for ( int8_t  n_cnt = 100; n_cnt >= 10; n_cnt -= 10 )
    {
        for ( uint8_t out_cnt = 0; out_cnt < LEDDRIVER18_MAX_OUTPUT_NUM; out_cnt++ )
        {
            leddriver18_set_output_pwm( out_cnt, n_cnt );
        }
        pwm_val = leddriver18_get_output_pwm( 0 );
        log_printf( &logger, " PWM value: %.2f \r\n", pwm_val );
        leddriver18_write_config( &leddriver18 );
        Delay_ms( 200 );
    }
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
