/*!
 * \file 
 * \brief I2cMux4 Click example
 * 
 * # Description
 * This example demonstrates the use of the I2C MUX 4 Click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, enables the click board and makes an initial log.
 * 
 * ## Application Task  
 * In this example, we read the device ID register of the connected click boards.
 * Channel 0 : 6DOF IMU 12 click [slave address: 0x68; reg: 0x00; id val.: 0x24],
 * Channel 1 : Compass 3 click   [slave address: 0x30; reg: 0x2F; id val.: 0x0C].
 * All data logs write on USB UART changes every 2 sec.
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

    i2cmux4_cfg_setup( &cfg );
    I2CMUX4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux4_init( &i2cmux4, &cfg );

    i2cmux4_power_on( &i2cmux4, I2CMUX4_ENABLE_POWER_ON );
    Delay_ms ( 100 );
    
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_ALL_DISABLE, 0x00 );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    // CH 0 - 6DOF IMU 12 click
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_0, 0x68 );
    Delay_ms ( 100 );

    i2cmux4_rmt_read_bytes( &i2cmux4, 0x00, &rx_data, 1 );
    Delay_ms ( 100 );

    log_printf( &logger, "    6DOF IMU 12 click   \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    log_printf( &logger, "       ID = 0x%.2X  \r\n", ( uint16_t ) rx_data );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms ( 1000 );
    
    
    // CH 1 - Compass 3 click
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_1, 0x30 );
    Delay_ms ( 100 );

    i2cmux4_rmt_read_bytes( &i2cmux4, 0x2F, &rx_data, 1 );
    Delay_ms ( 100 );

    log_printf( &logger, "      Compass 3 click      \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    log_printf( &logger, "       ID = 0x%.2X \r\n ", ( uint16_t ) rx_data );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
