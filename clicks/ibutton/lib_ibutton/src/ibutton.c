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
 * @file ibutton.c
 * @brief iButton Click Driver.
 */

#include "ibutton.h"

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
static uint8_t ibutton_calculate_crc8 ( uint8_t *data_buf, uint8_t len );

void ibutton_cfg_setup ( ibutton_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->gp0 = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    cfg->st2 = HAL_PIN_NC;
    cfg->st1 = HAL_PIN_NC;
    
    cfg->gpio_sel = IBUTTON_GPIO_1;
}

void ibutton_gpio_selection ( ibutton_cfg_t *cfg, ibutton_gpio_sel_t gpio_sel ) 
{
    cfg->gpio_sel = gpio_sel;
}

err_t ibutton_init ( ibutton_t *ctx, ibutton_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = ( cfg->gpio_sel == IBUTTON_GPIO_0 ) ? cfg->gp0 : cfg->gp1;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    // Output pins
    digital_out_init( &ctx->st2, cfg->st2 );
    digital_out_init( &ctx->st1, cfg->st1 );

    digital_out_high( &ctx->st2 );
    digital_out_high( &ctx->st1 );

    memset ( ctx->key_rom, 0, sizeof ( ctx->key_rom ) );
    ctx->num_keys = 0;

    return ONE_WIRE_SUCCESS;
}

err_t ibutton_add_key ( ibutton_t *ctx )
{
    one_wire_rom_address_t rom_addr;
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &rom_addr ) )
    {
        return IBUTTON_ERROR;
    }
    if ( ( IBUTTON_FAMILY_CODE != rom_addr.address[ 0 ] ) || 
         ( rom_addr.address[ 7 ] != ibutton_calculate_crc8 ( &rom_addr.address[ 0 ], 7 ) ) )
    {
        return IBUTTON_ERROR;
    }
    for ( uint8_t key_cnt = 0; key_cnt < ctx->num_keys; key_cnt++ )
    {
        if ( !memcmp ( &ctx->key_rom[ key_cnt ], &rom_addr, sizeof ( rom_addr ) ) )
        {
            return IBUTTON_KEY_ALREADY_EXIST;
        }
    }
    ctx->num_keys += 1;
    if ( ctx->num_keys > IBUTTON_MAX_KEY_NUMBER )
    {
        ctx->num_keys = 1;
    }
    memcpy ( &ctx->key_rom[ ctx->num_keys - 1 ], &rom_addr, sizeof ( rom_addr ) );
    return IBUTTON_OK;
}

void ibutton_remove_keys ( ibutton_t *ctx )
{
    memset ( ctx->key_rom, 0, sizeof ( ctx->key_rom ) );
    ctx->num_keys = 0;
}

err_t ibutton_check_key ( ibutton_t *ctx )
{
    one_wire_rom_address_t rom_addr;
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &rom_addr ) )
    {
        return IBUTTON_ERROR;
    }
    if ( ( IBUTTON_FAMILY_CODE != rom_addr.address[ 0 ] ) || 
         ( rom_addr.address[ 7 ] != ibutton_calculate_crc8 ( &rom_addr.address[ 0 ], 7 ) ) )
    {
        return IBUTTON_ERROR;
    }
    for ( uint8_t key_cnt = 0; key_cnt < ctx->num_keys; key_cnt++ )
    {
        if ( !memcmp ( &ctx->key_rom[ key_cnt ], &rom_addr, sizeof ( rom_addr ) ) )
        {
            return IBUTTON_OK;
        }
    }
    return IBUTTON_KEY_NO_MATCH;
}

void ibutton_enable_red_led ( ibutton_t *ctx )
{
    digital_out_low ( &ctx->st2 );
}

void ibutton_disable_red_led ( ibutton_t *ctx )
{
    digital_out_high ( &ctx->st2 );
}

void ibutton_enable_green_led ( ibutton_t *ctx )
{
    digital_out_low ( &ctx->st1 );
}

void ibutton_disable_green_led ( ibutton_t *ctx )
{
    digital_out_high ( &ctx->st1 );
}

static uint8_t ibutton_calculate_crc8 ( uint8_t *data_buf, uint8_t len )
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
