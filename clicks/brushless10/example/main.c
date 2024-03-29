/*!
 * @file main.c
 * @brief Brushless 10 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 10 click board by driving the 
 * motor at different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Controls the motor speed by changing the PWM duty cycle every 2 seconds.
 * The duty cycle ranges from 20% to 100%. Each step will be logged on the USB UART
 * where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless10.h"

static brushless10_t brushless10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless10_cfg_t brushless10_cfg;  /**< Click config object. */

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
    brushless10_cfg_setup( &brushless10_cfg );
    BRUSHLESS10_MAP_MIKROBUS( brushless10_cfg, MIKROBUS_1 );
    if ( BRUSHLESS10_OK != brushless10_init( &brushless10, &brushless10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS10_OK != brushless10_default_cfg ( &brushless10 ) )
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
    
    brushless10_set_duty_cycle ( &brushless10, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms( 2000 );

    duty_cnt += duty_inc;
    if ( duty_cnt > 10 ) 
    {        
        duty_cnt = 9;
        duty_inc = -1;
    }
    else if ( duty_cnt < 2 ) 
    {
        duty_cnt = 2;
        duty_inc = 1;
        log_printf( &logger, " Pull brake\r\n" );
        brushless10_pull_brake ( &brushless10 );
        Delay_ms( 3000 );
        log_printf( &logger, " Release brake\r\n" );
        brushless10_release_brake ( &brushless10 );
        Delay_ms( 1000 );
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
