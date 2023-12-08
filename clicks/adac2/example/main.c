/*!
 * @file main.c
 * @brief ADAC 2 Click example
 *
 * # Description
 * This example demonstrates the use of ADAC 2 click board by setting the DAC output (CIO)
 * and reading the ADC results from a single-ended channel (AI4) and from a differential
 * channel (AI5+, AI6-) as well as toggling all GPIO pins.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which enables
 * DAC voltage output, sets the analog input mode to single-ended for AI4 and 
 * differential (AI5+, AI6-), and enables all GPIOs as output.
 *
 * ## Application Task
 * Reads the ADC results from a single-ended (AI4) and a differential (AI5+, AI6-) channels,
 * then sets the raw DAC output increasing the value by 10000 after each iteration, and toggles
 * all GPIO pins. The results will be displayed on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adac2.h"

static adac2_t adac2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adac2_cfg_t adac2_cfg;  /**< Click config object. */

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
    adac2_cfg_setup( &adac2_cfg );
    ADAC2_MAP_MIKROBUS( adac2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adac2_init( &adac2, &adac2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADAC2_ERROR == adac2_default_cfg ( &adac2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage;
    if ( ADAC2_OK == adac2_set_active_ain_channel ( &adac2, ADAC2_CH_AI4_SINGLE_ENDED ) )
    {
        adac2_start_conversion ( &adac2, ADAC2_DATA_RATE_450_SPS );
        // Waits for the availability of the conversion result
        while ( adac2_get_rdy_pin ( &adac2 ) );
        adac2_stop_conversion ( &adac2 );
        if ( ADAC2_OK == adac2_read_voltage ( &adac2, ADAC2_FULL_SCALE_RANGE_12p5V, &voltage ) )
        {
            log_printf ( &logger, " Channel AI4 single-ended: %.2f V\r\n", voltage );
        }
    }
    if ( ADAC2_OK == adac2_set_active_ain_channel ( &adac2, ADAC2_CH_AI5_AI6_DIFFERENTIAL_25V ) )
    {
        adac2_start_conversion ( &adac2, ADAC2_DATA_RATE_450_SPS );
        // Waits for the availability of the conversion result
        while ( adac2_get_rdy_pin ( &adac2 ) );
        adac2_stop_conversion ( &adac2 );
        if ( ADAC2_OK == adac2_read_voltage ( &adac2, ADAC2_FULL_SCALE_RANGE_25V, &voltage ) )
        {
            log_printf ( &logger, " Channel AI5-AI6 differential: %.2f V\r\n", voltage );
        }
    }
    
    static int32_t dac = ADAC2_DAC_MIN_VALUE;
    if ( ADAC2_OK == adac2_write_dac ( &adac2, dac ) )
    {
        log_printf ( &logger, " DAC: %ld\r\n", dac );
        dac += 5000;
        if ( dac > ADAC2_DAC_MAX_VALUE )
        {
            dac = ADAC2_DAC_MIN_VALUE;
        }
    }
    
    uint32_t gpio_data;
    if ( ADAC2_OK == adac2_read_register ( &adac2, ADAC2_REG_GEN_GPIO_CTRL, &gpio_data ) )
    {
        gpio_data ^= ADAC2_GPIO_ALL_MASK;
        if ( ADAC2_OK == adac2_write_register ( &adac2, ADAC2_REG_GEN_GPIO_CTRL, gpio_data ) )
        {
            log_printf ( &logger, " GPIO: 0x%.2X\r\n\n", ( uint16_t ) ( gpio_data & ADAC2_GPIO_ALL_MASK ) );
        }
    }
    Delay_ms ( 1000 );
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
