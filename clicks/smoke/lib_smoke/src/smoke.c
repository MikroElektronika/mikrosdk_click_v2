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

//------------------------------------------------- PRIVATE FUNCTIONS

/**
 * @brief Set new value function
 *
 * @param ctx         Click object.
 * @param reg         8-bit register address
 * @param mask        8-bit value used as a mask
 * @param value       8-bit data to be written into register
 *
 * @description Function is used to apply new values.
**/
void dev_set_new_value ( smoke_t *ctx, uint8_t reg, uint8_t mask, uint8_t value );

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
    
    ctx->num_en_led = 0;
    ctx->red_value = 0;
    ctx->ir_value = 0;
    ctx->green_value = 0;

    return SMOKE_OK;
}

void smoke_default_cfg ( smoke_t *ctx )
{
    smoke_set_registers_t default_configuration;
    
    smoke_reset( ctx );
    Delay_100ms( );
    
    default_configuration.avg_samp = SMOKE_SAMPLEAVG_4; 
    default_configuration.mode = SMOKE_MODE_MULTILED;
    default_configuration.adc_range = SMOKE_ADCRANGE_16384;
    default_configuration.samp_rate = SMOKE_SAMPLERATE_50;
    default_configuration.pulse_width = SMOKE_PULSEWIDTH_411;
    default_configuration.led_pow_lvl = 0xFF;
    
    uint8_t status = smoke_set_registers( ctx, &default_configuration );
    
    if ( status != SMOKE_OK )
        for( ; ; );
    
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

void smoke_generic_read ( smoke_t *ctx, uint8_t rd_addr, uint8_t *buffer, uint8_t cnt )
{
    i2c_master_write_then_read( &ctx->i2c, &rd_addr, 1, buffer, cnt );
}

void smoke_set_new_value ( smoke_t *ctx, smoke_set_new_value_t *new_value_data )
{
    uint8_t old_val;

    old_val = smoke_read_data( ctx, new_value_data->reg_addr );
    old_val = old_val & new_value_data->mask;

    smoke_write_data( ctx, new_value_data->reg_addr, old_val | new_value_data->value );
}

uint8_t smoke_get_intrrupt ( smoke_t *ctx, uint8_t flag )
{
    if ( flag == SMOKE_INT_FLAG_GET_MAIN )
    {
        // Get the main interrupt group 
        return smoke_read_data( ctx, SMOKE_INT_STAT1 );
    }
    if ( flag == SMOKE_INT_FLAG_GET_TEMP_DATA )
    {
        // Get the temporary ready interrupt
        return smoke_read_data( ctx, SMOKE_INT_STAT2 );
    }
    else
    {
        return SMOKE_PARAMETER_ERROR;
    }
}

uint8_t smoke_enable_disable_interrupts ( smoke_t *ctx, uint8_t interrupt_flag, uint8_t enable_flag )
{
    smoke_set_new_value_t interrupt_data;
    
    if ( interrupt_flag == SMOKE_INT_FLAG_SET_AFULL )
    {
        interrupt_data.reg_addr = SMOKE_INT_STAT1;
        interrupt_data.mask = SMOKE_INT_A_FULL_MASK;
        
        if ( enable_flag == SMOKE_INT_FLAG_SET_ENABLE )
        {
            interrupt_data.value = SMOKE_INT_A_FULL_ENABLE;
        }
        else if ( enable_flag == SMOKE_INT_FLAG_SET_DISABLE )
        {
            interrupt_data.value = SMOKE_INT_A_FULL_DISABLE;
        }
        else
        {
            return SMOKE_PARAMETER_ERROR;
        }
    }
    else if ( interrupt_flag == SMOKE_INT_FLAG_SET_DATA_RDY )
    {
        interrupt_data.reg_addr = SMOKE_INT_STAT1;
        interrupt_data.mask = SMOKE_INT_DATA_RDY_MASK;
        
        if ( enable_flag == SMOKE_INT_FLAG_SET_ENABLE )
        {
            interrupt_data.value = SMOKE_INT_DATA_RDY_ENABLE;
        }
        else if ( enable_flag == SMOKE_INT_FLAG_SET_DISABLE )
        {
            interrupt_data.value = SMOKE_INT_DATA_RDY_DISABLE;
        }
        else
        {
            return SMOKE_PARAMETER_ERROR;
        }
    }
    else if ( interrupt_flag == SMOKE_INT_FLAG_SET_ALS_OVF )
    {
        interrupt_data.reg_addr = SMOKE_INT_STAT1;
        interrupt_data.mask = SMOKE_INT_ALC_OVF_MASK;
        
        if ( enable_flag == SMOKE_INT_FLAG_SET_ENABLE )
        {
            interrupt_data.value = SMOKE_INT_ALC_OVF_ENABLE;
        }
        else if ( enable_flag == SMOKE_INT_FLAG_SET_DISABLE )
        {
            interrupt_data.value = SMOKE_INT_ALC_OVF_DISABLE;
        }
        else
        {
            return SMOKE_PARAMETER_ERROR;
        }
    }
    else if ( interrupt_flag == SMOKE_INT_FLAG_SET_PROXY_THRESH )
    {
        interrupt_data.reg_addr = SMOKE_INT_STAT1;
        interrupt_data.mask = SMOKE_INT_PROX_INT_MASK;
        
        if ( enable_flag == SMOKE_INT_FLAG_SET_ENABLE )
        {
            interrupt_data.value = SMOKE_INT_PROX_INT_ENABLE;
        }
        else if ( enable_flag == SMOKE_INT_FLAG_SET_DISABLE )
        {
            interrupt_data.value = SMOKE_INT_PROX_INT_DISABLE;
        }
        else
        {
            return SMOKE_PARAMETER_ERROR;
        }
    }
    else if ( interrupt_flag == SMOKE_INT_FLAG_SET_TEMP )
    {
        interrupt_data.reg_addr = SMOKE_INT_STAT2;
        interrupt_data.mask = SMOKE_INT_DIE_TEMP_RDY_MASK;
        
        if ( enable_flag == SMOKE_INT_FLAG_SET_ENABLE )
        {
            interrupt_data.value = SMOKE_INT_DIE_TEMP_RDY_ENABLE;
        }
        else if ( enable_flag == SMOKE_INT_FLAG_SET_DISABLE )
        {
            interrupt_data.value = SMOKE_INT_DIE_TEMP_RDY_DISABLE;
        }
        else
        {
            return SMOKE_PARAMETER_ERROR;
        }
    }
    else
    {
        return SMOKE_PARAMETER_ERROR;
    }
    
    smoke_set_new_value( ctx, &interrupt_data );
    return SMOKE_OK;
}

uint8_t smoke_read_device_id ( smoke_t *ctx )
{
    uint8_t result;
    result = smoke_read_data( ctx, SMOKE_PART_ID );
    return result;
} 

void smoke_reset ( smoke_t *ctx )
{
    dev_set_new_value( ctx, SMOKE_REG_MODE_CONFIG, SMOKE_RESET_MASK, SMOKE_RESET );

    for( ; ; ) 
    {
        if ( ( smoke_read_data( ctx, SMOKE_REG_MODE_CONFIG ) & SMOKE_RESET ) == 0 ) 
            break;
        Delay_1ms(  );
    }
}

float smoke_read_temp ( smoke_t *ctx )
{
    float result;
    uint8_t temp_int;
    uint8_t temp_frac;

    smoke_write_data( ctx, SMOKE_DIE_TEMP_CONFIG, 0x01 );
    
    for ( ; ; )
    {
        if ( ( smoke_read_data( ctx, SMOKE_DIE_TEMP_CONFIG ) & 0x01 ) == 0 ) 
            break;
        Delay_1ms(  );
    }

    temp_int = smoke_read_data( ctx, SMOKE_DIE_TEMP_INT );
    temp_frac = smoke_read_data( ctx, SMOKE_DIE_TEMP_FRAC );

    result = ( float )temp_int + ( ( float )temp_frac * 0.0625 );

    return result;
}

uint8_t smoke_set_power ( smoke_t *ctx, uint8_t state )
{
    if ( ( state != SMOKE_SHUTDOWN ) && ( state != SMOKE_WAKEUP ) )
        return SMOKE_PARAMETER_ERROR;
    
    dev_set_new_value( ctx, SMOKE_REG_MODE_CONFIG, SMOKE_SHUTDOWN_MASK, state );
    
    return SMOKE_OK;
}

uint8_t smoke_set_led_mode ( smoke_t *ctx, uint8_t mode )
{
    if ( ( mode != SMOKE_MODE_REDONLY ) && 
         ( mode != SMOKE_MODE_REDIRONLY ) && 
         ( mode != SMOKE_MODE_MULTILED ) )
        return SMOKE_PARAMETER_ERROR;
    
    dev_set_new_value( ctx, SMOKE_REG_MODE_CONFIG, SMOKE_MODE_MASK, mode );
    
    return SMOKE_OK;
}

uint8_t smoke_set_adc_range ( smoke_t *ctx, uint8_t adc_range )
{
    if ( ( adc_range != SMOKE_ADCRANGE_2048 ) && 
         ( adc_range != SMOKE_ADCRANGE_4096 ) && 
         ( adc_range != SMOKE_ADCRANGE_8192 ) && 
         ( adc_range != SMOKE_ADCRANGE_16384 ) )
        return SMOKE_PARAMETER_ERROR;
    
    dev_set_new_value( ctx, SMOKE_REG_PARTICLE_CONFIG, SMOKE_ADCRANGE_MASK, adc_range );
    
    return SMOKE_OK;
}

uint8_t smoke_set_sample_rate ( smoke_t *ctx, uint8_t sample_rate )
{
    if ( ( sample_rate != SMOKE_SAMPLERATE_50 ) && 
         ( sample_rate != SMOKE_SAMPLERATE_100 ) && 
         ( sample_rate != SMOKE_SAMPLERATE_200 ) && 
         ( sample_rate != SMOKE_SAMPLERATE_400 ) && 
         ( sample_rate != SMOKE_SAMPLERATE_800 ) && 
         ( sample_rate != SMOKE_SAMPLERATE_1000 ) && 
         ( sample_rate != SMOKE_SAMPLERATE_1600 ) && 
         ( sample_rate != SMOKE_SAMPLERATE_3200 ) )
        return SMOKE_PARAMETER_ERROR;
    
    dev_set_new_value( ctx, SMOKE_REG_PARTICLE_CONFIG, SMOKE_SAMPLERATE_MASK, sample_rate );
    
    return SMOKE_OK;
}

uint8_t smoke_set_pulse_width ( smoke_t *ctx, uint8_t pulse_width )
{
    if ( ( pulse_width != SMOKE_PULSEWIDTH_69 ) && 
         ( pulse_width != SMOKE_PULSEWIDTH_118 ) && 
         ( pulse_width != SMOKE_PULSEWIDTH_215 ) && 
         ( pulse_width != SMOKE_PULSEWIDTH_411 ) )
        return SMOKE_PARAMETER_ERROR;
    
    dev_set_new_value( ctx, SMOKE_REG_PARTICLE_CONFIG, SMOKE_PULSEWIDTH_MASK, pulse_width );
    
    return SMOKE_OK;
}

uint8_t smoke_set_led_amplitude ( smoke_t *ctx, uint8_t led, uint8_t amplitude )
{    
    if ( ( led != SMOKE_REG_LED_RED_PULSE_AMP ) && 
         ( led != SMOKE_REG_LED_IR_PULSE_AMP ) && 
         ( led != SMOKE_REG_LED_GREEN_PULSE_AMP ) && 
         ( led != SMOKE_REG_LED_PROX_AMP ) )
        return SMOKE_PARAMETER_ERROR;
    
    smoke_write_data( ctx, led, amplitude );
    
    return SMOKE_OK;
}

void smoke_set_proximity_threshold( smoke_t *ctx, uint8_t threshold )
{
    smoke_write_data( ctx, SMOKE_REG_LED_PROX_THRESH, threshold );
}

uint8_t smoke_enable_slot ( smoke_t *ctx, uint8_t slot_num, uint8_t dev )
{
    if ( dev > SMOKE_SLOT_GREEN_PILOT )
        return SMOKE_PARAMETER_ERROR;
    
    switch ( slot_num )
    {
        case 1:
        {
            dev_set_new_value( ctx, SMOKE_REG_MULTI_LED_CONFIG1, SMOKE_SLOT1_MASK, dev );
            return SMOKE_OK;
        }
        case 2:
        {
            dev_set_new_value( ctx, SMOKE_REG_MULTI_LED_CONFIG1, SMOKE_SLOT2_MASK, dev << 4 );
            return SMOKE_OK;
        }
        case 3:
        {
            dev_set_new_value( ctx, SMOKE_REG_MULTI_LED_CONFIG2, SMOKE_SLOT3_MASK, dev );
            return SMOKE_OK;
        }
        case 4:
        {
            dev_set_new_value( ctx, SMOKE_REG_MULTI_LED_CONFIG2, SMOKE_SLOT4_MASK, dev << 4 );
            return SMOKE_OK;
        }
        default:
        {
            return SMOKE_PARAMETER_ERROR;
        }
    }
}

void smoke_disable_slots ( smoke_t *ctx )
{
    smoke_write_data( ctx, SMOKE_REG_MULTI_LED_CONFIG1, 0 );
    smoke_write_data( ctx, SMOKE_REG_MULTI_LED_CONFIG2, 0 );
}

void smoke_clear_fifo ( smoke_t *ctx )
{
    smoke_write_data( ctx, SMOKE_FIFO_WRITE_PTR, 0 );
    smoke_write_data( ctx, SMOKE_FIFO_OVERFLOW, 0 );
    smoke_write_data( ctx, SMOKE_FIFO_READ_PTR, 0 );
}

uint8_t smoke_get_write_ptr ( smoke_t *ctx )
{
    return smoke_read_data( ctx, SMOKE_FIFO_WRITE_PTR );
}

uint8_t smoke_get_read_ptr ( smoke_t *ctx )
{
    return smoke_read_data( ctx, SMOKE_FIFO_READ_PTR );
}

uint8_t smoke_set_rollover_state( smoke_t *ctx, uint8_t state )
{
    if ( ( state != SMOKE_ROLLOVER_ENABLE ) && ( SMOKE_ROLLOVER_ENABLE != SMOKE_ROLLOVER_DISABLE ) )
        return SMOKE_PARAMETER_ERROR;
    
    dev_set_new_value( ctx, SMOKE_REG_FIFO_CONFIG, SMOKE_ROLLOVER_MASK, state );
    
    return SMOKE_OK;
}

uint8_t smoke_set_almost_full_trigger( smoke_t *ctx, uint8_t trigger_range )
{
    if ( trigger_range > 0x0F )
        return SMOKE_PARAMETER_ERROR;
    
    dev_set_new_value( ctx, SMOKE_REG_FIFO_CONFIG, SMOKE_A_FULL_MASK, trigger_range );
    
    return SMOKE_OK;
}

uint8_t smoke_set_sample_avarage ( smoke_t *ctx, uint8_t samples )
{
    if ( ( samples != SMOKE_SAMPLEAVG_1 ) && 
         ( samples != SMOKE_SAMPLEAVG_2 ) && 
         ( samples != SMOKE_SAMPLEAVG_4 ) && 
         ( samples != SMOKE_SAMPLEAVG_8 ) && 
         ( samples != SMOKE_SAMPLEAVG_16 ) && 
         ( samples != SMOKE_SAMPLEAVG_32 ) )
        return SMOKE_PARAMETER_ERROR;
    
    dev_set_new_value( ctx, SMOKE_REG_FIFO_CONFIG, SMOKE_SAMPLEAVG_MASK, samples );
    
    return SMOKE_OK;
}

uint8_t smoke_set_registers ( smoke_t *ctx, smoke_set_registers_t *registers )
{    
    ctx->num_en_led = 0;
    
    if ( smoke_set_sample_avarage( ctx, registers->avg_samp ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    
    if ( smoke_set_rollover_state( ctx, SMOKE_ROLLOVER_ENABLE ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    
    switch ( registers->mode )
    {
        case SMOKE_MODE_REDONLY:
        {
            ctx->num_en_led = 1;
            smoke_set_led_mode( ctx, registers->mode );
            break;
        }
        case SMOKE_MODE_REDIRONLY:
        {
            ctx->num_en_led = 2;
            smoke_set_led_mode( ctx, registers->mode );
            break;
        }
        case SMOKE_MODE_MULTILED:
        {
            ctx->num_en_led = 3;
            smoke_set_led_mode( ctx, registers->mode );
            break;
        }
        default:
        {
            return SMOKE_PARAMETER_ERROR;
        }
    }
    
    if ( smoke_set_adc_range( ctx, registers->adc_range ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    
    if ( smoke_set_sample_rate( ctx, registers->samp_rate ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    
    if ( smoke_set_pulse_width( ctx, registers->pulse_width ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    
    if ( smoke_set_led_amplitude( ctx, SMOKE_REG_LED_RED_PULSE_AMP, registers->led_pow_lvl ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    if ( smoke_set_led_amplitude( ctx, SMOKE_REG_LED_IR_PULSE_AMP, registers->led_pow_lvl ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    if ( smoke_set_led_amplitude( ctx, SMOKE_REG_LED_GREEN_PULSE_AMP, registers->led_pow_lvl ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    if ( smoke_set_led_amplitude( ctx, SMOKE_REG_LED_PROX_AMP, registers->led_pow_lvl ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    
    
    if ( smoke_enable_slot( ctx, 1, SMOKE_SLOT_RED_PILOT ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    if ( smoke_enable_slot( ctx, 2, SMOKE_SLOT_IR_PILOT ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    if ( smoke_enable_slot( ctx, 3, SMOKE_SLOT_GREEN_PILOT ) != SMOKE_OK )
        return SMOKE_PARAMETER_ERROR;
    
    smoke_clear_fifo( ctx );
    
    return SMOKE_OK;
}

uint8_t smoke_read_leds ( smoke_t *ctx )
{
    uint8_t temp[ 9 ] = { 0 };
    uint8_t temp_led[ 4 ] = { 0 };
        
    if ( ctx->num_en_led == 0 )
    {
        return SMOKE_INIT_ERROR;
    }
    
    smoke_generic_read( ctx, SMOKE_FIFO_DATA, temp, ctx->num_en_led * 3 );
    
    temp_led[ 3 ] = 0;
    
    if ( ctx->num_en_led > 0 )
    {
        temp_led[ 2 ] = temp[ 0 ];
        temp_led[ 1 ] = temp[ 1 ];
        temp_led[ 0 ] = temp[ 2 ];
        memcpy( &ctx->red_value, temp_led, 4 );
    }
    
    if ( ctx->num_en_led > 1 )
    {
        temp_led[ 2 ] = temp[ 3 ];
        temp_led[ 1 ] = temp[ 4 ];
        temp_led[ 0 ] = temp[ 5 ];
        memcpy( &ctx->ir_value, temp_led, 4 );
    }
    
    if ( ctx->num_en_led > 2 )
    {
        temp_led[ 2 ] = temp[ 6 ];
        temp_led[ 1 ] = temp[ 7 ];
        temp_led[ 0 ] = temp[ 8 ];
        memcpy( &ctx->green_value, temp_led, 4 );
    }
    
    if ( ctx->num_en_led > 3 )
    {
        return SMOKE_INIT_ERROR;
    }
    
    return SMOKE_OK;
}

uint8_t smoke_check_int ( smoke_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

//--------------------------------------------------------------------------PRIVATE FUNCTIONS

void dev_set_new_value ( smoke_t *ctx, uint8_t reg, uint8_t mask, uint8_t value )
{
    uint8_t old_val;

    old_val = smoke_read_data( ctx, reg );
    old_val = old_val & mask;

    smoke_write_data( ctx, reg, old_val | value );
}

// ------------------------------------------------------------------------- END

