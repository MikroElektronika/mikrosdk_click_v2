/*!
 * @file main.c
 * @brief PiezoAccel Click example
 *
 * # Description
 * This application demonstrates the performance
 * of Piezo Accel click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of UART LOG and SPI click drivers.
 * Additionally, a default config is performed for
 * "out of the box" Piezo Accel click settings.
 * Calibration is optional and is used to correct
 * the power supply offset of the sensor.
 *
 * ## Application Task
 * The ADC is constantly read and converted to a
 * g-force acceleration unit. Data is sent via LOG
 * every 20 ms and works on MikroPlot for graphical
 * representation of the sensor results.
 *
 * *note:*
 * This demo app is intended to be used with MikroPlot data
 * visualization tool for clear understanding of the results.
 * https://www.mikroe.com/mikroplot-data-visualization-tool
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "piezoaccel.h"

static piezoaccel_t piezoaccel;
static log_t logger;

static piezoaccel_setup_t setup_cfg_data;
static double time_var = 0;
static const int time_incr = 20;


void application_init ( void ) {
    log_cfg_t log_cfg;                  /**< Logger config object. */
    piezoaccel_cfg_t piezoaccel_cfg;    /**< Click config object. */

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

    piezoaccel_cfg_setup( &piezoaccel_cfg );
    PIEZOACCEL_MAP_MIKROBUS( piezoaccel_cfg, MIKROBUS_1 );
    err_t init_flag = piezoaccel_init( &piezoaccel, &piezoaccel_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    piezoaccel_default_cfg( &piezoaccel, &setup_cfg_data );
    log_info( &logger, " Application Task " );
    Delay_ms( 200 );
}

void application_task ( void ) {
    float read_val;
    
    read_val = piezoaccel_g_unit_read( &piezoaccel, &setup_cfg_data );
    log_printf( &logger, "%.2f,%.2f\r\n", read_val, time_var );
    time_var += time_incr;
    Delay_ms( time_incr );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
