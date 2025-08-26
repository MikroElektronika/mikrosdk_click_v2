/*!
 * @file main.c
 * @brief Accel 33 Click example
 *
 * # Description
 * This example demonstrates the use of the Accel 33 Click board by periodically reading
 * acceleration data from all three axes (X, Y, Z) and displaying the results on the UART terminal.
 * It waits for the data ready interrupt before reading new data to ensure synchronization.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Accel 33 Click driver, then sets up the default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt and reads acceleration values for the X, Y, and Z axes,
 * then displays the values in g units via the UART terminal. The INT2 pin is used to signal
 * when new data is ready to be read from the sensor.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel33.h"

static accel33_t accel33;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel33_cfg_t accel33_cfg;  /**< Click config object. */

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
    accel33_cfg_setup( &accel33_cfg );
    ACCEL33_MAP_MIKROBUS( accel33_cfg, MIKROBUS_1 );
    err_t init_flag = accel33_init( &accel33, &accel33_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL33_ERROR == accel33_default_cfg ( &accel33 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    accel33_axes_t accel;
    // Wait for data ready interrupt
    while ( accel33_get_int2_pin ( &accel33 ) );

    if ( ACCEL33_OK == accel33_get_accel ( &accel33, &accel ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n\n", accel.z );
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
