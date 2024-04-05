/*!
 * @file main.c
 * @brief Accel 27 Click example
 *
 * # Description
 * This example demonstrates the use of Accel 27 click board by reading and displaying 
 * the accelerometer data (X, Y, and Z axis) averaged from 100 samples.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads and displays on the USB UART the accelerometer data (X, Y, and Z axis) averaged from 100 samples.
 *
 * @note
 * This click board should be used for high g applications of up to +-400g. It is not recommended
 * for low g applications because of its high scale factor which is about 200 mg per LSB.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel27.h"

// The number of data samples for averaging
#define NUM_OF_SAMPLES  100

static accel27_t accel27;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel27_cfg_t accel27_cfg;  /**< Click config object. */

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
    accel27_cfg_setup( &accel27_cfg );
    ACCEL27_MAP_MIKROBUS( accel27_cfg, MIKROBUS_1 );
    err_t init_flag = accel27_init( &accel27, &accel27_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL27_ERROR == accel27_default_cfg ( &accel27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    accel27_axes_t axes = { 0 };
    uint16_t cnt = 0;
    while ( cnt < NUM_OF_SAMPLES )
    {
        // Wait for data ready indication
        while ( !accel27_get_int1_pin ( &accel27 ) );

        accel27_axes_t tmp_axes;
        if ( ACCEL27_OK == accel27_get_axes ( &accel27, &tmp_axes ) )
        {
            axes.x += tmp_axes.x;
            axes.y += tmp_axes.y;
            axes.z += tmp_axes.z;
            cnt++;
        }
    }
    axes.x = axes.x / NUM_OF_SAMPLES;
    axes.y = axes.y / NUM_OF_SAMPLES;
    axes.z = axes.z / NUM_OF_SAMPLES;
    log_printf( &logger, " X: %.1f g\r\n", axes.x );
    log_printf( &logger, " Y: %.1f g\r\n", axes.y );
    log_printf( &logger, " Z: %.1f g\r\n\n", axes.z );
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
