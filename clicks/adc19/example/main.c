/*!
 * @file main.c
 * @brief ADC19 Click example
 *
 * # Description
 * This example demonstrates the use of ADC 19 click board by reading 
 * the voltage from the two analog input channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and sets the ADC voltage reference.
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
#include "adc19.h"

static adc19_t adc19;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc19_cfg_t adc19_cfg;  /**< Click config object. */

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
    adc19_cfg_setup( &adc19_cfg );
    ADC19_MAP_MIKROBUS( adc19_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc19_init( &adc19, &adc19_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    adc19_set_vref ( &adc19, ADC19_VREF_3V3 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage;
    if ( ADC19_OK == adc19_set_input_channel ( &adc19, ADC19_INPUT_CHANNEL_1 ) )
    {
        if ( ADC19_OK == adc19_get_voltage ( &adc19, &voltage ) )
        {
            log_printf ( &logger, " IN1 : %.3f V \r\n", voltage );
        }
    }
    if ( ADC19_OK == adc19_set_input_channel ( &adc19, ADC19_INPUT_CHANNEL_2 ) )
    {
        if ( ADC19_OK == adc19_get_voltage ( &adc19, &voltage ) )
        {
            log_printf ( &logger, " IN2 : %.3f V \r\n\n", voltage );
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
