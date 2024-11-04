/*!
 * @file main.c
 * @brief LEDDriver11 Click example
 *
 * # Description
 * This example demonstrates the use of LED Driver 11 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and executes the Click default configuration which
 * starts the PWM module and sets the LEDs current to minimum.
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
#include "leddriver11.h"

static leddriver11_t leddriver11;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    leddriver11_cfg_t leddriver11_cfg;  /**< Click config object. */

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
    leddriver11_cfg_setup( &leddriver11_cfg );
    LEDDRIVER11_MAP_MIKROBUS( leddriver11_cfg, MIKROBUS_1 );
    err_t init_flag = leddriver11_init( &leddriver11, &leddriver11_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    leddriver11_default_cfg ( &leddriver11 );
    log_printf( &logger, " Dimming the LEDs light...\r\n" );
}

void application_task ( void ) 
{
    static int16_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    leddriver11_set_duty_cycle ( &leddriver11, duty );
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
