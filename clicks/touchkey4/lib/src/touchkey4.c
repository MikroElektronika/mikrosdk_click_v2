/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "touchkey4.h"

// ------------------------------------------------------------------ VARIABLES

static uint8_t receive_check;
static uint8_t release_check;
static uint8_t input_check[ 3 ];
static uint8_t config_byte;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void touchkey4_cfg_setup ( touchkey4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_FULL; 
    cfg->i2c_address = TOUCHKEY4_SLAVE_ADDRESS;
}

TOUCHKEY4_RETVAL touchkey4_init ( touchkey4_t *ctx, touchkey4_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;
    
    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TOUCHKEY4_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TOUCHKEY4_OK;
}

void touchkey4_default_cfg ( touchkey4_t *ctx )
{
    touchkey4_write_reg( ctx, TOUCHKEY4_CONFIG2_REG, TOUCHKEY4_AN_CALIB_RETRY |
                         TOUCHKEY4_DETECT_RELEASE_EN );
    touchkey4_write_reg( ctx, TOUCHKEY4_REPEAT_RATE_EN_REG, TOUCHKEY4_REPEAT_RATE_DIS );
    touchkey4_write_reg( ctx, TOUCHKEY4_CONFIG_REG, TOUCHKEY4_AN_NOISE_FILTER_EN | 
                         TOUCHKEY4_DIG_NOISE_THRESHOLD_DIS );
    touchkey4_write_reg( ctx, TOUCHKEY4_STANDBY_THRESHOLD_REG, 0x40 );
    touchkey4_write_reg( ctx, TOUCHKEY4_STANDBY_SENSITIVITY_REG, 
                         TOUCHKEY4_STBY_SENSE_MULTIPLIER_64X );
    touchkey4_write_reg( ctx, TOUCHKEY4_STANDBY_CONFIG_REG, TOUCHKEY4_8_SAMPLES | 
                         TOUCHKEY4_SAMPLE_TIME_1280MICROSEC | TOUCHKEY4_CYCLE_TIME_70MILISEC );
    touchkey4_write_reg( ctx, TOUCHKEY4_AVRG_AND_SAMPL_CONFIG_REG, TOUCHKEY4_8_SAMPLES |
                         TOUCHKEY4_SAMPLE_TIME_1280MICROSEC | TOUCHKEY4_CYCLE_TIME_70MILISEC );
    touchkey4_write_reg( ctx, TOUCHKEY4_SENS_IN_CONFIG2_REG,
                         TOUCHKEY4_PRESS_AND_HOLD_EVENT_AFTER_280MILISEC );
    touchkey4_write_reg( ctx, TOUCHKEY4_SENS_IN_CONFIG_REG, TOUCHKEY4_5600MILISEC_BEFORE_RECALIB | 
                         TOUCHKEY4_INTERR_REPEAT_RATE_175MILISEC );
    touchkey4_write_reg( ctx, TOUCHKEY4_SENSITIVITY_CON_REG, TOUCHKEY4_SENSITIVITY_MULTIPLIER_32X | 
                         TOUCHKEY4_DATA_SCALING_FACTOR_256X );
    touchkey4_set_combo_mode( ctx, TOUCHKEY4_GAIN_1, TOUCHKEY4_COMBO_SENS_IN_ACT_EN,
                         TOUCHKEY4_COMBO_SENS_IN_BOTH_MODES_EN, TOUCHKEY4_COMBO_SENS_IN_STBY_EN );
}

void touchkey4_write_reg( touchkey4_t *ctx, const uint8_t register_address, const uint8_t transfer_data )
{
    uint8_t buff_data[ 2 ] = { 0 };
    
    buff_data[ 0 ] = register_address;
    buff_data[ 1 ] = transfer_data;
    
    i2c_master_write( &ctx->i2c, buff_data, 2 ); 
    receive_check = 1;

    switch ( register_address )
    {
        case 0x00: 
        {
            config_byte = transfer_data;
        break;
        }
        case 0x44: 
        {
            release_check = transfer_data;
        break;
        }
        default:
        break;
    }
}

void touchkey4_read_reg ( touchkey4_t *ctx, const uint8_t register_address, uint8_t *data_out,
                         const uint8_t n_bytes )
{
    uint8_t reg_write = register_address;
    i2c_master_write_then_read( &ctx->i2c, &reg_write, 1, data_out, n_bytes );
    receive_check = 1;
}

uint8_t touchkey4_receive_byte( touchkey4_t *ctx, const uint8_t register_address )
{
    uint8_t temp = register_address;
    
    if ( receive_check )
    {
        i2c_master_write( &ctx->i2c, &temp, 1 );  
        receive_check = 0;
    }
    
    i2c_master_read( &ctx->i2c, &temp, 1 );
    
    return temp;
}

void touchkey4_detect_touch ( touchkey4_t *ctx, uint8_t *input_sens )
{
    uint8_t int_check;
    uint8_t touch_check;
    uint8_t noise_check;
    uint8_t i;
    uint8_t temp;
    
    temp = 1;

    touchkey4_read_reg( ctx, 0x00, &int_check, 1 );
    while ( !(int_check & 0x01) )
        touchkey4_read_reg( ctx, 0x00, &int_check, 1 );
    config_byte &= 0xFE;
    touchkey4_write_reg( ctx, 0x00, config_byte );
    touchkey4_read_reg( ctx, 0x03, &touch_check, 1 );
    touchkey4_read_reg( ctx, 0x0A, &noise_check, 1 );
    for ( i = 0; i < 3; i++ )
    {
        if ( ( touch_check & temp ) && ( !( noise_check & temp ) ) )
        {
            input_sens[ i ] = 1;
            if ( !( release_check & 0x01 ) )
            {
                input_check[ i ] = 1;
            }
        }
        else if ( input_check[ i ] )
        {
            input_sens[ i ] = 2;
            input_check[ i ] = 0;
        }
        else
            input_sens[ i ] = 0;
        temp <<= 1;
    }
}

void touchkey4_set_active_mode ( touchkey4_t *ctx, const uint8_t analog_gain, const uint8_t en_input1,
                                const uint8_t en_input2, const uint8_t en_input3 )
{
    uint8_t temp;
    
    temp = en_input1 | en_input2 | en_input3;
    if ( temp & 0xFE )
        return;
    switch ( analog_gain )
    {
        case 1: 
        {
            temp = 0x00;
        break;
        }
        case 2:
        {
            temp = 0x44;
        break;
        }
        case 4: 
        {
            temp = 0x88;
        break;
        }
        case 8:
         {
            temp = 0xCC;
        break;
        }
        default: 
        return;
    }
    touchkey4_write_reg( ctx, 0x00, temp );
    temp = en_input3;
    temp <<= 1;
    temp |= en_input2;
    temp <<= 1;
    temp |= en_input1;
    touchkey4_write_reg( ctx, 0x21, temp );
    touchkey4_write_reg( ctx, 0x27, temp );
}

void touchkey4_set_standby_mode( touchkey4_t *ctx, const uint8_t analog_gain, const uint8_t en_input1,
                                 const uint8_t en_input2, const uint8_t en_input3 )
{
    uint8_t temp;

    temp = en_input1 | en_input2 | en_input3;
    if ( temp & 0xFE )
        return;
    switch ( analog_gain )
    {
        case 1: 
        {
            temp = 0x20;
        break;
        }
        case 2: 
        {
            temp = 0x64;
        break;
        }
        case 4:
        {
            temp = 0xA8;
        break;
        }
        case 8: 
        {
            temp = 0xEC;
        break;
        }
        default:
        return;
    }
    touchkey4_write_reg( ctx, 0x00, temp );
    temp = en_input3;
    temp <<= 1;
    temp |= en_input2;
    temp <<= 1;
    temp |= en_input1;
    touchkey4_write_reg( ctx, 0x40, temp );
    touchkey4_write_reg( ctx, 0x27, temp );
}

void touchkey4_set_combo_mode ( touchkey4_t *ctx, const uint8_t analog_gain, const uint8_t en_input1,
                               const uint8_t en_input2, const uint8_t en_input3 )
{
    uint8_t temp;
    uint8_t tmp;
    uint8_t interr_en;
    uint8_t i;
    uint8_t buffer_data[ 3 ];

    tmp = 0;

    temp = en_input1 | en_input2 | en_input3;
    if ( temp & 0xF8 )
        return;
    switch ( analog_gain )
    {
        case 1: 
        {
            temp = 0x02;
        break;
        }
        case 2:
        {   temp = 0x46;
        break;
        }
        case 4: 
        {
            temp = 0x8A;
        break;
        }
        case 8:
        {
            temp = 0xCE;
        break;
        }
        default:
        return;
    }
    touchkey4_write_reg( ctx, 0x00, temp );
    temp = 0;
    buffer_data[ 0 ] = en_input1;
    buffer_data[ 1 ] = en_input2;
    buffer_data[ 2 ] = en_input3;
    for ( i = 0; i < 3; i++ )
    {
        if ( buffer_data[ i ] & 0x04 )
        {
            temp |= ( ( buffer_data[ i ] & 0x01 ) << i);
            tmp |= ( ( buffer_data[ i ] & 0x01 ) << i);
        }
        else
        {
            if ( buffer_data[ i ] & 0x02 )
            { 
                    temp |= ( ( buffer_data[ i ] & 0x01 ) << i);
            }
            else
            {
                    tmp |= ( buffer_data[ i ] << i );
            }
        }
    }
    interr_en = temp | tmp;
    touchkey4_write_reg( ctx, 0x21, temp );
    touchkey4_write_reg( ctx, 0x40, tmp );
    touchkey4_write_reg( ctx, 0x27, interr_en );
}

void touchkey4_set_deep_sleep_mode ( touchkey4_t *ctx )
{
    uint8_t temp = 0x10;
    
    touchkey4_write_reg( ctx, 0x00, temp );
}

uint8_t touchkey4_check_interrupt ( touchkey4_t *ctx )
{
    if ( digital_in_read( &ctx->int_pin ) )
    {
            return 1;
    }
    else
    {
            return 0;
    }
}

// ------------------------------------------------------------------------- END

