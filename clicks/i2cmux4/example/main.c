/*!
 * \file 
 * \brief I2cMux4 Click example
 * 
 * # Description
 * This demo app demonstrates the use of the I2C MUX 4 Click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C,
 * executes call power On and hardware reset, also write log.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the I2C MUX 4 Click board.
 * In this example, we read "Who am I" ( or "State" ) register
 * of the connected click boards to the I2C MUX 4 click.
 * Channel 0 : 6DOF IMU 12 click [slave address: 0x0E; reg: 0x00; id val.: 0x24],
 * Channel 1 : RTC 10 click      [slave address: 0x68; reg: 0x0F; st val.: 0x88].
 * All data logs write on USB UART changes approximately every 2 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "i2cmux4.h"

// ------------------------------------------------------------------ VARIABLES

static i2cmux4_t i2cmux4;
static log_t logger;

uint8_t rx_data;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    i2cmux4_cfg_setup( &cfg );
    I2CMUX4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux4_init( &i2cmux4, &cfg );

    i2cmux4_power_on( &i2cmux4, I2CMUX4_ENABLE_POWER_ON );
    Delay_ms( 100 );
    
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_ALL_DISABLE, 0x00 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    // CH 0 - 6DOF IMU 12 click
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_0, 0x68 );
    Delay_ms( 100 );

    i2cmux4_rmt_read_bytes( &i2cmux4, 0x00, &rx_data, 1 );
    Delay_ms( 100 );

    log_printf( &logger, "    6DOF IMU 12 click   \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    log_printf( &logger, "       ID = 0x%d  \r\n", rx_data );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms( 1000 );
    
    
    // CH 1 - RTC 10 click
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_1, 0x68 );
    Delay_ms( 100 );

    i2cmux4_rmt_read_bytes( &i2cmux4, 0x0F, &rx_data, 1 );
    Delay_ms( 100 );

    log_printf( &logger, "      RTC 10 click      \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    log_printf( &logger, "       ID = 0x%d \r\n ", rx_data );
    log_printf( &logger, "----------------------- \r\n" );
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
