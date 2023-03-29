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
 * @file pac1720.c
 * @brief PAC1720 Click Driver.
 */

#include "pac1720.h"

void pac1720_cfg_setup ( pac1720_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PAC1720_SET_DEV_ADDR_SEL_0_OHM;
}

err_t pac1720_init ( pac1720_t *ctx, pac1720_cfg_t *cfg ) 
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

err_t pac1720_default_cfg ( pac1720_t *ctx ) 
{
    err_t error_flag = PAC1720_OK;
    
    if ( PAC1720_ERROR == pac1720_check_communication ( ctx ) )
    {
        return PAC1720_ERROR;
    }
    
    error_flag |= pac1720_set_vsource_config ( ctx, 
                                               PAC1720_CHANNEL_1, 
                                               PAC1720_SAMPLE_TIME_20mS, 
                                               PAC1720_AVG_4_SAMPLES );
    
    error_flag |= pac1720_set_vsource_config ( ctx, 
                                               PAC1720_CHANNEL_2, 
                                               PAC1720_SAMPLE_TIME_20mS, 
                                               PAC1720_AVG_4_SAMPLES );
    
    error_flag |= pac1720_set_vsense_config ( ctx, 
                                              PAC1720_CHANNEL_1, 
                                              PAC1720_SAMPLE_TIME_80mS, 
                                              PAC1720_AVG_DISABLE, 
                                              PAC1720_CS_RANGE_10mV );
    
    error_flag |= pac1720_set_vsense_config ( ctx, 
                                              PAC1720_CHANNEL_2, 
                                              PAC1720_SAMPLE_TIME_80mS, 
                                              PAC1720_AVG_DISABLE, 
                                              PAC1720_CS_RANGE_10mV );

    return error_flag;
}

err_t pac1720_write_block ( pac1720_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) 
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t pac1720_read_block ( pac1720_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t pac1720_write_byte ( pac1720_t *ctx, uint8_t reg, uint8_t data_in )
{
    return pac1720_write_block( ctx, reg, &data_in, 1 );
}

err_t pac1720_read_byte ( pac1720_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return pac1720_read_block ( ctx, reg, data_out, 1 );
}

err_t pac1720_set_address_pointer ( pac1720_t *ctx, uint8_t reg )
{
    return i2c_master_write( &ctx->i2c, &reg, 1 );
}

err_t pac1720_read_last_accessed_register ( pac1720_t *ctx, uint8_t *data_out )
{
    return i2c_master_read( &ctx->i2c, data_out, 1 );
}

err_t pac1720_set_slave_address ( pac1720_t *ctx, uint8_t slave_address )
{
    ctx->slave_address = slave_address;
    return i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ); 
}

uint8_t pac1720_get_int_pin ( pac1720_t *ctx )
{
    return digital_in_read ( &ctx->int_pin ); 
}

err_t pac1720_check_communication ( pac1720_t *ctx )
{
    uint8_t product_id = 0;
    
    if ( PAC1720_OK == pac1720_read_byte ( ctx, PAC1720_REG_PRODUCT_ID, &product_id ) )
    {
        if ( PAC1720_PRODUCT_ID == product_id )
        {
            return PAC1720_OK;
        }
    }
    return PAC1720_ERROR;
}

err_t pac1720_set_vsource_config ( pac1720_t *ctx, pac1720_ch_sel_t ch, 
                                   pac1720_sample_time_t stime, pac1720_avg_t avg )
{
    if ( stime > PAC1720_SAMPLE_TIME_20mS )
    {
        stime = PAC1720_SAMPLE_TIME_20mS;
    }
    uint8_t vsrc_data = 0;
    err_t error_flag = pac1720_read_byte ( ctx, PAC1720_REG_VSOURCE_CONFIG, &vsrc_data );
    
    vsrc_data &= ( ch == PAC1720_CHANNEL_1 ? 0xF0 : 0x0F );
    vsrc_data |= ( ( ( stime << 2 ) | avg ) << ( ch == PAC1720_CHANNEL_1 ? 0 : 4 ) );
    
    ctx->ch1_vsrc_cfg = vsrc_data & 0x0F;
    ctx->ch2_vsrc_cfg = ( vsrc_data & 0xF0 ) >> 4; 
    
    error_flag |= pac1720_write_byte ( ctx, PAC1720_REG_VSOURCE_CONFIG, vsrc_data );
    return error_flag;
}

err_t pac1720_set_vsense_config ( pac1720_t *ctx, pac1720_ch_sel_t ch, pac1720_sample_time_t stime, 
                                  pac1720_avg_t avg, pac1720_cs_rng_t cs_rng )
{
    uint8_t vsense_data = ( stime << 4 ) | ( avg << 2 ) | cs_rng;
    
    if ( PAC1720_CHANNEL_1 == ch )
    {
        ctx->ch1_vsense_cfg = vsense_data;
        return pac1720_write_byte ( ctx, PAC1720_REG_CH1_VSENSE_CONFIG, vsense_data );
    }
    else if ( PAC1720_CHANNEL_2 == ch )
    {
        ctx->ch2_vsense_cfg = vsense_data;
        return pac1720_write_byte ( ctx, PAC1720_REG_CH2_VSENSE_CONFIG, vsense_data );
    }
    else
    {
        return PAC1720_ERROR;
    }
}

err_t pac1720_get_measurements ( pac1720_t *ctx, pac1720_ch_sel_t ch, 
                                 float *voltage, float *current, float *power )
{
    err_t error_flag = PAC1720_OK;
    if ( PAC1720_CHANNEL_1 == ch )
    {
        uint8_t rx_buf[ 2 ] = { 0 };
        
        // voltage calculation
        uint8_t vsrc_stime = ctx->ch1_vsrc_cfg >> 2;
        uint16_t vsrc_den = ( 256 << vsrc_stime ) - 1;
        float fsv = PAC1720_MAX_VOLTAGE - PAC1720_MAX_VOLTAGE / ( vsrc_den + 1 );
        error_flag |= pac1720_read_block ( ctx, PAC1720_REG_CH1_VSOURCE_HIGH_BYTE, rx_buf, 2 );
        uint16_t vsrc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ] ) >> ( 8 - vsrc_stime );
        *voltage = fsv * ( ( float ) vsrc / vsrc_den );
        
        // current calculation
        uint8_t vsense_stime = ( ( ctx->ch1_vsense_cfg >> 4 ) < 5 ) ? ( ctx->ch1_vsense_cfg >> 4 ) : 5;
        uint16_t vsense_den = ( ( uint16_t ) 64 << vsense_stime ) - 1;
        float fsr = PAC1720_CURRENT_SENSE_RANGE_V * ( 1 << ( ctx->ch1_vsense_cfg & 0x03 ) );
        float fsc = fsr / PAC1720_RSENSE_OHM;
        error_flag |= pac1720_read_block ( ctx, PAC1720_REG_CH1_VSENSE_HIGH_BYTE, rx_buf, 2 );
        int16_t vsense = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ]; 
        vsense >>= ( 9 - vsense_stime );
        *current = fsc * ( ( float ) vsense / vsense_den );
        
        // power calculation
        float fsp = fsc * fsv;
        error_flag |= pac1720_read_block ( ctx, PAC1720_REG_CH1_POWER_RATIO_HIGH_BYTE, rx_buf, 2 );
        uint16_t pratio = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
        *power = fsp * ( ( float ) pratio / PAC1720_POWER_RATIO_RESOLUTION );
    }
    else if ( PAC1720_CHANNEL_2 == ch )
    {
        uint8_t rx_buf[ 2 ] = { 0 };
        
        // voltage calculation
        uint8_t vsrc_stime = ctx->ch2_vsrc_cfg >> 2;
        uint16_t vsrc_den = ( 256 << vsrc_stime ) - 1;
        float fsv = PAC1720_MAX_VOLTAGE - PAC1720_MAX_VOLTAGE / ( vsrc_den + 1 );
        error_flag |= pac1720_read_block ( ctx, PAC1720_REG_CH2_VSOURCE_HIGH_BYTE, rx_buf, 2 );
        uint16_t vsrc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ] ) >> ( 8 - vsrc_stime );
        *voltage = fsv * ( ( float ) vsrc / vsrc_den );
        
        // current calculation
        uint8_t vsense_stime = ( ( ctx->ch2_vsense_cfg >> 4 ) < 5 ) ? ( ctx->ch2_vsense_cfg >> 4 ) : 5;
        uint16_t vsense_den = ( ( uint16_t ) 64 << vsense_stime ) - 1;
        float fsr = PAC1720_CURRENT_SENSE_RANGE_V * ( 1 << ( ctx->ch2_vsense_cfg & 0x03 ) );
        float fsc = fsr / PAC1720_RSENSE_OHM;
        error_flag |= pac1720_read_block ( ctx, PAC1720_REG_CH2_VSENSE_HIGH_BYTE, rx_buf, 2 );
        int16_t vsense = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ]; 
        vsense >>= ( 9 - vsense_stime );
        *current = fsc * ( ( float ) vsense / vsense_den );
        
        // power calculation
        float fsp = fsc * fsv;
        error_flag |= pac1720_read_block ( ctx, PAC1720_REG_CH2_POWER_RATIO_HIGH_BYTE, rx_buf, 2 );
        uint16_t pratio = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
        *power = fsp * ( ( float ) pratio / PAC1720_POWER_RATIO_RESOLUTION );
    }
    else
    {
        error_flag = PAC1720_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
