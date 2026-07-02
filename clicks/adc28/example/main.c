/*!
 * @file main.c
 * @brief ADC 28 Click example
 *
 * # Description
 * This example demonstrates the use of the ADC 28 Click board by reading
 * voltage levels from all 8 single-ended analog input channels (CH0-CH7)
 * and displaying the results via UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the voltage from each channel (CH0 to CH7) and displays
 * the results on the USB UART once per second.
 *
 * @note
 * The input voltage range on each channel is 0 V to 3.3 V.
 * Do not apply voltages outside this range to the analog inputs.
 * 
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "adc28.h"

#ifndef MIKROBUS_POSITION_ADC28
    #define MIKROBUS_POSITION_ADC28 MIKROBUS_1
#endif

static adc28_t adc28;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc28_cfg_t adc28_cfg;  /**< Click config object. */

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
    adc28_cfg_setup( &adc28_cfg );
    ADC28_MAP_MIKROBUS( adc28_cfg, MIKROBUS_POSITION_ADC28 );
    if ( I2C_MASTER_ERROR == adc28_init( &adc28, &adc28_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC28_ERROR == adc28_default_cfg ( &adc28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;

    for ( uint8_t channel = ADC28_CHANNEL_0; channel <= ADC28_CHANNEL_7; channel++ )
    {
        if ( ADC28_OK == adc28_read_voltage( &adc28, channel, &voltage ) )
        {
            log_printf( &logger, " CH%u: %.3f V\r\n", ( uint16_t ) channel, voltage );
        }
    }
    log_printf( &logger, " -------------------\r\n" );
    Delay_ms( 1000 );
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
