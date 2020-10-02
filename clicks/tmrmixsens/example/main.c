/*!
 * \file 
 * \brief Tmrmixsens Click example
 * 
 * # Description
 * The TMR mix-sens Click has three types of magnetic field sensors: Two digital and one analog sensor. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - GPIO,
   initializes ADC and set ADC channel.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of TMR mix-sens Click board.
   This examples respond to changes north or south magnetic pole and display ADC data value.
   Results are being sent to the Usart Terminal where you can track their changes.
   All data logs on usb uart for aproximetly every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "tmrmixsens.h"

// ------------------------------------------------------------------ VARIABLES

static tmrmixsens_t tmrmixsens;
static log_t logger;

static uint16_t adc_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    tmrmixsens_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    tmrmixsens_cfg_setup( &cfg );
    TMRMIXSENS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tmrmixsens_init( &tmrmixsens, &cfg );
}

void application_task ( void )
{
    tmrmixsens_data_t tmp;
    
    tmp = tmrmixsens_generic_read ( &tmrmixsens );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    Delay_ms( 1000 );

    if ( tmrmixsens_get_bipolar( &tmrmixsens ) == TMRMIXSENS_NORTH_POLE )
    {
        log_printf( &logger, " ~~~ Nort  pole ~~~ \r\n" );
    }
    else if( tmrmixsens_get_bipolar( &tmrmixsens ) == TMRMIXSENS_SOUTH_POLE )
    {
        log_printf( &logger, " ~~~ South pole ~~~ \r\n" );
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
