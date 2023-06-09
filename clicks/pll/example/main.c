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
 * Every 2 seconds, the PLL increases the input clock from min (x2) to max (x8) level.
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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.
    pll_cfg_setup( &cfg );
    PLL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pll_init( &pll, &cfg );
    pll_set_clock_output( &pll, PLL_CLOCK_ENABLE );
}

void application_task ( void )
{
    log_printf( &logger, " PLL level: x2\r\n\n" );
    pll_set_pll_2x( &pll );
    Delay_ms( 2000 );
    log_printf( &logger, " PLL level: x3\r\n\n" );
    pll_set_pll_3x( &pll );
    Delay_ms( 2000 );
    log_printf( &logger, " PLL level: x3.125\r\n\n" );
    pll_set_pll_3_125x( &pll );
    Delay_ms( 2000 );
    log_printf( &logger, " PLL level: x4\r\n\n" );
    pll_set_pll_4x( &pll );
    Delay_ms( 2000 );
    log_printf( &logger, " PLL level: x5\r\n\n" );
    pll_set_pll_5x( &pll );
    Delay_ms( 2000 );
    log_printf( &logger, " PLL level: x5.3125\r\n\n" );
    pll_set_pll_5_3125x( &pll );
    Delay_ms( 2000 );
    log_printf( &logger, " PLL level: x6\r\n\n" );
    pll_set_pll_6x( &pll );
    Delay_ms( 2000 );
    log_printf( &logger, " PLL level: x6.25\r\n\n" );
    pll_set_pll_6_25x( &pll );
    Delay_ms( 2000 );
    log_printf( &logger, " PLL level: x8\r\n\n" );
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
