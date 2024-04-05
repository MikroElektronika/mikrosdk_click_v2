/*!
 * \file 
 * \brief Mpu9Dof Click example
 * 
 * # Description
 * MPU 9DOF click carries the world’s first 9-axis Motion Tracking device. It comprises two chips: one that contains 
 * a 3-axis accelerometer, a 3-axis gyroscope, and a DMP (digital motion processor); 
 * the other is a 3-axis digital compass.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C, initialize MPU-9150 XL G & MPU-9150 MAG and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of MPU 9DOF Click board.
 * Measured accel, gyro and magnetometar coordinates values ( X, Y, Z )
 * and temperature value in degrees celsius [ �C ] are being sent to the uart where you can track their changes.
 * All data logs on usb uart for aproximetly every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mpu9dof.h"

// ------------------------------------------------------------------ VARIABLES

static mpu9dof_t mpu9dof;
static log_t logger;

static int16_t accel_x;
static int16_t accel_y;
static int16_t accel_z;
static int16_t gyro_x;
static int16_t gyro_y;
static int16_t gyro_z;
static int16_t mag_x;
static int16_t mag_y;
static int16_t mag_z;
static float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mpu9dof_cfg_t cfg;

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

    mpu9dof_cfg_setup( &cfg );
    MPU9DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mpu9dof_init( &mpu9dof, &cfg );

    Delay_10ms( );
    mpu9dof_default_cfg ( &mpu9dof );
}

void application_task ( void )
{
    mpu9dof_read_accel( &mpu9dof, &accel_x, &accel_y, &accel_z );
    Delay_10ms( );
    mpu9dof_read_gyro( &mpu9dof, &gyro_x,  &gyro_y, &gyro_z );
    Delay_10ms( );
    temperature = mpu9dof_read_temperature( &mpu9dof );
    Delay_10ms( );
    mpu9dof_read_mag( &mpu9dof, &mag_x,  &mag_y, &mag_z );
    Delay_10ms( );

    log_printf( &logger, " Accel X : %d   |   Gyro X : %d   |   Mag X : %d \r\n", accel_x, gyro_x, mag_x );
    log_printf( &logger, " Accel Y : %d   |   Gyro Y : %d   |   Mag Y : %d \r\n", accel_y, gyro_y, mag_y );
    log_printf( &logger, " Accel Z : %d   |   Gyro Z : %d   |   Mag Z : %d \r\n", accel_z, gyro_z, mag_z );
    Delay_10ms( );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n" );
    Delay_10ms( );
    log_printf( &logger, "Temperature: %.2f C\r\n", temperature );
    Delay_100ms( );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "\r\n");
    Delay_ms ( 1000 );
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
