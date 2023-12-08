/*!
 * \file 
 * \brief Fever Click example
 * 
 * # Description
 * This application measures temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Click device initialization
 * 
 * ## Application Task  
 * Reading and displaying current temperature via UART
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fever.h"

// ------------------------------------------------------------------ VARIABLES

static fever_t fever;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fever_cfg_t cfg;

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

    fever_cfg_setup( &cfg );
    FEVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fever_init( &fever, &cfg );
}

void application_task ( void )
{
    float temperature;
    temperature = fever_get_temperature( &fever );
    log_printf( &logger, "Current Temperature : %.2f C \r\n", temperature );
    Delay_ms( 1000 );
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
