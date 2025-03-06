/*!
 * @file main.c
 * @brief Accel 32 Click example
 *
 * # Description
 * This example demonstrates the use of Accel 32 Click board by reading and
 * displaying the accelerometer data (X, Y, and Z axis) and a temperature
 * measurement in degrees Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the accelerometer and temperature measurements.
 * The results are displayed on the USB UART every 100 ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel32.h"

static accel32_t accel32;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel32_cfg_t accel32_cfg;  /**< Click config object. */

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
    accel32_cfg_setup( &accel32_cfg );
    ACCEL32_MAP_MIKROBUS( accel32_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == accel32_init( &accel32, &accel32_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL32_ERROR == accel32_default_cfg ( &accel32 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    accel32_data_t meas_data;
    if ( ACCEL32_OK == accel32_get_data ( &accel32, &meas_data ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", meas_data.temperature );
        Delay_ms ( 100 );
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
