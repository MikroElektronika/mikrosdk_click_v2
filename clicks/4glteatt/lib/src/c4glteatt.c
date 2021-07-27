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
 * @file c4glteatt.c
 * @brief 4G LTE-ATT Click Driver.
 */

#include "c4glteatt.h"
#include "string.h"
#include "conversions.h"


// ------------------------------------------------------------- PRIVATE MACROS 

#define BITMASK_7BITS                       0x7F
#define BITMASK_8BITS                       0xFF
#define BITMASK_HIGH_4BITS                  0xF0
#define BITMASK_LOW_4BITS                   0x0F
#define TYPE_OF_ADDRESS_INTERNATIONAL_PHONE 0x91
#define TYPE_OF_ADDRESS_NATIONAL_SUBSCRIBER 0xC8
#define SMS_DELIVER_ONE_MESSAGE             0x04
#define SMS_SUBMIT                          0x11
#define SMS_MAX_7BIT_TEXT_LENGTH            160
#define SMS_MAX_PDU_LENGTH                  256

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

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
static int16_t pdu_encode( char *service_center_number, char *phone_number, char *sms_text, uint8_t *output_buffer, uint16_t buffer_size );

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
static int16_t encode_pdu_message( char *sms_text, int16_t sms_text_length, uint8_t *output_buffer, uint16_t buffer_size );

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

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c4glteatt_cfg_setup ( c4glteatt_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sta   = HAL_PIN_NC;
    cfg->pwk = HAL_PIN_NC;
    cfg->rts   = HAL_PIN_NC;
    cfg->ring = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t c4glteatt_init ( c4glteatt_t *ctx, c4glteatt_cfg_t *cfg ) {
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

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR ) {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->pwk, cfg->pwk );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins
    digital_in_init( &ctx->sta, cfg->sta );
    digital_in_init( &ctx->ring, cfg->ring );
    digital_in_init( &ctx->cts, cfg->cts );

    return UART_SUCCESS;
}

void c4glteatt_module_power_on ( c4glteatt_t *ctx ) {
    digital_out_low( &ctx->rts );
    digital_out_high( &ctx->pwk );
    Delay_1ms();
    digital_out_low( &ctx->pwk );
    Delay_1ms();
    digital_out_high( &ctx->pwk );
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
}

err_t c4glteatt_generic_write ( c4glteatt_t *ctx, char *data_buf, uint16_t len ) {
    return uart_write( &ctx->uart, data_buf, len );
}

err_t c4glteatt_generic_read ( c4glteatt_t *ctx, char *data_buf, uint16_t max_len ) {
    return uart_read( &ctx->uart, data_buf, max_len );
}

void c4glteatt_set_pwk_pin ( c4glteatt_t *ctx, uint8_t state ) {
    digital_out_write( &ctx->pwk, state );
}

void c4glteatt_set_rts_pin ( c4glteatt_t *ctx, uint8_t state ) {
    digital_out_write( &ctx->rts, state );
}

uint8_t c4glteatt_get_cts_pin ( c4glteatt_t *ctx ) {
    return digital_in_read( &ctx->cts );
}

uint8_t c4glteatt_get_sta_pin ( c4glteatt_t *ctx ) {
    return digital_in_read( &ctx->sta );
}

uint8_t c4glteatt_get_ring_pin ( c4glteatt_t *ctx ) {
    return digital_in_read( &ctx->ring );
}

void c4glteatt_send_cmd ( c4glteatt_t *ctx, char *cmd ) {
    char cr[ 2 ] = { 13, 0 };
    
    while ( *cmd != 0 ) {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    
    uart_write( &ctx->uart, cr, 1 );
    Delay_100ms(  );
}

void c4glteatt_send_cmd_with_parameter ( c4glteatt_t *ctx, char *at_cmd_buf, char *param_buf ) {
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    c4glteatt_send_cmd( ctx, final_cmd );
}

void c4glteatt_send_cmd_check ( c4glteatt_t *ctx, char *at_cmd_buf ) {
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    c4glteatt_send_cmd( ctx, final_cmd );
}

void c4glteatt_send_cmd_parameter_check ( c4glteatt_t *ctx, char *at_cmd_buf ) {
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 3 ] = { '=' , '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    c4glteatt_send_cmd( ctx, final_cmd );
}

void c4glteatt_set_sim_apn ( c4glteatt_t *ctx, char *sim_apn ) {
    char final_cmd[ 50 ] = "1,\"IP\",\"";
    char end_cmd[ 3 ] = "\"";
    
    strcat( final_cmd, sim_apn );
    strcat( final_cmd, end_cmd );
    
    c4glteatt_send_cmd_with_parameter( ctx, C4GLTEATT_CMD_CGDCONT, final_cmd );
}

void c4glteatt_send_sms_text ( c4glteatt_t *ctx, char *phone_number, char *sms_text ) {
    char text[ 200 ] = { 0 };
    char cmd_start[] = "AT+CMGS=\"";
    char cmd_end[] = "\"\r";
    char txt_end[] = "\032";
    
    strcpy( text, cmd_start );
    strcat( text, phone_number );
    strcat( text, cmd_end );
    
    c4glteatt_send_cmd( ctx, text );
    memset( text, 0 , 200 );
    
    strcpy( text, sms_text );
    strcat( text, txt_end );
    c4glteatt_send_cmd( ctx, text );
}

err_t c4glteatt_send_sms_pdu ( c4glteatt_t *ctx, char *service_center_number, char *phone_number, char *sms_text ) {
    char text[ SMS_MAX_PDU_LENGTH ] = { 0 };
    char pdu_buf[ SMS_MAX_PDU_LENGTH ] = { 0 };
    char byte_buf[ 4 ] = { 0 };
    char ctrl_z[ ] = { 26, 0 };
    int16_t pdu_buf_len;
    uint8_t length;
    
    str_cut_chr ( service_center_number, '+' );
    str_cut_chr ( phone_number, '+' );
    
    pdu_buf_len = pdu_encode( service_center_number, phone_number, sms_text, pdu_buf, SMS_MAX_PDU_LENGTH );
    
    if ( pdu_buf_len < 0 ) {
        return C4GLTEATT_ERROR;
    }
    
    length = pdu_buf_len - ( ( strlen( service_center_number ) - 1 ) / 2 + 3 );
    uint8_to_str( length, byte_buf );
    str_cut_chr ( byte_buf, ' ');
    
    strcpy( text, C4GLTEATT_CMD_CMGS );
    strcat( text, "=" );
    strcat( text, byte_buf );
    
    c4glteatt_send_cmd( ctx, text );
    memset( text, 0, SMS_MAX_PDU_LENGTH );
    
    for ( int16_t cnt = 0; cnt < pdu_buf_len; cnt++ ) {
        uint8_to_hex ( pdu_buf[ cnt ], byte_buf );
        strcat ( text, byte_buf );
    }
    strcat( text, ctrl_z );
    
    c4glteatt_send_cmd( ctx, text );
    
    return C4GLTEATT_OK;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static int16_t pdu_encode( char *service_center_number, char *phone_number, char *sms_text, uint8_t *output_buffer, uint16_t buffer_size ) {
    if ( buffer_size < 2 ) {
        return C4GLTEATT_ERROR;
    }
        
    int16_t output_buffer_length = 0;

    // 1. Set SMS center number.
    int16_t length = 0;
    if ( ( service_center_number != 0 ) && ( strlen ( service_center_number ) > 0 ) ) {
        output_buffer[ 1 ] = TYPE_OF_ADDRESS_INTERNATIONAL_PHONE; // Add type of address.
        length = encode_phone_number( service_center_number, output_buffer + 2, buffer_size - 2 );
        if ( length < 0 && length >= 254 ) {
            return C4GLTEATT_ERROR;
        }
        length++;
    }
    output_buffer[ 0 ] = length;
    output_buffer_length = length + 1;
    if ( output_buffer_length + 4 > buffer_size ) {
        return C4GLTEATT_ERROR;  // Check if it has space for four more bytes.
    }

    // 2. Set type of message.
    output_buffer[ output_buffer_length++ ] = SMS_SUBMIT;
    output_buffer[ output_buffer_length++ ] = 0x00;  // Message reference.

    // 3. Set phone number.
    output_buffer[ output_buffer_length ] = strlen( phone_number );
    output_buffer[ output_buffer_length + 1 ] = TYPE_OF_ADDRESS_INTERNATIONAL_PHONE;
    length = encode_phone_number( phone_number, output_buffer + output_buffer_length + 2, buffer_size - output_buffer_length - 2);
    output_buffer_length += length + 2;
    if ( output_buffer_length + 4 > buffer_size ) {
        return C4GLTEATT_ERROR;  // Check if it has space for four more bytes.
    }

    // 4. Protocol identifiers.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-PID: Protocol identifier.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-DCS: Data coding scheme.
    output_buffer[ output_buffer_length++ ] = 0xB0;  // TP-VP: Validity: 10 days

    // 5. SMS message.
    int16_t sms_text_length = strlen( sms_text );
    if ( sms_text_length > SMS_MAX_7BIT_TEXT_LENGTH ) {
        return C4GLTEATT_ERROR;
    }
    output_buffer[ output_buffer_length++ ] = sms_text_length;
    length = encode_pdu_message( sms_text, sms_text_length, output_buffer + output_buffer_length, buffer_size - output_buffer_length );
    if ( length < 0 ) {
        return C4GLTEATT_ERROR;
    }
    output_buffer_length += length;

    return output_buffer_length;
}

static uint8_t swap_decimal_nibble( uint8_t x ) {
    return ( x / 16 ) + ( ( x % 16 ) * 10 );
}

static int16_t encode_pdu_message( char *sms_text, int16_t sms_text_length, uint8_t *output_buffer, uint16_t buffer_size ) {
    // Check if output buffer is big enough.
    if ( ( sms_text_length * 7 + 7 ) / 8 > buffer_size ) {
        return C4GLTEATT_ERROR;
    }

    int16_t output_buffer_length = 0;
    int16_t carry_on_bits = 1;
    int16_t i = 0;

    for ( ; i < sms_text_length - 1; ++i ) {
        output_buffer[ output_buffer_length++ ] = ( ( sms_text[ i ] & BITMASK_7BITS ) >> ( carry_on_bits - 1 ) ) | ( ( sms_text[ i + 1 ] & BITMASK_7BITS ) << ( 8 - carry_on_bits ) );
        carry_on_bits++;
        if ( carry_on_bits == 8 ) {
            carry_on_bits = 1;
            ++i;
        }
    }


    if ( i < sms_text_length ) {
        output_buffer[ output_buffer_length++ ] = ( sms_text[ i ] & BITMASK_7BITS ) >> ( carry_on_bits - 1 );
    }

    return output_buffer_length;
}

static int16_t encode_phone_number ( char *phone_number, uint8_t *output_buffer, uint16_t buffer_size ) {
    int16_t output_buffer_length = 0;  
    int16_t phone_number_length = strlen( phone_number );

    // Check if the output buffer is big enough.
    if ( ( phone_number_length + 1 ) / 2 > buffer_size ) {
        return C4GLTEATT_ERROR;
    }

    int16_t i = 0;
    for ( ; i < phone_number_length; ++i ) {
        if ( phone_number[ i ] < '0' && phone_number[ i ] > '9' ) {
            return C4GLTEATT_ERROR;
        }

        if ( i % 2 == 0 ) {
            output_buffer[ output_buffer_length++ ] = BITMASK_HIGH_4BITS | ( phone_number[ i ] - '0' );
        } else {
            output_buffer[ output_buffer_length - 1 ] = ( output_buffer[ output_buffer_length - 1 ] & BITMASK_LOW_4BITS ) | ( ( phone_number[ i ] - '0' ) << 4 ); 
        }
    }

    return output_buffer_length;
}

// ------------------------------------------------------------------------- END
