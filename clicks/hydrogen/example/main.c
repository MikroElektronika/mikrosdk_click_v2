/*!
 * @file main.c
 * @brief Hydrogen Click Example.
 *
 * # Description
 * The demo application shows the reading of the adc 
 * values given by the sensors.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configuring clicks and log objects.
 * 
 * ## Application Task
 * Reads the adc value and prints in two forms (DEC and HEX).
 * 
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "hydrogen.h"

static hydrogen_t hydrogen;   /**< Hydrogen Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    hydrogen_cfg_t hydrogen_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    hydrogen_cfg_setup( &hydrogen_cfg );
    HYDROGEN_MAP_MIKROBUS( hydrogen_cfg, MIKROBUS_1);
    if ( hydrogen_init( &hydrogen, &hydrogen_cfg ) == ADC_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    uint16_t hydrogen_an_value = 0;

    if ( hydrogen_read_an_pin_value ( &hydrogen, &hydrogen_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " ADC Value : %u\r\n", hydrogen_an_value );
    }

    float hydrogen_an_voltage = 0;

    if ( hydrogen_read_an_pin_voltage ( &hydrogen, &hydrogen_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", hydrogen_an_voltage );
    }

    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
