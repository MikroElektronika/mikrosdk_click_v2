/*!
 * \file 
 * \brief DigiPot2 Click example
 * 
 * # Description
 * This application change the output voltage every 5 seconds. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - SPI and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of DIGI POT 2 Click board.
 * Increments the wiper position by 10 position every 5 seconds.
 * Calculate ADC voltage and write log UART.
 * All data logs on usb uart for aproximetly every 5 sec.
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "digipot2.h"

// ------------------------------------------------------------------ VARIABLES

static digipot2_t digipot2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    digipot2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    digipot2_cfg_setup( &cfg );
    DIGIPOT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digipot2_init( &digipot2, &cfg );
}

void application_task ( void )
{
    uint16_t counter;
    float adc_voltage;

    for ( counter = 100; counter < 256; counter += 10 )
    {
        digipot2_set_wiper_positions( &digipot2, counter );
        
        adc_voltage = digipot2_convert_output( &digipot2, counter * 16 , DIGIPOT2_VREF_3V3 );
        
        Delay_ms( 1000 );
        Delay_ms( 1000 );
        
        log_printf( &logger, " ADC Voltage : %f V\r\n", adc_voltage );

        Delay_ms( 1000 );
        Delay_ms( 1000 );
        Delay_ms( 1000 );
    }

    log_printf( &logger, "--------------------------\r\n" );
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
