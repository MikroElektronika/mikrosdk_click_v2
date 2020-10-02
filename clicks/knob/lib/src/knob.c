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

#include "knob.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void knob_cfg_setup ( knob_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->ena = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->enb = HAL_PIN_NC;
    cfg->oe = HAL_PIN_NC;
    cfg->sw = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = KNOB_DEF_SLAVE_ADDRESS;
}

KNOB_RETVAL knob_init ( knob_t *ctx, knob_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return KNOB_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->oe, cfg->oe );

    // Input pins

    digital_in_init( &ctx->ena, cfg->ena );
    digital_in_init( &ctx->enb, cfg->enb );
    digital_in_init( &ctx->sw, cfg->sw );
    
    return KNOB_OK;
}

void knob_default_cfg ( knob_t *ctx )
{
    // Click default configuration

    knob_led_output_enable ( ctx, KNOB_ENABLE_LED_OUTPUTS );
    knob_set_output_gain ( ctx, KNOB_OUTPUT_GAIN_ALL_LED, KNOB_FULL_OUTPUT_CURRENT_GAIN);
    knob_set_encoder_start_position( ctx, 1 );
}

void knob_generic_write ( knob_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );  
}

void knob_generic_read ( knob_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void knob_reset ( knob_t *ctx )
{
    uint8_t rst_val;

    digital_out_low( &ctx->rst );
    Delay_10ms();
    digital_out_high( &ctx->rst  );
    Delay_10ms();

    rst_val = 0xFF;
    knob_generic_write( ctx, 0x40, &rst_val, 1 );
}

void knob_led_output_enable ( knob_t *ctx, uint8_t state)
{
    digital_out_write( &ctx->oe, state );
}

uint8_t knob_get_ena_state( knob_t *ctx )
{
    return digital_in_read( &ctx->ena );
}

uint8_t knob_get_enb_state ( knob_t *ctx )
{
    return digital_in_read( &ctx->enb );
}

uint8_t knob_get_sw_button_state( knob_t *ctx )
{
    return digital_in_read( &ctx->sw );
}

void knob_set_encoder_start_position ( knob_t *ctx, int32_t position )
{
    ctx->encoder_position = position;
}

void knob_set_led_state ( knob_t *ctx, uint8_t led, uint8_t state )
{
    knob_generic_write( ctx, 0x09 + led, &state, 1 );
}

void knob_set_brightness ( knob_t *ctx, uint8_t led, uint8_t value )
{
    if ( led == KNOB_BRIGHTNESS_ALL_LED )
    {
         knob_generic_write( ctx, 0x3F, &value, 1 );
    }
    else
    {
         knob_generic_write( ctx, led, &value, 1 );
    }
}

void knob_set_output_gain ( knob_t *ctx, uint8_t led, uint8_t value )
{
    if ( led == KNOB_OUTPUT_GAIN_ALL_LED )
    {
        knob_generic_write( ctx, 0x3F, &value, 1 );
    }
    else
    {
        knob_generic_write( ctx, led, &value, 1 );
    }
}

void knob_get_encoder_position ( knob_t *ctx, int32_t *position, uint8_t *dir )
{
    uint8_t ena_val;
    uint8_t enb_val;

    ena_val = knob_get_ena_state( ctx );
    enb_val = knob_get_enb_state( ctx );

    if ( ena_val == enb_val )
    {
        ctx->state_old_rotate = 0;
        ctx->start_status = ena_val && enb_val;
    }
    else
    {
        ctx->state_new_rotate = 1;
        if ( ctx->state_new_rotate != ctx->state_old_rotate )
        {
            ctx->state_old_rotate = 1;
            if ( ctx->start_status ==  knob_get_ena_state( ctx ) )
            {
                ctx->encoder_position++;
                *dir = 1;
            }
            else
            {
                ctx->encoder_position--;
                *dir = 2;
            }
        }
    }
    *position = ctx->encoder_position;
}

// ------------------------------------------------------------------------- END

