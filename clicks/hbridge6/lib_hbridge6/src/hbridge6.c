/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file hbridge6.c
 * @brief H-Bridge 6 Click Driver.
 */

#include "hbridge6.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS

/**
 * @brief Reset delay.
 * @details Function for applying delay after reset.
 */
static void dev_reset_delay ( void );

/**
 * @brief Default config delay.
 * @details Function for applying delay.
 */
static void dev_cfg_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS

void hbridge6_cfg_setup ( hbridge6_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ms   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HBRIDGE6_I2C_SLAVE_ADR_0;

    cfg->dev_pwm_freq = HBRIDGE6_DEF_FREQ;
}

err_t hbridge6_init ( hbridge6_t *ctx, hbridge6_cfg_t *cfg ) {
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

    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR ) {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->ms, cfg->ms );

    return I2C_MASTER_SUCCESS;
}

void hbridge6_generic_write ( hbridge6_t *ctx, uint8_t reg, uint8_t tx_buf ) {
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_buf;

    i2c_master_write( &ctx->i2c, data_buf, 2 );
}

uint8_t hbridge6_generic_read ( hbridge6_t *ctx, uint8_t reg ) {
    uint8_t rx_buf;

    i2c_master_write( &ctx->i2c, &reg, 1 );
    i2c_master_read( &ctx->i2c, &rx_buf, 1 );

    return rx_buf;
}

err_t hbridge6_default_cfg ( hbridge6_t *ctx ) {
    hbridge6_reset( ctx );
    dev_cfg_delay( );
    hbridge6_default_config( ctx );
    dev_cfg_delay( );
    hbridge6_enable_diagnostic( ctx, HBRIDGE6_DIAGNOSTIC_ENABLE );
    dev_cfg_delay( );
    hbridge6_set_duty_cycle ( ctx, 0.0 );
    hbridge6_pwm_start( ctx );
    dev_cfg_delay( );
    hbridge6_set_multi_sense( ctx, HBRIDGE6_IN_PORT_SEL_0, HBRIDGE6_PIN_STATE_LOW );
    hbridge6_set_multi_sense( ctx, HBRIDGE6_IN_PORT_SEL_1, HBRIDGE6_PIN_STATE_LOW );
    dev_cfg_delay( );
    return HBRIDGE6_OK;
}

err_t hbridge6_set_duty_cycle ( hbridge6_t *ctx, float duty_cycle ) {
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t hbridge6_pwm_stop ( hbridge6_t *ctx ) {
    return pwm_stop( &ctx->pwm );
}

err_t hbridge6_pwm_start ( hbridge6_t *ctx ) {
    return pwm_start( &ctx->pwm );
}

void hbridge6_reset ( hbridge6_t *ctx ) {
    digital_out_low( &ctx->rst );
    dev_reset_delay( );

    digital_out_high( &ctx->rst );
    dev_reset_delay( );
}

void hbridge6_set_output ( hbridge6_t *ctx, uint8_t n_out_port, hbridge6_cfg_t cfg_data ) {
    n_out_port &= HBRIDGE6_NUMBER_OF_PORTS;

    hbridge6_generic_write( ctx, HBRIDGE6_REG_OUT_PORT, cfg_data.in_out << n_out_port );

    hbridge6_generic_write( ctx, HBRIDGE6_REG_POL_INV, cfg_data.invert  << n_out_port );

    hbridge6_generic_write( ctx, HBRIDGE6_REG_CONFIG,  cfg_data.out_val  << n_out_port );
}

void hbridge6_get_output ( hbridge6_t *ctx, uint8_t n_out_port, hbridge6_cfg_t *cfg_data ) {
    uint8_t tmp;

    n_out_port &= HBRIDGE6_NUMBER_OF_PORTS;

    tmp = hbridge6_generic_read( ctx, HBRIDGE6_REG_IN_PORT );
    tmp >>= n_out_port;
    tmp &= 0x01;

    cfg_data->in_out = tmp;

    tmp = hbridge6_generic_read( ctx, HBRIDGE6_REG_POL_INV );
    tmp >>= n_out_port;
    tmp &= 0x01;

    cfg_data->invert = tmp;

    tmp = hbridge6_generic_read( ctx, HBRIDGE6_REG_CONFIG );
    tmp >>= n_out_port;
    tmp &= 0x01;

    cfg_data->out_val = tmp;
}

void hbridge6_default_config ( hbridge6_t *ctx ) {
    hbridge6_generic_write( ctx, HBRIDGE6_REG_CONFIG, HBRIDGE6_DEFAULT_CFG );
}

void hbridge6_set_input_port_a ( hbridge6_t *ctx, uint8_t pin_state ) {
    uint8_t aux_val;

    aux_val = hbridge6_generic_read( ctx, HBRIDGE6_REG_IN_PORT );

    if ( pin_state == HBRIDGE6_PIN_STATE_LOW ) {
        aux_val &= HBRIDGE6_IN_PORT_IN_LOW;
    } else if ( pin_state == HBRIDGE6_PIN_STATE_HIGH ) {
        aux_val |= HBRIDGE6_IN_PORT_IN_HIGH;
    }

    hbridge6_generic_write( ctx, HBRIDGE6_REG_OUT_PORT, aux_val );
}

void hbridge6_set_input_port_b ( hbridge6_t *ctx, uint8_t pin_state ) {
    uint8_t aux_reg_val;

    aux_reg_val = hbridge6_generic_read( ctx, HBRIDGE6_REG_IN_PORT );

    if ( pin_state == HBRIDGE6_PIN_STATE_LOW ) {
        aux_reg_val &= 0xEF;
    } else if ( pin_state == HBRIDGE6_PIN_STATE_HIGH ) {
        aux_reg_val |= 0x10;
    }

    hbridge6_generic_write( ctx, HBRIDGE6_REG_OUT_PORT, aux_reg_val );
}

void hbridge6_enable_diagnostic ( hbridge6_t *ctx, uint8_t en_state ) {
    uint8_t aux_val;

    aux_val = hbridge6_generic_read( ctx, HBRIDGE6_REG_IN_PORT );

    if ( en_state == HBRIDGE6_DIAGNOSTIC_DISABLE ) {
        aux_val &= HBRIDGE6_MS_EN_LOW;
    } else {
        aux_val |= HBRIDGE6_MS_EN_HIGH;
    }

    hbridge6_generic_write( ctx, HBRIDGE6_REG_OUT_PORT, aux_val );
}

void hbridge6_set_multi_sense ( hbridge6_t *ctx, uint8_t sel_num, uint8_t pin_state ) {
    uint8_t aux_val;

    sel_num &= HBRIDGE6_IN_PORT_SEL_BIT_MASK;

    aux_val = hbridge6_generic_read( ctx, HBRIDGE6_REG_IN_PORT );

    if ( pin_state == HBRIDGE6_PIN_STATE_LOW ) {
        aux_val &= HBRIDGE6_IN_PORT_MULTI_SENSE_LOW << sel_num;;
    } else {
        aux_val |= HBRIDGE6_IN_PORT_MULTI_SENSE_HIGH << sel_num;
    }

    hbridge6_generic_write( ctx, HBRIDGE6_REG_OUT_PORT, aux_val );
}

void hbridge6_set_direction ( hbridge6_t *ctx, uint8_t direction ) {
    switch ( direction ) {
        case HBRIDGE6_DIRECTION_BRAKE: {
            hbridge6_set_input_port_a ( ctx, HBRIDGE6_PIN_STATE_HIGH );
            hbridge6_set_input_port_b ( ctx, HBRIDGE6_PIN_STATE_HIGH );
            break;
        }
        case HBRIDGE6_DIRECTION_CLOCKWISE: {
            hbridge6_set_input_port_a ( ctx, HBRIDGE6_PIN_STATE_LOW );
            hbridge6_set_input_port_b ( ctx, HBRIDGE6_PIN_STATE_HIGH );
            break;
        }
        case HBRIDGE6_DIRECTION_COUNTERCLOCKWISE: {
            hbridge6_set_input_port_b ( ctx, HBRIDGE6_PIN_STATE_LOW );
            hbridge6_set_input_port_a ( ctx, HBRIDGE6_PIN_STATE_HIGH );
            break;
        }
        default: {
            hbridge6_set_input_port_a ( ctx, HBRIDGE6_PIN_STATE_HIGH );
            hbridge6_set_input_port_b ( ctx, HBRIDGE6_PIN_STATE_HIGH );
            break;
        }
    }
}

uint8_t hbridge6_get_an_diagnostic ( hbridge6_t *ctx ) {
    return digital_in_read( &ctx->ms );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void ) {
    Delay_100ms( );
    Delay_10ms( );
}

static void dev_cfg_delay ( void ){
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
