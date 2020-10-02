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
 * \file fan2.c
 *
 */

#include "fan2.h"


// ------------------------------------------------------------- PRIVATE MACROS

//  Temperature and speed (PWM duty cycle) register resolution.
#define FAN2_RESOL_TEMP_CELS  0.125
#define FAN2_RESOL_SPEED_PER  0.392156862745098

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void
fan2_cfg_setup( fan2_cfg_t *cfg )
{
    cfg->scl     = HAL_PIN_NC;
    cfg->sda     = HAL_PIN_NC;
    cfg->alr     = HAL_PIN_NC;
    cfg->shd     = HAL_PIN_NC;
    cfg->ff      = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_addr  = FAN2_I2C_ADDR_000;
}

fan2_err_t
fan2_init( fan2_t *ctx, fan2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_addr = cfg->i2c_addr;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return FAN2_ERR_INIT_DRV;
    }

    if ( digital_in_init( &ctx->alr,  cfg->alr ) != DIGITAL_IN_SUCCESS )
    {
        return FAN2_ERR_UNSUPPORTED_PIN;
    }

    if ( digital_in_init( &ctx->shd, cfg->shd ) != DIGITAL_IN_SUCCESS )
    {
        return FAN2_ERR_UNSUPPORTED_PIN;
    }

    if ( digital_in_init( &ctx->ff,  cfg->ff ) != DIGITAL_IN_SUCCESS )
    {
        return FAN2_ERR_UNSUPPORTED_PIN;
    }

    if ( digital_in_init( &ctx->int_pin, cfg->int_pin ) != DIGITAL_IN_SUCCESS )
    {
        return FAN2_ERR_UNSUPPORTED_PIN;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_addr );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return FAN2_OK;
}

void
fan2_default_cfg( fan2_t *ctx, fan2_wire_t n_wires )
{
    fan2_generic_write_byte( ctx, FAN2_REG_CTRL1, FAN2_CTRL1_PWM_FREQ_33_HZ |
                                                  FAN2_CTRL1_PWM_POL_POS 
                                                  );
    fan2_generic_write_byte( ctx, FAN2_REG_CTRL2, FAN2_CTRL2_NORMAL_MODE |
                                                  FAN2_CTRL2_ALERT_COMP |
                                                  FAN2_CTRL2_FF_OUTPUT_COMP |
                                                  FAN2_CTRL2_DIRECT_FAN_CTRL_EN 
                                                  );
    if (n_wires == FAN2_WIRES_4)
    {
        fan2_generic_write_byte( ctx, FAN2_REG_CTRL3, FAN2_CTRL3_CLR_FAIL |
                                                      FAN2_CTRL3_PWM_RAMP_RATE_FAST |
                                                      FAN2_CTRL3_PULSE_STRETCH_EN |
                                                      FAN2_CTRL3_TACH1_EN 
                                                      );
    }
    else
    {
        fan2_generic_write_byte( ctx, FAN2_REG_CTRL3, FAN2_CTRL3_CLR_FAIL |
                                                      FAN2_CTRL3_PWM_RAMP_RATE_FAST |
                                                      FAN2_CTRL3_PULSE_STRETCH_EN |
                                                      FAN2_CTRL3_TACH2_EN 
                                                      );
    }
}

fan2_err_t
fan2_generic_write_byte( fan2_t *ctx, uint8_t reg_addr, uint8_t data_in )
{
    uint8_t tmp_data[ 2 ];

    if ( ( ( reg_addr > 0x17 ) && ( reg_addr < 0x20 ) ) ||
         ( ( reg_addr > 0x50 ) && ( reg_addr != 0x5B ) ) )
    {
        return FAN2_ERR_REG_ADDR;
    }

    tmp_data[ 0 ] = reg_addr;
    tmp_data[ 1 ] = data_in;

    i2c_master_write( &ctx->i2c, tmp_data, 2 ); 

    return FAN2_OK;
}

fan2_err_t
fan2_generic_read_byte( fan2_t *ctx, uint8_t reg_addr, uint8_t *data_out )
{
    uint8_t tmp_data;

    if ( ( ( reg_addr > 0x17 ) && ( reg_addr < 0x20 ) ) || ( reg_addr > 0x5A ) )
    {
        return FAN2_ERR_REG_ADDR;
    }

    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, &tmp_data, 1 );

    *data_out = tmp_data;

    return FAN2_OK;
}

fan2_err_t
fan2_generic_write_word( fan2_t *ctx, uint8_t reg_addr, uint16_t data_in )
{
    uint8_t tmp_data[ 3 ];

    if ( ( reg_addr != 0x6 ) && ( reg_addr != 0x8 ) && ( reg_addr != 0xA ) &&
         ( reg_addr != 0xC ) && ( reg_addr != 0xE ) )
    {
        return FAN2_ERR_REG_ADDR;
    }

    tmp_data[ 0 ] = reg_addr;
    tmp_data[ 1 ] = data_in >> 8;
    tmp_data[ 2 ] = data_in;

    i2c_master_write( &ctx->i2c, tmp_data, 3 );  

    return FAN2_OK;
}

fan2_err_t
fan2_generic_read_word( fan2_t *ctx, uint8_t reg_addr, uint16_t data_out )
{
    uint8_t tmp_data[ 2 ];

    if ( ( reg_addr != 0x6 ) && ( reg_addr != 0x8 ) && ( reg_addr != 0xA ) &&
         ( reg_addr != 0xC ) && ( reg_addr != 0xE ) && ( reg_addr != 0x52 ) &&
         ( reg_addr != 0x54 ) && ( reg_addr != 0x56 ) && ( reg_addr != 0x58 ) )
    {
        return FAN2_ERR_REG_ADDR;
    }

    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, tmp_data, 2 );

    data_out = tmp_data[ 0 ];
    data_out <<= 8;
    data_out |= tmp_data[ 1 ];

    return FAN2_OK;
}

fan2_err_t
fan2_read_temp( fan2_t *ctx, uint8_t temp_addr, float *temp_cels )
{
    int16_t temp;
    double res;

    if ( ( temp_addr != 0x6 ) && ( temp_addr != 0x8 ) &&
         ( temp_addr != 0xA ) && ( temp_addr != 0xC ) &&
         ( temp_addr != 0x56 ) && ( temp_addr != 0x58 ) )
    {
        return FAN2_ERR_REG_ADDR;
    }

    fan2_generic_read_word( ctx, temp_addr, temp );

    res = FAN2_RESOL_TEMP_CELS;
    res /= 1 << FAN2_TEMP_DATA_OFFSET;
    res *= temp;

    *temp_cels = (float)res;

    return FAN2_OK;
}

fan2_err_t
fan2_write_temp( fan2_t *ctx, uint8_t temp_addr, float temp_cels )
{
    int16_t temp;
    double res;

    if ( ( temp_addr != 0x6 ) && ( temp_addr != 0x8 ) &&
         ( temp_addr != 0xA ) && ( temp_addr != 0xC ) )
    {
        return FAN2_ERR_REG_ADDR;
    }

    if ( ( temp_cels < -55 ) || ( temp_cels > 125 ) )
    {
        return FAN2_ERR_TEMP_RANGE;
    }

    res = FAN2_RESOL_TEMP_CELS;
    res /= 1 << FAN2_TEMP_DATA_OFFSET;
    temp = temp_cels / res;

    fan2_generic_write_word( ctx, temp_addr, temp & FAN2_TEMP_DATA_MASK );

    return FAN2_OK;
}

fan2_err_t
fan2_read_tacho( fan2_t *ctx, uint8_t tacho_addr, uint32_t *tacho_rpm )
{
    uint16_t tacho;
    double res;

    if ( ( tacho_addr != 0xE ) && ( tacho_addr != 0x52 ) &&
         ( tacho_addr != 0x54 ) )
    {
        return FAN2_ERR_REG_ADDR;
    }

    fan2_generic_read_word( ctx, tacho_addr, tacho );

    res = 100000;
    res /= tacho;
    res /= 4;
    res *= 60;

    *tacho_rpm = (uint32_t)res;

    return FAN2_OK;
}

void
fan2_write_tacho_threshold( fan2_t *ctx, uint32_t tacho_rpm )
{
    uint16_t tacho;
    double res;

    res = 100000;
    res /= tacho_rpm;
    res /= 4;
    tacho = res * 60;

    fan2_generic_write_word( ctx, FAN2_REG_TACH_CNT_THRSH, tacho );
}

fan2_err_t
fan2_direct_speed_control( fan2_t *ctx, float speed_per )
{
    uint8_t duty;

    if ( ( speed_per < 0 ) || ( speed_per > 100 ) )
    {
        return FAN2_ERR_PWM_DUTY_RANGE;
    }

    duty = speed_per / FAN2_RESOL_SPEED_PER;

    fan2_generic_write_byte( ctx, FAN2_REG_DIRECT_DUTY_CYCLE_CTRL, duty );

    return FAN2_OK;
}

float
fan2_read_current_speed( fan2_t *ctx )
{
    uint8_t duty;

    fan2_generic_read_byte( ctx, FAN2_REG_CURRENT_PWM_DUTY_CYCLE, &duty );

    return ( float )duty * FAN2_RESOL_SPEED_PER;
}

uint8_t
fan2_status( fan2_t *ctx, uint8_t flag_mask )
{
    uint8_t stat;

    fan2_generic_read_byte( ctx, FAN2_REG_STATUS, &stat );

    return stat & flag_mask;
}

fan2_err_t
fan2_write_lut( fan2_t *ctx, uint8_t lut_addr, uint8_t *lut_data,
                uint8_t n_data )
{
    uint8_t tmp_data[ 49 ];
    uint8_t cnt;

    if ( ( lut_addr < 0x20 ) || ( lut_addr > 0x4F ) )
    {
        return FAN2_ERR_REG_ADDR;
    }

    if ( ( n_data == 0 ) || ( n_data > 0x50 - lut_addr ) )
    {
        return FAN2_ERR_NDATA;
    }

    tmp_data[ 0 ] = lut_addr;

    for ( cnt = 1; cnt <= n_data; cnt++ )
    {
        tmp_data[ cnt ] = *lut_data;
        lut_data++;
    }

    i2c_master_write( &ctx->i2c, tmp_data, n_data + 1 );   

    return FAN2_OK;
}

void
fan2_sw_reset( fan2_t *ctx )
{
    uint8_t por_state;

    fan2_generic_write_byte( ctx, FAN2_REG_CTRL1, FAN2_CTRL1_SW_POR );
    Delay_1sec( );

    fan2_generic_read_byte( ctx, FAN2_REG_CTRL1, &por_state );

    while ( por_state & FAN2_CTRL1_SW_POR )
    {
        fan2_generic_read_byte( ctx, FAN2_REG_CTRL1, &por_state );
    }
}

uint8_t
fan2_get_alr_pin( fan2_t *ctx )
{
    return digital_in_read( &ctx->alr );
}

uint8_t
fan2_get_shd_pin( fan2_t *ctx )
{
    return digital_in_read( &ctx->shd );
}

uint8_t
fan2_get_ff_pin( fan2_t *ctx )
{
    return digital_in_read( &ctx->ff );
}

uint8_t
fan2_get_int_pin( fan2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------ END
