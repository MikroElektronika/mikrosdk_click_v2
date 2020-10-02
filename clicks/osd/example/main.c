/*!
 * \file 
 * \brief OSD Click example
 * 
 * # Description
 * This demo performs basic OSD Click functionality - write text on
 * screen.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize device.
 * 
 * ## Application Task  
 * Write text on the screen, write character per 1 second
 * in the first, seventh and fifteenth row of the screen.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "osd.h"

// ------------------------------------------------------------------ VARIABLES

static osd_t osd;
static log_t logger;

uint8_t cnt;
const uint8_t HEADER_TEXT[ 30 ]  = { ' ', ' ', 'O', 'S', 'D', ' ', 'c', 'l', 'i', 'c', 'k', ' ',
' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
const uint8_t MESSAGE_TEXT[ 30 ] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
'm', 'i', 'k', 'r', 'o', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
const uint8_t FOOTER_TEXT[ 30 ]  = { ' ', 'w', 'w', 'w', '.', 'm', 'i', 'k', 'r', 'o', 'e', '.',
'c', 'o', 'm', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    osd_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    osd_cfg_setup( &cfg );
    OSD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    osd_init( &osd, &cfg );

    osd_default_cfg( &osd );
    osd_clears_char_places( &osd, 0, 0, 16, 30 );
}

void application_task ( void )
{
    for ( cnt = 0; cnt < 30; cnt++ )
    {
        if ( HEADER_TEXT[ cnt ] != ' ' )
        {
            osd_write_character( &osd, 1, cnt, HEADER_TEXT[ cnt ] );
        }

        if ( MESSAGE_TEXT[ cnt ] != ' ' )
        {
            osd_write_character( &osd, 7, cnt, MESSAGE_TEXT[ cnt ] );
        }

        if ( FOOTER_TEXT[ cnt ] != ' ' )
        {
            osd_write_character( &osd, 14, cnt, FOOTER_TEXT[ cnt ] );
        }

        Delay_ms( 1000 );
    }
    
    osd_clears_char_places( &osd, 0, 0, 16, 30 );
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
