/*!
 * \file 
 * \brief Ata663254 Click example
 * 
 * # Description
 * This application is the combination of voltage regulator and bus transceiver.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes click driver.
 * 
 * ## Application Task  
 * Checks if new data byte have received in rx buffer (ready for reading), 
  and if ready than reads one byte from rx buffer.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ata663254.h"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static ata663254_t ata663254;
static log_t logger;

static char demo_message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ata663254_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ata663254_cfg_setup( &cfg );
    ATA663254_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ata663254_init( &ata663254, &cfg );
}

void application_task ( void )
{
    char tmp;
    
    //  Task implementation.
    
#ifdef DEMO_APP_RECEIVER

       // RECEIVER - UART polling

       tmp =  ata663254_generic_single_read( &ata663254 );
       log_printf( &logger, "%c", &tmp );
#endif
#ifdef DEMO_APP_TRANSMITER

       // TRANSMITER - TX each 2 sec
       
       ata663254_generic_multi_write( &ata663254, demo_message, 9 );
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
