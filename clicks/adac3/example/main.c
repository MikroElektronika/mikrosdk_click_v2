/*!
 * @file main.c
 * @brief ADAC3 Click example
 *
 * # Description
 * This example demonstrates the use of ADAC 3 click board by setting the DAC output
 * and reading the ADC results from 2 single-ended channels (AIN0, AIN1) and from a 
 * differential channel (AIN2+, AIN3-).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which enables
 * DAC output, sets the analog input mode to single-ended (AIN0, AIN1) and 
 * differential (AIN2+, AIN3-), and enables the auto increment mode.
 *
 * ## Application Task
 * Sets the DAC output increasing the value by 1 after each iteration, and reads the 
 * ADC results from 2 single-ended and 1 differential channels, and displays the results
 * on the USB UART every 100ms approximately.
 *
 * @note
 * Inputs should be connected to GND when not in use.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adac3.h"

static adac3_t adac3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adac3_cfg_t adac3_cfg;  /**< Click config object. */

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
    adac3_cfg_setup( &adac3_cfg );
    ADAC3_MAP_MIKROBUS( adac3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adac3_init( &adac3, &adac3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADAC3_ERROR == adac3_default_cfg ( &adac3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t dac = 0;
    uint8_t ain0, ain1, ain2_ain3_diff;
    if ( ADAC3_OK == adac3_write_dac ( &adac3, dac ) )
    {
        log_printf ( &logger, " DAC : %u mV\r\n", 
                     ( uint16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * dac++ ) );
    }
    if ( ADAC3_OK == adac3_read_adc ( &adac3, &ain0 ) )
    {
        log_printf ( &logger, " AIN0+: %u mV\r\n", 
                     ( uint16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * ain0 ) );
    }
    if ( ADAC3_OK == adac3_read_adc ( &adac3, &ain1 ) )
    {
        log_printf ( &logger, " AIN1+: %u mV\r\n",
                     ( uint16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * ain1 ) );
    }
    if ( ADAC3_OK == adac3_read_adc ( &adac3, &ain2_ain3_diff ) )
    {
        log_printf ( &logger, " AIN2+ - AIN3-: %d mV\r\n\n",
                     ( int16_t ) ( ( ADAC3_VREF_2048mV / ADAC3_RESOLUTION ) * ( int8_t ) ain2_ain3_diff ) );
    }
    Delay_ms ( 100 );
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
