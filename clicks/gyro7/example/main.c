/*!
 * @file main.c
 * @brief Gyro7 Click example
 *
 * # Description
 * This example demonstrates the use of Gyro 7 click board by reading and displaying
 * the values of X and Y axis in degrees per second and the chip internal temperature in Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets the sample rate
 * to 40 Hz, gyroscope resolution to 374 dps, and enables the data ready interrupt.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then reads the values of X and Y gyroscope axis as well as
 * the chip internal temperature and displays the results on the USB UART. The data sample rate is 
 * set to 40Hz by default, therefore the data is being read approximately every 25ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gyro7.h"

static gyro7_t gyro7;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gyro7_cfg_t gyro7_cfg;  /**< Click config object. */

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
    gyro7_cfg_setup( &gyro7_cfg );
    GYRO7_MAP_MIKROBUS( gyro7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == gyro7_init( &gyro7, &gyro7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GYRO7_ERROR == gyro7_default_cfg ( &gyro7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( gyro7_get_int_pin ( &gyro7 ) )
    {
        float x_axis, y_axis, temperature;
        if ( GYRO7_OK == gyro7_read_gyroscope ( &gyro7, &x_axis, &y_axis ) )
        {
            log_printf( &logger, " X : %.2f dps\r\n", x_axis );
            log_printf( &logger, " Y : %.2f dps\r\n", y_axis );
        }
        if ( GYRO7_OK == gyro7_read_temperature ( &gyro7, &temperature ) )
        {
            log_printf( &logger, " Temperature : %.2f C\r\n\n", temperature );
        }
    }
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
