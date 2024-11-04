/*!
 * \file 
 * \brief 9dof2 Click example
 * 
 * # Description
 * This example demonstrates the use of 9DOF 2 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI and device drivers, performs safety check, 
 * applies default configuration and writes an initial log.
 * 
 * ## Application Task  
 * Reads the angular and acceleration rates and displays the values of X, Y, and Z axis
 * on the USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c9dof2.h"

// ------------------------------------------------------------------ VARIABLES

static c9dof2_t c9dof2;
static log_t logger;

uint8_t id_val;
float x_accel;
float y_accel;
float z_accel;
float x_gyro;
float y_gyro;
float z_gyro;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c9dof2_cfg_t cfg;

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

    c9dof2_cfg_setup( &cfg );
    C9DOF2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c9dof2_init( &c9dof2, &cfg );

    c9dof2_dev_rst( &c9dof2 );
    Delay_ms ( 1000 );

    id_val = c9dof2_read_byte ( &c9dof2, C9DOF2_WHO_AM_I_ICM20948 );
     
    if ( id_val == C9DOF2_WHO_AM_I_ICM20948_VAL )
    {
        log_printf( &logger, "--------------------\r\n" );
        log_printf( &logger, "   9DOF  2  Click   \r\n" );
        log_printf( &logger, "--------------------\r\n" );
        c9dof2_power ( &c9dof2, C9DOF2_POWER_ON );
    }
    else
    {
        log_printf(  &logger, "--------------------\r\n" );
        log_printf(  &logger, "   FATAL ERROR!!!   \r\n" );
        log_printf(  &logger, "--------------------\r\n" );
        for ( ; ; );
    }
    
    c9dof2_def_settings( &c9dof2 );

    log_printf(  &logger, "--- Initialised ---\r\n" );
    log_printf(  &logger, "--------------------\r\n" );

    Delay_ms ( 1000 );
}

void application_task ( void )
{
    //  Task implementation.
    
    c9dof2_angular_rate( &c9dof2, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, "Angular rate: \r\n" );

    log_printf( &logger, "X-axis: %.2f \r\n", x_gyro );

    log_printf( &logger, "Y-axis: %.2f \r\n", y_gyro );

    log_printf( &logger, "Z-axis: %.2f \r\n", z_gyro );

    log_printf( &logger, "---------------------\r\n" );

    c9dof2_acceleration_rate( &c9dof2, &x_accel, &y_accel, &z_accel );

    log_printf( &logger, "Acceleration rate: \r\n" );

    log_printf( &logger, "X-axis: %.2f \r\n", x_accel );

    log_printf( &logger, "Y-axis: %.2f \r\n", y_accel );

    log_printf( &logger, "Z-axis: %.2f \r\n", z_accel );

    log_printf( &logger, "---------------------\r\n" );

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
