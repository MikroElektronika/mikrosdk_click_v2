/*!
 * \file 
 * \brief UV2 Click example
 * 
 * # Description
 * This app measurement UVA and UVB data and calculate UV index level.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device and set default cinfiguration.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of UV 2 Click board.
 * UV 2 Click communicates with VEML6075 sesnor via I2C by write to register and read from register.
 * This example measurement UVA and UVB data, calculate UV index level and write log.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 2 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uv2.h"

// ------------------------------------------------------------------ VARIABLES

static uv2_t uv2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uv2_cfg_t cfg;

    uint8_t state_id;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uv2_cfg_setup( &cfg );
    UV2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uv2_init( &uv2, &cfg );

    Delay_ms( 100 );

    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "       UV 2  Click      \r\n" );
    log_printf( &logger, "------------------------\r\n" );

    uv2_default_cfg( &uv2 );
    
    state_id = uv2_check_id( &uv2 );
    
    if ( state_id )
    {
        log_printf( &logger, "       Configured       \r\n" );
    }
    else
    {
        log_printf( &logger, "         ERROR          \r\n" );
    }

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint16_t val_uva;
    uint16_t val_uvb;
    float uv_index;

    val_uva = uv2_get_uva( &uv2 );
    log_printf( &logger, " UVA data = %d \r\n", val_uva );

    val_uvb = uv2_get_uvb( &uv2 );
    log_printf( &logger, " UVB data = %d \r\n", val_uvb );

    uv_index = uv2_get_uv_index( &uv2 );
    log_printf( &logger, " UV Index = %f \r\n", uv_index );

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 2000 );
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
