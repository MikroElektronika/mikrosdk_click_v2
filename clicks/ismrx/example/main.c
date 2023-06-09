/*!
 * @file main.c
 * @brief ISMRX Click example
 *
 * # Description
 * This application shows capability of ISM RX Click board.
 * It sets default configuration, and collects and processes
 * data from signal that received from ISM TX Click board.
 * It can collect and process data from 2 type of the signal
 * modulation( FSK and ASK ).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of log and communication, set's signal
 * modulation(FSK/ASK), recive mode(continuous/discontinuous),
 * default configuration for selected modulation, and
 * reinitializes device for receiving mode.
 *
 * ## Application Task
 * Collects samples of data from data line(MISO) when buffer
 * is full converts samples to manchester encoded data,
 * and checks for preamble(sync) data. If data is valid
 * decodes data and converts bits to valid data and logs
 * result of received decoded data.
 *
 * ## Additional Function
 * - static void clear_buffers ( void )
 * - static void wait_for_data ( void )
 * - static void man_to_hex_array ( void )
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ismrx.h"

static ismrx_t ismrx;
static log_t logger;

#define MAN_BUF_SIZE                    300
#define DATA_BUF_SIZE                   50

#define PREAMBLE_STRING                 "0101010101010101"

static uint8_t manchester_buf[ MAN_BUF_SIZE ];
static uint8_t data_buf[ DATA_BUF_SIZE ];

static uint16_t manchester_cnt          = 0;
static uint16_t data_cnt                = 0;

/**
 * @brief Clears app buffers.
 * @details This function clears application buffer and resets counters.
 * @return Nothing.
 */
static void clear_buffers ( void );

/**
 * @brief Waits for data start sequence.
 * @details This function waits for data start sequence.
 * @return Nothing.
 */
static void wait_for_data ( void );

/**
 * @brief Converts manchester_buf to data_buf hex array.
 * @details This function converts manchester_buf to data_buf hex array.
 * @return Nothing.
 */
static void man_to_hex_array ( void );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ismrx_cfg_t ismrx_cfg;  /**< Click config object. */

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
    ismrx_cfg_setup( &ismrx_cfg );
    ISMRX_MAP_MIKROBUS( ismrx_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ismrx_init( &ismrx, &ismrx_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    Delay_ms( 1000 );

    ismrx_master_reset( &ismrx );

    ismrx.modulation = ISMRX_MODULATION_FSK;
    ismrx.receive_mode = ISMRX_RECEIVE_MODE_RX;

    if ( ismrx_default_cfg ( &ismrx ) < 0 )
    {
        log_error( &logger, " Default configuration error. " );
        log_info( &logger, " Please, select signal modulation and/or receive mode... " );
        for ( ; ; );
    }

    if ( ismrx_task_init( &ismrx, &ismrx_cfg ) < 0 )
    {
        log_error( &logger, " Application Task Error. " );
    }

    log_info( &logger, " Application Task " );

    if ( ISMRX_RECEIVE_MODE_DRX == ismrx.receive_mode )
    {
       ismrx_start_drx( &ismrx );
    }
}

void application_task ( void )
{
    uint8_t transition = 0;
    
    clear_buffers ( );
    wait_for_data ( );
    Delay_50us ( );

    while ( manchester_cnt < MAN_BUF_SIZE )
    {
        transition = ismrx_get_data ( &ismrx );
        while ( transition == ismrx_get_data ( &ismrx ) );
        
        if ( transition )
        {
            manchester_buf[ manchester_cnt++ ] = '1';
            manchester_buf[ manchester_cnt++ ] = '0';
        }
        else
        {
            manchester_buf[ manchester_cnt++ ] = '0';
            manchester_buf[ manchester_cnt++ ] = '1';
        }
        Delay_500us ( );
        Delay_50us ( );
    }
    
    man_to_hex_array ( );
    
    for ( uint16_t byte_cnt = 0; byte_cnt < data_cnt; byte_cnt++ )
    {
        log_printf( &logger, "%.2X ", ( uint16_t ) data_buf[ byte_cnt ] );
    }

    if ( data_cnt )
    {
        log_printf( &logger, "\r\n%s\r\n", &data_buf[ 2 ] );
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

static void clear_buffers ( void )
{
    memset( manchester_buf, 0, MAN_BUF_SIZE );
    manchester_cnt = 0;
    memset( data_buf, 0, DATA_BUF_SIZE );
    data_cnt = 0;
}

static void wait_for_data ( void )
{
    uint16_t timeout_cnt = 0;
    while ( timeout_cnt < 30 )
    {
        if ( ismrx_get_data ( &ismrx ) )
        {
            timeout_cnt++;
        }
        else
        {
            timeout_cnt = 0;
        }
        Delay_50us ( );
    }
    while ( ismrx_get_data ( &ismrx ) );
}

static void man_to_hex_array ( void )
{
    uint16_t num_bytes_left = 0;
    uint16_t byte_cnt = 0;
    uint16_t bit_cnt = 0;
    uint8_t * __generic_ptr cmd_start;
    cmd_start = strstr( manchester_buf, PREAMBLE_STRING );
    memset ( data_buf, 0, sizeof ( data_buf ) );
    data_cnt = 0;
    if ( cmd_start )
    {
        num_bytes_left = ( manchester_cnt - ( cmd_start - manchester_buf ) );

        for ( byte_cnt = 0; ( ( byte_cnt < 2 ) && ( byte_cnt < DATA_BUF_SIZE ) ); byte_cnt++ )
        {
            for ( bit_cnt = 0; ( ( bit_cnt < 8 ) && ( num_bytes_left >= 2 ) ); bit_cnt++ )
            {
                if ( ( '0' == cmd_start[ byte_cnt * 16 + bit_cnt * 2 ] ) && 
                     ( '1' == cmd_start[ byte_cnt * 16 + bit_cnt * 2 + 1 ] ) )
                {
                    data_buf[ byte_cnt ] |= ( 1 << bit_cnt );
                }
                num_bytes_left -= 2;
            }
            data_cnt++;
        }
        
        for ( byte_cnt = 0; ( ( byte_cnt < data_buf[ 1 ] ) && ( ( byte_cnt + 2 ) < DATA_BUF_SIZE ) ); byte_cnt++ )
        {
            for ( bit_cnt = 0; ( ( bit_cnt < 8 ) && ( num_bytes_left >= 2 ) ); bit_cnt++ )
            {
                if ( ( '0' == cmd_start[ ( byte_cnt + 2 ) * 16 + bit_cnt * 2 ] ) && 
                     ( '1' == cmd_start[ ( byte_cnt + 2 ) * 16 + bit_cnt * 2 + 1 ] ) )
                {
                    data_buf[ byte_cnt + 2 ] |= ( 1 << bit_cnt );
                }
                num_bytes_left -= 2;
            }
            data_cnt++;
        }
    }
}

// ------------------------------------------------------------------------ END
