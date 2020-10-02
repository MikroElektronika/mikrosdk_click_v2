/*!
 * \file 
 * \brief Mic2 Click example
 * 
 * # Description
 * This range is  suited for audio and/or speech applications. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, ADC init and sets digital pot.
 * 
 * ## Application Task  
 * Reads ADC data from AN pin and plots it on serial plotter.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mic2.h"

// ------------------------------------------------------------------ VARIABLES
uint16_t plot_time;
static mic2_t mic2;
static log_t logger;
 
void plot_data( uint16_t data_plot )
{
    
    
    log_printf( &logger, "%d,%d", data_plot, plot_time++ );

    Delay_ms( 5 );
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    mic2_cfg_setup( &cfg );
    MIC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic2_init( &mic2, &cfg );

    mic2_set_potentiometer( &mic2, 35 );
}

void application_task ( void )
{
    mic2_data_t tmp;
    
    //  Task implementation.
    
    tmp = mic2_generic_read ( &mic2 );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    Delay_ms( 1000 );
    plot_data( tmp );

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
