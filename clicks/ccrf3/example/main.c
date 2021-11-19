/*!
 * @file main.c
 * @brief ccRF3 Click example
 *
 * # Description
 * This example demonstrates the use of ccRF 3 click board.
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
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ccrf3.h"

#define TEXT_TO_SEND "MikroE\r\n"

static ccrf3_t ccrf3;
static log_t logger;
static uint8_t rx_buffer[ 255 ];

#define DEMO_APP_TRANSMITTER

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ccrf3_cfg_t ccrf3_cfg;  /**< Click config object. */

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
    log_printf( &logger, " Application Init \r\n" );

    // Click initialization.
    ccrf3_cfg_setup( &ccrf3_cfg );
    CCRF3_MAP_MIKROBUS( ccrf3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ccrf3_init( &ccrf3, &ccrf3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Hardware reset\r\n" );
    ccrf3_hw_reset( &ccrf3 );
    Delay_ms( 1000 );
    
    if ( CCRF3_ERROR == ccrf3_default_cfg ( &ccrf3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, "----------------------\r\n" );
#ifdef DEMO_APP_TRANSMITTER
    ccrf3_set_tx_mode( &ccrf3 );
    
    log_printf( &logger, " Transmitter mode\r\n" );
#else
    ccrf3_set_rx_mode( &ccrf3 );
    
    log_printf( &logger, " Receiver mode\r\n" );
#endif

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 100 );
    
    log_printf( &logger, " Application Task \r\n" );
    log_printf( &logger, "----------------------\r\n" );
}

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    ccrf3_send_tx_data( &ccrf3, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_printf( &logger, " Sent message: MikroE\r\n" );
    log_printf( &logger, " Packet number: %u\r\n", ccrf3.packet_counter );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 2000 );
#else
    uint8_t num_bytes = ccrf3_receive_rx_data( &ccrf3, &rx_buffer[ 0 ] );
    if ( num_bytes )
    {
        log_printf( &logger, " Received message: " );
        for ( uint8_t cnt = 3; cnt < rx_buffer[ 0 ]; cnt++ )
        {
            log_printf( &logger, "%c", rx_buffer[ cnt ] );
        }
        log_printf( &logger, " Packet number: %u", ccrf3.packet_counter );
        log_printf( &logger, "\r\n----------------------\r\n" );
    }
#endif
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
