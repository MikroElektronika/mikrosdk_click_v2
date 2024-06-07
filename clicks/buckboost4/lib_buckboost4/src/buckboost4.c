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
 * @file buckboost4.c
 * @brief Buck-Boost 4 Click Driver.
 */

#include "buckboost4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void buckboost4_cfg_setup ( buckboost4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BUCKBOOST4_DEVICE_ADDRESS_1;
}

err_t buckboost4_init ( buckboost4_t *ctx, buckboost4_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t buckboost4_default_cfg ( buckboost4_t *ctx ) 
{   
    buckboost4_enable_device( ctx );
    Delay_100ms( );
    
    err_t err_flag = buckboost4_set_int_fb_ratio( ctx, BUCKBOOST4_VOUT_FS_INTFB_0_0564 );
    Delay_100ms( );
    
    err_flag |= buckboost4_output_enable( ctx );
    Delay_100ms( );

    return err_flag;
}

err_t buckboost4_generic_write ( buckboost4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t buckboost4_generic_read ( buckboost4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void buckboost4_enable_device ( buckboost4_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void buckboost4_disable_device ( buckboost4_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

err_t buckboost4_set_vref ( buckboost4_t *ctx, float vref_mv ) 
{
    err_t err_flag = BUCKBOOST4_OK;
    if ( ( BUCKBOOST4_VREF_MV_MAX < vref_mv ) || ( BUCKBOOST4_VREF_MV_MIN > vref_mv ) )
    {
        err_flag = BUCKBOOST4_ERROR;
    }
    else
    {
        uint8_t data_buf[ 2 ] = { 0 };
        vref_mv -= BUCKBOOST4_VREF_MV_MIN;
        vref_mv /= BUCKBOOST4_VREF_MV_STEP;
        data_buf[ 0 ] = ( uint8_t ) vref_mv;
        data_buf[ 1 ] = ( uint8_t ) ( ( uint16_t ) vref_mv >> 8 );
        err_flag = buckboost4_generic_write( ctx, BUCKBOOST4_REG_REF_LSB, data_buf, 2 );
    }
    return err_flag;
}

err_t buckboost4_current_limit_cfg ( buckboost4_t *ctx, uint8_t cl_en, float cltv_mv ) 
{
    err_t err_flag = BUCKBOOST4_OK;
    if ( (  BUCKBOOST4_IOUT_LIMIT_CLTV_MAX < cltv_mv ) || ( BUCKBOOST4_IOUT_LIMIT_CLTV_MIN > cltv_mv ) )
    {
        err_flag = BUCKBOOST4_ERROR;
    }
    else
    {
        uint8_t data_buf = DUMMY;
        data_buf = ( uint8_t ) ( cltv_mv / BUCKBOOST4_IOUT_LIMIT_CLTV_STEP );
        data_buf |= ( cl_en & 0x01 ) << 7;
        err_flag = buckboost4_generic_write( ctx, BUCKBOOST4_REG_IOUT_LIMIT, &data_buf, 1 );
    }
    return err_flag;
}

err_t buckboost4_set_ocp_delay ( buckboost4_t *ctx, uint8_t ocp_delay ) 
{
    err_t err_flag = BUCKBOOST4_OK;
    if ( BUCKBOOST4_VOUT_SR_OCP_DELAY_12_S < ocp_delay )
    {
        err_flag = BUCKBOOST4_ERROR;
    }
    else
    {
        uint8_t data_buf = DUMMY;
        err_flag = buckboost4_generic_read( ctx, BUCKBOOST4_REG_VOUT_SR, &data_buf, 1 );
        data_buf &= BUCKBOOST4_VOUT_SR_OCP_DELAY_BIT_MASK;
        data_buf |= ocp_delay << 4;
        err_flag = buckboost4_generic_write( ctx, BUCKBOOST4_REG_VOUT_SR, &data_buf, 1 );
    }
    return err_flag;
}

err_t buckboost4_set_slew_rate ( buckboost4_t *ctx, uint8_t slew_rate ) 
{
    err_t err_flag = BUCKBOOST4_OK;
    if ( BUCKBOOST4_VOUT_SR_SR_MV_US_10 < slew_rate )
    {
        err_flag = BUCKBOOST4_ERROR;
    }
    else
    {
        uint8_t data_buf = DUMMY;
        err_flag = buckboost4_generic_read( ctx, BUCKBOOST4_REG_VOUT_SR, &data_buf, 1 );
        data_buf &= BUCKBOOST4_VOUT_SR_SR_BIT_MASK;
        data_buf |= slew_rate;
        err_flag = buckboost4_generic_write( ctx, BUCKBOOST4_REG_VOUT_SR, &data_buf, 1 );
    }
    return err_flag;
}

err_t buckboost4_en_ext_output_vtg ( buckboost4_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = buckboost4_generic_read( ctx, BUCKBOOST4_REG_VOUT_FS, &data_buf, 1 );
    data_buf |= BUCKBOOST4_VOUT_FS_FB_EXT;
    err_flag |= buckboost4_generic_write( ctx, BUCKBOOST4_REG_VOUT_FS, &data_buf, 1 );
    return err_flag;
}

err_t buckboost4_set_int_fb_ratio ( buckboost4_t *ctx, uint8_t int_fb_ratio ) 
{
    uint8_t data_buf = DUMMY;
    int_fb_ratio &= BUCKBOOST4_VOUT_FS_INTFB_0_0564;
    err_t err_flag = buckboost4_generic_read( ctx, BUCKBOOST4_REG_VOUT_FS, &data_buf, 1 );
    data_buf &= BUCKBOOST4_VOUT_FS_INTFB_BIT_MASK;
    data_buf |= int_fb_ratio;
    err_flag |= buckboost4_generic_write( ctx, BUCKBOOST4_REG_VOUT_FS, &data_buf, 1 );
    return err_flag;
}

err_t buckboost4_output_enable ( buckboost4_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = buckboost4_generic_read( ctx, BUCKBOOST4_REG_MODE, &data_buf, 1 );
    data_buf |= BUCKBOOST4_MODE_OE_EN;
    err_flag |= buckboost4_generic_write( ctx, BUCKBOOST4_REG_MODE, &data_buf, 1 );
    return err_flag;
}

err_t buckboost4_output_disable ( buckboost4_t *ctx ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = buckboost4_generic_read( ctx, BUCKBOOST4_REG_MODE, &data_buf, 1 );
    data_buf &= ~BUCKBOOST4_MODE_OE_EN;
    err_flag |= buckboost4_generic_write( ctx, BUCKBOOST4_REG_MODE, &data_buf, 1 );
    return err_flag;
}

err_t buckboost4_set_mode ( buckboost4_t *ctx, uint8_t fswdbl, uint8_t hiccup, 
                                               uint8_t dischg, uint8_t fpwm ) 
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = buckboost4_generic_read( ctx, BUCKBOOST4_REG_MODE, &data_buf, 1 );
    data_buf &= BUCKBOOST4_MODE_BIT_MASK;
    data_buf |= ( fswdbl & BUCKBOOST4_MODE_FSWDBL_EN ) << 6;
    data_buf |= ( hiccup & BUCKBOOST4_MODE_HICCUP_EN ) << 5;
    data_buf |= ( dischg & BUCKBOOST4_MODE_DISCHG_EN ) << 4;
    data_buf |= ( fpwm & BUCKBOOST4_MODE_FPWM_EN ) << 1;
    err_flag |= buckboost4_generic_write( ctx, BUCKBOOST4_REG_MODE, &data_buf, 1 );
    return err_flag;
}

err_t buckboost4_get_status ( buckboost4_t *ctx, uint8_t *status ) 
{
    return buckboost4_generic_read( ctx, BUCKBOOST4_REG_STATUS, status, 1 );
}

err_t buckboost4_set_vout ( buckboost4_t *ctx, float vout_v ) 
{
    err_t err_flag = BUCKBOOST4_OK;
    uint8_t data_buf = DUMMY;
    float vref_mv = DUMMY;
    float intfb = BUCKBOOST4_INTFB_STEP_MAX;
    err_flag = buckboost4_generic_read( ctx, BUCKBOOST4_REG_VOUT_FS, &data_buf, 1 );
    data_buf &= BUCKBOOST4_VOUT_FS_INTFB_0_0564;
    if ( ( BUCKBOOST4_VOUT_LIM_MIN > vout_v )  ||
         ( ( BUCKBOOST4_VOUT_FS_INTFB_0_2256 == data_buf ) && ( BUCKBOOST4_VOUT_LIM_5_V < vout_v ) )  || 
         ( ( BUCKBOOST4_VOUT_FS_INTFB_0_1128 == data_buf ) && ( BUCKBOOST4_VOUT_LIM_10_V < vout_v ) ) || 
         ( ( BUCKBOOST4_VOUT_FS_INTFB_0_0752 == data_buf ) && ( BUCKBOOST4_VOUT_LIM_15_V < vout_v ) ) ||
         ( ( BUCKBOOST4_VOUT_FS_INTFB_0_0564 == data_buf ) && ( BUCKBOOST4_VOUT_LIM_20_V < vout_v ) ) ||
         ( BUCKBOOST4_VOUT_LIM_MAX < vout_v ) )
    {
        err_flag = BUCKBOOST4_ERROR;
    }
    else
    {
        data_buf++;
        intfb /= ( float ) data_buf;
        vref_mv = vout_v;
        vref_mv *= BUCKBOOST4_CONVERT_V_TO_MV;
        vref_mv *= intfb;
        err_flag |= buckboost4_set_vref( ctx, vref_mv );
    }
    return err_flag;
}

uint8_t buckboost4_fault_indicator ( buckboost4_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
