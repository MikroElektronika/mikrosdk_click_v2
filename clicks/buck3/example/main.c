/*!
 * \file 
 * \brief Buck 3 Click example
 * 
 * # Description
 * Demo application checks the status of the device and the voltage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration.
 * 
 * ## Application Task  
 * Sequentialy, each one second, checks the status of the 
 * Buck 3 Click and if the overvoltage detected or device is under thermal shutdown 
 * it logs a message on the USBUART.
 * 
 * *note:* 
 * Open Drain Power Good Indicator, it is asserted low if output voltage 
 * is out of PGOOD threshold, 
 * Overvoltage or if the device is under thermal shutdown, 
 * EN shutdown or during soft start.
 * Once the FB pin voltage is between 93% and 107% of the 
 * internal reference voltage (VREF) the PGOOD is pulled high.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck3.h"

// ------------------------------------------------------------------ VARIABLES

static buck3_t buck3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    buck3_cfg_setup( &cfg );
    BUCK3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck3_init( &buck3, &cfg );

    buck3_default_cfg( &buck3 );
    log_info( &logger, "---- Buck 3 is activated ----" );
}

void application_task ( void )
{
    uint8_t pg_state;

    //  Task implementation.
    
    pg_state = buck3_get_power_good( &buck3 );
	
    if ( pg_state == 0 )
    {
        log_info
        ( 
            &logger, 
            "---- Overvoltage or thermal shutdown detected ----" 
        );
    }
	Delay_1sec( );
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
