/*!
 * \file 
 * \brief Thermo11 Click example
 * 
 * # Description
 * The application measures temperature
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C serial interface and performs a software reset command
 * and device configurations.
 * 
 * ## Application Task  
 * Waits until data was ready and conversion cycle was done, and then reads 
 * the temperature and status data. The both data will be sent to the uart terminal with the limit status messages.
 *
 * *note:* 
 * The temperature that can be measured or written to the registers is in range from -256 to 255.9921875 Celsius degrees.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo11.h"

// ------------------------------------------------------------------ VARIABLES

static thermo11_t thermo11;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo11_cfg_t cfg;

    //  Logger initialization.

   LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );


    //  Click initialization.

    thermo11_cfg_setup( &cfg );
    THERMO11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo11_init( &thermo11, &cfg );

    thermo11_sw_reset( &thermo11 );

    thermo11_default_cfg( &thermo11 );
    
    log_printf( &logger, "** Thermo 11 is initialized ** \r\n" );
    log_printf( &logger, "************************************************ \r\n \r\n" );
    
    Delay_ms( 500 );
}

void application_task ( void )
{
    uint8_t response_check;
    float temperature;
    
    response_check = thermo11_get_int(  &thermo11 );
    while ( response_check == THERMO11_FLAG_IS_CLEARED )
    {
        response_check = thermo11_get_int( &thermo11 );
    }

    temperature = thermo11_get_temp(  &thermo11, THERMO11_TEMPERATURE_REG );
    response_check = thermo11_check_status( &thermo11 );
    
    log_printf( &logger, "*Temperature is: %.2f \r\n", temperature );

    
    if ( ( response_check & THERMO11_HIGH_ALERT_FLAG ) != THERMO11_FLAG_IS_CLEARED )
    {
        log_printf( &logger, "*HIGH limit detection! \r\n" );
    }
    if ( ( response_check & THERMO11_LOW_ALERT_FLAG ) != THERMO11_FLAG_IS_CLEARED )
    {
         log_printf( &logger, "*LOW limit detection! \r\n" );
    }
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
