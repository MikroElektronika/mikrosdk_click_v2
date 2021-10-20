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
 * @file color13.c
 * @brief Color 13 Click Driver.
 */

#include "color13.h"

/**
 * @brief Color 13 configuration object.
 * @details Configuration object of Color 13 Click driver.
 */
typedef struct
{
    uint8_t gain;
    uint8_t res;
    uint8_t integration_time;
    float lux_res;
} color13_resolution_t;

/**
 * @brief List of configuration parameters and corresponding resolutions.
 * @details Device configuraiton and corresponding resolutions for them.
 */
const color13_resolution_t color_lux[ 25 ] = 
{
    { /*1*/0, /*16*/4, 25,  2.193 },
    { /*1*/0, /*17*/3, 50,  1.099 },
    { /*1*/0, /*18*/2, 100, 0.548 },
    { /*1*/0, /*19*/1, 200, 0.273 },
    { /*1*/0, /*20*/0, 400, 0.136 },
    
    { /*3*/1, /*16*/4, 25,  0.722 },
    { /*3*/1, /*17*/3, 50,  0.359 },
    { /*3*/1, /*18*/2, 100, 0.18 },
    { /*3*/1, /*19*/1, 200, 0.09 },
    { /*3*/1, /*20*/0, 400, 0.045 },
    
    { /*6*/2, /*16*/4, 25,  0.360 },
    { /*6*/2, /*17*/3, 50,  0.179 },
    { /*6*/2, /*18*/2, 100, 0.09 },
    { /*6*/2, /*19*/1, 200, 0.045 },
    { /*6*/2, /*20*/0, 400, 0.022 },
    
    { /*9*/3, /*16*/4, 25,  0.239 },
    { /*9*/3, /*17*/3, 50,  0.119 },
    { /*9*/3, /*18*/2, 100, 0.059 },
    { /*9*/3, /*19*/1, 200, 0.03 },
    { /*9*/3, /*20*/0, 400, 0.015 },
    
    { /*18*/4, /*16*/4, 25,  0.117 },
    { /*18*/4, /*17*/3, 50,  0.059 },
    { /*18*/4, /*18*/2, 100, 0.029 },
    { /*18*/4, /*19*/1, 200, 0.015 },
    { /*18*/4, /*20*/0, 400, 0.007 }
};


void color13_cfg_setup ( color13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COLOR13_SET_DEV_ADDR;
}

err_t color13_init ( color13_t *ctx, color13_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_timeout( &ctx->i2c, 0 ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t color13_generic_write ( color13_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 38 ] = { 0 };
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t color13_generic_read ( color13_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

uint8_t color13_get_int ( color13_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t color13_get_proximity ( color13_t *ctx, uint16_t *ps_data )
{
    uint8_t temp_buf[ 2 ] = { 0 };
    uint16_t temp_data = 0;
    
    *ps_data = 0;
    
    err_t error_flag = color13_generic_read( ctx, COLOR13_REG_MAIN_CTRL, temp_buf, 1 );
    
    if ( !( temp_buf[ 0 ] & 1 ) )
    {
        error_flag = COLOR13_ERROR_CFG;
    }
    
    if ( !error_flag )
    {
        error_flag = color13_generic_read( ctx, COLOR13_REG_PS_DATA_0, temp_buf, 2 );

        temp_data = ( ( uint16_t )temp_buf[ 1 ] << 8 ) | temp_buf[ 0 ];
        
        *ps_data = temp_data & 0x07FF;
        
        if ( temp_data & 0x0800 )
        {
            error_flag = COLOR13_ERROR_OVF;
        }
    }
    
    return error_flag;
}

err_t color13_ls_color ( color13_t *ctx, uint8_t ls_reg, uint32_t *ls_data )
{
    uint32_t temp_data = 0;
    uint8_t ls_buf[ 3 ] = { 0 };
    err_t error_flag = COLOR13_OK;
    
    *ls_data = 0;
    
    if ( ( COLOR13_REG_LS_DATA_RED_0 != ls_reg ) && 
         ( COLOR13_REG_LS_DATA_GREEN_0 != ls_reg ) && 
         ( COLOR13_REG_LS_DATA_BLUE_0 != ls_reg ) && 
         ( COLOR13_REG_LS_DATA_IR_0 != ls_reg ) )
    {
        error_flag = COLOR13_ERROR_PARAM;
    }
    
    if ( !error_flag )
    {
        error_flag = color13_generic_read( ctx, ls_reg, ls_buf, 3 );
        
        if ( !error_flag )
        {
            temp_data = ( ( uint32_t )ls_buf[ 2 ] << 16 ) | 
                        ( ( uint32_t )ls_buf[ 1 ] << 8 ) | ls_buf[ 0 ];
            *ls_data = temp_data & 0x000FFFFF;
        }
    }

    return error_flag;
}

err_t color13_get_rgb_ir ( color13_t *ctx, color13_color_t *color_data )
{
    err_t error_flag = COLOR13_OK;
    uint32_t ls_data = 0;
    
    //Red
    error_flag |= color13_ls_color( ctx, COLOR13_REG_LS_DATA_RED_0, &ls_data );
    color_data->red = ls_data;
    //Green
    error_flag |= color13_ls_color( ctx, COLOR13_REG_LS_DATA_GREEN_0, &ls_data );
    color_data->green = ls_data;
    //Blue
    error_flag |= color13_ls_color( ctx, COLOR13_REG_LS_DATA_BLUE_0, &ls_data );
    color_data->blue = ls_data;
    //IR
    error_flag |= color13_ls_color( ctx, COLOR13_REG_LS_DATA_IR_0, &ls_data );
    color_data->ir = ls_data;
    
    return error_flag;
}

err_t color13_get_als ( color13_t *ctx, float *als_data )
{
    err_t error_flag = COLOR13_OK;
    uint32_t ls_data = 0;
    static uint8_t resolution = 0;
    uint8_t temp_data;
    
    if ( 0 == resolution )
    {
        resolution = 1;
        color13_get_als_resolution( ctx );
    }
    
    color13_ls_color( ctx, COLOR13_REG_LS_DATA_GREEN_0, &ls_data );
    *als_data = ls_data * ctx->lux_resolution;
    
    return error_flag;
}

float color13_get_als_resolution ( color13_t *ctx )
{
    float res = 0;
    uint8_t gain;
    uint8_t resolution;
    uint8_t temp_data;
    
    color13_generic_read( ctx, COLOR13_REG_LS_GAIN, &gain, 1 );
    gain &= 0x7;
    color13_generic_read( ctx, COLOR13_REG_LS_MEAS_RATE, &temp_data, 1 );
    resolution = ( temp_data & 0x70 ) >> 4;
    
    for ( uint8_t cnt = 0; cnt < 25; cnt += 5 )
    {
        if ( color_lux[cnt].gain == gain )
        {
            for ( uint8_t limit = cnt + 5; cnt < limit; cnt++ )
            {
                if ( color_lux[cnt].res == resolution )
                {
                    res = color_lux[cnt].lux_res;
                    break;
                }
            }
            if ( 0 != res )
            {
                break;
            }
        }
    }
    
    ctx->lux_resolution = res;
    
    return res;
}

// ------------------------------------------------------------------------- END
