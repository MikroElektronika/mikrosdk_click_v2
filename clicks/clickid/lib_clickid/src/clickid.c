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
 * @file clickid.c
 * @brief ClickID Driver.
 */

#include "clickid.h"

/** 
 * @brief Reflect bits.
 * @details This function reflects a desired number of bits in data.
 * @return Reflected data.
 * @note None.
 */
static uint16_t clickid_reflect_bits( uint16_t data_in, uint8_t len );

/** 
 * @brief CRC-16/MAXIM calculation for CRC16 function.
 * @details This function calculates CRC16 with parameteres: 
 * @li @c  Width 16 bit
 * @li @c  Polynomial 0x8005 ( x16 + x15 + x2 + x0 )
 * @li @c  Initialization 0x0000
 * @li @c  Reflect input True
 * @li @c  Reflect output True
 * @li @c  Final Xor 0xFFFF
 * @li @c  Example { 69, 00 } - 0xAFD1
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint16_t clickid_calculate_crc16 ( uint8_t *data_buf, uint16_t len );

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameters: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x8C (x8 + x5 + x4 + 1 )
 * @li @c  Initialization 0x00
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t clickid_calculate_crc8 ( uint8_t *data_buf, uint8_t len );

void clickid_cfg_setup ( clickid_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
}

err_t clickid_init ( clickid_t *ctx, clickid_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = cfg->cs;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_low( &ctx->rst );
    Delay_100ms ( );
    
    return ONE_WIRE_SUCCESS;
}

void clickid_deinit ( clickid_t *ctx ) 
{
    ctx->ow.state = false;
    digital_out_high( &ctx->rst );
    Delay_100ms ( );
}

err_t clickid_check_communication ( clickid_t *ctx )
{
    if ( ONE_WIRE_SUCCESS != one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return CLICKID_ERROR;
    }
    if ( CLICKID_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return CLICKID_ERROR;
    }
    if ( ctx->rom_addr.address[ 7 ] != clickid_calculate_crc8 ( &ctx->rom_addr.address[ 0 ], 7 ) )
    {
        return CLICKID_ERROR;
    }
    return CLICKID_OK;
}

err_t clickid_read_memory ( clickid_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len )
{
    err_t error_flag = CLICKID_OK;
    uint8_t page = address >> 5;
    uint8_t data_buf[ 1 + CLICKID_PAGE_SIZE ] = { 0 }; // Command byte + Page size
    uint8_t crc_buf[ 2 ] = { 0 };
    uint16_t crc = 0;
    
    // Always whole buffer is read, so if address is not aligned to start of page,
    // then we must calculate offset in first read page.
    uint8_t offset = address & 0x1F;
    
    while ( ( len > 0 ) && ( CLICKID_OK == error_flag ) )
    {
        // Calculate number of bytes need to be copied from page to output buffer
        uint8_t len_to_copy = len > ( CLICKID_PAGE_SIZE - offset ) ? ( CLICKID_PAGE_SIZE - offset ) : len;
        // 1-wire reset will put slave in waiting command state. 
        one_wire_reset( &ctx->ow );
        one_wire_skip_rom( &ctx->ow );
        data_buf[ 0 ] = CLICKID_CMD_READ_MEMORY;
        data_buf[ 1 ] = page;
        if ( ONE_WIRE_SUCCESS != one_wire_write_byte( &ctx->ow, data_buf, 2 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        // Read and check CRC
        if ( ONE_WIRE_SUCCESS != one_wire_read_byte( &ctx->ow, crc_buf, 2 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        crc = ( ( uint16_t ) crc_buf[ 1 ] << 8 ) | crc_buf[ 0 ];
        if ( crc != clickid_calculate_crc16 ( data_buf, 2 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        
        data_buf[ 0 ] = CLICKID_CMD_RELEASE;
        if ( ONE_WIRE_SUCCESS != one_wire_write_byte( &ctx->ow, data_buf, 1 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        Delay_10ms( );
        
        // Read operation status
        if ( ONE_WIRE_SUCCESS != one_wire_read_byte( &ctx->ow, data_buf, CLICKID_PAGE_SIZE + 1 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        // Read and check CRC
        if ( ONE_WIRE_SUCCESS != one_wire_read_byte( &ctx->ow, crc_buf, 2 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        crc = ( ( uint16_t ) crc_buf[ 1 ] << 8 ) | crc_buf[ 0 ];
        if ( crc != clickid_calculate_crc16 ( data_buf, CLICKID_PAGE_SIZE + 1 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        // Check memory access result
        if ( CLICKID_MEM_ACCESS_SUCCESS != data_buf[ 0 ] )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        // Copy temporary page buffer to read output buffer
        memcpy( data_out, &data_buf[ offset + 1 ], len_to_copy );
        // Move to next page
        page++;
        data_out += len_to_copy;
        len -= len_to_copy;
        // After first page, always copy data from start of page
        offset = 0;
    }
    return error_flag;
}

err_t clickid_write_memory ( clickid_t *ctx, uint16_t address, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = CLICKID_OK;
    uint8_t page = address >> 5;
    uint8_t data_buf[ 1 + CLICKID_PAGE_SIZE ] = { 0 }; // Command byte + Page size
    uint8_t crc_buf[ 2 ] = { 0 };
    uint16_t crc = 0;
    
    // Function return error if address is not aligned to page start.
    if ( address & 0x1F )
    {
        return CLICKID_ERROR;
    }
    
    while ( ( len > 0 ) && ( CLICKID_OK == error_flag ) )
    {
        // Calculate number of bytes need to be copied from input buffer to data_buf
        uint8_t len_to_copy = len > CLICKID_PAGE_SIZE ? CLICKID_PAGE_SIZE : len;
        // 1-wire reset will put slave in waiting command state. 
        one_wire_reset( &ctx->ow );
        one_wire_skip_rom( &ctx->ow );
        data_buf[ 0 ] = CLICKID_CMD_WRITE_MEMORY;
        data_buf[ 1 ] = page;
        if ( ONE_WIRE_SUCCESS != one_wire_write_byte( &ctx->ow, data_buf, 2 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        // Read and check CRC
        if ( ONE_WIRE_SUCCESS != one_wire_read_byte( &ctx->ow, crc_buf, 2 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        crc = ( ( uint16_t ) crc_buf[ 1 ] << 8 ) | crc_buf[ 0 ];
        if ( crc != clickid_calculate_crc16 ( data_buf, 2 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        
        // Copy write input buffer to temporary page buffer
        memset( data_buf, 0, sizeof ( data_buf ) );
        memcpy( data_buf, data_in, len_to_copy );
        if ( ONE_WIRE_SUCCESS != one_wire_write_byte( &ctx->ow, data_buf, CLICKID_PAGE_SIZE ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        // Read and check CRC
        if ( ONE_WIRE_SUCCESS != one_wire_read_byte( &ctx->ow, crc_buf, 2 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        crc = ( ( uint16_t ) crc_buf[ 1 ] << 8 ) | crc_buf[ 0 ];
        if ( crc != clickid_calculate_crc16 ( data_buf, CLICKID_PAGE_SIZE ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        
        data_buf[ 0 ] = CLICKID_CMD_RELEASE;
        if ( ONE_WIRE_SUCCESS != one_wire_write_byte( &ctx->ow, data_buf, 1 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        Delay_10ms( );
        Delay_10ms( );
        
        // Read operation status
        if ( ONE_WIRE_SUCCESS != one_wire_read_byte( &ctx->ow, data_buf, 1 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        // Read and check CRC
        if ( ONE_WIRE_SUCCESS != one_wire_read_byte( &ctx->ow, crc_buf, 2 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        crc = ( ( uint16_t ) crc_buf[ 1 ] << 8 ) | crc_buf[ 0 ];
        if ( crc != clickid_calculate_crc16 ( data_buf, 1 ) )
        {
            error_flag = CLICKID_ERROR;
            break;
        }
        
        // Check memory access result
        if ( CLICKID_MEM_ACCESS_SUCCESS != data_buf[ 0 ] )
        {
            error_flag = CLICKID_ERROR;
            break;
        }

        // Move to next page
        page++;
        data_in += len_to_copy;
        len -= len_to_copy;
    }
    return error_flag;
}

err_t clickid_read_information ( clickid_t *ctx, clickid_information_t *info )
{
    uint8_t data_buf[ CLICKID_PAGE_SIZE ] = { 0 };
    err_t error_flag = clickid_read_memory ( ctx, CLICKID_USER_EEPROM_START, data_buf, CLICKID_PAGE_SIZE );
    info->hw_rev.major = data_buf[ 0 ];
    info->hw_rev.minor = data_buf[ 1 ];
    info->serial = ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
    info->type = ( ( ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ] ) >> 1 ) & 0x03FF;
    info->custom = data_buf[ 2 ] & 0x0001;
    memcpy ( info->name, &data_buf[ 6 ], 20 );
    return error_flag;
}

static uint16_t clickid_reflect_bits( uint16_t data_in, uint8_t len )
{
    uint16_t data_out = 0;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        data_out |= ( ( data_in >> cnt ) & 1 ) << ( len - cnt - 1 );
    }
    return data_out;
}

static uint16_t clickid_calculate_crc16( uint8_t *data_buf, uint16_t len )
{
    uint16_t crc16 = 0x0000;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        crc16 ^= ( clickid_reflect_bits( data_buf[ cnt ], 8 ) << 8 );
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( crc16 & 0x8000 )
            {
                crc16 = ( crc16 << 1 ) ^ 0x8005;
            }
            else
            {
                crc16 <<= 1;
            }
        }
    }
    return clickid_reflect_bits( crc16, 16 ) ^ 0xFFFF;
}

static uint8_t clickid_calculate_crc8 ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0;
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ ) 
    {
        crc ^= data_buf[ byte_cnt ];
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( crc & 0x01 ) 
            {
                crc = ( crc >> 1 ) ^ 0x8C;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END
