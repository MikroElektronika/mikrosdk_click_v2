/*!
 * @file main.c
 * @brief Gyro6 Click example
 *
 * # Description
 * This example demonstrates the use of Gyro 6 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the data to be ready, then reads the values of all three axis
 * and displays the results on the USB UART. The data sample rate is set to 10Hz by default,
 * therefore the data is being read approximately every 100ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gyro6.h"

static gyro6_t gyro6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    gyro6_cfg_t gyro6_cfg;  /**< Click config object. */

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
    gyro6_cfg_setup( &gyro6_cfg );
    GYRO6_MAP_MIKROBUS( gyro6_cfg, MIKROBUS_1 );
    err_t init_flag  = gyro6_init( &gyro6, &gyro6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( GYRO6_ERROR == gyro6_default_cfg ( &gyro6 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( gyro6_get_int_pin ( &gyro6 ) )
    {
        float x_axis_value = 0;
        float y_axis_value = 0;
        float z_axis_value = 0;

        if ( GYRO6_OK == gyro6_get_axis ( &gyro6, &x_axis_value, &y_axis_value, &z_axis_value ) )
        {
            log_printf( &logger, " X : %.2f\r\n", x_axis_value );
            log_printf( &logger, " Y : %.2f\r\n", y_axis_value );
            log_printf( &logger, " Z : %.2f\r\n\n", z_axis_value );
        }
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
