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
 * @file force5.c
 * @brief Force 5 Click Driver.
 */

#include "force5.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Calibration delay of 10 milliseconds.
 * @details Time duration 10 microsecond.
 */
void dev_calibration_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void force5_cfg_setup ( force5_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = FORCE5_SET_DEV_ADDR;
}

err_t force5_init ( force5_t *ctx, force5_cfg_t *cfg ) {
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

err_t force5_generic_write ( force5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t force5_generic_read ( force5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t force5_read_byte ( force5_t *ctx, uint8_t *rx_data, uint8_t n_bytes ) {
    uint8_t status;
    
    status = FORCE5_OK;
    
    if ( ( n_bytes > 4 ) || ( n_bytes < 2 ) ) {
        status = FORCE5_ERROR;
    } else {
        i2c_master_read( &ctx->i2c, rx_data, n_bytes );
    }

    return status;
}

void force5_read_all_data ( force5_t *ctx, force5_data_t *force_data ) {
    uint8_t rx_buf[ 4 ];
    uint16_t force;
    uint16_t temp;

    i2c_master_read( &ctx->i2c, rx_buf, 4 );

    force_data->status_data = ( rx_buf[ 0 ] >> 6 ) & FORCE5_STATES_BIT_MASK;
    
    force = rx_buf[ 0 ];
    force <<= 8;
    force |= rx_buf[ 1 ];
    force &= 0x3FFF;
    
    force_data->force_data = force;
    
    temp = rx_buf[ 2 ];
    temp <<= 8;
    temp |= rx_buf[ 3 ];
    temp >>= 5;
    temp &= 0x07FF;
    
    force_data->temp_data = temp;
}

uint8_t force5_get_force_value ( force5_t *ctx, uint16_t *force ) {
    uint8_t rx_buf[ 4 ];
    uint8_t status;
    uint16_t tmp;

    i2c_master_read( &ctx->i2c, rx_buf, 4 );
    
    status = rx_buf[ 0 ] >> 6;
    status &= FORCE5_STATES_BIT_MASK;

    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    tmp &= 0x3FFF;
    
    *force = tmp;

    return status;
}

uint8_t force5_get_temperature_value ( force5_t *ctx, uint16_t *temperature ) {
    uint8_t rx_buf[ 4 ];
    uint8_t status;
    uint16_t tmp;

    i2c_master_read( &ctx->i2c, rx_buf, 4 );
    
    status = rx_buf[ 0 ] >> 6;
    status &= FORCE5_STATES_BIT_MASK;

    tmp = rx_buf[ 2 ];
    tmp <<= 8;
    tmp |= rx_buf[ 3 ];

    tmp >>= 5;

    tmp &= 0x07FF;
    
    *temperature = tmp;

    return status;
}

uint8_t force5_calibration ( force5_t *ctx, force5_calibration_t *calib_data ) {
    uint16_t force_val;
    uint8_t status;
    uint8_t n_cnt;
    uint32_t sum;
    
    sum = 0;
    
    for ( n_cnt = 0; n_cnt < 10; n_cnt++ ) {
        status = force5_get_force_value( ctx, &force_val );
        
        sum += force_val;
        
        dev_calibration_delay( );
    }
    
    calib_data->force_claib_data = ( uint16_t ) ( sum / 10 );
    
    return status;
}

float force5_get_force ( force5_t *ctx, force5_calibration_t calib_data ) {
    uint8_t status;
    uint16_t force_val;
    uint16_t force_calib;
    float force_n;

    status = force5_get_force_value ( ctx, &force_val );

    if ( status != FORCE5_STATES_NORMAL_OPERATION ) {
        force_n = 0.0;
    } else {
        if ( force_val < calib_data.force_claib_data ) {
            force_n = 0.0;
        } else {
            force_n = ( float ) force_val;
            force_n -= ( float ) calib_data.force_claib_data;
            force_n *= FORCE5_FORCE_SENSOR_25_N;
            force_n /= ( FORCE5_FORCE_MAX_VALUE - ( float ) calib_data.force_claib_data );
        }
    }

    return force_n;
}

float force5_get_temperature ( force5_t *ctx ) {
    uint8_t rx_buf[ 4 ];
    uint16_t temp;
    float temperature;

    force5_get_temperature_value( ctx, &temp );
    
    temperature = ( float ) temp;
    temperature /= 2047.0;
    temperature *= 200.0;
    temperature -= 50.0;

    return temperature;
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

void dev_calibration_delay ( void ) {
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END
