/*!
 * \file 
 * \brief Proximity3 Click example
 * 
 * # Description
 * This application reads the data from the ambient light sensor
 * and converts the data into digital form using calculations.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C, initialize VCNL4100,
 * write configuration register and start write log to Usart Terminal.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Proximity 3 Click board.
 * Measured distance ( proximity ) and illuminance ( abmient light ) from sensor,
 * results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 3 sec.
 *
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity3.h"

// ------------------------------------------------------------------ VARIABLES

static proximity3_t proximity3;
static log_t logger;
uint16_t result_proximity;
uint16_t result_ambient_light;
uint16_t value_id;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proximity3_cfg_setup( &cfg );
    PROXIMITY3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity3_init( &proximity3, &cfg );

    // Default startup options for Ambient Light Sensor
    proximity3_write_16( &proximity3, PROXIMITY3_ALS_CONF_REG, PROXIMITY3_ALS_CONF_CONFIG );
    Delay_ms( 10 );

    // Default startup options for Proximity
    proximity3_write_16( &proximity3, PROXIMITY3_PS_CONF1_CONF2_REG, PROXIMITY3_PS_CONF1_CONF2_CONFIG );
    Delay_ms( 10 );
    proximity3_write_16( &proximity3, PROXIMITY3_PS_CONF3_MS_REG, PROXIMITY3_PS_CONF3_MS_CONFIG );
    Delay_ms( 10 );

    // Set the proximity interrupt levels
    proximity3_write_16( &proximity3, PROXIMITY3_PS_THDL_REG, PROXIMITY3_PS_THDL_CONFIG );
    Delay_10ms();
    proximity3_write_16( &proximity3, PROXIMITY3_PS_THDH_REG, PROXIMITY3_PS_THDH_CONFIG );
    Delay_10ms();    

    // Check device ID
    value_id = proximity3_read_16( &proximity3, PROXIMITY3_DEVICE_ID_REG );

    if ( value_id != PROXIMITY3_DEVICE_ID_VALUE )
    {
        log_printf( &logger, "        ERROR" );
    }
    else
    {
        log_printf( &logger, "       Initialization\r\n" );
        log_printf( &logger, "--------------------------\r\n" );
    }

    Delay_100ms();
}

void application_task ( void )
{
    result_proximity = proximity3_get_distance( &proximity3 );
    Delay_ms( 10 );

    log_printf( &logger, " Proximity:             %d cm\r\n", result_proximity );

    result_ambient_light = proximity3_get_illuminance( &proximity3 );
    log_printf( &logger, " Ambient Light:         %d lux\r\n", result_ambient_light );

    log_printf( &logger, "-----------------------------------------\r\n" );
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
