/*!
 * \file 
 * \brief Thunder Click example
 * 
 * # Description
 * This application detects the presence and proximity of potentially 
 * lightning activity and provides estimated distance to the center of the storm. 
 * It can also provide information on the noise level.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI driver and performs the reset command and RCO calibrate command.
 * Also configures the device for working properly.
 * 
 * ## Application Task  
 * Always checks is interrupt event happend (Listening mode) and 
 * after that gets the informations about storm. Results logs on UART.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thunder.h"

// ------------------------------------------------------------------ VARIABLES

static thunder_t thunder;
static log_t logger;

uint8_t storm_mode;
uint32_t storm_energy;
uint8_t storm_distance;


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thunder_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    thunder_cfg_setup( &cfg );
    THUNDER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thunder_init( &thunder, &cfg );

    thunder_default_cfg( &thunder );
    Delay_ms( 300 );
}

void application_task ( void )
{
    storm_mode = thunder_check_interr( &thunder );

    if ( storm_mode == THUNDER_NOISE_LEVEL_INTERR )
    {
        log_printf( &logger, "Noise level too high\r\n" );
    }
    else if ( storm_mode == THUNDER_DISTURBER_INTERR )
    {
        log_printf( &logger, "Disturber detected\r\n" );
    }
    else if ( storm_mode ==  THUNDER_LIGHTNING_INTERR )
    {
        thunder_get_storm_info( &thunder, &storm_energy, &storm_distance );

        log_printf( &logger, "Energy of the single lightning : %ld\r\n", storm_energy );
        log_printf( &logger, "Distance estimation :  %d km\r\n", storm_distance );
    }

    Delay_ms( 1000 );
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
