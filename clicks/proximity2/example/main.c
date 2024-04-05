/*!
 * \file 
 * \brief Proximity2 Click example
 * 
 * # Description
 * This is an example that shows the most important
 * functions that Proximity 2 click has.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Setting the click in the default configuration.
 * 
 * ## Application Task  
 * Shows the most important proximity and ambient value.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity2.h"

// ------------------------------------------------------------------ VARIABLES

static proximity2_t proximity2;
static log_t logger;

static uint8_t proxi_val;
static uint16_t ambient;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity2_cfg_t cfg;

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
    log_info( &logger, "Application Init" );
    
    //  Click initialization.

    proximity2_cfg_setup( &cfg );
    PROXIMITY2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity2_init( &proximity2, &cfg );
    
    proximity2_default_cfg ( &proximity2 );
    
    log_info( &logger, "Application Init" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    proxi_val =  proximity2_read_prox ( &proximity2 );
    ambient = proximity2_read_als ( &proximity2 );

    log_printf( &logger, " Proximity ADC : %d \r\n", (uint16_t)proxi_val );
    
    log_printf( &logger, " Light    : %d \r\n", ambient );

    log_printf( &logger, "------------------\r\n" );
    
    Delay_ms ( 300 );
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
