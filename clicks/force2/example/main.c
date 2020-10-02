/*!
 * \file 
 * \brief Force2 Click example
 * 
 * # Description
 * This application is used to measure the pressure force.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes ADC driver, sets ADC channel and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows the 
 * capabilities of the Force 2 click by taking measurements from
 * the device and displaying it via USART terminal.
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "force2.h"

// ------------------------------------------------------------------ VARIABLES

static force2_t force2;
static log_t logger;

uint32_t force2_val_conv ( uint32_t x, uint32_t in_max,
                           uint32_t out_min, uint32_t out_max )
{
    uint32_t in_min = 0;

    return ( x - in_min ) * ( out_max - out_min ) / ( in_max - in_min ) + out_min;
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    force2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    force2_cfg_setup( &cfg );
    FORCE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force2_init( &force2, &cfg );


    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    Force 2 click   \r\n" );
    log_printf( &logger, "--------------------\r\n" );

    Delay_ms( 100 );
}

void application_task ( void )
{
    uint32_t disp_val;
    force2_data_t tmp;
    
    //  Task implementation.
    
    tmp = force2_generic_read ( &force2 );
    disp_val = force2_val_conv( tmp, 4095, 15, 0 );

    log_printf( &logger, "Force: %d N\r\n", disp_val );
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
