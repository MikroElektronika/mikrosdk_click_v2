/*!
 * \file 
 * \brief 6DofImu15 Click example
 * 
 * # Description
 * This example demonstrates the use of 6DOF IMU 15 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, checks the communication and sets the device 
 * default configuration.
 * 
 * ## Application Task  
 * Measures acceleration and gyroscope data and displays the results on USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu15.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu15_t c6dofimu15;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu15_cfg_t cfg;

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

    c6dofimu15_cfg_setup( &cfg );
    C6DOFIMU15_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu15_init( &c6dofimu15, &cfg );
    Delay_ms( 100 );

    if ( c6dofimu15_who_im_i( &c6dofimu15 ) )
    {
        log_printf( &logger, "---------------------- \r\n" );
        log_printf( &logger, "   6DOF IMU 15 click    \r\n" );
        log_printf( &logger, "---------------------- \r\n" );
    }
    else
    {
        log_printf( &logger, "---------------------- \r\n" );
        log_printf( &logger, "    FATAL ERROR!!      \r\n" );
        log_printf( &logger, "---------------------- \r\n" );
        for ( ; ; );
    }

    c6dofimu15_default_cfg( &c6dofimu15 );

    log_printf( &logger, "  ---Initialised---    \r\n" );
    log_printf( &logger, "---------------------- \r\n" );

    Delay_ms( 100 );
}

void application_task ( void )
{
    float x_accel;
    float y_accel;
    float z_accel;
    float x_gyro;
    float y_gyro;
    float z_gyro;

    c6dofimu15_acceleration_rate( &c6dofimu15, &x_accel, &y_accel, &z_accel );
    c6dofimu15_angular_rate( &c6dofimu15, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, " Accel X: %.2f \t Gyro X: %.2f\r\n", x_accel, x_gyro );
    log_printf( &logger, " Accel Y: %.2f \t Gyro Y: %.2f\r\n", y_accel, y_gyro );
    log_printf( &logger, " Accel Z: %.2f \t Gyro Z: %.2f\r\n", z_accel, z_gyro );
    log_printf( &logger, "----------------------------------\r\n");

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
