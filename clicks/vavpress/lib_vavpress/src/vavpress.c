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
 * @file vavpress.c
 * @brief VAV Press Click Driver.
 */

#include "vavpress.h"

void vavpress_cfg_setup ( vavpress_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = VAVPRESS_SET_DEV_ADDR_0;
}

err_t vavpress_init ( vavpress_t *ctx, vavpress_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t vavpress_default_cfg ( vavpress_t *ctx ) {
    // Click default configuration.
    vavpress_sensor_param_data_t param_data;
    
    param_data.scale_factor_temp = 72;
    param_data.scale_factor_press = 1200;
    param_data.readout_at_known_temperature = 50;
    param_data.known_temperature_c = 24.0;
    
    vavpress_set_default_sensor_param( ctx, &param_data );
    return VAVPRESS_OK;
}

err_t vavpress_set_command ( vavpress_t *ctx, uint8_t cmd ) {
    return i2c_master_write( &ctx->i2c, &cmd, 1 );
}

err_t vavpress_generic_write ( vavpress_t *ctx, uint8_t *tx_buf, uint8_t tx_len ) {
    return i2c_master_write( &ctx->i2c, tx_buf, tx_len );
}

err_t vavpress_generic_read ( vavpress_t *ctx, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_read( &ctx->i2c, rx_buf, rx_len );
}

err_t vavpress_set_default_sensor_param ( vavpress_t *ctx, vavpress_sensor_param_data_t *param_data ) {
    vavpress_el_signature_data_t el_signature_data;
     
    err_t error_flag = vavpress_retrieve_electronic_signature( ctx, &el_signature_data );
    
    param_data->scale_factor_temp = 72;
    param_data->scale_factor_press = el_signature_data.scale_factor;
    param_data->readout_at_known_temperature = 105;
    param_data->known_temperature_c = 23.1;
    
    return error_flag;
}

err_t vavpress_get_readout_data ( vavpress_t *ctx, int16_t *press_data, int16_t *temp_data ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 4 ];
    int16_t tmp;

    tx_buf[ 0 ] = VAVPRESS_SET_CMD_START_PRESSURE_CONVERSION;

    err_t error_flag = i2c_master_write( &ctx->i2c, tx_buf, 1 );
    Delay_100ms ( );
    error_flag |= i2c_master_read( &ctx->i2c, rx_buf, 4 );
    
    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 0 ];
    
    *press_data = tmp;
    
    tmp = rx_buf[ 3 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];
    
    *temp_data = tmp;

    return error_flag;
}

err_t vavpress_get_dif_press_and_temp ( vavpress_t *ctx, vavpress_sensor_param_data_t *param_data, float *diff_press, float *temperature ) {
    int16_t press_data;
    int16_t temp_data;
    float tmp;

    err_t error_flag = vavpress_get_readout_data ( ctx, &press_data, &temp_data );
    
    tmp = ( float ) press_data;
    tmp /= ( float ) param_data->scale_factor_press;
    *diff_press = tmp;
    
    tmp = ( float ) temp_data;
    tmp -= ( float ) param_data->readout_at_known_temperature;
    tmp /= ( float ) param_data->scale_factor_temp;
    tmp += param_data->known_temperature_c; 
    *temperature = tmp;

    return error_flag;
}

err_t vavpress_retrieve_electronic_signature ( vavpress_t *ctx, vavpress_el_signature_data_t *el_signature_data ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 54 ];
    uint16_t tmp;
    float tmp_f;

    tx_buf[ 0 ] = VAVPRESS_SET_CMD_RETRIEVE_ELECTRONIC_SIGNATURE;

    err_t error_flag = i2c_master_write( &ctx->i2c, tx_buf, 1 );
    error_flag |= i2c_master_read( &ctx->i2c, rx_buf, 54 );
    
    if ( rx_buf[ 1 ] < 10 ) {
        tmp_f = ( float ) rx_buf[ 0 ] + ( ( float ) rx_buf[ 1 ] / 10 );
    } else if ( rx_buf[ 1 ] < 100 ) {
        tmp_f = ( float ) rx_buf[ 0 ] + ( ( float ) rx_buf[ 1 ] / 100 );    
    } else {
        tmp_f = ( float ) rx_buf[ 0 ] + ( ( float ) rx_buf[ 1 ] / 1000 );    
    }
    el_signature_data->firmware_version = tmp_f;
    
    for ( uint8_t n_cnt = 0; n_cnt < 11; n_cnt++ ) {
        el_signature_data->part_number[ n_cnt ] = rx_buf[ n_cnt + 2 ];    
    }
    
    for ( uint8_t n_cnt = 0; n_cnt < 7; n_cnt++ ) {
        el_signature_data->lot_number[ n_cnt ] = rx_buf[ n_cnt + 13 ];    
    }
     
    tmp = rx_buf[ 20 ];
    tmp <<= 8;
    tmp |= rx_buf[ 21 ];
    el_signature_data->pressure_range = tmp;
    
    el_signature_data->output_type = rx_buf[ 22 ];
    
    tmp = rx_buf[ 23 ];
    tmp <<= 8;
    tmp |= rx_buf[ 24 ];
    el_signature_data->scale_factor = tmp;
    
    el_signature_data->calibration_id[ 0 ] = rx_buf[ 25 ];
    el_signature_data->calibration_id[ 1 ] = rx_buf[ 26 ];
    
    el_signature_data->week_number = rx_buf[ 27 ];
    
    el_signature_data->year_number = rx_buf[ 28 ];
    
    tmp = rx_buf[ 29 ];
    tmp <<= 8;
    tmp |= rx_buf[ 30 ];
    el_signature_data->sequence_number = tmp;

    return error_flag;
}

// ------------------------------------------------------------------------- END
