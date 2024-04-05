/*!
 * @file main.c
 * @brief Humidity Click example
 *
 * # Description
 * This example demonstrates the use of Humidity click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger. 
 * The I2C communication interface is selected by default.
 *
 * ## Application Task
 * Reads the ADC voltage and then calculates the relative humidity from it.
 * The calculated value of relative humidity in percents is being displayed on 
 * the USB UART approximately once per second. 
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "humidity.h"

static humidity_t humidity;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    humidity_cfg_t humidity_cfg;  /**< Click config object. */

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
    humidity_cfg_setup( &humidity_cfg );
    HUMIDITY_MAP_MIKROBUS( humidity_cfg, MIKROBUS_1 );
    if ( HUMIDITY_OK != humidity_init( &humidity, &humidity_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    if ( HUMIDITY_OK == humidity_read_voltage ( &humidity, &voltage ) )
    {
        log_printf( &logger, " Relative Humidity [%%RH]: %.2f\r\n\n", humidity_voltage_to_rh( &humidity, voltage ) );
    }
    Delay_ms ( 1000 );
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
