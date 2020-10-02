/*!
 * \file 
 * \brief Pac1934 Click example
 * 
 * # Description
 * This application measures the voltage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes device, enables the device and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows the most important
 * functions that PAC1934 click has, it mesures current voltage, amperage and power.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pac1934.h"

// ------------------------------------------------------------------ VARIABLES

static pac1934_t pac1934;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pac1934_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pac1934_cfg_setup( &cfg );
    PAC1934_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pac1934_init( &pac1934, &cfg );
}

void application_task ( void )
{
    float read_value;
    
    log_printf( &logger, "Send refresh command \r\n" );
    pac1934_write_byte( &pac1934, 0x1C, 0x71 );
    pac1934_write_byte( &pac1934, 0x01, 0xD0 );
    pac1934_send_command( &pac1934, PAC1934_REFRESH_CMD );
    log_printf( &logger, "     Refreshed!     \r\n" );
    Delay_ms( 100 );
    read_value = pac1934_measure_voltage( &pac1934, 1 );
    Delay_ms( 100 );
    log_printf( &logger, "Voltage : %.2f \r\n", read_value );
    
    log_printf( &logger, "V \r\n" );

    read_value = pac1934_measure_current( &pac1934, 1 );
    Delay_ms( 100 );
    log_printf( &logger, "Amperage :  %.2f \r\n", read_value );
    
    log_printf( &logger, "mA \r\n" );

    read_value = pac1934_measure_power( &pac1934, 1 );
    Delay_ms( 100 );
    log_printf( &logger, "Power : %.2f \r\n", read_value );

    log_printf( &logger, "W \r\n" );

    read_value = pac1934_measure_energy( &pac1934, 1, 8 );
    Delay_ms( 100 );
    log_printf( &logger, "Energy :  %.2f \r\n", read_value );
    
    log_printf( &logger, "J \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
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
