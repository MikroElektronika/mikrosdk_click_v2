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

#include "smoke.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void smoke_cfg_setup ( smoke_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = SMOKE_I2C_ADDRESS;
}

SMOKE_RETVAL smoke_init ( smoke_t *ctx, smoke_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return SMOKE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SMOKE_OK;
}

void smoke_default_cfg ( smoke_t *ctx )
{
    Delay_100ms( );

    smoke_reset( ctx );
    smoke_fifo_setting( ctx, 2, SMOKE_SAMPLEAVG_32 );
    smoke_fifo_setting( ctx, 1, 0 );
    smoke_setting_function( ctx, 2, SMOKE_MODE_MULTILED );
    smoke_setting_function( ctx, 3, SMOKE_ADCRANGE_2048 );
    smoke_setting_function( ctx, 4, SMOKE_SAMPLERATE_400 );
    smoke_setting_function( ctx, 5, SMOKE_PULSEWIDTH_411 );

 
    smoke_setting_prox_and_amp( ctx, 0, SMOKE_MIN_POWER_LEVEL );
    smoke_setting_prox_and_amp( ctx, 1, SMOKE_MIN_POWER_LEVEL );
    smoke_setting_prox_and_amp( ctx, 2, SMOKE_MAX_POWER_LEVEL );
    smoke_setting_prox_and_amp( ctx, 3, SMOKE_MIN_POWER_LEVEL );

    smoke_disable_slots( ctx );
    smoke_enable_slot( ctx, 1, SMOKE_SLOT_RED_LED );
    smoke_enable_slot( ctx, 2, SMOKE_SLOT_IR_LED );
    smoke_enable_slot( ctx, 3, SMOKE_SLOT_GREEN_LED );
    smoke_clear_fifo( ctx );

    Delay_100ms( );
    smoke_enable_disable_interrupts( ctx, 1, 1 );
    Delay_100ms( );
}

void smoke_write_data ( smoke_t *ctx, uint8_t wr_addr, uint8_t wr_data )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = wr_addr;
    w_buffer[ 1 ] = wr_data;  

    i2c_master_write( &ctx->i2c, w_buffer, 2 ); 
}

uint8_t smoke_read_data ( smoke_t *ctx, uint8_t rd_addr )
{
    uint8_t w_buffer[ 1 ];
    uint8_t r_buffer[ 1 ];

    w_buffer[ 0 ] = rd_addr;

    i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, r_buffer, 1 );

    return r_buffer[ 0 ];
}

void smoke_set_new_value ( smoke_t *ctx, uint8_t reg, uint8_t mask, uint8_t value )
{
    uint8_t old_val;

    old_val = smoke_read_data( ctx, reg );
    old_val = old_val & mask;

    smoke_write_data( ctx, reg, old_val | value );
}

uint8_t smoke_get_intrrupt ( smoke_t *ctx, uint8_t flag )
{
    if ( flag == 1 )
    {
        // Get the main interrupt group 
        return smoke_read_data( ctx, SMOKE_INT_STAT1 );
    }
    if ( flag == 2 )
    {
        // Get the temporary ready interrupt
        return smoke_read_data( ctx, SMOKE_INT_STAT2 );
    }
}

void smoke_enable_disable_interrupts ( smoke_t *ctx, uint8_t interrupt_flag, uint8_t enable_flag )
{
    uint8_t reg_addr;
    uint8_t mask; 
    uint8_t value;

    if ( interrupt_flag >= 0 && interrupt_flag <= 3 )
    {
        reg_addr = SMOKE_INT_ENABLE1;
    }
    else if ( interrupt_flag == 4 )
    {
        reg_addr = SMOKE_INT_ENABLE2;
    }

    if ( interrupt_flag == 0 )
    {
        mask = SMOKE_INT_A_FULL_MASK;
        if ( enable_flag == 1 )
        {
            value = SMOKE_INT_A_FULL_ENABLE;
        }
        else if ( enable_flag == 0 )
        {
            value = SMOKE_INT_A_FULL_DISABLE;
        }
    }
    
    if ( interrupt_flag == 1 )
    {
        mask = SMOKE_INT_DATA_RDY_MASK;
        if ( enable_flag == 1 )
        {
            value = SMOKE_INT_DATA_RDY_ENABLE;
        }
        else if ( enable_flag == 0 )
        {
            value = SMOKE_INT_DATA_RDY_DISABLE;
        }
    }

    if ( interrupt_flag == 2 )
    {
        mask = SMOKE_INT_ALC_OVF_MASK;
        if ( enable_flag == 1 )
        {
            value = SMOKE_INT_ALC_OVF_ENABLE;
        }
        else if ( enable_flag == 0 )
        {
            value = SMOKE_INT_ALC_OVF_DISABLE;
        }
    }

    if ( interrupt_flag == 3 )
    {
        mask = SMOKE_INT_PROX_INT_MASK;
        if ( enable_flag == 1 )
        {
            value = SMOKE_INT_PROX_INT_ENABLE;
        }
        else if ( enable_flag == 0 )
        {
            value = SMOKE_INT_PROX_INT_DISABLE;
        }
    }

    if ( interrupt_flag == 4 )
    {
        mask = SMOKE_INT_DIE_TEMP_RDY_MASK;
        if ( enable_flag == 1 )
        {
            value = SMOKE_INT_DIE_TEMP_RDY_ENABLE;
        }
        else if ( enable_flag == 0 )
        {
            value = SMOKE_INT_DIE_TEMP_RDY_DISABLE;
        }
    }

    smoke_set_new_value( ctx, reg_addr, mask, value );
}

void smoke_setting_function ( smoke_t *ctx, uint8_t flag, uint8_t mode )
{
    uint8_t reg_addr;
    uint8_t mask; 
    uint8_t value;

    if ( flag >= 0 && flag <= 2 )
    {
        reg_addr = SMOKE_MODE_CONFIG;
    }
    else if ( flag >= 3 && flag <= 5 )
    {
        reg_addr = SMOKE_PARTICLE_CONFIG;
    }

    if ( flag == 0 )
    {
        mask  = SMOKE_SHUTDOWN_MASK;
        value = SMOKE_SHUTDOWN;
    }
    else if ( flag == 1 )
    {
        mask  = SMOKE_SHUTDOWN_MASK;
        value = SMOKE_WAKEUP;
    }
    else if ( flag == 2 )
    {
        mask  = SMOKE_MODE_MASK;
    } 
    else if ( flag == 3 )
    {
        mask  = SMOKE_ADCRANGE_MASK;
    } 
    else if ( flag == 4 )
    {
        mask  = SMOKE_SAMPLERATE_MASK;
    } 
    else if ( flag == 5 )
    {
        mask  = SMOKE_PULSEWIDTH_MASK;
    } 

    if ( flag >= 2  && flag <= 5 )
    {
        value = mode;
    }

    smoke_set_new_value( ctx, reg_addr, mask, value );
}

void smoke_setting_prox_and_amp ( smoke_t *ctx, uint8_t flag, uint8_t write_data )
{
   uint8_t write_addr;

    if ( flag == 0 )
    {
        write_addr = SMOKE_LED1_PULSE_AMP;
    }
    else if ( flag == 1 )
    {
        write_addr = SMOKE_LED2_PULSE_AMP;
    }
    else if ( flag == 2 )
    {
        write_addr = SMOKE_LED3_PULSE_AMP;
    } 
    else if ( flag == 3 )
    {
        write_addr = SMOKE_LED_PROX_AMP;
    } 
    else if ( flag == 4 )
    {
        write_addr = SMOKE_PROX_INT_THRESH;
    } 

   smoke_write_data( ctx, write_addr, write_data );
}

void smoke_enable_slot ( smoke_t *ctx, uint8_t slot_num, uint8_t dev )
{
    if ( slot_num == 1 )
    {
        smoke_set_new_value( ctx, SMOKE_MULTI_LED_CONFIG1, SMOKE_SLOT1_MASK, dev );
    }
    else if ( slot_num == 2 )
    {
        smoke_set_new_value( ctx, SMOKE_MULTI_LED_CONFIG1, SMOKE_SLOT2_MASK, dev << 4 );
    }
    else if ( slot_num == 3 )
    {
        smoke_set_new_value( ctx, SMOKE_MULTI_LED_CONFIG2, SMOKE_SLOT3_MASK, dev );
    }
    else if ( slot_num == 4 )
    {
        smoke_set_new_value( ctx, SMOKE_MULTI_LED_CONFIG2, SMOKE_SLOT4_MASK, dev << 4 );
    }
}

void smoke_disable_slots ( smoke_t *ctx )
{
    smoke_write_data( ctx, SMOKE_MULTI_LED_CONFIG1, 0 );
    smoke_write_data( ctx, SMOKE_MULTI_LED_CONFIG2, 0 );
}

void smoke_clear_fifo ( smoke_t *ctx )
{
    smoke_write_data( ctx, SMOKE_FIFO_WRITE_PTR, 0 );
    smoke_write_data( ctx, SMOKE_FIFO_OVERFLOW, 0 );
    smoke_write_data( ctx, SMOKE_FIFO_READ_PTR, 0 );
}

void smoke_fifo_setting ( smoke_t *ctx, uint8_t flag, uint8_t samp_num )
{
    uint8_t mask; 
    uint8_t value;
    
    if ( flag == 0 || flag == 1 )
    {
        mask = SMOKE_ROLLOVER_MASK;
        if ( flag == 0 )
        {
            value = SMOKE_ROLLOVER_DISABLE;
        }
        else if ( flag == 1 )
        {
            value = SMOKE_ROLLOVER_ENABLE;
        }
    }
    else if ( flag == 2 || flag == 3 )
    {
        value = samp_num;
        if ( flag == 2 )
        {
            value = SMOKE_SAMPLEAVG_MASK;
        }
        else if ( flag == 3 )
        {
            value = SMOKE_A_FULL_MASK;
        }
    }

    smoke_set_new_value( ctx, SMOKE_FIFO_CONFIG, mask, value );
}

uint8_t smoke_get_write_ptr ( smoke_t *ctx )
{
    return smoke_read_data( ctx, SMOKE_FIFO_WRITE_PTR );
}

uint8_t smoke_get_read_ptr ( smoke_t *ctx )
{
    return smoke_read_data( ctx, SMOKE_FIFO_READ_PTR );
}

float smoke_read_temp_c ( smoke_t *ctx )
{
    float result;
    uint8_t temp_int;
    uint8_t temp_frac;

    smoke_write_data( ctx, SMOKE_DIE_TEMP_CONFIG, 0x01 );

    temp_int = smoke_read_data( ctx, SMOKE_DIE_TEMP_INT );
    temp_frac = smoke_read_data( ctx, SMOKE_DIE_TEMP_FRAC );

    result = ( float )temp_int + ( ( float )temp_frac * 0.0625 );

    return result;
}

float smoke_read_temp_f ( smoke_t *ctx )
{
    float result = smoke_read_temp_c( ctx );

    result = result * 1.8 + 32.0;

    return result;
}

void smoke_reset ( smoke_t *ctx )
{
    smoke_set_new_value( ctx, SMOKE_MODE_CONFIG, SMOKE_RESET_MASK, SMOKE_RESET );
}

uint8_t smoke_read_device_id ( smoke_t *ctx )
{
    uint8_t result;
    result = smoke_read_data( ctx, SMOKE_PART_ID );
    return result;
} 

uint32_t smoke_get_red_val ( smoke_t *ctx )
{
    uint8_t r_buffer[ 3 ];
    uint8_t w_buffer[ 1 ];
    uint32_t result;

    w_buffer[ 0 ] = SMOKE_FIFO_DATA;

    i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, r_buffer, 3 );

    result = r_buffer[ 2 ];
    result <<= 8;
    result |= r_buffer[ 1 ];
    result <<= 8;
    result |= r_buffer[ 0 ];
    result &= 0xFFFFFF;

    return result;
}

uint32_t smoke_get_ir_val ( smoke_t *ctx )
{
    uint8_t r_buffer[ 6 ];
    uint8_t w_buffer[ 1 ];
    uint32_t result;
    
    w_buffer[ 0 ] = SMOKE_FIFO_DATA;

    i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, r_buffer, 6 );

    result = r_buffer[ 5 ];
    result <<= 8;
    result |= r_buffer[ 4 ];
    result <<= 8;
    result |= r_buffer[ 3 ];
    result &= 0xFFFFFF;

    return result;
}

uint32_t smoke_get_green_val ( smoke_t *ctx )
{
    uint8_t r_buffer[ 9 ];
    uint8_t w_buffer[ 1 ];
    uint32_t result = 0;
    
    w_buffer[ 0 ] = SMOKE_FIFO_DATA;

    i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, r_buffer, 9 );

    result = r_buffer[ 8 ];
    result <<= 8;
    result |= r_buffer[ 7 ];
    result <<= 8;
    result |= r_buffer[ 6 ];
    result &= 0xFFFFFF;
    
    return result;
}

void smoke_read_fifo_data ( smoke_t *ctx, uint32_t *red_res, uint32_t *ir_res, uint32_t *grn_res )
{
    uint8_t r_buffer[ 9 ];
    uint8_t w_buffer[ 1 ];
    uint8_t led_num;
    uint32_t temp_rd;
    temp_rd = 0;
    
    w_buffer[ 0 ] = SMOKE_FIFO_DATA;
    smoke_clear_fifo( ctx );
    led_num = smoke_read_data( ctx, SMOKE_MODE_CONFIG );
    led_num &= 0x07;

    if ( led_num == SMOKE_MODE_REDONLY )
    {
        i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, r_buffer, 3 );

        temp_rd = r_buffer[ 2 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 1 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 0 ];
        *red_res = temp_rd;
    }
    else if ( led_num == SMOKE_MODE_REDIRONLY )
    {
        i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, r_buffer, 6 );

        temp_rd = r_buffer[ 2 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 1 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 0 ];
        *red_res = temp_rd;
         
        temp_rd = r_buffer[ 5 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 4 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 3 ];
        *ir_res = temp_rd;
    }
    else if ( led_num == SMOKE_MODE_MULTILED )
    {
        i2c_master_write_then_read( &ctx->i2c, w_buffer, 1, r_buffer, 9 );

        temp_rd = r_buffer[ 2 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 1 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 0 ];
        *red_res = temp_rd;

        temp_rd = r_buffer[ 5 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 4 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 3 ];
        *ir_res = temp_rd;

        temp_rd = r_buffer[ 8 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 7 ];
        temp_rd <<= 8;
        temp_rd |= r_buffer[ 6 ];
        *grn_res = temp_rd;
    }
}

void smoke_set_registers ( smoke_t *ctx, smoke_set_registers_t *registers )
{
    smoke_fifo_setting( ctx, 2, registers->avg_samp );
    smoke_fifo_setting( ctx, 1, 0 );
    smoke_setting_function( ctx, 2, registers->mode );
    smoke_setting_function( ctx, 3, registers->adc_range );   
    smoke_setting_function( ctx, 4, registers->samp_rate );
    smoke_setting_function( ctx, 5, registers->pulse_width );
    smoke_setting_prox_and_amp( ctx, 0, registers->led_pow_lvl );
    smoke_setting_prox_and_amp( ctx, 1, registers->led_pow_lvl );
    smoke_setting_prox_and_amp( ctx, 2, registers->led_pow_lvl );
    smoke_setting_prox_and_amp( ctx, 3, registers->led_pow_lvl );

    smoke_enable_slot( ctx, 1, SMOKE_SLOT_RED_LED );

    if ( registers->mode > 2 )
    {
        smoke_enable_slot( ctx, 1, SMOKE_SLOT_RED_LED );
        smoke_enable_slot( ctx, 2, SMOKE_SLOT_IR_LED );
    }
    if ( registers->mode > 3 )
    {
        smoke_enable_slot( ctx, 1, SMOKE_SLOT_RED_LED );
        smoke_enable_slot( ctx, 2, SMOKE_SLOT_IR_LED );
        smoke_enable_slot( ctx, 3, SMOKE_SLOT_GREEN_LED );
    }

    smoke_clear_fifo( ctx );
}

uint8_t smoke_check_int ( smoke_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

