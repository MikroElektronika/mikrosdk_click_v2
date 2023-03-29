/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "uv4.h"
// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void uv4_cfg_setup ( uv4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x55;
    cfg->dev_tmp = 0;
}

UV4_RETVAL uv4_init ( uv4_t *ctx, uv4_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return UV4_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    ctx->tmp = cfg->dev_tmp;

    return UV4_OK;
}

void uv4_default_cfg ( uv4_t* ctx )
{
    uv4_write_reg( ctx, UV4_COMMAND_REG, UV4_RESET_CTR_CMD );
    uv4_write_param_data( ctx, UV4_CHAN_LIST_PARAM, UV4_CHAN0_ENABLE | 
                               UV4_CHAN1_ENABLE | 
                               UV4_CHAN4_ENABLE );
    uv4_write_param_data( ctx, UV4_ADCPOST_0_PARAM, UV4_24BIT_OUT );
    uv4_write_param_data( ctx, UV4_ADCPOST_1_PARAM, UV4_24BIT_OUT );
    uv4_write_param_data( ctx, UV4_ADCPOST_4_PARAM, UV4_16BIT_OUT );
    uv4_write_param_data( ctx, UV4_MEASCONFIG_0_PARAM, UV4_MEASCOUNT1_SELECT );
    uv4_write_param_data( ctx, UV4_MEASCONFIG_1_PARAM, UV4_MEASCOUNT1_SELECT );
    uv4_write_param_data( ctx, UV4_MEASCONFIG_4_PARAM, UV4_MEASCOUNT1_SELECT );
    uv4_write_param_data( ctx, UV4_ADCCONFIG_0_PARAM, UV4_OPT_FUNC_WHITE );
    uv4_write_param_data( ctx, UV4_ADCCONFIG_1_PARAM, UV4_OPT_FUNC_SMALL_IR );
    uv4_write_param_data( ctx, UV4_ADCCONFIG_4_PARAM, UV4_OPT_FUNC_UV );
    uv4_write_param_data( ctx, UV4_BURST_PARAM, UV4_BURST_DISABLE );
    uv4_write_param_data( ctx, UV4_MEASRATE_H_PARAM, 0 );
    uv4_write_param_data( ctx, UV4_MEASRATE_L_PARAM, 0 );
    uv4_write_param_data( ctx, UV4_MEASCOUNT_1_PARAM, 0 );
}


UV4_RETVAL uv4_write_reg ( uv4_t* ctx, const uint8_t reg_address, const uint8_t transfer_data )
{
    uint8_t data_in[ 2 ] = { 0 };

    if ( reg_address > 0x2C )
    {
        return UV4_ADDR_ERR;
    }

    data_in[ 0 ] = reg_address | 0x40;
    data_in[ 1 ] = transfer_data;

    i2c_master_write( &ctx->i2c, data_in, 2 );   

    return UV4_OK;
}

UV4_RETVAL uv4_read_reg ( uv4_t* ctx,  uint8_t reg_address, uint8_t* data_out,
                          uint8_t n_bytes )
{
    uint8_t data_in[ 1 ] = { 0 };

    if ( reg_address > 0x2C )
    {
        return UV4_ADDR_ERR;
    }
    if ( ( ctx->inc_en != 0x40 ) && ( ctx->inc_en != 0x00 ) )
    {
        return UV4_PARAM_ERR;
    }

    data_in[ 0 ] = reg_address | ctx->inc_en;

    i2c_master_write_then_read( &ctx->i2c, data_in, 1, data_out, n_bytes );

    return UV4_OK;
}

UV4_RETVAL uv4_write_param_data ( uv4_t* ctx, uint8_t param_address, uint8_t transfer_data )
{
    UV4_RETVAL err_check;
    uint8_t cnt;
    uint8_t cnt_inc;

    if ( param_address > 0x3F )
    {
        return UV4_ADDR_ERR;
    }
    switch ( param_address )
    {
        case 0x01:
        {
            transfer_data &= 0x3F;
            ctx->config_byte = transfer_data;
            break;
        }
        case 0x04:
        {
            ctx->bit_size[ 0 ] = transfer_data & 0x40;
            ctx->bit_size[ 0 ] >>= 6;
            break;
        }
        case 0x08: 
        {
            ctx->bit_size[ 1 ] = transfer_data & 0x40;
            ctx->bit_size[ 1 ] >>= 6;
            break;
        }
        case 0x0C:
        {
            ctx->bit_size[ 2 ] = transfer_data & 0x40;
            ctx->bit_size[ 2 ] >>= 6;
            break;
        }
        case 0x10:
        {
            ctx->bit_size[ 3 ] = transfer_data & 0x40;
            ctx->bit_size[ 3 ] >>= 6;
            break;
        }
        case 0x14:
        {
            ctx->bit_size[ 4 ] = transfer_data & 0x40;
            ctx->bit_size[ 4 ] >>= 6;
            break;
        }
        case 0x18:
        {
            ctx->bit_size[ 5 ] = transfer_data & 0x40;
            ctx->bit_size[ 5 ] >>= 6;
            break;
        }
        case 0x02:
        {
            ctx->optical_data[ 0 ] = transfer_data & 0x1F;
            break;
        }
        case 0x06:
        {
            ctx->optical_data[ 1 ] = transfer_data & 0x1F;
            break;
        }
        case 0x0A:
        {
            ctx->optical_data[ 2 ] = transfer_data & 0x1F;
            break;
        }
        case 0x0E:
        {
            ctx->optical_data[ 3 ] = transfer_data & 0x1F;
            break;
        }
        case 0x12:
        {
            ctx->optical_data[ 4 ] = transfer_data & 0x1F;
            break;
        }
        case 0x16:
        {
            ctx->optical_data[ 5 ] = transfer_data & 0x1F;
            break;
        }
        default:
        {
            break;
        }
    }
    err_check = uv4_check_err_and_ctr( ctx, &cnt );
    if ( err_check )
    {
        return err_check;
    }
    uv4_write_reg( ctx, UV4_INPUT_0_REG, transfer_data );
    param_address |= 0x80;
    uv4_write_reg( ctx, UV4_COMMAND_REG, param_address );
    err_check = uv4_check_err_and_ctr( ctx, &cnt_inc );
    if ( err_check )
    {
        return err_check;
    }
    while ( cnt_inc == cnt )
    {
        uv4_check_err_and_ctr( ctx, &cnt_inc );
    }
    return UV4_OK;
}

UV4_RETVAL uv4_read_param_data ( uv4_t* ctx, uint8_t param_address, uint8_t* param_out )
{
    UV4_RETVAL err_check;
    uint8_t cnt;
    uint8_t cnt_inc;

    if ( param_address > 0x3F )
    {
        return UV4_ADDR_ERR;
    }
    err_check = uv4_check_err_and_ctr( ctx, &cnt );
    if ( err_check )
    {
        return err_check;
    }
    param_address |= 0x40;
    uv4_write_reg( ctx, UV4_COMMAND_REG, param_address );
    err_check = uv4_check_err_and_ctr( ctx, &cnt_inc );
    if ( err_check )
    {
        return err_check;
    }
    while ( cnt_inc == cnt )
    {
        uv4_check_err_and_ctr( ctx, &cnt_inc );
    }
    ctx->inc_en = UV4_AUTOINC_DISABLE;
    uv4_read_reg( ctx, UV4_RESPONSE_1_REG, param_out, 1 );
    return UV4_OK;
}

void uv4_read_measurements ( uv4_t* ctx, uint32_t* measure_out )
{
    uint8_t interr_status = 0;
    uint8_t cnt;
    uint8_t pom = 1;
    uint8_t temp_addr[ 8 ] = { 0 };
    uint8_t temp_addr0 = 0x13;
    uint8_t buff_data[ 3 ];
    uint32_t temp = 0;

    if ( ctx->tmp != ctx->config_byte )
    {
        uv4_write_reg( ctx, UV4_IRQ_ENABLE_REG, ctx->config_byte );
        ctx->tmp = ctx->config_byte;
    }
    uv4_write_reg( ctx, UV4_COMMAND_REG, UV4_START_CMD );
    ctx->inc_en = UV4_AUTOINC_DISABLE;
    uv4_read_reg( ctx, UV4_IRQ_STATUS_REG, &interr_status,  1 );
    while ( !interr_status )
    {
        ctx->inc_en = UV4_AUTOINC_DISABLE;
        uv4_read_reg( ctx, UV4_IRQ_STATUS_REG, &interr_status,  1 );
    }
    uv4_write_reg( ctx, UV4_COMMAND_REG, UV4_PAUSE_CMD );
    for ( cnt = 0; cnt < 6; cnt++ )
    {
        if ( ctx->config_byte & pom )
        {
            if ( ctx->bit_size[ cnt ] )
            {
                temp_addr[ cnt ] = temp_addr0;
                temp_addr0 += 3;
            }
            else
            {
                temp_addr[ cnt ] = temp_addr0;
                temp_addr0 += 2;
            }
        }
        pom <<= 1;
    }
    pom = 1;
    for ( cnt = 0; cnt < 6; cnt++ )
    {
        if ( interr_status & pom )
        {
            if ( ctx->bit_size[ cnt ] )
            {
                ctx->inc_en = UV4_AUTOINC_ENABLE;
                uv4_read_reg( ctx, temp_addr[ cnt ], buff_data, 3 );
                temp = buff_data[ 0 ];
                temp <<= 8;
                temp |= buff_data[ 1 ];
                temp <<= 8;
                temp |= buff_data[ 2 ];
            }
            else
            {
                ctx->inc_en = UV4_AUTOINC_ENABLE;
                uv4_read_reg( ctx, temp_addr[ cnt ], buff_data, 2 );
                temp = buff_data[ 0 ];
                temp <<= 8;
                temp |= buff_data[ 1 ];
            }
            measure_out[ cnt ] = temp;
            temp = 0;
        }
        pom <<= 1;
    }
}

UV4_RETVAL uv4_check_err_and_ctr ( uv4_t *ctx, uint8_t* cnt_data )
{
    uint8_t response;
    uint8_t cmmnd_err;
    uint8_t cmmnd_ctr;

    ctx->inc_en = UV4_AUTOINC_DISABLE;
    uv4_read_reg( ctx, UV4_RESPONSE_0_REG, &response,  1 );
    cmmnd_err = response & 0x10;
    cmmnd_ctr = response & 0x0F;
    if ( cmmnd_err )
    {
        switch ( cmmnd_ctr )
        {
            case 0x00:
            {
                return UV4_CMMND_ERR;
                break;
            }
            case 0x01:
            {
                return UV4_LOC_ERR;
                break;
            }
            case 0x02:
            {
                return UV4_ACCM_OVERFLOW;
                break;
            }
            case 0x03: 
            {
                return UV4_BUFF_OVERFLOW;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    else if ( cmmnd_ctr == 0x0F )
        return UV4_RST_OCCURED;
    else
    {
        *cnt_data = cmmnd_ctr;
        return UV4_OK;
    }
}

UV4_RETVAL uv4_check_interr ( uv4_t* ctx )
{
    if ( digital_in_read( &ctx->int_pin ) )
        return UV4_INTERR_OCCURED;
    else
        return UV4_NO_INTERR;
}

// ------------------------------------------------------------------------- END

