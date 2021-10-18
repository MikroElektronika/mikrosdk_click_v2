/*!
 * \file 
 * \brief Accel13 Click example
 * 
 * # Description
 * This application enables reading acceleration and tapping data on all 3 axes,
 * using I2C or SPI communication.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, Test communication, 
 * starts chip configuration for measurement and Temperature reads.
 * 
 * ## Application Task  
 * Reads Accelerometer data and detects tap on the axis
 * 
 * *note:* 
 * The example is the basic functionality of the IIS2DLPC sensor, 
 * it is possible to read the acceleration data and detect Tap on all 3 axes.
 * For other settings and improvements in reading accuracy, 
 * you need to further set up the registers and set the sensor to your conditions.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel13.h"

// ------------------------------------------------------------------ VARIABLES

static accel13_t accel13;
static log_t logger;
static accel13_axis_t axis;
static accel13_tap_t tap;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel13_cfg_t cfg;
    uint8_t device_id;
    float temperature;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    accel13_cfg_setup( &cfg );
    ACCEL13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel13_init( &accel13, &cfg );

    accel13_generic_read_bytes( &accel13, ACCEL13_REG_WHO_AM_I, &device_id, 1 );

    if ( device_id != ACCEL13_DEF_WHO_AM_I )
    {
        log_printf( &logger, "*\\*/*\\*/ Communication ERROR !!! \\*/*\\*/*" );
        for ( ; ; );
    }
    log_printf( &logger, "---- Communication OK!!! ----\r\n" );
    Delay_100ms( );

    // Configuration

    accel13_default_cfg ( &accel13 );

    accel13_generic_write_single_byte( &accel13, ACCEL13_REG_CTRL_6, ACCEL13_CTRL6_BW_FILT_ODR_2 |
                                                                     ACCEL13_CTRL6_FULL_SCALE_2g |
                                                                     ACCEL13_CTRL6_FDS_LOW_PASS |
                                                                     ACCEL13_CTRL6_LOW_NOISE_ENABLE );

    // Temperature

    temperature = accel13_get_temperature( &accel13 );
    log_printf( &logger, " Temperature : %f.2 \r\n", temperature);
}

void application_task ( void )
{

    // Reads Accel data
    
    accel13_get_axis_data( &accel13, &axis );

    log_printf( &logger, "---- Accel axis data ----\r\n\n" );
    
    log_printf( &logger, "* X : %d \r\n", axis.x );
   
    log_printf( &logger, "* Y : %d \r\n", axis.y);

    log_printf( &logger, "* Z : %d \r\n", axis.z);
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 300 );
    
    // Detections Tap on the axis
    
    accel13_get_tap_status( &accel13, &tap );

    if ( tap.tap_x == 0x01 )
    {
        log_printf( &logger, "---- Tap on the X axis ----\r\n" );
    }

    if ( tap.tap_y == 0x01 )
    {
        log_printf( &logger, "---- Tap on the Y axis ----\r\n" );
    }

    if ( tap.tap_z == 0x01 )
    {
        log_printf( &logger, "---- Tap on the Z axis ----\r\n" );
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
