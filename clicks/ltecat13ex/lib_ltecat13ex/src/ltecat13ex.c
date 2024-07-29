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
 * @file ltecat13ex.c
 * @brief LTE Cat.1 3 EX Click Driver.
 */

#include "ltecat13ex.h"
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
 * @brief LTE Cat.1 3 EX str cut chr function.
 * @details This function removes all selected characters from string str,
 * and returns it to the same str without those characters.
 * @param str Address of string.
 * @param chr Character to cut.
 */
static void ltecat13ex_str_cut_chr ( uint8_t *str, uint8_t chr );

void ltecat13ex_cfg_setup ( ltecat13ex_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->pwr = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->ri  = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LTECAT13EX_ADDRESS;
}

err_t ltecat13ex_init ( ltecat13ex_t *ctx, ltecat13ex_cfg_t *cfg ) 
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

    i2c_master_config_t i2c_cfg;   
    
    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    
    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    // Output pins
    digital_out_init( &ctx->pwr, cfg->pwr );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins
    digital_in_init( &ctx->ri, cfg->ri );
    digital_in_init( &ctx->cts, cfg->cts );

    digital_out_low( &ctx->pwr );

    return UART_SUCCESS;
}

err_t ltecat13ex_generic_write ( ltecat13ex_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t ltecat13ex_generic_read ( ltecat13ex_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void ltecat13ex_start_up ( ltecat13ex_t *ctx )
{
    ltecat13ex_set_pwr_pin( ctx, LTECAT13EX_PIN_STATE_HIGH );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    ltecat13ex_set_pwr_pin( ctx, LTECAT13EX_PIN_STATE_LOW );
}

void ltecat13ex_set_pwr_pin ( ltecat13ex_t *ctx, uint8_t pin_state )
{
    if ( LTECAT13EX_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->pwr );
    }
    else
    {
        digital_out_low( &ctx->pwr );
    }
}

void ltecat13ex_set_rts_pin ( ltecat13ex_t *ctx, uint8_t pin_state )
{
    if ( LTECAT13EX_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rts );
    }
    else
    {
        digital_out_low( &ctx->rts );
    }
}

uint8_t ltecat13ex_get_ri_pin ( ltecat13ex_t *ctx )
{
    return digital_in_read( &ctx->ri );
}

uint8_t ltecat13ex_get_cts_pin ( ltecat13ex_t *ctx )
{
    return digital_in_read( &ctx->cts );
}

err_t ltecat13ex_write_register ( ltecat13ex_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tmp_data[ 2 ] = { 0 };
    
    tmp_data[ 0 ] = reg;
    tmp_data[ 1 ] = data_in;
    
    return i2c_master_write( &ctx->i2c, tmp_data, 2 );
}

err_t ltecat13ex_read_register ( ltecat13ex_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t tmp_data[ 1 ] = { 0 };
    
    tmp_data[ 0 ] = reg;
    
    return i2c_master_write_then_read( &ctx->i2c, tmp_data, 1, data_out, 1 );
}

err_t ltecat13ex_max9860_cfg ( ltecat13ex_t *ctx ) 
{
    err_t error_flag = LTECAT13EX_OK;
    
    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_SYS_SHUTDOWN, LTECAT13EX_POWER_ON | 
                                                                                   LTECAT13EX_DAC_ENABLE | LTECAT13EX_ADCL_ADCR_ENABLE );
    
    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_SYS_CLK, LTECAT13EX_PSCLK_24MHZ );    
    
    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_STEREO_CLK_MSB, LTECAT13EX_LRCLK_8MHZ_MSB );
    
    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_STEREO_CLK_LSB, LTECAT13EX_LRCLK_8MHZ_LSB );
    
    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_AUDIO_INTERFACE_1, LTECAT13EX_DBCI_FALLING_EDGE | 
                                                                                        LTECAT13EX_HIZ_ENABLE | LTECAT13EX_TDM_ENABLE );
    
    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_AUDIO_INTERFACE_2, LTECAT13EX_ABCI_FALLING_EDGE | 
                                                                                        LTECAT13EX_ADLY_ENABLE | LTECAT13EX_STEREO_ENABLE );
    
    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_VOICE_FILTER, LTECAT13EX_AVFLT_DISABLE | LTECAT13EX_DVFLT_DISABLE );
    
    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_DAC_ATTENUATION, LTECAT13EX_DVA_GAIN_0 );

    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_ADC_OUTPUT_LEVELS, LTECAT13EX_ADC_GAIN_3 | LTECAT13EX_DAC_GAIN_0 );
    
    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_DAC_GAIN, LTECAT13EX_DVST_GAIN_0 );

    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_MIC_GAIN, LTECAT13EX_MIC_GAIN_0 | LTECAT13EX_PGAM_GAIN_0 );

    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_MIC_AGC, LTECAT13EX_AGCSRC_ENABLE );

    error_flag |= ltecat13ex_write_register( ctx, LTECAT13EX_MAX9860_REG_NOISE_GATE, LTECAT13EX_ANTH_DISABLE | LTECAT13EX_AGCTH_MINUS_3 );
    
    return error_flag;
}


void ltecat13ex_send_cmd ( ltecat13ex_t *ctx, uint8_t *cmd )
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

void ltecat13ex_send_cmd_with_params ( ltecat13ex_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    ltecat13ex_send_cmd( ctx, final_cmd );
}

void ltecat13ex_send_cmd_check ( ltecat13ex_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    ltecat13ex_send_cmd( ctx, final_cmd );
}

void ltecat13ex_send_cmd_param_check ( ltecat13ex_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 3 ] = { '=' , '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    ltecat13ex_send_cmd( ctx, final_cmd );
}

void ltecat13ex_set_sim_apn ( ltecat13ex_t *ctx, uint8_t *sim_apn )
{
    uint8_t final_cmd[ 50 ] = "1,\"IP\",\"";
    uint8_t end_cmd[ 3 ] = "\"";
    
    strcat( final_cmd, sim_apn );
    strcat( final_cmd, end_cmd );
    
    ltecat13ex_send_cmd_with_params( ctx, LTECAT13EX_CMD_CGDCONT, final_cmd );
}

void ltecat13ex_send_sms_text ( ltecat13ex_t *ctx, uint8_t *phone_number, uint8_t *sms_text )
{
    uint8_t text[ 200 ] = { 0 };
    uint8_t cmd_start[ ] = "=\"";
    uint8_t cmd_end[ ] = "\"\r";
    uint8_t txt_end[ ] = "\032";
    
    strcpy( text, LTECAT13EX_CMD_CMGS );
    strcat( text, cmd_start );
    strcat( text, phone_number );
    strcat( text, cmd_end );
    
    ltecat13ex_send_cmd( ctx, text );
    memset( text, 0 , 200 );
    
    strcpy( text, sms_text );
    strcat( text, txt_end );
    ltecat13ex_send_cmd( ctx, text );
}

err_t ltecat13ex_send_sms_pdu ( ltecat13ex_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text )
{
    uint8_t text[ SMS_MAX_PDU_LENGTH ] = { 0 };
    uint8_t pdu_buf[ SMS_MAX_PDU_LENGTH ] = { 0 };
    uint8_t byte_buf[ 4 ] = { 0 };
    uint8_t ctrl_z[ ] = { 26, 0 };
    int16_t pdu_buf_len;
    uint8_t length;
    uint8_t smsc[ 32 ] = { 0 };
    uint8_t phone_num[ 32 ] = { 0 };
    strcpy ( smsc, service_center_number );
    strcpy ( phone_num, phone_number );
    ltecat13ex_str_cut_chr ( smsc, '+' );
    ltecat13ex_str_cut_chr ( phone_num, '+' );
    
    pdu_buf_len = pdu_encode( smsc, phone_num, sms_text, pdu_buf, SMS_MAX_PDU_LENGTH );
    
    if ( pdu_buf_len < 0 )
    {
        return LTECAT13EX_ERROR;
    }
    
    length = pdu_buf_len - ( ( strlen( smsc ) - 1 ) / 2 + 3 );
    uint8_to_str( length, byte_buf );
    ltecat13ex_str_cut_chr ( byte_buf, ' ' );
    
    strcpy( text, LTECAT13EX_CMD_CMGS );
    strcat( text, "=" );
    strcat( text, byte_buf );
    Delay_10ms(  );
    
    ltecat13ex_send_cmd( ctx, text );
    memset( text, 0, SMS_MAX_PDU_LENGTH );
    
    for ( int16_t cnt = 0; cnt < pdu_buf_len; cnt++ ) 
    {
        uint8_to_hex ( pdu_buf[ cnt ], byte_buf );
        strcat ( text, byte_buf );
    }
    strcat( text, ctrl_z );
    
    ltecat13ex_send_cmd( ctx, text );
    ltecat13ex_send_cmd( ctx, ctrl_z );
    
    return LTECAT13EX_OK;
}

static int16_t pdu_encode( uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text,
                           uint8_t *output_buffer, uint16_t buffer_size )
{
    if ( buffer_size < 2 )
    {
        return LTECAT13EX_ERROR;
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
            return LTECAT13EX_ERROR;
        }
        length++;
    }
    output_buffer[ 0 ] = length;
    output_buffer_length = length + 1;
    if ( output_buffer_length + 4 > buffer_size )
    {
        return LTECAT13EX_ERROR;  // Check if it has space for four more bytes.
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
        return LTECAT13EX_ERROR;  // Check if it has space for four more bytes.
    }

    // 4. Protocol identifiers.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-PID: Protocol identifier.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-DCS: Data coding scheme.
    output_buffer[ output_buffer_length++ ] = 0xB0;  // TP-VP: Validity: 10 days

    // 5. SMS message.
    int16_t sms_text_length = strlen( sms_text );
    if ( sms_text_length > SMS_MAX_7BIT_TEXT_LENGTH )
    {
        return LTECAT13EX_ERROR;
    }
    output_buffer[ output_buffer_length++ ] = sms_text_length;
    length = encode_pdu_message( sms_text, sms_text_length, output_buffer + output_buffer_length, 
                                                            buffer_size - output_buffer_length );
    if ( length < 0 )
    {
        return LTECAT13EX_ERROR;
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
        return LTECAT13EX_ERROR;
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
        return LTECAT13EX_ERROR;
    }

    int16_t i = 0;
    for ( ; i < phone_number_length; ++i ) 
    {
        if ( phone_number[ i ] < '0' && phone_number[ i ] > '9' )
        {
            return LTECAT13EX_ERROR;
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

err_t ltecat13ex_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data )
{    
    if ( gpgga_element > LTECAT13EX_GPGGA_ELEMENT_SIZE )
    {
        return LTECAT13EX_ERROR;
    }
    char * __generic_ptr start_ptr = strstr( rsp_buf, LTECAT13EX_RSP_GPGGA );
    if ( start_ptr )
    {
        if ( strstr( start_ptr + 1, LTECAT13EX_RSP_START ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gpgga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, LTECAT13EX_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return LTECAT13EX_ERROR;
                }
            }
            char * __generic_ptr end_ptr = strstr( start_ptr, LTECAT13EX_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return LTECAT13EX_OK;
            }
        }
    }
    return LTECAT13EX_ERROR;
}

static void ltecat13ex_str_cut_chr ( uint8_t *str, uint8_t chr )
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
