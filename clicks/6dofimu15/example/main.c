/*!
 * \file 
 * \brief 6DofImu15 Click example
 * 
 * # Description
 * This demo exaple measures Angular rate and Acceleration rate.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI and I2C drivers, performs safety
 * check, applies default setup and writes an log.
 * 
 * ## Application Task  
 * Demonstrates use of 6DOF IMU 6 click board by reading
 * angular rate in milidegrees per second, and linear
 * acceleration rate in milligravities and displaying data
 * via USART terminal.
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

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
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
        log_printf( &logger, "   6DOF IMU 6 click    \r\n" );
        log_printf( &logger, "---------------------- \r\n" );
    }
    else
    {
        log_printf( &logger, "---------------------- \r\n" );
        log_printf( &logger, "    FATAL ERROR!!      \r\n" );
        log_printf( &logger, "---------------------- \r\n" );
        for ( ; ; );
    }

    c6dofimu15_device_conf_set( &c6dofimu15, C6DOFIMU15_PROP_EN );
    c6dofimu15_auto_inc_set( &c6dofimu15, C6DOFIMU15_PROP_EN );
    c6dofimu15_block_data_update_set( &c6dofimu15, C6DOFIMU15_PROP_EN );
    c6dofimu15_fifo_mode_set( &c6dofimu15, C6DOFIMU15_FIFO_DIS );
    c6dofimu15_accel_data_rate( &c6dofimu15, C6DOFIMU15_ODR_XL_104_HZ );
    c6dofimu15_accel_full_scale( &c6dofimu15, C6DOFIMU15_FS_XL_2_G );
    c6dofimu15_gyro_data_rate( &c6dofimu15, C6DOFIMU15_ODR_G_104_HZ );
    c6dofimu15_gyro_full_scale( &c6dofimu15, C6DOFIMU15_FS_G_2000_DPS );

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

    c6dofimu15_angular_rate( &c6dofimu15, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, "Angular rate:  \r\n" );
    log_printf( &logger, "X-axis: %.2f mdps \r\n", x_gyro );
    log_printf( &logger, "Y-axis: %.2f mdps \r\n", y_gyro );
    log_printf( &logger, "Z-axis: %.2f mdps \r\n", z_gyro );
    log_printf( &logger, "---------------------- \r\n" );

    c6dofimu15_acceleration_rate( &c6dofimu15, &x_accel, &y_accel, &z_accel );
    
    log_printf( &logger, "Acceleration rate:  \r\n" );
    log_printf( &logger, "X-axis: %.2f mg \r\n", x_accel );
    log_printf( &logger, "Y-axis: %.2f mg \r\n", y_accel );
    log_printf( &logger, "Z-axis: %.2f mg \r\n", z_accel );
    log_printf( &logger, "---------------------- \r\n" );

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
