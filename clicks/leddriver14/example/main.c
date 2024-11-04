/*!
 * @file main.c
 * @brief LEDDriver14 Click example
 *
 * # Description
 * This example demonstrates the use of LED Driver 14 Click board by controlling
 * the brightness of LEDs by changing the PWM Duty Cycle.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Adjusts the LEDs' brightness by changing the PWM duty cycle every 500ms.
 * A duty cycle value is being displayed on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver14.h"

static leddriver14_t leddriver14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver14_cfg_t leddriver14_cfg;  /**< Click config object. */

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
    leddriver14_cfg_setup( &leddriver14_cfg );
    LEDDRIVER14_MAP_MIKROBUS( leddriver14_cfg, MIKROBUS_1 );
    err_t init_flag = leddriver14_init( &leddriver14, &leddriver14_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( PWM_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER14_ERROR == leddriver14_default_cfg ( &leddriver14 ) )
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
    
    leddriver14_set_duty_cycle ( &leddriver14, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
    
    if ( !leddriver14_get_int_pin ( &leddriver14 ) )
    {
        log_info ( &logger, " Abnormality such as LED Open or the OUTx pin short circuit occured " );
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
