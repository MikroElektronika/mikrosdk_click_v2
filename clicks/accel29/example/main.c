/*!
 * @file main.c
 * @brief Accel 29 Click example
 *
 * # Description
 * This example demonstrates the use of Accel 29 click board by reading and
 * displaying the accelerometer data (X, Y, and Z axis) averaged from 100 samples.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the click default configuration, and calibrates
 * the accel data offsets.
 *
 * ## Application Task
 * Reads and displays on the USB UART the accelerometer data (X, Y, and Z axis)
 * averaged from 100 samples.
 *
 * @note
 * This click board should be used for high g applications of up to +-200g. 
 * It is not recommended for low g applications because of its high scale
 * factor which is about 48.83 mg per LSB.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel29.h"

/**
 * Starting accel position, used for calibrating accel offset. 
 * Should be in a range from -24.96 to 24.765 g.
 * Offset calibrating scale factor is 0.195 g per LSB.
 */
#define ACCEL29_CALIB_X     0.0f
#define ACCEL29_CALIB_Y     0.0f
#define ACCEL29_CALIB_Z     1.0f

static accel29_t accel29;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel29_cfg_t accel29_cfg;  /**< Click config object. */

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
    accel29_cfg_setup( &accel29_cfg );
    ACCEL29_MAP_MIKROBUS( accel29_cfg, MIKROBUS_1 );
    err_t init_flag = accel29_init( &accel29, &accel29_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL29_ERROR == accel29_default_cfg ( &accel29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    accel29_axes_t calib_axes;
    calib_axes.x = ACCEL29_CALIB_X;
    calib_axes.y = ACCEL29_CALIB_Y;
    calib_axes.z = ACCEL29_CALIB_Z;
    if ( ACCEL29_ERROR == accel29_calibrate_offset ( &accel29, calib_axes ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    accel29_axes_t axes;
    if ( ACCEL29_OK == accel29_get_avg_axes ( &accel29, ACCEL29_NUM_OF_SAMPLES, &axes ) )
    {
        log_printf( &logger, " X: %.1f g\r\n", axes.x );
        log_printf( &logger, " Y: %.1f g\r\n", axes.y );
        log_printf( &logger, " Z: %.1f g\r\n\n", axes.z );
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
