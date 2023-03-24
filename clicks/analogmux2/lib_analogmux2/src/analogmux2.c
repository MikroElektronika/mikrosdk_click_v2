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
 * @file analogmux2.c
 * @brief Analog MUX 2 Click Driver.
 */

#include "analogmux2.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Reset delay.
 * @details Reset delay for 100 milliseconds.
 */
static void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void analogmux2_cfg_setup ( analogmux2_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ANALOGMUX2_SET_DEV_ADDR_0;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref       = 2.048;
}

err_t analogmux2_init ( analogmux2_t *ctx, analogmux2_cfg_t *cfg ) {
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

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    if ( analog_in_set_vref_value( &ctx->adc, cfg->vref ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    if ( analog_in_set_resolution( &ctx->adc, cfg->resolution ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->rst, cfg->rst );

    return I2C_MASTER_SUCCESS;
}

void analogmux2_default_cfg ( analogmux2_t *ctx ) {
    // Click default configuration.

    // Reset.

    analogmux2_hw_reset( ctx );

    // Disable all channels.

    analogmux2_set_channel( ctx, ANALOGMUX2_SET_NO_CHANNEL );
}

void analogmux2_hw_reset ( analogmux2_t *ctx ) {
    digital_out_low( &ctx->rst );
    dev_reset_delay( );

    digital_out_high( &ctx->rst );
    dev_reset_delay( );
}

err_t analogmux2_generic_write ( analogmux2_t *ctx, uint8_t tx_data ) {
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = tx_data;

    return i2c_master_write( &ctx->i2c, tx_buf, 1 );
}

uint8_t analogmux2_generic_read ( analogmux2_t *ctx ) {
    uint8_t rx_buf[ 1 ];

    i2c_master_read( &ctx->i2c, rx_buf, 1 );

    return rx_buf[ 0 ];
}

err_t analogmux2_set_channel ( analogmux2_t *ctx, uint8_t mux_ch ) {
    uint8_t tx_buf[ 1 ];
    err_t status;

    status = ANALOGMUX2_SUCCESS;
    tx_buf[ 0 ] = ANALOGMUX2_VAL_CHANNEL_0;

    if ( mux_ch > ANALOGMUX2_SET_CHANNEL_7 ) {
        tx_buf[ 0 ] = ANALOGMUX2_VAL_CHANNEL_OFF;
        status = ANALOGMUX2_ERROR;
    }

    tx_buf[ 0 ] <<= mux_ch;
    i2c_master_write( &ctx->i2c, tx_buf, 1 );

    return status;
}

uint8_t analogmux2_get_channel ( analogmux2_t *ctx ) {
    uint8_t ch_val;
    uint8_t ch_pos;

    i2c_master_read( &ctx->i2c, &ch_val, 1 );

    switch ( ch_val ) {
        case ANALOGMUX2_VAL_CHANNEL_0: {
            ch_pos = ANALOGMUX2_SET_CHANNEL_0;
            break;
        }
        case ANALOGMUX2_VAL_CHANNEL_1: {
            ch_pos = ANALOGMUX2_SET_CHANNEL_1;
            break;
        }
        case ANALOGMUX2_VAL_CHANNEL_2: {
            ch_pos = ANALOGMUX2_SET_CHANNEL_2;
            break;
        }
        case ANALOGMUX2_VAL_CHANNEL_3: {
            ch_pos = ANALOGMUX2_SET_CHANNEL_3;
            break;
        }
        case ANALOGMUX2_VAL_CHANNEL_4: {
            ch_pos = ANALOGMUX2_SET_CHANNEL_4;
            break;
        }
        case ANALOGMUX2_VAL_CHANNEL_5: {
            ch_pos = ANALOGMUX2_SET_CHANNEL_5;
            break;
        }
        case ANALOGMUX2_VAL_CHANNEL_6: {
            ch_pos = ANALOGMUX2_SET_CHANNEL_6;
            break;
        }
        case ANALOGMUX2_VAL_CHANNEL_7: {
            ch_pos = ANALOGMUX2_SET_CHANNEL_7;
            break;
        }
        default: {
            ch_pos = ANALOGMUX2_SET_NO_CHANNEL;
            break;
        }
    }

    return ch_pos;
}

err_t analogmux2_read_an_pin_value ( analogmux2_t *ctx, uint16_t *data_out ) {
    return analog_in_read( &ctx->adc, data_out );
}

err_t analogmux2_read_an_pin_voltage ( analogmux2_t *ctx, float *data_out ) {
    return analog_in_read_voltage( &ctx->adc, data_out );
}


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
