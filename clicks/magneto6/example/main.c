/*!
 * @file main.c
 * @brief Magneto 6 Click example
 *
 * # Description
 * This example demonstrates the use of Magneto 6 click board by reading
 * the magnetic field strength from 3 axes as well as the ambient temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads data from the sensor and displays them on the USB UART once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneto6.h"

static magneto6_t magneto6;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto6_cfg_t magneto6_cfg;  /**< Click config object. */

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
    magneto6_cfg_setup( &magneto6_cfg );
    MAGNETO6_MAP_MIKROBUS( magneto6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == magneto6_init( &magneto6, &magneto6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO6_ERROR == magneto6_default_cfg ( &magneto6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    magneto6_data_t data_res;
    if ( MAGNETO6_OK == magneto6_read_data ( &magneto6, &data_res ) )
    {
        log_printf( &logger, " X data: %.1f mT\r\n", data_res.x_data );
        log_printf( &logger, " Y data: %.1f mT\r\n", data_res.y_data );
        log_printf( &logger, " Z data: %.1f mT\r\n", data_res.z_data );
        log_printf( &logger, " Temperature: %.2f degC\r\n\n", data_res.temperature );
    }
    Delay_ms ( 1000 );
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
