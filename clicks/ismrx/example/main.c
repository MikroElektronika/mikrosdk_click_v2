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
 * decodes data and converts bit's to valid data and logs 
 * result of received decoded data.
 * 
 * ## Additional Function
 * - static void clear_buffers ( void )
 * - static void proces_samples ( void )
 * - static void convert_to_manchester ( uint8_t same_data, uint8_t data_coll )
 * - static err_t check_preamble ( void )
 * - static void convert_to_bits ( void )
 * - static static err_t convert_to_data ( void )
 *
 * *note:*
 * Macros for checking sample data and delay in application_task
 * can be prone to change depending of speed of MCU. 
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ismrx.h"

static ismrx_t ismrx;
static log_t logger;

//minimum samples for single valid manchester data
#define SINGLE_MAN_MIN                  2
//maximum samples for single valid manchester data
#define SINGLE_MAN_MAX                  4
//maximum samples for double valid manchester data
#define DUAL_MAN_MAX                    7

#define BUFFER_SIZE                     800
#define MAN_BUF_SIZE                    800
#define BIT_BUF_SIZE                    400
#define DATA_BUF_SIZE                   50

#define ASK_PREAMBLE_STRING             "0101010101010101"
#define FSK_PREAMBLE_STRING             "010101010101"

static uint8_t buffer[ BUFFER_SIZE ];
static uint8_t manchester_buf[ MAN_BUF_SIZE ];
static uint8_t bit_buf[ BIT_BUF_SIZE ];
static uint8_t data_buf[ DATA_BUF_SIZE ];

static uint16_t buffer_cnt              = 0;
static uint16_t manchester_cnt          = 0;
static uint16_t bit_cnt                 = 0;
static uint16_t data_cnt                = 0;
static uint16_t manchester_start_preamble;

/**
 * @brief Clears app buffers.
 * @details This function clears application buffer and resets counters.
 * @return Nothing.
 */
static void clear_buffers ( void );

/**
 * @brief Proceses collected data.
 * @details Function goes throught collected samples and converts 
 * it to manchester data. Then seraches for preamble(sync) byte and
 * if it received it converts manchester encoded data to bits and
 * then that converts to bytes. Checks if data is correct and then
 * logs bytes from second to the byte value of the first converted byte.
 * @return Nothing.
 */
static void proces_samples ( void );

/**
 * @brief Adds element to manchester buffer.
 * @details This function adds @b data_coll element to manchester buffer
 * if @b same_data parameter is in range of valid data.
 * @param[in] same_data : Number of consecutive occurrence of the state.
 * @param[in] data_coll : Collected consecutive sample.
 * @return Nothing.
 */
static void convert_to_manchester ( uint8_t same_data, uint8_t data_coll );

/**
 * @brief Checks for preamble(sync) data.
 * @details This function searches manchester buffer for 
 *          preamble(sync) data and returns status.
 * @return @li @c  0 - Preamble data found,
 *         @li @c -1 - Preamble data not found.
 * @note Preamble data differs relative to signal modulation.
 */
static err_t check_preamble ( void );

/**
 * @brief Converts manchester buffer to bit buffer.
 * @details This function converts manchester encoded 
 *          buffer to bit buffer from preamble data.
 * @return Nothing.
 */
static void convert_to_bits ( void );

/**
 * @brief Converts bit buffer to data buffer.
 * @details This function converts bit buffer to data buffer.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note First byte will be number of bytes that ISM TX click transmissed.
 */
static err_t convert_to_data ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ismrx_cfg_t ismrx_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ismrx_cfg_setup( &ismrx_cfg );
    ISMRX_MAP_MIKROBUS( ismrx_cfg, MIKROBUS_1 );
    err_t init_flag  = ismrx_init( &ismrx, &ismrx_cfg );
    if ( init_flag == SPI_MASTER_ERROR )
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
    if ( ismrx_get_data( &ismrx ) )
    {
        buffer[ buffer_cnt ] = '1';
    }
    else
    {
        buffer[ buffer_cnt ] = '0';
    }

    buffer_cnt++;
    
    //Delay for sample ratio to be effective
    Delay_us( 60 );

    if ( buffer_cnt > BUFFER_SIZE )
    {        
        proces_samples();
        clear_buffers();
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
    memset( buffer, 0, BUFFER_SIZE );
    buffer_cnt = 0;
    memset( manchester_buf, 0, MAN_BUF_SIZE );
    manchester_cnt = 0;
    memset( bit_buf, 0, BIT_BUF_SIZE );
    bit_cnt = 0;
    memset( data_buf, 0, DATA_BUF_SIZE );
    data_cnt = 0;
}

static void proces_samples ( void )
{
    uint16_t i;
    uint8_t last_byte = buffer[ 0 ];
    uint8_t same_data_cnt = 1;

    for ( i = 1; i < buffer_cnt; i++ )
    {
        if ( last_byte == buffer[ i ] )
        {
            same_data_cnt++;
        }
        else
        {
            convert_to_manchester ( same_data_cnt, last_byte );
            last_byte = buffer[ i ];
            same_data_cnt = 1;
        }
        if ( manchester_cnt > MAN_BUF_SIZE )
        {
            break;
        }
    }
    
    if ( !check_preamble(  ) )
    {
        convert_to_bits(  );
        
        if ( !convert_to_data() )
        {
            for ( i = 1; i < data_buf[ 0 ] + 1; i++ )
            {
                log_printf( &logger, "%c", data_buf[ i ] );
            }
            log_printf( &logger, "\r\n" );
        }
    }
}

static void convert_to_manchester ( uint8_t same_data, uint8_t data_coll )
{
    if ( ( SINGLE_MAN_MIN <= same_data ) && ( SINGLE_MAN_MAX >= same_data ) )
    {
        manchester_buf[ manchester_cnt ] = data_coll;
        manchester_cnt++;
    }
    else if ( DUAL_MAN_MAX >= same_data )
    {
        manchester_buf[ manchester_cnt ] = data_coll;
        manchester_buf[ manchester_cnt + 1 ] = data_coll;
        manchester_cnt += 2;
    }
}

static err_t check_preamble ( )
{
    char preamble[ 20 ] = { 0 };
    char * __generic cmd_start;

    if ( ismrx.modulation == ISMRX_MODULATION_FSK )
    {
        strcpy( preamble, FSK_PREAMBLE_STRING );
    }
    else
    {
        strcpy( preamble, ASK_PREAMBLE_STRING );
    }

    cmd_start = strstr( manchester_buf, preamble );

    if ( cmd_start != 0 )
    {
        manchester_start_preamble = cmd_start - &manchester_buf[ 0 ];
        manchester_start_preamble += strlen( preamble );
        return ISMRX_OK;
    }
    else
    {
       return ISMRX_ERROR;        
    }
} 

static void convert_to_bits ( void )
{
    bit_cnt = 0;

    for ( uint16_t i = manchester_start_preamble; i < manchester_cnt; i += 2 )
    {
        if ( manchester_buf[ i ] == '0' )
        {
            bit_buf[ bit_cnt ] = 1;
        }

        if (  manchester_buf[ i ] == '1' )
        {
            bit_buf[ bit_cnt ] = 0;
        }
        bit_cnt++;
    }
}

static err_t convert_to_data ( void )
{
    data_cnt = 0;

    for ( uint16_t i = 0; i < bit_cnt; i++ )
    {
        if ( ( i != 0 ) && ( ( i % 8 ) == 0 ) )
        {
            data_cnt++;
        }
        data_buf[ data_cnt ] <<= 1;
        if ( bit_buf[ i ] )
        {
            data_buf[ data_cnt ] |= 1;
        }
    }
    
    if ( data_cnt < data_buf[ 0 ] )
    {
       return ISMRX_ERROR;
    }
    else
    {
        return ISMRX_OK;
    }
}

// ------------------------------------------------------------------------ END
