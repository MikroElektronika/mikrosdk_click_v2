/*!
 * \file 
 * \brief Shuttle Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the Terminal click. It is a simple
 * GPIO click which uses high-quality PCB design, four ICD BOX headers and flat ribbon cables to
 * enable stable communication and easy stacking of other click modules.
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
#include "shuttle.h"

// ------------------------------------------------------------------ VARIABLES

static shuttle_t shuttle;
static log_t logger;

static digital_out_t *pin_addr[ 12 ] =
{
    &shuttle.mosi,    // 0 MOSI
    &shuttle.miso,    // 1 MISO
    &shuttle.sck,     // 2 SCK
    &shuttle.cs,      // 3 CS
    &shuttle.rst,     // 4 RST
    &shuttle.an,      // 5 AN
    &shuttle.pwm,     // 6 PWM
    &shuttle.int_pin, // 7 INT
    &shuttle.tx_pin,  // 8 TX
    &shuttle.rx_pin,  // 9 RX
    &shuttle.scl,     // 10 SCL
    &shuttle.sda      // 11 SDA
};

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void blink ( digital_out_t *pin ) 
{
    shuttle_set_pin_high( pin );
    Delay_100ms( );
    shuttle_set_pin_low( pin );
}

static void all_on ( )
{
   int i;

   for( i = 0; i < 12; i++ )
   {
        shuttle_set_pin_high( pin_addr[ i ] );
   }
}

static void all_off ( )
{
   int i;

   for( i = 0; i < 12; i++ )
   {
        shuttle_set_pin_low( pin_addr[ i ] );
   }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    shuttle_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    shuttle_cfg_setup( &cfg );
    SHUTTLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    shuttle_init( &shuttle, &cfg );
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
