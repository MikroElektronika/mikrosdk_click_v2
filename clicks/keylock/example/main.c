/*!
 * \file 
 * \brief Keylock Click example
 * 
 * # Description
 * This application monitors key position in its lock mechanism.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables GPIO and also writes log.
 * 
 * ## Application Task  
 * Detects the position in which the key currently is.
 * Results are being sent to the Terminal, where you can track changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "keylock.h"

// ------------------------------------------------------------------ VARIABLES

static keylock_t keylock;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    keylock_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    keylock_cfg_setup( &cfg );
    KEYLOCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    keylock_init( &keylock, &cfg );
    Delay_ms( 100 );
    log_printf( &logger, "--------------- \r\n" );
    log_printf( &logger, " Keylock Click \r\n" );
    log_printf( &logger, "--------------- \r\n" );
}

void application_task ( void )
{
    uint8_t new_state;
    uint8_t old_state = 0;

    new_state = keylock_get_position( &keylock );

    if ( old_state != new_state )
    {
        if ( new_state == KEYLOCK_KEY_POS_1 )
        {
            log_printf( &logger, " Position ONE \r\n" );
        }
        else if ( new_state == KEYLOCK_KEY_POS_2 )
        {
            log_printf( &logger, " Position TWO \r\n" );
        }
        else if ( new_state == KEYLOCK_KEY_POS_3 )
        {
            log_printf( &logger, " Position THREE \r\n" );
        }
        else
        {
            log_printf( &logger, " ERROR!!! \r\n" );
        }
        
    old_state = new_state;
    log_printf( &logger, "---------------- \r\n" );
    }

    Delay_ms( 500 );
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
