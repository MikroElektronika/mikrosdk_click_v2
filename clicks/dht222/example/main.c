/*!
 * \file 
 * \brief Dht222 Click example
 * 
 * # Description
 * DHT22 2 click is used for measuring the environmental temperature and relative humidity. 
 * The calibration coefficient is saved in the OTP memory of an integrated MCU. The integrated 
 * MCU also provides I2C or 1-Wire interface, selectable by the onboard SMD jumper selectors. 
 * The operating voltage can also be selected by the onboard SMD jumper.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 *  Initialization driver enable's - I2C and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of DHT22 2 Click board.
 * DHT22 2 Click communicates with register via I2C protocol read data from register,
 * measured temperature and humidity data from the AM2322 sensor.
 * Convert temperature data to degrees Celsius [ �C ] and
 * humidity data to percentarg [ % ].
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 5 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dht222.h"

// ------------------------------------------------------------------ VARIABLES

static dht222_t dht222;
static log_t logger;

static uint16_t temperature;
static uint16_t humidity;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// Write log of humidity and temperature value as a two-digit number.

void dht222_display_temp_hum ( )
{
    log_printf( &logger, "   Humidity   : %d.%d %\r\n", humidity / 10, humidity % 10 );

    log_printf( &logger, "   Temperature: %d.%d C\r\n",  temperature / 10, temperature % 10 );

    log_printf( &logger, "--------------------------\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dht222_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dht222_cfg_setup( &cfg );
    DHT222_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dht222_init( &dht222, &cfg );

    Delay_ms( 500 );
}

void application_task ( void )
{
    temperature = dht222_get_temperature( &dht222 );

    Delay_1sec( );

    humidity = dht222_get_humidity( &dht222 );

    dht222_display_temp_hum( );

    Delay_ms( 5000 );
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
