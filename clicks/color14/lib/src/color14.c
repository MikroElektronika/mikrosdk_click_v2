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
 * @file color14.c
 * @brief Color 14 Click Driver.
 */

#include "color14.h"

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
} color14_resolution_t;

/**
 * @brief List of configuration parameters and corresponding resolutions.
 * @details Device configuraiton and corresponding resolutions for them.
 */
const color14_resolution_t color_lux[ 30 ] = 
{
    { /*1 gain*/0, /*13 bits*/5, /*delay ms*/3.125,  /*resolution*/28.8288 },
    { /*1 gain*/0, /*16 bits*/4, /*delay ms*/25   ,  /*resolution*/3.6036 },
    { /*1 gain*/0, /*17 bits*/3, /*delay ms*/50   ,  /*resolution*/1.8018 },
    { /*1 gain*/0, /*18 bits*/2, /*delay ms*/100  ,  /*resolution*/0.9009 },
    { /*1 gain*/0, /*19 bits*/1, /*delay ms*/200  ,  /*resolution*/0.4505 },
    { /*1 gain*/0, /*20 bits*/0, /*delay ms*/400  ,  /*resolution*/0.2252 },
    
    { /*3 gain*/1, /*13 bits*/5, /*delay ms*/3.125,  /*resolution*/9.4675 },
    { /*3 gain*/1, /*16 bits*/4, /*delay ms*/25   ,  /*resolution*/1.1834 },
    { /*3 gain*/1, /*17 bits*/3, /*delay ms*/50   ,  /*resolution*/0.5917 },
    { /*3 gain*/1, /*18 bits*/2, /*delay ms*/100  ,  /*resolution*/0.2959 },
    { /*3 gain*/1, /*19 bits*/1, /*delay ms*/200  ,  /*resolution*/0.1479 },
    { /*3 gain*/1, /*20 bits*/0, /*delay ms*/400  ,  /*resolution*/0.0740 },
    
    { /*6 gain*/2, /*13 bits*/5, /*delay ms*/3.125,  /*resolution*/4.7267 },
    { /*6 gain*/2, /*16 bits*/4, /*delay ms*/25   ,  /*resolution*/0.5908 },
    { /*6 gain*/2, /*17 bits*/3, /*delay ms*/50   ,  /*resolution*/0.2954 },
    { /*6 gain*/2, /*18 bits*/2, /*delay ms*/100  ,  /*resolution*/0.1477 },
    { /*6 gain*/2, /*19 bits*/1, /*delay ms*/200  ,  /*resolution*/0.0739 },
    { /*6 gain*/2, /*20 bits*/0, /*delay ms*/400  ,  /*resolution*/0.0369 },
    
    { /*9 gain*/3, /*13 bits*/5, /*delay ms*/3.125,  /*resolution*/3.1189 },
    { /*9 gain*/3, /*16 bits*/4, /*delay ms*/25   ,  /*resolution*/0.3899 },
    { /*9 gain*/3, /*17 bits*/3, /*delay ms*/50   ,  /*resolution*/0.1949 },
    { /*9 gain*/3, /*18 bits*/2, /*delay ms*/100  ,  /*resolution*/0.0975 },
    { /*9 gain*/3, /*19 bits*/1, /*delay ms*/200  ,  /*resolution*/0.0487 },
    { /*9 gain*/3, /*20 bits*/0, /*delay ms*/400  ,  /*resolution*/0.0244 },
    
    { /*18 gain*/4, /*13 bits*/5, /*delay ms*/3.125, /*resolution*/1.5459 },
    { /*18 gain*/4, /*16 bits*/4, /*delay ms*/25   , /*resolution*/0.1932 },
    { /*18 gain*/4, /*17 bits*/3, /*delay ms*/50   , /*resolution*/0.0966 },
    { /*18 gain*/4, /*18 bits*/2, /*delay ms*/100  , /*resolution*/0.0483 },
    { /*18 gain*/4, /*19 bits*/1, /*delay ms*/200  , /*resolution*/0.0242 },
    { /*18 gain*/4, /*20 bits*/0, /*delay ms*/400  , /*resolution*/0.0121 }
};

void color14_cfg_setup ( color14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
   //cfg->cs   = HAL_PIN_NC;
   //cfg->an   = HAL_PIN_NC;
   //cfg->rst = HAL_PIN_NC;
   //cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COLOR14_SET_DEV_ADDR;
}

err_t color14_init ( color14_t *ctx, color14_cfg_t *cfg ) 
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

err_t color14_generic_write ( color14_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
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

err_t color14_generic_read ( color14_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

uint8_t color14_get_int ( color14_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t color14_get_proximity ( color14_t *ctx, uint16_t *ps_data )
{
    uint8_t temp_buf[ 2 ] = { 0 };
    uint16_t temp_data = 0;
    
    *ps_data = 0;
    
    err_t error_flag = color14_generic_read( ctx, COLOR14_REG_MAIN_CTRL, temp_buf, 1 );
    
    if ( !( temp_buf[ 0 ] & 1 ) )
    {
        error_flag = COLOR14_ERROR_CFG;
    }
    
    if ( !error_flag )
    {
        error_flag = color14_generic_read( ctx, COLOR14_REG_PS_DATA_0, temp_buf, 2 );

        temp_data = ( ( uint16_t )temp_buf[ 1 ] << 8 ) | temp_buf[ 0 ];
        
        *ps_data = temp_data & 0x07FF;
        
        if ( temp_data & 0x0800 )
        {
            error_flag = COLOR14_ERROR_OVF;
        }
    }
    
    return error_flag;
}

err_t color14_ls_color ( color14_t *ctx, uint8_t ls_reg, uint32_t *ls_data )
{
    uint32_t temp_data = 0;
    uint8_t ls_buf[ 3 ] = { 0 };
    err_t error_flag = COLOR14_OK;
    
    *ls_data = 0;
    
    if ( ( COLOR14_REG_LS_DATA_RED_0 != ls_reg ) && 
         ( COLOR14_REG_LS_DATA_GREEN_0 != ls_reg ) && 
         ( COLOR14_REG_LS_DATA_BLUE_0 != ls_reg ) && 
         ( COLOR14_REG_LS_DATA_IR_0 != ls_reg ) )
    {
        error_flag = COLOR14_ERROR_PARAM;
    }
    
    if ( !error_flag )
    {
        error_flag = color14_generic_read( ctx, ls_reg, ls_buf, 3 );
        
        if ( !error_flag )
        {
            temp_data = ( ( uint32_t )ls_buf[ 2 ] << 16 ) | 
                        ( ( uint32_t )ls_buf[ 1 ] << 8 ) | ls_buf[ 0 ];
            *ls_data = temp_data & 0x000FFFFF;
        }
    }

    return error_flag;
}

err_t color14_get_rgb_ir ( color14_t *ctx, color14_color_t *color_data )
{
    err_t error_flag = COLOR14_OK;
    uint32_t ls_data = 0;
    
    //Red
    error_flag |= color14_ls_color( ctx, COLOR14_REG_LS_DATA_RED_0, &ls_data );
    color_data->red = ls_data;
    //Green
    error_flag |= color14_ls_color( ctx, COLOR14_REG_LS_DATA_GREEN_0, &ls_data );
    color_data->green = ls_data;
    //Blue
    error_flag |= color14_ls_color( ctx, COLOR14_REG_LS_DATA_BLUE_0, &ls_data );
    color_data->blue = ls_data;
    //IR
    error_flag |= color14_ls_color( ctx, COLOR14_REG_LS_DATA_IR_0, &ls_data );
    color_data->ir = ls_data;
    
    return error_flag;
}

err_t color14_get_als ( color14_t *ctx, float *als_data )
{
    err_t error_flag = COLOR14_OK;
    uint32_t ls_data = 0;
    static uint8_t resolution = 0;
    uint8_t temp_data;
    
    if ( 0 == resolution )
    {
        resolution = 1;
        color14_get_als_resolution( ctx );
    }
    
    color14_ls_color( ctx, COLOR14_REG_LS_DATA_GREEN_0, &ls_data );
    *als_data = ls_data * ctx->lux_resolution;
    
    return error_flag;
}

float color14_get_als_resolution ( color14_t *ctx )
{
    float res = 0;
    uint8_t gain;
    uint8_t resolution;
    uint8_t temp_data;
    
    color14_generic_read( ctx, COLOR14_REG_LS_GAIN, &gain, 1 );
    gain &= 0x7;
    color14_generic_read( ctx, COLOR14_REG_LS_MEAS_RATE, &temp_data, 1 );
    resolution = ( temp_data & 0x70 ) >> 4;
    
    for ( uint8_t cnt = 0; cnt < 30; cnt += 6 )
    {
        if ( color_lux[cnt].gain == gain )
        {
            for ( uint8_t limit = cnt + 6; cnt < limit; cnt++ )
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
