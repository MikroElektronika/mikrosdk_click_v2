/*!
 * @file main.c
 * @brief Brushless 28 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 28 Click board by driving the 
 * motor in both directions at different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Controls the motor speed by changing the PWM duty cycle every 500 milliseconds.
 * The duty cycle ranges from 0% to 100%. At the minimal speed, the motor switches direction.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless28.h"

#ifndef MIKROBUS_POSITION_BRUSHLESS28
    #define MIKROBUS_POSITION_BRUSHLESS28 MIKROBUS_1
#endif

static brushless28_t brushless28;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless28_cfg_t brushless28_cfg;  /**< Click config object. */

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
    brushless28_cfg_setup( &brushless28_cfg );
    BRUSHLESS28_MAP_MIKROBUS( brushless28_cfg, MIKROBUS_POSITION_BRUSHLESS28 );
    if ( BRUSHLESS28_OK != brushless28_init( &brushless28, &brushless28_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS28_OK != brushless28_default_cfg ( &brushless28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static int8_t duty_cnt = 0;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless28_set_duty_cycle ( &brushless28, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );

    duty_cnt += duty_inc;
    if ( duty_cnt > 10 ) 
    {        
        duty_cnt = 9;
        duty_inc = -1;
    }
    else if ( duty_cnt < 0 ) 
    {
        duty_cnt = 1;
        duty_inc = 1;
        log_printf( &logger, " Pull brake\r\n" );
        brushless28_pull_brake ( &brushless28 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Switch direction\r\n" );
        brushless28_switch_direction ( &brushless28 );
        Delay_ms ( 1000 );
        log_printf( &logger, " Release brake\r\n" );
        brushless28_release_brake ( &brushless28 );
        Delay_ms ( 1000 );
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
