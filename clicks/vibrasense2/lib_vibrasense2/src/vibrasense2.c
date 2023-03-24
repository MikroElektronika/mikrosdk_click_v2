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
 * @file vibrasense2.c
 * @brief Vibra Sense 2 Click Driver.
 */

#include "vibrasense2.h"

void vibrasense2_cfg_setup ( vibrasense2_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = VIBRASENSE2_SET_DEV_ADDR;
}

err_t vibrasense2_init ( vibrasense2_t *ctx, vibrasense2_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t vibrasense2_generic_write ( vibrasense2_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t vibrasense2_generic_read ( vibrasense2_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

uint16_t vibrasense2_read_data ( vibrasense2_t *ctx ) {
    uint8_t rx_buf[ 3 ];
    uint16_t result;

    i2c_master_read( &ctx->i2c, rx_buf, 2 );
    
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

uint16_t vibrasense2_read_voltage ( vibrasense2_t *ctx, uint16_t v_ref ) {
    float lbs_val = 0.0;
    uint16_t raw_data = 0;
    float result = 0.0;

    lbs_val = ( ( float )v_ref ) / ( ( float )VIBRASENSE2_RESOLUTION );
    raw_data = vibrasense2_read_data( ctx );
    raw_data &= VIBRASENSE2_12_BIT_DATA;

    result = ( ( float )raw_data ) * lbs_val;

    return ( uint16_t )result;
}

int8_t vibrasense2_vibration_level ( vibrasense2_t *ctx ) {
    uint16_t adc_val;

    adc_val = vibrasense2_read_data( ctx );
    
    adc_val &= 0x0FFF;

    if ( adc_val <= 468 ) {
        return VIBRASENSE2_VIBRA_LVL_0;
    } else if ( adc_val > 468 && adc_val <= 472 ) {
        return VIBRASENSE2_VIBRA_LVL_1;
    } else if ( adc_val > 472 && adc_val <= 725 ) {
        return VIBRASENSE2_VIBRA_LVL_2;
    } else if ( adc_val > 725 && adc_val <= 1450 ) {
        return VIBRASENSE2_VIBRA_LVL_3;
    } else if ( adc_val > 1450 && adc_val <= 2175 ) {
        return VIBRASENSE2_VIBRA_LVL_4;
    } else if ( adc_val > 2175 && adc_val <= 3625 ) {
        return VIBRASENSE2_VIBRA_LVL_5;
    } else if ( adc_val > 3625 ) {
        return VIBRASENSE2_VIBRA_LVL_6;
    } else {
        return VIBRASENSE2_VIBRA_LVL_ERROR;
    }
}

// ------------------------------------------------------------------------- END
