/*!
 * @file main.c
 * @brief ADC 22 Click example
 *
 * # Description
 * This example demonstrates the use of the ADC 22 Click board™ 
 * by reading and writing data by using SPI serial interface and reading results of AD conversion.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application reads the voltage levels from analog input and displays the results.
 * By default, the operating input range sets from 0V to 12.288V [3×Vref;Vref=4.096V].
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc22.h"

static adc22_t adc22;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc22_cfg_t adc22_cfg;  /**< Click config object. */

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
    adc22_cfg_setup( &adc22_cfg );
    ADC22_MAP_MIKROBUS( adc22_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc22_init( &adc22, &adc22_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    if ( ADC22_ERROR == adc22_default_cfg ( &adc22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{   
    static float voltage = 0.0;
    if ( ADC22_OK == adc22_get_voltage ( &adc22, &voltage ) )
    {
        log_printf( &logger, " Voltage : %.2f V\r\n", voltage );
        log_printf( &logger, " ----------------\r\n" );
        Delay_ms( 1000 );
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
