/*!
 * @file main.c
 * @brief LED Driver 17 Click example
 *
 * # Description
 * This example demonstrates the use of LED Driver 17 click board by changing
 * the LEDs dimming level.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Changes the LEDs dimming level by setting the PWM duty cycle every 500ms. 
 * The duty cycle percentage will be displayed on the USB UART. It also checks
 * the fault indication pin and displays it accordingly.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver17.h"

static leddriver17_t leddriver17;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver17_cfg_t leddriver17_cfg;  /**< Click config object. */

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
    leddriver17_cfg_setup( &leddriver17_cfg );
    LEDDRIVER17_MAP_MIKROBUS( leddriver17_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == leddriver17_init( &leddriver17, &leddriver17_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER17_ERROR == leddriver17_default_cfg ( &leddriver17 ) )
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
    
    if ( !leddriver17_get_fault_pin ( &leddriver17 ) )
    {
        log_printf( &logger, " Fault detected!\r\n" );
    }
    leddriver17_set_duty_cycle ( &leddriver17, duty );
    log_printf( &logger, " Duty: %u%%\r\n\n", ( uint16_t ) ( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
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
