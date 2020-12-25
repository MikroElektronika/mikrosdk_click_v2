/*!
 * \file main.c
 * \brief Ambient2 Click example
 *
 * # Description
 * This is a example which demonstrates the use of Ambient 2 Click board.
 * This example measures and calculates abmient light from OPT3001 sensor.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and all used pins for Ambient 2 click. 
 * Also executes a default configuration for this click, which
 * means that click will work in continuous conversion mode, in automatic full
 * scale range, with conversion time of 800ms.
 *
 * ## Application Task
 * Reads sensor data every time when conversion cycle was done
 * and data was ready for reading. Sends results to the uart terminal.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ambient2.h"

// ------------------------------------------------------------------ VARIABLES

static ambient2_t ambient2;
static log_t console;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    ambient2_cfg_t ambient2_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    ambient2_cfg_setup( &ambient2_cfg );
    AMBIENT2_MAP_MIKROBUS( ambient2_cfg, MIKROBUS_1 );
    ambient2_init( &ambient2, &ambient2_cfg );
    ambient2_default_cfg( &ambient2 );

    //  Console module initialization.
    LOG_MAP_USB_UART( console_cfg );
    console_cfg.level = LOG_LEVEL_DEBUG;
    console_cfg.baud = 57600;
    log_init( &console, &console_cfg );
    log_printf( &console, "* * *  Ambient 2 initialization done  * * *\r\n" );
    log_printf( &console, "*******************************************\r\n" );
}

void application_task( void )
{
    if ( ambient2_generic_read( &ambient2, AMBIENT2_REG_CONFIGURATION ) & AMBIENT2_FLAG_MASK_CONV_READY )
    {
        ambient2_get_sens_results( &ambient2 );

        log_printf( &console, "** Ambient Light Sensor : %.2f lux **\r\n", ambient2.sens_data.amb_light_lx );
        log_printf( &console, "** Ambient Light Range : %.2f lux **\r\n", ambient2.sens_data.amb_light_range );
        log_printf( &console, "** Ambient Light Percents : %d %% **\r\n\n", (int16_t)ambient2.sens_data.amb_light_per );
    }
}

void main( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
