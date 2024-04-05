/*!
 * \file 
 * \brief DiffPress Click example
 * 
 * # Description
 * This demo application is made for measuring differential pressure.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device and logger module.
 * 
 * ## Application Task  
 * Logs pressure difference data.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "diffpress.h"

// ------------------------------------------------------------------ VARIABLES

static diffpress_t diffpress;
static log_t logger;
float pressure_difference;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    diffpress_cfg_t cfg;

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

    diffpress_cfg_setup( &cfg );
    DIFFPRESS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    diffpress_init( &diffpress, &cfg );
}

void application_task ( void )
{
    pressure_difference = diffpress_get_pressure_difference( &diffpress );

    log_printf( &logger, "-- Pressure difference  : %f kPa\r\n", pressure_difference );

    Delay_ms ( 500 );
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
