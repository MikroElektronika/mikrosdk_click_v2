/*!
 * @file main.c
 * @brief LEDDriver13 Click example
 *
 * # Description
 * This library contains API for LED Driver 13 Click driver.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and executes the click default configuration which
 * starts the PWM module and sets the LEDs current to minimum.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the LED Driver 13 Click board™.
 * The app controls the LEDs brightness by changing the PWM duty cycle.
 * The PWM duty cycle percentage will be logged on the USB UART.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver13.h"


static leddriver13_t leddriver13;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver13_cfg_t leddriver13_cfg;  /**< Click config object. */

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
    leddriver13_cfg_setup( &leddriver13_cfg );
    LEDDRIVER13_MAP_MIKROBUS( leddriver13_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == leddriver13_init( &leddriver13, &leddriver13_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER13_ERROR == leddriver13_default_cfg ( &leddriver13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    
    leddriver13_set_duty_cycle ( &leddriver13, 0.01 );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 1000.0;
    
    leddriver13_set_duty_cycle ( &leddriver13, duty );
    log_printf( &logger, "> Duty: %.1f%%\r\n", duty * 100 );
    Delay_ms( 100 );
    
    if ( 30 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
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
