/*!
 * \file 
 * \brief LedDriver8 Click example
 * 
 * # Description
 * This demo app sets brightness.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and sets module for working
 * 
 * ## Application Task  
 * Changes brightness on all LEDs. 
 * Controls are blinking on one LED.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "leddriver8.h"

// ------------------------------------------------------------------ VARIABLES

static leddriver8_t leddriver8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver8_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    leddriver8_cfg_setup( &cfg );
    LEDDRIVER8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver8_init( &leddriver8, &cfg );

    leddriver8_reset( &leddriver8 );
    Delay_ms( 500 );
    
    leddriver8_output_enable_pin( &leddriver8, LEDDRIVER8_ENABLE_LED_OUTPUTS );
    leddriver8_set_output_gain( &leddriver8, LEDDRIVER8_OUTPUT_GAIN_ALL_LED, LEDDRIVER8_FULL_OUTPUT_CURRENT_GAIN );
    leddriver8_set_mode_register( &leddriver8, LEDDRIVER8_MODE1_NORMAL_MODE, LEDDRIVER8_MODE2_DMBLNK_DIMMING |
                                  LEDDRIVER8_MODE2_CLRERR_ALL | LEDDRIVER8_MODE2_EXP_DISABLE );
}

void application_task ( void )
{
    uint8_t cnt;

    for ( cnt = 0; cnt < 0xFF; cnt++ )
    {
        leddriver8_set_brightness( &leddriver8, LEDDRIVER8_BRIGHTNESS_ALL_LED, cnt );
        Delay_ms( 15 );
    }
    
    for ( cnt = 0; cnt < 5; cnt++ )
    {
       leddriver8_set_brightness( &leddriver8, LEDDRIVER8_LED_0, 200 );
       Delay_ms( 1000 );
       leddriver8_set_brightness( &leddriver8, LEDDRIVER8_LED_0, 0 );
       Delay_ms( 1000 );
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
