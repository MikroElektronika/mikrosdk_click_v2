/*!
 * @file main.c
 * @brief Heart Rate 14 Click example
 *
 * # Description
 * This example demonstrates the use of Heart Rate 14 Click board by reading
 * and displaying PPG measurements which can be visualized on the SerialPlot application.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration for heart rate measurement.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then reads the PPG measurements and displays it on the
 * USB UART (SerialPlot).
 *
 * @note
 * We recommend using the SerialPlot tool for data visualizing.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "heartrate14.h"

#ifndef MIKROBUS_POSITION_HEARTRATE14
    #define MIKROBUS_POSITION_HEARTRATE14 MIKROBUS_1
#endif

static heartrate14_t heartrate14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate14_cfg_t heartrate14_cfg;  /**< Click config object. */

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
    heartrate14_cfg_setup( &heartrate14_cfg );
    HEARTRATE14_MAP_MIKROBUS( heartrate14_cfg, MIKROBUS_POSITION_HEARTRATE14 );
    if ( I2C_MASTER_ERROR == heartrate14_init( &heartrate14, &heartrate14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE14_ERROR == heartrate14_default_cfg ( &heartrate14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    heartrate14_fifo_data_t fifo_data = { 0 };

    if ( HEARTRATE14_OK == heartrate14_get_fifo_data( &heartrate14, &fifo_data ) )
    {
        /* In the default configuration, ledc1 holds the Green LED PPG signal.*/
        log_printf( &logger, "%lu\r\n", fifo_data.ledc1 );
    }
    else
    {
        log_info( &logger, " No new data available." );
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
