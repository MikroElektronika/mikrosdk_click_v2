/*!
 * \file 
 * \brief Proximity13 Click example
 * 
 * # Description
 * This demo application shows example for measuring close distance
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization of I2C module and additional pin, checks id of device, 
 * configurates device for measuring 1. channel,
 * and then sends command to start measuring
 * 
 * ## Application Task  
 * Appliction measures values every 100ms and logs result
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity13.h"

// ------------------------------------------------------------------ VARIABLES

static proximity13_t proximity13;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity13_cfg_t cfg;
    uint8_t status;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proximity13_cfg_setup( &cfg );
    PROXIMITY13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity13_init( &proximity13, &cfg );
    
    status = proximity13_get_int_pin_status( &proximity13 );
    while ( status != PROXIMITY13_PIN_HIGH );

    status = porximity13_check_id( &proximity13 );
    if ( status == PROXIMITY13_OK )
    {
        log_info( &logger, " Device OK" );
    }
    else
    {
        log_info( &logger, " Device Error" );
        for ( ; ; );
    }
    
    log_info( &logger, " Setting default configuration" );
    proximity13_default_cfg ( &proximity13 );
    
    proximity13_send_command( &proximity13, PROXIMITY13_CMD_START );
    log_info( &logger, " Starting measurement" );
}

void application_task ( void )
{
    proximity13_chn_val_t chn_val;

    proximity13_read_channels( &proximity13, &chn_val );

    log_printf( &logger, " Data : %u\r\n", chn_val.channel_1 );

    Delay_ms ( 100 );
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
