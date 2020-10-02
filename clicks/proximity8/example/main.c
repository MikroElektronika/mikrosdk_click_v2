/*!
 * \file 
 * \brief Proximity8 Click example
 * 
 * # Description
 * This application enables usage of the proximity sensor
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization Driver init, test comunication and configuration chip for measurement
 * 
 * ## Application Task  
 * Reads Proximity data and this data logs to the USBUART every 1500ms.
 * 
 * *note:* 
 * The reading value and proximity of the data depend on the configuration.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity8.h"

// ------------------------------------------------------------------ VARIABLES

static proximity8_t proximity8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity8_cfg_t cfg;
    uint16_t tmp;
    uint16_t w_temp;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proximity8_cfg_setup( &cfg );
    PROXIMITY8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity8_init( &proximity8, &cfg );

    //Test Communication
    
    proximity8_generic_read( &proximity8, PROXIMITY8_REG_DEVICE_ID, &tmp );

    if ( tmp == PROXIMITY8_DEVICE_ID )
    {
        log_printf( &logger, "---- Comunication OK!!! ----\r\n" );
    }
    else
    {
        log_printf( &logger, "---- Comunication ERROR!!! ----\r\n" );
        for ( ; ; );
    }

    proximity8_default_cfg( &proximity8 );

    log_printf( &logger, "---- Start measurement ----\r\n" );
}

void application_task ( void )
{
   uint16_t proximity;
   
   proximity8_generic_read( &proximity8, PROXIMITY8_REG_PROX_DATA, &proximity );
   proximity = ( proximity & 0x7FFF );

   log_printf( &logger, " Proximity data: %d\r\n", proximity );
   
   log_printf( &logger, "-------------------------\r\n" );
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
