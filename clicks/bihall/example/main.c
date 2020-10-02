/*!
 * \file 
 * \brief BI HALL Click example
 * 
 * # Description
 * Detect the south & north pole magnetic fields.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of BI HALL Click board.
 * Detect the south & north pole magnetic fields near the BI HALL Click.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart when magnetic field is detected.
 * 
 * \author Nenad Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "bihall.h"

// ------------------------------------------------------------------ VARIABLES

static bihall_t bihall;
static log_t logger;

uint8_t bihall_state;
uint8_t bihall_state_old;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    bihall_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    bihall_cfg_setup( &cfg );
    BIHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bihall_init( &bihall, &cfg );
    
    log_printf(&logger, " Detecting magnetic fields\r\n");
    log_printf(&logger, "--------------------------\r\n");
    
    bihall_state = BIHALL_MAG_POLE_NORTH;
    bihall_state_old = BIHALL_MAG_POLE_NORTH;
}

void application_task ( void )
{
    bihall_state = bihall_det_mag_field( &bihall );

    if ( ( bihall_state == BIHALL_MAG_POLE_SOUTH ) && ( bihall_state_old == BIHALL_MAG_POLE_NORTH ) )
    {
        bihall_state_old = BIHALL_MAG_POLE_SOUTH;
        log_printf(&logger, "         ~ SOUTH ~\r\n");
        log_printf(&logger, "--------------------------\r\n");
    }

    if ( ( bihall_state == BIHALL_MAG_POLE_NORTH ) && ( bihall_state_old == BIHALL_MAG_POLE_SOUTH ) )
    {
        log_printf(&logger, "         ~ NORTH ~\r\n");
        log_printf(&logger, "--------------------------\r\n");
        bihall_state_old = BIHALL_MAG_POLE_NORTH;
    }
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
