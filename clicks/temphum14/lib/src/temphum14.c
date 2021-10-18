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
 * @file temphum14.c
 * @brief Temp Hum 14 Click Driver.
 */

#include "temphum14.h"

void temphum14_cfg_setup ( temphum14_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM14_I2C_SLAVE_ADDR_GND;
}

err_t temphum14_init ( temphum14_t *ctx, temphum14_cfg_t *cfg ) {
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

    digital_out_init( &ctx->rst, cfg->rst );

    return I2C_MASTER_SUCCESS;
}

err_t temphum14_generic_write ( temphum14_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t temphum14_generic_read ( temphum14_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void temphum14_hw_reset ( temphum14_t *ctx ) {
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
}

void temphum14_set_cmd ( temphum14_t *ctx, uint8_t cmd ) {
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = cmd;

    i2c_master_write( &ctx->i2c, tx_buf, 1 );
}

void temphum14_set_conversion ( temphum14_t *ctx, uint8_t hum_osr, uint8_t temp_osr ) {
    uint8_t tmp;
    
    hum_osr &= TEMPHUM14_BIT_MASK_HUM_OSR;
    temp_osr &= TEMPHUM14_BIT_MASK_TEMP_OSR;
    
    tmp = TEMPHUM14_CMD_CONVERSION;
    tmp |= hum_osr;
    tmp |= temp_osr;

    temphum14_set_cmd( ctx, tmp );
}

void temphum14_read_t_and_rh ( temphum14_t *ctx, uint8_t *p_rx_data ) {
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = TEMPHUM14_CMD_READ_T_AND_RH;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, p_rx_data, 6 );
}

void temphum14_get_temp_and_hum ( temphum14_t *ctx, float *temp, float *hum ) {
    uint8_t rx_buf[ 6 ];
    uint16_t tmp;
    float temperature;
    float humidity;
    
     uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = TEMPHUM14_CMD_READ_T_AND_RH;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 6 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    
    temperature = ( float ) tmp;
    temperature /= TEMPHUM14_CALC_16_BIT_DIVIDER;
    temperature *= TEMPHUM14_CALC_TEMP_MULTI_FACT;
    temperature -= TEMPHUM14_CALC_TEMP_SUB_FACT;
    
    *temp = temperature;
    
    tmp = rx_buf[ 3 ];
    tmp <<= 8;
    tmp |= rx_buf[ 4 ];
    
    humidity = ( float ) tmp;
    humidity /= TEMPHUM14_CALC_16_BIT_DIVIDER;
    humidity *= TEMPHUM14_CALC_HUM_MULTI_FACT;
    
    *hum = humidity;
}

void temphum14_read_rh ( temphum14_t *ctx, uint8_t *p_rx_data ) {
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = TEMPHUM14_CMD_READ_RH;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, p_rx_data, 4 );
}

float temphum14_get_hum ( temphum14_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 4 ];
    uint16_t tmp;
    float humidity;

    tx_buf[ 0 ] = TEMPHUM14_CMD_READ_RH;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 4 );
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    
    humidity = ( float ) tmp;
    humidity /= TEMPHUM14_CALC_16_BIT_DIVIDER;
    humidity *= TEMPHUM14_CALC_HUM_MULTI_FACT;
    
    return humidity;
}

void temphum14_soft_reset ( temphum14_t *ctx ) {
    temphum14_set_cmd( ctx, TEMPHUM14_CMD_RESET );
}

void temphum14_set_heater ( temphum14_t *ctx, uint8_t en_heater ) {
    if ( en_heater == TEMPHUM14_HEATER_ENABLE ) {
        temphum14_set_cmd( ctx, TEMPHUM14_CMD_HEATER_ON );
    } else {
        temphum14_set_cmd( ctx, TEMPHUM14_CMD_HEATER_OFF );
    }
}

void temphum14_get_diagnostic ( temphum14_t *ctx, temphum14_diagn_t *diag_data ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];

    tx_buf[ 0 ] = TEMPHUM14_CMD_READ_DIAGNOSTIC;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 1 );
    
    diag_data->nvm_error    = ( rx_buf[ 0 ] & 0x80 ) >> 7;
    diag_data->hum_un_over  = ( rx_buf[ 0 ] & 0x40 ) >> 6;
    diag_data->hum_h_err    = ( rx_buf[ 0 ] & 0x20 ) >> 5;
    diag_data->hum_l_err    = ( rx_buf[ 0 ] & 0x10 ) >> 4;
    diag_data->temp_un_over = ( rx_buf[ 0 ] & 0x08 ) >> 3;
    diag_data->temp_h_err   = ( rx_buf[ 0 ] & 0x04 ) >> 2;
    diag_data->temp_l_err   = ( rx_buf[ 0 ] & 0x02 ) >> 1;
    diag_data->heater_on    = rx_buf[ 0 ] & 0x01;
}

uint32_t temphum14_get_serial_number ( temphum14_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 6 ];
    uint32_t ser_numb;

    tx_buf[ 0 ] = TEMPHUM14_CMD_READ_SERIAL_NUMBER;

    i2c_master_write( &ctx->i2c, tx_buf, 1 );
    i2c_master_read( &ctx->i2c, rx_buf, 6 );
    
    ser_numb = rx_buf[ 0 ];
    ser_numb <<= 8;
    ser_numb |= rx_buf[ 2 ];
    ser_numb <<= 8;
    ser_numb |= rx_buf[ 4 ];
    
    return ser_numb;
}
// ------------------------------------------------------------------------- END
