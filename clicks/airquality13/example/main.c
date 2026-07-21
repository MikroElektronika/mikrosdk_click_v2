/*!
 * @file main.c
 * @brief Air Quality 13 Click example
 *
 * # Description
 * This example demonstrates the use of Air Quality 13 Click board by reading
 * PM1.0, PM2.5 and PM10 mass concentration measurements from the Bosch BMV080
 * ultra-miniature particulate matter sensor and displaying the results on the
 * USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Calls airquality13_serve_interrupt every 100 ms to process the sensor FIFO.
 * When a new measurement is ready (approximately once per second), logs the
 * PM1.0, PM2.5 and PM10 mass concentrations to the USB UART.
 * If the optical path is obstructed, a warning is printed instead.
 *
 * @note
 * This driver requires the Bosch BMV080 SDK which is not included in the repository
 * due to licensing restrictions. Before building, refer to the README file located
 * in the lib_airquality13/bosch/ directory for instructions on how to obtain the SDK
 * and copy the required files into the correct locations.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "airquality13.h"

#ifndef MIKROBUS_POSITION_AIRQUALITY13
    #define MIKROBUS_POSITION_AIRQUALITY13 MIKROBUS_1
#endif

static airquality13_t airquality13;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airquality13_cfg_t airquality13_cfg;  /**< Click config object. */

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
    airquality13_cfg_setup( &airquality13_cfg );
    AIRQUALITY13_MAP_MIKROBUS( airquality13_cfg, MIKROBUS_POSITION_AIRQUALITY13 );
    err_t init_flag = airquality13_init( &airquality13, &airquality13_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    /* A char array with a size of 13 elements must be allocated for the sensor ID. */
    char sensor_id[ AIRQUALITY13_SENSOR_ID_LEN ] = { 0 };
    
    if ( AIRQUALITY13_OK == airquality13_get_sensor_id( &airquality13, sensor_id ) )
    {
        log_printf( &logger, " Sensor ID: %s\r\n", sensor_id );
    }
    
    if ( AIRQUALITY13_ERROR == airquality13_default_cfg ( &airquality13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Waiting for first measurement (~2s)...\r\n" );
    log_printf( &logger, " The first 100 samples should be treated as warm-up data\r\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    airquality13_data_t meas_data = { 0 };
    
    /* A new measurement is available approximately every 1.03 seconds in continuous mode. 
     * airquality13_serve_interrupt must be called at least once per second to prevent FIFO overflow,
     * it is recommended to call it every 100 ms. */
    if ( AIRQUALITY13_OK == airquality13_serve_interrupt( &airquality13, &meas_data ) )
    {
        if ( meas_data.data_ready )
        {
            if ( !meas_data.is_obstructed )
            {
                log_printf( &logger, " Runtime in sec : %.2f s\r\n", meas_data.runtime_in_sec );
                log_printf( &logger, " PM1.0 : %.2f ug/m3\r\n", meas_data.pm1_mass_concentration );
                log_printf( &logger, " PM2.5 : %.2f ug/m3\r\n", meas_data.pm2_5_mass_concentration );
                log_printf( &logger, " PM10  : %.2f ug/m3\r\n", meas_data.pm10_mass_concentration );
                log_printf( &logger, " ----------------------\r\n\r\n" );
            }
            else
            {
                log_printf( &logger, " WARNING: Sensor obstructed!\r\n" );
            }
        }
    }

    Delay_ms( 100 );
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
