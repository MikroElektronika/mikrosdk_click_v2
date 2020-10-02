/*!
 * \file 
 * \brief Illuminance Click example
 * 
 * # Description
 * This example demonstrates basic Illuminance Click functionality.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize device and driver.
 * 
 * ## Application Task  
 * Every second calculate illuminance measured by sensor and log 
 * results to UART Terminal.
 * 
 * *note:* 
 * By default, integration time is set to 402ms but it may be modified
 * by user using illuminance_write_data() function and provided macros.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "illuminance.h"

// ------------------------------------------------------------------ VARIABLES

static illuminance_t illuminance;
static log_t logger;

static uint16_t value_ch0;
static uint16_t value_ch1;
static uint16_t lux_value;
static uint16_t lux_value_old;
static uint8_t sensitivity;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    illuminance_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    illuminance_cfg_setup( &cfg );
    ILLUMINANCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    illuminance_init( &illuminance, &cfg );
    illuminance_default_cfg ( &illuminance );

    // Variable Initializations for this example.
    
    lux_value_old = 0;
    sensitivity = 50;
}

void application_task ( void )
{
    illuminance_get_result( &illuminance, &value_ch0, &value_ch1 );

    lux_value = illuminance_calculate_lux( ILLUMINANCE_TSL2561_GAIN_0X, ILLUMINANCE_TSL2561_INTEGRATIONTIME_402MS , value_ch0, value_ch1 );
    Delay_ms( 1000 );

    if ( ( ( lux_value - lux_value_old ) > sensitivity ) && ( ( lux_value_old - lux_value ) > sensitivity ) )
    {
        log_printf( &logger, "\r\n--------------------------------" );
        log_printf( &logger, "\r\nFull  Spectrum: %u [ lux ]", lux_value );
        log_printf( &logger, "\r\nVisible  Value: %u [ lux ]", value_ch0 - value_ch1 );
        log_printf( &logger, "\r\nInfrared Value: %u [ lux ]", value_ch1 );    
        log_printf( &logger, "\r\n--------------------------------\r\n" );
        
        lux_value_old = lux_value;
    }
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
