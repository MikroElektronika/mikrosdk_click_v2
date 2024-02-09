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
 * @file charger.c
 * @brief Charger Click Driver.
 */

#include "charger.h"

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
static uint8_t charger_calculate_crc8 ( uint8_t *data_buf, uint8_t len );

void charger_cfg_setup ( charger_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->ow1 = HAL_PIN_NC;
    cfg->ow2 = HAL_PIN_NC;
    
    cfg->gpio_sel = CHARGER_GPIO_OW1;
}

void charger_gpio_selection ( charger_cfg_t *cfg, charger_gpio_sel_t gpio_sel ) 
{
    cfg->gpio_sel = gpio_sel;
}

err_t charger_init ( charger_t *ctx, charger_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = ( cfg->gpio_sel == CHARGER_GPIO_OW1 ) ? cfg->ow1 : cfg->ow2;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t charger_default_cfg ( charger_t *ctx ) 
{
    err_t error_flag = CHARGER_OK;
    ctx->address = CHARGER_ADDRESS_ALL;
    if ( CHARGER_ERROR == charger_check_communication ( ctx ) )
    {
        return CHARGER_ERROR;
    }
    return error_flag;
}

err_t charger_check_communication ( charger_t *ctx )
{
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return CHARGER_ERROR;
    }
    if ( CHARGER_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return CHARGER_ERROR;
    }
    if ( ctx->rom_addr.address[ 7 ] != charger_calculate_crc8 ( &ctx->rom_addr.address[ 0 ], 7 ) )
    {
        return CHARGER_ERROR;
    }
    return CHARGER_OK;
}

err_t charger_select_device ( charger_t *ctx )
{
    if ( CHARGER_ADDRESS_ALL == ctx->address )
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

err_t charger_read_scratchpad ( charger_t *ctx, uint8_t page, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = CHARGER_OK;
    uint8_t data_buf[ CHARGER_PAGE_SIZE + 1 ] = { 0 };
    if ( ( NULL == data_out ) || ( len > CHARGER_PAGE_SIZE ) || ( page > CHARGER_PAGE_7 ) )
    {
        return CHARGER_ERROR;
    }
    data_buf[ 0 ] = CHARGER_CMD_READ_SCRATCHPAD;
    data_buf[ 1 ] = page;
    error_flag |= charger_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 2 );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, CHARGER_PAGE_SIZE + 1 );

    if ( ( CHARGER_OK == error_flag ) && 
         ( data_buf[ CHARGER_PAGE_SIZE ] == charger_calculate_crc8 ( data_buf, CHARGER_PAGE_SIZE ) ) )
    {
        memcpy ( data_out, data_buf, len );
        return CHARGER_OK;
    }
    return CHARGER_ERROR;
}

err_t charger_write_scratchpad ( charger_t *ctx, uint8_t page, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = CHARGER_OK;
    uint8_t data_buf[ CHARGER_PAGE_SIZE + 2 ] = { 0 };
    if ( ( NULL == data_in ) || ( len > CHARGER_PAGE_SIZE ) || ( page > CHARGER_PAGE_7 ) )
    {
        return CHARGER_ERROR;
    }
    data_buf[ 0 ] = CHARGER_CMD_WRITE_SCRATCHPAD;
    data_buf[ 1 ] = page;
    memcpy ( &data_buf[ 2 ], data_in, len );
    error_flag |= charger_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, len + 2 );
    return error_flag;
}

err_t charger_copy_scratchpad ( charger_t *ctx, uint8_t page )
{
    err_t error_flag = CHARGER_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( page > CHARGER_PAGE_7 )
    {
        return CHARGER_ERROR;
    }
    data_buf[ 0 ] = CHARGER_CMD_COPY_SCRATCHPAD;
    data_buf[ 1 ] = page;
    error_flag |= charger_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 2 );
    Delay_10ms ( );
    return error_flag;
}

err_t charger_recall_memory ( charger_t *ctx, uint8_t page )
{
    err_t error_flag = CHARGER_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( page > CHARGER_PAGE_7 )
    {
        return CHARGER_ERROR;
    }
    data_buf[ 0 ] = CHARGER_CMD_RECALL_MEMORY;
    data_buf[ 1 ] = page;
    error_flag |= charger_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 2 );
    return error_flag;
}

err_t charger_convert_temperature ( charger_t *ctx )
{
    err_t error_flag = CHARGER_OK;
    uint8_t command = CHARGER_CMD_CONVERT_T;
    error_flag |= charger_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    Delay_10ms ( );
    return error_flag;
}

err_t charger_convert_voltage ( charger_t *ctx )
{
    err_t error_flag = CHARGER_OK;
    uint8_t command = CHARGER_CMD_CONVERT_V;
    error_flag |= charger_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    Delay_10ms ( );
    return error_flag;
}

err_t charger_read_temperature ( charger_t *ctx, float *temperature )
{
    err_t error_flag = CHARGER_OK;
    volatile int16_t raw_temp = 0;
    uint8_t data_buf[ 3 ] = { 0 };
    error_flag |= charger_convert_temperature ( ctx );
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_0 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 3 );
    if ( ( CHARGER_OK == error_flag ) && !( data_buf[ 0 ] & CHARGER_CONFIG_TB ) && ( NULL != temperature ) )
    {
        raw_temp = ( int16_t ) ( ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 1 ] );
        raw_temp >>= 3;
        *temperature = raw_temp * CHARGER_TEMPERATURE_RES;
    }
    else
    {
        error_flag = CHARGER_ERROR;
    }
    return error_flag;
}

err_t charger_read_batt_vdd ( charger_t *ctx, float *voltage )
{
    err_t error_flag = CHARGER_OK;
    uint16_t raw_vdd = 0;
    uint8_t data_buf[ 5 ] = { 0 };
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_0 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 1 );
    if ( CHARGER_CONFIG_AD != ( CHARGER_CONFIG_AD & data_buf[ 0 ] ) )
    {
        data_buf[ 0 ] |= CHARGER_CONFIG_AD;
        error_flag |= charger_write_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 1 );
        error_flag |= charger_copy_scratchpad ( ctx, CHARGER_PAGE_0 );
    }
    error_flag |= charger_convert_voltage ( ctx );
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_0 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 5 );
    if ( ( CHARGER_OK == error_flag ) && !( data_buf[ 0 ] & CHARGER_CONFIG_ADB ) && ( NULL != voltage ) )
    {
        raw_vdd = ( ( uint16_t ) ( data_buf[ 4 ] & 0x03 ) << 8 ) | data_buf[ 3 ];
        *voltage = raw_vdd * CHARGER_VOLTAGE_RES;
    }
    else
    {
        error_flag = CHARGER_ERROR;
    }
    return error_flag;
}

err_t charger_read_system_vdd ( charger_t *ctx, float *voltage )
{
    err_t error_flag = CHARGER_OK;
    uint16_t raw_vdd = 0;
    uint8_t data_buf[ 5 ] = { 0 };
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_0 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 1 );
    if ( CHARGER_CONFIG_AD == ( CHARGER_CONFIG_AD & data_buf[ 0 ] ) )
    {
        data_buf[ 0 ] &= ( ~CHARGER_CONFIG_AD );
        error_flag |= charger_write_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 1 );
        error_flag |= charger_copy_scratchpad ( ctx, CHARGER_PAGE_0 );
    }
    error_flag |= charger_convert_voltage ( ctx );
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_0 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 5 );
    if ( ( CHARGER_OK == error_flag ) && !( data_buf[ 0 ] & CHARGER_CONFIG_ADB ) && ( NULL != voltage ) )
    {
        raw_vdd = ( ( uint16_t ) ( data_buf[ 4 ] & 0x03 ) << 8 ) | data_buf[ 3 ];
        *voltage = raw_vdd * CHARGER_VOLTAGE_RES;
    }
    else
    {
        error_flag = CHARGER_ERROR;
    }
    return error_flag;
}

err_t charger_read_current ( charger_t *ctx, float *current )
{
    err_t error_flag = CHARGER_OK;
    volatile int16_t raw_i = 0;
    uint8_t data_buf[ 7 ] = { 0 };
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_0 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 1 );
    if ( CHARGER_CONFIG_IAD != ( CHARGER_CONFIG_IAD & data_buf[ 0 ] ) )
    {
        data_buf[ 0 ] |= CHARGER_CONFIG_IAD;
        error_flag |= charger_write_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 1 );
        error_flag |= charger_copy_scratchpad ( ctx, CHARGER_PAGE_0 );
        Delay_100ms ( );
    }
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_0 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 7 );
    if ( ( CHARGER_OK == error_flag ) && ( NULL != current ) )
    {
        raw_i = ( int16_t ) ( ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 5 ] );
        *current = raw_i / CHARGER_CURRENT_RES;
    }
    else
    {
        error_flag = CHARGER_ERROR;
    }
    return error_flag;
}

err_t charger_calibrate_current ( charger_t *ctx )
{
    err_t error_flag = CHARGER_OK;
    volatile int16_t raw_i = 0;
    uint8_t data_buf[ 7 ] = { 0 };
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_0 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 1 );
    if ( CHARGER_CONFIG_IAD == ( CHARGER_CONFIG_IAD & data_buf[ 0 ] ) )
    {
        data_buf[ 0 ] &= ( ~CHARGER_CONFIG_IAD );
        error_flag |= charger_write_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 1 );
        error_flag |= charger_copy_scratchpad ( ctx, CHARGER_PAGE_0 );
    }
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_1 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_1, data_buf, 7 );
    data_buf[ 5 ] = 0;
    data_buf[ 6 ] = 0;
    error_flag |= charger_write_scratchpad ( ctx, CHARGER_PAGE_1, data_buf, 7 );
    error_flag |= charger_copy_scratchpad ( ctx, CHARGER_PAGE_1 );
    
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_0 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 7 );
    if ( ( CHARGER_OK == error_flag ) )
    {
        raw_i = ( int16_t ) ( ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 5 ] );
        raw_i = -raw_i + 1;
        
        error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_1 );
        error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_1, data_buf, 7 );
        data_buf[ 5 ] = ( uint8_t ) ( raw_i & 0xFF );
        data_buf[ 6 ] = ( uint8_t ) ( ( raw_i >> 8 ) & 0xFF );
        error_flag |= charger_write_scratchpad ( ctx, CHARGER_PAGE_1, data_buf, 7 );
        error_flag |= charger_copy_scratchpad ( ctx, CHARGER_PAGE_1 );

        error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_0 );
        error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 1 );
        if ( CHARGER_CONFIG_IAD != ( CHARGER_CONFIG_IAD & data_buf[ 0 ] ) )
        {
            data_buf[ 0 ] |= CHARGER_CONFIG_IAD;
            error_flag |= charger_write_scratchpad ( ctx, CHARGER_PAGE_0, data_buf, 1 );
            error_flag |= charger_copy_scratchpad ( ctx, CHARGER_PAGE_0 );
            Delay_100ms ( );
        }
    }
    else
    {
        error_flag = CHARGER_ERROR;
    }
    return error_flag;
}

err_t charger_write_elapsed_time ( charger_t *ctx, uint32_t seconds )
{
    err_t error_flag = CHARGER_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_1 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_1, data_buf, 4 );
    if ( CHARGER_OK == error_flag )
    {
        data_buf[ 3 ] = ( uint8_t ) ( ( seconds >> 24 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( ( seconds >> 16 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( seconds >> 8 ) & 0xFF );
        data_buf[ 0 ] = ( uint8_t ) ( seconds & 0xFF );
        error_flag |= charger_write_scratchpad ( ctx, CHARGER_PAGE_1, data_buf, 4 );
        error_flag |= charger_copy_scratchpad ( ctx, CHARGER_PAGE_1 );
    }
    else
    {
        error_flag = CHARGER_ERROR;
    }
    return error_flag;
}

err_t charger_read_elapsed_time ( charger_t *ctx, uint32_t *seconds )
{
    err_t error_flag = CHARGER_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    error_flag |= charger_recall_memory ( ctx, CHARGER_PAGE_1 );
    error_flag |= charger_read_scratchpad ( ctx, CHARGER_PAGE_1, data_buf, 4 );
    if ( ( CHARGER_OK == error_flag ) && ( NULL != seconds ) )
    {
        *seconds = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) |
                   ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    else
    {
        error_flag = CHARGER_ERROR;
    }
    return error_flag;
}

static uint8_t charger_calculate_crc8 ( uint8_t *data_buf, uint8_t len )
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
