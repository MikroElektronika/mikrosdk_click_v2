/*!
 * @file main.c
 * @brief Accel 24 Click example
 *
 * # Description
 * This example demonstrates the use of Accel 24 click board by reading and displaying 
 * accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads and displays the accel data (X, Y, and Z axis) as well as temperature measurements
 * on the USB UART every 100ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel24.h"

static accel24_t accel24;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel24_cfg_t accel24_cfg;  /**< Click config object. */

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
    accel24_cfg_setup( &accel24_cfg );
    ACCEL24_MAP_MIKROBUS( accel24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == accel24_init( &accel24, &accel24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL24_ERROR == accel24_default_cfg ( &accel24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    accel24_data_t meas_data;
    // Wait for data ready indication
    while ( accel24_get_int_pin ( &accel24 ) );
    
    if ( ACCEL24_OK == accel24_read_data ( &accel24, &meas_data ) )
    {
        log_printf( &logger, " X: %.3f g\r\n", meas_data.x );
        log_printf( &logger, " Y: %.3f g\r\n", meas_data.y );
        log_printf( &logger, " Z: %.3f g\r\n", meas_data.z );
        log_printf( &logger, " Temperature: %.2f degC\r\n", meas_data.temperature );
    }
    Delay_ms ( 100 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
