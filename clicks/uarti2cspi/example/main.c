/*!
 * \file 
 * \brief UARTI2CSPI Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the UART I2C/SPI Click module. 
 * The Click is a I2C/SPI to UART bridge interface. It requires a RS232/485 cable in order to be 
 * connected to other Click module or an adapter.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, configures UART, and enables UART interrupts. 
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * every 2 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uarti2cspi.h"

// ------------------------------------------------------------------ VARIABLES

// #define DEMO_APP_TRANSMITTER
#define DEMO_APP_RECEIVER

#define TEXT_TO_SEND    "MikroE - UART I2C/SPI Click\r\n"

static uarti2cspi_t uarti2cspi;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uarti2cspi_cfg_t cfg;

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

    uarti2cspi_cfg_setup( &cfg );
    UARTI2CSPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uarti2cspi_init( &uarti2cspi, &cfg );
    Delay_ms ( 1000 );

    uarti2cspi_advanced_init( &uarti2cspi, 115200, UARTI2CSPI_UART_8_BIT_DATA, 
                                                   UARTI2CSPI_UART_NOPARITY,
                                                   UARTI2CSPI_UART_ONE_STOPBIT );
    Delay_ms ( 100 );
    uarti2cspi_interrupt_enable( &uarti2cspi, UARTI2CSPI_RXD_INT_EN | UARTI2CSPI_THR_EMPTY_INT_EN );

    Delay_ms ( 100 );

#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- TRANSMITTER MODE ----" );
#endif
#ifdef DEMO_APP_RECEIVER
    log_info( &logger, "---- RECEIVER MODE ----" );
#endif
    Delay_ms ( 1000 );
}

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    uarti2cspi_uart_write_text( &uarti2cspi, TEXT_TO_SEND );
    log_info( &logger, "---- The message has been sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
#ifdef DEMO_APP_RECEIVER
    if ( uarti2cspi_uart_data_ready( &uarti2cspi ) )
    {
        uint8_t rx_data = uarti2cspi_uart_read( &uarti2cspi );
        log_printf( &logger, "%c", rx_data );
    }
#endif
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
