/*!
 * @file main.c
 * @brief Accel 31 Click example
 *
 * # Description
 * This example demonstrates the use of Accel 31 Click board by reading and displaying 
 * the accelerometer data (X, Y, and Z axis) and a temperature measurement in degrees Celsius.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Checks for a new data ready indication and then reads the accelerometer and temperature
 * measurements. The results are displayed on the USB UART at 12.5 Hz output data rate.
 * 
 * @note
 * The Click board determines the communication protocol at the first communication check
 * after power-up. In the case of I2C, the IC responds with NACK on the first check,
 * which blocks the I2C bus on some MCUs. Re-running the program (without power cycling
 * the Click board power supply) should unlock the communication and solve this issue.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel31.h"

static accel31_t accel31;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel31_cfg_t accel31_cfg;  /**< Click config object. */

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
    accel31_cfg_setup( &accel31_cfg );
    ACCEL31_MAP_MIKROBUS( accel31_cfg, MIKROBUS_1 );
    err_t init_flag = accel31_init( &accel31, &accel31_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL31_ERROR == accel31_default_cfg ( &accel31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    accel31_data_t meas_data;
    if ( ACCEL31_OK == accel31_get_data ( &accel31, &meas_data ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
        log_printf( &logger, " Temperature: %d degC\r\n\n", ( int16_t ) meas_data.temperature );
        Delay_ms ( 80 );
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
