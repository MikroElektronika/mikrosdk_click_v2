/*!
 * @file main.c
 * @brief Accel 36 Click example
 *
 * # Description
 * This example demonstrates the use of Accel 36 Click board by reading and
 * displaying the accelerometer data (X, Y, and Z axis).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the accelerometer measurements.
 * The results are displayed on the USB UART every 100 ms.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "accel36.h"

#ifndef MIKROBUS_POSITION_ACCEL36
    #define MIKROBUS_POSITION_ACCEL36 MIKROBUS_1
#endif

static accel36_t accel36;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel36_cfg_t accel36_cfg;  /**< Click config object. */

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
    accel36_cfg_setup( &accel36_cfg );
    ACCEL36_MAP_MIKROBUS( accel36_cfg, MIKROBUS_POSITION_ACCEL36 );
    err_t init_flag = accel36_init( &accel36, &accel36_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( ACCEL36_ERROR == accel36_default_cfg ( &accel36 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    accel36_axes_t axes;

    if ( ACCEL36_OK == accel36_get_accel( &accel36, &axes ) )
    {
        log_printf( &logger, " X: %.3f g\r\n", axes.x );
        log_printf( &logger, " Y: %.3f g\r\n", axes.y );
        log_printf( &logger, " Z: %.3f g\r\n", axes.z );
        log_printf( &logger, " ---------------------------------\r\n" );
    }

    Delay_ms( 100 );
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
