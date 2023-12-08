/*!
 * \file 
 * \brief ccRf2 Click example
 * 
 * # Description
 * This example demonstrates the use of ccRF 2 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, performs the default configuration and enables the selected mode.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads the received data or sends the desired message
 * every 2 seconds. All data is being logged on the USB UART where you can track their changes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ccrf2.h"

#define TEXT_TO_SEND "MikroE\r\n"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_TRANSMITTER
// #define DEMO_APP_RECEIVER

static ccrf2_t ccrf2;
static log_t logger;

static uint8_t rx_buffer[ 255 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ccrf2_cfg_t cfg;

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

    ccrf2_cfg_setup( &cfg );
    CCRF2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf2_init( &ccrf2, &cfg );
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Hardware reset\r\n" );
    ccrf2_hw_reset( &ccrf2 );
    Delay_ms( 1000 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Default config\r\n" );
    ccrf2_default_cfg( &ccrf2 );
    Delay_ms( 1000 );

    log_printf( &logger, "----------------------\r\n" );

#ifdef DEMO_APP_RECEIVER
    ccrf2_set_rx_mode( &ccrf2 );
    
    log_printf( &logger, " Receiver mode\r\n" );
#endif
#ifdef DEMO_APP_TRANSMITTER
    ccrf2_set_tx_mode( &ccrf2 );
    
    log_printf( &logger, " Transmitter mode\r\n" );
#endif

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    uint8_t num_bytes = ccrf2_receive_rx_data( &ccrf2, &rx_buffer[ 0 ] );
    if ( num_bytes )
    {
        log_printf( &logger, " Received message: " );
        for ( uint8_t cnt = 3; cnt < rx_buffer[ 0 ]; cnt++ )
        {
            log_printf( &logger, "%c", rx_buffer[ cnt ] );
        }
        log_printf( &logger, " Packet number: %u", ccrf2.packet_counter );
        log_printf( &logger, "\r\n----------------------\r\n" );
    }
#endif
#ifdef DEMO_APP_TRANSMITTER
    ccrf2_send_tx_data( &ccrf2, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_printf( &logger, " Sent message: MikroE\r\n" );
    log_printf( &logger, " Packet number: %u\r\n", ccrf2.packet_counter );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 2000 );
#endif
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
