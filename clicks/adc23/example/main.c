/*!
 * @file main.c
 * @brief ADC 23 Click example
 *
 * # Description
 * This example demonstrates the use of the ADC 23 Click board™ 
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
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc23.h"

static adc23_t adc23;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc23_cfg_t adc23_cfg;  /**< Click config object. */

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
    adc23_cfg_setup( &adc23_cfg );
    ADC23_MAP_MIKROBUS( adc23_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc23_init( &adc23, &adc23_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC23_ERROR == adc23_default_cfg ( &adc23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    static float voltage = 0.0;
    if ( ADC23_OK == adc23_get_voltage( &adc23, &voltage ) )
    {
        log_printf( &logger, " Voltage : %.2f [mV]\r\n", voltage );
        Delay_ms ( 1000 );
    } 
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
