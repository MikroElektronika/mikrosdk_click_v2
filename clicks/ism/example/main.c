/*!
 * @file main.c
 * @brief Ism Click example
 *
 * # Description
 * This library contains API for the ISM Click driver.
 * This example transmits/receives and processes data from ISM clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and performs the default configuration. 
 *
 * ## Application Task
 * Transmitter/Receiver task depends on uncommented code.
 * Receiver logging each received byte to the UART for data logging,
 * while transmitter send messages every 1 second.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ism.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

static ism_t ism;
static log_t logger;

static uint8_t demo_message_1[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
static uint8_t demo_message_2[ 12 ] = { 'I', 'S', 'M', ' ', 'C', 'l', 'i', 'c', 'k', 13, 10, 0 };

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ism_cfg_t ism_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    ism_cfg_setup( &ism_cfg );
    ISM_MAP_MIKROBUS( ism_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ism_init( &ism, &ism_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    ism_default_cfg ( &ism );
    Delay_ms( 100 );
    
#ifdef DEMO_APP_TRANSMITTER
    ism_switch_tx_mode( &ism );
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    ism_switch_rx_mode( &ism );
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    ism_transmit_packet( &ism, ISM_CMD_W_TX_PAYLOAD_NOACK, demo_message_1, 9 );
    log_printf( &logger, "  Tx : %s", demo_message_1 );
    Delay_ms( 1000 );

    ism_transmit_packet( &ism, ISM_CMD_W_TX_PAYLOAD_NOACK, demo_message_2, 12 );
    log_printf( &logger, "  Tx : %s", demo_message_2 );
    Delay_ms( 1000 );
#else
    uint8_t rx_buf[ ISM_MAX_PACKET_LEN ] = { 0 };

    ism_receive_packet( &ism, &rx_buf[ 0 ] );

    if ( rx_buf[ 0 ] ) 
    {
        log_printf( &logger, "  Rx : %s", rx_buf );
    }
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
