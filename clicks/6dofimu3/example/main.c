/*!
 * \file 
 * \brief 6Dofimu3 Click example
 * 
 * # Description
 * This application shows functionality of this Click board
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization of communication module and configuration of device
 * 
 * ## Application Task  
 * Reads sensor measurements and logs it.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "C6dotimu3.h"

// ------------------------------------------------------------------ VARIABLES

static C6dotimu3_t C6dotimu3;
static log_t logger;

c6dofimu3_accel_t accel_data;
c6dofimu3_mag_t mag_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    C6dotimu3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    C6dotimu3_cfg_setup( &cfg );
    C6DOTIMU3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    C6dotimu3_init( &C6dotimu3, &cfg );

    C6dotimu3_default_cfg( &C6dotimu3 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    if ( c6dofimu3_check_data_ready( &C6dotimu3 ) )
    {
        c6dofimu3_get_data ( &C6dotimu3, &accel_data, &mag_data );

        log_printf( &logger, " Accel X : %d   |    Mag X : %d\r\n", accel_data.x, mag_data.x );

        log_printf( &logger, " Accel Y : %d   |    Mag Y : %d\r\n", accel_data.y, mag_data.y );
        
        log_printf( &logger, " Accel Z : %d   |    Mag Z : %d\r\n", accel_data.z, mag_data.z );
        
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
