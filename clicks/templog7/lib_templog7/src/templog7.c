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
 * @file templog7.c
 * @brief Temp-Log 7 Click Driver.
 */

#include "templog7.h"

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
static uint8_t templog7_calculate_crc8 ( uint8_t *data_buf, uint8_t len );

void templog7_cfg_setup ( templog7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->gp0 = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    
    cfg->gpio_sel = TEMPLOG7_GPIO_0;
}

void templog7_gpio_selection ( templog7_cfg_t *cfg, templog7_gpio_sel_t gpio_sel ) 
{
    cfg->gpio_sel = gpio_sel;
}

err_t templog7_init ( templog7_t *ctx, templog7_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = ( cfg->gpio_sel == TEMPLOG7_GPIO_0 ) ? cfg->gp0 : cfg->gp1;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    // Input pins
    digital_in_init( &ctx->alert, cfg->alert );

    return ONE_WIRE_SUCCESS;
}

err_t templog7_default_cfg ( templog7_t *ctx ) 
{
    err_t error_flag = TEMPLOG7_OK;
    templog7_scratchpad_1_t scratchpad_1 = { 0 };
    ctx->address = TEMPLOG7_ADDRESS_ALL;
    if ( TEMPLOG7_ERROR == templog7_check_communication ( ctx ) )
    {
        return TEMPLOG7_ERROR;
    }
    error_flag |= templog7_clear_eeprom ( ctx );
    scratchpad_1.config_1 = TEMPLOG7_CFG1_TEMP_FMT_16_BIT | 
                            TEMPLOG7_CFG1_CONV_TIME_SEL_5p5MS | 
                            TEMPLOG7_CFG1_ALERT_MODE_COMPARATOR | 
                            TEMPLOG7_CFG1_AVG_SEL_NO_AVG | 
                            TEMPLOG7_CFG1_CONV_MODE_SEL_ONE_SHOT;
    scratchpad_1.config_2 = TEMPLOG7_CFG2_OD_DIS | 
                            TEMPLOG7_CFG2_FLEX_ADDR_MODE_HOST | 
                            TEMPLOG7_CFG2_ARB_MODE_DIS | 
                            TEMPLOG7_CFG2_HYSTERESIS_5_C | 
                            TEMPLOG7_CFG2_LOCK_DIS;
    scratchpad_1.short_addr = TEMPLOG7_ADDRESS_0;
    if ( 0 != TEMPLOG7_TEMP_ALERT_LOW )
    {
        scratchpad_1.temp_limit_low = ( int16_t ) ( TEMPLOG7_TEMP_ALERT_LOW / TEMPLOG7_TEMP_RES_16BIT );
    }
    if ( 0 != TEMPLOG7_TEMP_ALERT_HIGH )
    {
        scratchpad_1.temp_limit_high = ( int16_t ) ( TEMPLOG7_TEMP_ALERT_HIGH / TEMPLOG7_TEMP_RES_16BIT );
    }
    if ( 0 != TEMPLOG7_TEMP_OFFSET )
    {
        scratchpad_1.temp_offset = ( int16_t ) ( TEMPLOG7_TEMP_OFFSET / TEMPLOG7_TEMP_RES_16BIT );
    }
    error_flag |= templog7_write_scratchpad_1 ( ctx, &scratchpad_1 );
    error_flag |= templog7_copy_scratchpad_1 ( ctx );
    
    error_flag |= templog7_write_gpio ( ctx, TEMPLOG7_IO_CFG_IO3_SEL_INPUT | 
                                             TEMPLOG7_IO_CFG_IO2_SEL_ALERT | 
                                             TEMPLOG7_IO_CFG_IO1_SEL_INPUT | 
                                             TEMPLOG7_IO_CFG_IO0_SEL_INPUT );
    return error_flag;
}

err_t templog7_check_communication ( templog7_t *ctx )
{
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return TEMPLOG7_ERROR;
    }
    if ( TEMPLOG7_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return TEMPLOG7_ERROR;
    }
    if ( ctx->rom_addr.address[ 7 ] != templog7_calculate_crc8 ( &ctx->rom_addr.address[ 0 ], 7 ) )
    {
        return TEMPLOG7_ERROR;
    }
    return TEMPLOG7_OK;
}

err_t templog7_select_device ( templog7_t *ctx )
{
    if ( TEMPLOG7_ADDRESS_ALL == ctx->address )
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

err_t templog7_write_scratchpad_1 ( templog7_t *ctx, templog7_scratchpad_1_t *scratchpad )
{
    err_t error_flag = TEMPLOG7_OK;
    uint8_t command = TEMPLOG7_CMD_WRITE_SCRATCHPAD_1;
    uint8_t data_buf[ 9 ] = { 0 };
    uint8_t crc_byte = 0;
    if ( NULL == scratchpad )
    {
        return TEMPLOG7_ERROR;
    }
    data_buf[ 0 ] = scratchpad->config_1 | TEMPLOG7_CFG1_RESERVED;
    data_buf[ 1 ] = scratchpad->config_2;
    data_buf[ 2 ] = scratchpad->short_addr;
    data_buf[ 3 ] = ( uint8_t ) ( scratchpad->temp_limit_low & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( scratchpad->temp_limit_low >> 8 ) & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( scratchpad->temp_limit_high & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( ( scratchpad->temp_limit_high >> 8 ) & 0xFF );
    data_buf[ 7 ] = ( uint8_t ) ( scratchpad->temp_offset & 0xFF );
    data_buf[ 8 ] = ( uint8_t ) ( ( scratchpad->temp_offset >> 8 ) & 0xFF );
    error_flag |= templog7_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 9 );
    error_flag |= one_wire_read_byte( &ctx->ow, &crc_byte, 1 );
    if ( ( TEMPLOG7_OK == error_flag ) && 
         ( crc_byte == templog7_calculate_crc8 ( data_buf, 9 ) ) )
    {
        return TEMPLOG7_OK;
    }
    return TEMPLOG7_ERROR;
}

err_t templog7_read_scratchpad_1 ( templog7_t *ctx, templog7_scratchpad_1_t *scratchpad )
{
    err_t error_flag = TEMPLOG7_OK;
    uint8_t command = TEMPLOG7_CMD_READ_SCRATCHPAD_1;
    uint8_t data_buf[ 18 ] = { 0 };
    if ( NULL == scratchpad )
    {
        return TEMPLOG7_ERROR;
    }
    error_flag |= templog7_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, 18 );
    if ( ( TEMPLOG7_OK == error_flag ) &&
         ( data_buf[ 8 ] == templog7_calculate_crc8 ( &data_buf[ 0 ], 8 ) ) &&
         ( data_buf[ 17 ] == templog7_calculate_crc8 ( &data_buf[ 9 ], 8 ) ) )
    {
        scratchpad->temperature = ( ( int16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        scratchpad->status = data_buf[ 2 ];
        scratchpad->config_1 = data_buf[ 4 ];
        scratchpad->config_2 = data_buf[ 5 ];
        scratchpad->short_addr = data_buf[ 6 ];
        scratchpad->temp_limit_low = ( ( int16_t ) data_buf[ 10 ] << 8 ) | data_buf[ 9 ];
        scratchpad->temp_limit_high = ( ( int16_t ) data_buf[ 12 ] << 8 ) | data_buf[ 11 ];
        scratchpad->temp_offset = ( ( int16_t ) data_buf[ 14 ] << 8 ) | data_buf[ 13 ];
        return TEMPLOG7_OK;
    }
    return TEMPLOG7_ERROR;
}

err_t templog7_copy_scratchpad_1 ( templog7_t *ctx )
{
    err_t error_flag = TEMPLOG7_OK;
    uint8_t command = TEMPLOG7_CMD_COPY_SCRATCHPAD_1;
    error_flag |= templog7_select_device( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    return error_flag;
}

err_t templog7_write_scratchpad_2 ( templog7_t *ctx, templog7_scratchpad_2_t *scratchpad )
{
    err_t error_flag = TEMPLOG7_OK;
    uint8_t command = TEMPLOG7_CMD_WRITE_SCRATCHPAD_2;
    uint8_t data_buf[ TEMPLOG7_EEPROM_ADDR_BLOCK + 2 ] = { 0 };
    uint8_t crc_byte = 0;
    if ( ( NULL == scratchpad ) || 
         ( scratchpad->address > TEMPLOG7_EEPROM_ADDR_MAX ) || 
         ( scratchpad->address % TEMPLOG7_EEPROM_ADDR_BLOCK ) )
    {
        return TEMPLOG7_ERROR;
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( scratchpad->address >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( scratchpad->address & 0xFF );
    memcpy ( &data_buf[ 2 ], scratchpad->data_buf, TEMPLOG7_EEPROM_ADDR_BLOCK );
    error_flag |= templog7_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, TEMPLOG7_EEPROM_ADDR_BLOCK + 2 );
    error_flag |= one_wire_read_byte( &ctx->ow, &crc_byte, 1 );
    if ( ( TEMPLOG7_OK == error_flag ) && 
         ( crc_byte == templog7_calculate_crc8 ( data_buf, TEMPLOG7_EEPROM_ADDR_BLOCK + 2 ) ) )
    {
        return TEMPLOG7_OK;
    }
    return TEMPLOG7_ERROR;
}

err_t templog7_read_scratchpad_2 ( templog7_t *ctx, templog7_scratchpad_2_t *scratchpad )
{
    err_t error_flag = TEMPLOG7_OK;
    uint8_t command = TEMPLOG7_CMD_READ_SCRATCHPAD_2;
    uint8_t data_buf[ TEMPLOG7_EEPROM_ADDR_BLOCK + 2 ] = { 0 };
    uint8_t crc_byte = 0;
    if ( ( NULL == scratchpad ) || 
         ( scratchpad->address > TEMPLOG7_EEPROM_ADDR_MAX ) || 
         ( scratchpad->address % TEMPLOG7_EEPROM_ADDR_BLOCK ) )
    {
        return TEMPLOG7_ERROR;
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( scratchpad->address >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( scratchpad->address & 0xFF );
    error_flag |= templog7_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 2 );
    error_flag |= one_wire_read_byte( &ctx->ow, &data_buf[ 2 ], TEMPLOG7_EEPROM_ADDR_BLOCK );
    error_flag |= one_wire_read_byte( &ctx->ow, &crc_byte, 1 );
    if ( ( TEMPLOG7_OK == error_flag ) &&
         ( crc_byte == templog7_calculate_crc8 ( data_buf, TEMPLOG7_EEPROM_ADDR_BLOCK + 2 ) ) )
    {
        memcpy ( scratchpad->data_buf, &data_buf[ 2 ], TEMPLOG7_EEPROM_ADDR_BLOCK );
        return TEMPLOG7_OK;
    }
    return TEMPLOG7_ERROR;
}

err_t templog7_copy_scratchpad_2 ( templog7_t *ctx )
{
    err_t error_flag = TEMPLOG7_OK;
    uint8_t command = TEMPLOG7_CMD_COPY_SCRATCHPAD_2;
    uint8_t qualifier = TEMPLOG7_COPY_SCRATCHPAD_2_QUALIFIER;
    error_flag |= templog7_select_device( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, &qualifier, 1 );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    return error_flag;
}

err_t templog7_start_measurement ( templog7_t *ctx )
{
    err_t error_flag = TEMPLOG7_OK;
    uint8_t command = TEMPLOG7_CMD_CONVERT_TEMP;
    error_flag |= templog7_select_device( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    return error_flag;
}

err_t templog7_read_temperature ( templog7_t *ctx, float *temperature )
{
    err_t error_flag = TEMPLOG7_OK;
    templog7_scratchpad_1_t scratchpad;
    error_flag |= templog7_start_measurement( ctx );
    // Wait for temperature conversion to be done.                                
    Delay_10ms();
    error_flag |= templog7_read_scratchpad_1 ( ctx, &scratchpad );
    if ( ( TEMPLOG7_OK == error_flag ) && ( scratchpad.status & TEMPLOG7_STATUS_DATA_VALID ) )
    {
        if ( scratchpad.config_1 & TEMPLOG7_CFG1_TEMP_FMT_16_BIT )
        {
            *temperature = scratchpad.temperature * TEMPLOG7_TEMP_RES_16BIT;
        }
        else
        {
            *temperature = scratchpad.temperature * TEMPLOG7_TEMP_RES_12BIT;
        }
    }
    return error_flag;
}

err_t templog7_write_eeprom ( templog7_t *ctx, uint16_t address, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = TEMPLOG7_OK;
    templog7_scratchpad_2_t scratchpad_2 = { 0 };
    uint16_t addr_cnt = 0;
    if ( ( NULL == data_in ) || 
         ( ( address + len ) > ( TEMPLOG7_EEPROM_ADDR_MAX + 1 ) ) || 
         ( address % TEMPLOG7_EEPROM_ADDR_BLOCK ) )
    {
        return TEMPLOG7_ERROR;
    }
    for ( addr_cnt = 0; addr_cnt < len; addr_cnt += TEMPLOG7_EEPROM_ADDR_BLOCK )
    {
        scratchpad_2.address = ( address + addr_cnt ) & TEMPLOG7_EEPROM_ADDR_MASK;
        if ( ( addr_cnt + TEMPLOG7_EEPROM_ADDR_BLOCK ) <= len )
        {
            memcpy ( scratchpad_2.data_buf, &data_in[ addr_cnt ], TEMPLOG7_EEPROM_ADDR_BLOCK );
        }
        else
        {
            memset ( scratchpad_2.data_buf, 0, TEMPLOG7_EEPROM_ADDR_BLOCK );
            memcpy ( scratchpad_2.data_buf, &data_in[ addr_cnt ], len - addr_cnt );
        }
        error_flag |= templog7_write_scratchpad_2 ( ctx, &scratchpad_2 );
        error_flag |= templog7_copy_scratchpad_2 ( ctx );
    }
    return error_flag;
}

err_t templog7_read_eeprom ( templog7_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len )
{
    err_t error_flag = TEMPLOG7_OK;
    uint8_t command = TEMPLOG7_CMD_READ_EEPROM;
    uint8_t data_buf[ 2 ] = { 0 };
    uint16_t addr_cnt = 0;
    if ( ( NULL == data_out ) || 
         ( ( address + len ) > ( TEMPLOG7_EEPROM_ADDR_MAX + 1 ) ) || 
         ( address % TEMPLOG7_EEPROM_ADDR_BLOCK ) )
    {
        return TEMPLOG7_ERROR;
    }
    for ( addr_cnt = 0; addr_cnt < len; addr_cnt++ )
    {
        if ( 0 == ( addr_cnt % TEMPLOG7_EEPROM_ADDR_BLOCK ) )
        {
            data_buf[ 0 ] = ( uint8_t ) ( ( ( address + addr_cnt ) >> 8 ) & 0xFF );
            data_buf[ 1 ] = ( uint8_t ) ( ( address + addr_cnt ) & 0xFF );
            error_flag |= templog7_select_device ( ctx );
            error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
            error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 2 );
            Delay_1ms ( );
        }
        error_flag |= one_wire_read_byte( &ctx->ow, &data_out[ addr_cnt ], 1 );
    }
    return error_flag;
}

err_t templog7_clear_eeprom ( templog7_t *ctx )
{
    err_t error_flag = TEMPLOG7_OK;
    uint16_t addr_cnt = 0;
    uint8_t data_buf[ TEMPLOG7_EEPROM_ADDR_BLOCK ] = { 0 };
    memset ( data_buf, 0, TEMPLOG7_EEPROM_ADDR_BLOCK );
    for ( addr_cnt = TEMPLOG7_EEPROM_ADDR_MIN; 
          addr_cnt <= TEMPLOG7_EEPROM_ADDR_MAX; 
          addr_cnt += TEMPLOG7_EEPROM_ADDR_BLOCK )
    {
        error_flag |= templog7_write_eeprom ( ctx, addr_cnt, data_buf, TEMPLOG7_EEPROM_ADDR_BLOCK );
    }
    return error_flag;
}

err_t templog7_write_gpio ( templog7_t *ctx, uint8_t data_in )
{
    err_t error_flag = TEMPLOG7_OK;
    uint8_t command = TEMPLOG7_CMD_GPIO_WRITE;
    uint8_t data_buf[ 2 ] = { 0 };
    uint8_t check_code = 0;
    data_buf[ 0 ] = data_in;
    data_buf[ 1 ] = ~data_in;
    error_flag |= templog7_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 2 );
    error_flag |= one_wire_read_byte( &ctx->ow, &check_code, 1 );
    if ( ( TEMPLOG7_OK == error_flag ) &&
         ( TEMPLOG7_IO_CHECK_CODE_OK == check_code ) )
    {
        return TEMPLOG7_OK;
    }
    return error_flag;
}

err_t templog7_read_gpio ( templog7_t *ctx, uint8_t *data_out )
{
    err_t error_flag = TEMPLOG7_OK;
    uint8_t command = TEMPLOG7_CMD_GPIO_READ;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( NULL == data_out )
    {
        return TEMPLOG7_ERROR;
    }
    error_flag |= templog7_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, 2 );
    if ( ( TEMPLOG7_OK == error_flag ) &&
         ( data_buf[ 1 ] == templog7_calculate_crc8 ( data_buf, 1 ) ) )
    {
        *data_out = data_buf[ 0 ];
        return TEMPLOG7_OK;
    }
    return error_flag;
}

uint8_t templog7_get_alert_pin ( templog7_t *ctx )
{
    return digital_in_read ( &ctx->alert );
}

static uint8_t templog7_calculate_crc8 ( uint8_t *data_buf, uint8_t len )
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
