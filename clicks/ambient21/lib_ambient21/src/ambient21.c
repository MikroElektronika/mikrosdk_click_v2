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
 * @file ambient21.c
 * @brief Ambient 21 Click Driver.
 */

#include "ambient21.h"

void ambient21_cfg_setup ( ambient21_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AMBIENT21_DEVICE_ADDRESS;
}

err_t ambient21_init ( ambient21_t *ctx, ambient21_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t ambient21_default_cfg ( ambient21_t *ctx ) 
{
    err_t error_flag = AMBIENT21_OK;
    if ( AMBIENT21_ERROR == ambient21_check_communication ( ctx ) )
    {
        return AMBIENT21_ERROR;
    }
    error_flag |= ambient21_write_register ( ctx, AMBIENT21_REG_ENABLE, AMBIENT21_ENABLE_AIEN | 
                                                                        AMBIENT21_ENABLE_AEN | 
                                                                        AMBIENT21_ENABLE_PON );
    error_flag |= ambient21_write_register ( ctx, AMBIENT21_REG_PERSIST, AMBIENT21_PERSIST_EVERY );
    error_flag |= ambient21_set_config ( ctx, AMBIENT21_AGAIN_MID, AMBIENT21_ATIME_200MS );
    return error_flag;
}

err_t ambient21_generic_write ( ambient21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    if ( len > AMBIENT21_REG_PERSIST )
    {
        return AMBIENT21_ERROR;
    }
    uint8_t data_buf[ AMBIENT21_REG_PERSIST + 1 ] = { 0 };
    data_buf[ 0 ] = ( reg & AMBIENT21_ADDR_SF_MASK ) | AMBIENT21_CMD_NORMAL_OP;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write ( &ctx->i2c, data_buf, len + 1 );
}

err_t ambient21_generic_read ( ambient21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( len > AMBIENT21_REG_C1DATAH )
    {
        return AMBIENT21_ERROR;
    }
    uint8_t cmd = ( reg & AMBIENT21_ADDR_SF_MASK ) | AMBIENT21_CMD_NORMAL_OP;
    return i2c_master_write_then_read( &ctx->i2c, &cmd, 1, data_out, len );
}

err_t ambient21_write_register ( ambient21_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ambient21_generic_write ( ctx, reg, &data_in, 1 );
}

err_t ambient21_read_register ( ambient21_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ambient21_generic_read ( ctx, reg, data_out, 1 );
}

err_t ambient21_write_spec_func ( ambient21_t *ctx, uint8_t spec_func )
{
    uint8_t cmd = ( spec_func & AMBIENT21_ADDR_SF_MASK ) | AMBIENT21_CMD_SPEC_FUNC;
    return i2c_master_write ( &ctx->i2c, &cmd, 1 );
}

uint8_t ambient21_get_int_pin ( ambient21_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t ambient21_check_communication ( ambient21_t *ctx )
{
    uint8_t dev_id;
    if ( AMBIENT21_OK == ambient21_read_register ( ctx, AMBIENT21_REG_ID, &dev_id ) ) 
    {
        if ( AMBIENT21_DEVICE_ID == dev_id )
        {
            return AMBIENT21_OK;
        }
    }
    return AMBIENT21_ERROR;
}

err_t ambient21_clear_interrupts ( ambient21_t *ctx )
{
    return ambient21_write_spec_func ( ctx, AMBIENT21_SF_CLEAR_ALS_NOPERS_INT );
}

err_t ambient21_set_config ( ambient21_t *ctx, uint8_t again, uint8_t atime )
{
    if ( ( again > AMBIENT21_AGAIN_MAX ) || ( atime > AMBIENT21_ATIME_600MS ) )
    {
        return AMBIENT21_ERROR;
    }
    switch ( again ) 
    {
        case AMBIENT21_AGAIN_LOW:
        {
            ctx->again = AMBIENT21_GAIN_0;
            break;
        }
        case AMBIENT21_AGAIN_MID:
        {
            ctx->again = AMBIENT21_GAIN_1;
            break;
        }
        case AMBIENT21_AGAIN_HIGH:
        {
            ctx->again = AMBIENT21_GAIN_2;
            break;
        }
        case AMBIENT21_AGAIN_MAX:
        {
            ctx->again = AMBIENT21_GAIN_3;
            break;
        }
    }
    ctx->atime_ms = AMBIENT21_TIME_RES + AMBIENT21_TIME_RES * atime; 
    ctx->cpl = ( ctx->atime_ms * ctx->again ) / AMBIENT21_LUX_GDF;
    return ambient21_write_register( ctx, AMBIENT21_REG_CONFIG, ( ( again << 4 ) & AMBIENT21_CONFIG_AGAIN_MASK ) | 
                                                                ( atime & AMBIENT21_CONFIG_ATIME_MASK ) );
}

err_t ambient21_read_raw_data ( ambient21_t *ctx, uint16_t *ch_0, uint16_t *ch_1 )
{
    uint8_t rx_data = 0;
    err_t error_flag = ambient21_read_register( ctx, AMBIENT21_REG_STATUS, &rx_data );
    if ( ( rx_data & AMBIENT21_STATUS_AINT ) && 
         ( rx_data & AMBIENT21_STATUS_AVALID ) && 
         ( AMBIENT21_OK == error_flag ) )
    {
        error_flag |= ambient21_read_register( ctx, AMBIENT21_REG_C0DATAL, &rx_data );
        *ch_0 = rx_data;
        error_flag |= ambient21_read_register( ctx, AMBIENT21_REG_C0DATAH, &rx_data );
        *ch_0 |= ( ( uint16_t ) rx_data << 8 );
        
        error_flag |= ambient21_read_register( ctx, AMBIENT21_REG_C1DATAL, &rx_data );
        *ch_1 = rx_data;
        error_flag |= ambient21_read_register( ctx, AMBIENT21_REG_C1DATAH, &rx_data );
        *ch_1 |= ( ( uint16_t ) rx_data << 8 );
        
        error_flag |= ambient21_clear_interrupts ( ctx );
        return error_flag;
    }
    return AMBIENT21_ERROR;
}

err_t ambient21_measure_light_level ( ambient21_t *ctx, uint16_t *lux )
{
    uint16_t ch0, ch1;
    err_t error_flag = ambient21_read_raw_data ( ctx, &ch0, &ch1 );
    if ( AMBIENT21_OK == error_flag )
    {
        if ( ( 0 != ch0 ) && ( 0 != ctx->cpl ) )
        {
            *lux = ( uint16_t ) ( ( ( ( float ) ch0 - ch1 ) * ( AMBIENT21_LUX_COEF - ( float ) ch1 / ch0 ) ) / ctx->cpl );
            return AMBIENT21_OK;
        }
    }
    return AMBIENT21_ERROR;
}

// ------------------------------------------------------------------------- END
