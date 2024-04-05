/*!
 * \file 
 * \brief TempHum7 Click example
 * 
 * # Description
 * This application measurement temperature and humidity data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device and logger module and sets default configuration for measurements.
 * 
 * ## Application Task  
 * Calculates and Logs temperature and relative humidity
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum7.h"

// ------------------------------------------------------------------ VARIABLES

static temphum7_t temphum7;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum7_cfg_t cfg;
    
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

    temphum7_cfg_setup( &cfg );
    TEMPHUM7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum7_init( &temphum7, &cfg );

    temphum7_default_cfg( &temphum7 );
}

void application_task ( void )
{
   float temperature;
   float relative_humidity; 

    temperature = temphum7_get_temperature( &temphum7, TEMPHUM7_HOLD_MASTER_MODE );
    log_printf( &logger, "-> Temperature: %f C\r\n", temperature );

    relative_humidity = temphum7_get_relative_humidity( &temphum7, TEMPHUM7_HOLD_MASTER_MODE );
    log_printf( &logger, "-> Relative humidity: %f %%RH\r\n ", relative_humidity );

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
