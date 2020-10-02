/*!
 * \file 
 * \brief ADC7 Click example
 * 
 * # Description
 * This application collects data from the analog signal, calculates and logs the
 * converted voltage value.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and performs configuration for conversion cycles.
 * 
 * ## Application Task  
 * Performs the determined number of conversion cycles which are necessary for
 * averaging.  When all conversion cycles are done,
 * then reads the converted voltage value.
 * Results will be logged on uart terminal. Repeats operation every 200ms.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adc7.h"

// ------------------------------------------------------------------ VARIABLES

static adc7_t adc7;
static log_t logger;

static int16_t voltage_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc7_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adc7_cfg_setup( &cfg );
    ADC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc7_init( &adc7, &cfg );
    
    adc7_default_cfg( &adc7 );
}

void application_task ( void )
{
    adc7_start_conv_cycle( &adc7 );
    adc7_read_results( &adc7, &voltage_data );

    log_printf( &logger, "Voltage: %d mV\r\n", voltage_data );

    Delay_ms( 200 );
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
