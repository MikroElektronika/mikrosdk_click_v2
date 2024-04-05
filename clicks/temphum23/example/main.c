/*!
 * @file main.c
 * @brief TempHum 23 Click example
 *
 * # Description
 * This example demonstrates the use of Temp & Hum 23 click board by reading
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
#include "temphum23.h"

static temphum23_t temphum23;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum23_cfg_t temphum23_cfg;  /**< Click config object. */

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
    temphum23_cfg_setup( &temphum23_cfg );
    TEMPHUM23_MAP_MIKROBUS( temphum23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum23_init( &temphum23, &temphum23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TEMPHUM23_OK == temphum23_soft_reset ( &temphum23 ) )
    {
        log_printf ( &logger, " Software reset\r\n" );
    }
    Delay_1sec ( );
    
    uint32_t serial_num;
    if ( TEMPHUM23_OK == temphum23_read_serial_num ( &temphum23, &serial_num ) )
    {
        log_printf ( &logger, " Serial number: 0x%.8LX\r\n", serial_num );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature, humidity;
    if ( TEMPHUM23_OK == temphum23_read_measurement_high_precision ( &temphum23, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n\n", humidity );
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
