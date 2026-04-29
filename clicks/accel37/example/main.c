/*!
 * @file main.c
 * @brief Accel 37 Click example
 *
 * # Description
 * This example demonstrates the use of Accel 37 Click board by reading and
 * displaying the accelerometer data (X, Y, and Z axis) and an internal temperature
 * measurement in degrees Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the accelerometer and temperature measurements.
 * The results are displayed on the USB UART every 100 ms.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "accel37.h"

#ifndef MIKROBUS_POSITION_ACCEL37
    #define MIKROBUS_POSITION_ACCEL37 MIKROBUS_1
#endif

static accel37_t accel37;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel37_cfg_t accel37_cfg;  /**< Click config object. */

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
    accel37_cfg_setup( &accel37_cfg );
    ACCEL37_MAP_MIKROBUS( accel37_cfg, MIKROBUS_POSITION_ACCEL37 );
    err_t init_flag = accel37_init( &accel37, &accel37_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL37_ERROR == accel37_default_cfg ( &accel37 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    accel37_data_t meas_data;

    if ( ACCEL37_OK == accel37_get_data( &accel37, &meas_data ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", meas_data.temperature );
        log_printf( &logger, " ----------------- \r\n" );

        Delay_ms( 100 );
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
