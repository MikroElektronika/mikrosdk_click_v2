/*!
 * \file 
 * \brief I2cMux3 Click example
 * 
 * # Description
 * This demo app shows the capabilities of the I2C MUX 3.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, preforms hardware reset
 * and makes an initial log.
 * 
 * ## Application Task  
 * This example shows the capabilities of the I2C MUX 3 click 
 *                   by reading device ID values from eight different click 
 *                   boards and displaying the readings via USART terminal. Some
 *                   of the used click boards have the same I2C slave addresses,
 *                   while others do not.
 * 
 * *note:* 
 * Click boards used in this example :
 *                6DOF IMU 12 click -   https://www.mikroe.com/6dof-imu-12-click
 *                RTC 10 click -             https://www.mikroe.com/rtc-10-click
 *                Surface Temp click - https://www.mikroe.com/surface-temp-click
 *                Spectrometer click - https://www.mikroe.com/spectrometer-click
 *                Compass 3 click -       https://www.mikroe.com/compass-3-click
 *                Color 3 click -           https://www.mikroe.com/color-3-click
 *                6DOF IMU 11 click -   https://www.mikroe.com/6dof-imu-11-click
 *                Heart Rate 4 click - https://www.mikroe.com/heart-rate-4-click
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "i2cmux3.h"

// ------------------------------------------------------------------ VARIABLES

static i2cmux3_t i2cmux3;
static log_t logger;

uint8_t id_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    i2cmux3_cfg_setup( &cfg );
    I2CMUX3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux3_init( &i2cmux3, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "------------------------- \r\n" );
    log_printf( &logger, "     I2C MUX 3 Click      \r\n" );
    log_printf( &logger, "------------------------- \r\n" );
    i2cmux3_hw_rst( &i2cmux3 );
    i2cmux3_ch_sel( &i2cmux3, I2CMUX3_DIS_ALL_CH );
    Delay_ms( 100 );
    log_printf( &logger, "     Click  Enabled!      \r\n" );
    log_printf( &logger, "------------------------- \r\n" );
}

void application_task ( void )
{
    log_printf( &logger, "------------------------- \r\n" );
    log_printf( &logger, "ID values by click board: \r\n" );
    log_printf( &logger, "------------------------- \r\n" );
    log_printf( &logger, " \r\n" );

    i2cmux3_ch_sel( &i2cmux3, 0 );
    i2cmux3_rd_slv ( &i2cmux3, 0x68, 0x00, &id_val, 1 );
    log_printf( &logger, " 6DOF IMU 12  : 0x%d \r\n", id_val );
    log_printf( &logger, "------------------------- \r\n" );
    Delay_ms( 100 );

    i2cmux3_ch_sel( &i2cmux3, 1 );
    i2cmux3_rd_slv ( &i2cmux3, 0x68, 0x0F, &id_val, 1 );
    log_printf( &logger, " RTC 10       : 0x%d \r\n", id_val );
    log_printf( &logger, "------------------------- \r\n" );
    Delay_ms( 100 );

    i2cmux3_ch_sel( &i2cmux3, 2 );
    i2cmux3_rd_slv ( &i2cmux3, 0x48, 0x0B, &id_val, 1 );
    log_printf( &logger, " Surface Temp : 0x%d \r\n", id_val );
    log_printf( &logger, "------------------------- \r\n" );
    Delay_ms( 100 );
    
    i2cmux3_ch_sel( &i2cmux3, 3 );
    i2cmux3_rd_slv ( &i2cmux3, 0x39, 0x92, &id_val, 1 );
    log_printf( &logger, " Spectrometer : 0x%d \r\n", id_val );
    log_printf( &logger, "------------------------- \r\n" );
    Delay_ms( 100 );
    
    i2cmux3_ch_sel( &i2cmux3, 4 );
    i2cmux3_rd_slv ( &i2cmux3, 0x30, 0x2F, &id_val, 1 );
    log_printf( &logger, " Compass 3    : 0x%d \r\n", id_val );
    log_printf( &logger, "------------------------- \r\n" );
    Delay_ms( 100 );
    
    i2cmux3_ch_sel( &i2cmux3, 5 );
    i2cmux3_rd_slv ( &i2cmux3, 0x29, 0x12, &id_val, 1 );
    log_printf( &logger, " Color 3      : 0x%d \r\n", id_val );
    log_printf( &logger, "------------------------- \r\n" );
    Delay_ms( 100 );
    
    i2cmux3_ch_sel( &i2cmux3, 6 );
    i2cmux3_rd_slv ( &i2cmux3, 0x0E, 0x00, &id_val, 1 );
    log_printf( &logger, " 6DOF IMU 11  : 0x%d \r\n", id_val );
    log_printf( &logger, "------------------------- \r\n" );
    Delay_ms( 100 );
    
    i2cmux3_ch_sel( &i2cmux3, 7 );
    i2cmux3_rd_slv ( &i2cmux3, 0x57, 0xFF, &id_val, 1 );
    log_printf( &logger, " Heart Rate 4 : 0x%d \r\n", id_val );
    log_printf( &logger, "------------------------- \r\n" );
    Delay_ms( 100 );

    log_printf( &logger, " \r\n" );
    log_printf( &logger, "------------------------- \r\n" );
    Delay_ms( 3000 );
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
