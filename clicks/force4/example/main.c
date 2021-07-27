/*!
 * \file 
 * \brief Force4 Click example
 * 
 * # Description
 * This example shows the use of Force 4 Click.
 * It reads 12bit ADC value, using I2C communication,
 * at the interval of one second. 
 * The result is represented on the UART terminal.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger, and makes an initial log.
 * 
 * ## Application Task  
 * It reads 12bit ADC value, using I2C communication,
 * at the interval of one second.
 * The result is represented on the UART terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "force4.h"

// ------------------------------------------------------------------ VARIABLES

static force4_t force4;
static log_t logger;

uint16_t adc_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    force4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    force4_cfg_setup( &cfg );
    FORCE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force4_init( &force4, &cfg );
    Delay_ms( 100 );
}

void application_task ( void )
{
    adc_val = force4_read_adc( &force4 );
    log_printf( &logger, "ADC value: %d\r\n", adc_val );
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
