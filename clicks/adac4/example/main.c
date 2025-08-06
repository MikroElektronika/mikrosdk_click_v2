/*!
 * @file main.c
 * @brief ADAC 4 Click example
 *
 * # Description
 * This example demonstrates the use of the ADAC 4 Click board which features 
 * an 8-channel, 12-bit DAC and ADC. The application configures each DAC channel 
 * with incremental values and measures the corresponding output voltage using 
 * the integrated ADC, as well as logs the device die temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board driver, and applies the default configuration.
 *
 * ## Application Task
 * Iterates through all 8 DAC/ADC channels, sets an output voltage, reads back the 
 * corresponding ADC voltage, and logs both values. Also reads and logs the die temperature.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adac4.h"

static adac4_t adac4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adac4_cfg_t adac4_cfg;  /**< Click config object. */

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
    adac4_cfg_setup( &adac4_cfg );
    ADAC4_MAP_MIKROBUS( adac4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adac4_init( &adac4, &adac4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADAC4_ERROR == adac4_default_cfg ( &adac4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint16_t dac_data = ADAC4_DAC_DATA_MIN;
    float die_temp = 0;
    float voltage = 0;
    for ( uint8_t ch_sel = ADAC4_CHANNEL_0; ch_sel <= ADAC4_CHANNEL_7; ch_sel++ )
    {
        log_printf ( &logger, "\r\n CH%u -> ", ( uint16_t ) ch_sel, dac_data );
        if ( ADAC4_OK == adac4_write_dac ( &adac4, ch_sel, dac_data ) )
        {
            log_printf ( &logger, "DAC: %.4u, ", dac_data );
        }
        if ( ADAC4_OK == adac4_read_adc_voltage ( &adac4, ch_sel, &voltage ) )
        {
            log_printf ( &logger, "Voltage: %.3f", voltage );
        }
        dac_data += 200;
        if ( dac_data > ADAC4_DAC_DATA_MAX )
        {
            dac_data = ADAC4_DAC_DATA_MIN;
        }
    }
    if ( ADAC4_OK == adac4_read_die_temp ( &adac4, &die_temp ) )
    {
        log_printf ( &logger, "\r\n Die Temperature: %.2f degC\r\n", die_temp );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
