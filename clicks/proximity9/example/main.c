/*!
 * \file 
 * \brief Proximity9 Click example
 * 
 * # Description
 * This application is proximity sensing (PS) and ambient light sensing (ALS) device.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C interface and performs a device configurations.
 * 
 * ## Application Task  
 * Performs a data reading and interrupt flag checking.
 * Allows data and interrupt flags messages to be showed on the uart terminal.
 * 
 * *note:* 
 * The ALS sensitivity depends on the ALS integration time setting.
 * The longer integration time has higher sensitivity.
 * The Proximity (PS) output data can be set to 12-bit or 16-bit resolution.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity9.h"

// ------------------------------------------------------------------ VARIABLES

static proximity9_t proximity9;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity9_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proximity9_cfg_setup( &cfg );
    PROXIMITY9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity9_init( &proximity9, &cfg );

    proximity9_default_cfg( &proximity9 );

    log_printf( &logger, "** Proximity 9 is initialized ** \r\n" );
    log_printf( &logger, "************************************ \r\n" );
    Delay_ms( 300 );
}

void application_task ( )
{
    uint8_t int_check;
    uint16_t prox_data;
    float als_data;
    uint8_t temp;

    als_data = proximity9_get_als_lux( &proximity9 );
    proximity9_read_register( &proximity9, PROXIMITY9_PS_DATA_REG, &prox_data );
    temp = PROXIMITY9_PS_IF_CLOSE_FLAG | PROXIMITY9_PS_IF_AWAY_FLAG;
    int_check = proximity9_check_int_flag( &proximity9, temp );
    
    log_printf( &logger, "** ALS: %.2f lux \r\n", als_data );
    log_printf( &logger, "** PROXIMITY: %d \r\n", prox_data );
    
    if ( int_check == PROXIMITY9_PS_IF_CLOSE_FLAG )
    {
        log_printf( &logger, "** Object is close! \r\n" );
        log_printf( &logger, "************************************ \r\n" );
        Delay_ms( 1000 );
    }
    if ( int_check == PROXIMITY9_PS_IF_AWAY_FLAG )
    {
        log_printf( &logger, "** Object is away!\r\n" );
        log_printf( &logger, "************************************ \r\n" );
        Delay_ms( 1000 );
    }
    if ( int_check == PROXIMITY9_INT_CLEARED )
    {
        log_printf( &logger, "************************************ \r\n" );
        Delay_ms( 1000 );
    }
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
