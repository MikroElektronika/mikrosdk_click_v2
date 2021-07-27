/*!
 * \file 
 * \brief Pressure10 Click example
 * 
 * # Description
 * Pressure 10 Click features a digital interface barometric pressure sensor, based on 
 * piezoresistive bridge. It can use both SPI and I2C communication protocols, allowing 
 * it to be interfaced with a broad range of MCUs. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, checks the communication and configures the module for measurement.
 * 
 * ## Application Task  
 * Reads the pressure and temperature data every 1500ms and displays the results on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure10.h"

// ------------------------------------------------------------------ VARIABLES

static pressure10_t pressure10;
static log_t logger;

static uint8_t check_com;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure10_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pressure10_cfg_setup( &cfg );
    PRESSURE10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure10_init( &pressure10, &cfg );

    check_com = pressure10_check_communication( &pressure10 );
    if ( check_com == 0 )
    {
        log_printf( &logger, ">> Communication [OK]\r\n" );
    }
    else
    {
        log_printf( &logger, ">> Communication [ERROR]\r\n" );
        for( ; ; );
    }

    pressure10_default_cfg ( &pressure10 );
    log_printf( &logger, "----------------------------\r\n" );
}

void application_task ( void )
{
    float temperature;
    float pressure;

    pressure = pressure10_get_pressure( &pressure10 );
    temperature = pressure10_get_temperature( &pressure10 );

    log_printf( &logger, ">> Temperature: %.2f C\r\n", temperature );

    log_printf( &logger, "----------------------------\r\n" );

    log_printf( &logger, ">> Pressure: %.2f mBar\r\n", pressure );

    log_printf( &logger, "----------------------------\r\n" );

    Delay_ms( 1500 );
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
