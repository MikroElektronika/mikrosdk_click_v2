/*!
 * @file main.c
 * @brief Ism Click example
 *
 * # Description
 * This library contains API for the ISM Click driver.
 * This example transmits/receives and processes data from ISM clicks.
 * The library initializes and defines the UART bus drivers 
 * to transmit or receive data. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and set performs the default configuration. 
 *
 * ## Application Task
 * Transmitter/Receiver task depends  on uncommented code.
 * Receiver logging each received byte to the UART for data logging,
 * while transmitted send messages every 1 second.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ism.h"

#define RECEIVER
// #define TRANSMITTER

static ism_t ism;
static log_t logger;

static uint8_t demo_message_1[ 9 ] = { 
    'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 
    
};
static uint8_t demo_message_2[ 12 ] = { 
    'I', 'S', 'M', ' ', 'C', 'l', 'i', 'c', 'k', 13, 10, 0 
    
};

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    ism_cfg_t ism_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ism_cfg_setup( &ism_cfg );
    ISM_MAP_MIKROBUS( ism_cfg, MIKROBUS_1 );
    err_t init_flag  = ism_init( &ism, &ism_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    ism_default_cfg ( &ism );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 100 );

    #ifdef RECEIVER   
        ism_switch_rx_mode( &ism );
        log_printf( &logger, "   Receive data  \r\n" );
    #endif
   
    #ifdef TRANSMITTER
        ism_switch_tx_mode( &ism );
        log_printf( &logger, "  Transmit data   \r\n" );
    #endif
        
    log_printf( &logger, "------------------\r\n" );
}

void application_task ( void ) {
    #ifdef RECEIVER
        uint8_t rx_buf[ ISM_MAX_PACKET_LEN ] = { 0 };

        ism_receive_packet( &ism, &rx_buf[ 0 ] );
    
        if ( rx_buf[ 0 ] != 0 ) {
            log_printf( &logger, "  Rx : %s", rx_buf );
        }
    #endif

    #ifdef TRANSMITTER
        ism_transmit_packet( &ism, ISM_CMD_W_TX_PAYLOAD_NOACK, &demo_message_1[ 0 ], 9 );
        log_printf( &logger, "  Tx : %s", demo_message_1 );
        Delay_ms( 1000 );
    
        ism_transmit_packet( &ism, ISM_CMD_W_TX_PAYLOAD_NOACK, &demo_message_2[ 0 ], 12 );
        log_printf( &logger, "  Tx : %s", demo_message_2 );
        Delay_ms( 1000 );
    #endif
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
