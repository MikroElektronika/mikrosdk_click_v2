/*!
 * \file 
 * \brief TempHum9 Click example
 * 
 * # Description
 * <DEMOAPP_DESCRIPTION>
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver and sends SLEEP and WAKEUP dommands
 * 
 * ## Application Task  
 * Performs simultaneous temperature and relative humidity measurements and logs both values
 * 
 * *note:* 
 * <NOTE>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "temphum9.h"

// ------------------------------------------------------------------ VARIABLES

static temphum9_t temphum9;
static log_t logger;
float measurement_data[ 2 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    temphum9_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    temphum9_cfg_setup( &cfg );
    TEMPHUM9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temphum9_init( &temphum9, &cfg );


    temphum9_send_command( &temphum9, TEMPHUM9_SLEEP );
    Delay_ms(500);
    temphum9_send_command( &temphum9,  TEMPHUM9_WAKEUP );
    Delay_ms(100);
    
    log_printf( &logger, "< < < app init done > > >\r\n" );
}

void application_task( )
{
    log_printf( &logger, " " );

    temhum9_get_temperature_and_humidity( &temphum9, TEMPHUM9_NORMAL_MODE, measurement_data );
    
    log_printf( &logger, "> > > Temperature: %.2fC\r\n", measurement_data[ 0 ] );

    log_printf( &logger, "> > > Relative humidity: %.2f %% \r\n", measurement_data[ 1 ] );
    
    log_printf( &logger, "------------------------------------------\r\n" );
    
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
