/*!
 * @file main.c
 * @brief ADC13 Click example
 *
 * # Description
 * This example demonstrates the use of ADC 13 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads the voltage between AIN0 and AIN1 channels, and the module internal temperature as well. 
 * All values are being displayed on the USB UART where you can track their changes.
 *
 * @note
 * An internal 2.5V reference is set by default. 
 * If you want, you can change it using the adc13_set_voltage_reference function.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc13.h"

static adc13_t adc13;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    adc13_cfg_t adc13_cfg;  /**< Click config object. */

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

    adc13_cfg_setup( &adc13_cfg );
    ADC13_MAP_MIKROBUS( adc13_cfg, MIKROBUS_1 );
    err_t init_flag  = adc13_init( &adc13, &adc13_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    adc13_default_cfg ( &adc13 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    float temperature = 0;
    
    adc13_measure_voltage ( &adc13, ADC13_VREF_INTERNAL, &voltage );
    log_printf( &logger, " Voltage: %.3f V\r\n", voltage );
    adc13_measure_temperature ( &adc13, &temperature );
    log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
    log_printf( &logger, " ---------------------------\r\n" );
    
    Delay_ms( 500 );
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
