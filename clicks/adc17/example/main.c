/*!
 * @file main.c
 * @brief ADC17 Click example
 *
 * # Description
 * This example demonstrates the use of ADC 17 Click board by reading 
 * the voltage from the two analog input channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which
 * sets the input channels to single-ended unipolar mode.
 *
 * ## Application Task
 * Reads and displays the voltage from the two analog input channels 
 * on the USB UART approximately every 500ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc17.h"

static adc17_t adc17;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc17_cfg_t adc17_cfg;  /**< Click config object. */

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
    adc17_cfg_setup( &adc17_cfg );
    ADC17_MAP_MIKROBUS( adc17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adc17_init( &adc17, &adc17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC17_ERROR == adc17_default_cfg ( &adc17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage;
    if ( ADC17_OK == adc17_set_channel ( &adc17, ADC17_CHANNEL_0 ) )
    {
        if ( ADC17_OK == adc17_get_voltage ( &adc17, &voltage ) )
        {
            log_printf ( &logger, " AIN0 voltage: %.3f V \r\n\n", voltage );
        }
    }
    if ( ADC17_OK == adc17_set_channel ( &adc17, ADC17_CHANNEL_1 ) )
    {
        if ( ADC17_OK == adc17_get_voltage ( &adc17, &voltage ) )
        {
            log_printf ( &logger, " AIN1 voltage: %.3f V \r\n\n", voltage );
        }
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
