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
 * @file proximity19.c
 * @brief Proximity 19 Click Driver.
 */

#include "proximity19.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void proximity19_cfg_setup ( proximity19_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY19_DEVICE_ADDRESS;
}

err_t proximity19_init ( proximity19_t *ctx, proximity19_cfg_t *cfg ) 
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
    ctx->data_range = PROXIMITY19_DATA_RANGE_50_US;
    ctx->gain = PROXIMITY19_GAIN_X1;

    return I2C_MASTER_SUCCESS;
}

err_t proximity19_default_cfg ( proximity19_t *ctx ) 
{
    uint8_t manufact_id = DUMMY;
    err_t err_flag = proximity19_get_manufact_id( ctx, &manufact_id );
    if ( PROXIMITY19_MANUFACT_ID == manufact_id )
    {
        err_flag |= proximity19_sw_reset( ctx );
        Delay_100ms( );

        err_flag |= proximity19_set_pulse_width( ctx, 0 );
        Delay_10ms( );

        err_flag |= proximity19_set_period( ctx, 0 );
        Delay_10ms( );
        
        err_flag |= proximity19_set_pd_sel( ctx, 1 );
        Delay_10ms( );

        err_flag |= proximity19_set_ps_gain( ctx, 0 );
        Delay_10ms( );

        err_flag |= proximity19_ps_enable( ctx );
        Delay_10ms( );
    }
    else
    {
        err_flag = PROXIMITY19_ERROR;
    }

    return err_flag;
}

err_t proximity19_generic_write ( proximity19_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t proximity19_generic_read ( proximity19_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t proximity19_sw_reset ( proximity19_t *ctx ) 
{
    uint8_t data_buf = PROXIMITY19_SW_RESET | PROXIMITY19_PART_ID_VAL;
    return proximity19_generic_write( ctx, PROXIMITY19_REG_SYSTEM_CONTROL, &data_buf, 1 );
}

err_t proximity19_get_part_id ( proximity19_t *ctx, uint8_t *part_id ) 
{
    err_t err_flag = proximity19_generic_read( ctx, PROXIMITY19_REG_SYSTEM_CONTROL, part_id, 1 );
    *part_id &= PROXIMITY19_PART_ID_BITMASK;
    return err_flag;
}

err_t proximity19_set_ps_gain ( proximity19_t *ctx, uint8_t ps_gain ) 
{
    uint8_t data_buf = DUMMY, pd_sel = DUMMY;
    err_t err_flag = proximity19_generic_read( ctx, PROXIMITY19_REG_MODE_CONTROL0, &data_buf, 1 );
    pd_sel = data_buf & PROXIMITY19_PD_SEL_BITMASK;
    data_buf &= PROXIMITY19_PS_GAIN_BITMASK;
    if ( PROXIMITY19_PS_GAIN_X1 == ps_gain )
    {
        err_flag |= proximity19_generic_write( ctx, PROXIMITY19_REG_MODE_CONTROL0, &data_buf, 1 );
        ctx->gain = PROXIMITY19_GAIN_X1;
    }
    else if ( PROXIMITY19_PS_GAIN_X2 == ps_gain )
    {
        data_buf |= PROXIMITY19_PS_GAIN_X2 << 3;
        err_flag |= proximity19_generic_write( ctx, PROXIMITY19_REG_MODE_CONTROL0, &data_buf, 1 );
        if ( PROXIMITY19_PD_SEL_BOTH == pd_sel )
        {
            ctx->gain = PROXIMITY19_GAIN_X2_BOTH_PD;
        }
        else
        if ( PROXIMITY19_PD_SEL_NEAR == pd_sel )
        {
            ctx->gain = PROXIMITY19_GAIN_X2;
        }
        else if ( PROXIMITY19_PD_SEL_FAR == pd_sel )
        {
            ctx->gain = PROXIMITY19_GAIN_X1;
        }
    }
    else
    {
        err_flag = PROXIMITY19_ERROR;
    }
    return err_flag;
}

err_t proximity19_set_pd_sel ( proximity19_t *ctx, uint8_t pd_sel ) 
{
    err_t err_flag = PROXIMITY19_ERROR;
    if ( PROXIMITY19_PD_SEL_BOTH >= pd_sel )
    {
        uint8_t data_buf = DUMMY;
        err_flag = proximity19_generic_read( ctx, PROXIMITY19_REG_MODE_CONTROL0, &data_buf, 1 );
        data_buf &= ~PROXIMITY19_PD_SEL_BITMASK;
        data_buf |= pd_sel;
        err_flag |= proximity19_generic_write( ctx, PROXIMITY19_REG_MODE_CONTROL0, &data_buf, 1 );
    }
    return err_flag;
}

err_t proximity19_set_period ( proximity19_t *ctx, uint8_t period ) 
{
    err_t err_flag = PROXIMITY19_ERROR;
    if ( PROXIMITY19_PERIOD_5_MS >= period )
    {
        uint8_t data_buf = DUMMY;
        err_flag = proximity19_generic_read( ctx, PROXIMITY19_REG_MODE_CONTROL1, &data_buf, 1 );
        data_buf &= ~PROXIMITY19_PERIOD_BITMASK;
        period <<= 4;
        data_buf |= period;
        err_flag |= proximity19_generic_write( ctx, PROXIMITY19_REG_MODE_CONTROL1, &data_buf, 1 );
    }
    return err_flag;
}

err_t proximity19_set_pulse_width ( proximity19_t *ctx, uint8_t pulse_width ) 
{
    err_t err_flag = PROXIMITY19_ERROR;
    if ( PROXIMITY19_PS_PULSE_400_US >= pulse_width )
    {
        ctx->data_range = PROXIMITY19_DATA_RANGE_50_US;
        if ( PROXIMITY19_PS_PULSE_200_US == pulse_width )
        {
            ctx->data_range = PROXIMITY19_DATA_RANGE_200_US;
        }
        else if ( PROXIMITY19_PS_PULSE_400_US == pulse_width )
        {
            ctx->data_range = PROXIMITY19_DATA_RANGE_400_US;
        }
        uint8_t data_buf = DUMMY;
        err_flag = proximity19_generic_read( ctx, PROXIMITY19_REG_MODE_CONTROL1, &data_buf, 1 );
        data_buf &= ~PROXIMITY19_PS_PULSE_BITMASK;
        pulse_width <<= 2;
        data_buf |= pulse_width;
        err_flag |= proximity19_generic_write( ctx, PROXIMITY19_REG_MODE_CONTROL1, &data_buf, 1 );
    }
    return err_flag;
}

err_t proximity19_set_vcsel_current ( proximity19_t *ctx, uint8_t vcsel_current ) 
{
    err_t err_flag = PROXIMITY19_ERROR;
    if ( PROXIMITY19_VCSEL_CURR_5_MA >= vcsel_current )
    {
        uint8_t data_buf = DUMMY;
        err_flag = proximity19_generic_read( ctx, PROXIMITY19_REG_MODE_CONTROL1, &data_buf, 1 );
        data_buf &= ~PROXIMITY19_VCSEL_CURR_BITMASK;
        data_buf |= vcsel_current;
        err_flag |= proximity19_generic_write( ctx, PROXIMITY19_REG_MODE_CONTROL1, &data_buf, 1 );
    }
    return err_flag;
}

err_t proximity19_ps_enable ( proximity19_t *ctx ) 
{
    uint8_t data_buf = PROXIMITY19_PS_ENABLE;
    return proximity19_generic_write( ctx, PROXIMITY19_REG_MODE_CONTROL2, &data_buf, 1 );
}

err_t proximity19_ps_disable ( proximity19_t *ctx ) 
{
    uint8_t data_buf = PROXIMITY19_PS_DISABLE;
    return proximity19_generic_write( ctx, PROXIMITY19_REG_MODE_CONTROL2, &data_buf, 1 );
}

err_t proximity19_get_ps_data ( proximity19_t *ctx, uint16_t *ps_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = proximity19_generic_read( ctx, PROXIMITY19_REG_PS_DATA_LSB, data_buf, 2 );
    *ps_data = data_buf[ 1 ] & PROXIMITY19_PS_RES_MSB_BITMASK;
    *ps_data <<= 8;
    *ps_data |= data_buf[ 0 ];

    return err_flag;
}

err_t proximity19_get_distance ( proximity19_t *ctx, float *proximity ) 
{
    uint16_t ps_data = DUMMY;
    err_t err_flag = proximity19_get_ps_data( ctx, &ps_data );
    *proximity = ctx->data_range;
    *proximity -= ( float ) ps_data;
    *proximity /= ctx->data_range;
    *proximity *= PROXIMITY19_DET_RANGE_MAX;
    *proximity *= ctx->gain;
    *proximity += PROXIMITY19_DET_RANGE_MIN;
    return err_flag;
}

err_t proximity19_set_ps_offset ( proximity19_t *ctx, uint16_t ps_offset ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ps_offset;
    data_buf[ 1 ] = ( ( uint8_t ) ( ps_offset >> 8 ) ) & PROXIMITY19_PS_OFFSET_BITMASK;
    return proximity19_generic_write( ctx, PROXIMITY19_REG_PS_OFFSET_LSB, data_buf, 2 );
}

err_t proximity19_int_cfg ( proximity19_t *ctx, uint8_t int_cfg ) 
{
    return proximity19_generic_write( ctx, PROXIMITY19_REG_INTERRUPT, &int_cfg, 1 );
}

err_t proximity19_set_ps_th ( proximity19_t *ctx, uint16_t ps_th_high, uint16_t ps_th_low ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ps_th_high;
    data_buf[ 1 ] = ( ( uint8_t ) ( ps_th_high >> 8 ) ) & PROXIMITY19_PS_TH_RES;
    err_t err_flag = proximity19_generic_write( ctx, PROXIMITY19_REG_PS_TH_HIGH_LSB, data_buf, 2 );
    data_buf[ 0 ] = ( uint8_t ) ps_th_low;
    data_buf[ 1 ] = ( ( uint8_t ) ( ps_th_low >> 8 ) ) & PROXIMITY19_PS_TH_RES;
    err_flag |= proximity19_generic_write( ctx, PROXIMITY19_REG_PS_TH_LOW_LSB, data_buf, 2 );
    return err_flag;
}

err_t proximity19_get_manufact_id ( proximity19_t *ctx, uint8_t *manufact_id ) 
{
    return proximity19_generic_read( ctx, PROXIMITY19_REG_MANUFACT_ID, manufact_id, 1 );
}

uint8_t proximity19_get_int_pin ( proximity19_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
