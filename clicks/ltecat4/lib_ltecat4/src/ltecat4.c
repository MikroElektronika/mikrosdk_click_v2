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
 * @file ltecat4.c
 * @brief LTE Cat.4 Click Driver.
 */

#include "ltecat4.h"
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
 * @brief LTE Cat.4 str cut chr function.
 * @details This function removes all selected characters from string str,
 * and returns it to the same str without those characters.
 * @param str Address of string.
 * @param chr Character to cut.
 */
static void ltecat4_str_cut_chr ( uint8_t *str, uint8_t chr );

void ltecat4_cfg_setup ( ltecat4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
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

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = LTECAT4_DEVICE_ADDRESS;
}

err_t ltecat4_init ( ltecat4_t *ctx, ltecat4_cfg_t *cfg ) 
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
    digital_out_low( &ctx->pwr );
    digital_out_low( &ctx->rts );

    // Input pins
    digital_in_init( &ctx->ring, cfg->ring );
    digital_in_init( &ctx->cts, cfg->cts );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );

    return LTECAT4_OK;
}

err_t ltecat4_write_register ( ltecat4_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tmp_data[ 2 ] = { 0 };
    tmp_data[ 0 ] = reg;
    tmp_data[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, tmp_data, 2 );
}

err_t ltecat4_read_register ( ltecat4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t ltecat4_config_codec ( ltecat4_t *ctx ) 
{
    err_t error_flag = LTECAT4_OK;
    
    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_SYS_SHUTDOWN, 
                                          LTECAT4_POWER_ON | LTECAT4_DAC_ENABLE | LTECAT4_ADCL_ADCR_ENABLE );
    
    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_SYS_CLK, LTECAT4_PSCLK_24MHZ );    
    
    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_STEREO_CLK_MSB, LTECAT4_LRCLK_8MHZ_MSB );
    
    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_STEREO_CLK_LSB, LTECAT4_LRCLK_8MHZ_LSB );
    
    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_AUDIO_INTERFACE_1, 
                                          LTECAT4_DBCI_FALLING_EDGE | LTECAT4_HIZ_ENABLE | LTECAT4_TDM_ENABLE );
    
    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_AUDIO_INTERFACE_2, 
                                          LTECAT4_ABCI_FALLING_EDGE | LTECAT4_ADLY_ENABLE | LTECAT4_STEREO_ENABLE );
    
    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_VOICE_FILTER, 
                                          LTECAT4_AVFLT_DISABLE | LTECAT4_DVFLT_DISABLE );
    
    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_DAC_ATTENUATION, LTECAT4_DVA_GAIN_0 );

    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_ADC_OUTPUT_LEVELS, 
                                          LTECAT4_ADC_GAIN_3 | LTECAT4_DAC_GAIN_0 );
    
    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_DAC_GAIN, LTECAT4_DVST_GAIN_0 );

    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_MIC_GAIN, 
                                          LTECAT4_MIC_GAIN_30 | LTECAT4_PGAM_GAIN_20 );

    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_MIC_AGC, 
                                          LTECAT4_AGCSRC_ENABLE | LTECAT4_AGCHLD_50 );

    error_flag |= ltecat4_write_register( ctx, LTECAT4_MAX9860_REG_NOISE_GATE, 
                                          LTECAT4_ANTH_DISABLE | LTECAT4_AGCTH_MINUS_3 );
    
    Delay_1sec ( );
    Delay_1sec ( );
    return error_flag;
}

err_t ltecat4_generic_write ( ltecat4_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t ltecat4_generic_read ( ltecat4_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void ltecat4_set_pwr_pin ( ltecat4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->pwr, state );
}

void ltecat4_set_rts_pin ( ltecat4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rts, state );
}

uint8_t ltecat4_get_ring_pin ( ltecat4_t *ctx )
{
    return digital_in_read ( &ctx->ring );
}

uint8_t ltecat4_get_cts_pin ( ltecat4_t *ctx )
{
    return digital_in_read ( &ctx->cts );
}

void ltecat4_set_power_state ( ltecat4_t *ctx, uint8_t state )
{
    if ( LTECAT4_POWER_STATE_OFF == state )
    {
        digital_out_high ( &ctx->pwr );
        Delay_1sec ( );
        digital_out_low ( &ctx->pwr );
        for ( uint8_t delay_cnt = 0; delay_cnt < 30; delay_cnt++ )
        {
            Delay_1sec ( );
        }
    }
    else if ( LTECAT4_POWER_STATE_ON == state )
    {
        digital_out_high ( &ctx->pwr );
        Delay_100ms ( );
        Delay_100ms ( );
        Delay_100ms ( );
        Delay_100ms ( );
        Delay_100ms ( );
        digital_out_low ( &ctx->pwr );
        for ( uint8_t delay_cnt = 0; delay_cnt < 15; delay_cnt++ )
        {
            Delay_1sec ( );
        }
    }
}

void ltecat4_send_cmd ( ltecat4_t *ctx, uint8_t *cmd )
{
    uint8_t carriage_return[ 2 ] = { '\r', 0 };
    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, carriage_return );
    ltecat4_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
    Delay_100ms(  );
}

void ltecat4_send_cmd_par ( ltecat4_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };
    
    strcpy( ctx->cmd_buffer, at_cmd_buf );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, param_buf );
    
    ltecat4_send_cmd( ctx, ctx->cmd_buffer );
}

void ltecat4_send_cmd_check ( ltecat4_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t check_char[ 2 ] = { '?', 0 };
    
    strcpy( ctx->cmd_buffer, at_cmd_buf );
    strcat( ctx->cmd_buffer, check_char );
    
    ltecat4_send_cmd( ctx, ctx->cmd_buffer );
}

void ltecat4_set_sim_apn ( ltecat4_t *ctx, uint8_t *sim_apn )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };
    uint8_t quotation_char[ 2 ] = { '\"', 0 };
    
    strcpy( ctx->cmd_buffer, LTECAT4_CMD_DEFINE_PDP_CONTEXT );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, "1,\"IP\",\"" );
    strcat( ctx->cmd_buffer, sim_apn );
    strcat( ctx->cmd_buffer, quotation_char );
    
    ltecat4_send_cmd( ctx, ctx->cmd_buffer );
}

void ltecat4_send_sms_text ( ltecat4_t *ctx, uint8_t *phone_number, uint8_t *sms_text )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };
    uint8_t quotation_char[ 2 ] = { '\"', 0 };
    uint8_t ctrl_z[ 2 ] = { 26, 0 };
    
    strcpy( ctx->cmd_buffer, LTECAT4_CMD_SEND_SMS );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, quotation_char );
    strcat( ctx->cmd_buffer, phone_number );
    strcat( ctx->cmd_buffer, quotation_char );
    
    ltecat4_send_cmd( ctx, ctx->cmd_buffer );
    Delay_1sec ( );
    
    strcpy( ctx->cmd_buffer, sms_text );
    strcat( ctx->cmd_buffer, ctrl_z );
    ltecat4_send_cmd( ctx, ctx->cmd_buffer );
}

err_t ltecat4_send_sms_pdu ( ltecat4_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text )
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
    ltecat4_str_cut_chr ( smsc, '+' );
    ltecat4_str_cut_chr ( phone_num, '+' );
    
    pdu_buf_len = pdu_encode( smsc, phone_num, sms_text, pdu_buf, SMS_MAX_PDU_LENGTH );
    
    if ( pdu_buf_len < 0 )
    {
        return LTECAT4_ERROR;
    }
    
    length = pdu_buf_len - ( ( strlen( smsc ) - 1 ) / 2 + 3 );
    uint8_to_str( length, byte_buf );
    ltecat4_str_cut_chr ( byte_buf, ' ' );
    
    ltecat4_send_cmd_par( ctx, LTECAT4_CMD_SEND_SMS, byte_buf );
    Delay_1sec ( );
    memset( ctx->cmd_buffer, 0, sizeof ( ctx->cmd_buffer ) );
    
    for ( int16_t cnt = 0; cnt < pdu_buf_len; cnt++ ) 
    {
        uint8_to_hex ( pdu_buf[ cnt ], byte_buf );
        strcat ( ctx->cmd_buffer, byte_buf );
    }
    strcat( ctx->cmd_buffer, ctrl_z );
    
    ltecat4_send_cmd( ctx, ctx->cmd_buffer );
    
    return LTECAT4_OK;
}

void ltecat4_dial_number ( ltecat4_t *ctx, uint8_t *phone_number )
{
    uint8_t set_call[ 2 ] = { ';', 0 };
    
    strcpy( ctx->cmd_buffer, LTECAT4_CMD_DIAL_NUMBER );
    strcat( ctx->cmd_buffer, phone_number );
    strcat( ctx->cmd_buffer, set_call );
    
    ltecat4_send_cmd( ctx, ctx->cmd_buffer );
}

err_t ltecat4_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data )
{
    if ( gga_element > LTECAT4_GGA_ELEMENT_SIZE )
    {
        return LTECAT4_ERROR;
    }
    uint8_t * __generic_ptr start_ptr = strstr( rsp_buf, LTECAT4_RSP_GGA );
    if ( start_ptr )
    {
        if ( strstr( start_ptr, ( char * ) LTECAT4_RSP_END ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, LTECAT4_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return LTECAT4_ERROR;
                }
            }
            uint8_t * __generic_ptr end_ptr = strstr( start_ptr, LTECAT4_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return LTECAT4_OK;
            }
        }
    }
    return LTECAT4_ERROR;
}

static int16_t pdu_encode( uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text,
                           uint8_t *output_buffer, uint16_t buffer_size )
{
    if ( buffer_size < 2 )
    {
        return LTECAT4_ERROR;
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
            return LTECAT4_ERROR;
        }
        length++;
    }
    output_buffer[ 0 ] = length;
    output_buffer_length = length + 1;
    if ( output_buffer_length + 4 > buffer_size )
    {
        return LTECAT4_ERROR;  // Check if it has space for four more bytes.
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
        return LTECAT4_ERROR;  // Check if it has space for four more bytes.
    }

    // 4. Protocol identifiers.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-PID: Protocol identifier.
    output_buffer[ output_buffer_length++ ] = 0x00;  // TP-DCS: Data coding scheme.
    output_buffer[ output_buffer_length++ ] = 0xB0;  // TP-VP: Validity: 10 days

    // 5. SMS message.
    int16_t sms_text_length = strlen( sms_text );
    if ( sms_text_length > SMS_MAX_7BIT_TEXT_LENGTH )
    {
        return LTECAT4_ERROR;
    }
    output_buffer[ output_buffer_length++ ] = sms_text_length;
    length = encode_pdu_message( sms_text, sms_text_length, output_buffer + output_buffer_length, 
                                                            buffer_size - output_buffer_length );
    if ( length < 0 )
    {
        return LTECAT4_ERROR;
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
        return LTECAT4_ERROR;
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
        return LTECAT4_ERROR;
    }

    int16_t i = 0;
    for ( ; i < phone_number_length; ++i ) 
    {
        if ( phone_number[ i ] < '0' && phone_number[ i ] > '9' )
        {
            return LTECAT4_ERROR;
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

static void ltecat4_str_cut_chr ( uint8_t *str, uint8_t chr )
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
