/*!
 * \file 
 * \brief PowerBank Click example
 * 
 * # Description
 * This application is example of the PowerBank Click functionality
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver and makes an initial log.
 * 
 * ## Application Task  
 * This example shows the capabilities of the 
 * PowerBank click by measuring voltage of the connected
 * battery. In order to get correct calculations user should
 * change "v_ref" value to his own power supply voltage.
 * 
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "powerbank.h"

// ------------------------------------------------------------------ VARIABLES

static powerbank_t powerbank;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    powerbank_cfg_t cfg;

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

    powerbank_cfg_setup( &cfg );
    POWERBANK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    powerbank_init( &powerbank, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "     PowerBank click    \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}

void application_task ( void )
{
    uint16_t voltage;
    uint16_t v_ref = 5075;

    voltage = powerbank_read_voltage( &powerbank, v_ref );
    log_printf( &logger, "Battery voltage: %d mV\r\n", voltage );
    
    log_printf( &logger, "------------------------\r\n" );
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
