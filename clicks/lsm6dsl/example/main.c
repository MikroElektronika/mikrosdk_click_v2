/*!
 * \file 
 * \brief Lsm6Dsl Click example
 * 
 * # Description
 * This app measures linear and angular velocity with six degrees of freedom.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of LSM6DSL Click board.
 * LSM6DSL Click communicates with register via SPI by write to register and read from register,
 * measured acceleration and gyroscope coordinates values ( X,Y,Z )
 * Result are being sent to the uart where you can track their changes.
 * All data logs on usb uart for aproximetly every 3 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lsm6dsl.h"

// ------------------------------------------------------------------ VARIABLES

static lsm6dsl_t lsm6dsl;
static log_t logger;
static lsm6dsl_accel_t accel;
static lsm6dsl_gyro_t gyro;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lsm6dsl_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lsm6dsl_cfg_setup( &cfg );
    LSM6DSL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lsm6dsl_init( &lsm6dsl, &cfg );

    lsm6dsl_default_cfg( &lsm6dsl );

    log_printf( &logger, "---------------------------------------\r\n" );
    log_printf( &logger, "|            LSM6DSL Click            |\r\n" );
    log_printf( &logger, "---------------------------------------\r\n" );
    log_printf( &logger, "|     Accel       |       Gyro        |\r\n" );
    log_printf( &logger, "---------------------------------------\r\n" );

    Delay_ms( 100 );
}

void application_task ( void )
{

    lsm6dsl_get_accel( &lsm6dsl, &accel, LSM6DSL_FULLSCALE_XL_2 );
    
    Delay_ms( 10 );
    
    lsm6dsl_get_gyro( &lsm6dsl, &gyro, LSM6DSL_FULLSCALE_G_245 );
    
    Delay_ms( 10 );

    log_printf( &logger, " Accel X : %.2f |  Gyro X : %.2f |\r\n", accel.accel_x, gyro.gyro_x );

    log_printf( &logger, " Accel Y : %.2f |  Gyro Y : %.2f |\r\n", accel.accel_y, gyro.gyro_y );

    log_printf( &logger, " Accel Z : %.2f |  Gyro Z : %.2f |\r\n", accel.accel_z, gyro.gyro_z );

    log_printf( &logger, "---------------------------------------\r\n" );

    Delay_ms( 3000 );
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
