/*!
 * \file 
 * \brief NO22 Click example
 * 
 * # Description
 * Measure the level of NO2
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver init
 * 
 * ## Application Task  
 * Measures in span of 1 seconc ppb of NO2
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "no22.h"

// ------------------------------------------------------------------ VARIABLES

static no22_t no22;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    no22_cfg_t cfg;
    uint8_t error_data;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    no22_cfg_setup( &cfg );
    NO22_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    no22_init( &no22, &cfg );

    error_data = no22_set_pht_state( &no22, NO22_PIN_STATE_LOW );

    if ( error_data == NO22_DEVICE_ERROR )
    {
        log_printf( &logger, "Device error \r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "***** App init ***** \r\n" );
}

void application_task ( )
{
    uint16_t temp_data_read;
    float data_ppb;
    
    temp_data_read = no22_read_data( &no22 );
    log_printf( &logger, "ADC: %d \n\r", temp_data_read );
    
    data_ppb = no22_get_ppb( &no22 );
    log_printf( &logger, "PPB: %f \r\n", data_ppb );
    
    log_printf( &logger, "___________________________\r\n" );
    
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
