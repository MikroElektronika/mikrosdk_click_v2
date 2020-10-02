/*!
 * \file 
 * \brief HydroProbe Click example
 * 
 * # Description
 * This demo app measures humidity.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, prerforms calibration and makes an initial log.
 * 
 * ## Application Task  
 * This example shows the capabilities of the Hydro Probe click
 * by measuring environment moisture content and displaying it in percent via
 * USART terminal.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hydroprobe.h"

// ------------------------------------------------------------------ VARIABLES

static hydroprobe_t hydroprobe;
static log_t logger;

static uint8_t humy_val = 0;
static uint16_t dry_val = 0;
static uint16_t wet_val = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void hydroprobe_calib ( )
{
    uint8_t cnt;

    log_printf( &logger, " Keep the Probe dry \r\n" );
    dry_val = hydroprobe_max_val( &hydroprobe );
    Delay_ms( 5000 );
    log_printf( &logger, " Submerge the Probe in liquid \r\n" );
    for ( cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %d \r\n ", cnt );
        Delay_ms( 1000 );
    }
    log_printf( &logger, " Keep the Probe submerged \r\n" );
    Delay_ms( 100 );
    wet_val = hydroprobe_min_val( &hydroprobe );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 5000 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hydroprobe_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hydroprobe_cfg_setup( &cfg );
    HYDROPROBE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hydroprobe_init( &hydroprobe, &cfg );
    
    Delay_ms( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Hydro Probe click  \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    hydroprobe_calib( );
    log_printf( &logger, "     Calibrated      \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 3000 );
}

void application_task ( void )
{
    humy_val = hydroprobe_rel_env_hum( &hydroprobe, dry_val, wet_val );
    log_printf( &logger, "Environment moisture content: %d %% \r\n ", humy_val );
    log_printf( &logger, "------------------------------\r\n" );
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
