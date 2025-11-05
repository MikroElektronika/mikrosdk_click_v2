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
 * @file pac1711.c
 * @brief PAC1711 Click Driver.
 */

#include "pac1711.h"

void pac1711_cfg_setup ( pac1711_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->a1_pin = HAL_PIN_NC;
    cfg->a0_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PAC1711_DEVICE_ADDRESS_A1A0_VCC_VCC;
}

err_t pac1711_init ( pac1711_t *ctx, pac1711_cfg_t *cfg ) 
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

    digital_in_init( &ctx->a1_pin, cfg->a1_pin );
    digital_in_init( &ctx->a0_pin, cfg->a0_pin );

    return I2C_MASTER_SUCCESS;
}

err_t pac1711_default_cfg ( pac1711_t *ctx ) 
{
    err_t error_flag = PAC1711_OK;
    if ( PAC1711_OK != pac1711_check_communication ( ctx ) )
    {
        return PAC1711_ERROR;
    }
    error_flag |= pac1711_set_fsr ( ctx, PAC1711_FSR_UNIPOLAR, PAC1711_FSR_UNIPOLAR );
    return error_flag;
}

err_t pac1711_send_byte ( pac1711_t *ctx, uint8_t data_in )
{
    return i2c_master_write( &ctx->i2c, &data_in, 1 );
}

err_t pac1711_receive_byte ( pac1711_t *ctx, uint8_t *data_out )
{
    return i2c_master_read( &ctx->i2c, data_out, 1 );
}

err_t pac1711_write_byte ( pac1711_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t pac1711_read_byte ( pac1711_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t pac1711_block_write ( pac1711_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t pac1711_block_read ( pac1711_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t pac1711_check_communication ( pac1711_t *ctx )
{
    uint8_t device_id[ 2 ] = { 0 };
    if ( PAC1711_OK == pac1711_block_read ( ctx, PAC1711_REG_PRODUCT_ID, device_id, 2 ) )
    {
        if ( ( PAC1711_PRODUCT_ID == device_id[ 0 ] ) &&
             ( PAC1711_MANUFACTURER_ID == device_id[ 1 ] ) )
        {
            return PAC1711_OK;
        }
    }
    return PAC1711_ERROR;
}

uint8_t pac1711_get_a0_pin ( pac1711_t *ctx )
{
    return digital_in_read ( &ctx->a0_pin );
}

uint8_t pac1711_get_a1_pin ( pac1711_t *ctx )
{
    return digital_in_read ( &ctx->a1_pin );
}

err_t pac1711_refresh ( pac1711_t *ctx )
{
    return pac1711_send_byte ( ctx, PAC1711_REG_REFRESH );
}

err_t pac1711_refresh_global ( pac1711_t *ctx )
{
    err_t error_flag = PAC1711_OK;
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, PAC1711_DEVICE_ADDRESS_GENERAL_CALL );
    error_flag |= pac1711_send_byte ( ctx, PAC1711_REG_REFRESH_G );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    return error_flag;
}

err_t pac1711_refresh_wo_acc_reset ( pac1711_t *ctx )
{
    return pac1711_send_byte ( ctx, PAC1711_REG_REFRESH_V );
}

err_t pac1711_set_fsr ( pac1711_t *ctx, uint8_t vsense_fsr, uint8_t vbus_fsr )
{
    err_t error_flag = PAC1711_OK;
    if ( ( vsense_fsr > PAC1711_FSR_BIPOLAR_HALF ) ||
         ( vbus_fsr > PAC1711_FSR_BIPOLAR_HALF ) )
    {
        error_flag = PAC1711_ERROR;
    }
    if ( PAC1711_OK == error_flag )
    {
        error_flag = pac1711_write_byte ( ctx, PAC1711_REG_NEG_PWR_FSR, ( vsense_fsr << 2 ) | vbus_fsr );
    }
    if ( PAC1711_OK == error_flag )
    {
        ctx->vsense_fsr = vsense_fsr;
        ctx->vbus_fsr = vbus_fsr;
    }
    return error_flag;
}

err_t pac1711_read_data ( pac1711_t *ctx, pac1711_data_t *data_out )
{
    err_t error_flag = PAC1711_OK;
    uint8_t data_buf[ 39 ] = { 0 };
    uint16_t raw_12 = 0;
    int16_t raw_12_s = 0;
    uint32_t raw_24 = 0;
    int32_t raw_24_s = 0;
    uint32_t vbus_res = 0;
    uint32_t isense_res = 0;
    uint32_t power_res = 0;
    if ( NULL == data_out )
    {
        error_flag = PAC1711_ERROR;
    }
    if ( PAC1711_OK == error_flag )
    {
        error_flag = pac1711_block_read ( ctx, PAC1711_REG_ACC_COUNT, data_buf, 39 );
    }
    if ( PAC1711_OK == error_flag )
    {
        // Power, voltage and current data resolution calculation
        if ( PAC1711_FSR_BIPOLAR == ctx->vbus_fsr )
        {
            vbus_res = 11;
        }
        else
        {
            vbus_res = 12;
        }
        if ( PAC1711_FSR_BIPOLAR == ctx->vsense_fsr )
        {
            isense_res = 11;
        }
        else
        {
            isense_res = 12;
        }
        power_res = ( ( 1ul << ( vbus_res + isense_res ) ) - 1 );
        vbus_res = ( ( 1ul << vbus_res ) - 1 );
        isense_res = ( ( 1ul << isense_res ) - 1 );

        // Accumulator data
        data_out->acc_count = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | 
                              ( ( uint32_t ) data_buf[ 1 ] << 16 ) | 
                              ( ( uint32_t ) data_buf[ 2 ] << 8 ) | 
                              ( ( uint32_t ) data_buf[ 3 ] << 0 );
        data_out->acc_data_msb = ( ( uint32_t ) data_buf[ 4 ] << 16 ) | 
                                 ( ( uint32_t ) data_buf[ 5 ] << 8 ) | 
                                 ( ( uint32_t ) data_buf[ 6 ] << 0 );
        data_out->acc_data_lsb = ( ( uint32_t ) data_buf[ 7 ] << 24 ) | 
                                 ( ( uint32_t ) data_buf[ 8 ] << 16 ) | 
                                 ( ( uint32_t ) data_buf[ 9 ] << 8 ) | 
                                 ( ( uint32_t ) data_buf[ 10 ] << 0 );
        
        // Voltage measurements
        if ( PAC1711_FSR_UNIPOLAR == ctx->vbus_fsr )
        {
            raw_12 = ( ( uint16_t ) data_buf[ 11 ] << 8 ) | 
                     ( ( uint16_t ) data_buf[ 12 ] << 0 );
            raw_12 >>= 4;
            data_out->vbus = ( PAC1711_VSOURCE_MAX * raw_12 ) / vbus_res;

            raw_12 = ( ( uint16_t ) data_buf[ 15 ] << 8 ) | 
                     ( ( uint16_t ) data_buf[ 16 ] << 0 );
            raw_12 >>= 4;
            data_out->vbus_avg = ( PAC1711_VSOURCE_MAX * raw_12 ) / vbus_res;

            raw_12 = ( ( uint16_t ) data_buf[ 23 ] << 8 ) | 
                     ( ( uint16_t ) data_buf[ 24 ] << 0 );
            raw_12 >>= 4;
            data_out->vbus_min = ( PAC1711_VSOURCE_MAX * raw_12 ) / vbus_res;

            raw_12 = ( ( uint16_t ) data_buf[ 25 ] << 8 ) | 
                     ( ( uint16_t ) data_buf[ 26 ] << 0 );
            raw_12 >>= 4;
            data_out->vbus_max = ( PAC1711_VSOURCE_MAX * raw_12 ) / vbus_res;
        }
        else
        {
            raw_12_s = ( ( int16_t ) data_buf[ 11 ] << 8 ) | 
                       ( ( int16_t ) data_buf[ 12 ] << 0 );
            raw_12_s >>= 4;
            data_out->vbus = ( PAC1711_VSOURCE_MAX * raw_12_s ) / vbus_res;

            raw_12_s = ( ( int16_t ) data_buf[ 15 ] << 8 ) | 
                       ( ( int16_t ) data_buf[ 16 ] << 0 );
            raw_12_s >>= 4;
            data_out->vbus_avg = ( PAC1711_VSOURCE_MAX * raw_12_s ) / vbus_res;

            raw_12_s = ( ( int16_t ) data_buf[ 23 ] << 8 ) | 
                       ( ( int16_t ) data_buf[ 24 ] << 0 );
            raw_12_s >>= 4;
            data_out->vbus_min = ( PAC1711_VSOURCE_MAX * raw_12_s ) / vbus_res;

            raw_12_s = ( ( int16_t ) data_buf[ 25 ] << 8 ) | 
                       ( ( int16_t ) data_buf[ 26 ] << 0 );
            raw_12_s >>= 4;
            data_out->vbus_max = ( PAC1711_VSOURCE_MAX * raw_12_s ) / vbus_res;
        }

        // Current measurements
        if ( PAC1711_FSR_UNIPOLAR == ctx->vsense_fsr )
        {
            raw_12 = ( ( uint16_t ) data_buf[ 13 ] << 8 ) | 
                     ( ( uint16_t ) data_buf[ 14 ] << 0 );
            raw_12 >>= 4;
            data_out->isense = ( PAC1711_FSC * raw_12 ) / isense_res;

            raw_12 = ( ( uint16_t ) data_buf[ 17 ] << 8 ) | 
                     ( ( uint16_t ) data_buf[ 18 ] << 0 );
            raw_12 >>= 4;
            data_out->isense_avg = ( PAC1711_FSC * raw_12 ) / isense_res;

            raw_12 = ( ( uint16_t ) data_buf[ 27 ] << 8 ) | 
                     ( ( uint16_t ) data_buf[ 28 ] << 0 );
            raw_12 >>= 4;
            data_out->isense_min = ( PAC1711_FSC * raw_12 ) / isense_res;

            raw_12 = ( ( uint16_t ) data_buf[ 29 ] << 8 ) | 
                     ( ( uint16_t ) data_buf[ 30 ] << 0 );
            raw_12 >>= 4;
            data_out->isense_max = ( PAC1711_FSC * raw_12 ) / isense_res;
        }
        else
        {
            raw_12_s = ( ( int16_t ) data_buf[ 13 ] << 8 ) | 
                       ( ( int16_t ) data_buf[ 14 ] << 0 );
            raw_12_s >>= 4;
            data_out->isense = ( PAC1711_FSC * raw_12_s ) / isense_res;

            raw_12_s = ( ( int16_t ) data_buf[ 17 ] << 8 ) | 
                       ( ( int16_t ) data_buf[ 18 ] << 0 );
            raw_12_s >>= 4;
            data_out->isense_avg = ( PAC1711_FSC * raw_12_s ) / isense_res;

            raw_12_s = ( ( int16_t ) data_buf[ 27 ] << 8 ) | 
                       ( ( int16_t ) data_buf[ 28 ] << 0 );
            raw_12_s >>= 4;
            data_out->isense_min = ( PAC1711_FSC * raw_12_s ) / isense_res;

            raw_12_s = ( ( int16_t ) data_buf[ 29 ] << 8 ) | 
                       ( ( int16_t ) data_buf[ 30 ] << 0 );
            raw_12_s >>= 4;
            data_out->isense_max = ( PAC1711_FSC * raw_12_s ) / isense_res;
        }

        // Power measurements
        if ( ( PAC1711_FSR_UNIPOLAR == ctx->vsense_fsr ) && ( PAC1711_FSR_UNIPOLAR == ctx->vbus_fsr ) )
        {
            raw_24 = ( ( uint32_t ) data_buf[ 19 ] << 24 ) | 
                     ( ( uint32_t ) data_buf[ 20 ] << 16 ) | 
                     ( ( uint32_t ) data_buf[ 21 ] << 8 ) | 
                     ( ( uint32_t ) data_buf[ 22 ] << 0 );
            raw_24 >>= 8;
            data_out->power = ( PAC1711_POWER_FSR * raw_24 ) / power_res;

            raw_24 = ( ( uint32_t ) data_buf[ 31 ] << 24 ) | 
                     ( ( uint32_t ) data_buf[ 32 ] << 16 ) | 
                     ( ( uint32_t ) data_buf[ 33 ] << 8 ) | 
                     ( ( uint32_t ) data_buf[ 34 ] << 0 );
            raw_24 >>= 8;
            data_out->power_min = ( PAC1711_POWER_FSR * raw_24 ) / power_res;

            raw_24 = ( ( uint32_t ) data_buf[ 35 ] << 24 ) | 
                     ( ( uint32_t ) data_buf[ 36 ] << 16 ) | 
                     ( ( uint32_t ) data_buf[ 37 ] << 8 ) | 
                     ( ( uint32_t ) data_buf[ 38 ] << 0 );
            raw_24 >>= 8;
            data_out->power_max = ( PAC1711_POWER_FSR * raw_24 ) / power_res;
        }
        else
        {
            raw_24_s = ( ( int32_t ) data_buf[ 19 ] << 24 ) | 
                       ( ( int32_t ) data_buf[ 20 ] << 16 ) | 
                       ( ( int32_t ) data_buf[ 21 ] << 8 ) | 
                       ( ( int32_t ) data_buf[ 22 ] << 0 );
            raw_24_s >>= 8;
            data_out->power = ( PAC1711_POWER_FSR * raw_24_s ) / power_res;

            raw_24_s = ( ( int32_t ) data_buf[ 31 ] << 24 ) | 
                       ( ( int32_t ) data_buf[ 32 ] << 16 ) | 
                       ( ( int32_t ) data_buf[ 33 ] << 8 ) | 
                       ( ( int32_t ) data_buf[ 34 ] << 0 );
            raw_24_s >>= 8;
            data_out->power_min = ( PAC1711_POWER_FSR * raw_24_s ) / power_res;

            raw_24_s = ( ( int32_t ) data_buf[ 35 ] << 24 ) | 
                       ( ( int32_t ) data_buf[ 36 ] << 16 ) | 
                       ( ( int32_t ) data_buf[ 37 ] << 8 ) | 
                       ( ( int32_t ) data_buf[ 38 ] << 0 );
            raw_24_s >>= 8;
            data_out->power_max = ( PAC1711_POWER_FSR * raw_24_s ) / power_res;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
