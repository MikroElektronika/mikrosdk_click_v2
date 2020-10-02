/*!
 * \file 
 * \brief RadioStation Click example
 * 
 * # Description
 * RadioStation click can be used to broadcast the music via the FM radio band 
 * ( which operates in the frequency range of 76MHz to 108MHz ).
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C and sets transmit_frequency.
 * 
 * ## Application Task  
 * In this example Radio Station Click is receiving signal from audio connector and broadcasting 
 * it on 100.00 MHz frequency.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "radiostation.h"

// ------------------------------------------------------------------ VARIABLES

static radiostation_t radiostation;
static radiostation_cmd_t radiostation_cmd;
static log_t logger;

static uint8_t buff[ 16 ];
 
// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    radiostation_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    radiostation_cfg_setup( &cfg, true );
    RADIOSTATION_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    radiostation_init( &radiostation, &cfg );

    radiostation.transmit_frequency = 10000; 
    radiostation.status = 0xFF;

    radiostation_default_cfg( &radiostation, &radiostation_cmd );
}

void application_task ( void )
{
    radiostation_get_asq_status( &radiostation, &radiostation_cmd, &buff[ 0 ] );
    Delay_ms( 50 );
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
