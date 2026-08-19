/*!
 * @file main.c
 * @brief ADC 29 Click example
 *
 * # Description
 * This example demonstrates the use of the ADC 29 Click board by reading
 * the voltage levels from the single-ended analog input and displaying 
 * the results via UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and waits for the device power-on auto-calibration to complete.
 *
 * ## Application Task
 * Reads the voltage from the analog input and displays the result
 * on the USB UART once per second.
 *
 * @note
 * The absolute maximum input voltage is -0.3 V to 3.3 V (VREF + 0.3 V).
 * Do not apply voltages outside this range to the analog input.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "adc29.h"

#ifndef MIKROBUS_POSITION_ADC29
    #define MIKROBUS_POSITION_ADC29 MIKROBUS_1
#endif

static adc29_t adc29;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc29_cfg_t adc29_cfg;  /**< Click config object. */

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
    adc29_cfg_setup( &adc29_cfg );
    ADC29_MAP_MIKROBUS( adc29_cfg, MIKROBUS_POSITION_ADC29 );
    if ( SPI_MASTER_ERROR == adc29_init( &adc29, &adc29_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage = 0;

    if ( ADC29_OK == adc29_read_voltage( &adc29, &voltage ) )
    {
        log_printf( &logger, " AIN Voltage: %.3f V\r\n", voltage );
    }
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
