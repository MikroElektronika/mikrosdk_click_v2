/*!
 * \file 
 * \brief UARTI2CSPI Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the UART I2C/SPI click module. The
 * click is a I2C/SPI to UART bridge interface. It requires a RS232/485 cable in order to be conn-
 * ected to a different click module or an adapter.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click and logger modules. There's also a communic-
 * ation initialization function which puts the click module in "echo-mode". 
 * 
 * ## Application Task  
 * This function uses the "echo-mode" to write back every message the click receives over UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uarti2cspi.h"

// ------------------------------------------------------------------ VARIABLES

static uarti2cspi_t uarti2cspi;
static log_t logger;

uint8_t str0[ 19 ] = "System initialized";
uint8_t str1[ 22 ] = "+++++++++++++++++++++";
uint8_t str2[ 24 ] = "Entering echo mode";

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void comm_init ( )
{
    uint16_t cnt;
    char text[ 6 ] = { 'M', 'i', 'k', 'r', 'o', 'E' };

    for( cnt = 0; cnt < 10; cnt++ )
    {
        uarti2cspi_serial_write( &uarti2cspi, &text[ 0 ], LINE_PRINT );
        Delay_100ms( );
    }

    uarti2cspi_serial_write( &uarti2cspi, &str1[ 0 ], LINE_PRINT );
    uarti2cspi_serial_write( &uarti2cspi, &str2[ 0 ], LINE_PRINT );
    uarti2cspi_uart_write( &uarti2cspi, 0x00 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uarti2cspi_cfg_t cfg;
    uarti2cspi_package_t package;
    uint8_t vector;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 19200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uarti2cspi_cfg_setup( &cfg );
    UARTI2CSPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uarti2cspi_init( &uarti2cspi, &cfg );

    package.baud_rate = 19200;
    package.data_bits = UARTI2CSPI_UART_8_BIT_DATA;
    package.parity_mode = UARTI2CSPI_UART_NOPARITY;
    package.stop_bits = UARTI2CSPI_UART_ONE_STOPBIT;

    vector = UARTI2CSPI_RXD_INT_EN | UARTI2CSPI_THR_EMPTY_INT_EN;

    uarti2cspi_advanced_init( &uarti2cspi, package );
    uarti2cspi_interrupt_enable( &uarti2cspi, vector );

    Delay_100ms( );
    uarti2cspi_serial_write( &uarti2cspi, &str0[ 0 ], LINE_PRINT );
    log_printf( &logger, " * Initialization complete *\r\n" );
    Delay_1sec( );

    comm_init( );
    Delay_1sec( );
}

void application_task ( void )
{
    uarti2cspi_uart_write( &uarti2cspi, uarti2cspi_uart_read( &uarti2cspi ) );
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
