/*!
 * @file main.c
 * @brief Smart DOF 4 Click example
 *
 * # Description
 * This example demonstrates the use of Smart DOF 4 Click board by reading
 * the accelerometer, gyroscope, and magnetometer data measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration enabling
 * accelerometer, gyroscope, and magnetometer sensors with an output data rate of 10Hz.
 * After that, it reads the software version, part number, and build number information.
 *
 * ## Application Task
 * Reads the accelerometer (g), gyroscope (dps), and magnetometer (uT) measurements
 * and displays results on the USB UART every 100ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartdof4.h"

static smartdof4_t smartdof4;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartdof4_cfg_t smartdof4_cfg;  /**< Click config object. */

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
    smartdof4_cfg_setup( &smartdof4_cfg );
    SMARTDOF4_MAP_MIKROBUS( smartdof4_cfg, MIKROBUS_1 );
    err_t init_flag = smartdof4_init( &smartdof4, &smartdof4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTDOF4_ERROR == smartdof4_default_cfg ( &smartdof4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    smartdof4_pid_t pid;
    if ( SMARTDOF4_OK == smartdof4_read_pid ( &smartdof4, &pid ) )
    {
        log_printf ( &logger, " SW Version: %u.%u.%u\r\n", ( uint16_t ) pid.sw_ver_major, 
                                                           ( uint16_t ) pid.sw_ver_minor, 
                                                           ( uint16_t ) pid.sw_ver_patch );
        log_printf ( &logger, " SW Part Number: %lu\r\n", pid.sw_part_num );
        log_printf ( &logger, " SW Build Number: %lu\r\n\n", pid.sw_build_num );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static smartdof4_axis_t accel, gyro, mag;
    if ( SMARTDOF4_OK == smartdof4_read_data ( &smartdof4, &accel, &gyro, &mag ) )
    {
        log_printf ( &logger, " Accel X: %.3f g\r\n", accel.x );
        log_printf ( &logger, " Accel Y: %.3f g\r\n", accel.y );
        log_printf ( &logger, " Accel Z: %.3f g\r\n", accel.z );
        log_printf ( &logger, " Gyro X: %.1f dps\r\n", gyro.x );
        log_printf ( &logger, " Gyro Y: %.1f dps\r\n", gyro.y );
        log_printf ( &logger, " Gyro Z: %.1f dps\r\n", gyro.z );
        log_printf ( &logger, " Mag X: %.1f uT\r\n", mag.x );
        log_printf ( &logger, " Mag Y: %.1f uT\r\n", mag.y );
        log_printf ( &logger, " Mag Z: %.1f uT\r\n\n", mag.z );
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
