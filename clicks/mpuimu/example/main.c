/*!
 * \file 
 * \brief MpuImu Click example
 * 
 * # Description
 * MPU IMU Click carries the integrated 6-axis motion tracking device 
 * that combines 3-axis gyroscope and accelerometer.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * Measured Accel and Gyro coordinates (X,Y,Z) and Temperature in degrees C 
 * are being sent to the UART where you can track their changes. 
 * All data logs on USB UART for every 1 sec.
 *  
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mpuimu.h"

float temperature;

// ------------------------------------------------------------------ VARIABLES

static mpuimu_t mpuimu;
static log_t logger;

mpuimu_accel_data_t accel_data;
mpuimu_gyro_data_t gyro_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mpuimu_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms ( 100 );

    //  Click initialization.

    mpuimu_cfg_setup( &cfg );
    MPUIMU_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mpuimu_init( &mpuimu, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ----  MPU IMU Click ----\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    mpuimu_default_cfg ( &mpuimu );
    Delay_ms ( 1000 );
    
    
    log_printf( &logger, " ---- Initialization ---\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    mpuimu_read_accel( &mpuimu, &accel_data );
    Delay_ms ( 100 );
    mpuimu_read_gyro( &mpuimu, &gyro_data );
    Delay_ms ( 100 );
    temperature = mpuimu_read_temperature( &mpuimu );
    Delay_ms ( 100 );
    
    log_printf( &logger, "    Accel    |    Gyro    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " X = %6d  | X = %6d \r\n", accel_data.accel_x, gyro_data.gyro_x );
    log_printf( &logger, " Y = %6d  | Y = %6d \r\n", accel_data.accel_y, gyro_data.gyro_y );
    log_printf( &logger, " Z = %6d  | Z = %6d \r\n", accel_data.accel_z, gyro_data.gyro_z );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "      TEMP = %0.2f C\r\n", temperature );
    log_printf( &logger, "--------------------------\r\n" ); 
    
    software_reset ( &mpuimu );
    Delay_ms ( 1000 );
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
