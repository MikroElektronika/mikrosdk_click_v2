/*!
 * @file main.c
 * @brief ADC 14 Click example
 *
 * # Description
 * This example demonstrates the use of the ADC 14 Click board™ 
 * by reading results of AD conversion by using SPI serial interface.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART and enabled internal voltage reference.
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
#include "adc14.h"

static adc14_t adc14;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc14_cfg_t adc14_cfg;  /**< Click config object. */

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
    adc14_cfg_setup( &adc14_cfg );
    ADC14_MAP_MIKROBUS( adc14_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adc14_init( &adc14, &adc14_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void )
{
    float voltage = 0.0;
    if ( ADC14_OK == adc14_get_voltage( &adc14, &voltage ) )
    {
        log_printf( &logger, " Voltage : %.2f [mV]\r\n", voltage );
        Delay_ms( 1000 );
    }
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
