/*!
 * @file main.c
 * @brief TempHum 25 Click example
 *
 * # Description
 * This example demonstrates the use of TempHum 25 click board by reading
 * the temperature and humidity data.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the device reset, reads and displays
 * the sensor unique serial number, and then starts the measurements with 1 MPS.
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
#include "temphum25.h"

static temphum25_t temphum25;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum25_cfg_t temphum25_cfg;  /**< Click config object. */

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
    temphum25_cfg_setup( &temphum25_cfg );
    TEMPHUM25_MAP_MIKROBUS( temphum25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum25_init( &temphum25, &temphum25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    temphum25_reset_device ( &temphum25 );

    uint32_t serial_num = 0;
    if ( TEMPHUM25_OK == temphum25_read_serial_num ( &temphum25, &serial_num ) )
    {
        log_printf ( &logger, " Serial number: 0x%.8LX\r\n", serial_num );
    }

    temphum25_start_measurement ( &temphum25, TEMPHUM25_CMD_MEAS_CONT_REP_HIGH_MPS_1 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    float humidity = 0;
    if ( TEMPHUM25_OK == temphum25_read_measurement ( &temphum25, &temperature, &humidity ) )
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
