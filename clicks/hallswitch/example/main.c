/*!
 * \file 
 * \brief Hall Switch Click example
 * 
 * # Description
 * The application sets sensor magnetic pole
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and turn OFF S-pole and N-pole
 * 
 * ## Application Task  
 * Turns S and N on and off every 500 ms
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hallswitch.h"

// ------------------------------------------------------------------ VARIABLES

static hallswitch_t hallswitch;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallswitch_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    hallswitch_cfg_setup( &cfg );
    HALLSWITCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallswitch_init( &hallswitch, &cfg );

    hallswitch_set_npole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
    hallswitch_set_spole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
}

void application_task()
{
    hallswitch_set_npole( &hallswitch, HALLSWITCH_POLE_ACTIVE );
    Delay_ms( 500 );
    hallswitch_set_spole( &hallswitch, HALLSWITCH_POLE_ACTIVE );
    Delay_ms( 500 );
    hallswitch_set_npole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
    Delay_ms( 500 );
    hallswitch_set_spole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
    Delay_ms( 500 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
