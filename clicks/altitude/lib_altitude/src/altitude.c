/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright ( c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files ( the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file altitude.c
 *
 */

#include "altitude.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void altitude_cfg_setup( altitude_cfg_t *cfg )
{
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->it1 = HAL_PIN_NC;
    cfg->it2 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_addr  = ALTITUDE_SLAVE_ADDR;
}

altitude_err_t altitude_init( altitude_t *ctx, altitude_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_addr = cfg->i2c_addr;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ALTITUDE_ERR_INIT_DRV;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_addr );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_in_init( &ctx->it1, cfg->it1 );
    digital_in_init( &ctx->it2, cfg->it2 );

    return ALTITUDE_OK;
}

void altitude_default_cfg( altitude_t *ctx )
{
    altitude_generic_single_write( ctx, ALTITUDE_REG_CTRL1,       ALTITUDE_CTRL1_SBYB          |
                                                                  ALTITUDE_CTRL1_ALT           |
                                                                  ALTITUDE_CTRL1_OS32_130MS    );
    altitude_generic_single_write( ctx, ALTITUDE_REG_CTRL2,       0x10                         );
    altitude_generic_single_write( ctx, ALTITUDE_REG_CTRL3,       0                            );
    altitude_generic_single_write( ctx, ALTITUDE_REG_CTRL4,       ALTITUDE_CTRL4_INT_EN_DRDY   |
                                                                  ALTITUDE_CTRL4_INT_EN_PCHG   );
    altitude_generic_single_write( ctx, ALTITUDE_REG_CTRL5,       ALTITUDE_CTRL5_INT1_DRDY     );
    altitude_generic_single_write( ctx, ALTITUDE_REG_PT_DATA_CFG, ALTITUDE_PT_DATA_DR_EVENT_EN |
                                                                  ALTITUDE_PT_DATA_PD_EVENT_EN );
}

altitude_err_t altitude_generic_single_write( altitude_t *ctx, uint8_t reg_addr, uint8_t data_in )
{
    uint8_t tx_data[ 2 ];

    if ( reg_addr > 0x29 )
    {
        return ALTITUDE_ERR_ADDR;
    }

    tx_data[ 0 ] = reg_addr;
    tx_data[ 1 ] = data_in;

    i2c_master_write( &ctx->i2c, tx_data, 2 );

    return ALTITUDE_OK;
}

altitude_err_t altitude_generic_multiple_write( altitude_t *ctx, uint8_t reg_addr, uint8_t *data_in, uint8_t n_data )
{
    uint8_t tx_data[ 33 ];
    uint8_t cnt;

    if ( reg_addr > 0x29 )
    {
        return ALTITUDE_ERR_ADDR;
    }

    if ( ( n_data < ALTITUDE_NDATA_TRANSFER_MIN ) || ( n_data > ALTITUDE_NDATA_TRANSFER_MAX ) )
    {
        return ALTITUDE_ERR_NDATA;
    }

    tx_data[ 0 ] = reg_addr;

    for ( cnt = 1; cnt <= n_data; cnt++ )
    {
        tx_data[ cnt ] = *data_in;
        data_in++;
    }

    i2c_master_write( &ctx->i2c, tx_data, n_data + 1 ); 

    return ALTITUDE_OK;
}

altitude_err_t altitude_generic_multiple_read( altitude_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_data )
{
    uint8_t tx_data;

    if ( reg_addr > 0x29 )
    {
        return ALTITUDE_ERR_ADDR;
    }

    if ( ( n_data < ALTITUDE_NDATA_TRANSFER_MIN) || ( n_data > ALTITUDE_NDATA_TRANSFER_MAX ) )
    {
        return ALTITUDE_ERR_NDATA;
    }

    tx_data = reg_addr;

    i2c_master_write_then_read( &ctx->i2c, &tx_data, 1, data_out, n_data );

    return ALTITUDE_OK;
}

void altitude_set_system_mode( altitude_t *ctx, altitude_sys_mode_t mode )
{
    uint8_t tmp_data;

    altitude_generic_multiple_read( ctx, ALTITUDE_REG_CTRL1, &tmp_data, ALTITUDE_NDATA_TRANSFER_MIN );

    tmp_data &= 0xFE;
    tmp_data |= mode;

    altitude_generic_single_write( ctx, ALTITUDE_REG_CTRL1, tmp_data );
}

void altitude_set_sensor_mode( altitude_t *ctx, altitude_sens_mode_t mode )
{
    uint8_t tmp_data;

    altitude_generic_multiple_read( ctx, ALTITUDE_REG_CTRL1, &tmp_data, ALTITUDE_NDATA_TRANSFER_MIN );

    tmp_data &= 0x7F;
    tmp_data |= mode << 7;

    altitude_generic_single_write( ctx, ALTITUDE_REG_CTRL1, tmp_data );
}

void altitude_sw_reset( altitude_t *ctx )
{
    uint8_t tmp_data;

    altitude_generic_single_write( ctx, ALTITUDE_REG_CTRL1, ALTITUDE_CTRL1_RST );
    Delay_1sec();
    altitude_generic_multiple_read( ctx, ALTITUDE_REG_CTRL1, &tmp_data, ALTITUDE_NDATA_TRANSFER_MIN );

    while ( tmp_data )
    {
        altitude_generic_multiple_read( ctx, ALTITUDE_REG_CTRL1, &tmp_data, ALTITUDE_NDATA_TRANSFER_MIN );
    }
}

uint8_t altitude_get_drdy_status( altitude_t *ctx, uint8_t flag_mask )
{
    uint8_t tmp_data;

    altitude_generic_multiple_read( ctx, ALTITUDE_REG_DR_STATUS, &tmp_data, ALTITUDE_NDATA_TRANSFER_MIN );

    return ( tmp_data & flag_mask );
}

uint8_t altitude_get_int_status( altitude_t *ctx, uint8_t flag_mask )
{
    uint8_t tmp_data;

    altitude_generic_multiple_read( ctx, ALTITUDE_REG_INT_SOURCE, &tmp_data, ALTITUDE_NDATA_TRANSFER_MIN );

    return ( tmp_data & flag_mask );
}

uint8_t altitude_get_int1_pin( altitude_t *ctx )
{
    return digital_in_read( &ctx->it1 );
}

uint8_t altitude_get_int2_pin( altitude_t *ctx )
{
    return digital_in_read( &ctx->it2 );
}

float altitude_get_altitude( altitude_t *ctx )
{
    uint8_t tmp_data[ 3 ];
    int32_t alt_data;
    float ret_val;

    altitude_generic_multiple_read( ctx, ALTITUDE_REG_OUT_P_MSB, tmp_data, 3 );

    alt_data = tmp_data[ 0 ];
    alt_data <<= 8;
    alt_data |= tmp_data[ 1 ];
    alt_data <<= 8;
    alt_data |= tmp_data[ 2 ];
    alt_data >>= 4;

    if ( alt_data & 0x80000 )
    {
        alt_data |= 0xFFF00000;
    }

    ret_val = alt_data;
    ret_val *= 0.0625;

    return ret_val;
}

float altitude_get_pressure( altitude_t *ctx )
{
    uint8_t tmp_data[ 3 ];
    uint32_t press_data;
    float ret_val;

    altitude_generic_multiple_read( ctx, ALTITUDE_REG_OUT_P_MSB, tmp_data, 3 );

    press_data = tmp_data[ 0 ];
    press_data <<= 8;
    press_data |= tmp_data[ 1 ];
    press_data <<= 8;
    press_data |= tmp_data[ 2 ];
    press_data >>= 4;

    ret_val = press_data;
    ret_val *= 0.25;

    return ( ret_val / 100 );
}

float altitude_get_temperature( altitude_t *ctx )
{
    uint8_t tmp_data[ 2 ];
    int16_t temp_data;
    float ret_val;

    altitude_generic_multiple_read( ctx, ALTITUDE_REG_OUT_T_MSB, tmp_data, 2 );

    temp_data = tmp_data[ 0 ];
    temp_data <<= 8;
    temp_data |= tmp_data[ 1 ];
    temp_data >>= 4;

    if ( temp_data & 0x800 )
    {
        temp_data |= 0xF000;
    }

    ret_val = temp_data;
    ret_val *= 0.0625;

    return ret_val;
}

// ------------------------------------------------------------------------ END
