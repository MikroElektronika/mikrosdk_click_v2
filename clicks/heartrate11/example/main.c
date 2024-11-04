/*!
 * @file main.c
 * @brief HeartRate11 Click example
 *
 * # Description
 * This example demonstrates the use of Heart Rate 11 Click board by reading and displaying
 * the PPG1 (HR) values which can be visualized on the SerialPlot application.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration for heart rate measurement.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then reads the values of PPG from FIFO and displays it on the
 * USB UART (SerialPlot) every 32ms approximately.
 *
 * @note
 * We recommend using the SerialPlot tool for data visualizing.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "heartrate11.h"

static heartrate11_t heartrate11;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate11_cfg_t heartrate11_cfg;  /**< Click config object. */

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
    heartrate11_cfg_setup( &heartrate11_cfg );
    HEARTRATE11_MAP_MIKROBUS( heartrate11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate11_init( &heartrate11, &heartrate11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE11_ERROR == heartrate11_default_cfg ( &heartrate11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    // Wait for the data ready interrupt indication
    while ( heartrate11_get_int_pin ( &heartrate11 ) );
    
    uint32_t ppg;
    if ( HEARTRATE11_OK == heartrate11_read_fifo ( &heartrate11, &ppg ) )
    {
        log_printf ( &logger, "%lu\r\n", ppg );
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
