/*!
 * \file 
 * \brief C420mat Click example
 * 
 * # Description
 * This aplication changes the value of the output current.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Click SPI driver.
 * 
 * ## Application Task  
 * Periodically changes Iout value.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c420mat.h"

// ------------------------------------------------------------------ VARIABLES

static c420mat_t c420mat;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c420mat_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c420mat_cfg_setup( &cfg );
    C420MAT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c420mat_init( &c420mat, &cfg );
}

void application_task ( void )
{
   c420mat_set_i_out( &c420mat, 56 );                   // sets Iout to 5.6mA
   Delay_ms ( 1000 );
   Delay_ms ( 1000 );
   Delay_ms ( 1000 );
   c420mat_set_i_out( &c420mat, 158 );                  // sets Iout to 15.8mA
   Delay_ms ( 1000 );
   Delay_ms ( 1000 );
   Delay_ms ( 1000 );
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
