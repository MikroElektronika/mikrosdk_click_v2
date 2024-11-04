/*!
 * \file 
 * \brief Buck Boost 2 Click example
 * 
 * # Description
 * This application enables use of DC-DC step-down/step-up regulator (buck/boost).
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and turn ON chip and settings mode with improvement current.
 * 
 * ## Application Task  
 * The Click has a constant output voltage of 5V, no additional settings are required.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buckboost2.h"

// ------------------------------------------------------------------ VARIABLES

static buckboost2_t buckboost2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buckboost2_cfg_t cfg;

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

    buckboost2_cfg_setup( &cfg );
    BUCKBOOST2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buckboost2_init( &buckboost2, &cfg );

    buckboost2_power_on( &buckboost2 );
    buckboost2_set_mode( &buckboost2, BUCKBOOST2_WITH_IMPROVEMENT );
}

void application_task ( void )
{
    //  Task implementation.

}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
