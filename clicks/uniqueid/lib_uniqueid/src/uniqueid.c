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
 * @file uniqueid.c
 * @brief UNIQUE ID Click Driver.
 */

#include "uniqueid.h"

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
static uint8_t uniqueid_calculate_crc8_maxim( uint8_t *data_buf, uint8_t len );

void uniqueid_cfg_setup ( uniqueid_cfg_t *cfg ) 
{
    // Communication GPIO pins
    cfg->gp0 = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    
    cfg->gpio_sel = UNIQUEID_GPIO_0;
}

void uniqueid_gpio_selection ( uniqueid_cfg_t *cfg, uniqueid_gpio_sel_t gpio_sel ) 
{
    cfg->gpio_sel = gpio_sel;
}

err_t uniqueid_init ( uniqueid_t *ctx, uniqueid_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = ( cfg->gpio_sel == UNIQUEID_GPIO_0 ) ? cfg->gp0 : cfg->gp1;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t uniqueid_read_id ( uniqueid_t *ctx, uint8_t *family, uint8_t *serial_num )
{
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return UNIQUEID_ERROR;
    }
    if ( UNIQUEID_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return UNIQUEID_ERROR;
    }
    *family = ctx->rom_addr.address[ 0 ];
    if ( ctx->rom_addr.address[ 7 ] != uniqueid_calculate_crc8_maxim( &ctx->rom_addr.address[ 0 ], 7 ) )
    {
        return  UNIQUEID_ERROR; 
    }
    memcpy( serial_num, &ctx->rom_addr.address[ 1 ], 6 );
    
    return UNIQUEID_OK;
}

static uint8_t uniqueid_calculate_crc8_maxim( uint8_t *data_buf, uint8_t len )
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
