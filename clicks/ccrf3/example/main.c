/*!
 * \file 
 * \brief ccRf3 Click example
 * 
 * # Description
 * The clicks will enable you to add a low-power consumption radio transceiver at 433 MHz 
 * frequency. ccRF 3 click is designed to run on a 3.3V power supply. It communicates with 
 * the target microcontroller over SPI interface.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - SPI,
 * hardware reset chip, sets default configuration, sets manual calibration, 
 * sets operation mode, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of ccRF 3 click board.
 * If RX mode selected, checks if new data byte has received in RX buffer ( ready for reading ),
 * and if ready than reads one byte from RX buffer.
 * In the second case, the application task writes received message data via UART.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ccrf3.h"

// ------------------------------------------------------------------ VARIABLES

static ccrf3_t ccrf3;
static log_t logger;

static uint8_t tx_buffer[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
static uint8_t rx_buffer[ 9 ];

static uint8_t mode_selected;
static uint8_t length_rx;
static uint8_t length_tx;
static uint8_t cnt;
static uint8_t send_flag = 0;
static uint8_t receive_flag = 0;
static uint8_t reading_flag = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ccrf3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ccrf3_cfg_setup( &cfg );
    CCRF3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf3_init( &ccrf3, &cfg );

    log_printf( &logger, "    Hardware reset    \r\n" );
    ccrf3_hw_reset( &ccrf3 );
    Delay_ms( 100 );

    log_printf( &logger, " Set Default Config.  \r\n" );
    ccrf3_default_cfg( &ccrf3 );
    Delay_ms( 100 );

    log_printf( &logger, "  Manual Calibration  \r\n" );
    ccrf3_manual_calibration( &ccrf3 );
    Delay_ms( 100 );

    log_printf( &logger, "    Operation Mode:   \r\n" );
    mode_selected = CCRF3_IDLE_MODE;

    switch ( mode_selected )
    {
        case CCRF3_TX_MODE :
        {
            ccrf3_set_tx_mode( &ccrf3 );
            send_flag = 1;

            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF3_RX_MODE :
        {
            ccrf3_set_rx_mode( &ccrf3 );
            receive_flag = 1;

            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF3_IDLE_MODE :
        {
            log_printf( &logger, "      Idle  Mode      \r\n" );
            break;
        }
    }

    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    mode_selected = CCRF3_TX_MODE;

    switch ( mode_selected )
    {
        case CCRF3_TX_MODE :
        {
            send_flag = 0;
            reading_flag = 0;
            Delay_ms( 200 );
            ccrf3_set_tx_mode( &ccrf3 );
            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF3_RX_MODE :
        {
            receive_flag = 0;
            ccrf3_set_rx_mode( &ccrf3 );
            reading_flag = 1;
            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF3_IDLE_MODE :
        {
            log_printf( &logger, "      Idle  Mode      \r\n" );
            break;
        }
    }

    switch( mode_selected )
    {
        case CCRF3_TX_MODE :
        {
            ccrf3_send_tx_data( &ccrf3, &tx_buffer[ 0 ], 9 );
            length_tx = sizeof( tx_buffer );

            for ( cnt = 0; cnt < length_tx; cnt++ )
            {
                log_printf( &logger, " tx_buffer[ %d ]= %c\r\n", cnt, tx_buffer[ cnt ] );
            }

            Delay_ms( 1000 );
            log_printf( &logger, "----------------------\r\n" );
            break;
        }
        case CCRF3_RX_MODE :
        {
            if ( reading_flag )
            {
                ccrf3_receive_rx_data( &ccrf3, &rx_buffer[ 0 ] );
                length_rx = sizeof( rx_buffer );

                for ( cnt = 0; cnt < length_rx; cnt++ )
                {
                    log_printf( &logger, " rx_buffer[ %d ]= %c\r\n", cnt, rx_buffer[ cnt ] );
                }

                Delay_ms( 1000 );
                log_printf( &logger, "----------------------\r\n" );
            }
            break;
        }
    }
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
