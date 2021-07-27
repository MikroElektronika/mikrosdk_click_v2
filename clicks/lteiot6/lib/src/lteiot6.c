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
 * @file lteiot6.c
 * @brief This file contains API for LTE IoT 6 Click Driver.
 */

#include "lteiot6.h"
#include "string.h"
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


void lteiot6_cfg_setup ( lteiot6_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->pwr = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->ri  = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t lteiot6_init ( lteiot6_t *ctx, lteiot6_cfg_t *cfg )
{
    digital_in_init( &ctx->rx_pin, cfg->rx_pin );
    
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
    digital_out_init( &ctx->pwr, cfg->pwr );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins
    digital_in_init( &ctx->ri, cfg->ri );
    digital_in_init( &ctx->cts, cfg->cts );

    return UART_SUCCESS;
}

err_t lteiot6_generic_write ( lteiot6_t *ctx, char *data_buf, uint16_t len )
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t lteiot6_generic_read ( lteiot6_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void lteiot6_power_on ( lteiot6_t *ctx )
{
    digital_out_low( &ctx->pwr );
    Delay_1sec( );
    digital_out_high( &ctx->pwr );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
}

void lteiot6_reset ( lteiot6_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_1sec( );
    digital_out_low( &ctx->rst );
    Delay_1sec( );
}

void lteiot6_set_pwr ( lteiot6_t *ctx, uint8_t state )
{
    if ( state > 0 )
    {
        digital_out_high( &ctx->pwr );
    }
    else
    {
        digital_out_low( &ctx->pwr );
    }
}

void lteiot6_set_rst ( lteiot6_t *ctx, uint8_t state )
{
    if ( state > 0 )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void lteiot6_set_rts ( lteiot6_t *ctx, uint8_t state )
{
    if ( state > 0 )
    {
        digital_out_high( &ctx->rts );
    }
    else
    {
        digital_out_low( &ctx->rts );
    }
}

uint8_t lteiot6_get_ri ( lteiot6_t *ctx )
{
    return digital_in_read( &ctx->ri );
}

uint8_t lteiot6_get_rx ( lteiot6_t *ctx )
{
    return digital_in_read( &ctx->rx_pin );
}

uint8_t lteiot6_get_cts ( lteiot6_t *ctx )
{
    return digital_in_read( &ctx->cts );
}

void lteiot6_send_cmd ( lteiot6_t *ctx, char *cmd )
{
    char final_cmd[ 100 ] = { 0 };
    char cr_lf[ 3 ] = { 13, 10, 0 };
    
    while ( *cmd != 0 )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    
    uart_write( &ctx->uart, cr_lf, 2 );
    Delay_100ms(  );
}

void lteiot6_send_cmd_with_parameter ( lteiot6_t *ctx, char *at_cmd_buf, char *param_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    lteiot6_send_cmd( ctx, final_cmd );
}

void lteiot6_send_cmd_check ( lteiot6_t *ctx, char *at_cmd_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    lteiot6_send_cmd( ctx, final_cmd );
}

void lteiot6_send_cmd_parameter_check ( lteiot6_t *ctx, char *at_cmd_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 3 ] = { '=' , '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    lteiot6_send_cmd( ctx, final_cmd );
}

void lteiot6_set_sim_apn ( lteiot6_t *ctx, char *sim_apn )
{
    char final_cmd[ 50 ] = "1,\"IP\",\"";
    char end_cmd[ 3 ] = "\"";
    
    strcat( final_cmd, sim_apn );
    strcat( final_cmd, end_cmd );
    
    lteiot6_send_cmd_with_parameter( ctx, LTEIOT6_CMD_CGDCONT, final_cmd );
}

void lteiot6_send_text_message ( lteiot6_t *ctx, char *phone_number, char *message_context )
{
    char text[ 200 ] = { 0 };
    char cmd_start[] = "AT+CMGS=\"";
    char cmd_end[] = { '"', 13, 0 };
    
    char txt_end[] = { 26, 0 };
    
    strcpy( text, cmd_start );
    strcat( text, phone_number );
    strcat( text, cmd_end );
    lteiot6_generic_write( ctx, text, strlen(text) );
    memset( text, 0, strlen(text) );
    Delay_10ms();
    strcpy( text, message_context );
    strcat( text, txt_end );
    lteiot6_generic_write( ctx, text, strlen(text) );
    Delay_10ms();
}

err_t lteiot6_send_sms_pdu ( lteiot6_t *ctx, char *service_center_number, char *phone_number, char *sms_text )
{
    char text[ SMS_MAX_PDU_LENGTH ] = { 0 };
    char pdu_buf[ SMS_MAX_PDU_LENGTH ] = { 0 };
    char byte_buf[ 4 ] = { 0 };
    char ctrl_z[ ] = { 26, 0 };
    int16_t pdu_buf_len;
    uint8_t length;
    
    str_cut_chr ( service_center_number, '+' );
    str_cut_chr ( phone_number, '+' );
    
    pdu_buf_len = pdu_encode( service_center_number, phone_number, sms_text, pdu_buf, SMS_MAX_PDU_LENGTH );
    
    if ( pdu_buf_len < 0 )
    {
        return LTEIOT6_ERROR;
    }
    
    length = pdu_buf_len - ( ( strlen( service_center_number ) - 1 ) / 2 + 3 );
    uint8_to_str( length, byte_buf );
    str_cut_chr ( byte_buf, ' ');
    
    strcpy( text, LTEIOT6_CMD_CMGS );
    strcat( text, "=" );
    strcat( text, byte_buf );
    
    lteiot6_send_cmd( ctx, text );
    memset( text, 0, SMS_MAX_PDU_LENGTH );
    
    for ( int16_t cnt = 0; cnt < pdu_buf_len; cnt++ ) 
    {
        uint8_to_hex ( pdu_buf[ cnt ], byte_buf );
        strcat ( text, byte_buf );
    }
    strcat( text, ctrl_z );
    
    lteiot6_send_cmd( ctx, text );
    
    return LTEIOT6_OK;
}

static int16_t pdu_encode( char *service_center_number, char *phone_number, char *sms_text,
                           uint8_t *output_buffer, uint16_t buffer_size )
{
    if ( buffer_size < 2 )
    {
        return LTEIOT6_ERROR;
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
            return LTEIOT6_ERROR;
        }
        length++;
    }
    output_buffer[ 0 ] = length;
    output_buffer_length = length + 1;
    if ( output_buffer_length + 4 > buffer_size )
    {
        return LTEIOT6_ERROR;  // Check if it has space for four more bytes.
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
        return LTEIOT6_ERROR;  // Check if it has space for four more bytes.
    }

    // 4. Protocol identifiers.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-PID: Protocol identifier.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-DCS: Data coding scheme.
    output_buffer[ output_buffer_length++ ] = 0xB0;  // TP-VP: Validity: 10 days

    // 5. SMS message.
    int16_t sms_text_length = strlen( sms_text );
    if ( sms_text_length > SMS_MAX_7BIT_TEXT_LENGTH )
    {
        return LTEIOT6_ERROR;
    }
    output_buffer[ output_buffer_length++ ] = sms_text_length;
    length = encode_pdu_message( sms_text, sms_text_length, output_buffer + output_buffer_length, 
                                                            buffer_size - output_buffer_length );
    if ( length < 0 )
    {
        return LTEIOT6_ERROR;
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
        return LTEIOT6_ERROR;
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
        return LTEIOT6_ERROR;
    }

    int16_t i = 0;
    for ( ; i < phone_number_length; ++i ) 
    {
        if ( phone_number[ i ] < '0' && phone_number[ i ] > '9' )
        {
            return LTEIOT6_ERROR;
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


// ------------------------------------------------------------------------- END
