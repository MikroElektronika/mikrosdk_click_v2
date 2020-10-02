/*!
 * \file 
 * \brief Barometer3 Click example
 * 
 * # Description
 * This demo app measures pressure.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and configuration module for measurement.
 * 
 * ## Application Task  
 * Reads Pressure data in Pascal [ Pa ]. Results are being sent to the Usart Terminal 
 * where you can track their changes. All data logs write on USB uart changes for every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "barometer3.h"

// ------------------------------------------------------------------ VARIABLES

static barometer3_t barometer3;
static log_t logger;

uint8_t status_val;
float pressure;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    barometer3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    barometer3_cfg_setup( &cfg );
    BAROMETER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    barometer3_init( &barometer3, &cfg );

    Delay_ms( 100 );

    barometer3_def_cfg( &barometer3 );
    Delay_ms( 100 );

    status_val = barometer3_meas_prs_once( &barometer3, &pressure, BAROMETER3_PM_PRC_128 );
    Delay_ms( 100 );

    if ( status_val != BAROMETER3_SUCCESS )
    {
        log_printf( &logger, "FAIL! Err. code: %d \r\n", status_val );
    }
    
    Delay_ms( 100 );
}

void application_task ( void )
{
    status_val = barometer3_meas_prs_once( &barometer3, &pressure, BAROMETER3_PM_PRC_128 );

    if ( status_val == BAROMETER3_SUCCESS )
    {
        log_printf( &logger, " Pressure: %.2f Pa \r\n", pressure );
        log_printf( &logger, "----------------------- \r\n" );
        Delay_ms( 1000 );
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
