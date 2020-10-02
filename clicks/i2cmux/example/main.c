/*!
 * \file 
 * \brief I2cMux Click example
 * 
 * # Description
 * This app reads "Who am I" register of the connected click boards to the UART MUX click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C,
 * executes call hardware reset, also write log.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the I2C MUX Click board.
 * In this example, we read "Who am I" register of the connected click boards to the UART MUX click.
 * Channel 0 : 6DOF IMU 9 click [ slave address: 0x69; reg: 0x75; id val.: 0xA9 ],
 * Channel 1 : RTC 10 click     [ slave address: 0x68; reg: 0x0F; id val.: 0x88 ],
 * Channel 2 : Altintude click  [ slave address: 0x60; reg: 0x0C; id val.: 0xC4 ],
 * Channel 3 : Temp & Hum click [ slave address: 0x5F; reg: 0x0F; id val.: 0xBC ].
 * All data logs write on USB UART changes every 2 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "i2cmux.h"

// ------------------------------------------------------------------ VARIABLES

static i2cmux_t i2cmux;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "  I2C MUX  Click  \r\n" );
    log_printf( &logger, "------------------\r\n" );

    i2cmux_cfg_setup( &cfg );
    I2CMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux_init( &i2cmux, &cfg );

    log_printf( &logger, " I2C driver init. \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 100 );
     
    i2cmux_hw_reset( &i2cmux );
    log_printf( &logger, "     HW reset     \r\n" );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint8_t rx_data;

    // SET CHANNEL 0: 6DOF IMU 9 click
    i2cmux_set_channel( &i2cmux, I2CMUX_CMD_SET_CH_0, 0x69 );
    Delay_ms( 100 );

    i2cmux_generic_read( &i2cmux, 0x75, &rx_data, 1 );
    log_printf( &logger, " CH-0 : ID = 0x%d\r\n", rx_data );

    // SET CHANNEL 1: RTC 10 click
    i2cmux_set_channel( &i2cmux, I2CMUX_CMD_SET_CH_1, 0x68 );
    Delay_ms( 100 );
    
    i2cmux_generic_read( &i2cmux, 0x0F, &rx_data, 1 );
    log_printf( &logger, " CH-1 : ST = 0x%d\r\n", rx_data );

    // SET CHANNEL 2: Altitude click
    i2cmux_set_channel( &i2cmux, I2CMUX_CMD_SET_CH_2, 0x60 );
    Delay_ms( 100 );
    
    i2cmux_generic_read( &i2cmux, 0x0C, &rx_data, 1 );
    log_printf( &logger, " CH-2 : ID = 0x%d\r\n", rx_data );

    // SET CHANNEL 3: Temp & Hum click
    i2cmux_set_channel( &i2cmux, I2CMUX_CMD_SET_CH_3, 0x5F );
    Delay_ms( 100 );
    
    i2cmux_generic_read( &i2cmux, 0x0F, &rx_data, 1 );
    log_printf( &logger, " CH-3 : ID = 0x%d\r\n", rx_data );

    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 2000 );
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
