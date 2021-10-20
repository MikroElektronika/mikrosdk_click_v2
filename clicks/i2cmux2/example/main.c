/*!
 * \file 
 * \brief I2cMux2 Click example
 * 
 * # Description
 * This example demonstrates the use of the I2C MUX 2 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, performs the device reset, and makes an initial log.
 * 
 * ## Application Task  
 * In this example, we read the device ID register of the connected click boards.
 * Channel 0 : 6DOF IMU 11 click [slave address: 0x0E; reg: 0x00; id val.: 0x2D],
 * Channel 1 : Altitude click    [slave address: 0x60; reg: 0x0C; id val.: 0xC4],
 * Channel 2 : 6DOF IMU 9 click  [slave address: 0x69; reg: 0x75; id val.: 0xA9],
 * Channel 3 : Compass 3 click   [slave address: 0x30; reg: 0x2F; id val.: 0x0C].
 * All data logs write on USB UART changes every 2 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "i2cmux2.h"

// ------------------------------------------------------------------ VARIABLES

static i2cmux2_t i2cmux2;
static log_t logger;
static uint8_t rx_data;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void display_log ( uint8_t sel_ch )
{
    switch ( sel_ch )
    {
        case I2CMUX2_CMD_SET_CH_0:
        {
            log_printf( &logger, "   0  |  " );
            break;
        }
        case I2CMUX2_CMD_SET_CH_1:
        {
            log_printf( &logger, "   1  |  " );
            break;
        }
        case I2CMUX2_CMD_SET_CH_2:
        {
            log_printf( &logger, "   2  |  " );
            break;
        }
        case I2CMUX2_CMD_SET_CH_3:
        {
            log_printf( &logger, "   3  |  " );
            break;
        }
        default:
            break;
    }
    log_printf( &logger, "0x%.2X", ( uint16_t ) rx_data );
    
    if ( i2cmux2_check_int( &i2cmux2 ) == I2CMUX2_INT_PIN_STATE_ACTIVE )
    {
        if ( i2cmux2_read_interrupt( &i2cmux2 ) & sel_ch  )
        {
            log_printf( &logger, "  |  ON \r\n" );
        }
        else
        {
            log_printf( &logger, "  | OFF \r\n" );
        }
    }
    else
    {
        log_printf( &logger, "  | OFF \r\n" );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux2_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    i2cmux2_cfg_setup( &cfg );
    I2CMUX2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux2_init( &i2cmux2, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "I2C MUX 2 Click driver init\r\n");
    log_printf( &logger, "---------------------------------------\r\n");
    Delay_ms( 100 );

    i2cmux2_hw_reset( &i2cmux2 );
    log_printf( &logger, "I2C MUX 2 Click HW reset\r\n");
    log_printf( &logger, "---------------------------------------\r\n");
    Delay_ms( 100 );
}

void application_task ( void )
{
    log_printf( &logger, "  CH  |   ID   |  INT \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    
    // SET CHANNEL 0: 6DOF IMU 11 click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_0, 0x0E );
    Delay_ms( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x00, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_0 );
    
    // SET CHANNEL 1: Altitude click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_1, 0x60 );
    Delay_ms( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x0C, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_1 );
    
    // SET CHANNEL 2: 6DOF IMU 9 click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_2, 0x69 );
    Delay_ms( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x75, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_2 );

    // SET CHANNEL 3: Compass 3 click
    i2cmux2_set_channel( &i2cmux2, I2CMUX2_CMD_SET_CH_3, 0x30 );
    Delay_ms( 100 );
    i2cmux2_generic_read( &i2cmux2, 0x2F, &rx_data, 1 );
    display_log( I2CMUX2_CMD_SET_CH_3 );

    log_printf( &logger, "----------------------\r\n" );
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
