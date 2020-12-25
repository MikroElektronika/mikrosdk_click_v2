/*!
 * \file 
 * \brief Adc2 Click example
 * 
 * # Description
 * This application enables usage of the 22bit ADC.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI driver and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows the capabilities of the ADC 2 click
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adc2.h"

// ------------------------------------------------------------------ VARIABLES

static adc2_t adc2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adc2_cfg_setup( &cfg );
    ADC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc2_init( &adc2, &cfg );

    Delay_ms( 100 );
    
    adc2_set_vref( &adc2, ADC2_VCC_3v3 );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    ADC 2 Click   \r\n" );
    log_printf( &logger, "------------------\r\n" );
}

void application_task ( void )
{
    float adc_val;

    //  Task implementation.

    adc_val = adc2_read_adc_data( &adc2 );

    log_printf( &logger, "Value : %.2f mV\r\n", adc_val );
    
    if ( adc2.ovf_h )
        log_printf( &logger, "HIGH OVERFLOW DETECTED\r\n" );
    else if ( adc2.ovf_l )
        log_printf( &logger, "LOW OVERFLOW DETECTED\r\n" );
    
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 500 );
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
