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
 * @file thermo2.c
 * @brief Thermo 2 Click Driver.
 */

#include "thermo2.h"

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
static uint8_t thermo2_calculate_crc8_maxim( uint8_t *data_buf, uint8_t len );

void thermo2_cfg_setup ( thermo2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->gp0 = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    
    cfg->gpio_sel = THERMO2_GPIO_0;
}

void thermo2_gpio_selection ( thermo2_cfg_t *cfg, thermo2_gpio_sel_t gpio_sel ) 
{
    cfg->gpio_sel = gpio_sel;
}

err_t thermo2_init ( thermo2_t *ctx, thermo2_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = ( cfg->gpio_sel == THERMO2_GPIO_0 ) ? cfg->gp0 : cfg->gp1;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t thermo2_default_cfg ( thermo2_t *ctx ) 
{
    err_t error_flag = THERMO2_OK;
    
    error_flag |= thermo2_check_communication ( ctx );
    
    error_flag |= thermo2_write_scratchpad ( ctx, THERMO2_DEFAULT_TEMP_HIGH_ALARM, THERMO2_DEFAULT_TEMP_LOW_ALARM, 
                                             THERMO2_DEFAULT_ADDRESS | THERMO2_DEFAULT_RESOLUTION );
    
    return error_flag;
}

err_t thermo2_check_communication ( thermo2_t *ctx )
{
    one_wire_rom_address_t search_rom_addr;
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return THERMO2_ERROR;
    }
    if ( THERMO2_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return THERMO2_ERROR;
    }
    if ( ONE_WIRE_ERROR == one_wire_search_first_device ( &ctx->ow, &search_rom_addr ) )
    {
        return THERMO2_ERROR;
    }
    if ( memcmp ( &ctx->rom_addr, &search_rom_addr, sizeof ( one_wire_rom_address_t ) ) )
    {
        return THERMO2_ERROR;
    }
    return THERMO2_OK;
}

err_t thermo2_select_device ( thermo2_t *ctx )
{
    if ( ctx->config & THERMO2_CONFIG_ADDRESS_ALL )
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

err_t thermo2_start_measurement ( thermo2_t *ctx )
{
    err_t error_flag = THERMO2_OK;
    // "Convert Temperature" command.
    error_flag |= thermo2_select_device( ctx );
    uint8_t command = THERMO2_CMD_CONVERT_TEMPERATURE;
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    return error_flag;
}

err_t thermo2_read_scratchpad ( thermo2_t *ctx, uint8_t *scratchpad )
{
    err_t error_flag = THERMO2_OK;
    uint8_t data_buf[ 9 ];
    uint8_t command = THERMO2_CMD_READ_SCRATCHPAD;
    
    error_flag |= thermo2_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, 9 );

    if ( ( THERMO2_OK == error_flag ) && 
         ( data_buf[ 8 ] == thermo2_calculate_crc8_maxim ( data_buf, 8 ) ) )
    {
        if ( THERMO2_CONFIG_ADDRESS_ALL != ( ctx->config & THERMO2_CONFIG_ADDRESS_ALL ) )
        {
            if ( ( ctx->config & THERMO2_CONFIG_ADDRESS_15 ) != ( data_buf[ 4 ] & THERMO2_CONFIG_ADDRESS_15 ) )
            {
                return THERMO2_ERROR;
            }
        }
        memcpy ( scratchpad, data_buf, 5 );
        return THERMO2_OK;
    }
    return THERMO2_ERROR;
}

err_t thermo2_write_scratchpad ( thermo2_t *ctx, uint8_t temp_high, uint8_t temp_low, uint8_t config )
{
    err_t error_flag = THERMO2_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = THERMO2_CMD_WRITE_SCRATCHPAD;
    data_buf[ 1 ] = temp_high;
    data_buf[ 2 ] = temp_low;
    ctx->config = ( config & THERMO2_CONFIG_ADDRESS_BIT_MASK ) | ( config & THERMO2_CONFIG_RESOLUTION_BIT_MASK );
    data_buf[ 3 ] = ctx->config | THERMO2_CONFIG_RESERVED_BITS;
    
    error_flag |= thermo2_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 4 );
    return error_flag;
}

err_t thermo2_read_temperature ( thermo2_t *ctx, float *temperature )
{
    err_t error_flag = THERMO2_OK;
    error_flag |= thermo2_start_measurement( ctx );
    // Wait for temperature conversion to be done.
    switch ( ctx->config & THERMO2_CONFIG_RESOLUTION_BIT_MASK )
    {
        case THERMO2_CONFIG_RESOLUTION_9BIT:
        {
            // At least 93.75ms delay is required for conversion
            Delay_100ms( );
            break;
        }
        case THERMO2_CONFIG_RESOLUTION_10BIT:
        {
            // At least 187.5ms delay is required for conversion
            Delay_100ms( );
            Delay_100ms( );
            break;
        }
        case THERMO2_CONFIG_RESOLUTION_11BIT:
        {
            // At least 375ms delay is required for conversion
            Delay_100ms( );
            Delay_100ms( );
            Delay_100ms( );
            Delay_100ms( );
            break;
        }
        case THERMO2_CONFIG_RESOLUTION_12BIT:
        {
            // At least 750ms delay is required for conversion
            Delay_100ms( );
            Delay_100ms( );
            Delay_100ms( );
            Delay_100ms( );
            Delay_100ms( );
            Delay_100ms( );
            Delay_100ms( );
            Delay_100ms( );
            break;
        }
    }
    uint8_t scratchpad[ 5 ];
    error_flag |= thermo2_read_scratchpad ( ctx, scratchpad );
    int16_t raw_temp = ( ( int16_t ) scratchpad[ 1 ] << 8 ) | scratchpad[ 0 ];
    *temperature = raw_temp * THERMO2_DATA_RESOLUTION;
    return error_flag;
}

static uint8_t thermo2_calculate_crc8_maxim( uint8_t *data_buf, uint8_t len )
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
