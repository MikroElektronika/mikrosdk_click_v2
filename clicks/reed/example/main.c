/*!
 * \file 
 * \brief REED Click example
 * 
 * # Description
 * This is a example which demonstrates the use of REED Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * Detect the magnetic field near the REED Click.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart when magnetic field is detected.
 * 
 * \author Nenad Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "reed.h"

// ------------------------------------------------------------------ VARIABLES

static reed_t reed;
static log_t logger;

static uint8_t reed_state;
static uint8_t reed_state_old;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    reed_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf(&logger, "- Application Init -\r\n");

    //  Click initialization.

    reed_cfg_setup( &cfg );
    REED_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    reed_init( &reed, &cfg );

    reed_state = REED_NO_MAGNETIC_FIELD;
    reed_state_old = REED_NO_MAGNETIC_FIELD;

    log_printf(&logger, "--------------------\r\n");
    log_printf(&logger, "     REED click\r\n");
    log_printf(&logger, "--------------------\r\n");
    Delay_100ms();
}

void application_task ( void )
{
    reed_state = reed_get_status( &reed );

    if ( ( reed_state == REED_MAGNETIC_FIELD_DETECTED ) && ( reed_state_old == REED_NO_MAGNETIC_FIELD ) )
    {
        reed_state_old = REED_MAGNETIC_FIELD_DETECTED;
        log_printf(&logger, "     ~ LOCKED ~\r\n");
        log_printf(&logger, "--------------------\r\n");
    }

    if ( ( reed_state == REED_NO_MAGNETIC_FIELD ) && ( reed_state_old == REED_MAGNETIC_FIELD_DETECTED ) )
    {
        log_printf(&logger, "    ~ UNLOCKED ~\r\n");
        log_printf(&logger, "--------------------\r\n");
        reed_state_old = REED_NO_MAGNETIC_FIELD;
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
