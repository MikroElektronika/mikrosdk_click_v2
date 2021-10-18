/*!
 * \file 
 * \brief 6Dofimu3 Click example
 * 
 * # Description
 * This example demonstrates the use of 6DOF IMU 3 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and sets the device default configuration.
 * 
 * ## Application Task  
 * Measures acceleration and magnetometer data and displays the results on USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu3.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu3_t c6dofimu3;
static log_t logger;

c6dofimu3_accel_t accel_data;
c6dofimu3_mag_t mag_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu3_cfg_t cfg;

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

    c6dofimu3_cfg_setup( &cfg );
    C6DOFIMU3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu3_init( &c6dofimu3, &cfg );

    c6dofimu3_default_cfg( &c6dofimu3 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    if ( c6dofimu3_check_data_ready( &c6dofimu3 ) )
    {
        c6dofimu3_get_data ( &c6dofimu3, &accel_data, &mag_data );

        log_printf( &logger, " Accel X : %.2f mg \t Mag X : %.2f uT\r\n", accel_data.x, mag_data.x );

        log_printf( &logger, " Accel Y : %.2f mg \t Mag Y : %.2f uT\r\n", accel_data.y, mag_data.y );
        
        log_printf( &logger, " Accel Z : %.2f mg \t Mag Z : %.2f uT\r\n", accel_data.z, mag_data.z );
        
        log_printf( &logger, "-------------------------------------\r\n" );

        Delay_ms( 800 );
    }
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
