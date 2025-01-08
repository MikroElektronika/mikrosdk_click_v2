/*!
 * @file main.c
 * @brief Air Quality 12 Click example
 *
 * # Description
 * This example demonstrates the use of Air Quality 12 Click board by reading the
 * IAQ 2nd Gen measurements and displays the results on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the Click board to the default configuration.
 * Then it reads the sensor product ID, firmware version, and the 48-bit tracking number.
 *
 * ## Application Task
 * Checks the data ready interrupt pin and then reads the IAQ 2nd Gen measurements
 * and displays the results on the USB UART. The GP1 LED turns ON during the data reading.
 * The data sample rate is set to 3 seconds for the IAQ 2nd Gen operating mode, and the first
 * 100 samples upon startup should be ignored since the sensor is in the warm-up phase.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "airquality12.h"

static airquality12_t airquality12;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airquality12_cfg_t airquality12_cfg;  /**< Click config object. */

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
    airquality12_cfg_setup( &airquality12_cfg );
    AIRQUALITY12_MAP_MIKROBUS( airquality12_cfg, MIKROBUS_1 );
    if ( AIRQUALITY12_OK != airquality12_init( &airquality12, &airquality12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AIRQUALITY12_ERROR == airquality12_default_cfg ( &airquality12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    airquality12_info_t info;
    if ( AIRQUALITY12_OK == airquality12_get_sensor_info ( &airquality12, &info ) )
    {
        log_printf( &logger, " ---- Sensor info ----\r\n" );
        log_printf( &logger, " Product ID: 0x%.4X\r\n", info.product_id );
        log_printf( &logger, " FW version: %u.%u.%u\r\n", ( uint16_t ) info.fw_ver_major, 
                                                          ( uint16_t ) info.fw_ver_minor, 
                                                          ( uint16_t ) info.fw_ver_patch );
        log_printf( &logger, " Tracking number: 0x%.2X%.2X%.2X%.2X%.2X%.2X\r\n", 
                    ( uint16_t ) info.tracking_num[ 5 ], ( uint16_t ) info.tracking_num[ 4 ], 
                    ( uint16_t ) info.tracking_num[ 3 ], ( uint16_t ) info.tracking_num[ 2 ], 
                    ( uint16_t ) info.tracking_num[ 1 ], ( uint16_t ) info.tracking_num[ 0 ] );
        log_printf( &logger, " ---------------------\r\n" );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    airquality12_results_t results = { 0 };

    if ( airquality12_get_int_pin ( &airquality12 ) )
    {
        airquality12_set_gp1_pin ( &airquality12, 1 );
        if ( AIRQUALITY12_OK == airquality12_get_measurement ( &airquality12, &results ) )
        {
            log_printf ( &logger, " Sample number: %u\r\n", ( uint16_t ) results.sample_num );
            log_printf ( &logger, " IAQ: %.1f\r\n", results.iaq );
            log_printf ( &logger, " TVOC: %.2f mg/m^3\r\n", results.tvoc );
            log_printf ( &logger, " ETOH: %.2f ppm\r\n", results.etoh );
            log_printf ( &logger, " ECO2: %u ppm\r\n", results.eco2 );
            log_printf ( &logger, " rel_IAQ: %u\r\n\n", results.rel_iaq );
        }
        airquality12_set_gp1_pin ( &airquality12, 0 );
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
