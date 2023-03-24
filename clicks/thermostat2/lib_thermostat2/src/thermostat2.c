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
 * @file thermostat2.c
 * @brief Thermostat 2 Click Driver.
 */

#include "thermostat2.h"

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
static uint8_t thermostat2_calculate_crc8_maxim( uint8_t *data_buf, uint8_t len );

void thermostat2_cfg_setup ( thermostat2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->gp0 = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
}

err_t thermostat2_init ( thermostat2_t *ctx, thermostat2_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = cfg->gp0; 

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }
    
    digital_out_init( &ctx->cs, cfg->cs );

    return ONE_WIRE_SUCCESS;
}

err_t thermostat2_default_cfg ( thermostat2_t *ctx )
{
    err_t error_flag = THERMOSTAT2_OK;
    
    error_flag |= thermostat2_check_communication ( ctx );
    
    error_flag |= thermostat2_write_scratchpad ( ctx, THERMOSTAT2_DEFAULT_TEMP_HIGH_ALARM, 
                                                 THERMOSTAT2_DEFAULT_TEMP_LOW_ALARM, 
                                                 THERMOSTAT2_DEFAULT_RESOLUTION );
    thermostat2_relay_state ( ctx, THERMOSTAT2_RELAY_OFF );
    
    return error_flag;
}

err_t thermostat2_check_communication ( thermostat2_t *ctx )
{
    one_wire_rom_address_t search_rom_addr;
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return THERMOSTAT2_ERROR;
    }
    if ( THERMOSTAT2_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return THERMOSTAT2_ERROR;
    }
    if ( ONE_WIRE_ERROR == one_wire_search_first_device ( &ctx->ow, &search_rom_addr ) )
    {
        return THERMOSTAT2_ERROR;
    }
    if ( memcmp ( &ctx->rom_addr, &search_rom_addr, sizeof ( one_wire_rom_address_t ) ) )
    {
        return THERMOSTAT2_ERROR;
    }
    return THERMOSTAT2_OK;
}

err_t thermostat2_read_scratchpad ( thermostat2_t *ctx, uint8_t *scratchpad )
{
    err_t error_flag = THERMOSTAT2_OK;
    uint8_t data_buf[ 9 ] = { 0 };
    uint8_t command = THERMOSTAT2_CMD_READ_SCRATCHPAD;
    
    error_flag |= one_wire_match_rom( &ctx->ow, &ctx->rom_addr ); 
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, 9 );

    if ( ( THERMOSTAT2_OK == error_flag ) && 
         ( data_buf[ 8 ] == thermostat2_calculate_crc8_maxim ( data_buf, 8 ) ) )
    {
        memcpy ( scratchpad, data_buf, 5 );
        return THERMOSTAT2_OK;
    }
    return THERMOSTAT2_ERROR;
}

err_t thermostat2_write_scratchpad ( thermostat2_t *ctx, uint8_t temp_high, uint8_t temp_low, uint8_t config )
{
    err_t error_flag = THERMOSTAT2_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = THERMOSTAT2_CMD_WRITE_SCRATCHPAD;
    data_buf[ 1 ] = temp_high;
    data_buf[ 2 ] = temp_low;
    ctx->config = config & THERMOSTAT2_CONFIG_RESOLUTION_BIT_MASK;
    data_buf[ 3 ] = ctx->config | THERMOSTAT2_CONFIG_RESERVED_BITS;
    error_flag |= one_wire_match_rom( &ctx->ow, &ctx->rom_addr ); 
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 4 );
    return error_flag;
}

err_t thermostat2_start_measurement ( thermostat2_t *ctx )
{
    err_t error_flag = THERMOSTAT2_OK;
    error_flag |= one_wire_skip_rom( &ctx->ow );
    uint8_t command = THERMOSTAT2_CMD_CONVERT_TEMPERATURE;
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    return error_flag;
}

void thermostat2_relay_state ( thermostat2_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->cs, state ); 
}

err_t thermostat2_read_temperature ( thermostat2_t *ctx, float *temperature )
{
    err_t error_flag = THERMOSTAT2_OK;
    error_flag |= thermostat2_start_measurement( ctx );
    // For some DS18x20 it is required minimum 750ms for the data conversion.
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    
    uint8_t scratchpad[ 5 ];
    error_flag |= thermostat2_read_scratchpad ( ctx, scratchpad );
    int16_t raw_temp = ( ( int16_t ) scratchpad[ 1 ] << 8 ) | scratchpad[ 0 ];

    switch ( ctx->config & THERMOSTAT2_CONFIG_RESOLUTION_BIT_MASK )
    {
        case THERMOSTAT2_CONFIG_RESOLUTION_9BIT:
        {
            *temperature = raw_temp * THERMOSTAT2_RESOLUTION_9BIT;
            break;
        }
        case THERMOSTAT2_CONFIG_RESOLUTION_10BIT:
        {
            *temperature = raw_temp * THERMOSTAT2_RESOLUTION_10BIT;
            break;
        }
        case THERMOSTAT2_CONFIG_RESOLUTION_11BIT:
        {
            *temperature = raw_temp * THERMOSTAT2_RESOLUTION_11BIT;
            break;
        }
        case THERMOSTAT2_CONFIG_RESOLUTION_12BIT:
        {
            *temperature = raw_temp * THERMOSTAT2_RESOLUTION_12BIT;
            break;
        }
    }
    return error_flag;
}

static uint8_t thermostat2_calculate_crc8_maxim( uint8_t *data_buf, uint8_t len )
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
