/*!
 * @file main.c
 * @brief IrDA 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of an IrDA 2 Click board by showing
 * the communication between the two Click boards.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes device and makes an initial log.
 * 
 * ## Application Task
 * Depending on the selected application mode, it reads all the received data or 
 * sends the desired text message once per second.
 *
 * @author MikroE Team
 *
 */
#include "board.h"
#include "log.h"
#include "irda2.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

// Text message to send in the transmitter application mode
#define DEMO_TEXT_MESSAGE           "MIKROE - IrDA 2 Click board\r\n\0"

static irda2_t irda2;
static log_t logger;

void application_init ( void ) 
{
    irda2_cfg_t irda2_cfg;
    log_cfg_t logger_cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( logger_cfg );
    log_init( &logger, &logger_cfg );
    log_info( &logger, " Application Init " );
    
    //  Click initialization.
    irda2_cfg_setup( &irda2_cfg );
    IRDA2_MAP_MIKROBUS( irda2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == irda2_init( &irda2, &irda2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    irda2_default_cfg( &irda2 );
    irda2_reset( &irda2 );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    irda2_generic_write( &irda2, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) );
    log_printf( &logger, "%s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 ); 
#else
    uint8_t rx_byte = 0;
    if ( 1 == irda2_generic_read( &irda2, &rx_byte, 1 ) )
    {
       log_printf( &logger, "%c", rx_byte );
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

