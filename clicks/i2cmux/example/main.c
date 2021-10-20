/*!
 * \file 
 * \brief I2cMux Click example
 * 
 * # Description
 * This example demonstrates the use of I2C MUX Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes the driver, preforms hardware reset, then enables channel 0 and 
 * makes an initial log.
 * 
 * ## Application Task  
 * Reads the device ID of a Spectrometer click (dev ID: 0x24) and displays it 
 * on the USB UART each second.
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

    i2cmux_cfg_setup( &cfg );
    I2CMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux_init( &i2cmux, &cfg );
    Delay_ms( 100 );
    i2cmux_hw_reset( &i2cmux );
    Delay_ms( 100 );
    
    i2cmux_set_channel( &i2cmux, I2CMUX_CMD_SET_CH_0, 0x39 );
    log_printf( &logger, " Please connect a Spectrometer click to channel 0\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms( 2000 );
}

void application_task ( void )
{
    uint8_t rx_data;
    
    i2cmux_generic_read( &i2cmux, 0x92, &rx_data, 1 );
    log_printf( &logger, " The click device ID is:  0x%.2X\r\n", ( uint16_t ) rx_data );
    log_printf( &logger, "-------------------------------\r\n" );
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
