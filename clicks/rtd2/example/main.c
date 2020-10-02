/*!
 * \file 
 * \brief Rtd 2 Click example
 * 
 * # Description
 * RTD 2 Click board is commonly used for measure ambient temperature
 * from the PT100 3-wire temperature probe.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - SPI,
 * hardware reset the device and set default configuration 
 * and start the measurement, also write log.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of RTD 2 Click board.
 * RTD 2 Click board can be used to measure ambient temperature
 * from the PT100 3-wire temperature probe
 * wired to the 4ADS1247 24-Bit, 2-kSPS, Analog-To-Digital Converters With
 * Programmable Gain Amplifier (PGA) For Sensor Measurement
 * on the RTD 2 click board
 * All data logs write on USB uart changes for every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rtd2.h"

// ------------------------------------------------------------------ VARIABLES

static rtd2_t rtd2;
static log_t logger;
static float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    rtd2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    rtd2_cfg_setup( &cfg );
    RTD2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtd2_init( &rtd2, &cfg );

    Delay_ms( 200 );

    log_printf( &logger, "----- Hardware Reset ------\r\n" );
    rtd2_hw_reset( &rtd2 );
    Delay_ms( 100 );
    
    log_printf( &logger, "-- Default configuration --\r\n" );

    rtd2_default_cfg( &rtd2 );
    Delay_ms( 1000 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Start Measurement    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    if ( rtd2_check_new_data_ready( &rtd2 ) == RTD2_NEW_DATA_IS_READY )
    {
        temperature = rtd2_get_temperature( &rtd2 );
        log_printf( &logger, " Temperature : %f C\r\n", temperature );
        log_printf( &logger, "--------------------------\r\n");
        Delay_ms( 1000 );
    }
    else
    {
        rtd2_enable_start( &rtd2, RTD2_START_CONVERSION_DISABLE );
        Delay_ms( 1000 );
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
