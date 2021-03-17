/*!
 * \file 
 * \brief Ambient9 Click example
 * 
 * # Description
 * This example demonstrates the use of Ambient 9 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver then reads the device status and part ID. If there's any error occured 
 * it displays an appropriate message on the USB UART. After that, it enables the device mode
 * defined by the dev_mode variable. ALS mode is selected by default.
 * 
 * ## Application Task  
 * Depending on the selected device mode, it reads an ambient light sensor or proximity data and 
 * displays the results on the USB UART every 100ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ambient9.h"

// ------------------------------------------------------------------ VARIABLES

static ambient9_t ambient9;
static log_t logger;

static uint8_t dev_mode = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient9_cfg_t cfg;

    uint8_t status_data;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ambient9_cfg_setup( &cfg );
    AMBIENT9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient9_init( &ambient9, &cfg );

    ambient9_generic_read( &ambient9, AMBIENT9_REG_PART_ID, &status_data, 1 );
    if ( AMBIENT9_PART_ID_VAL != status_data )
    {
        log_printf( &logger, " *****  ERROR ID!  ***** \r\n" );
        for( ; ; );
    }
    Delay_ms( 500 );
    ambient9_generic_read( &ambient9, AMBIENT9_REG_MAIN_STATUS, &status_data, 1 );
    if ( AMBIENT9_POWER_ON == ( status_data & AMBIENT9_POWER_ON ) )
    {
        log_printf( &logger, " *****  ERROR POWER ON!  ***** \r\n" );
        for( ; ; );
    }
    
    dev_mode = AMBIENT9_ALS;
    ambient9_enable_data( &ambient9, dev_mode );  

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    uint16_t proxy_data;
    uint32_t als_data;

    if ( AMBIENT9_ALS == dev_mode )
    {
        als_data = ambient9_als_data( &ambient9 );
        log_printf( &logger, " - ALS data: %lu \r\n", als_data );
    }
    else if ( AMBIENT9_PROXY == dev_mode )
    {
        proxy_data = ambient9_proxy_data( &ambient9 );
        log_printf( &logger, " - Proximity data: %u \r\n", proxy_data );
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
