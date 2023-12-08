/*!
 * \file 
 * \brief 6DofImu11 Click example
 * 
 * # Description
 * Designed to strike a balance between current consumption and noise performance with excellent bias stability over temperature
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C, check device ID, sets default configuration, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of 6DOF IMU 11 Click board.
 * Measured and display Accel and Magnetometer magnetic field 
 * strength values for X-axis, Y-axis and Z-axis. 
 * Results are being sent to the Uart Terminal where
 * you can track their changes. 
 * All data logs write on USB uart changes for every 2 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu11.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu11_t c6dofimu11;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu11_cfg_t cfg;

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

    c6dofimu11_cfg_setup( &cfg );
    C6DOFIMU11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu11_init( &c6dofimu11, &cfg );

    if ( c6dofimu11_check_id( &c6dofimu11 ) == C6DOFIMU11_CHECK_ID_SUCCESS )
    {
        log_printf( &logger, "         SUCCESS          \r\n" );
        log_printf( &logger, "--------------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "          ERROR           \r\n" );
        log_printf( &logger, "     Reset the device     \r\n" );
        log_printf( &logger, "--------------------------\r\n" );
        for ( ; ; );
    }

    c6dofimu11_default_cfg(  &c6dofimu11 );

    log_printf( &logger, "    Set default config    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
   c6dofimu11_mag_t mag_data;
   c6dofimu11_accel_t accel_data;
   
    c6dofimu11_read_accel ( &c6dofimu11, &accel_data );
    Delay_ms( 10 );
    c6dofimu11_read_mag ( &c6dofimu11, &mag_data );
    Delay_ms( 10 );

    log_printf( &logger, " Accel X : %.2f g\r\n", accel_data.x  );

    log_printf( &logger, " Accel Y : %.2f g\r\n", accel_data.y  );

    log_printf( &logger, " Accel Z : %.2f g\r\n", accel_data.z  );

    
    log_printf( &logger, "\r\n" );

    
    log_printf( &logger, " Mag X : %.2f uT\r\n", mag_data.x  );

    log_printf( &logger, " Mag Y : %.2f uT\r\n", mag_data.y  );
    
    log_printf( &logger, " Mag Z : %.2f uT\r\n", mag_data.z  );
    
 
    log_printf( &logger, "--------------------------\r\n" );

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
