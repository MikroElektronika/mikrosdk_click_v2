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
 * @file magneto11.c
 * @brief Magneto 11 Click Driver.
 */

#include "magneto11.h"

/**
 * @brief Magneto 11 calculate parity bit function.
 * @details This function calculates the parity bit.
 * @param[in] ctx : Click context object.
 * See #magneto11_t object definition for detailed explanation.
 * @param[in] data_in : Data from which it will calculate the parity bit.
 * @return @li @c  0 - Even parity,
 *         @li @c  1 - ODD parity.
 * @note None.
 */
static uint8_t magneto11_calculate_parity_bit ( uint16_t data_in );

void magneto11_cfg_setup ( magneto11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = MAGNETO11_DEV_ADDR_VCC;
}

err_t magneto11_init ( magneto11_t *ctx, magneto11_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t magneto11_default_cfg ( magneto11_t *ctx ) 
{
    err_t error_flag = MAGNETO11_OK;
    
    error_flag |= magneto11_set_config ( ctx, MAGNETO11_CONFIG_SPEED_FAST | 
                                              MAGNETO11_CONFIG_POLARITY_NORMAL | 
                                              MAGNETO11_CONFIG_OP_NORMAL );
    error_flag |= magneto11_set_sensitivity ( ctx, MAGNETO11_SENSITIVITY_RES_50mT );
    
    return error_flag;
}

err_t magneto11_generic_write ( magneto11_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len )
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t magneto11_generic_read ( magneto11_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t magneto11_get_magnetic_field ( magneto11_t *ctx, float *mag_field )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( MAGNETO11_OK == magneto11_generic_read ( ctx, MAGNETO11_REG_DATA_LSB, data_buf, 2 ) )
    {
        int16_t raw_data = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        uint8_t offset_comp_flag = ( raw_data & MAGNETO11_DATA_OCF_MASK ) >> 11;
        uint8_t parity_bit = ( raw_data & MAGNETO11_DATA_PARITY_MASK ) >> 10;
        raw_data &= MAGNETO11_DATA_RESOLUTION;
        if ( offset_comp_flag && ( parity_bit == magneto11_calculate_parity_bit ( raw_data ) ) )
        {
            uint8_t sensitivity = 0;
            if ( MAGNETO11_ERROR == magneto11_generic_read ( ctx, MAGNETO11_REG_SENSITIVITY, &sensitivity, 1 ) )
            {
                return MAGNETO11_ERROR;
            }
            *mag_field = raw_data - MAGNETO11_DATA_RESOLUTION / 2;
            switch ( sensitivity & MAGNETO11_SENSITIVITY_RES_MASK )
            {
                case MAGNETO11_SENSITIVITY_RES_50mT:
                {
                    *mag_field *= MAGNETO11_SENSITIVITY_LSB_50mT;
                    break;
                }
                case MAGNETO11_SENSITIVITY_RES_25mT:
                {
                    *mag_field *= MAGNETO11_SENSITIVITY_LSB_25mT;
                    break;
                }
                case MAGNETO11_SENSITIVITY_RES_12p5mT:
                {
                    *mag_field *= MAGNETO11_SENSITIVITY_LSB_12p5mT;
                    break;
                }
                case MAGNETO11_SENSITIVITY_RES_18p75mT:
                {
                    *mag_field *= MAGNETO11_SENSITIVITY_LSB_18p75mT;
                    break;
                }
            }
            return MAGNETO11_OK;
        }
    }
    return MAGNETO11_ERROR;
}

err_t magneto11_get_offset ( magneto11_t *ctx, uint16_t *offset )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( MAGNETO11_OK == magneto11_generic_read ( ctx, MAGNETO11_REG_OFFSET_LSB, data_buf, 2 ) )
    {
        *offset = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        return MAGNETO11_OK;
    }
    return MAGNETO11_ERROR;
}

err_t magneto11_set_config ( magneto11_t *ctx, uint8_t config )
{
    return magneto11_generic_write ( ctx, MAGNETO11_REG_CONFIG, &config, 1 );
}

err_t magneto11_set_sensitivity ( magneto11_t *ctx, uint8_t sensitivity )
{
    return magneto11_generic_write ( ctx, MAGNETO11_REG_SENSITIVITY, &sensitivity, 1 );
}

static uint8_t magneto11_calculate_parity_bit ( uint16_t data_in )
{
    uint8_t parity = 0;
    while ( data_in )
    {
        parity++;
        data_in &= ( data_in - 1 );
    }
    return parity & 0x01;
}

// ------------------------------------------------------------------------- END
