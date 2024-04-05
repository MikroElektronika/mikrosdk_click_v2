/*!
 * \file 
 * \brief Thermo16 Click example
 * 
 * # Description
 * This demo-app shows the temperature measurement procedure using Thermo 16 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * 
 * ## Application Task  
 * Reads ambient temperature data and this data logs to USBUART every 1500ms.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo16.h"

// ------------------------------------------------------------------ VARIABLES

static thermo16_t thermo16;
static log_t logger;

float temp;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo16_cfg_t cfg;

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

    thermo16_cfg_setup( &cfg );
    THERMO16_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo16_init( &thermo16, &cfg );
}

void application_task ( void )
{
    
    //  Task implementation.
    
    temp = thermo16_get_temperature ( &thermo16, THERMO16_TEMP_IN_CELSIUS );
    log_printf( &logger, "** Temperature : %.2f C \r\n", temp );
    
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
