/*!
 * @file main.c
 * @brief ISM 3 Click example
 *
 * # Description
 * This example demonstrates the use of an ISM 3 Click board by showing
 * the communication between the two Click boards (Server and Client).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * There are two application modes: Server and Client.
 * - Server mode: Waits for a message from client device, reads the received packet
 *                and responds with an acknowledge message.
 * - Client mode: Initiates communication with the server device by sending a desired
 *                packet which contains the text message and a packet counter approximately 
 *                every 500 milliseconds. After sending the packet it waits for an acknowledge
 *                response from server. The packet counter is incremented only after
 *                successfull acknowledgment for the last packet.
 * All data is being displayed on the USB UART where you can track their changes.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ism3.h"

// Comment out the line below in order to switch the application mode to client
#define DEMO_APP_SERVER

// Text message which the client device sends to the server
#define TEXT_MESSAGE_TO_SEND    "Greetings from ISM 3 Click board client"

// An acknowledge response message which the server device sends to the client
#define ACKNOWLEDGE_RESPONSE    "ACK OK"

static ism3_t ism3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ism3_cfg_t ism3_cfg;  /**< Click config object. */

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
    ism3_cfg_setup( &ism3_cfg );
    ISM3_MAP_MIKROBUS( ism3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ism3_init( &ism3, &ism3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ISM3_ERROR == ism3_default_cfg ( &ism3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    err_t error_flag = ISM3_OK;
    static uint16_t packet_cnt = 0;
    uint8_t data_buf[ ISM3_PACKET_LEN ] = { 0 };
#ifdef DEMO_APP_SERVER
    log_printf ( &logger, " Waiting for a packet message from client device...\r\n" );
    error_flag = ism3_receive_packet ( &ism3, data_buf, NULL );
    if ( ISM3_OK == error_flag )
    {
        packet_cnt = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        log_printf ( &logger, " Packet #%u is received with message: %s\r\n", packet_cnt, &data_buf[ 2 ] );
        Delay_ms ( 200 );
        log_printf ( &logger, " Server transmits an acknowledge message to client for packet #%u\r\n", packet_cnt );
        error_flag = ism3_transmit_packet ( &ism3, ACKNOWLEDGE_RESPONSE, strlen ( ACKNOWLEDGE_RESPONSE ) );
    }
    log_printf ( &logger, " --------------------------------------------\r\n\n" );
#else
    if ( ( strlen ( TEXT_MESSAGE_TO_SEND ) + 2 ) > ISM3_PACKET_LEN )
    {
        log_error( &logger, " Packet exceeds maximal allowable length." );
        error_flag = ISM3_ERROR;
    }
    if ( ISM3_OK == error_flag )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( packet_cnt >> 8 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( packet_cnt & 0xFF );
        memcpy ( &data_buf[ 2 ], TEXT_MESSAGE_TO_SEND, strlen ( TEXT_MESSAGE_TO_SEND ) );
        log_printf ( &logger, " Client transmits packet #%u to server\r\n", packet_cnt );
        error_flag = ism3_transmit_packet ( &ism3, data_buf, strlen ( TEXT_MESSAGE_TO_SEND ) + 2 );
    }
    if ( ISM3_OK == error_flag )
    {
        log_printf ( &logger, " Waiting for an acknowledge...\r\n" );
        error_flag = ism3_receive_packet ( &ism3, data_buf, NULL );
    }
    if ( ( ISM3_OK == error_flag ) && ( strstr ( data_buf, ACKNOWLEDGE_RESPONSE ) ) )
    {
        log_printf ( &logger, " Acknowledge message is received from server!\r\n" );
        packet_cnt++;
    }
    else
    {
        log_printf ( &logger, " Acknowledge message is NOT received from server!\r\n" );
        error_flag = ism3_go_to_rx ( &ism3 );
    }
    log_printf ( &logger, " --------------------------------------------\r\n\n" );
    Delay_ms ( 500 );
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
