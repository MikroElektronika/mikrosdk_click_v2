/*!
 * \file 
 * \brief Tester Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the Tester click. It is a simple
 * GPIO click which is used to test if all the pins on a MikroBUS are working correctly.
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
#include "tester.h"

// ------------------------------------------------------------------ VARIABLES

static tester_t tester;
static log_t logger;

static digital_out_t *pin_addr[ 12 ] =
{
    &tester.mosi,    // 0 MOSI
    &tester.miso,    // 1 MISO
    &tester.sck,     // 2 SCK
    &tester.cs,      // 3 CS
    &tester.rst,     // 4 RST
    &tester.an,      // 5 AN
    &tester.pwm,     // 6 PWM
    &tester.int_pin, // 7 INT
    &tester.tx_pin,  // 8 TX
    &tester.rx_pin,  // 9 RX
    &tester.scl,     // 10 SCL
    &tester.sda      // 11 SDA
};

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void blink ( digital_out_t *pin ) 
{
    tester_set_pin_high( pin );
    Delay_100ms( );
    tester_set_pin_low( pin );
}

static void all_on ( )
{
   int i;

   for( i = 0; i < 12; i++ )
   {
        tester_set_pin_high( pin_addr[ i ] );
   }
}

static void all_off ( )
{
   int i;

   for( i = 0; i < 12; i++ )
   {
        tester_set_pin_low( pin_addr[ i ] );
   }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    tester_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    tester_cfg_setup( &cfg );
    TESTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tester_init( &tester, &cfg );
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
