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
 * @file nfctag2.c
 * @brief NFC Tag 2 Click Driver.
 */

#include "nfctag2.h"
#include <string.h>

/**
 * @brief NFC Tag 2 write and verify block function.
 * @details This function writes an NFC Tag 2 Click memory block and compares its readback with the input data.
 * @param[in,out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in] block : User memory block address.
 * @param[in] data_in : Input buffer of NFCTAG2_BLOCK_SIZE bytes.
 * @param[out] stage : Failed write or verification step. May be NULL.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note I2C memory ownership is retained for the caller's access sequence.
 */
static err_t nfctag2_write_verify_block ( nfctag2_t *ctx, uint8_t block, uint8_t *data_in,
                                          nfctag2_ndef_stage_t *stage );

/**
 * @brief NFC Tag 2 write NDEF record function.
 * @details This function stores and verifies a complete NDEF TLV in NFC Tag 2 Click user EEPROM.
 * @param[in,out] ctx : Click context object.
 * See #nfctag2_t object definition for detailed explanation.
 * @param[in,out] record : NDEF TLV buffer including the terminator byte.
 * @param[in] record_len : Number of valid bytes in the NDEF TLV buffer.
 * @param[out] stage : Failed write or verification step. May be NULL.
 * @return @li @c 0 - Success,
 *         @li @c -1 - Error.
 * @note Uses user EEPROM blocks only. Tag metadata and reserved blocks are unchanged.
 */
static err_t nfctag2_write_ndef_record ( nfctag2_t *ctx, uint8_t *record, uint16_t record_len,
                                         nfctag2_ndef_stage_t *stage );

void nfctag2_cfg_setup ( nfctag2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->fd = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = NFCTAG2_DEVICE_ADDRESS;
}

err_t nfctag2_init ( nfctag2_t *ctx, nfctag2_cfg_t *cfg ) 
{
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

    digital_in_init( &ctx->fd, cfg->fd );

    return I2C_MASTER_SUCCESS;
}

err_t nfctag2_default_cfg ( nfctag2_t *ctx ) 
{
    err_t error_flag = NFCTAG2_OK;
    uint8_t control = 0;

    // Configure this powered session without changing EEPROM configuration or lock bits.
    error_flag = nfctag2_write_reg( ctx, NFCTAG2_REG_NC, NFCTAG2_NC_DEFAULT );
    if ( NFCTAG2_OK == error_flag )
    {
        error_flag = nfctag2_write_reg( ctx, NFCTAG2_REG_WDT_LS, NFCTAG2_WDT_LS_DEFAULT );
    }
    if ( NFCTAG2_OK == error_flag )
    {
        error_flag = nfctag2_write_reg( ctx, NFCTAG2_REG_WDT_MS, NFCTAG2_WDT_MS_DEFAULT );
    }
    if ( NFCTAG2_OK == error_flag )
    {
        error_flag = nfctag2_read_reg( ctx, NFCTAG2_REG_NC, &control );
        if ( NFCTAG2_NC_DEFAULT != control )
        {
            error_flag = NFCTAG2_ERROR;
        }
    }
    if ( NFCTAG2_OK != nfctag2_release_i2c( ctx ) )
    {
        error_flag = NFCTAG2_ERROR;
    }

    return error_flag;
}

err_t nfctag2_write_reg ( nfctag2_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return nfctag2_update_reg( ctx, reg, 0xFF, data_in );
}

err_t nfctag2_write_regs ( nfctag2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = NFCTAG2_ERROR;
    uint8_t cnt;

    if ( ( NULL != data_in ) && ( 0 != len ) && ( reg <= NFCTAG2_REG_NS ) &&
         ( len <= NFCTAG2_REG_NS + 1 - reg ) )
    {
        error_flag = NFCTAG2_OK;
        for ( cnt = 0; ( cnt < len ) && ( NFCTAG2_OK == error_flag ); cnt++ )
        {
            error_flag = nfctag2_write_reg( ctx, reg + cnt, data_in[ cnt ] );
        }
    }
    return error_flag;
}

err_t nfctag2_read_reg ( nfctag2_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    err_t error_flag = NFCTAG2_ERROR;
    uint8_t command[ 2 ];

    if ( ( NULL != data_out ) && ( reg <= NFCTAG2_REG_NS ) )
    {
        command[ 0 ] = NFCTAG2_BLOCK_SESSION;
        command[ 1 ] = reg;
        // A STOP separates register selection from the read; repeated START can trigger a soft reset.
        error_flag = i2c_master_write( &ctx->i2c, command, sizeof( command ) );
        if ( NFCTAG2_OK == error_flag )
        {
            Delay_50us( );
            error_flag = i2c_master_read( &ctx->i2c, data_out, 1 );
        }
    }
    return error_flag;
}

err_t nfctag2_read_regs ( nfctag2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t error_flag = NFCTAG2_ERROR;
    uint8_t cnt;

    if ( ( NULL != data_out ) && ( 0 != len ) && ( reg <= NFCTAG2_REG_NS ) &&
         ( len <= NFCTAG2_REG_NS + 1 - reg ) )
    {
        error_flag = NFCTAG2_OK;
        for ( cnt = 0; ( cnt < len ) && ( NFCTAG2_OK == error_flag ); cnt++ )
        {
            error_flag = nfctag2_read_reg( ctx, reg + cnt, &data_out[ cnt ] );
        }
    }
    return error_flag;
}

err_t nfctag2_update_reg ( nfctag2_t *ctx, uint8_t reg, uint8_t mask, uint8_t data_in )
{
    err_t error_flag = NFCTAG2_ERROR;
    uint8_t command[ 4 ];

    if ( reg <= NFCTAG2_REG_NS )
    {
        command[ 0 ] = NFCTAG2_BLOCK_SESSION;
        command[ 1 ] = reg;
        command[ 2 ] = mask;
        command[ 3 ] = data_in;
        error_flag = i2c_master_write( &ctx->i2c, command, sizeof( command ) );
    }
    return error_flag;
}

err_t nfctag2_read_block ( nfctag2_t *ctx, uint8_t block, uint8_t *data_out )
{
    err_t error_flag = NFCTAG2_ERROR;

    if ( ( NULL != data_out ) && ( ( block <= NFCTAG2_BLOCK_DYNAMIC_LOCK ) ||
         ( NFCTAG2_BLOCK_CONFIGURATION == block ) ||
         ( ( block >= NFCTAG2_BLOCK_SRAM_FIRST ) && ( block <= NFCTAG2_BLOCK_SRAM_LAST ) ) ) )
    {
        error_flag = i2c_master_write( &ctx->i2c, &block, 1 );
        if ( NFCTAG2_OK == error_flag )
        {
            // The 50 us access time also supports tags with I2C clock stretching disabled.
            Delay_50us( );
            error_flag = i2c_master_read( &ctx->i2c, data_out, NFCTAG2_BLOCK_SIZE );
        }
    }
    return error_flag;
}

err_t nfctag2_write_block ( nfctag2_t *ctx, uint8_t block, uint8_t *data_in )
{
    err_t error_flag = NFCTAG2_ERROR;
    uint8_t command[ NFCTAG2_BLOCK_SIZE + 1 ];

    if ( ( NULL != data_in ) &&
         ( ( ( block >= NFCTAG2_BLOCK_USER_FIRST ) && ( block <= NFCTAG2_BLOCK_USER_LAST ) ) ||
           ( ( block >= NFCTAG2_BLOCK_SRAM_FIRST ) && ( block <= NFCTAG2_BLOCK_SRAM_LAST ) ) ) )
    {
        command[ 0 ] = block;
        memcpy( &command[ 1 ], data_in, NFCTAG2_BLOCK_SIZE );
        error_flag = i2c_master_write( &ctx->i2c, command, sizeof( command ) );
        if ( ( NFCTAG2_OK == error_flag ) && ( block <= NFCTAG2_BLOCK_USER_LAST ) )
        {
            // EEPROM programming must complete before another memory access or lock release.
            Delay_5ms( );
        }
    }
    return error_flag;
}

err_t nfctag2_release_i2c ( nfctag2_t *ctx )
{
    return nfctag2_update_reg( ctx, NFCTAG2_REG_NS, NFCTAG2_NS_I2C_LOCKED, 0 );
}

err_t nfctag2_get_uid ( nfctag2_t *ctx, uint8_t *uid )
{
    err_t error_flag = NFCTAG2_ERROR;
    uint8_t data_buf[ NFCTAG2_BLOCK_SIZE ];

    if ( NULL != uid )
    {
        error_flag = nfctag2_read_block( ctx, NFCTAG2_BLOCK_SERIAL_NUMBER, data_buf );
        if ( NFCTAG2_OK == error_flag )
        {
            // The seven UID bytes are consecutive; byte 7 is SAK, not part of the UID.
            memcpy( uid, data_buf, NFCTAG2_UID_SIZE );
        }
        if ( NFCTAG2_OK != nfctag2_release_i2c( ctx ) )
        {
            error_flag = NFCTAG2_ERROR;
        }
    }
    return error_flag;
}

err_t nfctag2_write_ndef_text ( nfctag2_t *ctx, char *text, nfctag2_ndef_stage_t *stage )
{
    err_t error_flag = NFCTAG2_ERROR;
    uint8_t record[ NFCTAG2_NDEF_BUFFER_SIZE ] = { 0 };
    size_t text_len;

    if ( NULL != stage )
    {
        *stage = NFCTAG2_NDEF_STAGE_INVALID_TEXT;
    }
    if ( NULL != text )
    {
        text_len = strlen( text );
        if ( text_len <= NFCTAG2_NDEF_TEXT_MAX_LENGTH )
        {
            // TLV + short well-known Text record: UTF-8, language "en", then the terminator TLV.
            record[ 0 ] = NFCTAG2_NDEF_TLV;
            record[ 1 ] = text_len + 7;
            record[ 2 ] = NFCTAG2_NDEF_RECORD_HEADER;
            record[ 3 ] = 1;
            record[ 4 ] = text_len + 3;
            record[ 5 ] = NFCTAG2_NDEF_TEXT_TYPE;
            record[ 6 ] = 2;
            record[ 7 ] = 'e';
            record[ 8 ] = 'n';
            memcpy( &record[ 9 ], text, text_len );
            record[ text_len + 9 ] = NFCTAG2_NDEF_TERMINATOR;
            error_flag = nfctag2_write_ndef_record( ctx, record,
                                                    text_len + NFCTAG2_NDEF_TEXT_OVERHEAD, stage );
        }
    }
    return error_flag;
}

err_t nfctag2_write_ndef_uri ( nfctag2_t *ctx, char *uri, nfctag2_ndef_stage_t *stage )
{
    err_t error_flag = NFCTAG2_ERROR;
    uint8_t record[ NFCTAG2_NDEF_BUFFER_SIZE ] = { 0 };
    size_t uri_len;

    if ( NULL != stage )
    {
        *stage = NFCTAG2_NDEF_STAGE_INVALID_URI;
    }
    if ( NULL != uri )
    {
        uri_len = strlen( uri );
        if ( ( 0 < uri_len ) && ( uri_len <= NFCTAG2_NDEF_URI_MAX_LENGTH ) )
        {
            // URI RTD with prefix code 0 stores the supplied URI without abbreviation.
            record[ 0 ] = NFCTAG2_NDEF_TLV;
            record[ 1 ] = uri_len + 5;
            record[ 2 ] = NFCTAG2_NDEF_RECORD_HEADER;
            record[ 3 ] = 1;
            record[ 4 ] = uri_len + 1;
            record[ 5 ] = NFCTAG2_NDEF_URI_TYPE;
            record[ 6 ] = NFCTAG2_NDEF_URI_PREFIX_NONE;
            memcpy( &record[ 7 ], uri, uri_len );
            record[ uri_len + 7 ] = NFCTAG2_NDEF_TERMINATOR;
            error_flag = nfctag2_write_ndef_record( ctx, record,
                                                    uri_len + NFCTAG2_NDEF_URI_OVERHEAD, stage );
        }
    }
    return error_flag;
}

uint8_t nfctag2_get_field_detect ( nfctag2_t *ctx )
{
    return digital_in_read( &ctx->fd );
}

static err_t nfctag2_write_verify_block ( nfctag2_t *ctx, uint8_t block, uint8_t *data_in,
                                          nfctag2_ndef_stage_t *stage )
{
    uint8_t data_buf[ NFCTAG2_BLOCK_SIZE ];
    err_t error_flag;

    if ( NULL != stage )
    {
        *stage = NFCTAG2_NDEF_STAGE_BLOCK_WRITE;
    }
    error_flag = nfctag2_write_block( ctx, block, data_in );
    if ( NFCTAG2_OK == error_flag )
    {
        if ( NULL != stage )
        {
            *stage = NFCTAG2_NDEF_STAGE_VERIFY_READ;
        }
        error_flag = nfctag2_read_block( ctx, block, data_buf );
        if ( ( NFCTAG2_OK == error_flag ) && ( 0 != memcmp( data_buf, data_in, NFCTAG2_BLOCK_SIZE ) ) )
        {
            error_flag = NFCTAG2_ERROR;
            if ( NULL != stage )
            {
                *stage = NFCTAG2_NDEF_STAGE_VERIFY_COMPARE;
            }
        }
    }
    return error_flag;
}

static err_t nfctag2_write_ndef_record ( nfctag2_t *ctx, uint8_t *record, uint16_t record_len,
                                         nfctag2_ndef_stage_t *stage )
{
    err_t error_flag = NFCTAG2_ERROR;
    uint8_t data_buf[ NFCTAG2_BLOCK_SIZE ];
    uint8_t block;
    uint8_t block_count = 0;
    uint8_t record_valid = 0;
    uint8_t rewrite = 0;
    uint16_t offset;

    if ( ( NULL != record ) && ( record_len >= 4 ) && ( record_len <= NFCTAG2_NDEF_BUFFER_SIZE ) &&
         ( NFCTAG2_NDEF_TLV == record[ 0 ] ) && ( record[ 1 ] == record_len - 3 ) &&
         ( NFCTAG2_NDEF_TERMINATOR == record[ record_len - 1 ] ) )
    {
        block_count = ( record_len + NFCTAG2_BLOCK_SIZE - 1 ) / NFCTAG2_BLOCK_SIZE;
        if ( block_count <= NFCTAG2_BLOCK_USER_LAST - NFCTAG2_BLOCK_USER_FIRST + 1 )
        {
            record_valid = 1;
            error_flag = NFCTAG2_OK;
        }
    }

    // Compare first so restarting the example does not repeatedly wear the EEPROM.
    for ( block = 0; ( block < block_count ) && ( NFCTAG2_OK == error_flag ); block++ )
    {
        offset = ( uint16_t ) block * NFCTAG2_BLOCK_SIZE;
        if ( NULL != stage )
        {
            *stage = NFCTAG2_NDEF_STAGE_DATA_READ;
        }
        error_flag = nfctag2_read_block( ctx, NFCTAG2_BLOCK_USER_FIRST + block, data_buf );
        if ( ( NFCTAG2_OK == error_flag ) && ( 0 != memcmp( data_buf, &record[ offset ], NFCTAG2_BLOCK_SIZE ) ) )
        {
            rewrite = 1;
        }
    }

    if ( ( NFCTAG2_OK == error_flag ) && ( 0 != rewrite ) )
    {
        // Keep the NDEF length zero until every payload block has been written and verified.
        record[ 1 ] = 0;
        error_flag = nfctag2_write_verify_block( ctx, NFCTAG2_BLOCK_USER_FIRST, record, stage );
        for ( block = 1; ( block < block_count ) && ( NFCTAG2_OK == error_flag ); block++ )
        {
            offset = ( uint16_t ) block * NFCTAG2_BLOCK_SIZE;
            error_flag = nfctag2_write_verify_block( ctx, NFCTAG2_BLOCK_USER_FIRST + block,
                                                      &record[ offset ], stage );
        }
        if ( NFCTAG2_OK == error_flag )
        {
            record[ 1 ] = record_len - 3;
            error_flag = nfctag2_write_verify_block( ctx, NFCTAG2_BLOCK_USER_FIRST, record, stage );
        }
    }
    if ( NFCTAG2_OK == error_flag )
    {
        // Exclude the terminator TLV when locating the last block of the NDEF message.
        block = ( record_len - 1 + NFCTAG2_BLOCK_SIZE - 1 ) / NFCTAG2_BLOCK_SIZE;
        if ( NULL != stage )
        {
            *stage = NFCTAG2_NDEF_STAGE_LAST_BLOCK;
        }
        error_flag = nfctag2_write_reg( ctx, NFCTAG2_REG_LAST_NDEF_BLOCK, block );
    }
    // Release after a valid record attempt, including I2C failures.
    if ( 0 != record_valid )
    {
        if ( NFCTAG2_OK != nfctag2_release_i2c( ctx ) )
        {
            if ( NFCTAG2_OK == error_flag )
            {
                error_flag = NFCTAG2_ERROR;
                if ( NULL != stage )
                {
                    *stage = NFCTAG2_NDEF_STAGE_RELEASE;
                }
            }
        }
        else if ( ( NFCTAG2_OK == error_flag ) && ( NULL != stage ) )
        {
            *stage = NFCTAG2_NDEF_STAGE_OK;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
