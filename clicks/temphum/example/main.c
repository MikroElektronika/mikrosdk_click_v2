/*!
 * \file 
 * \brief TempHum Click example
 * 
 * # Description
 * This application measures temperature and humidity, 
 * with temperature in range of 0 - 60 deg.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 *  Initialization driver enable's - I2C,
 *  set default configuration and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of TempAndHum Click board.
 * Measured temperature and humidity data from the HTS221 sensor.
 * Convert temperature data to degrees Celsius [ C ] and humidity data to 
percentarg [ % ].
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 3 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum.h"

// ------------------------------------------------------------------ VARIABLES

static temphum_t temphum;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum_cfg_setup( &cfg );
    TEMPHIM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum_init( &temphum, &cfg );

    temphum_default_cfg( &temphum );

    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "      Temp&Hum Click      \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "       Initializing       \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    
    Delay_ms( 100 );
}

void application_task ( void )
{
    float temperature;
    float humidity;

    temperature = temphum_get_temperature( &temphum );
    humidity = temphum_get_humidity( &temphum );

    log_printf( &logger, " Temperature :  %.2f C\r\n", temperature );
    log_printf( &logger, " Humidity    : %.2f %%\r\n", humidity );
    log_printf( &logger, "--------------------------\r\n" );
    
    Delay_ms( 3000 );
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
