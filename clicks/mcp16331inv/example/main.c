/*!
 * \file 
 * \brief Mcp16331Inv Click example
 * 
 * # Description
 * This application enables usage of this click as a buck-boost voltage regulator.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes click driver and enables VIN Pull Up.
 * 
 * ## Application Task  
 * Sets DAC output voltage on 3500mV, when gain is set up on 1x VREF,
 * on 4s delay time, and then sets DAC output voltage on 5000mV, when gain is now set up on 2x VREF,
 * on also 4s delay time. VIN Pull Up voltage must be greater than 4V.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mcp16331inv.h"

// ------------------------------------------------------------------ VARIABLES

static mcp16331inv_t mcp16331inv;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp16331inv_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mcp16331inv_cfg_setup( &cfg );
    MCP16331INV_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    Delay_ms( 100 );

    mcp16331inv_init( &mcp16331inv, &cfg );

    Delay_ms( 100 );

    mcp16331inv_enable_vin( &mcp16331inv, MCP16331INV_ENABLE_VIN_PULL_UP );
}

void application_task ( void )
{
    //  Task implementation.

    mcp16331inv_set_dac_vout( &mcp16331inv, MCP16331INV_3500_MV_1X_GAIN, MCP16331INV_GAIN_1X_VREF, MCP16331INV_ACTIVE_MODE );
    Delay_ms( 4000 );
    mcp16331inv_set_dac_vout( &mcp16331inv, MCP16331INV_5000_MV_2X_GAIN, MCP16331INV_GAIN_2X_VREF, MCP16331INV_ACTIVE_MODE );
    Delay_ms( 4000 );
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
