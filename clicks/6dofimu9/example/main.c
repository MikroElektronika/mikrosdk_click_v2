/*!
 * \file 
 * \brief 6DOFIMU9 Click example
 * 
 * # Description
 * This application measure 3-axis gyroscope and a 3-axis accelerometer.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C, check device ID,
 * configure accelerometer and gyroscope, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of 6DOF IMU 9 Click board.
 * Measured and display Accel and Gyro data coordinates values for X-axis, Y-axis and Z-axis.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes for every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu9.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu9_t c6dofimu9;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu9_cfg_t cfg;
    uint8_t device_id;

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

    c6dofimu9_cfg_setup( &cfg );
    C6DOFIMU9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu9_init( &c6dofimu9, &cfg );

    log_printf( &logger, "       Driver  Initialization        \r\n" );
    log_printf( &logger, "-------------------------------------\r\n" );
    Delay_ms( 100 );
    
    device_id = c6dofimu9_get_device_id( &c6dofimu9 );

    if ( device_id == C6DOFIMU9_DEVICE_ID )
    {
        log_printf( &logger, "       SUCCESS        \r\n" );
        log_printf( &logger, "-------------------------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "                ERROR              \r\n" );
        log_printf( &logger, "            RESET DEVICE           \r\n" );
        log_printf( &logger, "-----------------------------------\r\n" );
        for ( ; ; );
    }

    c6dofimu9_set_gyro_config_lp_mode( &c6dofimu9, C6DOFIMU9_GYRO_AVERAGE_1x );
    c6dofimu9_set_gyro_measurement_range( &c6dofimu9, C6DOFIMU9_GYRO_FULL_SCALE_250dps );
    c6dofimu9_set_accel_measurement_range( &c6dofimu9, C6DOFIMU9_ACCEL_FULL_SCALE_2g );
    c6dofimu9_set_accel_avg_filter_mode( &c6dofimu9, C6DOFIMU9_ACCEL_AVERAGE_4_SAMPLES );
    
    log_printf( &logger, "            Start measurement             \r\n" );
    log_printf( &logger, "-------------------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( )
{
    int16_t accel_axis_x;
    int16_t accel_axis_y;
    int16_t accel_axis_z;
    int16_t gyro_axis_x;
    int16_t gyro_axis_y;
    int16_t gyro_axis_z;

    c6dofimu9_get_accel_data( &c6dofimu9, &accel_axis_x, &accel_axis_y, &accel_axis_z );
    Delay_ms( 10 );
    c6dofimu9_get_gyro_data( &c6dofimu9, &gyro_axis_x,  &gyro_axis_y, &gyro_axis_z );
    Delay_ms( 10 );

    log_printf( &logger, " Accel X : %d ", accel_axis_x );
    log_printf( &logger, "    |     ");
    log_printf( &logger, " Gyro X : %d \r\n", gyro_axis_x );

    log_printf( &logger, " Accel Y : %d ", accel_axis_y );
    log_printf( &logger, "    |     ");
    log_printf( &logger, " Gyro Y : %d \r\n", gyro_axis_y );

    log_printf( &logger, " Accel Z : %d ", accel_axis_z );
    log_printf( &logger, "    |     ");
    log_printf( &logger, " Gyro Z : %d \r\n", gyro_axis_z );

    log_printf( &logger, "-------------------------------------\r\n" );
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
