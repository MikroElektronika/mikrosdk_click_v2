/*!
 * @file main.c
 * @brief LEDDriver10 Click example
 *
 * # Description
 * This example demonstrates the use of LED Driver 10 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, starts the PWM module and enables all channels.
 *
 * ## Application Task
 * Controls the LEDs brightness by changing the PWM duty cycle.
 * The PWM duty cycle percentage will be logged on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver10.h"

static leddriver10_t leddriver10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    leddriver10_cfg_t leddriver10_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    leddriver10_cfg_setup( &leddriver10_cfg );
    LEDDRIVER10_MAP_MIKROBUS( leddriver10_cfg, MIKROBUS_1 );
    err_t init_flag  = leddriver10_init( &leddriver10, &leddriver10_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    leddriver10_pwm_start( &leddriver10 );    
    leddriver10_set_channels ( &leddriver10, LEDDRIVER10_ENABLE_ALL_CH );
    log_printf( &logger, " All channels enabled!\r\n" );
    log_printf( &logger, " Dimming the LEDs light...\r\n" );
}

void application_task ( void ) 
{
    static int16_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver10_set_duty_cycle ( &leddriver10, duty );
    log_printf( &logger, "> Duty: %u%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
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
