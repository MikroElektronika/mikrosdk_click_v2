/*!
 * @file main.c
 * @brief LED Ring 2 Click example
 *
 * # Description
 * This library contains API for LED Ring 2 Click driver.
 * The library initializes and defines the I2C bus drivers 
 * to write and read data from registers. 
 * The library also includes a function for controlling LEDs.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the LED Ring 2 Click board™.
 * The demo example controls every LED and changes the LED brightness by PWM,
 * increasing its brightness from LED1 to LED54.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ledring2.h"

static ledring2_t ledring2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ledring2_cfg_t ledring2_cfg;  /**< Click config object. */

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
    ledring2_cfg_setup( &ledring2_cfg );
    LEDRING2_MAP_MIKROBUS( ledring2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ledring2_init( &ledring2, &ledring2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( LEDRING2_ERROR == ledring2_default_cfg ( &ledring2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " LED Ring 2 Click\r\n" );
}

void application_task ( void ) 
{
    for ( uint8_t led_pos = 1; led_pos < 55; led_pos++ )
    {
        if ( LEDRING2_OK == ledring2_set_led_brightness( &ledring2, led_pos, ( led_pos * 100 ) + 255 ) )
        {
            ledring2_set_vsync( &ledring2 );
            Delay_ms ( 10 );
        }
    }
    Delay_ms ( 1000 );
    
    for ( uint8_t led_pos = 54; led_pos > 0; led_pos-- )
    {
        if ( LEDRING2_OK == ledring2_set_led_brightness( &ledring2, led_pos, 0 ) )
        {
            ledring2_set_vsync( &ledring2 );
            Delay_ms ( 10 );
        }
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
