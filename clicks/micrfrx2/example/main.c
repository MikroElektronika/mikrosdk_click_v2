/*!
 * @file main.c
 * @brief MICRF RX 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of MICRF RX 2 click board by reading and parsing
 * packet messages received from the transmitter.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the device. 
 *
 * ## Application Task
 * Waits for a data ready indication, then reads all packet data, verifies the CRC
 * bytes in a packet, and displays its data as well as the RSSI value on the USB UART.
 *
 * @note
 * The OOK TX click board is a compatible transmitter for the MICRF RX 2 click.
 * Here are a few steps for troubleshooting if you are experiencing issues running
 * this example:
 *  - Check the MCU clock configuration, use an external oscillator instead of the MCU's
 * internal one for better accuracy on manchester data rate delay.
 *  - Measure the actual data rate on the data line and adjust the MICRFRX2_MAN_BIT_LEN_US
 * value accordingly.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "micrfrx2.h"

#define MICRFRX2_PREAMBLE       0x5AA5  /**< Packet preamble word. */

static micrfrx2_t micrfrx2;     /**< MICRF RX 2 Click driver object. */
static log_t logger;            /**< Logger object. */
static uint8_t packet_buf[ MICRFRX2_MAX_DATA_LEN + 5 ] = { 0 };  /**< Packet buffer. */

/** 
 * @brief MICRF RX 2 wait ready function.
 * @details This function waits for all training bytes to arrive which indicates data ready.
 * @param[in] ctx : Click context object.
 * See #micrfrx2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void micrfrx2_wait_ready ( micrfrx2_t *ctx );

/** 
 * @brief MICRF RX 2 read packet function.
 * @details This function reads data packet and stores it in a packet_buf only if
 * the MICRFRX2_PREAMBLE bytes are received successfully.
 * @param[in] ctx : Click context object.
 * See #micrfrx2_t object definition for detailed explanation.
 * @return Number of data bytes stored in a packet_buf.
 * @note The expected packet format is as follows (MSB first, manchester IEEE 802.3):
 * TRAINING_BYTES (at least two bytes of 0xAA), PREABMLE, LEN, DATA_IN, CRC16 (calculated
 * from whole packet excluding training bytes). Training bytes are excluded from packet_buf.
 * This function must be called immediately after calling micrfrx2_wait_ready.
 */
static uint8_t micrfrx2_read_packet ( micrfrx2_t *ctx );

/** 
 * @brief Reflect bits.
 * @details This function reflects a desired number of bits in data.
 * @return Reflected data.
 * @note None.
 */
static uint16_t micrfrx2_reflect_bits( uint16_t data_in, uint8_t len );

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
static uint16_t micrfrx2_calculate_crc16 ( uint8_t *data_buf, uint16_t len );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    micrfrx2_cfg_t micrfrx2_cfg;  /**< Click config object. */

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
    micrfrx2_cfg_setup( &micrfrx2_cfg );
    MICRFRX2_MAP_MIKROBUS( micrfrx2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == micrfrx2_init( &micrfrx2, &micrfrx2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    micrfrx2_enable_device ( &micrfrx2 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static float rssi_v = 0;
    static uint8_t packet_len = 0;
    static uint8_t msg_cnt = 0;
    static uint16_t crc = 0;

    log_printf( &logger, "\r\n Waiting for data ready...\r\n" );
    micrfrx2_wait_ready ( &micrfrx2 );
    packet_len = micrfrx2_read_packet ( &micrfrx2 );
    if ( packet_len )
    {
        micrfrx2_read_rssi_voltage ( &micrfrx2, &rssi_v );
        crc = ( ( uint16_t ) packet_buf[ packet_len - 2 ] << 8 ) | packet_buf[ packet_len - 1 ];
        if ( crc == micrfrx2_calculate_crc16 ( packet_buf, packet_len - 2 ) )
        {
            log_printf( &logger, " Received message: " );
            for ( msg_cnt = 0; msg_cnt < packet_buf[ 2 ]; msg_cnt++ )
            {
                log_printf( &logger, "%c", ( uint16_t ) packet_buf[ msg_cnt + 3 ] );
            }
            log_printf( &logger, "\r\n RSSI: %.1f dBm\r\n", MICRFRX2_RSSI_V_TO_DBM ( rssi_v ) );
        }
    }
    Delay_ms ( 100 );
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

static void micrfrx2_wait_ready ( micrfrx2_t *ctx )
{
    uint16_t time_cnt = 0;
    uint16_t training_high_cnt = 0;
    uint16_t training_low_cnt = 0;
    // Loop until at least two 0xAA bytes of training data is detected
    for ( ; ; )
    {
        // Measure time in steps of MICRFRX2_MAN_BIT_LEN_US / 40 for high signal
        for ( time_cnt = 0; micrfrx2_get_data_pin ( ctx ); time_cnt++ )
        {
            Delay_us ( MICRFRX2_MAN_BIT_LEN_US / 40 );
        }
        if ( time_cnt > 30 )
        {
            // Increment training_high_cnt if signal width is at least 75% of MICRFRX2_MAN_BIT_LEN_US
            training_high_cnt++;
        }
        else
        {
            // Reset counters if any invalid signal is detected
            training_high_cnt = 0;
            training_low_cnt = 0;
        }

        // Measure time in steps of MICRFRX2_MAN_BIT_LEN_US / 40 for low signal
        for ( time_cnt = 0; ( training_high_cnt > 0 ) && !micrfrx2_get_data_pin ( ctx ); time_cnt++ )
        {
            Delay_us ( MICRFRX2_MAN_BIT_LEN_US / 40 );
        }
        if ( time_cnt > 30 )
        {
            // Increment training_low_cnt if signal width is at least 75% of MICRFRX2_MAN_BIT_LEN_US
            training_low_cnt++;
        }
        else if ( ( training_high_cnt >= 8 ) && ( training_high_cnt == ( training_low_cnt + 1 ) ) )
        {
            // At least two 0xAA bytes are detected ending with shorter low signal, so break the loop here.
            // Waiting for 12.5% of MICRFRX2_MAN_BIT_LEN_US as an offset for packet reading.
            Delay_us ( MICRFRX2_MAN_BIT_LEN_US / 8 );
            break;
        }
    }
}

static uint8_t micrfrx2_read_packet ( micrfrx2_t *ctx )
{
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    // Loop until all data bytes are received or a bad PREAMBLE word is detected
    for ( ; ; )
    {
        if ( !micrfrx2_get_data_pin ( ctx ) )
        {
            // Store data in packet_buf in manchester IEEE 802.3 format, MSB first
            packet_buf[ byte_cnt ] |= ( 0x80 >> bit_cnt );
        }
        
        if ( 8 == ++bit_cnt )
        {
            // Reset bit counter and increment byte counter if 8 bits are received
            bit_cnt = 0;
            byte_cnt++;
        }

        if ( 2 == byte_cnt )
        {
            // Two bytes are received, check PREAMBLE word
            if ( MICRFRX2_PREAMBLE != ( ( ( uint16_t ) packet_buf[ 0 ] << 8 ) | packet_buf[ 1 ] ) )
            {
                byte_cnt = 0;
                break;
            }
        }
        else if ( ( packet_buf[ 2 ] + 5 ) == byte_cnt )
        {
            // Break the loop if all packet data are received (PREAMBLE + DATA_LEN + DATA + CRC)
            break;
        }

        // Move to the next manchester clock high state by delaying for MICRFRX2_MAN_BIT_LEN_US
        Delay_us ( MICRFRX2_MAN_BIT_LEN_US );
    }
    return byte_cnt;
}

static uint16_t micrfrx2_reflect_bits( uint16_t data_in, uint8_t len )
{
    uint16_t data_out = 0;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        data_out |= ( ( data_in >> cnt ) & 1 ) << ( len - cnt - 1 );
    }
    return data_out;
}

static uint16_t micrfrx2_calculate_crc16( uint8_t *data_buf, uint16_t len )
{
    uint16_t crc16 = 0x0000;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        crc16 ^= ( micrfrx2_reflect_bits( data_buf[ cnt ], 8 ) << 8 );
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
    return micrfrx2_reflect_bits( crc16, 16 ) ^ 0xFFFF;
}

// ------------------------------------------------------------------------ END
