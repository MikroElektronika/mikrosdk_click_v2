/*!
 * @file main.c
 * @brief Accel20 Click example
 *
 * # Description
 * This library contains API for Accel 20 Click driver.
 * The library initializes and defines the I2C or SPI bus drivers 
 * to write and read data from registers. 
 * The library also includes a function for reading X-axis, Y-axis, and Z-axis data. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or SPI module, log UART, and additional pins. 
 * After the driver init, the app executes a default configuration,
 * checks communication and device ID. 
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Accel 20 Click board™.
 * Measures and displays acceleration data for X-axis, Y-axis, and Z-axis. 
 * Results are being sent to the USART terminal where the user can track their changes. 
 * This task repeats every 1 sec.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel20.h"

static accel20_t accel20;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    accel20_cfg_t accel20_cfg;  /**< Click config object. */

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
    accel20_cfg_setup( &accel20_cfg );
    ACCEL20_MAP_MIKROBUS( accel20_cfg, MIKROBUS_1 );
    err_t init_flag  = accel20_init( &accel20, &accel20_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    accel20_default_cfg ( &accel20 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "      Accel 20 Click     \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 100 ); 
    
    if ( accel20_check_id( &accel20 ) == ACCEL20_OK ) 
    {
        log_printf( &logger, "     Communication OK    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    else 
    {
        log_printf( &logger, "   Communication ERROR   \r\n" );
        log_printf( &logger, "     Reset the device    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );

        for ( ; ; );
    }
    
    log_printf( &logger, "       Accel Data:       \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 100 ); 
}

void application_task ( void )
{
    static accel20_axis_t axis;
    
    if ( accel20_get_int_1( &accel20 ) == ACCEL20_INT1_DATA_READY )
    {
        accel20_get_axis_data( &accel20, &axis );
        log_printf( &logger, "\tX : %5d \r\n\tY : %5d \r\n\tZ : %5d \r\n", axis.x, axis.y, axis.z );
        log_printf( &logger, "-------------------------\r\n" );
        Delay_ms( 1000 );     
    }
    Delay_ms( 1 );  
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
