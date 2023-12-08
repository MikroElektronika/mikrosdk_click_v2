/*!
 * @file main.c
 * @brief Brushless 24 Click example
 *
 * # Description
 * This application is a schowcase of controlling speed of brushless motor using Brushless 24 Click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of LOG, PWM module and additional pins.
 *
 * ## Application Task
 * In a span of second changes duty cycle from 0 to 100% which is changing speed of the motor.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless24.h"

static brushless24_t brushless24;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless24_cfg_t brushless24_cfg;  /**< Click config object. */

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
    brushless24_cfg_setup( &brushless24_cfg );
    BRUSHLESS24_MAP_MIKROBUS( brushless24_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless24_init( &brushless24, &brushless24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS24_ERROR == brushless24_default_cfg ( &brushless24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless24_set_duty_cycle ( &brushless24, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms( 1000 );
    
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
