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
 * @file smartbuck2.c
 * @brief Smart Buck 2 Click Driver.
 */

#include "smartbuck2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY    0x00

void smartbuck2_cfg_setup ( smartbuck2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTBUCK2_DEVICE_ADDRESS;
}

err_t smartbuck2_init ( smartbuck2_t *ctx, smartbuck2_cfg_t *cfg ) 
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

err_t smartbuck2_default_cfg ( smartbuck2_t *ctx ) 
{
    uint8_t ven_id = DUMMY, part_num_id = DUMMY, chip_id = DUMMY;
    err_t err_flag = smartbuck2_get_device_id( ctx, &ven_id, &part_num_id, &chip_id );
    Delay_1ms( );
    if ( ( SMARTBUCK2_ID_VENDOR == ven_id ) || ( SMARTBUCK2_ID_PART_NUM == part_num_id ) )
    {
        err_flag |= smartbuck2_set_ctrl( ctx, SMARTBUCK2_CTRL_PD_EN | 
                                              SMARTBUCK2_CTRL_PD_VSEL0_DIS | 
                                              SMARTBUCK2_CTRL_PD_VSEL1_DIS );
    
        err_flag |= smartbuck2_set_voltage( ctx, SMARTBUCK2_VOUT_MIN );
        err_flag |= smartbuck2_set_op_mode( ctx, SMARTBUCK2_OP_MODE_PFM );
        err_flag |= smartbuck2_set_temp_shd( ctx, SMARTBUCK2_TEMP_TS_ENABLE );
    }
    else
    {
        err_flag = SMARTBUCK2_ERROR;
    }
    return err_flag;
}

err_t smartbuck2_generic_write ( smartbuck2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t smartbuck2_generic_read ( smartbuck2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t smartbuck2_set_voltage ( smartbuck2_t *ctx, uint16_t vout_mv ) 
{
    err_t err_flag = SMARTBUCK2_ERROR;
    if ( ( SMARTBUCK2_VOUT_MIN <= vout_mv ) && ( SMARTBUCK2_VOUT_MAX >= vout_mv ) )
    {
        uint8_t data_buf = DUMMY;
        err_flag = smartbuck2_generic_read( ctx, SMARTBUCK2_REG_SET2, &data_buf, 1 );
        data_buf &= SMARTBUCK2_OP_MOD_BIT_MASK;
        data_buf |= ( uint8_t ) ( ( vout_mv - SMARTBUCK2_VOUT_START_500MV ) / SMARTBUCK2_VOUT_STEP_10MV );
        err_flag |= smartbuck2_generic_write( ctx, SMARTBUCK2_REG_SET2, &data_buf, 1 );
    }
    return err_flag;
}

err_t smartbuck2_get_voltage ( smartbuck2_t *ctx, uint16_t *vout_mv ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = smartbuck2_generic_read( ctx, SMARTBUCK2_REG_SET2, &data_buf, 1 );
    data_buf &= ~SMARTBUCK2_OP_MOD_BIT_MASK;
    *vout_mv = ( uint16_t ) data_buf;
    *vout_mv *= SMARTBUCK2_VOUT_STEP_10MV;
    *vout_mv += SMARTBUCK2_VOUT_START_500MV;
    return err_flag;
}

err_t smartbuck2_set_op_mode ( smartbuck2_t *ctx, uint8_t op_mode ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = smartbuck2_get_op_mode( ctx, &data_buf );
    data_buf &= ~SMARTBUCK2_OP_MOD_BIT_MASK;
    if ( SMARTBUCK2_OP_MODE_FORCED_PWM == op_mode )
    {
        data_buf |= SMARTBUCK2_OP_MODE_FORCED_PWM;
    }
    err_flag |= smartbuck2_generic_write( ctx, SMARTBUCK2_REG_SET2, &data_buf, 1 );
    return err_flag;
}

err_t smartbuck2_get_op_mode ( smartbuck2_t *ctx, uint8_t *op_mode ) 
{
    err_t err_flag = smartbuck2_generic_read( ctx, SMARTBUCK2_REG_SET2, op_mode, 1 );
    *op_mode &= ~SMARTBUCK2_OP_MOD_BIT_MASK;
    return err_flag;
}

err_t smartbuck2_set_ctrl ( smartbuck2_t *ctx, uint8_t ctrl ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = smartbuck2_generic_read( ctx, SMARTBUCK2_REG_CTRL, &data_buf, 1 );
    ctrl &= SMARTBUCK2_CTRL_BIT_MASK;
    data_buf |= ctrl;
    err_flag |= smartbuck2_generic_write( ctx, SMARTBUCK2_REG_CTRL, &data_buf, 1 );
    return err_flag;
}

err_t smartbuck2_get_ctrl ( smartbuck2_t *ctx, uint8_t *ctrl ) 
{
    err_t err_flag = smartbuck2_generic_read( ctx, SMARTBUCK2_REG_CTRL, ctrl, 1 );
    *ctrl &= SMARTBUCK2_CTRL_BIT_MASK;
    return err_flag;
}

err_t smartbuck2_set_temp_shd ( smartbuck2_t *ctx, uint8_t temp_enable ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = smartbuck2_generic_read( ctx, SMARTBUCK2_REG_TEMP, &data_buf, 1 );
    data_buf &= SMARTBUCK2_TEMP_DIS_BIT_MASK;
    if ( SMARTBUCK2_TEMP_TS_DISABLE == temp_enable )
    {
        data_buf |= SMARTBUCK2_TEMP_TS_DISABLE;
    }
    err_flag |= smartbuck2_generic_write( ctx, SMARTBUCK2_REG_TEMP, &data_buf, 1 );
    return err_flag;
}

uint8_t smartbuck2_check_temp_warning ( smartbuck2_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    if ( SMARTBUCK2_OK == smartbuck2_generic_read( ctx, SMARTBUCK2_REG_TEMP, &data_buf, 1 ) )
    {
        data_buf &= SMARTBUCK2_TEMP_TJEW;
        data_buf >>= 1;
    }
    else
    {
        data_buf = SMARTBUCK2_TEMP_ERROR;
    }
    return data_buf;
}

err_t smartbuck2_set_vtg_ramp_timing ( smartbuck2_t *ctx, uint8_t slope ) 
{
    err_t err_flag = SMARTBUCK2_ERROR;
    uint8_t data_buf = DUMMY;
    if ( SMARTBUCK2_RMP_VTG_T_0_25MVNS >= slope )
    {
        err_flag = smartbuck2_generic_read( ctx, SMARTBUCK2_REG_RMPCTRL, &data_buf, 1 );
        data_buf &= SMARTBUCK2_RMP_VTG_T_BIT_MASK;
        data_buf |= ( slope << 5 );
        err_flag |= smartbuck2_generic_write( ctx, SMARTBUCK2_REG_RMPCTRL, &data_buf, 1 ); 
    }
    return err_flag;
}

err_t smartbuck2_get_device_id ( smartbuck2_t *ctx, uint8_t *ven_id, uint8_t *part_num_id, uint8_t *chip_id ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = smartbuck2_generic_read( ctx, SMARTBUCK2_REG_CHIP_ID_0, &data_buf, 1 );
    *ven_id      = ( data_buf & SMARTBUCK2_VENDOR_ID_BIT_MASK ) >> 4;
    *part_num_id = ( data_buf & SMARTBUCK2_PART_NUM_ID_BIT_MASK ) >> 2;
    *chip_id     = data_buf & SMARTBUCK2_CHIP_REV_ID_BIT_MASK;
    return err_flag;
}

// ------------------------------------------------------------------------- END
