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
 * @file bucknboost.c
 * @brief Buck n Boost Click Driver.
 */

#include "bucknboost.h"

void bucknboost_cfg_setup ( bucknboost_cfg_t *cfg ) 
{
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins

    cfg->en   = HAL_PIN_NC;
    cfg->por  = HAL_PIN_NC;
    cfg->stb  = HAL_PIN_NC;
    cfg->pg   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BUCKNBOOST_DEV_ADDR;
}

err_t bucknboost_init ( bucknboost_t *ctx, bucknboost_cfg_t *cfg ) 
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

    digital_out_init( &ctx->stb, cfg->stb );
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->por, cfg->por );
    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t bucknboost_default_cfg ( bucknboost_t *ctx ) 
{
    bucknboost_device_enable( ctx, BUCKNBOOST_ENABLE );
    Delay_100ms( );
    err_t error_check = bucknboost_reg_standby_mode ( ctx, BUCKNBOOST_WAKE_UP );
    error_check |= bucknboost_send_cmd ( ctx, BUCKNBOOST_CMD_RESET );
    Delay_100ms( );
    error_check |= bucknboost_write_byte ( ctx, BUCKNBOOST_REG_STBY_CTRL, BUCKNBOOST_NORMAL_MODE_ALL );
    error_check |= bucknboost_write_byte ( ctx, BUCKNBOOST_REG_ILIMIT_1_2, BUCKNBOOST_CURRENT_LIMIT_1100mA );
    error_check |= bucknboost_write_byte ( ctx, BUCKNBOOST_REG_ILIMIT_3_4, BUCKNBOOST_CURRENT_LIMIT_1100mA );
    error_check |= bucknboost_write_byte ( ctx, BUCKNBOOST_REG_ILIMIT_5_6, BUCKNBOOST_CURRENT_LIMIT_1100mA );
    
    error_check |= bucknboost_send_cmd ( ctx, BUCKNBOOST_CMD_SAVECONFIG );
    Delay_100ms( );
    
    error_check |= bucknboost_set_buck_out_voltage( ctx, BUCKNBOOST_OUTPUT_CH_1, 
                                                         BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1800mV );
    
    error_check |= bucknboost_set_buck_out_voltage( ctx, BUCKNBOOST_OUTPUT_CH_2, 
                                                         BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1100mV );
    
    error_check |= bucknboost_set_buck_out_voltage( ctx, BUCKNBOOST_OUTPUT_CH_3, 
                                                         BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1800mV );
    
    error_check |= bucknboost_set_buck_out_voltage( ctx, BUCKNBOOST_OUTPUT_CH_4, 
                                                         BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1050mV );
    
    error_check |= bucknboost_set_buck_out_voltage( ctx, BUCKNBOOST_OUTPUT_CH_5, 
                                                         BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1250mV );
    
    error_check |= bucknboost_set_boost_out_voltage( ctx, BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_12000mV );
    Delay_100ms( );
    
    return error_check;
}

err_t bucknboost_generic_write ( bucknboost_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) 
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t bucknboost_generic_read ( bucknboost_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t bucknboost_send_cmd ( bucknboost_t *ctx, uint8_t cmd )
{
    return i2c_master_write( &ctx->i2c, &cmd, 1 );
}

err_t bucknboost_write_byte ( bucknboost_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = data_in;

    return i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

err_t bucknboost_read_byte ( bucknboost_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void bucknboost_pin_standby_mode ( bucknboost_t *ctx, uint8_t state )
{
    if ( state == BUCKNBOOST_ENABLE )
    {
        digital_out_high( &ctx->stb );
        Delay_100ms( );
        digital_out_low( &ctx->stb );
    }
    else if ( state == BUCKNBOOST_DISABLE )
    {
        digital_out_low( &ctx->stb );
        Delay_100ms();
        digital_out_high( &ctx->stb );
    }
}

err_t bucknboost_reg_standby_mode ( bucknboost_t *ctx, uint8_t state )
{
    uint8_t aux_reg_val;

    bucknboost_pin_standby_mode( ctx, BUCKNBOOST_ENABLE );

    err_t error_check = bucknboost_read_byte( ctx, BUCKNBOOST_REG_STBY_CTRL, &aux_reg_val );

    if ( state == BUCKNBOOST_WAKE_UP )
    {
        aux_reg_val &= 0xBF;
    }
    else if ( state == BUCKNBOOST_STANDBY )
    {
        aux_reg_val |= 0x40;
    }

    error_check |= bucknboost_write_byte( ctx, BUCKNBOOST_REG_STBY_CTRL, aux_reg_val );
    
    return error_check;
}

void bucknboost_device_enable ( bucknboost_t *ctx, uint8_t state )
{
    if ( state == BUCKNBOOST_ENABLE )
    {
        digital_out_high( &ctx->en );
    }
    else if ( state == BUCKNBOOST_DISABLE )
    {
        digital_out_low( &ctx->en );
    }
}

uint8_t bucknboost_check_power_good ( bucknboost_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

uint8_t bucknboost_check_por ( bucknboost_t *ctx )
{
    return digital_in_read( &ctx->por );
}

err_t bucknboost_read_oc_fault ( bucknboost_t *ctx, uint8_t *data_out )
{
    uint8_t oc_reg;
    uint8_t stby;
    uint8_t wr_reg;
    uint8_t en_state;

    err_t error_check = bucknboost_read_byte( ctx, BUCKNBOOST_REG_FAULT, data_out );
    *data_out &= 0x3F;
    oc_reg = *data_out;
    
    if ( oc_reg )
    {
        error_check |= bucknboost_read_byte( ctx, BUCKNBOOST_REG_STBY_CTRL, &stby );
        stby &= 0x40;
        
        wr_reg = stby > 0 ? BUCKNBOOST_REG_STBY_CTRL : BUCKNBOOST_REG_EN;

        error_check |= bucknboost_read_byte( ctx, wr_reg, &en_state );
        en_state = en_state & ~oc_reg;
        error_check |= bucknboost_write_byte( ctx, wr_reg, en_state );
        error_check |= bucknboost_write_byte( ctx, BUCKNBOOST_REG_FAULT, 0x00 );
        en_state = en_state | oc_reg;
        error_check |= bucknboost_write_byte( ctx, wr_reg, en_state );
    }
    return error_check;
}

err_t bucknboost_set_buck_out_voltage ( bucknboost_t *ctx, uint8_t ch_num, uint8_t data_in )
{
    err_t error_check = BUCKNBOOST_ERROR;
    uint8_t tmp_en;

    if ( ( data_in <= BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_800mV ) && 
         ( ch_num >= BUCKNBOOST_OUTPUT_CH_1 ) && 
         ( ch_num <= BUCKNBOOST_OUTPUT_CH_5 ) )
    {
        ch_num--;
        error_check = bucknboost_read_byte( ctx, BUCKNBOOST_REG_EN, &tmp_en );
        
        error_check |= bucknboost_write_byte( ctx, BUCKNBOOST_REG_OUT1 + ch_num, data_in );
        
        tmp_en = tmp_en | ( BUCKNBOOST_ENABLE << ch_num );

        error_check |= bucknboost_write_byte( ctx, BUCKNBOOST_REG_EN, tmp_en );
    }

    return error_check;
}

err_t bucknboost_set_all_buck_out_voltage ( bucknboost_t *ctx, uint8_t data_in )
{
    err_t error_check = BUCKNBOOST_ERROR;
    uint8_t tmp_en;

    if ( data_in <= BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_800mV )
    {
        error_check = bucknboost_set_buck_out_voltage ( ctx, BUCKNBOOST_OUTPUT_CH_1, data_in );
        
        error_check |= bucknboost_set_buck_out_voltage ( ctx, BUCKNBOOST_OUTPUT_CH_2, data_in );
        
        error_check |= bucknboost_set_buck_out_voltage ( ctx, BUCKNBOOST_OUTPUT_CH_3, data_in );
        
        error_check |= bucknboost_set_buck_out_voltage ( ctx, BUCKNBOOST_OUTPUT_CH_4, data_in );
        
        error_check |= bucknboost_set_buck_out_voltage ( ctx, BUCKNBOOST_OUTPUT_CH_5, data_in );
    }

    return error_check;
}

err_t bucknboost_set_boost_out_voltage ( bucknboost_t *ctx, uint8_t data_in )
{
    uint8_t tmp_en;
    err_t error_check = BUCKNBOOST_ERROR;

    if ( data_in <= BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_7000mV )
    {
        error_check = bucknboost_read_byte( ctx, BUCKNBOOST_REG_EN, &tmp_en );
        
        error_check |= bucknboost_write_byte( ctx, BUCKNBOOST_REG_OUT6, data_in );

        error_check |= bucknboost_write_byte( ctx, BUCKNBOOST_REG_EN, tmp_en | 0x20 );  
    }

    return error_check;
}

err_t bucknboost_get_status ( bucknboost_t *ctx, bucknboost_status_t *st_data )
{
    uint8_t tmp_pg;
    uint8_t tmp_e;
    uint8_t tmp_o;

    err_t error_check = bucknboost_read_byte( ctx, BUCKNBOOST_REG_PGOOD1_6, &tmp_pg );
    error_check |= bucknboost_read_byte( ctx, BUCKNBOOST_REG_STATUS, &tmp_e );
    error_check |= bucknboost_read_byte( ctx, BUCKNBOOST_REG_FAULT, &tmp_o );

    st_data->power_good = tmp_pg & BUCKNBOOST_PGOOD_ALL_MASK;
    st_data->eeprom_status = tmp_e & BUCKNBOOST_EEPROM_ALL_MASK;
    st_data->overcurrent_fault = tmp_o & BUCKNBOOST_FAULT_ALL_MASK;

    return error_check;
}

err_t bucknboost_update_cfg_out ( bucknboost_t *ctx, uint8_t ch_num, bucknboost_cfg_buck_t b_data )
{
    uint8_t tmp_standby;
    uint8_t tmp_en;

    err_t error_check = BUCKNBOOST_ERROR;

    if ( ( ch_num >= BUCKNBOOST_OUTPUT_CH_1 ) && ( ch_num <= BUCKNBOOST_OUTPUT_CH_5 ) )
    {
        error_check = bucknboost_read_byte( ctx, BUCKNBOOST_REG_STBY_CTRL, &tmp_standby );
        error_check |= bucknboost_read_byte( ctx, BUCKNBOOST_REG_EN, &tmp_en );
        ch_num--;

        if ( b_data.out_standby == BUCKNBOOST_ENABLE )
        {
            tmp_standby &= ~( b_data.out_standby << ch_num );

            error_check |= bucknboost_write_byte( ctx, BUCKNBOOST_REG_STBY_OUT1 + ch_num, b_data.out_vol_stby_mode );
        }
        else
        {
            tmp_standby |= b_data.out_standby << ch_num;

            error_check |= bucknboost_write_byte( ctx, BUCKNBOOST_REG_OUT1 + ch_num, b_data.out_vol_normal_mode );
        }

        error_check |= bucknboost_write_byte( ctx, BUCKNBOOST_REG_STBY_CTRL, tmp_standby );

        if ( b_data.out_enable == BUCKNBOOST_ENABLE )
        {
            tmp_en |= BUCKNBOOST_ENABLE << ch_num;
        }
        else
        {
            tmp_en &= ~( BUCKNBOOST_ENABLE << ch_num );
        }

        error_check |= bucknboost_write_byte( ctx, BUCKNBOOST_REG_EN, tmp_en );
    }

    return error_check;
}

err_t bucknboost_get_power_good_status ( bucknboost_t *ctx, uint8_t *data_out )
{
    return bucknboost_read_byte( ctx, BUCKNBOOST_REG_PGOOD1_6, data_out );
}

err_t bucknboost_check_power_good_status ( bucknboost_t *ctx, uint8_t ch_num, uint8_t *data_out )
{
    err_t error_check = BUCKNBOOST_ERROR;

    if ( ( ch_num >= BUCKNBOOST_OUTPUT_CH_1 ) && ( ch_num <= BUCKNBOOST_OUTPUT_CH_5 ) )
    {
        error_check = bucknboost_get_power_good_status( ctx, data_out );

        ch_num--;
        *data_out >>= ch_num;
        *data_out &= BUCKNBOOST_ENABLE;
    }

    return error_check;
}

err_t bucknboost_get_eeprom_status ( bucknboost_t *ctx, uint8_t *data_out )
{
    return bucknboost_read_byte( ctx, BUCKNBOOST_REG_STATUS, data_out );
}

err_t bucknboost_get_overcurrent_fault_status ( bucknboost_t *ctx, uint8_t *data_out )
{
    return bucknboost_read_byte( ctx, BUCKNBOOST_REG_FAULT, data_out );
}

err_t bucknboost_check_overc_fault_status ( bucknboost_t *ctx, uint8_t ch_num, uint8_t *data_out )
{
    err_t error_check = BUCKNBOOST_ERROR;

    if ( ( ch_num >= BUCKNBOOST_OUTPUT_CH_1 ) && ( ch_num <= BUCKNBOOST_OUTPUT_CH_5 ) )
    {
        error_check = bucknboost_get_overcurrent_fault_status( ctx, data_out );
        
        ch_num--;
        *data_out >>= ch_num;
        *data_out &= BUCKNBOOST_ENABLE;
    }

    return error_check;
}


// ------------------------------------------------------------------------- END
