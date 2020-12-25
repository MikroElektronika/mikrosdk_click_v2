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

#include "grideye.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void grideye_cfg_setup ( grideye_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GRIDEYE_I2C_ADDR;
}

GRIDEYE_RETVAL grideye_init ( grideye_t *ctx, grideye_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return GRIDEYE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return GRIDEYE_OK;
}

void grideye_default_cfg ( grideye_t *ctx )
{
    grideye_set_power_control( ctx, GRIDEYE_PCLT_NORMAL );
    grideye_flag_reset( ctx );
    grideye_set_fps10( ctx );
    Delay_100ms( );
    grideye_write_int_lvl_high( ctx, 0x0030 );
    grideye_write_int_lvl_low( ctx, 0x0015 );
    grideye_write_int_hyst_lvl( ctx, 0x0020 );
    Delay_100ms( ); 
}

void grideye_generic_write ( grideye_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
    Delay_1ms( );
}

void grideye_generic_read ( grideye_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void grideye_write_data ( grideye_t *ctx, uint8_t wr_addr, uint16_t wr_data )
{
    uint8_t buffer[ 2 ];

    buffer[ 0 ] = wr_data & 0xFF;
    buffer[ 1 ] = ( wr_data >> 8 ) & 0x0F;

    grideye_generic_write( ctx, wr_addr, buffer, 2 );
}

uint16_t grideye_read_data ( grideye_t *ctx, uint8_t rd_addr )
{
    uint16_t result;
    uint8_t r_buffer[ 2 ];

    grideye_generic_read( ctx, rd_addr, r_buffer, 2 );
    
    result = r_buffer[ 1 ];
    result <<= 8;
    result |= r_buffer[ 0 ];

    return result;
}

void grideye_read_grid ( grideye_t *ctx, int16_t *buffer )
{
    uint8_t buffer_r[ 128 ]; 
    uint8_t temp = 0;
    uint8_t i;
    
    grideye_generic_read( ctx, 0x80, buffer_r, 128 );
    for( i = 0; i < 64; i++ )
    {
        temp += 2;
        buffer[ i ] = buffer_r[ temp - 1 ] << 8;
        
        buffer[ i ] |= buffer_r[ temp - 2 ];
         
    }
}

uint8_t grideye_check_interrupt ( grideye_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void grideye_set_power_control ( grideye_t *ctx, uint8_t pow_cnt )
{
    grideye_generic_write( ctx, GRIDEYE_PCLT, &pow_cnt, 1 );
}

uint8_t grideye_read_power_control ( grideye_t *ctx )
{
    uint8_t result;

    grideye_generic_read( ctx ,GRIDEYE_PCLT, &result, 1 );

    return result;
}

void grideye_flag_reset ( grideye_t *ctx )
{
    uint8_t tmp;
    tmp = GRIDEYE_RST_FLAG;
    
    grideye_generic_write( ctx, GRIDEYE_RST, &tmp, 1 );
}

void grideye_initial_reset ( grideye_t *ctx )
{
    uint8_t tmp;
    tmp = GRIDEYE_RST_INIT;
     
    grideye_generic_write( ctx, GRIDEYE_RST, &tmp, 1 );
}

void grideye_set_fps1 ( grideye_t *ctx )
{
    uint8_t tmp;
    tmp = GRIDEYE_FPSC_1FPS;
    
    grideye_generic_write( ctx, GRIDEYE_FPSC, &tmp, 1 );
}

void grideye_set_fps10 ( grideye_t *ctx )
{
    uint8_t tmp;
    tmp = GRIDEYE_FPSC_10FPS;
    
    grideye_generic_write( ctx, GRIDEYE_FPSC, &tmp, 1 );
}

uint8_t grideye_check_fps ( grideye_t *ctx )
{
    uint8_t result;

    grideye_generic_read( ctx, GRIDEYE_FPSC, &result, 1 );

    return result;
}

void grideye_set_int_ctl_reg ( grideye_t *ctx, uint8_t int_cnt )
{
    grideye_generic_write( ctx, GRIDEYE_INTC, &int_cnt, 1 );
}

uint8_t grideye_read_int_ctl_reg ( grideye_t *ctx )
{
    uint8_t result;

    grideye_generic_read( ctx, GRIDEYE_INTC, &result, 1 );

    return result;
}

uint8_t grideye_read_stat_reg ( grideye_t *ctx )
{
    uint8_t result;

    grideye_generic_read( ctx, GRIDEYE_STAT, &result, 1 );
    
    return result;
}

void grideye_set_stat_clr_reg ( grideye_t *ctx, uint8_t int_cnt )
{
    grideye_generic_write( ctx, GRIDEYE_SCLR, &int_cnt, 1 );
}

void grideye_set_ave_reg ( grideye_t *ctx, uint8_t mamod )
{
    grideye_generic_write( ctx, GRIDEYE_AVE, &mamod, 1 );
}

uint8_t grideye_read_ave_reg ( grideye_t *ctx )
{
    uint8_t result;

    grideye_generic_read( ctx, GRIDEYE_AVE, &result, 1 );

    return result;
}

void grideye_write_int_lvl_high ( grideye_t *ctx, uint16_t wr_data )
{
    grideye_write_data( ctx, GRIDEYE_INTHL, wr_data );
}

void grideye_write_int_lvl_low ( grideye_t *ctx, uint16_t wr_data )
{
    grideye_write_data( ctx, GRIDEYE_INTLL, wr_data );
}

uint16_t grideye_read_int_lvl_high ( grideye_t *ctx )
{
    uint16_t result;

    result = grideye_read_data( ctx, GRIDEYE_INTHL );

    return result;
}

uint16_t grideye_read_int_lvl_low ( grideye_t *ctx )
{
    uint16_t result;

    result = grideye_read_data( ctx, GRIDEYE_INTLL );

    return result;
}

void grideye_write_int_hyst_lvl ( grideye_t *ctx, uint16_t wr_data )
{
    grideye_write_data( ctx, GRIDEYE_IHYSL, wr_data );
}

uint16_t grideye_read_int_hyst_lvl ( grideye_t *ctx )
{
    uint16_t result;

    result = grideye_read_data( ctx, GRIDEYE_IHYSL );

    return result;
}

float grideye_read_therm_temp_reg ( grideye_t *ctx )
{
    float result;
    uint16_t temp_val;

    temp_val = grideye_read_data( ctx, GRIDEYE_TTHL );

    if( temp_val >= 0x0800 )
    {
        result = ( float )temp_val * -0.0625;
    }
    else
    {
        result = ( float )temp_val * 0.0625;
    }

    return result;
}

uint8_t grideye_read_int0 ( grideye_t *ctx ) 
{
    uint8_t result;

    result = grideye_read_data( ctx, GRIDEYE_INT0 );

    return result;
}

uint8_t grideye_read_int1 ( grideye_t *ctx )
{
    uint8_t result;

    result = grideye_read_data( ctx, GRIDEYE_INT1 );

    return result;
}

uint8_t grideye_read_int2 ( grideye_t *ctx )
{
    uint8_t result;

    result = grideye_read_data( ctx ,GRIDEYE_INT2  );

    return result;
}

uint8_t grideye_read_int3 ( grideye_t *ctx )
{
    uint8_t result;
    
    result = grideye_read_data( ctx, GRIDEYE_INT3 );
    
    return result;
}

uint8_t grideye_read_int4 ( grideye_t *ctx )
{
    uint8_t result;

    result = grideye_read_data( ctx, GRIDEYE_INT4  );
    
    return result;
}

uint8_t grideye_read_int5 ( grideye_t *ctx )
{
    uint8_t result;

    result = grideye_read_data( ctx, GRIDEYE_INT5 );
    
    return result;
}

uint8_t grideye_read_int6 ( grideye_t *ctx )
{
    uint8_t result;
    
    result = grideye_read_data( ctx, GRIDEYE_INT6 );
    
    return result;
}

uint8_t grideye_read_int7 ( grideye_t *ctx )
{
    uint8_t result;

    result = grideye_read_data( ctx, GRIDEYE_INT7 );
    
    return result;
}

// ------------------------------------------------------------------------ END
