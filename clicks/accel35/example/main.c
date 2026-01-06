/*!
 * @file main.c
 * @brief Accel 35 Click example
 *
 * # Description
 * This example demonstrates the use of the Accel 35 Click board by reading 
 * acceleration and temperature data from the onboard 3-axis accelerometer.
 * The measured values are displayed via the UART terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board and applies the default configuration.
 *
 * ## Application Task
 * Reads the acceleration values in X, Y, and Z axis as well as the internal 
 * temperature, then displays the results on the UART terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel35.h"

static accel35_t accel35;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel35_cfg_t accel35_cfg;  /**< Click config object. */

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
    accel35_cfg_setup( &accel35_cfg );
    ACCEL35_MAP_MIKROBUS( accel35_cfg, MIKROBUS_1 );
    err_t init_flag = accel35_init( &accel35, &accel35_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL35_ERROR == accel35_default_cfg ( &accel35 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    accel35_data_t meas_data;
    if ( ACCEL35_OK == accel35_get_data ( &accel35, &meas_data ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
        log_printf( &logger, " Temperature: %.2f degC\r\n\n", meas_data.temperature );
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
