/*!
 * @file main.c
 * @brief Accel 30 Click example
 *
 * # Description
 * This library contains API for Accel 30 Click driver.
 * The library initializes and defines the I2C or SPI bus drivers 
 * to write and read data from registers. 
 * The library also includes a function for reading X-axis, Y-axis, and Z-axis data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or SPI module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the Accel 30 Click board™.
 * Measures and displays acceleration data for X-axis, Y-axis, and Z-axis.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel30.h"

static accel30_t accel30;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel30_cfg_t accel30_cfg;  /**< Click config object. */

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
    accel30_cfg_setup( &accel30_cfg );
    ACCEL30_MAP_MIKROBUS( accel30_cfg, MIKROBUS_1 );
    err_t init_flag = accel30_init( &accel30, &accel30_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( ACCEL30_ERROR == accel30_default_cfg ( &accel30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "       Accel Data       \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 100 ); 
}

void application_task ( void )
{
    static accel30_axis_t axis;
    if ( ACCEL30_OK == accel30_get_axis( &accel30, &axis ) )
    {
        log_printf( &logger, "\tX : %d \r\n\tY : %d \r\n\tZ : %d \r\n", axis.x, axis.y, axis.z );
        log_printf( &logger, "------------------------\r\n" );
    }
    Delay_ms( 1000 );
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
