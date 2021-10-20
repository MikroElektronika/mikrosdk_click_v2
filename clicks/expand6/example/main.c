/*!
 * \file 
 * \brief Expand6 Click example
 * 
 * # Description
 * This example demonstrates the use of EXPAND 6 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver and makes an initial log.
 * 
 * ## Application Task  
 * This example shows the capabilities of the EXPAND 6 click by toggling 
 * each of the 20 available pins.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "expand6.h"

// ------------------------------------------------------------------ VARIABLES

static expand6_t expand6;
static log_t logger;

uint8_t pin_num;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand6_cfg_t cfg;

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

    expand6_cfg_setup( &cfg );
    EXPAND6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand6_init( &expand6, &cfg );

    expand6_reset ( &expand6 );
    Delay_ms( 1000 );
    
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   EXPAND 6 click   \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}

void application_task ( void )
{
    expand6_write_port( &expand6, EXPAND6_PORT_0, 0xFF );
    expand6_write_port( &expand6, EXPAND6_PORT_1, 0xFF );
    expand6_write_port( &expand6, EXPAND6_PORT_2, 0xFF );
    
    log_printf( &logger, "All pins set to HIGH logic level!\r\n" );
    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms( 2000 );
    
    for ( pin_num = 0; pin_num < 20; pin_num++ )
    {
        expand6_write_pin( &expand6, pin_num, EXPAND6_LOW );
        log_printf( &logger, "Pin %u is set to LOW logic level!\r\n", ( uint16_t) pin_num );
        Delay_ms( 300 );
    }

    log_printf( &logger, "---------------------------------\r\n" );
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
