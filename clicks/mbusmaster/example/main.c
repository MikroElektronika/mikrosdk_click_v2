/*!
 * \file 
 * \brief MBusMaster Click example
 * 
 * # Description
 * This application used for remote reading of heat meters,
 * and other types of consumption.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init
 * 
 * ## Application Task  
 * Sends a message [MikroE] to the M-BUS connector every 2 seconds.
 * 
 * *note:* 
 * - M-Bus master communication works at 36v.
 * - This click acts only as 'master', therefore it must be connected to appropriate 'slave'.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mbusmaster.h"

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static mbusmaster_t mbusmaster;
static log_t logger;

static char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mbusmaster_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mbusmaster_cfg_setup( &cfg );
    MBUSMASTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mbusmaster_init( &mbusmaster, &cfg );
}

void application_task ( void )
{
    char tmp;
    
#ifdef DEMO_APP_RECEIVER

       // RECEIVER - UART polling

       tmp =  mbusmaster_generic_single_read( &mbusmaster );
       log_printf( &logger, "%c" , tmp );
#endif

    log_printf( &logger, ">> MESSAGE SENT << \r\n" );
    Delay_ms( 2000 );

#ifdef DEMO_APP_TRANSMITER

       // TRANSMITER - TX each 2 sec
       
       mbusmaster_generic_multi_write( &mbusmaster, demo_message, 9 );
       Delay_ms( 2000 );
#endif

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
