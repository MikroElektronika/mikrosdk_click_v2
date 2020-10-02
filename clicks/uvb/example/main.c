/*!
 * \file 
 * \brief Uvb Click example
 * 
 * # Description
 * This Click is ultraviolet sensing board, capable of measuring UV index between 0 to 16. 
 * UVB Click supports integrated functions of ultraviolet light sensors.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init, check communication and configuration module for measurement.
 * 
 * ## Application Task  
 * Reads UVB data and logs to the USBUART every 1500ms.
 * 
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uvb.h"

// ------------------------------------------------------------------ VARIABLES

static uvb_t uvb;
static log_t logger;

static uint16_t uvb_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uvb_cfg_t cfg;
    uint8_t check_com;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uvb_cfg_setup( &cfg );
    UVB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uvb_init( &uvb, &cfg );

    check_com = uvb_check_communication( &uvb );
    if ( check_com == 0 )
    {
        log_printf( &logger, ">> Communication [OK]\r\n" );
    }
    else
    {
        log_printf( &logger, ">> Communication [ERROR]\r\n" );
        for( ; ; );
    }

    uvb_default_cfg ( &uvb );

    log_printf( &logger, ">> Configuration done !!!\r\n" );
    Delay_ms( 1500 );
}

void application_task ( void )
{
    uvb_data = uvb_get_uv_data( &uvb );

    log_printf( &logger, ">> UVB data: %d\r\n", uvb_data );

    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1500 );
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
