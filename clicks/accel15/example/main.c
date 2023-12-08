/*!
 * @file main.c
 * @brief Accel15 Click example
 *
 * # Description
 * This library contains API for Accel 15 Click driver.
 * The library initializes and defines the I2C or SPI bus drivers 
 * to write and read data from registers. 
 * The library also includes a function for reading X-axis, Y-axis, and Z-axis data. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or SPI module, log UART, and additional pins. 
 * After the driver init, the app checks communication, 
 * sensor ID, and then executes a default configuration.
 *
 * ## Application Task
 * Measures and displays acceleration data for X-axis, Y-axis, and Z-axis. 
 * Results are being sent to the USART terminal where the user can track their changes. 
 * This task repeats at data output rate which is set to 12.5 Hz.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel15.h"

static accel15_t accel15;
static log_t logger;
static accel15_axis_t axis;

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    accel15_cfg_t accel15_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n-------------------------\r\n" );
    log_printf( &logger, "     Application Init    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );

    // Click initialization.
    accel15_cfg_setup( &accel15_cfg );
    ACCEL15_MAP_MIKROBUS( accel15_cfg, MIKROBUS_1 );
    err_t init_flag  = accel15_init( &accel15, &accel15_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    if ( ACCEL15_ERROR == accel15_check_id( &accel15 ) ) 
    {
        log_printf( &logger, "   Communication ERROR   \r\n" );
        log_printf( &logger, "     Reset the device    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        for ( ; ; );
    }
    
    if ( ACCEL15_ERROR == accel15_default_cfg ( &accel15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, "     Application Task    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    if ( ACCEL15_DRDY == accel15_get_int_1( &accel15 ) ) 
    {
        if ( ACCEL15_OK == accel15_get_axis_data( &accel15, &axis ) )
        {
            log_printf( &logger, "\tX : %d \r\n", axis.x );
            log_printf( &logger, "\tY : %d \r\n", axis.y );
            log_printf( &logger, "\tZ : %d \r\n", axis.z );
            log_printf( &logger, "-------------------------\r\n" );
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
