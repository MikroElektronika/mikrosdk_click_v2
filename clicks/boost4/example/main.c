/*!
 * \file 
 * \brief Boost4 Click example
 * 
 * # Description
 * This example demonstrates the use of Boost 4 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger, and enables the click board.
 * 
 * ## Application Task  
 * Set the desired output voltage by cycling through a couple of predefined voltage values.
 * All data are being logged on USB UART every 3 seconds.
 * 
 * @note
 * Vout cannot be set to voltage below Vin. So in order to get all values at Vout exactly 
 * as it is set in this example, please provide 2.5V to Vin. 
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "boost4.h"

// ------------------------------------------------------------------ VARIABLES

static boost4_t boost4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    boost4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    boost4_cfg_setup( &cfg );
    BOOST4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost4_init( &boost4, &cfg );
    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, "        Boost 4 Click        \r\n" );
    log_printf( &logger, "-----------------------------\r\n" );
    boost4_enable( &boost4, BOOST4_ENABLE );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    log_printf( &logger, " Set the max Vout \r\n" );
    boost4_set_out_voltage( &boost4, BOOST4_VOUT_MAX );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );

    log_printf( &logger, " Set Vout to 5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_5 );

    Delay_ms( 3000 );
    
    log_printf( &logger, "-----------------------------\r\n" );

    log_printf( &logger, " Set Vout to 4.5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_4_5 );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 4V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_4 );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 3.5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_3_5 );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 3V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_3 );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set Vout to 2.5V\r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_2_5 );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
    
    log_printf( &logger, " Set the min Vout \r\n" );

    boost4_set_out_voltage( &boost4, BOOST4_VOUT_MIN );

    Delay_ms( 3000 );

    log_printf( &logger, "-----------------------------\r\n" );
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
