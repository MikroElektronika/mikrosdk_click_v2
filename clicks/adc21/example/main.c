/*!
 * @file main.c
 * @brief ADC 21 Click example
 *
 * # Description
 * This example demonstrates the use of ADC 21 click board by reading and displaying
 * the voltage levels from 8 analog input channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the voltage levels from all 8 analog input channels and displays the results
 * on the USB UART once per second approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc21.h"

static adc21_t adc21;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc21_cfg_t adc21_cfg;  /**< Click config object. */

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
    adc21_cfg_setup( &adc21_cfg );
    ADC21_MAP_MIKROBUS( adc21_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc21_init( &adc21, &adc21_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t ch_num = ADC21_CHANNEL_0;
    float ch_voltage;
    if ( ADC21_OK == adc21_read_voltage ( &adc21, ch_num, ADC21_AVCC_3V3, &ch_voltage ) )
    {
        log_printf ( &logger, " CH%u voltage: %.2f V\r\n", ( uint16_t ) ch_num, ch_voltage );
    }
    if ( ++ch_num > ADC21_CHANNEL_7 )
    {
        log_printf ( &logger, " ------------------------\r\n\n" );
        ch_num = ADC21_CHANNEL_0;
        Delay_ms ( 1000 );
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
