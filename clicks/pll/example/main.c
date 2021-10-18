/*!
 * \file 
 * \brief PLL Click example
 * 
 * # Description
 * This app sets PLL signals.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Every 2 seconds, the PLL increases the input clock in the order of x4, x5, x6 and x8.
 * 
 * *note:*
 * If you use PLL x4, x5, x6 or x8, set S0 (RST pin) and S1 (AN pin) as OUTPUT.
 * If you use PLL x3.125 or x6.25, set S1 ( AN pin ) as INPUT and S0( RST pin ) as OUTPUT.
 * If you use PLL x3 or x5.3125, set S0 ( RST pin ) as INPUT and S1 ( AN pin ) as OUTPUT.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pll.h"

// ------------------------------------------------------------------ VARIABLES

static pll_t pll;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pll_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    pll_cfg_setup( &cfg );
    PLL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pll_init( &pll, &cfg );
    pll_set_clock_output( &pll, PLL_CLOCK_ENABLE );
}

void application_task ( void )
{
    pll_set_pll_4x( &pll );
    Delay_ms( 2000 );
    pll_set_pll_5x( &pll );
    Delay_ms( 2000 );
    pll_set_pll_6x( &pll );
    Delay_ms( 2000 );
    pll_set_pll_8x( &pll );
    Delay_ms( 2000 );
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
