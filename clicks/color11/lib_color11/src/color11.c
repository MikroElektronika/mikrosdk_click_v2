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
 * @file color11.c
 * @brief Color 11 Click Driver.
 */

#include "color11.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                        0x00

void color11_cfg_setup ( color11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COLOR11_DEVICE_ADDRESS;
}

err_t color11_init ( color11_t *ctx, color11_cfg_t *cfg ) 
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

err_t color11_default_cfg ( color11_t *ctx ) 
{    
    color11_identification_t id;
    err_t err_flag = color11_get_identification( ctx, &id );
    Delay_1ms( );
    if ( ( COLOR11_ID_AUX == id.aux_id ) && ( COLOR11_ID_REV == id.rev_id ) && ( COLOR11_ID_DEV == id.dev_id ) )
    {        
        err_flag |= color11_set_power_ctrl( ctx, COLOR11_ENABLE, COLOR11_ENABLE, 
                                                 COLOR11_DISABLE, COLOR11_DISABLE );
        Delay_1ms( );
        
        err_flag |= color11_set_als_step( ctx, COLOR11_ALS_STEP_DEFAULT );
        Delay_1ms( );
        
        err_flag |= color11_set_als_time( ctx, COLOR11_ALS_INTEG_TIME_DEFAULT );
        Delay_1ms( );
        
        err_flag |= color11_set_gain( ctx, COLOR11_AGAIN_X8 );
        Delay_1ms( );
        
        err_flag |= color11_set_als_thold( ctx, COLOR11_ALS_THOLD_LOW_DEFAULT, COLOR11_ALS_THOLD_HIGH_DEFAULT );
        Delay_1ms( );
        
        err_flag |= color11_set_interrupt( ctx, COLOR11_SET_INTENAB_ASI_DIS | COLOR11_SET_INTENAB_AI_EN | COLOR11_SET_INTENAB_SI_DIS );
        Delay_1ms( );
    }
    else
    {
        err_flag = COLOR11_ERROR;
    }
    
    return err_flag;
}

err_t color11_generic_write ( color11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t color11_generic_read ( color11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t color11_get_identification ( color11_t *ctx, color11_identification_t *id ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    err_t err_flag = color11_generic_read( ctx, COLOR11_REG_AUXID, data_buf, 3 );
    id->aux_id = data_buf[ 0 ];
    id->rev_id = data_buf[ 1 ];
    id->dev_id = data_buf[ 2 ];
    return err_flag;
}

err_t color11_set_als_thold ( color11_t *ctx, uint16_t l_thold, uint16_t h_thold ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) l_thold;
    data_buf[ 1 ] = ( uint8_t ) ( l_thold >> 8 );
    err_t err_flag = color11_generic_write( ctx, COLOR11_REG_AILTL, data_buf, 2 );
    data_buf[ 0 ] = ( uint8_t ) h_thold;
    data_buf[ 1 ] = ( uint8_t ) ( h_thold >> 8 );
    err_flag |= color11_generic_write( ctx, COLOR11_REG_AIHTL, data_buf, 2 );
    return err_flag;
}

err_t color11_set_power_ctrl ( color11_t *ctx, 
                               color11_pwr_ctrl_t pwr, 
                               color11_pwr_ctrl_t aen, 
                               color11_pwr_ctrl_t wen, 
                               color11_pwr_ctrl_t fden ) 
{
    uint8_t data_buf = pwr;
    data_buf |= aen << 1;
    data_buf |= wen << 3;
    data_buf |= fden << 6;
    return color11_generic_write( ctx, COLOR11_REG_ENABLE, &data_buf, 1 );
}

err_t color11_set_als_step ( color11_t *ctx, uint32_t als_step ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint32_t step = als_step * COLOR11_ALS_STEP_CONV_TO_US;
    step += COLOR11_ALS_STEP_MIN_ASTEP / 2;
    step /= COLOR11_ALS_STEP_MIN_ASTEP;
    --step;
    data_buf[ 0 ] = ( uint8_t ) step;
    data_buf[ 1 ] = ( uint8_t ) ( step >> 8 );
    return color11_generic_write( ctx, COLOR11_REG_ASTEPL, data_buf, 2 );
}

err_t color11_get_als_step ( color11_t *ctx, uint32_t *als_step ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint32_t step = DUMMY;
    err_t err_flag = color11_generic_read( ctx, COLOR11_REG_ASTEPL, data_buf, 2 );
    step = data_buf[ 1 ];
    step <<= 8;
    step |= data_buf[ 0 ];
    ++step;
    step *= COLOR11_ALS_STEP_MIN_ASTEP;
    step += COLOR11_ALS_STEP_COR_FACT;
    step /= COLOR11_ALS_STEP_CONV_TO_US;
    *als_step = ( uint16_t ) step;
    return err_flag;
}

err_t color11_set_als_wait ( color11_t *ctx, uint8_t wait_time ) 
{
    return color11_generic_write( ctx, COLOR11_REG_WTIME, &wait_time, 1 );
}

err_t color11_set_als_time ( color11_t *ctx, uint32_t als_time ) 
{
    uint8_t data_buf = DUMMY;
    uint32_t step = DUMMY;
    err_t err_flag = color11_get_als_step( ctx, &step );
    data_buf = ( uint8_t ) ( ( ( als_time * COLOR11_ALS_STEP_CONV_TO_US ) + ( step / 2 ) ) / step - 1 );
    return color11_generic_write( ctx, COLOR11_REG_ATIME, &data_buf, 2 );
}

err_t color11_get_als_time ( color11_t *ctx, float *als_time ) 
{
    uint8_t data_buf = DUMMY;
    uint32_t step = DUMMY;
    err_t err_flag = color11_get_als_step( ctx, &step );
    err_flag |= color11_generic_read( ctx, COLOR11_REG_ATIME, &data_buf, 1 );
    *als_time = ( float ) data_buf;
    *als_time += 1;
    *als_time *= ( ( step + COLOR11_ALS_STEP_COR_FACT ) / COLOR11_ALS_STEP_CONV_TO_US ) * 2;
    return err_flag;
}

err_t color11_set_gain ( color11_t *ctx, color11_again_t gain ) 
{
    return color11_generic_write( ctx, COLOR11_REG_CFG1, &gain, 1 );
}

err_t color11_get_gain ( color11_t *ctx, uint8_t *gain ) 
{
    return color11_generic_read( ctx, COLOR11_REG_CFG1, gain, 1 );
}

err_t color11_set_interrupt ( color11_t *ctx, uint8_t intenab ) 
{
    return color11_generic_write( ctx, COLOR11_REG_INTENAB, &intenab, 1 );
}

err_t color11_get_data_valid_status ( color11_t *ctx, uint8_t *status ) 
{
    return color11_generic_read( ctx, COLOR11_REG_STATUS2, status, 1 );
}

err_t color11_get_als_data ( color11_t *ctx, color11_als_data_t *als_data ) 
{
    uint8_t data_buf[ 13 ] = { 0 };
    err_t err_flag = color11_generic_read( ctx, COLOR11_REG_ASTATUS, data_buf, 13 );
    
    als_data->clear = data_buf[ 2 ];
    als_data->clear <<= 8;
    als_data->clear |= data_buf[ 1 ];
    
    als_data->red = data_buf[ 4 ];
    als_data->red <<= 8;
    als_data->red |= data_buf[ 3 ];
    
    als_data->green = data_buf[ 6 ];
    als_data->green <<= 8;
    als_data->green |= data_buf[ 5 ];
    
    als_data->blue = data_buf[ 8 ];
    als_data->blue <<= 8;
    als_data->blue |= data_buf[ 7 ];
    
    als_data->wideband = data_buf[ 10 ];
    als_data->wideband <<= 8;
    als_data->wideband |= data_buf[ 9 ];
    
    als_data->flicker = data_buf[ 12 ];
    als_data->flicker <<= 8;
    als_data->flicker |= data_buf[ 11 ];
    return err_flag;
}

err_t color11_get_ir ( color11_t *ctx, float *ir ) 
{
    color11_als_data_t als_data;
    err_t err_flag = color11_get_als_data( ctx, &als_data );
    
    *ir = ( float ) als_data.red;
    *ir += ( float ) als_data.green;
    *ir += ( float ) als_data.blue;
    *ir -= ( float ) als_data.clear;
    *ir /= 2.0;
    return err_flag;
}

err_t color11_get_illuminance ( color11_t *ctx, float *lux ) 
{
    color11_als_data_t als_data;
    err_t err_flag = color11_get_als_data( ctx, &als_data );
    Delay_1ms( );
    float als_time = DUMMY,  ir = DUMMY;
    uint8_t gain = DUMMY;
    color11_get_als_time( ctx, &als_time );
    Delay_1ms( );
    
    color11_get_gain( ctx, &gain );
    Delay_1ms( );
    
    color11_get_ir( ctx, &ir );
    
    if ( COLOR11_AGAIN_X0_5 == gain )
    {
        als_time /= 2.0; 
    }
    else
    {
        --gain;
        als_time *= ( float ) ( 1u << gain );
    }
 
    *lux = COLOR11_COEF_CLR_DEFAULT * ( ( float ) als_data.clear - ir );
    *lux += COLOR11_COEF_RED_DEFAULT * ( ( float ) als_data.red - ir );
    *lux += COLOR11_COEF_GREEN_DEFAULT * ( ( float ) als_data.green - ir );
    *lux += COLOR11_COEF_BLUE_DEFAULT * ( ( float ) als_data.blue - ir );
    *lux *= COLOR11_COEF_DGF_DEFAULT;
    *lux /= ( float ) ( als_time * COLOR11_ALS_STEP_CONV_TO_US );
    return err_flag;
}

uint8_t color11_get_interrupt ( color11_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
