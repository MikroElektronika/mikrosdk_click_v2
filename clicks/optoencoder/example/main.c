/*!
 * \file 
 * \brief Opto Encoder Click example
 * 
 * # Description
 * This application is used to encode motion or rotation.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and opto encoder init.
 * 
 * ## Application Task  
 * Detects the change of step and logs to usb uart number of stepped steps.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "optoencoder.h"

// ------------------------------------------------------------------ VARIABLES

static optoencoder_t optoencoder;
static log_t logger;
static int16_t old_step = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    optoencoder_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    optoencoder_cfg_setup( &cfg );
    OPTOENCODER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    optoencoder_init( &optoencoder, &cfg );

    optoencoder_init_dev( &optoencoder );
}

void application_task ( )
{
    int16_t new_step;
    new_step = optoencoder_get_position( &optoencoder );
    if ( old_step != new_step)
    {
        log_printf( &logger, "Step: %d \r\n", new_step );
        old_step = new_step;
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
