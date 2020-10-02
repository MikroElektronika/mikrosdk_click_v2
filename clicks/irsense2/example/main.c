/*!
 * \file 
 * \brief IrSense2 Click example
 * 
 * # Description
 * This application enables usage of IR sensor for presence detection.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver initialization.
 * 
 * ## Application Task  
 * Fetches IR and temperature sensor data and prints them on terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irsense2.h"

// ------------------------------------------------------------------ VARIABLES

static irsense2_t irsense2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    irsense2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    irsense2_cfg_setup( &cfg );
    IRSENSE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irsense2_init( &irsense2, &cfg );

    Delay_us( 100 );
    
    irsense2_default_cfg ( &irsense2 );
}

void application_task ( void )
{
    //  Task implementation.

    float temperature;
    float ir_data;
    uint8_t flag;

    Delay_ms( 400 );

    irsense2_data_read( &irsense2, &ir_data, &temperature );

    flag = irsense_human_detected( &irsense2, ir_data );
    
    if ( flag == 1 )
    {   log_printf( &logger, " \r\n----------------------------- \r\n");
        log_printf( &logger, "\r\n Person detected!!! \r\n" );
        log_printf( &logger, " \r\n----------------------------- \r\n");
        Delay_ms( 300 );
    }

    log_printf( &logger, "\r\n\r\nIR Value:       %.2f  pA ", ir_data );
    log_printf( &logger, " \r\n----------------------------- \r\n");
    log_printf( &logger, "Temperature: %.8f  C \r\n", temperature );

    Delay_ms( 1000 );
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
