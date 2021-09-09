/*!
 * @file main.c
 * @brief Ambient 10 Click Example.
 *
 * # Description
 * This example demonstrates the use of Ambient 10 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the voltage reference.
 *
 * ## Application Task
 * Reads the ADC voltage and then calculates the illuminance from it.
 * The calculated value of illuminance in lux is being displayed on the USB UART approximately once per second. 
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient10.h"

static ambient10_t ambient10;       /**< Ambient 10 Click driver object. */
static log_t logger;                /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    ambient10_cfg_t ambient10_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    ambient10_cfg_setup( &ambient10_cfg );
    AMBIENT10_MAP_MIKROBUS( ambient10_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == ambient10_init( &ambient10, &ambient10_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    ambient10_set_vref( &ambient10, AMBIENT10_VREF_3V3 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    
    if ( AMBIENT10_OK == ambient10_read_adc_voltage ( &ambient10, &voltage ) )
    {
        log_printf( &logger, " Illuminance : %u Lux\r\n\n", ambient10_voltage_to_lux( &ambient10, voltage ) );
    }
    
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
