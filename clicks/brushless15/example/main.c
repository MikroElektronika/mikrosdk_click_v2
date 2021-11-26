/*!
 * @file main.c
 * @brief Brushless15 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 15 click board by driving the 
 * motor in both directions at different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Controls the motor speed by changing the PWM duty cycle once per second.
 * The duty cycle ranges from 20% to 80%. At the minimal speed, the motor switches direction.
 * Each step will be logged on the USB UART where you can track the program flow.
 * 
 * @note
 * The maximal PWM Clock frequency for this click board is 1 kHz. 
 * So, depending on the selected setup the user will need to lower the MCU's main clock frequency 
 * in the setup in order to get the PWM clock frequency down to 1 kHz.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless15.h"


static brushless15_t brushless15;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless15_cfg_t brushless15_cfg;  /**< Click config object. */

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
    brushless15_cfg_setup( &brushless15_cfg );
    BRUSHLESS15_MAP_MIKROBUS( brushless15_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless15_init( &brushless15, &brushless15_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS15_ERROR == brushless15_default_cfg ( &brushless15 ) )
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
    
    brushless15_set_duty_cycle ( &brushless15, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms( 1000 );
    duty_cnt += duty_inc;
    if ( 8 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 1 == duty_cnt ) 
    {
        duty_inc = 1;
        duty_cnt = 2;
        log_printf( &logger, " Switch direction\r\n\n" );
        brushless15_switch_direction ( &brushless15 );
    }
}

void main ( void )  
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
