/*!
 * @file main.c
 * @brief RF Meter 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of RF Meter 3 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the click board.
 *
 * ## Application Task
 * Measures the RF input signal power in dBm and displays the results on the USB UART every 100ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rfmeter3.h"

static rfmeter3_t rfmeter3;   /**< RF Meter 3 Click driver object. */
static log_t logger;          /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    rfmeter3_cfg_t rfmeter3_cfg;  /**< Click config object. */

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
    rfmeter3_cfg_setup( &rfmeter3_cfg );
    RFMETER3_MAP_MIKROBUS( rfmeter3_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == rfmeter3_init( &rfmeter3, &rfmeter3_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    rfmeter3_enable_device ( &rfmeter3 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float rfmeter3_rf_input_power = 0;

    if ( RFMETER3_ERROR != rfmeter3_get_rf_input_power ( &rfmeter3, &rfmeter3_rf_input_power ) ) 
    {
        log_printf( &logger, " RF Input Power: %.2f dBm\r\n", rfmeter3_rf_input_power );
        Delay_ms( 100 );
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
