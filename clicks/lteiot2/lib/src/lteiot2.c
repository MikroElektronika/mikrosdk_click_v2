/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "lteiot2.h"
#include "string.h"
#include "generic_pointer.h"
#include "conversions.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PARSER_READY                        0
#define PARSER_COMMAND_NOT_SUPPORTED        1
#define PARSER_ELEMENT_NOT_SUPPORTED        2

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

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

// Checks if the command is supported.
static uint8_t check_support_command ( uint8_t command, uint8_t element, char *command_buf );

/* 
 * Encode an SMS message. Output the encoded message into output pdu buffer.
 * Returns the length of the SMS encoded message in the output buffer or
 * a negative number in case encoding failed (for example provided output buffer
 * does not have enough space).
 */
static int16_t pdu_encode( char *service_center_number, char *phone_number, char *sms_text,
                           uint8_t *output_buffer, uint16_t buffer_size );

// Swap decimal digits of a number (e.g. 12 -> 21).
static uint8_t swap_decimal_nibble( uint8_t x );

// Encode PDU message by merging 7 bit ASCII characters into 8 bit octets.
static int16_t encode_pdu_message( char *sms_text, int16_t sms_text_length, 
                                   uint8_t *output_buffer, uint16_t buffer_size );

// Encode a digit based phone number for SMS based format.
static int16_t encode_phone_number ( char *phone_number, uint8_t *output_buffer, uint16_t buffer_size );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lteiot2_cfg_setup ( lteiot2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->sta = HAL_PIN_NC;
    cfg->pwk = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->ri  = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

LTEIOT2_RETVAL lteiot2_init ( lteiot2_t *ctx, lteiot2_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin. 
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin. 
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );  
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 

    digital_out_init( &ctx->pwk, cfg->pwk );
    digital_out_init( &ctx->rts, cfg->rts );
    digital_out_low( &ctx->rts );
    digital_out_high( &ctx->pwk );

    // Input pins

    digital_in_init( &ctx->sta, cfg->sta );
    digital_in_init( &ctx->ri, cfg->ri );
    digital_in_init( &ctx->cts, cfg->cts );

    return LTEIOT2_OK;
}

void lteiot2_module_power ( lteiot2_t *ctx, uint8_t state )
{
    do
    {
        digital_out_low( &ctx->pwk );
        Delay_1sec( );
        digital_out_high( &ctx->pwk );
        Delay_1sec( );
        Delay_1sec( );
        Delay_1sec( );
    } while ( digital_in_read( &ctx->sta ) != state );
}

void lteiot2_generic_write ( lteiot2_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t lteiot2_generic_read ( lteiot2_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void lteiot2_set_rts ( lteiot2_t *ctx, uint8_t state )
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

uint8_t lteiot2_get_cts ( lteiot2_t *ctx )
{
    return digital_in_read( &ctx->cts );
}

void lteiot2_send_cmd ( lteiot2_t *ctx, char *cmd )
{
    char cr[ 2 ] = { 13, 0 };
    
    while ( *cmd != 0 )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    
    uart_write( &ctx->uart, cr, 1 );
    Delay_100ms(  );
}

void lteiot2_send_cmd_with_parameter ( lteiot2_t *ctx, char *at_cmd_buf, char *param_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    lteiot2_send_cmd( ctx, final_cmd );
}

void lteiot2_send_cmd_check ( lteiot2_t *ctx, char *at_cmd_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    lteiot2_send_cmd( ctx, final_cmd );
}

void lteiot2_send_cmd_parameter_check ( lteiot2_t *ctx, char *at_cmd_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 3 ] = { '=' , '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    lteiot2_send_cmd( ctx, final_cmd );
}

void lteiot2_set_sim_apn ( lteiot2_t *ctx, char *sim_apn )
{
    char final_cmd[ 50 ] = "1,\"IP\",\"";
    char end_cmd[ 3 ] = "\"";
    
    strcat( final_cmd, sim_apn );
    strcat( final_cmd, end_cmd );
    
    lteiot2_send_cmd_with_parameter( ctx, LTEIOT2_CMD_CGDCONT, final_cmd );
}

void lteiot2_send_sms_text ( lteiot2_t *ctx, char *phone_number, char *sms_text )
{
    char text[ 200 ] = { 0 };
    char cmd_start[] = "AT+CMGS=\"";
    char cmd_end[] = "\"\r";
    char txt_end[] = "\032";
    
    strcpy( text, cmd_start );
    strcat( text, phone_number );
    strcat( text, cmd_end );
    
    lteiot2_send_cmd( ctx, text );
    memset( text, 0 , 200 );
    
    strcpy( text, sms_text );
    strcat( text, txt_end );
    lteiot2_send_cmd( ctx, text );
}

err_t lteiot2_send_sms_pdu ( lteiot2_t *ctx, char *service_center_number, 
                                           char *phone_number, char *sms_text )
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
        return LTEIOT2_ERROR;
    }
    
    length = pdu_buf_len - ( ( strlen( service_center_number ) - 1 ) / 2 + 3 );
    uint8_to_str( length, byte_buf );
    str_cut_chr ( byte_buf, ' ');
    
    strcpy( text, LTEIOT2_CMD_CMGS );
    strcat( text, "=" );
    strcat( text, byte_buf );
    
    lteiot2_send_cmd( ctx, text );
    memset( text, 0, SMS_MAX_PDU_LENGTH );
    
    for ( int16_t cnt = 0; cnt < pdu_buf_len; cnt++ ) 
    {
        uint8_to_hex ( pdu_buf[ cnt ], byte_buf );
        strcat ( text, byte_buf );
    }
    strcat( text, ctrl_z );
    
    lteiot2_send_cmd( ctx, text );
    
    return LTEIOT2_OK;
}

lteiot2_error_t lteiot2_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
)
{    
    char * __generic start_rsp;
    char * __generic end_rsp;
    char rsp_buf[ 200 ];
    
    uint8_t element_cnt = 0;
    char * __generic element_start;
    char * __generic element_end;
    
    char current_cmd_buf[ 10 ];
    
    // check command and element
    if ( check_support_command( command, element, current_cmd_buf ) != 0 )
    {
        return LTEIOT2_ERROR_COMMAND_OR_ELEMENT;
    }
    
    start_rsp = strstr( rsp, current_cmd_buf );
    end_rsp = strstr( start_rsp + 1 , "OK" );
    
    if ( ( end_rsp != 0 ) && ( start_rsp != 0 ) )
    {
        strncpy( rsp_buf, start_rsp, end_rsp - start_rsp );
        element_start = rsp_buf;
        
        while ( element_cnt++ < element )
        {
            element_start = strstr( element_start, "," );
            if ( element_start != 0 )
            {
                element_start++;
            }
        }
        element_end = strstr( element_start, "," );
        
        if ( ( element_start != 0 ) && ( element_end != 0 ) )
        {
            strncpy( parser_buf, element_start, element_end - element_start );
        }
    }
    else
    {
        return LTEIOT2_ERROR_START_OR_END_COMMAND;
    }
    
    return LTEIOT2_NO_ERROR;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t check_support_command ( uint8_t command, uint8_t element, char *command_buf )
{
    switch ( command )
    {
        case LTEIOT2_NMEA_GPGGA:
        {
            strcpy( command_buf, "+QGPSGNMEA" );
            if ( element > LTEIOT2_NMEA_GPGGA_NUM_ELEMENT )
            {
                return PARSER_ELEMENT_NOT_SUPPORTED;
            }
            return PARSER_READY;
        }
        default:
        {
            return PARSER_COMMAND_NOT_SUPPORTED;
        }
    }
}

static int16_t pdu_encode( char *service_center_number, char *phone_number, char *sms_text,
                           uint8_t *output_buffer, uint16_t buffer_size )
{
    if ( buffer_size < 2 )
    {
        return LTEIOT2_ERROR;
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
            return LTEIOT2_ERROR;
        }
        length++;
    }
    output_buffer[ 0 ] = length;
    output_buffer_length = length + 1;
    if ( output_buffer_length + 4 > buffer_size )
    {
        return LTEIOT2_ERROR;  // Check if it has space for four more bytes.
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
        return LTEIOT2_ERROR;  // Check if it has space for four more bytes.
    }

    // 4. Protocol identifiers.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-PID: Protocol identifier.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-DCS: Data coding scheme.
    output_buffer[ output_buffer_length++ ] = 0xB0;  // TP-VP: Validity: 10 days

    // 5. SMS message.
    int16_t sms_text_length = strlen( sms_text );
    if ( sms_text_length > SMS_MAX_7BIT_TEXT_LENGTH )
    {
        return LTEIOT2_ERROR;
    }
    output_buffer[ output_buffer_length++ ] = sms_text_length;
    length = encode_pdu_message( sms_text, sms_text_length, output_buffer + output_buffer_length, 
                                                            buffer_size - output_buffer_length );
    if ( length < 0 )
    {
        return LTEIOT2_ERROR;
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
        return LTEIOT2_ERROR;

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
        return LTEIOT2_ERROR;
    }

    int16_t i = 0;
    for ( ; i < phone_number_length; ++i ) 
    {
        if ( phone_number[ i ] < '0' && phone_number[ i ] > '9' )
        {
            return LTEIOT2_ERROR;
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

