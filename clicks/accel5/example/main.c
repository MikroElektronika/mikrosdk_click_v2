/*!
 * \file 
 * \brief Accel5 Click example
 * 
 * # Description
 * This application allows linear motion and gravitational force measurements.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and settings accelerometer data range and mode.
 * 
 * ## Application Task  
 * Reads the accel X / Y / Z axis data, every 500 ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel5.h"

// ------------------------------------------------------------------ VARIABLES

static accel5_t accel5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    accel5_cfg_setup( &cfg );
    ACCEL5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel5_init( &accel5, &cfg );
    accel5_soft_reset( &accel5 );
    accel5_default_cfg( &accel5, ACCEL5_CFG_0_NORMAL_MODE, ACCEL5_CFG_1_ACC_RANGE_4g );

}

void application_task ( void )
{
    int16_t x_axis_data;
    int16_t y_axis_data;
    int16_t z_axis_data;
    
    //  Task implementation.

    x_axis_data = accel5_get_axis( &accel5, ACCEL5_X_AXIS );
    log_printf ( &logger, " X axis : %d \r\n  ", x_axis_data );
    
    y_axis_data = accel5_get_axis( &accel5, ACCEL5_Y_AXIS );
    log_printf ( &logger, " Y axis : %d \r\n  ", y_axis_data );

    z_axis_data = accel5_get_axis( &accel5, ACCEL5_Z_AXIS );
    log_printf ( &logger, " Z axis : %d \r\n  ", z_axis_data );
    
    Delay_ms( 500 );
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
