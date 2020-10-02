/*!
 * \file 
 * \brief Pedometer Click example
 * 
 * # Description
 * This application detected steps.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and sets step counter on 0.
 * 
 * ## Application Task  
 * It checks if a new step is detected, if detected new step - 
 * reads the current number of steps made and logs data to the USBUART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pedometer.h"

// ------------------------------------------------------------------ VARIABLES

static pedometer_t pedometer;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pedometer_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    pedometer_cfg_setup( &cfg );
    PEDOMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pedometer_init( &pedometer, &cfg );
}

void application_task ( void )
{
    //  Task implementation.

    uint8_t new_step;
    uint32_t s_counter;
    char demoText[ 50 ];
    
    new_step = pedometer_process( &pedometer );

    if ( new_step == PEDOMETER_NEW_STEP_DETECTED )
    {
        s_counter = pedometer_get_step_counter( &pedometer );
        log_printf( &logger, " Step Counter : %d \r\n ", s_counter );
       
        Delay_ms( 50 );
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
