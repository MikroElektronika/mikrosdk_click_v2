/*!
 * \file 
 * \brief Wheatstone Click example
 * 
 * # Description
 * 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and ADC module init.
 * 
 * ## Application Task  
 * Reads the ADC value and converts to voltage on the AN pin.
 * 
 * *note:* 
 * Set the ADC resolution and vref before programming.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "wheatstone.h"

// ------------------------------------------------------------------ VARIABLES

static wheatstone_t wheatstone;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    wheatstone_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wheatstone_cfg_setup( &cfg );
    WHEATSTONE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wheatstone_init( &wheatstone, &cfg );

    wheatstone_set_potentiometer ( &wheatstone, WHEATSTONE_DEF_POTENCIOMETER );
    wheatstone_set_adc_vref ( &wheatstone, 2048.0 );
    wheatstone_set_adc_resolution ( &wheatstone, 4096.0 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    float voltage;
    uint32_t adc_value = 0;
    
    adc_value = wheatstone_generic_read( &wheatstone );

    log_printf( &logger, "-- ADC value: %d \r\n", adc_value );
    
    voltage = wheatstone_get_voltage( &wheatstone, adc_value );

    log_printf( &logger, "-- Voltage: %.2f mV\r\n", voltage );
    
    Delay_ms( 2000 );
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
