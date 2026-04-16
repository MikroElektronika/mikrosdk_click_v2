/*!
 * @file main.c
 * @brief MiWi Click example
 *
 * # Description
 * This example demonstrates basic transmit and receive functionality of the
 * MiWi Click board based on the MRF89XA sub-GHz transceiver. The application
 * configures the device to operate at 868 MHz using FSK modulation in packet
 * mode with a bit rate of 5 kbps and frequency deviation of 33 kHz.
 *
 * The demo supports two operating modes:
 *  - Transmitter mode
 *  - Receiver mode
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and driver, performs the default radio configuration,
 * and sets the device into transmitter or receiver mode depending on the
 * selected demo macro.
 *
 * ## Application Task
 * In transmitter mode, the application periodically sends a fixed-length
 * payload and logs transmitted packet.
 * In receiver mode, the application polls the IRQ0 pin for packet reception,
 * reads the received payload from FIFO, and logs packet data.
 *
 * @note
 * The payload length is fixed and must match the configured packet handler
 * settings inside the default driver configuration.
 * 
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "miwi.h"

#ifndef MIKROBUS_POSITION_MIWI
    #define MIKROBUS_POSITION_MIWI MIKROBUS_1
#endif

// Demo message used as payload in transmitter mode
#define DEMO_MESSAGE    "MiWi Click Demo!"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

static miwi_t miwi;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    miwi_cfg_t miwi_cfg;  /**< Click config object. */

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
    miwi_cfg_setup( &miwi_cfg );
    MIWI_MAP_MIKROBUS( miwi_cfg, MIKROBUS_POSITION_MIWI );
    if ( SPI_MASTER_ERROR == miwi_init( &miwi, &miwi_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MIWI_ERROR == miwi_default_cfg ( &miwi ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, " *** TX MODE ***" );
    log_printf( &logger, "868 MHz | FSK | 5kbps | 33Khz frequency deviation | %u B payload\r\n", MIWI_PAYLOAD_LEN );
    log_printf( &logger, "-----------------------------------\r\n" );
    Delay_ms( 200 );
#else
    /* Enter RX mode immediately */
    miwi_set_mode( &miwi, MIWI_RF_RECEIVER );
    log_info( &logger, " *** RX MODE ***" );
    log_printf( &logger, "868 MHz | FSK | 5kbps | 33Khz frequency deviation | %u B payload\r\n", MIWI_PAYLOAD_LEN );
    log_printf( &logger, "Waiting for packets...\r\n" );
    log_printf( &logger, "-----------------------------------\r\n" );
    Delay_ms( 200 ); 
#endif

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint16_t pkt_count = 0;
    uint8_t payload[ MIWI_PAYLOAD_LEN ];

#ifdef DEMO_APP_TRANSMITTER
    memcpy( payload, DEMO_MESSAGE, MIWI_PAYLOAD_LEN );

    log_printf( &logger, "[TX #%u] %.*s\r\n", pkt_count, MIWI_PAYLOAD_LEN, ( char* ) payload );

    if ( MIWI_OK == miwi_tx_packet( &miwi, payload ) )
    {
        log_printf( &logger, "  TXDONE OK\r\n" );
    }
    else
    {
        log_printf( &logger, "  TXDONE TIMEOUT\r\n" );
    }

    log_printf( &logger, "-----------------------------------\r\n" );
    pkt_count++;
    Delay_ms( MIWI_TX_INTERVAL_MS );
#else
    if ( MIWI_OK == miwi_rx_packet( &miwi, payload ) )
    {
        log_printf( &logger, "[RX #%u] %.*s\r\n", pkt_count, MIWI_PAYLOAD_LEN, ( char* ) payload );
        log_printf( &logger, "-----------------------------------\r\n" );
        pkt_count++;
    }
    else
    {
        log_printf( &logger, "  RX TIMEOUT\r\n" );
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
