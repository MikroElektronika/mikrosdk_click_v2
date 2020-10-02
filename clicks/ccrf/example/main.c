/*!
 * \file 
 * \brief ccRf Click example
 * 
 * # Description
 * ccRF click communicates with the target microcontroller via mikroBUS SPI, RST and PWM lines.
 * It features Low-Power RF transceiver as well as PCB trace antenna. Maximum device range is 
 * up to 20 meters in open space.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - SPI,
 * hardware reset chip, sets default configuration, sets operation mode, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of ccRF click board.
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
#include "ccrf.h"

// ------------------------------------------------------------------ VARIABLES

static ccrf_t ccrf;
static log_t logger;

static uint8_t mode_selected;
static uint8_t tx_buffer[ 8 ] = { 12, 13, 14, 15, 22, 23, 24, 25 };
static uint8_t rx_buffer[ 8 ];

static uint8_t length_rx;
static uint8_t length_tx;
static uint8_t cnt;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ccrf_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ccrf_cfg_setup( &cfg );
    CCRF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ccrf_init( &ccrf, &cfg );

    log_printf( &logger, "    Hardware reset    \r\n" );
    ccrf_hw_reset( &ccrf );
    Delay_ms( 100 );
    
    ccrf_sw_reset( &ccrf );
    Delay_ms( 100 );
    
    log_printf( &logger, " Set Default Config.  \r\n" );
    ccrf_default_cfg( &ccrf );
    Delay_ms( 100 );
    ccrf_write_byte( &ccrf, CCRF_PATABLE, 0xFE );
    Delay_ms( 100 );
    
    log_printf( &logger, "    Operation Mode:   \r\n" );
    mode_selected = CCRF_IDLE_MODE;

    switch ( mode_selected )
    {
        case CCRF_TX_MODE :
        {
            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF_RX_MODE :
        {
            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF_IDLE_MODE :
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
    mode_selected = CCRF_RX_MODE;

    switch ( mode_selected )
    {
        case CCRF_TX_MODE :
        {
            log_printf( &logger, "       TX  Mode       \r\n" );
            break;
        }
        case CCRF_RX_MODE :
        {
            log_printf( &logger, "       RX  Mode       \r\n" );
            break;
        }
        case CCRF_IDLE_MODE :
        {
            log_printf( &logger, "      Idle  Mode      \r\n" );
            break;
        }
    }

    switch( mode_selected )
    {
        case CCRF_TX_MODE :
        {
            length_tx = sizeof( tx_buffer );

            ccrf_transmit_packet( &ccrf, &tx_buffer[ 0 ], length_tx );

            Delay_ms( 1000 );
            break;
        }
        case CCRF_RX_MODE :
        {
            length_rx = sizeof( rx_buffer );

            if ( ccrf_receive_packet( &ccrf, &rx_buffer[ 0 ], &length_rx ) )
            {
                for ( cnt = 0; cnt < length_rx; cnt++ )
                {
                    log_printf( &logger, " rx_buffer[ %d ] = %c \r\n",  cnt, rx_buffer[ cnt ] );
                }

                log_printf( &logger, "----------------------\r\n" );
                Delay_ms( 1000 );
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
