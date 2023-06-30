/*!
 * @file main.c
 * @brief Accel 28 Click example
 *
 * # Description
 * This example demonstrates the use of Accel 28 click board by reading and
 * displaying the accelerometer data (X, Y, and Z axis).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the click default configuration.
 *
 * ## Application Task
 * Reads and displays on the USB UART the accelerometer data (X, Y, and Z axis)
 * when it is available. 
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "accel28.h"

static accel28_t accel28;
static log_t logger;
accel28_data_t accel_data;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel28_cfg_t accel28_cfg;  /**< Click config object. */

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
    accel28_cfg_setup( &accel28_cfg );
    ACCEL28_MAP_MIKROBUS( accel28_cfg, MIKROBUS_1 );
    err_t init_flag = accel28_init( &accel28, &accel28_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    uint8_t id_data = 0;
    
    accel28_generic_read( &accel28, ACCEL28_REG_WHO_AM_I, &id_data, 1 );
    if ( ACCEL28_WHO_AM_I_VALUE != id_data )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( ACCEL28_ERROR == accel28_default_cfg ( &accel28 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
        
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    err_t error_flag = ACCEL28_OK;
    if ( ACCEL28_PIN_STATE_HIGH == accel28_get_int_state( &accel28 ) )
    {
        uint8_t tmp_data;
        error_flag = accel28_read_reg( &accel28, ACCEL28_REG_STATUS, &tmp_data );
         if ( ( tmp_data & ACCEL28_STATUS_ZYX_DATA_AVL ) && ( ACCEL28_OK == error_flag ) )
        {
            error_flag = accel28_get_data( &accel28, &accel_data );
            if ( ACCEL28_OK == error_flag )
            {
                log_printf( &logger, " X-axis %.2f mg\r\n", accel_data.x_data );
                log_printf( &logger, " Y-axis %.2f mg\r\n", accel_data.y_data );
                log_printf( &logger, " Z-axis %.2f mg\r\n", accel_data.z_data );
                log_printf( &logger, " = = = = = = = = = = = = = =\r\n" );
            }
        }
    }
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
