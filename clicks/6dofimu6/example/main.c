/*!
 * \file 
 * \brief 6DofImu6 Click example
 * 
 * # Description
 * 6DOF IMU 6 Click features a 6-axis MotionTracking device that combines a 3-axis gyroscope, 
 * a 3-axis accelerometer, and a Digital Motion Processor. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI and I2C drivers, performs safety check, applies default 
 * settings and writes an initial log.
 * 
 * ## Application Task  
 * Demonstrates the use of 6DOF IMU 6 click board by reading angular rate, acceleration rate 
 * and displaying data to USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu6.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu6_t c6dofimu6;
static log_t logger;

static uint8_t id_val;
static float x_accel;
static float y_accel;
static float z_accel;
static float x_gyro;
static float y_gyro;
static float z_gyro;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu6_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    c6dofimu6_cfg_setup( &cfg );
    C6DOFIMU6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu6_init( &c6dofimu6, &cfg );

    Delay_ms( 100 );
    c6dofimu6_generic_read ( &c6dofimu6, C6DOFIMU6_WHO_AM_I, &id_val, 1 );
    if ( id_val == C6DOFIMU6_WHO_AM_I_VAL )
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "   6DOF  IMU  6  click   \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        c6dofimu6_power ( &c6dofimu6, C6DOFIMU6_POWER_ON );
    }
    else
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "     FATAL  ERROR!!!     \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        for ( ; ; );
    }

    c6dofimu6_default_cfg( &c6dofimu6 );

    log_printf( &logger, "    ---Initialised---    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );

    Delay_ms( 100 );
}

void application_task ( void )
{
    c6dofimu6_angular_rate( &c6dofimu6, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, "Gyro \r\n" );

    log_printf( &logger, "X-axis: %.2f\r\n", x_gyro );
    log_printf( &logger, "Y-axis: %.2f\r\n", y_gyro );
    log_printf( &logger, "Z-axis: %.2f\r\n", z_gyro );
    log_printf( &logger, "---------------------\r\n" );

    c6dofimu6_acceleration_rate( &c6dofimu6, &x_accel, &y_accel, &z_accel );

    log_printf( &logger, "Accel \r\n" );

    log_printf( &logger, "X-axis: %.2f\r\n", x_accel );
    log_printf( &logger, "Y-axis: %.2f\r\n", y_accel );
    log_printf( &logger, "Z-axis: %.2f\r\n", z_accel );
    log_printf( &logger, "---------------------\r\n\r\n" );
    Delay_ms( 1000 );
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
