/*!
 * @file main.c
 * @brief HBridge8 Click example
 *
 * # Description
 * This library contains an API for the H-Bridge 8 Click driver.
 * This demo application shows the use of a H-Bridge 8 Click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of PWM module and log UART.
 * After driver initialization, the app set duty cycle, start PWM and
 * set motor drive the forward.
 *
 * ## Application Task
 * This is an example that shows the use of an H-Bridge 8 Click board™.
 * In this example, the app drives the motor forward and switched the PWM signal back and forth 
 * from 3% duty cycle to 8% duty cycle and back every 3000 milliseconds.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge8.h"

static hbridge8_t hbridge8;
static log_t logger;
uint8_t mode;

void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    hbridge8_cfg_t hbridge8_cfg;  /**< Click config object. */

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

    hbridge8_cfg_setup( &hbridge8_cfg );
    HBRIDGE8_MAP_MIKROBUS( hbridge8_cfg, MIKROBUS_1 );
    err_t init_flag  = hbridge8_init( &hbridge8, &hbridge8_cfg );
    if ( PWM_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    hbridge8_default_cfg ( &hbridge8 );
    Delay_ms ( 100 );
   
    hbridge8_set_mode( &hbridge8, HBRIDGE8_MODE_FORWARD );
    log_printf( &logger, "\r\n>>> Forward\r\n\r\n" );
    hbridge8_set_duty_cycle ( &hbridge8, 0.1 );
    hbridge8_pwm_start( &hbridge8 );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 3;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 100.0;
    
    hbridge8_set_duty_cycle ( &hbridge8, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt ) );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( 8 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 3 == duty_cnt ) 
    {
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
