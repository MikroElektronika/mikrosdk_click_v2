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
 * @file current12.c
 * @brief Current 12 Click Driver.
 */

#include "current12.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void current12_cfg_setup ( current12_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CURRENT12_DEVICE_ADDRESS_0;
}

err_t current12_init ( current12_t *ctx, current12_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alr, cfg->alr );

    return I2C_MASTER_SUCCESS;
}

err_t current12_default_cfg ( current12_t *ctx ) 
{
    uint16_t device_id = DUMMY;
    err_t err_flag = current12_get_device_id( ctx, &device_id );
    if ( CURRENT12_DEVICE_ID == device_id )
    {
        current12_measure_cfg_t measure_cfg;
        measure_cfg.rst = CURRENT12_CFG_RST_DISABLE;
        measure_cfg.ct = CURRENT12_CFG_CT_1024_US;
        measure_cfg.temp = CURRENT12_CFG_TEMP_ENABLE;
        measure_cfg.op_mode = CURRENT12_CFG_OP_MODE_SLV_CONT;
        err_flag |= current12_set_measure_cfg( ctx, measure_cfg );
        Delay_100ms( );

        err_flag |= current12_set_rshunt( ctx, CURRENT12_RSHUNT_5_MOHM );
        Delay_100ms( );
    }
    else
    {
        err_flag = CURRENT12_ERROR;
    }
    return err_flag;
}

err_t current12_generic_write ( current12_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t current12_generic_read ( current12_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t current12_write_word ( current12_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in >> 8 );
    data_buf[ 1 ] = ( uint8_t ) data_in;
    return current12_generic_write( ctx, reg, data_buf, 2 );
}

err_t current12_read_word ( current12_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = current12_generic_read( ctx, reg, data_buf, 2 );
    *data_out = data_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= data_buf[ 1 ];
    return err_flag;
}

err_t current12_set_measure_cfg ( current12_t *ctx, current12_measure_cfg_t measure_cfg ) 
{
    uint16_t data_buf = DUMMY;
    data_buf =  ( ( uint16_t ) ( measure_cfg.rst     & 0x01 ) ) << 15;
    data_buf |= ( ( uint16_t ) ( measure_cfg.ct      & 0x0F ) ) << 4;
    data_buf |= ( ( uint16_t ) ( measure_cfg.temp    & 0x01 ) ) << 3;
    data_buf |=   ( uint16_t ) ( measure_cfg.op_mode & 0x07 );
    return current12_write_word( ctx, CURRENT12_REG_CONFIGURATION, data_buf );
}

err_t current12_get_shunt_voltage ( current12_t *ctx, float *shunt_voltage ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = current12_read_word( ctx, CURRENT12_REG_SHUNT_VOLTAGE, &data_buf );
    *shunt_voltage = ( float ) data_buf;
    *shunt_voltage *= CURRENT12_CALC_SHUNT_VTG_MV;
    return err_flag;
}

err_t current12_get_load_voltage ( current12_t *ctx, float *load_voltage ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = current12_read_word( ctx, CURRENT12_REG_LOAD_VOLTAGE, &data_buf );
    *load_voltage = ( float ) data_buf;
    *load_voltage *= CURRENT12_CALC_LOAD_VTG_V;
    return err_flag;
}

err_t current12_get_dc_power ( current12_t *ctx, float *dc_power ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = current12_read_word( ctx, CURRENT12_REG_DC_POWER, &data_buf );
    *dc_power = ( float ) data_buf;
    *dc_power *= CURRENT12_CALC_DC_POWER_W;
    return err_flag;
}

err_t current12_get_current ( current12_t *ctx, float *current ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = current12_read_word( ctx, CURRENT12_REG_CURRENT, &data_buf );
    *current = ( float ) data_buf;
    *current *=  CURRENT12_CALC_CURRENT_MA;
    return err_flag;
}

err_t current12_get_temperature ( current12_t *ctx, float *temperature ) 
{
    uint16_t data_buf = DUMMY;
    err_t err_flag = current12_read_word( ctx, CURRENT12_REG_TEMPERATURE, &data_buf );
    if ( CURRENT12_TEMP_ERROR_BITMASK != data_buf )
    {
        *temperature = ( float ) ( ( int16_t ) data_buf );
        *temperature *=  CURRENT12_CALC_TEMP_C;
    }
    else
    {
        err_flag = CURRENT12_ERROR;
    }
    
    return err_flag;
}

err_t current12_set_rshunt ( current12_t *ctx, float rshunt_mohm ) 
{
    err_t err_flag = CURRENT12_ERROR;
    if ( CURRENT12_RSHUNT_MAX > rshunt_mohm )
    {
        err_flag = current12_write_word( ctx, CURRENT12_REG_RSHUNT, ( uint16_t ) ( rshunt_mohm * 100.0 ) );
    }
    return err_flag;
}

err_t current12_get_device_id ( current12_t *ctx, uint16_t *device_id ) 
{
    return current12_read_word( ctx, CURRENT12_REG_MANUFACTURING_ID, device_id );
}

uint8_t current12_get_alert ( current12_t *ctx ) 
{
    return digital_in_read( &ctx->alr );
}

// ------------------------------------------------------------------------- END
