/*!
 * @file main.c
 * @brief Gyro 9 Click example
 *
 * # Description
 * This library contains API for Gyro 9 Click driver.
 * The library initializes and defines the I2C and SPI bus drivers to 
 * write and read data from registers, as well as the default 
 * configuration for reading gyroscope data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or SPI module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Gyro 9 Click board™.
 * Measures and displays gyroscope angular rate for X-axis, Y-axis, and Z-axis.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gyro9.h"

static gyro9_t gyro9;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gyro9_cfg_t gyro9_cfg;  /**< Click config object. */

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
    gyro9_cfg_setup( &gyro9_cfg );
    GYRO9_MAP_MIKROBUS( gyro9_cfg, MIKROBUS_1 );
    err_t init_flag = gyro9_init( &gyro9, &gyro9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GYRO9_ERROR == gyro9_default_cfg ( &gyro9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "_________________\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    gyro9_axis_t gyro_axis;
    if ( gyro9_get_data_ready( &gyro9 ) )
    {
        if ( GYRO9_OK == gyro9_get_gyro_axis( &gyro9, &gyro_axis ) )
        {
            log_printf( &logger, " Gyro X: %.2f pds\r\n", gyro_axis.x );
            log_printf( &logger, " Gyro Y: %.2f pds\r\n", gyro_axis.y );
            log_printf( &logger, " Gyro Z: %.2f pds\r\n", gyro_axis.z );
            log_printf( &logger, "_________________\r\n" );
            Delay_ms ( 1000 );
        }
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
