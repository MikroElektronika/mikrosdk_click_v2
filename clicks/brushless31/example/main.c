/*!
 * @file main.c
 * @brief Brushless 31 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 31 Click board by driving the 
 * motor in both directions at different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Controls the motor speed by changing the PWM duty cycle every 500 milliseconds.
 * The duty cycle ranges from 80% to 0%. At the minimal speed, the motor switches direction.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @note
 * This Click board is designed for 5V systems but can also be controlled with 3V3 GPIO lines.
 * Ensure your MCU is 5V tolerant on mikroBUS GPIO lines before turning on the power supply.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless31.h"

static brushless31_t brushless31;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless31_cfg_t brushless31_cfg;  /**< Click config object. */

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
    brushless31_cfg_setup( &brushless31_cfg );
    BRUSHLESS31_MAP_MIKROBUS( brushless31_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless31_init( &brushless31, &brushless31_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS31_ERROR == brushless31_default_cfg ( &brushless31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 8;
    static int8_t duty_inc = -1;
    float duty = duty_cnt / 10.0;
    
    brushless31_set_duty_cycle ( &brushless31, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );

    duty_cnt += duty_inc;
    if ( duty_cnt > 8 ) 
    {        
        duty_cnt = 8;
        duty_inc = -1;
        log_printf( &logger, " Pull brake\r\n" );
        brushless31_pull_brake ( &brushless31 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Switch direction\r\n" );
        brushless31_switch_direction ( &brushless31 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Release brake\r\n" );
        brushless31_release_brake ( &brushless31 );
        Delay_ms ( 1000 );
    }
    else if ( duty_cnt < 0 ) 
    {
        duty_cnt = 1;
        duty_inc = 1;
    }
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
