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

#include "brushless7.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t dev_get_max_speed_rpm ( uint8_t reg_14_val );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void brushless7_cfg_setup ( brushless7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = BRUSHLESS7_SLAVE_ADDR;
}

BRUSHLESS7_RETVAL brushless7_init ( brushless7_t *ctx, brushless7_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return BRUSHLESS7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->pwm, cfg->pwm );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->cs );

    return BRUSHLESS7_OK;
}

void brushless7_default_cfg ( brushless7_t *ctx )
{
    uint8_t tmp;

    tmp = 0x00;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_0, &tmp, 1 );
    tmp = 0x00;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_1, &tmp, 1 );
    tmp = 0x0F;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_2, &tmp, 1 );
    tmp = 0x33;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_3, &tmp, 1 );
    tmp = 0x00;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_4, &tmp, 1 );
    tmp = 0xCC;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_5, &tmp, 1 );
    tmp = 0x33;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_6, &tmp, 1 );
    tmp = 0x08;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_7, &tmp, 1 );
    tmp = 0x12;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_8, &tmp, 1 );
    tmp = 0x00;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_9, &tmp, 1 );
    tmp = 0x00;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_10, &tmp, 1 );
    tmp = 0x00;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_11, &tmp, 1 );
    tmp = 0x7F;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_12, &tmp, 1 );
    tmp = 0x7F;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_13, &tmp, 1 );
    tmp = 0x37;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_14, &tmp, 1 );
    tmp = 0x11;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_15, &tmp, 1 );
    tmp = 0x10;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_16, &tmp, 1 );
    tmp = 0xC3;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_17, &tmp, 1 );
    tmp = 0x01;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_18, &tmp, 1 );
    tmp = 0x02;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_19, &tmp, 1 );
    tmp = 0xA2;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_20, &tmp, 1 );
    tmp = 0x0C;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_21, &tmp, 1 );
    tmp = 0x82;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_22, &tmp, 1 );
    tmp = 0x3F;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_23, &tmp, 1 );
    tmp = 0x40;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_24, &tmp, 1 );
}

void brushless7_generic_write ( brushless7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void brushless7_generic_read ( brushless7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void brushless7_set_sby_pin_state ( brushless7_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->cs, state );
}

uint8_t brushless7_get_int_pin_state ( brushless7_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t brushless7_start_duty ( brushless7_t *ctx, float duty_ptc )
{
    uint8_t temp_data = 0;
    volatile float temp_duty = 0;

    if ( ( BRUSHLESS7_START_DUTY_MAX < duty_ptc ) || ( BRUSHLESS7_ZERO > duty_ptc ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }
    
    temp_duty = duty_ptc / 100;

    temp_data = temp_duty * BRUSHLESS7_START_DUTY_AMP;

    brushless7_generic_write( ctx, BRUSHLESS7_REG_3, &temp_data, 1 );
    
    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_stop_duty ( brushless7_t *ctx, float duty_ptc )
{
    uint8_t stop_data = 0;
    uint8_t temp_data = 0;
    volatile float temp_duty = 0;

    if ( ( BRUSHLESS7_STOP_DUTY_MAX < duty_ptc ) || ( BRUSHLESS7_ZERO > duty_ptc ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }
    temp_duty = duty_ptc / 100;
    brushless7_generic_read( ctx, BRUSHLESS7_REG_2, &temp_data, 1 );
    temp_data &= 0x80;
    stop_data = temp_duty * BRUSHLESS7_STOP_DUTY_AMP;
    temp_data |= stop_data;
    brushless7_generic_write( ctx, BRUSHLESS7_REG_2, &temp_data, 1 );
    
    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_change_duty ( brushless7_t *ctx, float duty_ptc )
{
    uint8_t temp_data = 0;
    volatile float temp_duty = 0;

    if ( ( BRUSHLESS7_CHANGE_DUTY_MAX < duty_ptc ) || ( BRUSHLESS7_CHANGE_DUTY_MIN > duty_ptc ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }
    temp_duty = duty_ptc / BRUSHLESS7_PRECENTAGE_DIV;
    temp_data = temp_duty * BRUSHLESS7_CHANGE_DUTY_AMP;

    brushless7_generic_write( ctx, BRUSHLESS7_REG_4, &temp_data, 1 );
    
    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_max_duty ( brushless7_t *ctx, float duty_ptc )
{
    uint8_t temp_data = 0;
    volatile float temp_duty = 0;

    if ( ( BRUSHLESS7_MAX_DUTY_MAX < duty_ptc ) || ( BRUSHLESS7_MAX_DUTY_MIN > duty_ptc ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }

    temp_duty = duty_ptc / BRUSHLESS7_PRECENTAGE_DIV;
    temp_data = temp_duty * BRUSHLESS7_STOP_DUTY_AMP;

    brushless7_generic_write( ctx, BRUSHLESS7_REG_5, &temp_data, 1 );
    
    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_start_rpm ( brushless7_t *ctx, uint16_t rpm_val )
{
    uint8_t lsb_data = 0;
    uint8_t msb_data = 0;
    uint8_t temp_data;

    if ( ( BRUSHLESS7_START_RPM_MAX < rpm_val ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }

    brushless7_generic_read( ctx, BRUSHLESS7_REG_7, &temp_data, 1 );

    lsb_data = ( uint8_t )( rpm_val & 0x00FF );

    msb_data = rpm_val >> 8;
    msb_data <<= 4;
    temp_data &= BRUSHLESS7_START_RPM_MASK;
    temp_data |= msb_data;

    brushless7_generic_write( ctx, BRUSHLESS7_REG_6, &lsb_data, 1 );
    brushless7_generic_write( ctx, BRUSHLESS7_REG_7, &temp_data, 1 );
    
    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_max_speed_rpm ( brushless7_t *ctx, uint8_t max_speed_rpm )
{
    uint8_t temp_data = 0;

    if ( !( ( BRUSHLESS7_MAX_SPEED_4096 == max_speed_rpm  ) || 
            ( BRUSHLESS7_MAX_SPEED_8192 == max_speed_rpm  ) ||
            ( BRUSHLESS7_MAX_SPEED_16384 == max_speed_rpm  ) ||
            ( BRUSHLESS7_MAX_SPEED_32768 == max_speed_rpm  ) ) )
    {
        return BRUSHLESS7_DEV_ERROR;
    }

    brushless7_generic_read( ctx, BRUSHLESS7_REG_14, &temp_data, 1 );

    temp_data &= BRUSHLESS7_MAX_SPEED_RMP_MASK;
    temp_data |= max_speed_rpm;

    brushless7_generic_write( ctx, BRUSHLESS7_REG_14, &temp_data, 1 );

    return BRUSHLESS7_DEV_OK;
}

uint8_t brushless7_rotating_direction ( brushless7_t *ctx, uint8_t direction_rot )
{
    uint8_t temp_data;
    brushless7_generic_read( ctx, BRUSHLESS7_REG_14, &temp_data, 1 );
    switch ( direction_rot )
    {
        case BRUSHLESS7_DIR_CW:
        {
            temp_data &= 0xBF;
            brushless7_generic_write( ctx, BRUSHLESS7_REG_14, &temp_data, 1 );
            return BRUSHLESS7_DEV_OK;
        }
        case BRUSHLESS7_DIR_CCW:
        {
            temp_data |= 0x40;
            brushless7_generic_write( ctx, BRUSHLESS7_REG_14, &temp_data, 1 );
            return BRUSHLESS7_DEV_OK;
        }
        default:
        {
            return BRUSHLESS7_DEV_ERROR;
        }
    }
}

uint8_t brushless7_control_mode_set ( brushless7_t *ctx, uint8_t ctrl_type )
{
    uint8_t ctrl_mode_data1;
    uint8_t ctrl_mode_data2;
    uint8_t ctrl_mode_data3;

    switch ( ctrl_type )
    {
        case BRUSHLESS7_CTRL_TYPE_RPM:
        {
            brushless7_generic_read( ctx, BRUSHLESS7_REG_2, &ctrl_mode_data1, 1 );
            brushless7_generic_read( ctx, BRUSHLESS7_REG_9, &ctrl_mode_data2, 1 );
            brushless7_generic_read( ctx, BRUSHLESS7_REG_11, &ctrl_mode_data3, 1 );
            ctrl_mode_data1 |= 0x80;
            ctrl_mode_data2 &= 0xFC;
            ctrl_mode_data3 &= 0xFE;
            brushless7_generic_write( ctx, BRUSHLESS7_REG_2, &ctrl_mode_data1, 1 );
            brushless7_generic_write( ctx, BRUSHLESS7_REG_9, &ctrl_mode_data2, 1 );
            brushless7_generic_write( ctx, BRUSHLESS7_REG_11, &ctrl_mode_data3, 1 );
            return BRUSHLESS7_DEV_OK;
        }
        case BRUSHLESS7_CTRL_TYPE_DUTY:
        {
            brushless7_generic_read( ctx, BRUSHLESS7_REG_2, &ctrl_mode_data1, 1 );
            brushless7_generic_read( ctx, BRUSHLESS7_REG_9, &ctrl_mode_data2, 1 );
            brushless7_generic_read( ctx, BRUSHLESS7_REG_11, &ctrl_mode_data3, 1 );
            ctrl_mode_data1 |= 0x80;
            ctrl_mode_data2 &= 0xFC;
            ctrl_mode_data2 |= 0x01;
            ctrl_mode_data3 |= 0x01;
            brushless7_generic_write( ctx, BRUSHLESS7_REG_2, &ctrl_mode_data1, 1 );
            brushless7_generic_write( ctx, BRUSHLESS7_REG_9, &ctrl_mode_data2, 1 );
            brushless7_generic_write( ctx, BRUSHLESS7_REG_11, &ctrl_mode_data3, 1 );
            return BRUSHLESS7_DEV_OK;
        }
        case BRUSHLESS7_CTRL_TYPE_STOP:
        {
            brushless7_generic_read( ctx, BRUSHLESS7_REG_2, &ctrl_mode_data1, 1 );
            brushless7_generic_read( ctx, BRUSHLESS7_REG_9, &ctrl_mode_data2, 1 );
            ctrl_mode_data1 &= 0x7F;
            ctrl_mode_data2 &= 0xFC;
            brushless7_generic_write( ctx, BRUSHLESS7_REG_2, &ctrl_mode_data1, 1 );
            brushless7_generic_write( ctx, BRUSHLESS7_REG_9, &ctrl_mode_data2, 1 );
            return BRUSHLESS7_DEV_OK;
        }
        default:
        {
            return BRUSHLESS7_DEV_ERROR;
        }
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t dev_get_max_speed_rpm ( uint8_t reg_14_val )
{
    switch ( reg_14_val )
    {
        case BRUSHLESS7_MAX_SPEED_4096:
        {
            return 4096;
        }
        case BRUSHLESS7_MAX_SPEED_8192:
        {    
            return 8192;
        }
        case BRUSHLESS7_MAX_SPEED_16384:
        { 
            return 16384;
        }
        case BRUSHLESS7_MAX_SPEED_32768:
        { 
            return 32768;
        }
        default:
        {
            return BRUSHLESS7_DEV_ERROR;
        }
    }
}

// ------------------------------------------------------------------------- END

