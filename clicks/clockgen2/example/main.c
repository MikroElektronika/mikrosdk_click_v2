/*!
 * \file 
 * \brief ClockGen2 Click example
 * 
 * # Description
 * This application enables generation of square waved clock signal in range from 260 kHz to 66,6 MHz
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver initialization.
 * 
 * ## Application Task  
 * Changes the prescaler and enables/disables the clock output.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "clockgen2.h"

// ------------------------------------------------------------------ VARIABLES

static clockgen2_t clockgen2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    clockgen2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    clockgen2_cfg_setup( &cfg );
    CLOCKGEN2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    clockgen2_init( &clockgen2, &cfg );

    Delay_ms(100);
}

void application_task ( void )
{
    //  Task implementation.

    char i;
     
     for ( i = 5; i< 8; i++ )
     {
       clockgen2_set_prescaler( &clockgen2, i );
       clockgen2_output_enable( &clockgen2, 1 );
       Delay_ms( 2000 );

       clockgen2_output_enable( &clockgen2, 0 );
       Delay_ms( 2000 );
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
