/*!
 * @file main.c
 * @brief Current7 Click example
 *
 * # Description
 * This library contains API for Current 7 Click driver.
 * The demo application reads ADC value and current ( A ).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C or AN driver and log UART.
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Current 7 Click board™.
 * In this example, we read and display the ADC values and current ( A ) data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "current7.h"

static current7_t current7;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    current7_cfg_t current7_cfg;  /**< Click config object. */

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
    current7_cfg_setup( &current7_cfg );
    CURRENT7_MAP_MIKROBUS( current7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == current7_init( &current7, &current7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENT7_ERROR == current7_default_cfg ( &current7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static float current;
    static uint16_t adc_val;
    
    current7_get_adc( &current7, &adc_val );
    log_printf( &logger, " ADC     : %d \r\n", adc_val );
    log_printf( &logger, "- - - - - - - - - - \r\n" );
    current7_get_current( &current7, &current );
    log_printf( &logger, " Current : %.3f A\r\n", current );
    log_printf( &logger, "--------------------\r\n" );
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
