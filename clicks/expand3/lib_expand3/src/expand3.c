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
 * @file expand3.c
 * @brief Expand 3 Click Driver.
 */

#include "expand3.h"

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
static uint8_t expand3_calculate_crc8 ( uint8_t *data_buf, uint8_t len );

void expand3_cfg_setup ( expand3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->ow0 = HAL_PIN_NC;
    cfg->ow1 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    
    cfg->gpio_sel = EXPAND3_GPIO_OW0;
}

void expand3_gpio_selection ( expand3_cfg_t *cfg, expand3_gpio_sel_t gpio_sel ) 
{
    cfg->gpio_sel = gpio_sel;
}

err_t expand3_init ( expand3_t *ctx, expand3_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = ( cfg->gpio_sel == EXPAND3_GPIO_OW0 ) ? cfg->ow0 : cfg->ow1;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    return ONE_WIRE_SUCCESS;
}

err_t expand3_default_cfg ( expand3_t *ctx ) 
{
    err_t error_flag = EXPAND3_OK;
    expand3_reset_device ( ctx );
    ctx->address = EXPAND3_ADDRESS_ALL;
    if ( EXPAND3_ERROR == expand3_check_communication ( ctx ) )
    {
        return EXPAND3_ERROR;
    }
    error_flag |= expand3_write_control ( ctx, EXPAND3_CONTROL_DEFAULT );
    error_flag |= expand3_write_mask ( ctx, EXPAND3_MASK_DEFAULT );
    error_flag |= expand3_write_polarity ( ctx, EXPAND3_POLARITY_DEFAULT );
    return error_flag;
}

err_t expand3_check_communication ( expand3_t *ctx )
{
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return EXPAND3_ERROR;
    }
    if ( EXPAND3_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return EXPAND3_ERROR;
    }
    if ( ctx->rom_addr.address[ 7 ] != expand3_calculate_crc8 ( &ctx->rom_addr.address[ 0 ], 7 ) )
    {
        return EXPAND3_ERROR;
    }
    return EXPAND3_OK;
}

err_t expand3_select_device ( expand3_t *ctx )
{
    if ( EXPAND3_ADDRESS_ALL == ctx->address )
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

err_t expand3_read_register ( expand3_t *ctx, uint16_t reg, uint8_t *data_out )
{
    err_t error_flag = EXPAND3_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    if ( ( reg < EXPAND3_REG_PIO_LOGIC ) || ( reg > EXPAND3_REG_CONTROL ) || ( NULL == data_out ) )
    {
        return EXPAND3_ERROR;
    }
    data_buf[ 0 ] = EXPAND3_CMD_READ_PIO_REGISTERS;
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    error_flag |= expand3_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 3 );
    error_flag |= one_wire_read_byte( &ctx->ow, data_out, 1 );
    return error_flag;
}

err_t expand3_write_register ( expand3_t *ctx, uint16_t reg, uint8_t data_in )
{
    err_t error_flag = EXPAND3_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    if ( ( reg < EXPAND3_REG_CHANNEL_MASK ) || ( reg > EXPAND3_REG_CONTROL ) )
    {
        return EXPAND3_ERROR;
    }
    data_buf[ 0 ] = EXPAND3_CMD_WRITE_CONDITIONAL;
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( reg >> 8 ) & 0xFF );
    data_buf[ 3 ] = data_in;
    error_flag |= expand3_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 4 );
    return error_flag;
}

err_t expand3_read_state ( expand3_t *ctx, uint8_t *state )
{
    err_t error_flag = EXPAND3_OK;
    uint8_t data_buf[ 1 ] = { EXPAND3_CMD_CHANNEL_ACCESS_READ };
    error_flag |= expand3_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, state, 1 );
    return error_flag;
}

err_t expand3_write_state ( expand3_t *ctx, uint8_t state )
{
    err_t error_flag = EXPAND3_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = EXPAND3_CMD_CHANNEL_ACCESS_WRITE;
    data_buf[ 1 ] = state;
    data_buf[ 2 ] = ~state;
    error_flag |= expand3_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 3 );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, 1 );
    if ( EXPAND3_CONFIRMATION_BYTE != data_buf[ 0 ] )
    {
        error_flag |= EXPAND3_ERROR;
    }
    return error_flag;
}

err_t expand3_reset_activity ( expand3_t *ctx )
{
    err_t error_flag = EXPAND3_OK;
    uint8_t data_buf[ 1 ] = { EXPAND3_CMD_RESET_ACTIVITY_LATCHES };
    error_flag |= expand3_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, 1 );
    if ( EXPAND3_CONFIRMATION_BYTE != data_buf[ 0 ] )
    {
        error_flag |= EXPAND3_ERROR;
    }
    return error_flag;
}

err_t expand3_write_mask ( expand3_t *ctx, uint8_t mask )
{
    return expand3_write_register( ctx, EXPAND3_REG_CHANNEL_MASK, mask );
}

err_t expand3_write_polarity ( expand3_t *ctx, uint8_t polarity )
{
    return expand3_write_register( ctx, EXPAND3_REG_CHANNEL_POLARITY, polarity );
}

err_t expand3_write_control ( expand3_t *ctx, uint8_t control )
{
    return expand3_write_register( ctx, EXPAND3_REG_CONTROL, control );
}

err_t expand3_read_control ( expand3_t *ctx, uint8_t *control )
{
    return expand3_read_register( ctx, EXPAND3_REG_CONTROL, control );
}

err_t expand3_read_current_state ( expand3_t *ctx, uint8_t *curr_state )
{
    return expand3_read_register( ctx, EXPAND3_REG_PIO_LOGIC, curr_state );
}

err_t expand3_read_last_state ( expand3_t *ctx, uint8_t *last_state )
{
    return expand3_read_register( ctx, EXPAND3_REG_PIO_OUT_LATCH, last_state );
}

err_t expand3_read_activity ( expand3_t *ctx, uint8_t *activity )
{
    return expand3_read_register( ctx, EXPAND3_REG_PIO_ACTIVITY_LATCH, activity );
}

void expand3_set_rst_pin ( expand3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void expand3_reset_device ( expand3_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

static uint8_t expand3_calculate_crc8 ( uint8_t *data_buf, uint8_t len )
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
