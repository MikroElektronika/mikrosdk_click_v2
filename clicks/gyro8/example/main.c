/*!
 * @file main.c
 * @brief Gyro 8 Click example
 *
 * # Description
 * This example demonstrates the use of Gyro 8 click board by reading and displaying
 * the temperature and angular rate measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and the click board, and reads the serial ID number which
 * is marked on the sensor lid.
 *
 * ## Application Task
 * Reads the temperature and angular rate measurements every 100ms and displays the results
 * on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gyro8.h"

static gyro8_t gyro8;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gyro8_cfg_t gyro8_cfg;  /**< Click config object. */

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
    gyro8_cfg_setup( &gyro8_cfg );
    GYRO8_MAP_MIKROBUS( gyro8_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == gyro8_init( &gyro8, &gyro8_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GYRO8_ERROR == gyro8_default_cfg ( &gyro8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t serial_id;
    if ( GYRO8_OK == gyro8_read_serial_id ( &gyro8, &serial_id ) )
    {
        log_printf ( &logger, " Serial ID: %lu\r\n", serial_id );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float temperature, angular_rate;
    if ( GYRO8_OK == gyro8_read_temperature ( &gyro8, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f degC\r\n", temperature );
    }
    if ( GYRO8_OK == gyro8_read_angular_rate ( &gyro8, &angular_rate ) )
    {
        log_printf ( &logger, " Angular rate: %.2f dps\r\n\n", angular_rate );
    }
    Delay_ms ( 100 );
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
