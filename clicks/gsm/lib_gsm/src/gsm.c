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
 * @file gsm.c
 * @brief GSM Click Driver.
 */

#include "gsm.h"
#include "conversions.h"
#include "generic_pointer.h"

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
static int16_t pdu_encode ( uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text,
                            uint8_t *output_buffer, uint16_t buffer_size );

/**
 * @brief Swap decimal digits of a number.
 * @details Swap decimal digits of a number (e.g. 12 -> 21).
 * @param[in] x : Decimal number to swap digits.
 * @return Swapped decimal number.
 */
static uint8_t swap_decimal_nibble ( uint8_t x );

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
static int16_t encode_pdu_message ( uint8_t *sms_text, int16_t sms_text_length, 
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
 * @brief GSM str cut chr function.
 * @details This function removes all selected characters from string str,
 * and returns it to the same str without those characters.
 * @param str Address of string.
 * @param chr Character to cut.
 */
static void gsm_str_cut_chr ( uint8_t *str, uint8_t chr );

void gsm_cfg_setup ( gsm_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->pwr   = HAL_PIN_NC;
    cfg->rst   = HAL_PIN_NC;
    cfg->rts   = HAL_PIN_NC;
    cfg->gp2   = HAL_PIN_NC;
    cfg->cts   = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t gsm_init ( gsm_t *ctx, gsm_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins
    digital_in_init( &ctx->pwr, cfg->pwr );
    digital_in_init( &ctx->gp2, cfg->gp2 );
    digital_in_init( &ctx->cts, cfg->cts );
    
    digital_out_low ( &ctx->rts );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    digital_out_low ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );

    return UART_SUCCESS;
}

err_t gsm_generic_write ( gsm_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t gsm_generic_read ( gsm_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

void gsm_set_rst_pin ( gsm_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->rst, state );
}

void gsm_set_rts_pin ( gsm_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->rts, state );
}

uint8_t gsm_get_cts_pin ( gsm_t *ctx ) 
{
    return digital_in_read( &ctx->cts );
}

uint8_t gsm_get_pwr_pin ( gsm_t *ctx ) 
{
    return digital_in_read( &ctx->pwr );
}

uint8_t gsm_get_gp2_pin ( gsm_t *ctx ) 
{
    return digital_in_read( &ctx->gp2 );
}

void gsm_send_cmd ( gsm_t *ctx, uint8_t *cmd )
{
    uint8_t carriage_return = 13;
    while ( *cmd != 0 )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    uart_write( &ctx->uart, &carriage_return, 1 );
    Delay_100ms(  );
}

void gsm_send_cmd_with_par ( gsm_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    gsm_send_cmd( ctx, final_cmd );
}

void gsm_send_cmd_check ( gsm_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    gsm_send_cmd( ctx, final_cmd );
}

void gsm_send_cmd_par_check ( gsm_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 3 ] = { '=' , '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    gsm_send_cmd( ctx, final_cmd );
}

void gsm_set_sim_apn ( gsm_t *ctx, uint8_t *sim_apn )
{
    uint8_t final_cmd[ 50 ] = "1,\"IP\",\"";
    uint8_t end_cmd[ 3 ] = "\"";
    
    strcat( final_cmd, sim_apn );
    strcat( final_cmd, end_cmd );
    
    gsm_send_cmd_with_par( ctx, GSM_CMD_CGDCONT, final_cmd );
}

void gsm_send_sms_text ( gsm_t *ctx, uint8_t *phone_number, uint8_t *sms_text )
{
    uint8_t text[ 200 ] = { 0 };
    uint8_t cmd_start[ ] = "=\"";
    uint8_t cmd_end[ ] = "\"\r";
    uint8_t txt_end[ ] = "\032";
    
    strcpy( text, GSM_CMD_CMGS );
    strcat( text, cmd_start );
    strcat( text, phone_number );
    strcat( text, cmd_end );
    
    gsm_send_cmd( ctx, text );
    memset( text, 0, sizeof ( text ) );
    
    strcpy( text, sms_text );
    strcat( text, txt_end );
    gsm_send_cmd( ctx, text );
}

err_t gsm_send_sms_pdu ( gsm_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text )
{
    uint8_t text[ SMS_MAX_PDU_LENGTH ] = { 0 };
    uint8_t pdu_buf[ SMS_MAX_PDU_LENGTH ] = { 0 };
    uint8_t byte_buf[ 4 ] = { 0 };
    uint8_t ctrl_z[ 2 ] = { 26, 0 };
    int16_t pdu_buf_len = 0;
    uint8_t length = 0;
    uint8_t smsc[ 32 ] = { 0 };
    uint8_t phone_num[ 32 ] = { 0 };
    strcpy ( smsc, service_center_number );
    strcpy ( phone_num, phone_number );
    gsm_str_cut_chr ( smsc, '+' );
    gsm_str_cut_chr ( phone_num, '+' );
    
    pdu_buf_len = pdu_encode( smsc, phone_num, sms_text, pdu_buf, SMS_MAX_PDU_LENGTH );
    
    if ( pdu_buf_len < 0 )
    {
        return GSM_ERROR;
    }
    
    length = pdu_buf_len - ( ( strlen( smsc ) - 1 ) / 2 + 3 );
    uint8_to_str( length, byte_buf );
    gsm_str_cut_chr ( byte_buf, ' ' );
    
    strcpy( text, GSM_CMD_CMGS );
    strcat( text, "=" );
    strcat( text, byte_buf );
    
    gsm_send_cmd( ctx, text );
    memset( text, 0, SMS_MAX_PDU_LENGTH );
    
    for ( int16_t cnt = 0; cnt < pdu_buf_len; cnt++ ) 
    {
        uint8_to_hex ( pdu_buf[ cnt ], byte_buf );
        strcat ( text, byte_buf );
    }
    strcat( text, ctrl_z );
    
    gsm_send_cmd( ctx, text );
    
    return GSM_OK;
}

static int16_t pdu_encode ( uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text,
                            uint8_t *output_buffer, uint16_t buffer_size )
{
    if ( buffer_size < 2 )
    {
        return GSM_ERROR;
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
            return GSM_ERROR;
        }
        length++;
    }
    output_buffer[ 0 ] = length;
    output_buffer_length = length + 1;
    if ( output_buffer_length + 4 > buffer_size )
    {
        return GSM_ERROR;  // Check if it has space for four more bytes.
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
        return GSM_ERROR;  // Check if it has space for four more bytes.
    }

    // 4. Protocol identifiers.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-PID: Protocol identifier.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-DCS: Data coding scheme.
    output_buffer[ output_buffer_length++ ] = 0xB0;  // TP-VP: Validity: 10 days

    // 5. SMS message.
    int16_t sms_text_length = strlen( sms_text );
    if ( sms_text_length > SMS_MAX_7BIT_TEXT_LENGTH )
    {
        return GSM_ERROR;
    }
    output_buffer[ output_buffer_length++ ] = sms_text_length;
    length = encode_pdu_message( sms_text, sms_text_length, output_buffer + output_buffer_length, 
                                                            buffer_size - output_buffer_length );
    if ( length < 0 )
    {
        return GSM_ERROR;
    }
    output_buffer_length += length;

    return output_buffer_length;
}

static uint8_t swap_decimal_nibble ( uint8_t x )
{
    return ( x / 16 ) + ( ( x % 16 ) * 10 );
}

static int16_t encode_pdu_message ( uint8_t *sms_text, int16_t sms_text_length, 
                                    uint8_t *output_buffer, uint16_t buffer_size )
{
    // Check if output buffer is big enough.
    if ( ( sms_text_length * 7 + 7 ) / 8 > buffer_size )
    {
        return GSM_ERROR;
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

static int16_t encode_phone_number ( uint8_t *phone_number, uint8_t *output_buffer, uint16_t buffer_size )
{
    int16_t output_buffer_length = 0;  
    int16_t phone_number_length = strlen( phone_number );

    // Check if the output buffer is big enough.
    if ( ( phone_number_length + 1 ) / 2 > buffer_size )
    {
        return GSM_ERROR;
    }

    int16_t i = 0;
    for ( ; i < phone_number_length; ++i ) 
    {
        if ( phone_number[ i ] < '0' && phone_number[ i ] > '9' )
        {
            return GSM_ERROR;
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

static void gsm_str_cut_chr ( uint8_t *str, uint8_t chr )
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
