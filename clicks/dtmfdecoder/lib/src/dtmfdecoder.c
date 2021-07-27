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
 * @file dtmfdecoder.c
 * @brief DTMF Decoder Click Driver.
 */

#include "dtmfdecoder.h"

/**
 * @brief DTMF Decoder Click nibble mask.
 * @details Used for extracting only usefull tone data.
 */
#define DEV_DTMFDECODER_NIBBLE_MASK                0x0F

/**
 * @brief DTMF Decoder Click number of tones.
 * @details Max number of recognizing tones.
 */
#define DEV_DTMFDECODER_NUM_OF_TONES               16

static const uint8_t dev_ascii_matrix[ DEV_DTMFDECODER_NUM_OF_TONES ][ 2 ] =
{
    { 0x01, 0x31 }, // 1
    { 0x02, 0x32 }, // 2
    { 0x03, 0x33 }, // 3
    { 0x04, 0x34 }, // 4
    { 0x05, 0x35 }, // 5
    { 0x06, 0x36 }, // 6
    { 0x07, 0x37 }, // 7
    { 0x08, 0x38 }, // 8
    { 0x09, 0x39 }, // 9
    { 0x0A, 0x30 }, // 0
    { 0x0B, 0x2A }, // *
    { 0x0C, 0x23 }, // #
    { 0x0D, 0x41 }, // A
    { 0x0E, 0x42 }, // B
    { 0x0F, 0x43 }, // C
    { 0x00, 0x44 }, // D
};

void dtmfdecoder_cfg_setup ( dtmfdecoder_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->pwd = HAL_PIN_NC;
    cfg->inh = HAL_PIN_NC;
    cfg->std = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DTMFDECODER_SET_DEV_ADDR;
}

err_t dtmfdecoder_init ( dtmfdecoder_t *ctx, dtmfdecoder_cfg_t *cfg ) {
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

    digital_out_init( &ctx->inh, cfg->inh );
    digital_out_init( &ctx->pwd, cfg->pwd );

    digital_in_init( &ctx->std, cfg->std );

    return I2C_MASTER_SUCCESS;
}

void dtmfdecoder_default_cfg ( dtmfdecoder_t *ctx ) {
    dtmfdecoder_powerdown_off( ctx );
    dtmfdecoder_inhibit_off( ctx );
}

err_t dtmfdecoder_generic_write ( dtmfdecoder_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t dtmfdecoder_generic_read ( dtmfdecoder_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void dtmfdecoder_inhibit_on ( dtmfdecoder_t *ctx ) {
    digital_out_high( &ctx->inh );
}

void dtmfdecoder_inhibit_off ( dtmfdecoder_t *ctx ) {
    digital_out_low( &ctx->inh );
}

void dtmfdecoder_powerdown_on ( dtmfdecoder_t *ctx ) {
    digital_out_high( &ctx->pwd );
}

void dtmfdecoder_powerdown_off ( dtmfdecoder_t *ctx ) {
    digital_out_low( &ctx->pwd );
}

uint8_t dtmfdecoder_delayed_steering_check ( dtmfdecoder_t *ctx ) {
    return digital_in_read( &ctx->std );
}

uint8_t dtmfdecoder_tone_read ( dtmfdecoder_t *ctx ) {
    uint8_t tone_bin;
    uint8_t cnt;
    uint8_t decoded_data;
    
    dtmfdecoder_generic_read( ctx, DTMFDECODER_CMD_BYTE_INPUT, &tone_bin, 1 );
    tone_bin &= DEV_DTMFDECODER_NIBBLE_MASK;
    for ( cnt = 0 ; cnt < DEV_DTMFDECODER_NUM_OF_TONES ; cnt++ ) {
        if ( dev_ascii_matrix[ cnt ][ 0 ] == tone_bin ) {
            decoded_data = dev_ascii_matrix[ cnt ][ 1 ];
        }
    }
    
    return decoded_data;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
