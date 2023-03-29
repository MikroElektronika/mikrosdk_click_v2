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
 * @file leddriver9.c
 * @brief LED Driver 9 Click Driver.
 */

#include "leddriver9.h"

// ------------------------------------------------------------- PRIVATE MACROS

/**
 * @brief MODE1 register mask.
 * @details Mask for write valid bits of mode1 register.
 */
#define DEV_REG_MODE1_BITMASK                                              0x1F

/**
 * @brief MODE2 register mask.
 * @details Mask for write valid bits of mode2 register.
 */
#define DEV_REG_MODE2_BITMASK                                              0xA8

/**
 * @brief Number of channels.
 * @details Maximum number of available ledout channels.
 */
#define DEV_NUMBER_OF_CHANNELS                                             16

/**
 * @brief Max duty cycle.
 * @details Maximum settable duty cycle.
 */
#define DEV_MAX_DUTY_CYCLE                                                 100.0

/**
 * @brief Percentage conversion coefficient.
 * @details Coefficient used for percentage conversion.
 */
#define DEV_PERCENTAGE_CONV_COEF                                           100.0

/**
 * @brief Linear steps.
 * @details Maximum linear steps supported by the device.
 */
#define DEV_LINEAR_STEPS                                                   256.0

/**
 * @brief PWM channel offset address.
 * @details Address offset for setting the desired ledout channel pwm.
 */
#define DEV_PWM_CHANNEL_OFFSET_ADDR                                        0x02

/**
 * @brief Min blink period.
 * @details Minimum settable led blinking period.
 */
#define DEV_MIN_BLINK_PERIOD                                               0.042

/**
 * @brief Max blink period.
 * @details Maximum settable led blinking period.
 */
#define DEV_MAX_BLINK_PERIOD                                               10.73

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void dev_reset_delay ( void );

// ------------------------------------------------ PUNLIC FUNCTION DEFINITIONS

void leddriver9_cfg_setup ( leddriver9_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LEDDRIVER9_SET_DEV_ADDR;
}

err_t leddriver9_init ( leddriver9_t *ctx, leddriver9_cfg_t *cfg ) {
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

    digital_out_init( &ctx->rst, cfg->rst );

    return I2C_MASTER_SUCCESS;
}

void leddriver9_default_cfg ( leddriver9_t *ctx ) {
    // Click default configuration.
    leddriver9_hardware_reset( ctx );
}

err_t leddriver9_generic_write ( leddriver9_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t leddriver9_generic_read ( leddriver9_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t leddriver9_mode1_reg_write ( leddriver9_t *ctx, leddriver9_mode_reg_t *mode_reg ) {
    uint8_t reg_value;
    
    reg_value = mode_reg->mode_1->byte & DEV_REG_MODE1_BITMASK;
    
    return leddriver9_generic_write( ctx, LEDDRIVER9_REG_MODE1, &reg_value, 1 );
}

err_t leddriver9_mode1_reg_read ( leddriver9_t *ctx, leddriver9_mode_reg_t *mode_reg ) {
    uint8_t reg_value;
    int32_t status;
    
    status = leddriver9_generic_read( ctx, LEDDRIVER9_REG_MODE1, &reg_value, 1 );
    
    mode_reg->mode_1->byte = reg_value;
    
    return status;
}

err_t leddriver9_mode2_reg_write ( leddriver9_t *ctx, leddriver9_mode_reg_t *mode_reg ) {
    uint8_t reg_value;
    
    reg_value = mode_reg->mode_2->byte & DEV_REG_MODE2_BITMASK;
    
    return leddriver9_generic_write( ctx, LEDDRIVER9_REG_MODE2, &reg_value, 1 );
}

err_t leddriver9_mode2_reg_read ( leddriver9_t *ctx, leddriver9_mode_reg_t *mode_reg ) {
    uint8_t reg_value;
    int32_t status;
    
    status = leddriver9_generic_read( ctx, LEDDRIVER9_REG_MODE2, &reg_value, 1 );
    
    mode_reg->mode_2->byte = reg_value;
    
    return status;
}

err_t leddriver9_ledout_state ( leddriver9_t *ctx, leddriver9_output_state_t *output_state ) {
    uint8_t reg_value;
    uint8_t start_reg;
    uint8_t status;
    
    status = LEDDRIVER9_OK;
    start_reg = LEDDRIVER9_REG_LEDOUT0;
    
    reg_value = output_state->LEDOUT0->byte;
    status = leddriver9_generic_write( ctx, start_reg, &reg_value, 1 );
    
    if ( status ) {
        return status;
    }
    
    reg_value = output_state->LEDOUT1->byte;
    status = leddriver9_generic_write( ctx, ++start_reg, &reg_value, 1 );
    
    if ( status ) {
        return status;
    }
    
    reg_value = output_state->LEDOUT2->byte;
    status = leddriver9_generic_write( ctx, ++start_reg, &reg_value, 1 );
    
    if ( status ) {
        return status;
    }
    
    reg_value = output_state->LEDOUT3->byte;
    status = leddriver9_generic_write( ctx, ++start_reg, &reg_value, 1 );
    
    return status;
}

err_t leddriver9_set_pwm ( leddriver9_t *ctx, leddriver9_channel_sel_t ch_out, float duty_cycle ) {
    uint8_t reg_value;
    
    if ( ( ch_out < DEV_NUMBER_OF_CHANNELS ) && ( duty_cycle <= DEV_MAX_DUTY_CYCLE ) ) {
        reg_value = ( uint8_t )( ( duty_cycle / DEV_PERCENTAGE_CONV_COEF ) * ( DEV_LINEAR_STEPS - 1 ) );
        leddriver9_generic_write( ctx, ch_out + DEV_PWM_CHANNEL_OFFSET_ADDR, &reg_value, 1 );
        
        return LEDDRIVER9_OK;
    } else {
        return LEDDRIVER9_ERROR;
    }
}

err_t leddriver9_set_dimmer_pwm ( leddriver9_t *ctx, float duty_cycle ) {
    uint8_t reg_value;
    
    if ( duty_cycle <= DEV_MAX_DUTY_CYCLE ) {
        reg_value = ( uint8_t )( ( duty_cycle / DEV_PERCENTAGE_CONV_COEF ) * ( DEV_LINEAR_STEPS - 1 ) );
        leddriver9_generic_write( ctx, LEDDRIVER9_REG_GRPPWM, &reg_value, 1 );
        
        return LEDDRIVER9_OK;
    } else {
        return LEDDRIVER9_ERROR;
    }
}

err_t leddriver9_set_blink_period ( leddriver9_t *ctx, float period ) {
    uint8_t reg_value;
    
    if ( period >= DEV_MIN_BLINK_PERIOD && period <= DEV_MAX_BLINK_PERIOD ) {
        reg_value = ( uint8_t )( ( period * 24 ) - 1 );
        leddriver9_generic_write( ctx, LEDDRIVER9_REG_GRPFREQ, &reg_value, 1 );
        
        return LEDDRIVER9_OK;
    } else {
        return LEDDRIVER9_ERROR;
    }
}

void leddriver9_hardware_reset ( leddriver9_t *ctx ) {
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void ) {
    Delay_1us( );
}

// ------------------------------------------------------------------------- END
