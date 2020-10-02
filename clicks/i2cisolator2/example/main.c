/*!
 * \file 
 * \brief I2CIsolator2 Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the I2C Isolator 2 click module.
 * The click provides I2C lines and power isolation for slave devices. In order for this exam-
 * ple to work, you need the IrThermo 2 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click and logger modules. Additional configuring
 * is done in the default_cfg(...) function.
 * 
 * ## Application Task  
 * This function reads temperature data from the IrThermo 2 click and displays that data in the
 * UART console every second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "i2cisolator2.h"

// ------------------------------------------------------------------ VARIABLES

static i2cisolator2_t i2cisolator2;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

float get_object_temperature( )
{
    uint8_t r_buf[ 2 ];
    uint16_t temp;

    i2cisolator2_generic_read( &i2cisolator2, I2CISOLATOR2_IRTHERMO2_OBJECT_TEMPERATURE, r_buf, 2 );

    temp = r_buf[ 0 ];
    temp <<= 8;
    temp |= r_buf[ 1 ];
    temp >>= 2;

    return ( float ) temp * I2CISOLATOR2_IRTHERMO2_TEMP_COEFFICIENT;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    i2cisolator2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    i2cisolator2_cfg_setup( &cfg );
    I2CISOLATOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cisolator2_init( &i2cisolator2, &cfg );
    i2cisolator2_default_cfg( &i2cisolator2 );
}

void application_task ( )
{
    float temp;

    temp = get_object_temperature( );
    Delay_100ms( );

    log_printf( &logger, " .temperature: %f C\r\n", temp );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_1sec( );
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
