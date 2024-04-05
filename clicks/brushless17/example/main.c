/*!
 * @file main.c
 * @brief Brushless17 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 17 click board by driving the 
 * motor in both directions at different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Controls the motor speed by changing the PWM duty cycle every 500ms.
 * The duty cycle ranges from 40% to 80%. At the minimal speed, the motor switches direction.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless17.h"


static brushless17_t brushless17;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless17_cfg_t brushless17_cfg;  /**< Click config object. */

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
    brushless17_cfg_setup( &brushless17_cfg );
    BRUSHLESS17_MAP_MIKROBUS( brushless17_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless17_init( &brushless17, &brushless17_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS17_ERROR == brushless17_default_cfg ( &brushless17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 4;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    brushless17_set_duty_cycle ( &brushless17, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    duty_cnt += duty_inc;
    if ( 8 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 3 == duty_cnt ) 
    {
        duty_inc = 1;
        duty_cnt = 4;
        log_printf( &logger, " Switch direction\r\n\n" );
        brushless17_switch_direction ( &brushless17 );
    }
    
    if ( !brushless17_get_diagnostic_pin ( &brushless17 ) )
    {
        log_info ( &logger, " An overcurrent or overtemperature event has occured " );
    }

    Delay_ms ( 500 );
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
