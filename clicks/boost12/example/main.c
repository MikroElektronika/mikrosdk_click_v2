/*!
 * @file main.c
 * @brief Boost 12 Click example
 *
 * # Description
 * This example demonstrates the use of the Boost 12 Click board, changing
 * the output voltage by generating a PWM signal whose duty cycle is gradually
 * increased and decreased between 10% and 100%.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Boost 12 Click driver and applies the default
 * configuration.
 *
 * ## Application Task
 * Adjusts the PWM duty cycle in 1% steps, logs the current value, and smoothly
 * oscillates the duty between minimum and maximum levels.
 *
 * @note
 * The higher the duty cycle the higher the output voltage.
 * The output voltage range is from VIN to 12V.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "boost12.h"

static boost12_t boost12;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost12_cfg_t boost12_cfg;  /**< Click config object. */

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
    boost12_cfg_setup( &boost12_cfg );
    BOOST12_MAP_MIKROBUS( boost12_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == boost12_init( &boost12, &boost12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BOOST12_ERROR == boost12_default_cfg ( &boost12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 10;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 100.0;
    
    boost12_set_duty_cycle ( &boost12, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( int16_t ) duty_cnt );
    
    duty_cnt += duty_inc;
    if ( ( duty_cnt < 10 ) || ( duty_cnt > 100 ) ) 
    {
        duty_inc = -duty_inc;
        duty_cnt += duty_inc;
        duty_cnt += duty_inc;
    }
    Delay_ms ( 1000 );
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
