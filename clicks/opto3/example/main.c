/*!
 * \file 
 * \brief Opto 3 Click example
 * 
 * # Description
 * Opto 3 click to be used in applications that require reinforced galvanic 
 * isolation for both their input and output stages.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO interface.
 * 
 * ## Application Task  
 * Switches ON or switches OFF the both outputs depending on the
 * states of the inputs, respectively.
 * 
 * *note:* 
 * Input state is active low, and output state is active high.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "opto3.h"

// ------------------------------------------------------------------ VARIABLES

static opto3_t opto3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    opto3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    opto3_cfg_setup( &cfg );
    OPTO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto3_init( &opto3, &cfg );

    log_printf( &logger, "** Opto 3 is initialized **\r\n" );
}

void application_task ( void )
{
    OPTO3_STATE state_in1;
    OPTO3_STATE state_in2;
    OPTO3_SWITCH state_out1;
    OPTO3_SWITCH state_out2;

    state_in1 = opto3_get_in1( &opto3 );
    state_in2 = opto3_get_in2( &opto3 );
    
    state_out1 = state_in1 ^ 1;
    state_out2 = state_in2 ^ 1;
    
    log_printf( &logger, "** Opto 3 out1 is**\r\n" );
    opto3_set_out1( &opto3, state_out1 );
    log_printf( &logger, "** Opto 3 out2 is **\r\n" );
    opto3_set_out2( &opto3, state_out2 );
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
