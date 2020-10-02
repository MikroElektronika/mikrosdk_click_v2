/*!
 * \file 
 * \brief Buck13 Click example
 * 
 * # Description
 * This example switches the output of the Buck13 and logs the output voltage 
 * on the Vout terminal.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI serial interface and turns OFF the Buck 13 output as default state.
 * 
 * ## Application Task  
 * Displays the output voltage every 2 seconds.
 * 
 * *note:* 
 * Input voltage range must be from 6.5 to 50V.
 * Output voltage is about 3.3V.
 * Current limit is 3A.
 * 
 * \author Petar Suknjaja
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck13.h"

// ------------------------------------------------------------------ VARIABLES

static buck13_t buck13;
static log_t logger;
static uint16_t out_voltage;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck13_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck13_cfg_setup( &cfg );
    BUCK13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck13_default_cfg ( &buck13 );
    buck13_init( &buck13, &cfg );
    log_info( &logger, "Buck 13 is enabled now" );
}

void application_task ( void )
{
    //  Task implementation.

    buck13_enable( &buck13, BUCK13_ENABLE ); 
    out_voltage = buck13_get_voltage( &buck13 );
    log_printf( &logger, "Vout =  %d mV\r\n", out_voltage );
    
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
