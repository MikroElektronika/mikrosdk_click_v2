/*!
 * \file 
 * \brief 9Dof3 Click example
 * 
 * # Description
 * This click introduces a small-scale absolute orientation sensor in the class of low-noise 
 * 9-axis measurement units. It comprises the full functionality of a triaxial, low-g acceleration 
 * sensor, a triaxial angular rate sensor and a triaxial geomagnetic sensor. All three sensor 
 * components can be operated and addressed independently from each other. 9DOF 3 Click offers 
 * both SPI and I2C digital interfaces
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C or SPI, check communication, 
 * set default configuration for accelerometer, gyroscope and magnetometer, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of 9DOF 3 Click board.
 * Measured and display Accel, Gyroscope and Magnetometer
 * data coordinates values for X-axis, Y-axis and Z-axis.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes for every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c9dof3.h"

// ------------------------------------------------------------------ VARIABLES

static c9dof3_t c9dof3;
static log_t logger;

c9dof3_accel_t accel_data;
c9dof3_gyro_t gyro_data;
c9dof3_mag_t mag_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c9dof3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c9dof3_cfg_setup( &cfg );
    C9DOF3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c9dof3_init( &c9dof3, &cfg );

    if ( c9dof3_check_communication( &c9dof3 ) == C9DOF3_ACC_COMM_SUCCESS  |
                                                  C9DOF3_GYRO_COMM_SUCCESS |
                                                  C9DOF3_MAG_COMM_SUCCESS )
    {
        log_printf( &logger, "    Communication OK     \r\n" );
    }
    else
    {
        log_printf( &logger, "   Communication ERROR   \r\n" );
        log_printf( &logger, "     Reset the device    \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        for ( ; ; );
    }
    
    log_printf( &logger, "-------------------------\r\n" );
    c9dof3_default_cfg( &c9dof3 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    c9dof3_get_data ( &c9dof3, &accel_data, &gyro_data, &mag_data );

    log_printf( &logger, " Accel X: %d | Gyro X: %d |  Mag X: %d\r\n", accel_data.x, gyro_data.x, mag_data.x );
    log_printf( &logger, " Accel Y: %d | Gyro Y: %d |  Mag Y: %d\r\n", accel_data.y, gyro_data.y, mag_data.y );
    log_printf( &logger, " Accel Z: %d | Gyro Z: %d |  Mag Z: %d\r\n", accel_data.z, gyro_data.z, mag_data.z );

    log_printf( &logger, "-------------------------\r\n" );

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
