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
 * @file charger3.c
 * @brief Charger 3 Click Driver.
 */

#include "charger3.h"

// ------------------------------------------------------------- PRIVATE MACROS

#define CHARGER3_10_BIT                                       0x03FF

#define CHARGER3_RES_MIN_VAL                                  200
#define CHARGER3_RES_MAX_VAL                                  10000
#define CHARGER3_WIPER_RESOLUTION                             1024

#define CHARGER3_CURR_MIN_VAL                                 0.11
#define CHARGER3_CURR_MAX_VAL                                 1
#define CHARGER3_CURR_COEF                                    1200
#define CHARGER3_SERIES_RES_VAL                               1000

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void charger3_cfg_setup ( charger3_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CHARGER3_SET_DEV_ADDR;
}

err_t charger3_init ( charger3_t *ctx, charger3_cfg_t *cfg ) {
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

void charger3_default_cfg ( charger3_t *ctx ) {
    charger3_enable_write( ctx );
    Delay_10ms( );
    charger3_operating_mode ( ctx, CHARGER3_ENABLE_CHARGING );
    Delay_10ms( );
}

err_t charger3_generic_write ( charger3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t charger3_generic_read ( charger3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void charger3_enable_write ( charger3_t *ctx ) {
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = CHARGER3_COMMAND_WRITE_MEMORY;
    tx_buf[ 1 ] = CHARGER3_UPDATE_WIPER_POS;
    i2c_master_write( &ctx->i2c, tx_buf, 3 );
}

void charger3_operating_mode ( charger3_t *ctx, uint8_t mode ) {
    uint8_t enable_charging = 0x00;
    uint8_t disable_charging = 0x01;
    
    if ( mode == CHARGER3_ENABLE_CHARGING  ) {
        charger3_generic_write( ctx, CHARGER3_COMMAND_SW_SHUTDOWN, &enable_charging, 1 );
    }
    else {
        charger3_generic_write( ctx, CHARGER3_COMMAND_SW_SHUTDOWN, &disable_charging, 1 );
    }
}

void charger3_write_rdac ( charger3_t *ctx, uint16_t rdac_data ) {
    uint8_t tx_buf[ 2 ];

    rdac_data &= CHARGER3_10_BIT;

    tx_buf[ 0 ] = CHARGER3_COMMAND_WRITE_RDAC;
    tx_buf[ 0 ] |= ( uint8_t ) ( rdac_data >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) rdac_data;

    i2c_master_write( &ctx->i2c, tx_buf, 3 );
}

uint8_t charger3_set_digipot_res ( charger3_t *ctx, uint16_t res_ohm ) {
    uint8_t status;
    uint16_t rdac_data;
    float tmp;

    status = CHARGER3_STATUS_ERROR_SUCCESS;
    
    if ( res_ohm < CHARGER3_RES_MAX_VAL && res_ohm >= CHARGER3_RES_MIN_VAL ) {
        tmp = CHARGER3_WIPER_RESOLUTION;
        tmp *= ( float ) res_ohm;
        tmp /= CHARGER3_RES_MAX_VAL;
        
        rdac_data = ( uint16_t ) tmp;
        
        charger3_write_rdac( ctx, rdac_data );
    }
    else {
        status = CHARGER3_STATUS_ERROR_FAILURE;
    }
        return status;
}

uint8_t charger3_set_current ( charger3_t *ctx, float curr_value ) {
    uint8_t status;
    uint16_t res_data;
    float tmp;

    status = CHARGER3_STATUS_ERROR_SUCCESS;
    
    if ( curr_value <= CHARGER3_CURR_MAX_VAL && curr_value > CHARGER3_CURR_MIN_VAL ) {
        tmp = CHARGER3_CURR_COEF;
        tmp /= curr_value;
        tmp -= CHARGER3_SERIES_RES_VAL;
        
        res_data = ( uint16_t ) tmp;
        
        charger3_set_digipot_res( ctx, res_data ) ;
    }
    else {
        status = CHARGER3_STATUS_ERROR_FAILURE;
    }
        return status;
}

uint16_t charger3_read_rdac ( charger3_t *ctx ) {
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 2 ];
    uint16_t result;

    tx_buf[ 0 ] = CHARGER3_COMMAND_READ_RDAC;
    tx_buf[ 1 ] = CHARGER3_DUMMY;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    result &= CHARGER3_10_BIT;

    return result;
}

float charger3_calc_digipot_res ( charger3_t *ctx ) {
    float result;

    result = charger3_read_rdac( ctx );
    result /= CHARGER3_WIPER_RESOLUTION;
    result *= CHARGER3_RES_MAX_VAL;

    return result;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
