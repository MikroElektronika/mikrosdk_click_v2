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
 * @file c1wirei2c.c
 * @brief 1-Wire I2C Click Driver.
 */

#include "c1wirei2c.h"

/** 
 * @brief Reflect bits.
 * @details This function reflects a desired number of bits in data.
 * @return Reflected data.
 * @note None.
 */
static uint16_t c1wirei2c_reflect_bits( uint16_t data_in, uint8_t len );

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
static uint16_t c1wirei2c_calculate_crc16 ( uint8_t *data_buf, uint16_t len );

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
static uint8_t c1wirei2c_calculate_crc8 ( uint8_t *data_buf, uint8_t len );

void c1wirei2c_cfg_setup ( c1wirei2c_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->ow1 = HAL_PIN_NC;
    cfg->ow2 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    
    cfg->gpio_sel = C1WIREI2C_GPIO_OW1;
}

void c1wirei2c_gpio_selection ( c1wirei2c_cfg_t *cfg, c1wirei2c_gpio_sel_t gpio_sel ) 
{
    cfg->gpio_sel = gpio_sel;
}

err_t c1wirei2c_init ( c1wirei2c_t *ctx, c1wirei2c_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = ( cfg->gpio_sel == C1WIREI2C_GPIO_OW1 ) ? cfg->ow1 : cfg->ow2;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    return ONE_WIRE_SUCCESS;
}

err_t c1wirei2c_default_cfg ( c1wirei2c_t *ctx ) 
{
    err_t error_flag = C1WIREI2C_OK;
    ctx->address = C1WIREI2C_ADDRESS_ALL;
    c1wirei2c_reset_device ( ctx );
    if ( C1WIREI2C_ERROR == c1wirei2c_check_communication ( ctx ) )
    {
        return C1WIREI2C_ERROR;
    }
    error_flag |= c1wirei2c_write_configuration ( ctx, C1WIREI2C_CONFIGURATION_SPD_100KHZ );
    return error_flag;
}

err_t c1wirei2c_check_communication ( c1wirei2c_t *ctx )
{
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return C1WIREI2C_ERROR;
    }
    if ( C1WIREI2C_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return C1WIREI2C_ERROR;
    }
    if ( ctx->rom_addr.address[ 7 ] != c1wirei2c_calculate_crc8 ( &ctx->rom_addr.address[ 0 ], 7 ) )
    {
        return C1WIREI2C_ERROR;
    }
    return C1WIREI2C_OK;
}

err_t c1wirei2c_select_device ( c1wirei2c_t *ctx )
{
    if ( C1WIREI2C_ADDRESS_ALL == ctx->address )
    {
        // One Wire Reset sequence and "Skip ROM" command.
        return one_wire_skip_rom( &ctx->ow );
    }
    else
    {
        // One Wire Reset sequence and "Match ROM" command.
        return one_wire_match_rom( &ctx->ow, &ctx->rom_addr );
    }
}

err_t c1wirei2c_write_data_stop ( c1wirei2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = C1WIREI2C_OK;
    uint16_t crc16 = 0;
    uint8_t data_buf[ 260 ] = { 0 };
    data_buf[ 0 ] = C1WIREI2C_CMD_WRITE_DATA_WITH_STOP;
    data_buf[ 1 ] = ( slave_addr << 1 );
    data_buf[ 2 ] = len;
    memcpy ( &data_buf[ 3 ], data_in, len );
    crc16 = c1wirei2c_calculate_crc16 ( data_buf, len + 3 );
    data_buf[ len + 3 ] = ( uint8_t ) ( crc16 & 0xFF );
    data_buf[ len + 4 ] = ( uint8_t ) ( ( crc16 >> 8 ) & 0xFF );
    error_flag |= c1wirei2c_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, len + 5 );
    Delay_10ms ( );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, 2 );
    if ( data_buf[ 0 ] || data_buf[ 1 ] )
    {
        error_flag = C1WIREI2C_ERROR;
    }
    return error_flag;
}

err_t c1wirei2c_write_data ( c1wirei2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = C1WIREI2C_OK;
    uint16_t crc16 = 0;
    uint8_t data_buf[ 260 ] = { 0 };
    data_buf[ 0 ] = C1WIREI2C_CMD_WRITE_DATA_NO_STOP;
    data_buf[ 1 ] = ( slave_addr << 1 );
    data_buf[ 2 ] = len;
    memcpy ( &data_buf[ 3 ], data_in, len );
    crc16 = c1wirei2c_calculate_crc16 ( data_buf, len + 3 );
    data_buf[ len + 3 ] = ( uint8_t ) ( crc16 & 0xFF );
    data_buf[ len + 4 ] = ( uint8_t ) ( ( crc16 >> 8 ) & 0xFF );
    error_flag |= c1wirei2c_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, len + 5 );
    Delay_10ms ( );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, 2 );
    if ( data_buf[ 0 ] || data_buf[ 1 ] )
    {
        error_flag = C1WIREI2C_ERROR;
    }
    return error_flag;
}

err_t c1wirei2c_write_data_only ( c1wirei2c_t *ctx, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = C1WIREI2C_OK;
    uint16_t crc16 = 0;
    uint8_t data_buf[ 259 ] = { 0 };
    data_buf[ 0 ] = C1WIREI2C_CMD_WRITE_DATA_ONLY;
    data_buf[ 1 ] = len;
    memcpy ( &data_buf[ 2 ], data_in, len );
    crc16 = c1wirei2c_calculate_crc16 ( data_buf, len + 2 );
    data_buf[ len + 2 ] = ( uint8_t ) ( crc16 & 0xFF );
    data_buf[ len + 3 ] = ( uint8_t ) ( ( crc16 >> 8 ) & 0xFF );
    error_flag |= c1wirei2c_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, len + 4 );
    Delay_10ms ( );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, 2 );
    if ( data_buf[ 0 ] || data_buf[ 1 ] )
    {
        error_flag = C1WIREI2C_ERROR;
    }
    return error_flag;
}

err_t c1wirei2c_write_data_only_stop ( c1wirei2c_t *ctx, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = C1WIREI2C_OK;
    uint16_t crc16 = 0;
    uint8_t data_buf[ 259 ] = { 0 };
    data_buf[ 0 ] = C1WIREI2C_CMD_WRITE_DATA_ONLY_WITH_STOP;
    data_buf[ 1 ] = len;
    memcpy ( &data_buf[ 2 ], data_in, len );
    crc16 = c1wirei2c_calculate_crc16 ( data_buf, len + 2 );
    data_buf[ len + 2 ] = ( uint8_t ) ( crc16 & 0xFF );
    data_buf[ len + 3 ] = ( uint8_t ) ( ( crc16 >> 8 ) & 0xFF );
    error_flag |= c1wirei2c_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, len + 4 );
    Delay_10ms ( );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, 2 );
    if ( data_buf[ 0 ] || data_buf[ 1 ] )
    {
        error_flag = C1WIREI2C_ERROR;
    }
    return error_flag;
}

err_t c1wirei2c_read_data_stop ( c1wirei2c_t *ctx, uint8_t slave_addr, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = C1WIREI2C_OK;
    uint16_t crc16 = 0;
    uint8_t data_buf[ 260 ] = { 0 };
    data_buf[ 0 ] = C1WIREI2C_CMD_READ_DATA_WITH_STOP;
    data_buf[ 1 ] = ( slave_addr << 1 ) | 0x01; // Slave address + Read bit
    data_buf[ 2 ] = len;
    crc16 = c1wirei2c_calculate_crc16 ( data_buf, 3 );
    data_buf[ 3 ] = ( uint8_t ) ( crc16 & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( crc16 >> 8 ) & 0xFF );
    error_flag |= c1wirei2c_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 5 );
    Delay_10ms ( );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, len + 2 );
    if ( data_buf[ 0 ] )
    {
        error_flag = C1WIREI2C_ERROR;
    }
    if ( C1WIREI2C_OK == error_flag )
    {
        // Chip sends one '0' bit before reading starts, so everything needs to be shifted by one bit.
        for ( uint8_t cnt = 0; cnt < len; cnt++ )
        {
            data_out[ cnt ] = ( data_buf[ 1 + cnt ] >> 1 ) | ( ( data_buf[ 2 + cnt ] & 0x01 ) << 7 );
        }
    }
    return error_flag;
}

err_t c1wirei2c_write_read_data_stop ( c1wirei2c_t *ctx, uint8_t slave_addr, 
                                       uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len )
{
    err_t error_flag = C1WIREI2C_OK;
    uint16_t crc16 = 0;
    uint8_t data_buf[ 261 ] = { 0 };
    data_buf[ 0 ] = C1WIREI2C_CMD_WRITE_READ_DATA_WITH_STOP;
    data_buf[ 1 ] = ( slave_addr << 1 );
    data_buf[ 2 ] = in_len;
    memcpy ( &data_buf[ 3 ], data_in, in_len );
    data_buf[ in_len + 3 ] = out_len;
    crc16 = c1wirei2c_calculate_crc16 ( data_buf, in_len + 4 );
    data_buf[ in_len + 4 ] = ( uint8_t ) ( crc16 & 0xFF );
    data_buf[ in_len + 5 ] = ( uint8_t ) ( ( crc16 >> 8 ) & 0xFF );
    error_flag |= one_wire_reset ( &ctx->ow );
    error_flag |= c1wirei2c_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, in_len + 6 );
    Delay_10ms ( );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, out_len + 3 );
    if ( data_buf[ 0 ] || data_buf[ 1 ] )
    {
        error_flag = C1WIREI2C_ERROR;
    }
    if ( C1WIREI2C_OK == error_flag )
    {
        // Chip sends one '0' bit before reading starts, so everything needs to be shifted by one bit.
        for ( uint8_t cnt = 0; cnt < out_len; cnt++ )
        {
            data_out[ cnt ] = ( data_buf[ 2 + cnt ] >> 1 ) | ( ( data_buf[ 3 + cnt ] & 0x01 ) << 7 );
        }
    }
    return error_flag;
}

err_t c1wirei2c_write_configuration ( c1wirei2c_t *ctx, uint8_t config )
{
    err_t error_flag = C1WIREI2C_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = C1WIREI2C_CMD_WRITE_CONFIGURATION;
    data_buf[ 1 ] = config;
    error_flag |= c1wirei2c_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 2 );
    Delay_10ms ( );
    return error_flag;
}

err_t c1wirei2c_read_configuration ( c1wirei2c_t *ctx, uint8_t *config )
{
    err_t error_flag = C1WIREI2C_OK;
    uint8_t command = C1WIREI2C_CMD_READ_CONFIGURATION;
    error_flag |= c1wirei2c_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, config, 1 );
    return error_flag;
}

err_t c1wirei2c_enable_sleep_mode ( c1wirei2c_t *ctx )
{
    err_t error_flag = C1WIREI2C_OK;
    uint8_t command = C1WIREI2C_CMD_ENABLE_SLEEP_MODE;
    error_flag |= c1wirei2c_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    return error_flag;
}

err_t c1wirei2c_read_device_revision ( c1wirei2c_t *ctx, uint8_t *revision )
{
    err_t error_flag = C1WIREI2C_OK;
    uint8_t command = C1WIREI2C_CMD_READ_DEVICE_REVISION;
    error_flag |= c1wirei2c_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, revision, 1 );
    return error_flag;
}

void c1wirei2c_set_rst_pin ( c1wirei2c_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void c1wirei2c_reset_device ( c1wirei2c_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

static uint16_t c1wirei2c_reflect_bits( uint16_t data_in, uint8_t len )
{
    uint16_t data_out = 0;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        data_out |= ( ( data_in >> cnt ) & 1 ) << ( len - cnt - 1 );
    }
    return data_out;
}

static uint16_t c1wirei2c_calculate_crc16( uint8_t *data_buf, uint16_t len )
{
    uint16_t crc16 = 0x0000;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        crc16 ^= ( c1wirei2c_reflect_bits( data_buf[ cnt ], 8 ) << 8 );
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
    return c1wirei2c_reflect_bits( crc16, 16 ) ^ 0xFFFF;
}

static uint8_t c1wirei2c_calculate_crc8 ( uint8_t *data_buf, uint8_t len )
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
