/*!
 * \file 
 * \brief Accel3 Click example
 * 
 * # Description
 * Accel 3 Click represent 3-axis linear accelerometer.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * This is an example which demonstrates the usage of Accel 3 Click board.
 * Measured coordinates (X,Y,Z) are being sent to the UART where you can 
 * track their changes. All data logs on USB UART for every 1 sec.
 * 
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel3.h"

// ------------------------------------------------------------------ VARIABLES

static accel3_t accel3;
static log_t logger;

accel3_data_t accel3_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms ( 100 );

    //  Click initialization.

    accel3_cfg_setup( &cfg );
    ACCEL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel3_init( &accel3, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " -----  Accel 3 Click  -----\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    accel3_default_cfg ( &accel3, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, " -- Initialization  done. --\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    accel3_read_data( &accel3, &accel3_data );
    Delay_ms ( 100 );
    
    log_printf( &logger, "        Accelerometer       \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, "        X = %6d \r\n", accel3_data.x );
    log_printf( &logger, "        Y = %6d \r\n", accel3_data.y );
    log_printf( &logger, "        Z = %6d \r\n", accel3_data.z );
    log_printf( &logger, "----------------------------\r\n" );
    
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
