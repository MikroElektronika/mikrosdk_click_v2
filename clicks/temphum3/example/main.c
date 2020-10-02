/*!
 * \file 
 * \brief TempHum3 Click example
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
#include "temphum3.h"

// ------------------------------------------------------------------ VARIABLES

static temphum3_t temphum3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum3_cfg_setup( &cfg );
    TEMPHUM3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum3_init( &temphum3, &cfg );
    log_info( &logger, "---- Init done -----" );
    
    temphum3_default_cfg( &temphum3 );
    
    log_info( &logger, "--- Settings Temp&Hum done---" );
}

void application_task ( void )
{
    float temperature;
    float humidity;

    //  Task implementation.
    
    temperature = temphum3_get_temperature( &temphum3 );
    log_printf( &logger, " Temperature : %f C \r\n", temperature );
    
    humidity = temphum3_get_humidity( &temphum3 );
    log_printf( &logger, " Humidity : %f %% \r\n", humidity );
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
