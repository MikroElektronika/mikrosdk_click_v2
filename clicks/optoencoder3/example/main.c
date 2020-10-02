/*!
 * \file 
 * \brief Opto Encoder 3 Click example
 * 
 * # Description
 * The demo application displays the counter value or displays the status of each O pins.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Select demo application mode.
 * 
 * ## Application Task  
 * Depending on the set demo application mode:
 *    - DEMO_CNT - Measures and displays the value of the counter.
 *    - DEMO_GRAPH - Draws the status of each O pin.
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "optoencoder3.h"

// ------------------------------------------------------------------ VARIABLES

static optoencoder3_t optoencoder3;
static log_t logger;

optoencoder3_pins_t pins;
static uint8_t example_setter;

// ------------------------------------------------------------------ MACRO

#define DEMO_CNT    1
#define DEMO_GRAPH  2

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void draw_pins_status( void )
{
    optoencoder3_read_all_pins( &optoencoder3, &pins );

    log_printf( &logger, "-Pins status:\r\n" );

    if ( pins.pin_o1 == OPTOENCODER3_PIN_ACTIVE )
    {
        log_printf( &logger, "*  " );
    }
    else
    {
        log_printf( &logger, "o  " );
    }

    if ( pins.pin_o3 == OPTOENCODER3_PIN_ACTIVE )
    {
        log_printf( &logger, "*  \r\n" );
    }
    else
    {
        log_printf( &logger, "o  \r\n" );
    }

    if ( pins.pin_o2 == OPTOENCODER3_PIN_ACTIVE )
    {
        log_printf( &logger, "*  " );
    }
    else
    {
        log_printf( &logger, "o  " );
    }

    if ( pins.pin_o4 == OPTOENCODER3_PIN_ACTIVE )
    {
        log_printf( &logger, "*  " );
    }
    else
    {
        log_printf( &logger, "o  " );
    }

    log_printf( &logger, "  \r\n" );
}

void view_counters ( void )
{
    uint8_t cnt;
    int8_t swipe_cnt;

    cnt = optoencoder3_cnt( &optoencoder3 );
    swipe_cnt = optoencoder3_dir_cnt( &optoencoder3 );

    log_printf( &logger, "---Counter number of swipes and direction counter:\r\n" );
    log_printf( &logger, "* Counter : %d \r\n", cnt );
    log_printf( &logger, "*Direction counter :  %d \r\n", cnt );
    log_printf( &logger, " _________________________________ \r\n \r\n \r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    optoencoder3_cfg_t cfg;

    //  Logger initialization.

    
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    optoencoder3_cfg_setup( &cfg );
    OPTOENCODER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    optoencoder3_init( &optoencoder3, &cfg );

    example_setter = DEMO_CNT;
}

void application_task ( void )
{
    if ( example_setter == DEMO_GRAPH )
    {
        draw_pins_status(  );
    }
    else if ( example_setter == DEMO_CNT )
    {
        view_counters(  );
    }
    Delay_ms( 100 );
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
