/*!
 * @file main.c
 * @brief Expand9 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Expand 9 Click board™.
 * The library initializes and defines the I2C bus drivers 
 * to write and read data from registers. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C  module, log UART, and additional pins. 
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Expand 9 Click board™.
 * This example shows the capabilities of the Expand 9 click by toggling each of 16 available channels.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "expand9.h"

static expand9_t expand9;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand9_cfg_t expand9_cfg;  /**< Click config object. */

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
    expand9_cfg_setup( &expand9_cfg );
    EXPAND9_MAP_MIKROBUS( expand9_cfg, MIKROBUS_1 );
    err_t init_flag = expand9_init( &expand9, &expand9_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    expand9_default_cfg ( &expand9 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{   
    expand9_soft_reset( &expand9 );
    Delay_ms( 100 );
    
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_ON );
        Delay_ms( 100 );
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_OFF );
        Delay_ms( 100 );
    }
    
    for ( uint8_t cnt = 15; cnt > 0; cnt-- )
    {
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_ON );
        Delay_ms( 100 );
        expand9_set_ch_output_state( &expand9, cnt, CH_OUTPUT_OFF );
        Delay_ms( 100 );
    }
    
    expand9_soft_reset( &expand9 );
    Delay_ms( 100 );
    
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 10 );
        Delay_ms( 100 );
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 200 );
        Delay_ms( 100 );
    }
    
    for ( uint8_t cnt = 15; cnt > 0; cnt-- )
    {
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 200 );
        Delay_ms( 100 );
        expand9_led_driver_config( &expand9, cnt, EXPAND9_FREQ_DIV_1, EXPAND9_LED_MODE_LINEAR );
        expand9_set_intensity( &expand9, cnt, 10 );
        Delay_ms( 100 );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
