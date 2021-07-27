/*!
 * \file 
 * \brief Pressure12 Click example
 * 
 * # Description
 * Reads ADC value, convert ADC data to Voltage[ mV ] and pressure [ mBar ].
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes ADC and LOG for logging data.
 * 
 * ## Application Task  
 * Reads ADC value, convert ADC data to Voltage[ mV ] on the AN pin and
 * convert to Pressure data in mBar. All data logs to the USBUART each second.
 *
 * ## NOTE
 * Output is proportional to the difference between applied pressure 
 * and atmospheric (ambient) pressure.
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure12.h"

// ------------------------------------------------------------------ VARIABLES

static pressure12_t pressure12;
static log_t logger;

static uint16_t pressure_val;
static float voltage_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure12_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pressure12_cfg_setup( &cfg );
    PRESSURE12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( pressure12_init( &pressure12, &cfg ) == ADC_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }
    log_info( &logger, "---- Application Init Done ----\r\n" );

    pressure_val = 0;
    voltage_val = 0;
}

void application_task ( void )
{
    if ( pressure12_read_pin_voltage( &pressure12, &voltage_val ) != ADC_ERROR )
    {
        log_printf( &logger, " Voltage [V] : %.2f\r\n", voltage_val );
    }

    if ( pressure12_get_pressure( &pressure12, &pressure_val ) != ADC_ERROR )
    {
        log_printf( &logger, " Pressure [mBar] : %u\r\n", pressure_val );
    }

    log_printf( &logger, "-----------------------------\r\n" );
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
