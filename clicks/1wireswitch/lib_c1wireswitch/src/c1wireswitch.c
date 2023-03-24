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
 * @file c1wireswitch.c
 * @brief 1-Wire Switch Click Driver.
 */

#include "c1wireswitch.h"

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x31 (x8 + x5 + x4 + 1 )
 * @li @c  Initialization 0x00
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t c1wireswitch_calculate_crc8 ( uint8_t *data_buf, uint8_t len );

void c1wireswitch_cfg_setup ( c1wireswitch_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->gp0 = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    
    cfg->gpio_sel = C1WIRESWITCH_GPIO_1;
}

void c1wireswitch_gpio_selection ( c1wireswitch_cfg_t *cfg, c1wireswitch_gpio_sel_t gpio_sel ) 
{
    cfg->gpio_sel = gpio_sel;
}

err_t c1wireswitch_init ( c1wireswitch_t *ctx, c1wireswitch_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = ( cfg->gpio_sel == C1WIRESWITCH_GPIO_0 ) ? cfg->gp0 : cfg->gp1;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t c1wireswitch_default_cfg ( c1wireswitch_t *ctx ) 
{
    err_t error_flag = C1WIRESWITCH_OK;
    ctx->address = C1WIRESWITCH_ADDRESS;
    if ( C1WIRESWITCH_ERROR == c1wireswitch_check_communication ( ctx ) )
    {
        return C1WIRESWITCH_ERROR;
    }
    error_flag = c1wireswitch_set_pio_state( ctx, C1WIRESWITCH_PIOA_OFF, C1WIRESWITCH_PIOB_OFF );
    return error_flag;
}

err_t c1wireswitch_check_communication ( c1wireswitch_t *ctx )
{
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return C1WIRESWITCH_ERROR;
    }
    if ( C1WIRESWITCH_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return C1WIRESWITCH_ERROR;
    }
    if ( ctx->rom_addr.address[ 7 ] != c1wireswitch_calculate_crc8( &ctx->rom_addr.address[ 0 ], 7 ) )
    {
        return C1WIRESWITCH_ERROR;
    }
    return C1WIRESWITCH_OK;
}

err_t c1wireswitch_select_device ( c1wireswitch_t *ctx )
{
    if ( C1WIRESWITCH_ADDRESS_ALL == ctx->address )
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

err_t c1wireswitch_read_scratchpad ( c1wireswitch_t *ctx, uint8_t *scratchpad, uint8_t scratchpad_len )
{
    err_t error_flag = C1WIRESWITCH_OK;
    uint8_t data_buf[ 255 ] = { 0 };
    uint8_t command = C1WIRESWITCH_CMD_READ_SCRATCHPAD;
    
    error_flag |= c1wireswitch_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, scratchpad_len );

    if ( ( C1WIRESWITCH_OK == error_flag ) && 
         ( data_buf[ scratchpad_len ] == c1wireswitch_calculate_crc8( data_buf, scratchpad_len ) ) )
    {
        memcpy ( scratchpad, data_buf, scratchpad_len );
        return C1WIRESWITCH_OK;
    }
    return C1WIRESWITCH_ERROR;
}

err_t c1wireswitch_write_scratchpad ( c1wireswitch_t *ctx, uint8_t *scratchpad, uint8_t scratchpad_len )
{
    err_t error_flag = C1WIRESWITCH_OK;
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = C1WIRESWITCH_CMD_WRITE_SCRATCHPAD;
    memcpy ( &data_buf[ 1 ], scratchpad, scratchpad_len );
    error_flag |= c1wireswitch_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, scratchpad_len + 1 );
    return error_flag;
}

err_t c1wireswitch_write_pio ( c1wireswitch_t *ctx, uint8_t state )
{
    err_t error_flag = C1WIRESWITCH_OK;
    uint8_t tx_data[ 2 ] = { 0 };
    
    tx_data[ 0 ] = 0xFC | state;
    tx_data[ 1 ] = ~tx_data[ 0 ];
    
    error_flag = c1wireswitch_write_scratchpad( ctx, tx_data, 2 );
    
    return error_flag;
}

err_t c1wireswitch_read_pio ( c1wireswitch_t *ctx, uint8_t *state )
{
    err_t error_flag = C1WIRESWITCH_OK;
    uint8_t rx_data;
    uint8_t command = C1WIRESWITCH_CMD_READ_PIO;
    
    error_flag |= c1wireswitch_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    
    error_flag |= one_wire_read_byte( &ctx->ow, &rx_data, 1 );
    
    if ( ( rx_data & 0x0F ) && ( ~rx_data >> 4 ) )
    {
        *state = rx_data;
    }
    else
    {
        error_flag = C1WIRESWITCH_ERROR;
    }
    
    return error_flag;
}

err_t c1wireswitch_set_pio_state ( c1wireswitch_t *ctx, uint8_t pio_a, uint8_t pio_b )
{
    err_t error_flag = C1WIRESWITCH_OK;
    uint8_t tx_data;
    tx_data = pio_b | pio_a;
    
    error_flag = c1wireswitch_write_pio( ctx, tx_data );
    
    return error_flag;
}

err_t c1wireswitch_get_pio_state ( c1wireswitch_t *ctx, uint8_t *pio_a, uint8_t *pio_b )
{
    err_t error_flag = C1WIRESWITCH_OK;
    uint8_t rx_data;
    
    error_flag = c1wireswitch_read_pio( ctx, &rx_data );
    
    *pio_a = ( rx_data & C1WIRESWITCH_PIOA_STATE_MASK );
    *pio_b = ( rx_data & C1WIRESWITCH_PIOB_STATE_MASK );
    
    return error_flag;
}

err_t c1wireswitch_get_pio_latch_state ( c1wireswitch_t *ctx, uint8_t *pio_a_latch, uint8_t *pio_b_latch )
{
     err_t error_flag = C1WIRESWITCH_OK;
    uint8_t rx_data;
    
    error_flag = c1wireswitch_read_pio( ctx, &rx_data );
    
    *pio_a_latch = ( rx_data & C1WIRESWITCH_PIOA_LATCH_STATE_MASK );
    *pio_b_latch = ( rx_data & C1WIRESWITCH_PIOB_LATCH_STATE_MASK );
    
    return error_flag;
}

static uint8_t c1wireswitch_calculate_crc8 ( uint8_t *data_buf, uint8_t len )
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
