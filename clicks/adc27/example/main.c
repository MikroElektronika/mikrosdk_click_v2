/*!
 * @file main.c
 * @brief ADC 27 Click example
 *
 * # Description
 * This example demonstrates the use of the ADC 27 Click board by reading voltages
 * from multiple analog input channels configured in both single-ended and differential modes.
 * The measured voltage values are displayed via UART.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the ADC 27 Click driver, and performs the default configuration.
 *
 * ## Application Task
 * Reads and logs voltage values from channels CH0-CH3 (single-ended) and CH4/CH5, CH6/CH7 (differential).
 *
 * @note
 * CH0 and CH1 operate with respect to ground and VREF, while CH2 and CH3 provide bipolar inputs.
 * Channels CH4/CH5 and CH6/CH7 are differential input pairs. Measurements are taken every second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc27.h"

static adc27_t adc27;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc27_cfg_t adc27_cfg;  /**< Click config object. */

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
    adc27_cfg_setup( &adc27_cfg );
    ADC27_MAP_MIKROBUS( adc27_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc27_init( &adc27, &adc27_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC27_ERROR == adc27_default_cfg ( &adc27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage = 0;
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_SGL_0, &voltage ) )
    {
        log_printf ( &logger, " CH0: %.3f V (gnd,vref/2)\r\n", voltage );
    }
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_SGL_1, &voltage ) )
    {
        log_printf ( &logger, " CH1: %.3f V (gnd,vref)\r\n", voltage );
    }
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_SGL_2, &voltage ) )
    {
        log_printf ( &logger, " CH2: %.3f V (-vref/4,vref/4)\r\n", voltage );
    }
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_SGL_3, &voltage ) )
    {
        log_printf ( &logger, " CH3: %.3f V (-vref/2,vref/2)\r\n", voltage );
    }
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_DIF_45, &voltage ) )
    {
        log_printf ( &logger, " CH4+/CH5-: %.3f V (-vref,vref)\r\n", voltage );
    }
    if ( ADC27_OK == adc27_read_voltage ( &adc27, ADC27_CONFIG_CH_DIF_67, &voltage ) )
    {
        log_printf ( &logger, " CH6+/CH7-: %.3f V (-2xvref,2xvref)\r\n\n", voltage );
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
