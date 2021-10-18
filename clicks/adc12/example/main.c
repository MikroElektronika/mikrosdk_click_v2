/*!
 * @file main.c
 * @brief ADC12 Click example
 *
 * # Description
 * This example demonstrates the use of ADC 12 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the input and power-down modes.
 *
 * ## Application Task
 * Reads the RAW ADC data and converts it to voltage in milivolts and displays
 * both values on the USB UART every second.
 *
 * @note
 * With internal reference voltage set the click measures up to 2500 mV.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc12.h"

static adc12_t adc12;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc12_cfg_t adc12_cfg;  /**< Click config object. */

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

    adc12_cfg_setup( &adc12_cfg );
    ADC12_MAP_MIKROBUS( adc12_cfg, MIKROBUS_1 );
    err_t init_flag = adc12_init( &adc12, &adc12_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    adc12_set_sd_mode ( &adc12, ADC12_CMD_SD_SINGLE_END );
    adc12_set_pd_mode( &adc12, ADC12_CMD_PD_IRON_ADON );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t raw_adc;
    float voltage;

    adc12_read_raw_data ( &adc12, ADC12_SINGLE_END_CH0, &raw_adc );
    adc12_read_voltage ( &adc12, ADC12_SINGLE_END_CH0, ADC12_INTERNAL_VREF, &voltage );
    
    log_printf( &logger, " RAW ADC: %u \r\n", raw_adc );
    log_printf( &logger, " Voltage from Channel 0: %.2f mV \r\n", voltage );
    log_printf( &logger, " ---------------------------\r\n" );
    Delay_ms( 1000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
