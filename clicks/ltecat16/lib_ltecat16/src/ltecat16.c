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
 * @file ltecat16.c
 * @brief LTE Cat.1 6 Click Driver.
 */

#include "ltecat16.h"
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
static int16_t pdu_encode( uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text,
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
static int16_t encode_pdu_message( uint8_t *sms_text, int16_t sms_text_length, 
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
static int16_t encode_phone_number ( uint8_t *phone_number, uint8_t *output_buffer, uint16_t buffer_size );

/**
 * @brief LTE Cat.1 6 str cut chr function.
 * @details This function removes all selected characters from string str,
 * and returns it to the same str without those characters.
 * @param str Address of string.
 * @param chr Character to cut.
 */
static void ltecat16_str_cut_chr ( uint8_t *str, uint8_t chr );

void ltecat16_cfg_setup ( ltecat16_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->pwr = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->ring = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t ltecat16_init ( ltecat16_t *ctx, ltecat16_cfg_t *cfg ) 
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

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->pwr, cfg->pwr );
    digital_out_init( &ctx->rts, cfg->rts );
    digital_out_low( &ctx->pwr );
    digital_out_high( &ctx->rts );

    // Input pins
    digital_in_init( &ctx->ring, cfg->ring );
    digital_in_init( &ctx->cts, cfg->cts );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );

    return UART_SUCCESS;
}

err_t ltecat16_generic_write ( ltecat16_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t ltecat16_generic_read ( ltecat16_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void ltecat16_set_pwr_pin ( ltecat16_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->pwr, state );
}

void ltecat16_set_rts_pin ( ltecat16_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rts, state );
}

uint8_t ltecat16_get_ring_pin ( ltecat16_t *ctx )
{
    return digital_in_read ( &ctx->ring );
}

uint8_t ltecat16_get_cts_pin ( ltecat16_t *ctx )
{
    return digital_in_read ( &ctx->cts );
}

void ltecat16_set_power_state ( ltecat16_t *ctx, uint8_t state )
{
    if ( LTECAT16_POWER_STATE_OFF == state )
    {
        digital_out_high ( &ctx->pwr );
        Delay_1sec ( );
        Delay_1sec ( );
        Delay_1sec ( );
        digital_out_low ( &ctx->pwr );
        for ( uint8_t delay_cnt = 0; delay_cnt < 30; delay_cnt++ )
        {
            Delay_1sec ( );
        }
    }
    else if ( LTECAT16_POWER_STATE_ON == state )
    {
        digital_out_high ( &ctx->pwr );
        Delay_100ms ( );
        Delay_100ms ( );
        Delay_100ms ( );
        Delay_100ms ( );
        Delay_100ms ( );
        digital_out_low ( &ctx->pwr );
        for ( uint8_t delay_cnt = 0; delay_cnt < 20; delay_cnt++ )
        {
            Delay_1sec ( );
        }
    }
}

void ltecat16_send_cmd ( ltecat16_t *ctx, uint8_t *cmd )
{
    uint8_t carriage_return[ 2 ] = { '\r', 0 };
    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, carriage_return );
    ltecat16_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
    Delay_100ms(  );
}

void ltecat16_send_cmd_par ( ltecat16_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };
    
    strcpy( ctx->cmd_buffer, at_cmd_buf );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, param_buf );
    
    ltecat16_send_cmd( ctx, ctx->cmd_buffer );
}

void ltecat16_send_cmd_check ( ltecat16_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t check_char[ 2 ] = { '?', 0 };
    
    strcpy( ctx->cmd_buffer, at_cmd_buf );
    strcat( ctx->cmd_buffer, check_char );
    
    ltecat16_send_cmd( ctx, ctx->cmd_buffer );
}

void ltecat16_set_sim_apn ( ltecat16_t *ctx, uint8_t *sim_apn )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };
    uint8_t quotation_char[ 2 ] = { '\"', 0 };
    
    strcpy( ctx->cmd_buffer, LTECAT16_CMD_DEFINE_PDP_CONTEXT );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, "1,\"IP\",\"" );
    strcat( ctx->cmd_buffer, sim_apn );
    strcat( ctx->cmd_buffer, quotation_char );
    
    ltecat16_send_cmd( ctx, ctx->cmd_buffer );
}

void ltecat16_send_sms_text ( ltecat16_t *ctx, uint8_t *phone_number, uint8_t *sms_text )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };
    uint8_t quotation_char[ 2 ] = { '\"', 0 };
    uint8_t ctrl_z[ 2 ] = { 26, 0 };
    
    strcpy( ctx->cmd_buffer, LTECAT16_CMD_SEND_SMS );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, quotation_char );
    strcat( ctx->cmd_buffer, phone_number );
    strcat( ctx->cmd_buffer, quotation_char );
    
    ltecat16_send_cmd( ctx, ctx->cmd_buffer );
    Delay_1sec ( );
    
    strcpy( ctx->cmd_buffer, sms_text );
    strcat( ctx->cmd_buffer, ctrl_z );
    ltecat16_send_cmd( ctx, ctx->cmd_buffer );
}

err_t ltecat16_send_sms_pdu ( ltecat16_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text )
{
    uint8_t pdu_buf[ SMS_MAX_PDU_LENGTH ] = { 0 };
    uint8_t byte_buf[ 4 ] = { 0 };
    uint8_t ctrl_z[ 2 ] = { 26, 0 };
    int16_t pdu_buf_len = 0;
    uint8_t length = 0;
    uint8_t smsc[ 32 ] = { 0 };
    uint8_t phone_num[ 32 ] = { 0 };
    strcpy ( smsc, service_center_number );
    strcpy ( phone_num, phone_number );
    ltecat16_str_cut_chr ( smsc, '+' );
    ltecat16_str_cut_chr ( phone_num, '+' );
    
    pdu_buf_len = pdu_encode( smsc, phone_num, sms_text, pdu_buf, SMS_MAX_PDU_LENGTH );
    
    if ( pdu_buf_len < 0 )
    {
        return LTECAT16_ERROR;
    }
    
    length = pdu_buf_len - ( ( strlen( smsc ) - 1 ) / 2 + 3 );
    uint8_to_str( length, byte_buf );
    ltecat16_str_cut_chr ( byte_buf, ' ' );
    
    ltecat16_send_cmd_par( ctx, LTECAT16_CMD_SEND_SMS, byte_buf );
    Delay_1sec ( );
    memset( ctx->cmd_buffer, 0, sizeof ( ctx->cmd_buffer ) );
    
    for ( int16_t cnt = 0; cnt < pdu_buf_len; cnt++ ) 
    {
        uint8_to_hex ( pdu_buf[ cnt ], byte_buf );
        strcat ( ctx->cmd_buffer, byte_buf );
    }
    strcat( ctx->cmd_buffer, ctrl_z );
    
    ltecat16_send_cmd( ctx, ctx->cmd_buffer );
    
    return LTECAT16_OK;
}

static int16_t pdu_encode( uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text,
                           uint8_t *output_buffer, uint16_t buffer_size )
{
    if ( buffer_size < 2 )
    {
        return LTECAT16_ERROR;
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
            return LTECAT16_ERROR;
        }
        length++;
    }
    output_buffer[ 0 ] = length;
    output_buffer_length = length + 1;
    if ( output_buffer_length + 4 > buffer_size )
    {
        return LTECAT16_ERROR;  // Check if it has space for four more bytes.
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
        return LTECAT16_ERROR;  // Check if it has space for four more bytes.
    }

    // 4. Protocol identifiers.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-PID: Protocol identifier.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-DCS: Data coding scheme.
    output_buffer[ output_buffer_length++ ] = 0xB0;  // TP-VP: Validity: 10 days

    // 5. SMS message.
    int16_t sms_text_length = strlen( sms_text );
    if ( sms_text_length > SMS_MAX_7BIT_TEXT_LENGTH )
    {
        return LTECAT16_ERROR;
    }
    output_buffer[ output_buffer_length++ ] = sms_text_length;
    length = encode_pdu_message( sms_text, sms_text_length, output_buffer + output_buffer_length, 
                                                            buffer_size - output_buffer_length );
    if ( length < 0 )
    {
        return LTECAT16_ERROR;
    }
    output_buffer_length += length;

    return output_buffer_length;
}

static uint8_t swap_decimal_nibble( uint8_t x )
{
    return ( x / 16 ) + ( ( x % 16 ) * 10 );
}

static int16_t encode_pdu_message( uint8_t *sms_text, int16_t sms_text_length, 
                                   uint8_t *output_buffer, uint16_t buffer_size )
{
    // Check if output buffer is big enough.
    if ( ( sms_text_length * 7 + 7 ) / 8 > buffer_size )
    {
        return LTECAT16_ERROR;
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
        if ( 8 == carry_on_bits ) 
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

static int16_t encode_phone_number ( uint8_t *phone_number, uint8_t *output_buffer, uint16_t buffer_size )
{
    int16_t output_buffer_length = 0;  
    int16_t phone_number_length = strlen( phone_number );

    // Check if the output buffer is big enough.
    if ( ( phone_number_length + 1 ) / 2 > buffer_size )
    {
        return LTECAT16_ERROR;
    }

    int16_t i = 0;
    for ( ; i < phone_number_length; ++i ) 
    {
        if ( phone_number[ i ] < '0' && phone_number[ i ] > '9' )
        {
            return LTECAT16_ERROR;
        }

        if ( 0 == i % 2 ) 
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

static void ltecat16_str_cut_chr ( uint8_t *str, uint8_t chr )
{
    uint16_t cnt_0 = 0, cnt_1 = 0;
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
