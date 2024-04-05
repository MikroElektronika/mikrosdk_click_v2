/*!
 * @file main.c
 * @brief Accel19 Click example
 *
 * # Description
 * This library contains API for Accel 19 Click driver.
 * The library initializes and defines the I2C or SPI bus drivers 
 * to write and read data from registers. 
 * The library also includes a function for reading X-axis, Y-axis, and Z-axis data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or SPI module, log UART, and additional pins. 
 * After the driver init, the app executes a default configuration
 * and checks communication and device ID.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Accel 19 Click board™.
 * Measures and displays acceleration data for X-axis, Y-axis, and Z-axis. 
 * Results are being sent to the USART terminal where the user can track their changes. 
 * This task repeats every 1 sec.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel19.h"

static accel19_t accel19;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    accel19_cfg_t accel19_cfg;  /**< Click config object. */

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
    accel19_cfg_setup( &accel19_cfg );
    ACCEL19_MAP_MIKROBUS( accel19_cfg, MIKROBUS_1 );
    err_t init_flag  = accel19_init( &accel19, &accel19_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 1000 );
    
    if ( ACCEL19_ERROR == accel19_default_cfg ( &accel19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( ACCEL19_ERROR == accel19_check_device_id( &accel19 ) ) 
    {
        log_printf( &logger, "   Communication ERROR   \r\n" );
        log_printf( &logger, "     Reset the device    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 1000 ); 
}

void application_task ( void )
{
    static accel19_axis_t axis;
    
    if ( ACCEL19_STATUS_DRDY == accel19_data_ready( &accel19 ) )
    {
        accel19_get_axis_data( &accel19, &axis );
        log_printf( &logger, "\tX : %d \r\n\tY : %d \r\n\tZ : %d \r\n",axis.x, axis.y, axis.z );
        log_printf( &logger, "-------------------------\r\n" );
        Delay_ms ( 1000 );     
    }
    Delay_ms ( 1 );  
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
