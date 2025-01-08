/*!
 * \file 
 * \brief Vibra sense Click example
 * 
 * # Description
 * This is a example which demonstrates the use of Vibra sense Click board.
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init
 * Configuring Clicks and log objects.
 * 
 * ## Application Task  
 * It detects vibrations and enables PWM and writes log according to them.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "vibrasense.h"

// ------------------------------------------------------------------ VARIABLES

static vibrasense_t vibrasense;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS


void application_init ( void )
{
    log_cfg_t log_cfg;
    vibrasense_cfg_t cfg;

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
    log_printf(&logger, "- Application Init -\r\n");

    //  Click initialization.

    vibrasense_cfg_setup( &cfg );
    VIBRASENSE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vibrasense_init( &vibrasense, &cfg );
    Delay_ms ( 100 );
    
    log_printf(&logger, "--------------------\r\n");
    log_printf(&logger, "  Vibra sense Click \r\n");
    log_printf(&logger, "--------------------\r\n");

    vibrasense_set_mode( &vibrasense, VIBRASENSE_ENABLE );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    if ( vibrasense_check_interrupt( &vibrasense ) )
    {
        log_printf(&logger, "       TILT !!!     \r\n");
        log_printf(&logger, "--------------------\r\n");
        Delay_ms ( 100 );
    }
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
