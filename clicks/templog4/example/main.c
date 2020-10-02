/*!
 * \file 
 * \brief TempLog4 Click example
 * 
 * # Description
 * This application measures the temperature
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C interface and performs a device configuration for properly working.
   Also sets the temperature limit to the desired values.
 * 
 * ## Application Task  
 * First ensures that the minimum conversion time is met, and then reads the
   ambient temperature calculated to the Celsius degrees.
   Also checks the limit status and shows a message when some limit condition is met.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "templog4.h"

// ------------------------------------------------------------------ VARIABLES

static templog4_t templog4;
static log_t logger;

static uint8_t ret_status;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void static check_limit_status ( )
{
    if ( ( ret_status & 0x80 ) != 0x00 )
    {
        log_printf( &logger, "** Critical temperature detection! **\r\n" );
    }
    if ( ( ret_status & 0x40) != 0x00 )
    {
        log_printf( &logger, "** Ambient temperature is higher than upper limit temperature! **\r\n" );
    }
    else if ( ( ret_status & 0x20) != 0x00 )
    {
        log_printf( &logger, "** Ambient temperature is lower than lower limit temperature! **\r\n" );
    }
}

void static wait_conversion_done ( )
{
    uint8_t time_cnt;

    for ( time_cnt = 0; time_cnt < 13; time_cnt++ )
    {
        Delay_10ms( );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    templog4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    templog4_cfg_setup( &cfg );
    TEMPLOG4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    templog4_init( &templog4, &cfg );
    templog4_default_cfg ( &templog4 );
}

void application_task ( )
{
    float temperature;

    wait_conversion_done( );

    ret_status = templog4_get_temp( &templog4, TEMPLOG4_TEMP_AMBIENT_REG, &temperature );

    log_printf( &logger, "** Ambient temperature: %f C **\r\n", temperature );

    check_limit_status( );

    log_printf( &logger, "\r\n", temperature );

    Delay_ms( 300 );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
