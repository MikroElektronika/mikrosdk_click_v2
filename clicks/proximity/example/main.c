/*!
 * \file 
 * \brief Proximity Click example
 * 
 * # Description
 * Measures proximity data and ambient light.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and sets chip on the default mode
 * 
 * ## Application Task  
 * Reads Proximity data and Ambient light data and logs data to USBUART every 500 ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity.h"

// ------------------------------------------------------------------ VARIABLES

static proximity_t proximity;
static log_t logger;

uint16_t proximity_ambi_value;
uint16_t proximity_proxi_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity_cfg_t cfg;

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

    proximity_cfg_setup( &cfg );
    PROXIMITY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity_init( &proximity, &cfg );
    proximity_set_default_mode( &proximity );
}

void application_task ( void )
{
    //  Task implementation.
    
    proximity_ambi_value = proximity_read_ambient_light( &proximity );
    proximity_proxi_value = proximity_read_prox_data( &proximity );

    log_printf( &logger, "Proximity:   %u\r\n", proximity_proxi_value );
    log_printf( &logger, " Ambient:   %u LUX\r\n ", proximity_ambi_value );

    Delay_ms( 500 );
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
