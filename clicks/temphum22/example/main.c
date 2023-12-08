/*!
 * @file main.c
 * @brief TempHum 22 Click example
 *
 * # Description
 * This example demonstrates the use of Temp & Hum 22 click board by reading
 * the temperature and humidity data.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the sensor software reset and then reads
 * and displays the sensor unique serial number.
 *
 * ## Application Task
 * Reads the temperature (degC) and the relative humidity (%RH) data and 
 * displays the results on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum22.h"

static temphum22_t temphum22;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum22_cfg_t temphum22_cfg;  /**< Click config object. */

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
    temphum22_cfg_setup( &temphum22_cfg );
    TEMPHUM22_MAP_MIKROBUS( temphum22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum22_init( &temphum22, &temphum22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM22_OK == temphum22_soft_reset ( &temphum22 ) )
    {
        log_printf ( &logger, " Software reset\r\n" );
    }
    Delay_1sec ( );
    
    uint32_t serial_num;
    if ( TEMPHUM22_OK == temphum22_read_serial_num ( &temphum22, &serial_num ) )
    {
        log_printf ( &logger, " Serial number: 0x%.8LX\r\n", serial_num );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature, humidity;
    if ( TEMPHUM22_OK == temphum22_read_measurement_high_precision ( &temphum22, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n\n", humidity );
        Delay_ms ( 1000 );
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
