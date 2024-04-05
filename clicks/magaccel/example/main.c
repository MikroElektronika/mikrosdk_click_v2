/*!
 * @file main.c
 * @brief MagAccel Click example
 *
 * # Description
 * This library contains API for the MagAccel Click driver.
 * The library initializes and defines the I2C drivers to 
 * write and read data from registers, as well as the default 
 * configuration for reading accelerator data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the MagAccel Click board.
 * Measures and displays acceleration data for the X-axis, Y-axis, and Z-axis 
 * and the presence of a magnetic field. 
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magaccel.h"

static magaccel_t magaccel;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magaccel_cfg_t magaccel_cfg;  /**< Click config object. */

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
    magaccel_cfg_setup( &magaccel_cfg );
    MAGACCEL_MAP_MIKROBUS( magaccel_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == magaccel_init( &magaccel, &magaccel_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGACCEL_ERROR == magaccel_default_cfg ( &magaccel ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "_________________\r\n" );
}

void application_task ( void ) 
{
    if ( MAGACCEL_DATA_READY == magaccel_check_data_ready( &magaccel ) )
    {
        magaccel_axes_t acc_axis;
        magaccel_get_axes_data( &magaccel, &acc_axis );
        
        if ( MAGACCEL_DET_MAG_FIELD == magaccel_check_mag_field( &magaccel ) )
        {
            log_printf( &logger, " Presence of a magnetic field\r\n" );
            log_printf( &logger, "_________________\r\n" );
        }
        
        log_printf( &logger, " Accel X: %.2f mg\r\n", acc_axis.x );
        log_printf( &logger, " Accel Y: %.2f mg\r\n", acc_axis.y );
        log_printf( &logger, " Accel Z: %.2f mg\r\n", acc_axis.z );
        log_printf( &logger, "_________________\r\n" );
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
