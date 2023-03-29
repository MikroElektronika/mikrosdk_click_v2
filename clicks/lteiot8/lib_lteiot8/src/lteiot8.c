/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file lteiot8.c
 * @brief LTE IoT 8 Click Driver.
 */

#include "lteiot8.h"
#include "conversions.h"

/**
 * @brief PDU macros.
 * @details Predefined PDU macros for driver use.
 */
#define BITMASK_7BITS                       0x7F
#define BITMASK_8BITS                       0xFF
#define BITMASK_HIGH_4BITS                  0xF0
#define BITMASK_LOW_4BITS                   0x0F
#define TYPE_OF_ADDRESS_INTERNATIONAL_PHONE 0x91
#define TYPE_OF_ADDRESS_NATIONAL_SUBSCRIBER 0xC8
#define SMS_DELIVER_ONE_MESSAGE             0x04
#define SMS_DELIVER_ONE_MESSAGE             0x04
#define SMS_SUBMIT                          0x11
#define SMS_MAX_7BIT_TEXT_LENGTH            160
#define SMS_MAX_PDU_LENGTH                  256

/**
 * @brief Encode message for PDU mode.
 * @details Encode message for PDU mode and outputs 
 * the encoded message into output buffer.
 * @param[in] service_center_number : Service center of devices SIM.
 * @param[in] phone_number : Phone number to send message to.
 * @param[in] sms_text : SMS text.
 * @param[out] output_buffer : Output PDU encoded message.
 * @param[in] buffer_size : Output buffer size.
 * @return @li @c  >=0 - Length of the SMS encoded message,
 *         @li @c   <0 - Error.
 */
static int16_t pdu_encode( char *service_center_number, char *phone_number, char *sms_text,
                           uint8_t *output_buffer, uint16_t buffer_size );

/**
 * @brief Swap decimal digits of a number.
 * @details Swap decimal digits of a number (e.g. 12 -> 21).
 * @param[in] x : Decimal number to swap digits.
 * @return Swapped decimal number.
 */
static uint8_t swap_decimal_nibble( uint8_t x );

/**
 * @brief Encode text content for PDU mode.
 * @details Encode text content for PDU mode and 
 * outputs the encoded message into output buffer.
 * @param[in] sms_text : Sms text content to encode
 * @param[in] sms_text_length : Length of the text message.
 * @param[out] output_buffer : Output PDU encoded text message.
 * @param[in] buffer_size : Output buffer size.
 * @return @li @c  >=0 - Length of the enccoded text messages,
 *         @li @c   <0 - Error.
 */
static int16_t encode_pdu_message( char *sms_text, int16_t sms_text_length, 
                                   uint8_t *output_buffer, uint16_t buffer_size );

/**
 * @brief Encode phone number for PDU mode.
 * @details Encode phone number for PDU mode and 
 * outputs the encoded message into output buffer.
 * @param[in] phone_number : Phone number to send message to.
 * @param[out] output_buffer : Output PDU encoded message.
 * @param[in] buffer_size : Output buffer size.
 * @return @li @c  >=0 - Length of the SMS encoded message,
 *         @li @c   <0 - Error.
 */
static int16_t encode_phone_number ( char *phone_number, uint8_t *output_buffer, uint16_t buffer_size );

/**
 * @brief LTE IoT 8 str cut chr function.
 * @details This function removes all selected characters from string str,
 * and returns it to the same str without those characters.
 * @param str Address of string.
 * @param chr Character to cut.
 */
static void lteiot8_str_cut_chr ( char *str, char chr );

void lteiot8_cfg_setup ( lteiot8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rng    = HAL_PIN_NC;
    cfg->rst    = HAL_PIN_NC;
    cfg->cts    = HAL_PIN_NC;
    cfg->pst    = HAL_PIN_NC;
    cfg->rts    = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t lteiot8_init ( lteiot8_t *ctx, lteiot8_cfg_t *cfg ) 
{
    uart_config_t uart_cfg;

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );

    // Input pins
    digital_in_init( &ctx->rng, cfg->rng );
    digital_in_init( &ctx->pst, cfg->pst );
    digital_in_init( &ctx->rts, cfg->rts );

    return UART_SUCCESS;
}

err_t lteiot8_default_cfg ( lteiot8_t *ctx ) 
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
    
    
    return LTEIOT8_OK;
}

err_t lteiot8_generic_write ( lteiot8_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t lteiot8_generic_read ( lteiot8_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void lteiot8_send_cmd ( lteiot8_t *ctx, char *cmd )
{
    char cr_lf[ 3 ] = { 13, 0 };
    
    while ( *cmd != 0 )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    
    uart_write( &ctx->uart, cr_lf, 1 );
}

void lteiot8_send_cmd_with_parameter ( lteiot8_t *ctx, char *at_cmd_buf, char *param_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    lteiot8_send_cmd( ctx, final_cmd );
}

void lteiot8_send_cmd_check ( lteiot8_t *ctx, char *at_cmd_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    lteiot8_send_cmd( ctx, final_cmd );
}

void lteiot8_send_cmd_syntax_check ( lteiot8_t *ctx, char *at_cmd_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 3 ] = { '=' , '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    lteiot8_send_cmd( ctx, final_cmd );
}

void lteiot8_set_sim_apn ( lteiot8_t *ctx, char *sim_apn )
{
    char final_cmd[ 50 ] = "1,\"IP\",\"";
    char end_cmd[ 3 ] = "\"";
    
    strcat( final_cmd, sim_apn );
    strcat( final_cmd, end_cmd );
    
    lteiot8_send_cmd_with_parameter( ctx, LTEIOT8_CMD_CGDCONT, final_cmd );
}

void lteiot8_send_text_message ( lteiot8_t *ctx, char *phone_number, char *message_content )
{
    char text[ 200 ] = { 0 };
    char cmd_start[] = "AT+CMGS=\"";
    char cmd_end[] = "\"\r";
    char txt_end[] = "\032";
    
    strcpy( text, cmd_start );
    strcat( text, phone_number );
    strcat( text, cmd_end );
    
    strcat( text, message_content );
    strcat( text, txt_end );
    lteiot8_send_cmd( ctx, text );
}

err_t lteiot8_send_sms_pdu ( lteiot8_t *ctx, char *service_center_number, char *phone_number, char *sms_text )
{
    char text[ SMS_MAX_PDU_LENGTH ] = { 0 };
    char pdu_buf[ SMS_MAX_PDU_LENGTH ] = { 0 };
    char byte_buf[ 4 ] = { 0 };
    char ctrl_z[ ] = { 26, 0 };
    int16_t pdu_buf_len;
    uint8_t length;
    char smsc[ 32 ] = { 0 };
    char phone_num[ 32 ] = { 0 };
    strcpy ( smsc, service_center_number );
    strcpy ( phone_num, phone_number );
    lteiot8_str_cut_chr ( smsc, '+' );
    lteiot8_str_cut_chr ( phone_num, '+' );
    
    pdu_buf_len = pdu_encode( smsc, phone_num, sms_text, pdu_buf, SMS_MAX_PDU_LENGTH );
    
    if ( pdu_buf_len < 0 )
    {
        return LTEIOT8_ERROR;
    }
    
    length = pdu_buf_len - ( ( strlen( smsc ) - 1 ) / 2 + 3 );
    uint8_to_str( length, byte_buf );
    lteiot8_str_cut_chr ( byte_buf, ' ' );
    
    strcpy( text, LTEIOT8_CMD_CMGS );
    strcat( text, "=" );
    strcat( text, byte_buf );
    
    lteiot8_send_cmd( ctx, text );
    memset( text, 0, SMS_MAX_PDU_LENGTH );
    
    for ( int16_t cnt = 0; cnt < pdu_buf_len; cnt++ ) 
    {
        uint8_to_hex ( pdu_buf[ cnt ], byte_buf );
        strcat ( text, byte_buf );
    }
    strcat( text, ctrl_z );
    
    lteiot8_send_cmd( ctx, text );
    
    return LTEIOT8_OK;
}

static int16_t pdu_encode( char *service_center_number, char *phone_number, char *sms_text,
                           uint8_t *output_buffer, uint16_t buffer_size )
{
    if ( buffer_size < 2 )
    {
        return LTEIOT8_ERROR;
    }
        
    int16_t output_buffer_length = 0;

    // 1. Set SMS center number.
    int16_t length = 0;
    if ( ( service_center_number != 0 ) && ( strlen ( service_center_number ) > 0 ) ) 
    {
        output_buffer[ 1 ] = TYPE_OF_ADDRESS_INTERNATIONAL_PHONE; // Add type of address.
        length = encode_phone_number( service_center_number, output_buffer + 2, buffer_size - 2 );
        if ( length < 0 && length >= 254 )
        {
            return LTEIOT8_ERROR;
        }
        length++;
    }
    output_buffer[ 0 ] = length;
    output_buffer_length = length + 1;
    if ( output_buffer_length + 4 > buffer_size )
    {
        return LTEIOT8_ERROR;  // Check if it has space for four more bytes.
    }

    // 2. Set type of message.
    output_buffer[ output_buffer_length++ ] = SMS_SUBMIT;
    output_buffer[ output_buffer_length++ ] = 0x00;  // Message reference.

    // 3. Set phone number.
    output_buffer[ output_buffer_length ] = strlen( phone_number );
    output_buffer[ output_buffer_length + 1 ] = TYPE_OF_ADDRESS_INTERNATIONAL_PHONE;
    length = encode_phone_number( phone_number, output_buffer + output_buffer_length + 2,
                                                buffer_size - output_buffer_length - 2);
    output_buffer_length += length + 2;
    if ( output_buffer_length + 4 > buffer_size )
    {
        return LTEIOT8_ERROR;  // Check if it has space for four more bytes.
    }

    // 4. Protocol identifiers.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-PID: Protocol identifier.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-DCS: Data coding scheme.
    output_buffer[ output_buffer_length++ ] = 0xB0;  // TP-VP: Validity: 10 days

    // 5. SMS message.
    int16_t sms_text_length = strlen( sms_text );
    if ( sms_text_length > SMS_MAX_7BIT_TEXT_LENGTH )
    {
        return LTEIOT8_ERROR;
    }
    output_buffer[ output_buffer_length++ ] = sms_text_length;
    length = encode_pdu_message( sms_text, sms_text_length, output_buffer + output_buffer_length, 
                                                            buffer_size - output_buffer_length );
    if ( length < 0 )
    {
        return LTEIOT8_ERROR;
    }
    output_buffer_length += length;

    return output_buffer_length;
}

static uint8_t swap_decimal_nibble( uint8_t x )
{
    return ( x / 16 ) + ( ( x % 16 ) * 10 );
}

static int16_t encode_pdu_message( char *sms_text, int16_t sms_text_length, 
                                   uint8_t *output_buffer, uint16_t buffer_size )
{
    // Check if output buffer is big enough.
    if ( ( sms_text_length * 7 + 7 ) / 8 > buffer_size )
    {
        return LTEIOT8_ERROR;
    }

    int16_t output_buffer_length = 0;
    int16_t carry_on_bits = 1;
    int16_t i = 0;

    for ( ; i < sms_text_length - 1; ++i ) 
    {
        output_buffer[ output_buffer_length++ ] = 
                            ( ( sms_text[ i ] & BITMASK_7BITS ) >> ( carry_on_bits - 1 ) ) |
                            ( ( sms_text[ i + 1 ] & BITMASK_7BITS ) << ( 8 - carry_on_bits ) );
        carry_on_bits++;
        if ( carry_on_bits == 8 ) 
        {
            carry_on_bits = 1;
            ++i;
        }
    }


    if ( i < sms_text_length )
    {
        output_buffer[ output_buffer_length++ ] = ( sms_text[ i ] & BITMASK_7BITS ) >> ( carry_on_bits - 1 );
    }

    return output_buffer_length;
}

static int16_t encode_phone_number ( char *phone_number, uint8_t *output_buffer, uint16_t buffer_size )
{
    int16_t output_buffer_length = 0;  
    int16_t phone_number_length = strlen( phone_number );

    // Check if the output buffer is big enough.
    if ( ( phone_number_length + 1 ) / 2 > buffer_size )
    {
        return LTEIOT8_ERROR;
    }

    int16_t i = 0;
    for ( ; i < phone_number_length; ++i ) 
    {
        if ( phone_number[ i ] < '0' && phone_number[ i ] > '9' )
        {
            return LTEIOT8_ERROR;
        }

        if ( i % 2 == 0 ) 
        {
            output_buffer[ output_buffer_length++ ] = BITMASK_HIGH_4BITS | ( phone_number[ i ] - '0' );
        } 
        else 
        {
            output_buffer[ output_buffer_length - 1 ] = 
                                    ( output_buffer[ output_buffer_length - 1 ] & BITMASK_LOW_4BITS ) |
                                    ( ( phone_number[ i ] - '0' ) << 4 ); 
        }
    }

    return output_buffer_length;
}

static void lteiot8_str_cut_chr ( char *str, char chr )
{
    uint16_t cnt_0, cnt_1;
    for ( cnt_0 = 0; cnt_0 < strlen( str ); cnt_0++ )
    {
        if ( str[ cnt_0 ] == chr )
        {
            for ( cnt_1 = cnt_0; cnt_1 < strlen( str ); cnt_1++ )
            {
                str[ cnt_1 ] = str[ cnt_1 + 1 ];
            }
        }
    }
}

// ------------------------------------------------------------------------- END
