/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file nfctag.c
 * @brief NFC Tag Click Driver.
 */

#include "nfctag.h"

#define NFCTAG_I2C_CLOCK_RETRIES               100  // One 10 us wait per attempt.
#define NFCTAG_I2C_READ_BIT                    0x01u

/**
 * @brief NFC Tag drive bus line function.
 * @details This function preloads the GPIO output latch, then configures the pin as an output and drives it low.
 * @param[in] line : Initialized GPIO input object.
 * @param[in] pin : Pin descriptor.
 * @return GPIO initialization result.
 * @note None.
 */
static err_t nfctag_clear_line ( digital_in_t *line, pin_name_t pin );

/**
 * @brief NFC Tag release SCL function.
 * @details This function releases SCL and waits for the pull-up to raise it.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note None.
 */
static err_t nfctag_set_scl ( nfctag_t *ctx );

/**
 * @brief NFC Tag I2C START function.
 * @details This function sends a START condition on an idle I2C bus.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note None.
 */
static err_t nfctag_i2c_start ( nfctag_t *ctx );

/**
 * @brief NFC Tag I2C STOP function.
 * @details This function sends a STOP condition and releases both bus pins.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note SCL must be held low on entry.
 */
static err_t nfctag_i2c_stop ( nfctag_t *ctx );

/**
 * @brief NFC Tag I2C write bit function.
 * @details This function drives SDA low or releases it before pulsing SCL.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] data_in : Zero for a low level, nonzero for a high level.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note None.
 */
static err_t nfctag_i2c_write_bit ( nfctag_t *ctx, uint8_t data_in );

/**
 * @brief NFC Tag I2C read bit function.
 * @details This function samples SDA during the SCL high period.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[out] data_out : Received logic level.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note None.
 */
static err_t nfctag_i2c_read_bit ( nfctag_t *ctx, uint8_t *data_out );

/**
 * @brief NFC Tag I2C write byte function.
 * @details This function writes a byte and checks the receiver ACK.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] data_in : Byte to send.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note None.
 */
static err_t nfctag_i2c_write_byte ( nfctag_t *ctx, uint8_t data_in );

/**
 * @brief NFC Tag I2C read byte function.
 * @details This function reads a byte and sends ACK or NACK.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[out] data_out : Received byte.
 * @param[in] nack : 0 to acknowledge or 1 to end the read.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note None.
 */
static err_t nfctag_i2c_read_byte ( nfctag_t *ctx, uint8_t *data_out, uint8_t nack );

/**
 * @brief NFC Tag I2C write function.
 * @details This function writes a complete command in a single START to STOP transaction.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] data_in : Command buffer.
 * @param[in] len : Number of command bytes.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note None.
 */
static err_t nfctag_i2c_write ( nfctag_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NFC Tag I2C read function.
 * @details This function reads the requested number of bytes in a single START to STOP transaction.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[out] data_out : Response buffer.
 * @param[in] len : Number of response bytes to clock.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note None.
 */
static err_t nfctag_i2c_read ( nfctag_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NFC Tag CRC calculation function.
 * @details This function calculates ISO/IEC 14443 CRC-A over the frame bytes, excluding the I2C address.
 * @param[in] buffer : Frame bytes.
 * @param[in] len : Number of frame bytes.
 * @return CRC value, transmitted least significant byte first.
 * @note The initial value is 0x6363; the result is not inverted.
 */
static uint16_t nfctag_calc_crc ( uint8_t *buffer, uint16_t len );

/**
 * @brief NFC Tag command exchange function.
 * @details This function adds the PCB and CRC to the command, receives a response,
 * and handles waiting time extensions.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in,out] command : Frame buffer with space for PCB and two CRC bytes.
 * @param[in] len : Frame length excluding CRC, including PCB.
 * @param[out] data_out : Response payload buffer, or NULL for status-only commands.
 * @param[in] read_len : Expected payload length.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note A transport error requires session release before another command.
 */
static err_t nfctag_exchange ( nfctag_t *ctx, uint8_t *command, uint16_t len,
                               uint8_t *data_out, uint8_t read_len );

/**
 * @brief NFC Tag binary read function.
 * @details This function reads bytes from the selected file using the specified ReadBinary command class.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] offset : Byte offset in the selected file.
 * @param[out] data_out : Output buffer.
 * @param[in] len : Number of bytes to read.
 * @param[in] command_class : Standard or ST command class.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note The caller owns the I2C session.
 */
static err_t nfctag_read_file ( nfctag_t *ctx, uint16_t offset, uint8_t *data_out,
                                uint8_t len, uint8_t command_class );

/**
 * @brief NFC Tag write and verify block function.
 * @details This function writes a portion of the NFC Tag Click NDEF file and compares its readback with the input data.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] offset : Byte offset in the NDEF file.
 * @param[in] data_in : Input buffer.
 * @param[in] len : Number of bytes.
 * @param[out] stage : Failed write or verification step. May be NULL.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note Extended reads allow verification while NLEN is zero.
 */
static err_t nfctag_write_verify_block ( nfctag_t *ctx, uint16_t offset, uint8_t *data_in,
                                         uint8_t len, nfctag_ndef_stage_t *stage );

/**
 * @brief NFC Tag write NDEF record function.
 * @details This function stores and verifies a complete NDEF record in the NFC Tag Click Type 4 NDEF file.
 * @param[in,out] ctx : Click context object.
 * See #nfctag_t object definition for detailed explanation.
 * @param[in] record : NDEF message without NLEN, TLV, or terminator bytes.
 * @param[in] record_len : Number of NDEF message bytes.
 * @param[out] stage : Failure stage for diagnostics, or NFCTAG_NDEF_STAGE_OK on success. May be NULL.
 * @return See #nfctag_return_value_t for detailed explanation.
 * @note Attempts to release the session after every successful acquisition, including when an operation fails.
 */
static err_t nfctag_write_ndef_record ( nfctag_t *ctx, uint8_t *record, uint16_t record_len,
                                        nfctag_ndef_stage_t *stage );

void nfctag_cfg_setup ( nfctag_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dis = HAL_PIN_NC;
    cfg->gpo = HAL_PIN_NC;

    cfg->i2c_address = NFCTAG_DEVICE_ADDRESS;
}

err_t nfctag_init ( nfctag_t *ctx, nfctag_cfg_t *cfg )
{
    err_t error_flag = NFCTAG_OK;

    ctx->slave_address = cfg->i2c_address;
    ctx->scl = cfg->scl;
    ctx->sda = cfg->sda;
    ctx->block_number = 0;
    ctx->session_active = 0;
    ctx->last_status = 0;
    ctx->uid_stage = NFCTAG_UID_STAGE_OK;

    if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->scl_in, ctx->scl ) )
    {
        error_flag = NFCTAG_ERROR;
    }
    else if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->sda_in, ctx->sda ) )
    {
        error_flag = NFCTAG_ERROR;
    }
    else if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_init( &ctx->dis, cfg->dis ) )
    {
        error_flag = NFCTAG_ERROR;
    }
    else if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->gpo, cfg->gpo ) )
    {
        error_flag = NFCTAG_ERROR;
    }
    else
    {
        digital_out_low( &ctx->dis );
    }

    return error_flag;
}

err_t nfctag_default_cfg ( nfctag_t *ctx )
{
    err_t error_flag;
    err_t release_status;

    nfctag_set_rf_disable( ctx, NFCTAG_RF_ENABLE );
    // Clear an I2C token left behind by an MCU-only reset.
    error_flag = nfctag_release_i2c( ctx );
    if ( NFCTAG_OK == error_flag )
    {
        error_flag = nfctag_get_session( ctx );
        if ( NFCTAG_OK == error_flag )
        {
            error_flag = nfctag_select_application( ctx );
            release_status = nfctag_release_i2c( ctx );
            if ( NFCTAG_OK == error_flag )
            {
                error_flag = release_status;
            }
        }
    }
    return error_flag;
}

err_t nfctag_get_session ( nfctag_t *ctx )
{
    uint8_t command = NFCTAG_CMD_GET_SESSION;
    err_t error_flag = NFCTAG_ERROR;

    if ( ( 0 == ctx->session_active ) && ( NFCTAG_BLOCK_INVALID != ctx->block_number ) )
    {
        ctx->last_status = 0;
        error_flag = nfctag_i2c_write( ctx, &command, 1 );
        if ( NFCTAG_OK == error_flag )
        {
            ctx->block_number = 0;
            ctx->session_active = 1;
            // GetSession has no response frame; allow internal session setup.
            Delay_10ms( );
        }
        else
        {
            // A failed transfer can leave the tag token in an unknown state.
            nfctag_release_i2c( ctx );
        }
    }
    return error_flag;
}

err_t nfctag_release_i2c ( nfctag_t *ctx )
{
    err_t error_flag;

    if ( NFCTAG_BLOCK_INVALID == ctx->block_number )
    {
        // A failed transfer may have started the device's 90 ms maximum EEPROM write.
        Delay_100ms( );
    }

    error_flag = nfctag_i2c_start( ctx );
    if ( NFCTAG_OK == error_flag )
    {
        // DocID023790 section 7.4: delay the first clock edge beyond the 40 ms maximum.
        Delay_100ms( );
        error_flag = nfctag_i2c_stop( ctx );
    }

    if ( NFCTAG_OK == error_flag )
    {
        ctx->session_active = 0;
        ctx->block_number = 0;
    }
    else
    {
        ctx->block_number = NFCTAG_BLOCK_INVALID;
    }
    return error_flag;
}

err_t nfctag_select_application ( nfctag_t *ctx )
{
    uint8_t command[ 16 ] = { 0, NFCTAG_CLA_STANDARD, NFCTAG_CMD_SELECT, 0x04, 0x00, 0x07,
                              0xD2, 0x76, 0x00, 0x00, 0x85, 0x01, 0x01, 0x00, 0, 0 };

    return nfctag_exchange( ctx, command, sizeof( command ) - NFCTAG_CRC_SIZE, NULL, 0 );
}

err_t nfctag_select_file ( nfctag_t *ctx, uint16_t file_id )
{
    uint8_t command[ 10 ] = { 0, NFCTAG_CLA_STANDARD, NFCTAG_CMD_SELECT, 0x00, 0x0C, 0x02, 0, 0, 0, 0 };

    command[ 6 ] = ( uint8_t ) ( file_id >> 8 );
    command[ 7 ] = ( uint8_t ) file_id;
    return nfctag_exchange( ctx, command, sizeof( command ) - NFCTAG_CRC_SIZE, NULL, 0 );
}

err_t nfctag_read_binary ( nfctag_t *ctx, uint16_t offset, uint8_t *data_out, uint8_t len )
{
    return nfctag_read_file( ctx, offset, data_out, len, NFCTAG_CLA_STANDARD );
}

err_t nfctag_read_binary_ext ( nfctag_t *ctx, uint16_t offset, uint8_t *data_out, uint8_t len )
{
    return nfctag_read_file( ctx, offset, data_out, len, NFCTAG_CLA_EXTENDED );
}

err_t nfctag_update_binary ( nfctag_t *ctx, uint16_t offset, uint8_t *data_in, uint8_t len )
{
    uint8_t command[ NFCTAG_FRAME_SIZE ];
    err_t error_flag = NFCTAG_ERROR;

    if ( ( NULL != data_in ) && ( 0 != len ) && ( len <= NFCTAG_TRANSFER_MAX ) &&
         ( offset < NFCTAG_NDEF_FILE_SIZE ) && ( len <= NFCTAG_NDEF_FILE_SIZE - offset ) )
    {
        command[ 1 ] = NFCTAG_CLA_STANDARD;
        command[ 2 ] = NFCTAG_CMD_UPDATE_BINARY;
        command[ 3 ] = ( uint8_t ) ( offset >> 8 );
        command[ 4 ] = ( uint8_t ) offset;
        command[ 5 ] = len;
        memcpy( &command[ 6 ], data_in, len );
        error_flag = nfctag_exchange( ctx, command, ( uint16_t ) len + 6, NULL, 0 );
    }
    return error_flag;
}

err_t nfctag_get_uid ( nfctag_t *ctx, uint8_t *uid )
{
    err_t error_flag = NFCTAG_ERROR;
    err_t release_status;

    ctx->uid_stage = NFCTAG_UID_STAGE_BUFFER;
    ctx->last_status = 0;
    if ( NULL != uid )
    {
        ctx->uid_stage = NFCTAG_UID_STAGE_SESSION;
        error_flag = nfctag_get_session( ctx );
        if ( NFCTAG_OK == error_flag )
        {
            ctx->uid_stage = NFCTAG_UID_STAGE_APPLICATION;
            error_flag = nfctag_select_application( ctx );
            if ( NFCTAG_OK == error_flag )
            {
                ctx->uid_stage = NFCTAG_UID_STAGE_FILE;
                error_flag = nfctag_select_file( ctx, NFCTAG_FILE_SYSTEM );
            }
            if ( NFCTAG_OK == error_flag )
            {
                ctx->uid_stage = NFCTAG_UID_STAGE_READ;
                error_flag = nfctag_read_binary( ctx, NFCTAG_SYSTEM_UID, uid, NFCTAG_UID_SIZE );
            }
            release_status = nfctag_release_i2c( ctx );
            if ( NFCTAG_OK == error_flag )
            {
                error_flag = release_status;
                ctx->uid_stage = NFCTAG_UID_STAGE_RELEASE;
            }
        }
    }
    if ( NFCTAG_OK == error_flag )
    {
        ctx->uid_stage = NFCTAG_UID_STAGE_OK;
    }
    return error_flag;
}

err_t nfctag_write_ndef_text ( nfctag_t *ctx, char *text, nfctag_ndef_stage_t *stage )
{
    err_t error_flag = NFCTAG_ERROR;
    uint8_t record[ NFCTAG_NDEF_BUFFER_SIZE ] = { 0 };
    size_t text_len;

    if ( NULL != stage )
    {
        *stage = NFCTAG_NDEF_STAGE_INVALID_TEXT;
    }
    if ( NULL != text )
    {
        text_len = strlen( text );
        if ( text_len <= NFCTAG_NDEF_TEXT_MAX_LENGTH )
        {
            // Type 4 stores the short UTF-8 Text record directly, without a Type 2 TLV.
            record[ 0 ] = NFCTAG_NDEF_RECORD_HEADER;
            record[ 1 ] = 1;
            record[ 2 ] = ( uint8_t ) ( text_len + 3 );
            record[ 3 ] = NFCTAG_NDEF_TEXT_TYPE;
            record[ 4 ] = 2;
            record[ 5 ] = 'e';
            record[ 6 ] = 'n';
            memcpy( &record[ NFCTAG_NDEF_TEXT_OVERHEAD ], text, text_len );
            error_flag = nfctag_write_ndef_record( ctx, record, text_len + NFCTAG_NDEF_TEXT_OVERHEAD, stage );
        }
    }
    return error_flag;
}

err_t nfctag_write_ndef_uri ( nfctag_t *ctx, char *uri, nfctag_ndef_stage_t *stage )
{
    err_t error_flag = NFCTAG_ERROR;
    uint8_t record[ NFCTAG_NDEF_BUFFER_SIZE ] = { 0 };
    size_t uri_len;

    if ( NULL != stage )
    {
        *stage = NFCTAG_NDEF_STAGE_INVALID_URI;
    }
    if ( NULL != uri )
    {
        uri_len = strlen( uri );
        if ( ( 0 < uri_len ) && ( uri_len <= NFCTAG_NDEF_URI_MAX_LENGTH ) )
        {
            // URI RTD with prefix code 0 stores the supplied URI without abbreviation.
            record[ 0 ] = NFCTAG_NDEF_RECORD_HEADER;
            record[ 1 ] = 1;
            record[ 2 ] = ( uint8_t ) ( uri_len + 1 );
            record[ 3 ] = NFCTAG_NDEF_URI_TYPE;
            record[ 4 ] = NFCTAG_NDEF_URI_PREFIX_NONE;
            memcpy( &record[ NFCTAG_NDEF_URI_OVERHEAD ], uri, uri_len );
            error_flag = nfctag_write_ndef_record( ctx, record, uri_len + NFCTAG_NDEF_URI_OVERHEAD, stage );
        }
    }
    return error_flag;
}

void nfctag_set_rf_disable ( nfctag_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->dis, state );
}

uint8_t nfctag_get_gpo ( nfctag_t *ctx )
{
    return digital_in_read( &ctx->gpo );
}

static err_t nfctag_clear_line ( digital_in_t *line, pin_name_t pin )
{
    digital_out_t line_out;
    err_t error_flag;

    // Preload zero where supported to avoid a high pulse when enabling output.
    hal_gpio_clear_pin_output( &line->pin );
    error_flag = digital_out_init( &line_out, pin );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN != error_flag )
    {
        // Some GPIOs only accept writes in output mode.
        digital_out_low( &line_out );
    }
    return error_flag;
}

static err_t nfctag_set_scl ( nfctag_t *ctx )
{
    uint8_t retry = 0;
    err_t error_flag = digital_in_init( &ctx->scl_in, ctx->scl );

    if ( NFCTAG_OK == error_flag )
    {
        while ( ( retry < NFCTAG_I2C_CLOCK_RETRIES ) && ( 0 == digital_in_read( &ctx->scl_in ) ) )
        {
            Delay_10us( );
            retry++;
        }
        if ( 0 == digital_in_read( &ctx->scl_in ) )
        {
            error_flag = NFCTAG_TIMEOUT;
        }
    }
    return error_flag;
}

static err_t nfctag_i2c_start ( nfctag_t *ctx )
{
    err_t error_flag = NFCTAG_ERROR;

    if ( ( 0 != digital_in_read( &ctx->scl_in ) ) && ( 0 != digital_in_read( &ctx->sda_in ) ) )
    {
        error_flag = nfctag_clear_line( &ctx->sda_in, ctx->sda );
        if ( NFCTAG_OK == error_flag )
        {
            // START hold time with SCL high.
            Delay_10us( );
            if ( 0 == digital_in_read( &ctx->sda_in ) )
            {
                error_flag = nfctag_clear_line( &ctx->scl_in, ctx->scl );
                Delay_10us( );
                if ( ( NFCTAG_OK == error_flag ) && ( 0 != digital_in_read( &ctx->scl_in ) ) )
                {
                    error_flag = NFCTAG_ERROR;
                }
            }
            else
            {
                error_flag = NFCTAG_ERROR;
            }
        }
        if ( NFCTAG_OK != error_flag )
        {
            digital_in_init( &ctx->scl_in, ctx->scl );
            digital_in_init( &ctx->sda_in, ctx->sda );
        }
    }
    return error_flag;
}

static err_t nfctag_i2c_stop ( nfctag_t *ctx )
{
    err_t error_flag = nfctag_clear_line( &ctx->sda_in, ctx->sda );
    err_t line_status;

    Delay_10us( );
    line_status = nfctag_set_scl( ctx );
    if ( NFCTAG_OK == error_flag )
    {
        error_flag = line_status;
    }
    Delay_10us( );
    line_status = digital_in_init( &ctx->sda_in, ctx->sda );
    if ( NFCTAG_OK == error_flag )
    {
        error_flag = line_status;
    }
    // Leave enough bus free time for the next START.
    Delay_10us( );
    if ( ( NFCTAG_OK == error_flag ) && ( 0 == digital_in_read( &ctx->sda_in ) ) )
    {
        error_flag = NFCTAG_ERROR;
    }
    return error_flag;
}

static err_t nfctag_i2c_write_bit ( nfctag_t *ctx, uint8_t data_in )
{
    err_t error_flag;
    err_t line_status;

    if ( 0 != data_in )
    {
        error_flag = digital_in_init( &ctx->sda_in, ctx->sda );
    }
    else
    {
        error_flag = nfctag_clear_line( &ctx->sda_in, ctx->sda );
    }
    if ( NFCTAG_OK == error_flag )
    {
        Delay_10us( );
        error_flag = nfctag_set_scl( ctx );
        if ( NFCTAG_OK == error_flag )
        {
            Delay_10us( );
        if ( ( 0 != data_in ) && ( 0 == digital_in_read( &ctx->sda_in ) ) )
            {
                error_flag = NFCTAG_ERROR;
            }
        }
        line_status = nfctag_clear_line( &ctx->scl_in, ctx->scl );
        if ( NFCTAG_OK == error_flag )
        {
            error_flag = line_status;
        }
    }
    return error_flag;
}

static err_t nfctag_i2c_read_bit ( nfctag_t *ctx, uint8_t *data_out )
{
    err_t error_flag = digital_in_init( &ctx->sda_in, ctx->sda );
    err_t line_status;

    if ( NFCTAG_OK == error_flag )
    {
        Delay_10us( );
        error_flag = nfctag_set_scl( ctx );
        if ( NFCTAG_OK == error_flag )
        {
            Delay_10us( );
        *data_out = ( uint8_t ) ( 0 != digital_in_read( &ctx->sda_in ) );
        }
        line_status = nfctag_clear_line( &ctx->scl_in, ctx->scl );
        if ( NFCTAG_OK == error_flag )
        {
            error_flag = line_status;
        }
    }
    return error_flag;
}

static err_t nfctag_i2c_write_byte ( nfctag_t *ctx, uint8_t data_in )
{
    err_t error_flag = NFCTAG_OK;
    uint8_t nack;
    int8_t bit_cnt;

    for ( bit_cnt = 7; ( bit_cnt >= 0 ) && ( NFCTAG_OK == error_flag ); bit_cnt-- )
    {
        error_flag = nfctag_i2c_write_bit( ctx, ( data_in >> bit_cnt ) & 1u );
    }
    if ( NFCTAG_OK == error_flag )
    {
        error_flag = nfctag_i2c_read_bit( ctx, &nack );
        if ( ( NFCTAG_OK == error_flag ) && ( 0 != nack ) )
        {
            error_flag = NFCTAG_ERROR;
        }
    }
    return error_flag;
}

static err_t nfctag_i2c_read_byte ( nfctag_t *ctx, uint8_t *data_out, uint8_t nack )
{
    err_t error_flag = NFCTAG_OK;
    uint8_t rd_byte = 0;
    uint8_t rd_bit;
    uint8_t bit_cnt;

    for ( bit_cnt = 0; ( bit_cnt < 8 ) && ( NFCTAG_OK == error_flag ); bit_cnt++ )
    {
        error_flag = nfctag_i2c_read_bit( ctx, &rd_bit );
        if ( NFCTAG_OK == error_flag )
        {
            rd_byte = ( rd_byte << 1 ) | rd_bit;
        }
    }
    if ( NFCTAG_OK == error_flag )
    {
        error_flag = nfctag_i2c_write_bit( ctx, nack );
        if ( NFCTAG_OK == error_flag )
        {
        *data_out = rd_byte;
        }
    }
    return error_flag;
}

static err_t nfctag_i2c_write ( nfctag_t *ctx, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = nfctag_i2c_start( ctx );
    err_t stop_status;
    uint16_t cnt;

    if ( NFCTAG_OK == error_flag )
    {
        error_flag = nfctag_i2c_write_byte( ctx, ctx->slave_address << 1 );
        for ( cnt = 0; ( cnt < len ) && ( NFCTAG_OK == error_flag ); cnt++ )
        {
            error_flag = nfctag_i2c_write_byte( ctx, data_in[ cnt ] );
        }
        stop_status = nfctag_i2c_stop( ctx );
        if ( NFCTAG_OK == error_flag )
        {
            error_flag = stop_status;
        }
    }
    return error_flag;
}

static err_t nfctag_i2c_read ( nfctag_t *ctx, uint8_t *data_out, uint16_t len )
{
    err_t error_flag = nfctag_i2c_start( ctx );
    err_t stop_status;
    uint16_t cnt;

    if ( NFCTAG_OK == error_flag )
    {
        error_flag = nfctag_i2c_write_byte( ctx, ( ctx->slave_address << 1 ) | NFCTAG_I2C_READ_BIT );
        for ( cnt = 0; ( cnt < len ) && ( NFCTAG_OK == error_flag ); cnt++ )
        {
            error_flag = nfctag_i2c_read_byte( ctx, &data_out[ cnt ], ( uint8_t ) ( cnt == len - 1 ) );
        }
        stop_status = nfctag_i2c_stop( ctx );
        if ( NFCTAG_OK == error_flag )
        {
            error_flag = stop_status;
        }
    }
    return error_flag;
}

static uint16_t nfctag_calc_crc ( uint8_t *buffer, uint16_t len )
{
    uint16_t crc = NFCTAG_CRC_INITIAL;
    uint16_t cnt;
    uint8_t bit_cnt;

    for ( cnt = 0; cnt < len; cnt++ )
    {
        crc ^= buffer[ cnt ];
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( 0 != ( crc & 1u ) )
            {
                crc = ( crc >> 1 ) ^ NFCTAG_CRC_POLYNOMIAL;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

static err_t nfctag_exchange ( nfctag_t *ctx, uint8_t *command, uint16_t len,
                               uint8_t *data_out, uint8_t read_len )
{
    uint8_t response[ NFCTAG_TRANSFER_MAX + NFCTAG_RESPONSE_OVERHEAD ];
    uint16_t response_len = ( uint16_t ) read_len + NFCTAG_RESPONSE_OVERHEAD;
    uint16_t crc;
    uint8_t wait_step;
    uint8_t wait_steps = 1;
    uint8_t wtx_count = 0;
    uint8_t complete = 0;
    uint8_t pcb = NFCTAG_PCB_I_BLOCK | ctx->block_number;
    err_t error_flag = NFCTAG_ERROR;

    ctx->last_status = 0;
    if ( ( 0 != ctx->session_active ) && ( ctx->block_number <= 1 ) )
    {
        command[ 0 ] = pcb;
        crc = nfctag_calc_crc( command, len );
        command[ len ] = ( uint8_t ) crc;
        command[ len + 1 ] = ( uint8_t ) ( crc >> 8 );
        error_flag = nfctag_i2c_write( ctx, command, len + NFCTAG_CRC_SIZE );
        while ( ( NFCTAG_OK == error_flag ) && ( 0 == complete ) )
        {
            // STOP separates request and response; allow the 9.6 ms frame waiting time.
            for ( wait_step = 0; wait_step < wait_steps; wait_step++ )
            {
                Delay_10ms( );
            }
            error_flag = nfctag_i2c_read( ctx, response, response_len );
            if ( NFCTAG_OK == error_flag )
            {
                if ( NFCTAG_PCB_WTX == response[ 0 ] )
                {
                    if ( 0 != nfctag_calc_crc( response, NFCTAG_WTX_SIZE ) )
                    {
                        error_flag = NFCTAG_CRC_ERROR;
                    }
                    else if ( ( 0 == response[ 1 ] ) || ( response[ 1 ] > NFCTAG_WTX_MAX ) )
                    {
                        error_flag = NFCTAG_RESPONSE_ERROR;
                    }
                    else if ( wtx_count >= NFCTAG_WTX_RETRIES )
                    {
                        error_flag = NFCTAG_TIMEOUT;
                    }
                    else
                    {
                        wtx_count++;
                        wait_steps = response[ 1 ];
                        // Echo the validated four-byte WTX frame, then wait for completion.
                        error_flag = nfctag_i2c_write( ctx, response, NFCTAG_WTX_SIZE );
                    }
                }
                else if ( pcb != response[ 0 ] )
                {
                    error_flag = NFCTAG_RESPONSE_ERROR;
                }
                else
                {
                    if ( 0 != nfctag_calc_crc( response, response_len ) )
                    {
                        // A rejected read returns a five-byte status frame without payload.
                        if ( ( 0 == read_len ) ||
                             ( 0 != nfctag_calc_crc( response, NFCTAG_RESPONSE_OVERHEAD ) ) )
                        {
                            error_flag = NFCTAG_CRC_ERROR;
                        }
                        else
                        {
                            response_len = NFCTAG_RESPONSE_OVERHEAD;
                            if ( NFCTAG_STATUS_READ_OK == ( ( uint16_t ) response[ 1 ] << 8 ) )
                            {
                                error_flag = NFCTAG_RESPONSE_ERROR;
                            }
                        }
                    }
                    if ( NFCTAG_OK == error_flag )
                    {
                        ctx->last_status = ( ( uint16_t ) response[ response_len - 4 ] << 8 ) |
                                             response[ response_len - 3 ];
                        ctx->block_number ^= 1u;
                        complete = 1;
                        if ( ( ( 0 == read_len ) && ( NFCTAG_STATUS_OK == ctx->last_status ) ) ||
                             ( ( 0 != read_len ) && ( response_len > NFCTAG_RESPONSE_OVERHEAD ) &&
                               ( NFCTAG_STATUS_READ_OK == ( ctx->last_status & NFCTAG_STATUS_SW1_MASK ) ) ) )
                        {
                            if ( 0 != read_len )
                            {
                                memcpy( data_out, &response[ 1 ], read_len );
                            }
                        }
                        else
                        {
                            error_flag = NFCTAG_DEVICE_ERROR;
                        }
                    }
                }
            }
        }
        if ( ( NFCTAG_OK != error_flag ) && ( NFCTAG_DEVICE_ERROR != error_flag ) )
        {
            ctx->block_number = NFCTAG_BLOCK_INVALID;
        }
    }
    return error_flag;
}

static err_t nfctag_read_file ( nfctag_t *ctx, uint16_t offset, uint8_t *data_out,
                                uint8_t len, uint8_t command_class )
{
    uint8_t command[ 8 ];
    err_t error_flag = NFCTAG_ERROR;

    if ( ( NULL != data_out ) && ( 0 != len ) && ( len <= NFCTAG_TRANSFER_MAX ) &&
         ( offset < NFCTAG_NDEF_FILE_SIZE ) && ( len <= NFCTAG_NDEF_FILE_SIZE - offset ) )
    {
        command[ 1 ] = command_class;
        command[ 2 ] = NFCTAG_CMD_READ_BINARY;
        command[ 3 ] = ( uint8_t ) ( offset >> 8 );
        command[ 4 ] = ( uint8_t ) offset;
        command[ 5 ] = len;
        error_flag = nfctag_exchange( ctx, command, sizeof( command ) - NFCTAG_CRC_SIZE, data_out, len );
    }
    return error_flag;
}

static err_t nfctag_write_verify_block ( nfctag_t *ctx, uint16_t offset, uint8_t *data_in,
                                         uint8_t len, nfctag_ndef_stage_t *stage )
{
    uint8_t data_buf[ NFCTAG_TRANSFER_MAX ];
    err_t error_flag;

    if ( NULL != stage )
    {
        *stage = NFCTAG_NDEF_STAGE_BLOCK_WRITE;
    }
    error_flag = nfctag_update_binary( ctx, offset, data_in, len );
    if ( NFCTAG_OK == error_flag )
    {
        if ( NULL != stage )
        {
            *stage = NFCTAG_NDEF_STAGE_VERIFY_READ;
        }
        error_flag = nfctag_read_binary_ext( ctx, offset, data_buf, len );
        if ( ( NFCTAG_OK == error_flag ) && ( 0 != memcmp( data_buf, data_in, len ) ) )
        {
            error_flag = NFCTAG_ERROR;
            if ( NULL != stage )
            {
                *stage = NFCTAG_NDEF_STAGE_VERIFY_COMPARE;
            }
        }
    }
    return error_flag;
}

static err_t nfctag_write_ndef_record ( nfctag_t *ctx, uint8_t *record, uint16_t record_len,
                                        nfctag_ndef_stage_t *stage )
{
    uint8_t data_buf[ NFCTAG_TRANSFER_MAX ];
    uint8_t nlen[ NFCTAG_NLEN_SIZE ] = { 0, 0 };
    uint8_t rewrite = 0;
    uint8_t opened = 0;
    uint8_t count;
    uint16_t offset;
    uint16_t file_id;
    uint16_t file_size;
    err_t error_flag;
    err_t release_status;

    if ( NULL != stage )
    {
        *stage = NFCTAG_NDEF_STAGE_SESSION;
    }
    error_flag = nfctag_get_session( ctx );
    if ( NFCTAG_OK == error_flag )
    {
        opened = 1;
        if ( NULL != stage )
        {
            *stage = NFCTAG_NDEF_STAGE_SELECT;
        }
        error_flag = nfctag_select_application( ctx );
    }
    if ( NFCTAG_OK == error_flag )
    {
        error_flag = nfctag_select_file( ctx, NFCTAG_FILE_CC );
    }
    if ( NFCTAG_OK == error_flag )
    {
        if ( NULL != stage )
        {
            *stage = NFCTAG_NDEF_STAGE_CAPABILITY;
        }
        error_flag = nfctag_read_binary( ctx, 0, data_buf, NFCTAG_CC_SIZE );
        if ( NFCTAG_OK == error_flag )
        {
            file_id = ( ( uint16_t ) data_buf[ 9 ] << 8 ) | data_buf[ 10 ];
            file_size = ( ( uint16_t ) data_buf[ 11 ] << 8 ) | data_buf[ 12 ];
            if ( ( 0 != data_buf[ 0 ] ) || ( NFCTAG_CC_SIZE != data_buf[ 1 ] ) ||
                 ( NFCTAG_CC_NDEF_TYPE != data_buf[ 7 ] ) || ( NFCTAG_CC_TLV_LENGTH != data_buf[ 8 ] ) ||
                 ( NFCTAG_FILE_NDEF != file_id ) || ( file_size < record_len + NFCTAG_NLEN_SIZE ) ||
                 ( NFCTAG_CC_ACCESS_FREE != data_buf[ 13 ] ) || ( NFCTAG_CC_ACCESS_FREE != data_buf[ 14 ] ) )
            {
                error_flag = NFCTAG_ERROR;
            }
        }
    }
    if ( NFCTAG_OK == error_flag )
    {
        if ( NULL != stage )
        {
            *stage = NFCTAG_NDEF_STAGE_SELECT;
        }
        error_flag = nfctag_select_file( ctx, file_id );
    }
    if ( NFCTAG_OK == error_flag )
    {
        if ( NULL != stage )
        {
            *stage = NFCTAG_NDEF_STAGE_DATA_READ;
        }
        error_flag = nfctag_read_binary( ctx, 0, data_buf, NFCTAG_NLEN_SIZE );
        if ( ( NFCTAG_OK == error_flag ) &&
             ( record_len != ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) ) )
        {
            rewrite = 1;
        }
    }

    // Compare first so restarting the example does not repeatedly wear the EEPROM.
    for ( offset = 0; ( offset < record_len ) && ( NFCTAG_OK == error_flag ); offset += count )
    {
        count = NFCTAG_TRANSFER_MAX;
        if ( record_len - offset < count )
        {
            count = ( uint8_t ) ( record_len - offset );
        }
        error_flag = nfctag_read_binary_ext( ctx, offset + NFCTAG_NLEN_SIZE, data_buf, count );
        if ( ( NFCTAG_OK == error_flag ) && ( 0 != memcmp( data_buf, &record[ offset ], count ) ) )
        {
            rewrite = 1;
        }
    }

    if ( ( NFCTAG_OK == error_flag ) && ( 0 != rewrite ) )
    {
        // Publish NLEN only after all payload bytes have been written and verified.
        error_flag = nfctag_write_verify_block( ctx, 0, nlen, NFCTAG_NLEN_SIZE, stage );
        for ( offset = 0; ( offset < record_len ) && ( NFCTAG_OK == error_flag ); offset += count )
        {
            count = NFCTAG_TRANSFER_MAX;
            if ( record_len - offset < count )
            {
                count = ( uint8_t ) ( record_len - offset );
            }
            error_flag = nfctag_write_verify_block( ctx, offset + NFCTAG_NLEN_SIZE,
                                                     &record[ offset ], count, stage );
        }
        if ( NFCTAG_OK == error_flag )
        {
            nlen[ 0 ] = ( uint8_t ) ( record_len >> 8 );
            nlen[ 1 ] = ( uint8_t ) record_len;
            error_flag = nfctag_write_verify_block( ctx, 0, nlen, NFCTAG_NLEN_SIZE, stage );
        }
    }
    if ( 0 != opened )
    {
        release_status = nfctag_release_i2c( ctx );
        if ( NFCTAG_OK == error_flag )
        {
            error_flag = release_status;
            if ( NULL != stage )
            {
                *stage = NFCTAG_NDEF_STAGE_RELEASE;
            }
        }
    }
    if ( ( NFCTAG_OK == error_flag ) && ( NULL != stage ) )
    {
        *stage = NFCTAG_NDEF_STAGE_OK;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
