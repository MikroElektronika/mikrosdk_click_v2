/*!
 * @file main.c
 * @brief Barometer 14 Click example
 *
 * # Description
 * This example demonstrates the use of Barometer 14 Click board by reading and
 * displaying the pressure, temperature and acceleration measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the Click default configuration and
 * displays sensor ID and product code on the USB UART.
 *
 * ## Application Task
 * Reads the pressure [kPa], temperature [degC] and acceleration [g] measurements
 * and displays the results on the USB UART every second.
 *
 * @note
 * It is highly recommended to lock the serial interface selection using the
 * barometer14_lock_ser_interface() function commented out in the default configuration
 * to avoid performing the serial interface selection procedure at every Power On reset
 * or Softreset (User Manual, Chapter 1, page 5). This operation is irreversible and permanently
 * locks the device to the currently selected serial interface.
 * 
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "barometer14.h"

#ifndef MIKROBUS_POSITION_BAROMETER14
    #define MIKROBUS_POSITION_BAROMETER14 MIKROBUS_1
#endif

static barometer14_t barometer14;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer14_cfg_t barometer14_cfg;  /**< Click config object. */

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
    barometer14_cfg_setup( &barometer14_cfg );
    BAROMETER14_MAP_MIKROBUS( barometer14_cfg, MIKROBUS_POSITION_BAROMETER14 );
    err_t init_flag = barometer14_init( &barometer14, &barometer14_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER14_ERROR == barometer14_default_cfg ( &barometer14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint32_t sensor_id = 0;
    uint16_t product_code = 0;
    barometer14_read_id( &barometer14, &sensor_id, &product_code );
    log_printf( &logger, " Sensor ID: 0x%.8lX\r\n", sensor_id );
    log_printf( &logger, " Product Code: 0x%.4X\r\n", product_code );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " --------------------------------\r\n" );
}

void application_task ( void )
{
    float   pressure     = 0;
    float   temperature  = 0;
    float   acceleration = 0;
    uint8_t meas_status  = 0;

    if ( BAROMETER14_OK == barometer14_measure_pressure( &barometer14, &meas_status, &pressure ) )
    {
        log_printf( &logger, " Pressure    : %.2f kPa\r\n", pressure );
        if ( BAROMETER14_MEAS_STATUS_OK != meas_status )
        {
            log_printf( &logger, " Pressure status : 0x%.2X\r\n", ( uint16_t ) meas_status );
        }
    }

    if ( BAROMETER14_OK == barometer14_measure_temp( &barometer14, &meas_status, &temperature ) )
    {
        log_printf( &logger, " Temperature : %.2f degC\r\n", temperature );
        if ( BAROMETER14_MEAS_STATUS_OK != meas_status )
        {
            log_printf( &logger, " Temperature status : 0x%.2X\r\n", ( uint16_t ) meas_status );
        }
    }

    if ( BAROMETER14_OK == barometer14_measure_accel( &barometer14, &meas_status, &acceleration ) )
    {
        log_printf( &logger, " Acceleration: %.2f g\r\n", acceleration );
        if ( BAROMETER14_MEAS_STATUS_OK != meas_status )
        {
            log_printf( &logger, " Acceleration status : 0x%.2X\r\n", ( uint16_t ) meas_status );
        }
    }

    log_printf( &logger, " --------------------------------\r\n" );
    Delay_ms( 1000 );
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
