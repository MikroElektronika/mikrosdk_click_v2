/*!
 * \file 
 * \brief Terminal Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the Terminal click. It is a simple
 * GPIO click which is used like an adapter for connecting and stacking other clicks and external
 * equimpent.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click and logger modules.
 * 
 * ## Application Task  
 * This function sets the output on all the pins (one by one) on the left side to high, going
 * from top to bottom and then does the same with the ones on the right side, after which it 
 * sets all pins to high and after one second sets them back to low.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "terminal.h"

// ------------------------------------------------------------------ VARIABLES

static terminal_t terminal;
static log_t logger;

static digital_out_t *pin_addr[ 12 ] =
{
    &terminal.mosi,    // 0 MOSI
    &terminal.miso,    // 1 MISO
    &terminal.sck,     // 2 SCK
    &terminal.cs,      // 3 CS
    &terminal.rst,     // 4 RST
    &terminal.an,      // 5 AN
    &terminal.pwm,     // 6 PWM
    &terminal.int_pin, // 7 INT
    &terminal.tx_pin,  // 8 TX
    &terminal.rx_pin,  // 9 RX
    &terminal.scl,     // 10 SCL
    &terminal.sda      // 11 SDA
};

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void blink ( digital_out_t *pin ) 
{
    terminal_set_pin_high( pin );
    Delay_100ms( );
    terminal_set_pin_low( pin );
}

static void all_on ( )
{
   int i;

   for( i = 0; i < 12; i++ )
   {
        terminal_set_pin_high( pin_addr[ i ] );
   }
}

static void all_off ( )
{
   int i;

   for( i = 0; i < 12; i++ )
   {
        terminal_set_pin_low( pin_addr[ i ] );
   }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    terminal_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    terminal_cfg_setup( &cfg );
    TERMINAL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    terminal_init( &terminal, &cfg );
}

void application_task ( )
{
    int i;

    for( i = 0; i < 12; i++ )
    {
        blink( pin_addr[ i ] );
    }

    all_on( );
    Delay_1sec( );
    all_off( );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
