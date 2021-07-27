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
 * @file volume2.c
 * @brief Volume 2 Click Driver.
 */

#include "volume2.h"

// ------------------------------------------------------------- PRIVATE MACROS

/**
 * @brief Gain Ch2 bit shift.
 * @details Shifts the Ch2 data by 2 so it's safely stored into reg.
 */
#define DEV_VOLUME2_GAIN_CH2_BIT_SHIFT                          2

/**
 * @brief Zero cross bit shift.
 * @details Shifts the zero cross detection bit by 7 so it's safely stored into reg.
 */
#define DEV_VOLUME2_ZERO_CROSS_BIT_SHIFT                        7

/**
 * @brief Zero address bit mask.
 * @details Masks the first 4 bits of zero register since they are only usable.
 */
#define DEV_VOLUME2_ZERO_ADD_BIT_MASK                           0x0F

/**
 * @brief Minimal attenuation value.
 * @details If this value is stored into the volume register, the attenuation is zero.
 */
#define DEV_VOLUME2_MIN_VOL_ATTENUATION                         0x77

/**
 * @brief Attenuation bit mask.
 * @details Masks the first 7 bits of the volume regster, last one is reserved.
 */
#define DEV_VOLUME2_VOL_ATTENUATION_BIT_MASK                    0x7F

/**
 * @brief Start address.
 * @details This is the start address for full update of the volume data.
 */
#define DEV_VOLUME2_START_ADDRESS                               0x00

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void volume2_cfg_setup ( volume2_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->mte = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = VOLUME2_SET_DEV_ADDR;
}

err_t volume2_init ( volume2_t *ctx, volume2_cfg_t *cfg ) {
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

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->mte, cfg->mte );

    return I2C_MASTER_SUCCESS;
}

err_t volume2_default_cfg ( volume2_t *ctx ) {
    volume2_vol_data_t update_data;
    
    update_data.gain_ch1 = VOLUME2_GAIN_OPT_9_DB;
    update_data.gain_ch2 = VOLUME2_GAIN_OPT_9_DB;
    update_data.zero_cross_det_ch1 = VOLUME2_ZERO_CROSS_DET_OPT_ON;
    update_data.zero_cross_det_ch2 = VOLUME2_ZERO_CROSS_DET_OPT_ON;
    update_data.attenuation_ch1 = 0;
    update_data.attenuation_ch2 = 0;
    
    volume2_update_vol_data( ctx, update_data );
    
    return volume2_device_mute( ctx, VOLUME2_DEVICE_MUTE_OFF );
}

err_t volume2_generic_write ( volume2_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t volume2_generic_read ( volume2_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t volume2_device_mute ( volume2_t *ctx, uint8_t mte_state ) {
    if ( mte_state == VOLUME2_DEVICE_MUTE_ON ) {
        digital_out_write( &ctx->mte, 1 );
        return VOLUME2_OK;
    } else if ( mte_state == VOLUME2_DEVICE_MUTE_OFF ) {
        digital_out_write( &ctx->mte, 0 );
        return VOLUME2_OK;
    }
    return VOLUME2_ERROR;
}

err_t volume2_update_vol_data ( volume2_t *ctx, volume2_vol_data_t update_data ) {
    uint8_t tx_buf[ 3 ];
    
    tx_buf[ 0 ] = ( update_data.gain_ch1 | ( update_data.gain_ch2 << DEV_VOLUME2_GAIN_CH2_BIT_SHIFT ) ) & DEV_VOLUME2_ZERO_ADD_BIT_MASK;
    tx_buf[ 1 ] = ( update_data.zero_cross_det_ch1 << DEV_VOLUME2_ZERO_CROSS_BIT_SHIFT ) | ( ( DEV_VOLUME2_MIN_VOL_ATTENUATION - update_data.attenuation_ch1 ) & DEV_VOLUME2_VOL_ATTENUATION_BIT_MASK );
    tx_buf[ 2 ] = ( update_data.zero_cross_det_ch2 << DEV_VOLUME2_ZERO_CROSS_BIT_SHIFT ) | ( ( DEV_VOLUME2_MIN_VOL_ATTENUATION - update_data.attenuation_ch2 ) & DEV_VOLUME2_VOL_ATTENUATION_BIT_MASK );
    
    return volume2_generic_write( ctx, DEV_VOLUME2_START_ADDRESS, tx_buf, 3 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
