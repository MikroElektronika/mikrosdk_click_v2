/*!
 * \file 
 * \brief LightRanger Click example
 * 
 * # Description
 * This application measures and calculates ambient light intensity and distance 
 * from the sensor, and then logs the results.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver , initialization sensor Vl6180X and start
 * write log.
 * 
 * ## Application Task  
 * Measures and calculates ambient light intensity and distance from sensor,
 * when the distance is changed log is updated,
 * results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for approximately every 1 sec when the data value changes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lightranger.h"

// ------------------------------------------------------------------ VARIABLES

static lightranger_t lightranger;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lightranger_cfg_setup( &cfg );
    LIGHTRANGER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger_init( &lightranger, &cfg );
}

void application_task ( void )
{
    uint16_t range_value;
    uint16_t lux_value;
    
    lightranger_start_single_shot_range_mode( &lightranger );
    
    Delay_ms( 100 );
    
    lightranger_poll_range( &lightranger );
    lightranger_interrupts_clear( &lightranger );
    
    range_value = lightranger_get_distance( &lightranger );
    log_printf( &logger, "Proximity : %d [ mm ]\r\n", range_value );

    lux_value = lightranger_get_ambiant_light( &lightranger, LIGHTRANGER_CMD_GAIN_1X );
    log_printf( &logger, "Ambient Light: %d [ lux ]\r\n", lux_value );

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
