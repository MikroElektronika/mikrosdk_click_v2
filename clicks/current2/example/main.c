/*!
 * \file 
 * \brief current2 Click example
 * 
 * # Description
 * This application measures current.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI interface in Mode 0
 * 
 * ## Application Task  
 * Reads the current averaged result of 20 samples and
 * gets this result in a proper value [mA]. Repeats the current reading every 500ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "current2.h"

// ------------------------------------------------------------------ VARIABLES

static current2_t current;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    current2_cfg_t cfg;

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

    current2_cfg_setup( &cfg );
    CURRENT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    current2_init( &current, &cfg );
    Delay_ms( 300 );
    log_printf( &logger, "Current 2 is initialized \r\n \r\n" );
}

void application_task ( void )
{
    uint16_t tmp;

    tmp = current2_get_current( &current, 20 );

    log_printf( &logger, "Current : %d mA \r\n", tmp );

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
