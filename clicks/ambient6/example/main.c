/*!
 * \file 
 * \brief Ambient6 Click example
 * 
 * # Description
 * This application measurement ambient light
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and default configuration device for measurement
 * 
 * ## Application Task  
 * Read Ambient Light in lux[lx] and this data logs to USBUART every 1sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ambient6.h"

// ------------------------------------------------------------------ VARIABLES

static ambient6_t ambient6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient6_cfg_t cfg;

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

    ambient6_cfg_setup( &cfg );
    AMBIENT6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient6_init( &ambient6, &cfg );
    ambient6_default_cfg( &ambient6 );    
}

void application_task ( )
{
    float ambient_light;
    
    ambient_light = ambient6_get_ambient_light( &ambient6 );
    log_printf( &logger, "Ambient Light: %.2f lx \r\n", ambient_light );
    Delay_ms( 1000 );
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
