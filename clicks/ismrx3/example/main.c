/*!
 * @file main.c
 * @brief ISMRX3 Click example
 *
 * # Description
 * This example showcases ability of click board to configure
 * and read incoming rf signal and parses data using data and clock line.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules (SPI, UART), and additional
 * communication pins. Resets device, reads device ID, and sets default
 * configuration that sets ASK modulation and 433.92MHz with 5bps data rate.
 *
 * ## Application Task
 * Reads clock pin and gets samples of data pin state, converts it in manchester
 * data that is stored in a buffer. When it fills out manchester buffer checks if
 * expected preamble data is received. If it is, checks the next byte(it should be
 * received data length). Then parses rest of data and if it's correct shows it on log.
 *
 * @note
 * The expected data that is received is:
 * _PREAMBLE_WORD_(2bytes), _DATA_LENGTH_(1byte), _DATA_(1..255bytes)
 *
 * By default _PREAMBLE_WORD_ is set to be 0xAAAA.
 *
 * @author Luka FIlipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ismrx3.h"
#include "string.h"

static ismrx3_t ismrx3;
static log_t logger;

#define MANCHESTER_BUF_LEN  1500/*<Manchester buffer size*/
#define PREAMBLE_WORD       "01100110011001100110011001100110"/*<Preamble word,
                                                                by default: 0xAAAA*/

uint8_t manchester_buf[ MANCHESTER_BUF_LEN ] = { 0 };/*<Manchester buffer*/

static uint16_t manchester_counter;/*<Manchester data counter*/
static uint8_t last_sample;/*<Last data pin state from clock sample*/
static uint8_t sample;/*<Data pin state from clock sample*/
static uint8_t consecutive;/*<Consecutive number of same data pin state from clock sample*/

/**
 * @brief Parse and convert manchester buffer.
 * @details This function checks if preamble data is received.
 * If received converts manchester data buffer to data and logs result.
 * @param[in] ctx : Click context object.
 * See #ismrx3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Didn't find preamble,
 *         @li @c -1 - Data not complete.
 *
 * See #err_t definition for detailed explanation.
 * @note Expected data to receive:
 * PREAMBLE_WORD(0xAAAA), DATA_LEN(0x6), DATA("MikroE").
 */
static err_t parse_samples( void );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ismrx3_cfg_t ismrx3_cfg;  /**< Click config object. */

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
    ismrx3_cfg_setup( &ismrx3_cfg );
    ISMRX3_MAP_MIKROBUS( ismrx3_cfg, MIKROBUS_1 );
    err_t init_flag  = ismrx3_init( &ismrx3, &ismrx3_cfg );
    if ( init_flag == SPI_MASTER_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    ismrx3_reset( &ismrx3 );

    uint8_t read_data;
    ismrx3_generic_read( &ismrx3, 0x1E, &read_data );
    log_info( &logger, " > ID: 0x%.2X", ( uint16_t )read_data );
    Delay_ms( 500 );

    ismrx3.modulation = ISMRX3_MODULATION_ASK;
    ismrx3.reference_freq = ISMRX3_FREQUENCY_MHZ_433p92;
    ismrx3.data_rate = ISMRX3_DATA_RATE_KBPS_5;
    ismrx3.freq_deviation = ISMRX3_DEVIATION_KHZ_40;

    if ( ISMRX3_ERROR == ismrx3_default_cfg ( &ismrx3 ) )
    {
        log_error( &logger, " Configuration Error. " );
        log_info( &logger, " Please, change device configuration parameters and run program again... " );

        for ( ; ; );
    }

    manchester_counter = 0;
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( ismrx3_get_clk( &ismrx3 ) )
    {
        sample = ismrx3_get_data( &ismrx3 );
        if ( last_sample == sample )
        {
            consecutive++;
        }
        else
        {
            if ( consecutive < 4 )//Single sample
            {
                manchester_buf[ manchester_counter++ ] = last_sample + 48;//Convert to ascii 1/0
            }
            else if ( consecutive < 6 )//Two samples
            {
                manchester_buf[ manchester_counter++ ] = last_sample + 48;//Convert to ascii 1/0
                manchester_buf[ manchester_counter++ ] = last_sample + 48;//Convert to ascii 1/0
            }
            consecutive = 1;
            last_sample = sample;
        }

        while ( ismrx3_get_clk( &ismrx3 ) );
    }

    if ( manchester_counter >= MANCHESTER_BUF_LEN - 1 )
    {
        parse_samples(  );
        manchester_counter = 0;
    }
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

static err_t parse_samples( void )
{
    //check preamble data
    char * __generic_ptr manchester_data = strstr( manchester_buf, ( char * )PREAMBLE_WORD );
    if ( manchester_data )
    {
        manchester_data += strlen( ( char * )PREAMBLE_WORD );

        if ( ( strlen( manchester_data ) + 16 ) > strlen( manchester_buf ) )
        {
            return ISMRX3_ERROR_BUF_LEN;
        }

        //get data len
        uint8_t data_len = 0;
        uint8_t offset;
        for ( offset = 1; offset < 16; offset += 2 )
        {
            data_len <<= 1;
            data_len |= ( *( manchester_data + offset )- 48 );
        }

        manchester_data += offset - 1;
        if ( ( strlen( manchester_data ) + ( 16 * data_len ) ) > strlen( manchester_buf ) )
        {
            return ISMRX3_ERROR_BUF_LEN;//Not whole data captured in sample
        }

        log_printf( &logger, "> Length: %d\r\n", ( uint16_t )data_len );

        //get data
        log_printf( &logger, "> Data: " );
        for ( uint8_t data_bytes = 0; data_bytes < data_len; data_bytes++ )
        {
            uint8_t data_byte;
            for ( offset = 1; offset < 16; offset += 2 )
            {
                data_byte <<= 1;
                data_byte |= ( *( manchester_data + offset )- 48 );
            }
            log_printf( &logger, "%c", data_byte );
            manchester_data += offset - 1;
        }
        log_printf( &logger, "\r\n" );
        return ISMRX3_OK;
    }
    return ISMRX3_ERROR;
}

// ------------------------------------------------------------------------ END
