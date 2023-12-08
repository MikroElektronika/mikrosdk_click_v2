/*!
 * @file main.c
 * @brief OOK TX Click Example.
 *
 * # Description
 * This example demonstrates the use of OOK TX click board by sending
 * a predefined message to the receiver.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Sends a predefined message every 3 seconds and displays it on the USB UART.
 *
 * @note
 * The OOK RX click board is a compatible receiver for the OOK TX click.
 * Here are a few steps for troubleshooting if you are experiencing issues running
 * this example:
 *  - Check the MCU clock configuration, use an external oscillator instead of the MCU's
 * internal one for better accuracy on manchester data rate delay.
 *  - Measure the actual data rate on the data line and adjust the OOKTX_MAN_BIT_LEN_US
 * value accordingly.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ooktx.h"

#define OOKTX_PREAMBLE          0x5AA5      /**< Packet preamble word. */
#define OOKTX_MESSAGE           "MIKROE"    /**< Text message to send. */

static ooktx_t ooktx;           /**< OOK TX Click driver object. */
static log_t logger;            /**< Logger object. */

/**
 * @brief OOK TX send data function.
 * @details This function builds and sends a packet of data. 
 * The packet format is as follows (MSB first, manchester IEEE 802.3):
 * OOKTX_TRAINING_BYTES, PREABMLE, LEN, DATA_IN, CRC16 (calculated from whole packet excluding training bytes).
 * @param[in] ctx : Click context object.
 * See #ooktx_t object definition for detailed explanation.
 * @param[in] preamble : Preamble word.
 * @param[in] data_in : Data buffer.
 * @param[in] len : Number of bytes in data buffer.
 * @return None.
 * @note Default manchester bit length is set to 2000us.
 */
static void ooktx_send_data ( ooktx_t *ctx, uint16_t preamble, uint8_t *data_in, uint8_t len );

/** 
 * @brief Manchester encode bits.
 * @details This function encodes a data byte to manchester word (IEEE 802.3).
 * @return Manchester word.
 * @note None.
 */
static uint16_t ooktx_man_encode ( uint8_t data_in );

/** 
 * @brief Reflect bits.
 * @details This function reflects a desired number of bits in data.
 * @return Reflected data.
 * @note None.
 */
static uint16_t ooktx_reflect_bits( uint16_t data_in, uint8_t len );

/** 
 * @brief CRC-16/MAXIM calculation for CRC16 function.
 * @details This function calculates CRC16 with parameteres: 
 * @li @c  Width 16 bit
 * @li @c  Polynomial 0x8005 ( x16 + x15 + x2 + x0 )
 * @li @c  Initialization 0x0000
 * @li @c  Reflect input True
 * @li @c  Reflect output True
 * @li @c  Final Xor 0xFFFF
 * @li @c  Example { 69, 00 } - 0xAFD1
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint16_t ooktx_calculate_crc16 ( uint8_t *data_buf, uint16_t len );

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    ooktx_cfg_t ooktx_cfg;      /**< Click config object. */

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
    ooktx_cfg_setup( &ooktx_cfg );
    OOKTX_MAP_MIKROBUS( ooktx_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ooktx_init( &ooktx, &ooktx_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf ( &logger, " Sending data: %s\r\n\n", ( char * ) OOKTX_MESSAGE );
    ooktx_send_data ( &ooktx, OOKTX_PREAMBLE, OOKTX_MESSAGE, strlen ( OOKTX_MESSAGE ) );
    Delay_ms ( 3000 );
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

static void ooktx_send_data ( ooktx_t *ctx, uint16_t preamble, uint8_t *data_in, uint8_t len )
{
    uint8_t training[ ] = OOKTX_TRAINING_BYTES;
    uint8_t packet_buf[ OOKTX_MAX_DATA_LEN + 5 ] = { 0 };
    uint16_t crc = 0;
    uint16_t man_data = 0;
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;

    packet_buf[ 0 ] = ( uint8_t ) ( ( preamble >> 8 ) & 0xFF );
    packet_buf[ 1 ] = ( uint8_t ) ( preamble & 0xFF );
    packet_buf[ 2 ] = len;
    memcpy ( &packet_buf[ 3 ], data_in, len );
    crc = ooktx_calculate_crc16 ( packet_buf, len + 3 );
    packet_buf[ len + 3 ] = ( uint8_t ) ( ( crc >> 8 ) & 0xFF );
    packet_buf[ len + 4 ] = ( uint8_t ) ( crc & 0xFF );

    ooktx_start ( ctx, OOKTX_CALIB_ENABLE, OOKTX_CFG_ENABLE, OOKTX_CFG_DEFAULT );
    Delay_10ms( );
    // Send training bytes first
    for ( byte_cnt = 0; byte_cnt < sizeof ( training ); byte_cnt++ )
    {
        man_data = ooktx_man_encode ( training[ byte_cnt ] );
        for ( bit_cnt = 0; bit_cnt < 16; bit_cnt++ )
        {
            if ( man_data & OOKTX_MAN_MSB )
            {
                ooktx_set_data_pin ( ctx );
            }
            else
            {
                ooktx_clear_data_pin ( ctx );
            }
            man_data <<= 1;
            Delay_us ( OOKTX_MAN_BIT_LEN_US / 2 );
        }
    }
    // Send the packet bytes
    for ( byte_cnt = 0; byte_cnt < ( len + 5 ); byte_cnt++ )
    {
        man_data = ooktx_man_encode ( packet_buf[ byte_cnt ] );
        for ( bit_cnt = 0; bit_cnt < 16; bit_cnt++ )
        {
            if ( man_data & OOKTX_MAN_MSB )
            {
                ooktx_set_data_pin ( ctx );
            }
            else
            {
                ooktx_clear_data_pin ( ctx );
            }
            man_data <<= 1;
            Delay_us ( OOKTX_MAN_BIT_LEN_US / 2 );
        }
    }
    Delay_10ms( );
    ooktx_stop ( ctx );
}

static uint16_t ooktx_man_encode ( uint8_t data_in )
{
    uint16_t man_data = 0;

    for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
    { 
        man_data <<= 2;
        if ( data_in & ( 0x80 >> bit_cnt ) )
        {
            man_data |= 1;  // 1: low going to a high
        }
        else
        {
            man_data |= 2;  // 0: high going to a low
        }
    }
    return man_data;
}

static uint16_t ooktx_reflect_bits( uint16_t data_in, uint8_t len )
{
    uint16_t data_out = 0;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        data_out |= ( ( data_in >> cnt ) & 1 ) << ( len - cnt - 1 );
    }
    return data_out;
}

static uint16_t ooktx_calculate_crc16( uint8_t *data_buf, uint16_t len )
{
    uint16_t crc16 = 0x0000;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        crc16 ^= ( ooktx_reflect_bits( data_buf[ cnt ], 8 ) << 8 );
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( crc16 & 0x8000 )
            {
                crc16 = ( crc16 << 1 ) ^ 0x8005;
            }
            else
            {
                crc16 <<= 1;
            }
        }
    }
    return ooktx_reflect_bits( crc16, 16 ) ^ 0xFFFF;
}

// ------------------------------------------------------------------------ END
