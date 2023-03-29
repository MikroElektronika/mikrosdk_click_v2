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
 * @file ph2.c
 * @brief pH 2 Click Driver.
 */

#include "ph2.h"

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
static uint8_t ph2_calculate_crc8 ( uint8_t *data_buf, uint8_t len );

void ph2_cfg_setup ( ph2_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->st1 = HAL_PIN_NC;
    cfg->st2 = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PH2_SET_DEV_ADDR;
    cfg->vref        = PH2_VREF_3V3;
    cfg->drv_sel     = PH2_DRV_SEL_I2C;
}

void ph2_drv_interface_selection ( ph2_cfg_t *cfg, ph2_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t ph2_init ( ph2_t *ctx, ph2_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;

    if ( PH2_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
        {
            return I2C_MASTER_ERROR;
        }
    }
    else
    {
        analog_in_config_t adc_cfg;

        analog_in_configure_default( &adc_cfg );

        adc_cfg.input_pin = cfg->an;

        if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
        {
            return ADC_ERROR;
        }

        if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
        {
            return ADC_ERROR;
        }

        if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
        {
            return ADC_ERROR;
        }
    }

    digital_out_init( &ctx->st1, cfg->st1 );
    digital_out_init( &ctx->st2, cfg->st2 );

    return PH2_OK;
}

err_t ph2_read_raw_adc ( ph2_t *ctx, uint16_t *raw_adc ) 
{
    if ( PH2_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint8_t rx_buf[ 2 ];
        err_t err_flag = i2c_master_read( &ctx->i2c, rx_buf, 2 );
        *raw_adc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | ( rx_buf[ 1 ] & 0xFF ) ) & PH2_ADC_RESOLUTION;
        return err_flag;
    }
    else
    {
        return analog_in_read( &ctx->adc, raw_adc );
    }
}

err_t ph2_read_voltage ( ph2_t *ctx, float *voltage ) 
{
    if ( PH2_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        uint16_t raw_adc;
        err_t err_flag = ph2_read_raw_adc( ctx, &raw_adc );
        *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) PH2_ADC_RESOLUTION );
        return err_flag;
    }
    else
    {
        return analog_in_read_voltage( &ctx->adc, voltage );
    }
}

err_t ph2_set_vref ( ph2_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( PH2_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        return PH2_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

err_t ph2_calibrate ( ph2_t *ctx, float pH_value )
{
    err_t error_flag = PH2_OK;
    float rx_data = 0;
    
    error_flag = ph2_read_voltage( ctx, &rx_data );
    ctx->pH_vol = rx_data;
    ctx->pH_val = pH_value;

    return error_flag;
}

err_t ph2_calculate_ph ( ph2_t *ctx, float *pH_value )
{
    err_t error_flag = PH2_OK;
    float rx_data = 0;
    
    error_flag = ph2_read_voltage( ctx, &rx_data );
    *pH_value = ctx->pH_val + ( (ctx->pH_vol - rx_data) / PH2_PH_CALCULATION_COEF);
    
    return error_flag;
}

void ph2_calibrate_offset ( ph2_t *ctx )
{
    float rx_data = 0;
    while ( ( (uint8_t) ( rx_data * 100)  ) != ( (uint8_t) ( ctx->vref * 50 ) ) )
    {
        ph2_read_voltage( ctx, &rx_data );
        if ( ( (uint8_t) ( rx_data * 100 ) ) > ( (uint8_t) ( ctx->vref * 50 ) ) )
        {
            ph2_enable_st2( ctx );
            Delay_100ms( );
            ph2_disable_st2( ctx );
            Delay_100ms( );
        }
        if ( ( (uint8_t) ( rx_data * 100 ) ) < ( (uint8_t) ( ctx->vref * 50 ) ) )
        {
            ph2_enable_st1( ctx );
            Delay_100ms( );
            ph2_disable_st1( ctx );
            Delay_100ms( );
        }
    }
    ph2_enable_st1( ctx );
    ph2_enable_st2( ctx );
    Delay_100ms( );
    ph2_disable_st1( ctx );
    ph2_disable_st2( ctx );
}

void ph2_enable_st1 ( ph2_t *ctx )
{
    digital_out_high( &ctx->st1 );
}

void ph2_disable_st1 ( ph2_t *ctx )
{
    digital_out_low( &ctx->st1 );
}

void ph2_enable_st2 ( ph2_t *ctx )
{
    digital_out_high( &ctx->st2 );
}

void ph2_disable_st2 ( ph2_t *ctx )
{
    digital_out_low( &ctx->st2 );
}

err_t ph2_ds18b20_init ( ph2_t *ctx, ph2_cfg_t *cfg )
{
    one_wire_configure_default( &ctx->ow );
    
    ctx->ow.data_pin = cfg->dq;
    
    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    return ONE_WIRE_SUCCESS;
}

err_t ph2_ds18b20_check_communication ( ph2_t *ctx )
{
    one_wire_rom_address_t search_rom_addr;
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return PH2_ERROR;
    }
    if ( PH2_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return PH2_ERROR;
    }
    if ( ONE_WIRE_ERROR == one_wire_search_first_device ( &ctx->ow, &search_rom_addr ) )
    {
        return PH2_ERROR;
    }
    if ( memcmp ( &ctx->rom_addr, &search_rom_addr, sizeof ( one_wire_rom_address_t ) ) )
    {
        return PH2_ERROR;
    }
    return PH2_OK;
}

err_t ph2_ds18b20_select_device ( ph2_t *ctx )
{
    if ( ctx->config & PH2_CONFIG_ADDRESS )
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

err_t ph2_ds18b20_read_scratchpad ( ph2_t *ctx, uint8_t *scratchpad )
{
    err_t error_flag = PH2_OK;
    uint8_t data_buf[ 9 ];
    uint8_t command = PH2_CMD_READ_SCRATCHPAD;

    error_flag |= ph2_ds18b20_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, data_buf, 9 );

    if ( ( PH2_OK == error_flag ) &&
         ( data_buf[ 8 ] == ph2_calculate_crc8 ( data_buf, 8 ) ) )
    {
        if ( PH2_CONFIG_ADDRESS != ( ctx->config & PH2_CONFIG_ADDRESS ) )
        {
            if ( ( ctx->config & PH2_CONFIG_ADDRESS ) != ( data_buf[ 4 ] & PH2_CONFIG_ADDRESS ) )
            {
                return PH2_ERROR;
            }
        }
        memcpy ( scratchpad, data_buf, 5 );
        return PH2_OK;
    }
    return PH2_ERROR;
}

err_t ph2_ds18b20_write_scratchpad ( ph2_t *ctx, uint8_t temp_high, uint8_t temp_low, uint8_t config )
{
    err_t error_flag = PH2_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = PH2_CMD_WRITE_SCRATCHPAD;
    data_buf[ 1 ] = temp_high;
    data_buf[ 2 ] = temp_low;
    ctx->config = ( config & PH2_CONFIG_ADDRESS ) | ( config & PH2_CONFIG_RESOLUTION_BIT_MASK );
    data_buf[ 3 ] = ctx->config | PH2_CONFIG_RESERVED_BITS;

    error_flag |= ph2_ds18b20_select_device ( ctx );
    error_flag |= one_wire_write_byte( &ctx->ow, data_buf, 4 );
    return error_flag;
}

err_t ph2_ds18b20_default_cfg ( ph2_t *ctx )
{
    err_t error_flag = PH2_OK;

    error_flag |= ph2_ds18b20_check_communication ( ctx );

    error_flag |= ph2_ds18b20_write_scratchpad ( ctx, PH2_DEFAULT_TEMP_HIGH_ALARM, PH2_DEFAULT_TEMP_LOW_ALARM,
                                                 PH2_DEFAULT_ADDRESS | PH2_DEFAULT_RESOLUTION );

    return error_flag;
}

err_t ph2_ds18b20_start_measurement ( ph2_t *ctx )
{
    err_t error_flag = PH2_OK;
    // "Convert Temperature" command.
    error_flag |= ph2_ds18b20_select_device( ctx );
    uint8_t command = PH2_CMD_CONVERT_TEMPERATURE;
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );
    return error_flag;
}

err_t ph2_ds18b20_read_temperature ( ph2_t *ctx, float *temperature )
{
    err_t error_flag = PH2_OK;
    error_flag |= ph2_ds18b20_start_measurement( ctx );
    // Wait for temperature conversion to be done.
    switch ( ctx->config & PH2_CONFIG_RESOLUTION_BIT_MASK )
    {
        case PH2_CONFIG_RESOLUTION_9BIT:
        {
            // At least 93.75ms delay is required for conversion
            Delay_100ms( );
            break;
        }
        case PH2_CONFIG_RESOLUTION_10BIT:
        {
            // At least 187.5ms delay is required for conversion
            Delay_100ms( );
            Delay_100ms( );
            break;
        }
        case PH2_CONFIG_RESOLUTION_11BIT:
        {
            // At least 375ms delay is required for conversion
            Delay_100ms( );
            Delay_100ms( );
            Delay_100ms( );
            Delay_100ms( );
            break;
        }
        case PH2_CONFIG_RESOLUTION_12BIT:
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
    error_flag |= ph2_ds18b20_read_scratchpad ( ctx, scratchpad );
    int16_t raw_temp = ( ( int16_t ) scratchpad[ 1 ] << 8 ) | scratchpad[ 0 ];
    *temperature = raw_temp * PH2_DATA_RESOLUTION;
    return error_flag;
}

static uint8_t ph2_calculate_crc8 ( uint8_t *data_buf, uint8_t len )
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
