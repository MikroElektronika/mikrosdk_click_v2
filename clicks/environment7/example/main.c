/*!
 * @file main.c
 * @brief Environment 7 Click example
 *
 * # Description
 * This example demonstrates the use of the Environment 7 Click board, which provides 
 * temperature, humidity, and CO2 concentration measurements. The example initializes 
 * the device, reads sensor IDs, and continuously logs environmental data.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger, retrieves and logs the product and serial numbers, and starts
 * the measurement in continuous mode with 1Hz sampling rate.
 *
 * ## Application Task
 * Continuously reads and logs temperature (degC) and humidity (%RH), and CO2 concentration (ppm)
 * from sensors.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "environment7.h"

static environment7_t environment7;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    environment7_cfg_t environment7_cfg;  /**< Click config object. */

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
    environment7_cfg_setup( &environment7_cfg );
    ENVIRONMENT7_MAP_MIKROBUS( environment7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == environment7_init( &environment7, &environment7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint32_t prod_num = 0;
    uint32_t serial_msb = 0;
    uint32_t serial_lsb = 0;
    if ( ENVIRONMENT7_OK != environment7_read_id ( &environment7, &prod_num, &serial_msb, &serial_lsb ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    log_printf ( &logger, " Product number: 0x%.8LX\r\n", prod_num );
    log_printf ( &logger, " Serial number: 0x%.8LX%.8LX\r\n", serial_msb, serial_lsb );
    
    if ( ENVIRONMENT7_OK == environment7_set_meas_mode ( &environment7, ENVIRONMENT7_MEAS_MODE_START_CONTINUOUS ) )
    {
        log_printf ( &logger, " Continuous measurement started (1 Hz output)\r\n" );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    float humidity = 0;
    uint16_t co2_concentration = 0;

    if ( ENVIRONMENT7_OK == environment7_read_meas ( &environment7, &co2_concentration, &temperature, &humidity ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
        log_printf ( &logger, " Humidity: %.2f %%RH\r\n", humidity );
        log_printf ( &logger, " CO2: %u ppm\r\n\n", co2_concentration );
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
