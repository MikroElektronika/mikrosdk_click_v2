/*!
 * @file main.c
 * @brief ADC18 Click example
 *
 * # Description
 * This example demonstrates the use of ADC 18 Click board by reading 
 * the voltage from 12 analog input single-ended channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and performs the Click default configuration.
 *
 * ## Application Task
 * Reads and displays the voltage from 12 analog input single-ended channels 
 * on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc18.h"

static adc18_t adc18;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc18_cfg_t adc18_cfg;  /**< Click config object. */

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
    adc18_cfg_setup( &adc18_cfg );
    ADC18_MAP_MIKROBUS( adc18_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc18_init( &adc18, &adc18_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC18_ERROR == adc18_default_cfg ( &adc18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t channel = ADC18_CH_AI1_SINGLE_ENDED;
    if ( ADC18_OK == adc18_set_active_channel ( &adc18, channel ) )
    {
        adc18_start_conversion ( &adc18, ADC18_DATA_RATE_225_SPS );
        
        // Waits for the availability of the conversion result
        while ( adc18_get_rdy_pin ( &adc18 ) );
        
        adc18_stop_conversion ( &adc18 );
        
        float voltage;
        if ( ADC18_OK == adc18_read_voltage ( &adc18, &voltage ) )
        {
            log_printf ( &logger, "Channel AI%u: %.2f V\r\n", channel + 1, voltage );
            if ( ++channel > ADC18_CH_AI12_SINGLE_ENDED )
            {
                channel = ADC18_CH_AI1_SINGLE_ENDED;
                log_printf ( &logger, "\r\n" );
                Delay_ms ( 1000 );
            }
        }
    }
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
