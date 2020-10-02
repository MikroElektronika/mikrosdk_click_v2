/*!
 * \file 
 * \brief Thumbstick Click example
 * 
 * # Description
 * The demo application shows reading the thumbstick position ..
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * It reads the position of the thumbstick,
 *  - if it detects that the thumbstick has moved from the zero position,
 *    it prints a message about the current position.
 *  - It also checks the status of the switch button.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thumbstick.h"

// ------------------------------------------------------------------ VARIABLES

static thumbstick_t thumbstick;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thumbstick_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    thumbstick_cfg_setup( &cfg );
    THUMBSTICK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thumbstick_init( &thumbstick, &cfg );
}

void application_task ( void )
{
    uint8_t pos;
    uint8_t button_state;

    pos = thumbstick_get_position( &thumbstick );
    button_state = thumbstick_button_state( &thumbstick );

    if ( button_state == THUMBSTICK_PRESS_BUTTON )
    {
        log_printf( &logger, ">> Button is pressted \r\n" );
    }

    switch ( pos )
    {
        case THUMBSTICK_POSITION_TOP:
        {
            log_printf( &logger, ">> Position: [ TOP ] \r\n" );
            break;
        }
        case THUMBSTICK_POSITION_RIGHT:
        {
            log_printf( &logger, ">> Position: [ RIGHT ] \r\n" );
            break;
        }
        case THUMBSTICK_CHANNEL_BOTTOM:
        {
            log_printf( &logger, ">> Position: [ BOTTOM ] \r\n" );
            break;
        }
        case THUMBSTICK_CHANNEL_LEFT:
        {
            log_printf( &logger, ">> Position: [ LEFT ] \r\n" );
            break;
        }
    }
    Delay_ms( 30 );
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
