/*!
 * \file 
 * \brief Temp&Hum4 Click example
 * 
 * # Description
 * This application reads temperature and humidity data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and settings chip mode ACTIVE and configuration Measurement and Interrupt, 
 * then settings maximum / minimum possible Temperature and Huminidy.
 * 
 * ## Application Task  
 * Reads the temperature and huminidy and logs to the USBUART every 500 ms.
 * 
 * 
 * \author Petar Suknjaja
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum4.h"

// ------------------------------------------------------------------ VARIABLES

static temphum4_t temphum4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum4_cfg_setup( &cfg );
    TEMPHUM4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum4_init( &temphum4, &cfg );
    
    temphum4_default_cfg( &temphum4 );

    log_info( &logger, "---Temp&Hum 4 Configured---" );
}

void application_task ( void )
{
    float temperature;
    float humidity;
    
    temperature = temphum4_get_temperature( &temphum4 );
    log_printf( &logger, " Temperature : %f C \r\n", temperature );
    humidity = temphum4_get_humidity( &temphum4 );
    log_printf( &logger, " Humidity : %f %% \r\n", humidity );
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
