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
 * @file thumbwheel.c
 * @brief Thumbwheel Click Driver.
 */

#include "thumbwheel.h"

/** 
 * @brief Calculation for Maxim CRC 8 function.
 * @details This function calculates Maxim CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x31 (x8 + x5 + x4 + 1 )
 * @li @c  Initialization 0x00
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated Maxim CRC.
 * @note None.
 */
static uint8_t thumbwheel_calculate_crc8_maxim( uint8_t *data_buf, uint8_t len );

void thumbwheel_cfg_setup ( thumbwheel_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->gp0 = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    
    cfg->rst = HAL_PIN_NC;
    
    cfg->gpio_sel = THUMBWHEEL_GPIO_0;
}

void thumbwheel_gpio_selection ( thumbwheel_cfg_t *cfg, thumbwheel_gpio_sel_t gpio_sel ) 
{
    cfg->gpio_sel = gpio_sel;
}

err_t thumbwheel_init ( thumbwheel_t *ctx, thumbwheel_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = ( cfg->gpio_sel == THUMBWHEEL_GPIO_0 ) ? cfg->gp0 : cfg->gp1;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_high ( &ctx->rst );

    return ONE_WIRE_SUCCESS;
}

err_t thumbwheel_check_communication ( thumbwheel_t *ctx )
{
    one_wire_rom_address_t search_rom_addr;
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return THUMBWHEEL_ERROR;
    }
    if ( THUMBWHEEL_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return THUMBWHEEL_ERROR;
    }
    if ( ONE_WIRE_ERROR == one_wire_search_first_device ( &ctx->ow, &search_rom_addr ) )
    {
        return THUMBWHEEL_ERROR;
    }
    if ( memcmp ( &ctx->rom_addr, &search_rom_addr, sizeof ( one_wire_rom_address_t ) ) )
    {
        return THUMBWHEEL_ERROR;
    }
    return THUMBWHEEL_OK;
}

err_t thumbwheel_write_register ( thumbwheel_t *ctx, uint16_t reg, uint8_t data_in )
{
    err_t error_flag = THUMBWHEEL_OK; 
    uint8_t data_buf[ 4 ];
    if ( ( reg < THUMBWHEEL_REG_COND_SEARCH_SELECTION ) || ( reg > THUMBWHEEL_REG_CONTROL_STATUS ) )
    {
        return THUMBWHEEL_ERROR;
    }
    if ( THUMBWHEEL_REG_CONTROL_STATUS == reg )
    {
        data_in &= ( ~THUMBWHEEL_CONFIG_RESERVED_BITS );
    }
    data_buf[ 0 ] = THUMBWHEEL_CMD_WRITE_COND_SEARCH_REG; 
    data_buf[ 1 ] = reg & 0xFF; 
    data_buf[ 2 ] = ( reg >> 8 ) & 0xFF; 
    data_buf[ 3 ] = data_in; 
    error_flag |= one_wire_match_rom( &ctx->ow, &ctx->rom_addr );
    error_flag |= one_wire_write_byte ( &ctx->ow, data_buf, 4 );
    return error_flag; 
}

err_t thumbwheel_read_register ( thumbwheel_t *ctx, uint16_t reg, uint8_t *data_out )
{
    err_t error_flag = THUMBWHEEL_OK; 
    uint8_t data_buf[ 3 ];
    if ( ( reg < THUMBWHEEL_REG_PIO_LOGIC  ) || ( reg > THUMBWHEEL_REG_CONTROL_STATUS ) )
    {
        return THUMBWHEEL_ERROR;
    }
    data_buf[ 0 ] = THUMBWHEEL_CMD_READ_PIO_REG; 
    data_buf[ 1 ] = reg & 0xFF; 
    data_buf[ 2 ] = ( reg >> 8 ) & 0xFF; 
    error_flag |= one_wire_match_rom( &ctx->ow, &ctx->rom_addr );
    error_flag |= one_wire_write_byte ( &ctx->ow, data_buf, 3 );
    error_flag |= one_wire_read_byte ( &ctx->ow, data_out, 1 );
    return error_flag; 
}

err_t thumbwheel_reset_latches ( thumbwheel_t *ctx )
{
    err_t error_flag = THUMBWHEEL_OK; 
    uint8_t command = THUMBWHEEL_CMD_RESET_ACTIVITY_LATCHES; 
    error_flag |= one_wire_match_rom( &ctx->ow, &ctx->rom_addr );
    error_flag |= one_wire_write_byte ( &ctx->ow, &command, 1 );
    return error_flag; 
}

err_t thumbwheel_get_position ( thumbwheel_t *ctx, uint8_t *position )
{
    err_t error_flag = THUMBWHEEL_OK;
    uint8_t command = THUMBWHEEL_CMD_CHANNEL_ACCESS_READ; 
    error_flag |= one_wire_match_rom( &ctx->ow, &ctx->rom_addr );
    error_flag |= one_wire_write_byte ( &ctx->ow, &command, 1 );
    error_flag |= one_wire_read_byte ( &ctx->ow, position, 1 );
    ( *position )++; 
    return error_flag; 
}

void thumbwheel_set_rst_pin ( thumbwheel_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

static uint8_t thumbwheel_calculate_crc8_maxim( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0x00;
    for ( uint8_t cnt_0 = 0; cnt_0 < len; cnt_0++ ) 
    {
        uint8_t in_byte = data_buf[ cnt_0 ];
        for ( uint8_t cnt_1 = 0; cnt_1 < 8; cnt_1++ ) 
        {
            uint8_t mix = ( crc ^ in_byte ) & 0x01;
            crc >>= 1;
            if ( 0 != mix ) 
            {
                crc ^= 0x8C;
            }
            in_byte >>= 1;
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END
