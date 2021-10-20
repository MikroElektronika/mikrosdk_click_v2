/*!
 * @file main.c
 * @brief TempHum15 Click example
 *
 * # Description
 * This demo app represents the performance of the
 * Temp&Hum 15 click board. The log displays the
 * temperature and humidity obtained from the sensor.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of UART LOG and I2C drivers.
 * The application also performs reset upon init.
 *
 * ## Application Task
 * Temperature and humidity data are being acquired
 * every two seconds. If the acquisition fails, LOG
 * states that no data is available.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "temphum15.h"

static temphum15_t temphum15;
static log_t logger;

static float temperature;
static float humidity;

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    temphum15_cfg_t temphum15_cfg;  /**< Click config object. */

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

    temphum15_cfg_setup( &temphum15_cfg );
    TEMPHUM15_MAP_MIKROBUS( temphum15_cfg, MIKROBUS_1 );
    err_t init_flag = temphum15_init( &temphum15, &temphum15_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    Delay_ms( 100 );
    temphum15_default_cfg( &temphum15 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) {
    err_t status_data;
    
    status_data = temphum15_get_temp_and_hum( &temphum15, TEMPHUM15_MODE_HIGH_PRECISION, &temperature, &humidity );
    if ( status_data == TEMPHUM15_SUCCESS ) {
        log_printf( &logger, "----------------------------\r\n" );
        log_printf( &logger, "> Temperature : %.2f C\r\n", temperature );
        log_printf( &logger, "> Humidity: %.2f %RH\r\n", humidity );
    } else {
        log_printf( &logger, "----------------------------\r\n" );
        log_printf( &logger, "> No data\r\n" );
    }
    Delay_ms( 2000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
