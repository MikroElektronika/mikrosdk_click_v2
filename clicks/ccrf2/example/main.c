/*!
 * \file 
 * \brief ccRf2 Click example
 * 
 * # Description
 * This click carries CC1120, single-chip radio transceiver. Designed mainly for the ISM 
 * (Industrial, Scientific, and Medical) and SRD (Short Range Device) frequency bands at 
 * 820–960 MHz, CC1120 provides extensive hardware support for packet handling, data buffering, 
 * burst transmissions, clear channel assessment, link quality indication, and Wake-On-Radio. 
 * It also has exceptional receiver sensibility. ccRF2 click communicates with the target board 
 * through SPI (MISO, MOSI, CSK), and AN, RST, CS, PWM and INT lines.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - SPI, hardware reset chip, sets default configuration, 
 * sets manual calibration, sets operation mode, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of ccRF 2 click board.
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
#include "ccrf2.h"

// ------------------------------------------------------------------ VARIABLES

static ccrf2_t ccrf2;
static log_t logger;

static uint8_t mode_selected;
static uint8_t tx_buffer[ 8 ] = { 12, 13, 14, 15, 22, 23, 24, 25 };
static uint8_t rx_buffer[ 8 ];

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
    ccrf2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ccrf2_cfg_setup( &cfg );
    CCRF2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf2_init( &ccrf2, &cfg );
    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "    Hardware reset    \r\n" );
    ccrf2_hw_reset( &ccrf2 );
    Delay_ms( 100 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, " Set Default Config.  \r\n" );
    ccrf2_default_cfg( &ccrf2 );
    Delay_ms( 100 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "  Manual Calibration  \r\n" );
    ccrf2_manual_calibration( &ccrf2 );
    Delay_ms( 100 );

    log_printf( &logger, "----------------------\r\n" );
    log_printf( &logger, "    Operation Mode:   \r\n" );
    mode_selected = CCRF2_IDLE_MODE;

    switch ( mode_selected )
    {
        case CCRF2_TX_MODE :
        {
            ccrf2_set_tx_mode( &ccrf2 );
            send_flag = 1;

            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF2_RX_MODE :
        {
            ccrf2_set_rx_mode( &ccrf2 );
            receive_flag = 1;

            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF2_IDLE_MODE :
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
    mode_selected = CCRF2_TX_MODE;

    switch ( mode_selected )
    {
        case CCRF2_TX_MODE :
        {
            send_flag = 0;
            reading_flag = 0;
            Delay_ms( 200 );
            ccrf2_set_tx_mode( &ccrf2 );
            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF2_RX_MODE :
        {
            receive_flag = 0;
            ccrf2_set_rx_mode( &ccrf2 );
            reading_flag = 1;
            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF2_IDLE_MODE :
        {
            log_printf( &logger, "      Idle  Mode      \r\n" );
            break;
        }
    }

    switch ( mode_selected )
    {
        case CCRF2_TX_MODE :
        {
            ccrf2_send_tx_data( &ccrf2, &tx_buffer[ 0 ], 9 );
            length_tx = sizeof( tx_buffer );

            for ( cnt = 0; cnt < length_tx; cnt++ )
            {
                log_printf( &logger, " tx_buffer[ %d ]= %c\r\n", cnt, tx_buffer[ cnt ] );
            }

            Delay_ms( 1000 );
            log_printf( &logger, "----------------------\r\n" );
            break;
        }
        case CCRF2_RX_MODE :
        {
            if ( reading_flag )
            {
                ccrf2_receive_rx_data( &ccrf2, &rx_buffer[ 0 ] );
                length_rx = sizeof( rx_buffer );

                for ( cnt = 0; cnt < length_rx; cnt++ )
                {
                    log_printf( &logger, " rx_buffer[ %d ]= %d\r\n", cnt, rx_buffer[ cnt ] );
                    Delay_ms( 200 );
                }

                Delay_ms( 1000 );
                log_printf( &logger, "----------------------\r\n" );
                Delay_ms( 200 );
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
