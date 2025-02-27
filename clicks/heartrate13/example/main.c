/*!
 * @file main.c
 * @brief Heart Rate 13 Click example
 *
 * # Description
 * This example demonstrates the use of Heart Rate 13 Click board by reading and displaying
 * the PPG measurements which can be visualized on the SerialPlot application.
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
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "heartrate13.h"

static heartrate13_t heartrate13;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate13_cfg_t heartrate13_cfg;  /**< Click config object. */

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
    heartrate13_cfg_setup( &heartrate13_cfg );
    HEARTRATE13_MAP_MIKROBUS( heartrate13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate13_init( &heartrate13, &heartrate13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE13_ERROR == heartrate13_default_cfg ( &heartrate13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    heartrate13_pd_data_t pd_data;
    if ( HEARTRATE13_OK == heartrate13_get_pd_data ( &heartrate13, &pd_data ) )
    {
        log_printf ( &logger, "%u\r\n", pd_data.pd3 );
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
