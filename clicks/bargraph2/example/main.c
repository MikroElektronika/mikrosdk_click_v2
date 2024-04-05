/*!
 * \file 
 * \brief Bargraph2 Click example
 * 
 * # Description
 * The example starts off with the initalisation and configuration of the logger and click
 * modules and later on showcases different ways of lighting LED diodes on the click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function shows the user how to light single and multiple LED diodes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "bargraph2.h"

// ------------------------------------------------------------------ VARIABLES

static bargraph2_t bargraph2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    bargraph2_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    bargraph2_cfg_setup( &cfg );
    BARGRAPH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bargraph2_init( &bargraph2, &cfg );
    
    barpgraph2_power( &bargraph2, BARGRAPH2_POWER_ON );
}

void application_task ( )
{
    uint8_t cnt; 
        
    // Single LED switch
    
    for ( cnt = 1; cnt <= 10; cnt++ )
    {
        bargraph2_led_green( &bargraph2, cnt );
        Delay_ms ( 200 );
        bargraph2_led_red( &bargraph2, 10 - ( cnt - 1 ) );
        Delay_ms ( 200 );
    }
    
    bargraph2_lights_out ( &bargraph2 );

    // Multiple LED switch

    bargraph2_leds_green ( &bargraph2, 1, 10 );
    Delay_ms ( 1000 );
    bargraph2_leds_red ( &bargraph2, 1, 10 );
    Delay_ms ( 1000 );
    bargraph2_leds_yellow ( &bargraph2, 1, 10 );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
