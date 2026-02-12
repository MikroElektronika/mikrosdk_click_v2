/*!
 * @file main.c
 * @brief TempHum 28 Click example
 *
 * # Description
 * This example demonstrates the use of the TempHum 28 Click board for
 * ambient temperature and relative humidity measurement. The application
 * reads temperature and humidity data via the SPI interface and displays
 * the measured values on the serial terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and TempHum 28 Click driver, disables the internal
 * heater, and enables the device for normal operation.
 *
 * ## Application Task
 * Periodically reads temperature and humidity values from the sensor and
 * logs the results to the serial terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum28.h"

static temphum28_t temphum28;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum28_cfg_t temphum28_cfg;  /**< Click config object. */

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
    temphum28_cfg_setup( &temphum28_cfg );
    TEMPHUM28_MAP_MIKROBUS( temphum28_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == temphum28_init( &temphum28, &temphum28_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    temphum28_heater_disable ( &temphum28 );
    temphum28_device_enable ( &temphum28 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float temperature = 0;
    float humidity = 0;

    if ( TEMPHUM28_OK == temphum28_read_temperature ( &temphum28, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
    }

    if ( TEMPHUM28_OK == temphum28_read_humidity ( &temphum28, &humidity ) )
    {
        log_printf ( &logger, " Humidity: %.1f %%RH\r\n\n", humidity );
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
