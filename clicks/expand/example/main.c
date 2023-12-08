/*!
 * \file 
 * \brief Expand Click example
 * 
 * # Description
 * This applicatioin use for expansion I/O lines.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - GPIO,
 * reset MCP23S17 chip, set PORTA to be output and PORTB to be input,
 * set default configuration and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Expand Click board.
 * Expand Click communicates with register via SPI protocol by write and read from register,
 * set configuration and state and read configuration and state.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 500 ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "expand.h"

// ------------------------------------------------------------------ VARIABLES

static expand_t expand;
static log_t logger;

static uint8_t port_status;
static uint8_t position;
static uint16_t pin_position;

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand_cfg_t cfg;

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

    expand_cfg_setup( &cfg );
    EXPAND_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand_init( &expand, &cfg );
    
    expand_default_configuration( &expand, EXPAND_SPI_MODULE_POSITION_0 );

    expand_set_direction_port_a( &expand, EXPAND_SPI_MODULE_POSITION_0, EXPAND_PORT_DIRECTION_OUTPUT );
    
    expand_set_direction_port_b( &expand, EXPAND_SPI_MODULE_POSITION_0, EXPAND_PORT_DIRECTION_INPUT );
    
    expand_set_pull_ups_port_b( &expand, EXPAND_SPI_MODULE_POSITION_0, 0xFF );
}

void application_task ( void )
{
    pin_position = 1;

    for ( position = 0; position < 8; position++ )
    {
        expand_write_port_a( &expand, EXPAND_SPI_MODULE_POSITION_0, pin_position );
        log_printf( &logger, " PA%d set\r\n", (uint16_t) position );

        port_status = expand_read_port_b( &expand, EXPAND_SPI_MODULE_POSITION_0 );

        log_printf( &logger, " Status PB (input) : %d  \r\n", (uint16_t) port_status );
        log_printf( &logger, "----------------\r\n" );
        
        pin_position <<= 1;

        Delay_ms( 500 );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
