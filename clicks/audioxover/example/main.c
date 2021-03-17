/*!
 * \file 
 * \brief Audio Xover Click example
 * 
 * # Description
 * This example demonstrates the use of the Audio Xover click board. 
 * The click is an analog active crossover solution for two-way loudspeakers. 
 * The primary purpose of the crossover circuit in a loudspeaker is to split 
 * an incoming audio signal into frequency bands that are passed to 
 * the speaker best suited.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes the driver and makes an initial log.
 * 
 * ## Application Task  
 * This function enables and disables the click board every 10 seconds,
 * and logs an appropriate message on the USB UART.
 * 
 * @note
 * The hardware revision v100 of the click board works only with MCUs that operates
 * at 5V operating voltage level.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "audioxover.h"

// ------------------------------------------------------------------ VARIABLES

static audioxover_t audioxover;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioxover_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    audioxover_cfg_setup( &cfg );
    AUDIOXOVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioxover_init( &audioxover, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, " * Switch: ON *\r\n" );
    audioxover_power_on ( &audioxover );
    Delay_ms( 10000 );

    log_printf( &logger, " * Switch: OFF *\r\n" );
    audioxover_shut_down ( &audioxover );
    Delay_ms( 10000 );
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
