/*!
 * @file main.c
 * @brief TempHum 27 Click example
 *
 * # Description
 * This example demonstrates the use of the TempHum 27 Click board by reading ambient temperature
 * and relative humidity values using periodic measurements. After initializing the device and 
 * starting the periodic mode at 1 Hz, the application waits for the ALERT pin to indicate data 
 * readiness and then logs the measurements to the USB UART terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click driver, resets the device, reads and logs the sensor ID, 
 * and starts periodic measurements with a 1-second output rate.
 *
 * ## Application Task
 * Waits for the ALERT pin to go low indicating new measurement data is available, then reads 
 * and logs the temperature and humidity values.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum27.h"

static temphum27_t temphum27;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    temphum27_cfg_t temphum27_cfg;  /**< Click config object. */

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
#ifdef INTERFACE_LOGGER_UART
    log_cfg.is_interrupt = false;
#endif
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    temphum27_cfg_setup( &temphum27_cfg );
    TEMPHUM27_MAP_MIKROBUS( temphum27_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == temphum27_init( &temphum27, &temphum27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint32_t sensor_id = 0;
    if ( TEMPHUM27_ERROR == temphum27_read_sensor_id ( &temphum27, &sensor_id ) )
    {
        log_error( &logger, " Sensor ID read." );
        for ( ; ; );
    }
    log_printf ( &logger, " Sensor ID: 0x%.8LX\r\n", sensor_id );

    if ( TEMPHUM27_OK == temphum27_start_periodic_meas ( &temphum27, TEMPHUM27_PERIODIC_FREQ_1S ) )
    {
        log_printf ( &logger, " Periodic measurement started with 1Hz output\r\n" );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    float humidity = 0;

    // Wait for a periodic data ready (alert pin falling edge)
    while ( !temphum27_get_alert_pin ( &temphum27 ) );
    while ( temphum27_get_alert_pin ( &temphum27 ) );

    if ( TEMPHUM27_OK == temphum27_read_data_periodic ( &temphum27, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n\n", humidity );
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
