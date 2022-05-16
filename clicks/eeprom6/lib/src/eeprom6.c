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
 * @file eeprom6.c
 * @brief EEPROM 6 Click Driver.
 */

#include "eeprom6.h"

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
static uint8_t eeprom6_calculate_crc8_maxim( uint8_t *data_buf, uint8_t len );

void eeprom6_cfg_setup ( eeprom6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->gp0 = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    
    cfg->gpio_sel = EEPROM6_GPIO_0;
}

void eeprom6_gpio_selection ( eeprom6_cfg_t *cfg, eeprom6_gpio_sel_t gpio_sel ) 
{
    cfg->gpio_sel = gpio_sel;
}

err_t eeprom6_init ( eeprom6_t *ctx, eeprom6_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = ( cfg->gpio_sel == EEPROM6_GPIO_0 ) ? cfg->gp0 : cfg->gp1;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t eeprom6_default_cfg ( eeprom6_t *ctx ) 
{
    err_t error_flag = EEPROM6_OK;

    ctx->address = EEPROM6_ADDRESS_ALL;
    
    if ( EEPROM6_ERROR == eeprom6_check_communication ( ctx ) )
    {
        return EEPROM6_ERROR;
    }

    return error_flag;
}

err_t eeprom6_check_communication ( eeprom6_t *ctx )
{
    one_wire_rom_address_t search_rom_addr;
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return EEPROM6_ERROR;
    }
    if ( EEPROM6_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return EEPROM6_ERROR;
    }
    if ( ONE_WIRE_ERROR == one_wire_search_first_device ( &ctx->ow, &search_rom_addr ) )
    {
        return EEPROM6_ERROR;
    }
    if ( memcmp ( &ctx->rom_addr, &search_rom_addr, sizeof ( one_wire_rom_address_t ) ) )
    {
        return EEPROM6_ERROR;
    }
    return EEPROM6_OK;
}

err_t eeprom6_select_device ( eeprom6_t *ctx )
{
    if ( EEPROM6_ADDRESS_ALL == ctx->address )
    {
        // One Wire Reset sequence and "Skip ROM" command.
        return one_wire_skip_rom( &ctx->ow );
    }
    else
    {
        // One Wire Reset sequence and "Match ROM" command.
        return one_wire_match_rom( &ctx->ow, ctx->rom_addr );
    }
}

err_t eeprom6_read_scratchpad ( eeprom6_t *ctx, uint8_t *scratchpad, uint8_t scratchpad_len )
{
    err_t error_flag = EEPROM6_OK;
    uint8_t data_buf[ 255 ] = { 0 };
    uint8_t command = EEPROM6_CMD_READ_SCRATCHPAD;
    
    error_flag |= eeprom6_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, scratchpad_len );

    if ( ( EEPROM6_OK == error_flag ) && 
         ( data_buf[ scratchpad_len ] == eeprom6_calculate_crc8_maxim ( data_buf, scratchpad_len ) ) )
    {
        memcpy ( scratchpad, data_buf, scratchpad_len );
        return EEPROM6_OK;
    }
    return EEPROM6_ERROR;
}

err_t eeprom6_write_scratchpad ( eeprom6_t *ctx, uint8_t *scratchpad, uint8_t scratchpad_len )
{
    err_t error_flag = EEPROM6_OK;
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = EEPROM6_CMD_WRITE_SCRATCHPAD;
    memcpy ( &data_buf[ 1 ], scratchpad, scratchpad_len );
    error_flag |= eeprom6_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, scratchpad_len + 1 );
    return error_flag;
}

err_t eeprom6_read_mem ( eeprom6_t *ctx, uint16_t reg_adr, uint8_t *data_out, uint16_t data_len )
{
    err_t error_flag = EEPROM6_OK;
    uint8_t command = EEPROM6_CMD_READ_MEMORY;
    error_flag |= eeprom6_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );

    uint8_t t_adr_1 = ( uint8_t )( reg_adr & 0xFF );
    uint8_t t_adr_2 = ( uint8_t )( ( reg_adr >> 8 ) & 0xFF );
    error_flag |= one_wire_write_byte( &ctx->ow, &t_adr_1, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, &t_adr_2, 1 );
    
    error_flag |= one_wire_read_byte( &ctx->ow, data_out, data_len );   
    return error_flag;
}

err_t eeprom6_write_mem ( eeprom6_t *ctx, uint16_t reg_adr, uint8_t *data_in, uint16_t data_len )
{    
    uint8_t t_adr_1 = ( uint8_t ) ( reg_adr & 0xFF );
    uint8_t t_adr_2 = ( uint8_t ) ( ( reg_adr >> 8 ) & 0xFF );
    uint8_t tmp_val;
    err_t error_flag = EEPROM6_OK;
    uint8_t command = EEPROM6_CMD_WRITE_SCRATCHPAD;
    error_flag |= eeprom6_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, &t_adr_1, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, &t_adr_2, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, data_in, data_len );    
    
    error_flag |= eeprom6_select_device ( ctx );
    command = EEPROM6_CMD_READ_SCRATCHPAD;
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    
    error_flag |= one_wire_read_byte( &ctx->ow, &tmp_val, 1 );
    
    if ( tmp_val != t_adr_1 )
    {
        return EEPROM6_ERROR;
    }
    
    error_flag |= one_wire_read_byte( &ctx->ow, &tmp_val, 1 );
    
    if ( tmp_val != t_adr_2 )
    {
        return EEPROM6_ERROR;
    }
    
    uint8_t e_adr;
    error_flag |= one_wire_read_byte( &ctx->ow, &e_adr, 1);
    uint8_t n_cnt_j = 0;
    for ( n_cnt_j = 0 ; n_cnt_j < data_len; n_cnt_j++ )
    {
        error_flag |= one_wire_read_byte( &ctx->ow, &tmp_val, 1);
        if ( tmp_val != *( data_in + n_cnt_j ) )
        {
            return EEPROM6_ERROR;
        }
    }
            
    Delay_10ms( );
    error_flag |= eeprom6_select_device ( ctx );
    command = EEPROM6_CMD_COPY_SCRATCHPAD;
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, &t_adr_1, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, &t_adr_2, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, &e_adr, 1 );
    Delay_10ms( );
    
    return error_flag;
}

static uint8_t eeprom6_calculate_crc8_maxim( uint8_t *data_buf, uint8_t len )
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
