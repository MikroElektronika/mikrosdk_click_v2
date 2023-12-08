/*!
 * \file 
 * \brief 9Dof Click example
 * 
 * # Description
 * This application shows accelerometer, gyroscope
 * and magnetometer axes values.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO pins, I2C, LOG modules and
 * sets default configuration.
 * 
 * ## Application Task  
 * Gets accelerometer, gyroscope
 * and magnetometer axes data and LOGs those values.
 * 
 * \author Nenad Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c9dof.h"

// ------------------------------------------------------------------ VARIABLES

static c9dof_t c9dof;
static log_t logger;

c9dof_accel_data_t accel_data;
c9dof_gyro_data_t gyro_data;
c9dof_mag_data_t mag_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c9dof_cfg_t cfg;

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

    c9dof_cfg_setup( &cfg );
    C9DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c9dof_init( &c9dof, &cfg );
    
    c9dof_default_cfg ( &c9dof );
    Delay_ms( 1000 );
    
    log_printf( &logger, "              9DOF Click \r\n" );
    log_printf( &logger, "--------------------------------------\r\n" );
}

void application_task ( void )
{
    c9dof_read_accel( &c9dof, &accel_data );
    Delay_ms( 10 );
    
    c9dof_read_gyro( &c9dof, &gyro_data );
    Delay_ms( 10 );
    
    c9dof_read_mag( &c9dof, &mag_data );
    Delay_ms( 10 );
    
    log_printf( &logger, "   Accel    |    Gyro    |    Mag\r\n" );
    log_printf( &logger, "--------------------------------------\r\n" );
    log_printf( &logger, " X = %d | X = %d | X = %d\r\n", accel_data.x, gyro_data.x, mag_data.x );
    log_printf( &logger, " Y = %d | Y = %d | Y = %d\r\n", accel_data.y, gyro_data.y, mag_data.y );
    log_printf( &logger, " Z = %d | Z = %d | Z = %d\r\n", accel_data.z, gyro_data.z, mag_data.z );
    log_printf( &logger, "--------------------------------------\r\n" );
    Delay_ms( 2000 );
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
