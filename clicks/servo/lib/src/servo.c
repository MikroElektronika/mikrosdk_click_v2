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

#include "servo.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t map_priv ( servo_map_t map );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void servo_cfg_setup ( servo_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->oe = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address_of_pca9685 = 0x40;
    cfg->i2c_address_of_ltc2497 = 0x14;
}

SERVO_RETVAL servo_init ( servo_t *ctx, servo_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address_of_pca9685 = cfg->i2c_address_of_pca9685;
    ctx->slave_address_of_ltc2497 = cfg->i2c_address_of_ltc2497;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return SERVO_INIT_ERROR;
    }

    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->oe, cfg->oe );

    return SERVO_OK;
}

void servo_default_cfg ( servo_t *ctx )
{
    servo_pos_and_res_t pos_and_res;

    pos_and_res.min_position = 0;
    pos_and_res.max_position = 180;
    pos_and_res.low_resolution = SERVO_DEFAULT_LOW_RESOLUTION;
    pos_and_res.high_resolution = SERVO_DEFAULT_HIGH_RESOLUTION;
    
    servo_setting( ctx, pos_and_res ); 
    servo_set_vref( ctx, SERVO_VREF_3300 );
    servo_set_mode( ctx, SERVO_REG_MODE_1, SERVO_MODE1_RESTART_ENABLE | SERVO_MODE1_USE_ALL_CALL_ADR );
    servo_sleep( ctx );
    servo_set_freq( ctx, 30 );
    servo_set_mode( ctx, SERVO_REG_MODE_1, SERVO_MODE1_RESTART_ENABLE | SERVO_MODE1_AUTO_INCREMENT_ENABLE | SERVO_MODE1_USE_ALL_CALL_ADR );
}

void servo_generic_write_of_pca9685 ( servo_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_of_pca9685 );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );  
}

void servo_generic_write_of_ltc2497 ( servo_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_of_ltc2497 );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );     
}

void servo_generic_read_of_pca9685 ( servo_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{  
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_of_pca9685 );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void servo_generic_read_of_ltc2497 ( servo_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{  
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_of_ltc2497 );
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void servo_setting ( servo_t *ctx, servo_pos_and_res_t pos_and_res )
{
    ctx->min_pos = pos_and_res.min_position;
    ctx->max_pos = pos_and_res.max_position;
    ctx->low_res  = pos_and_res.low_resolution & 0x0FFF;
    ctx->high_res = pos_and_res.high_resolution & 0x0FFF;
}

void servo_set_vref ( servo_t *ctx, uint16_t v_ref )
{
    ctx->vref = v_ref;
}

void servo_stop ( servo_t *ctx )
{
    digital_out_high( &ctx->oe );
}

void servo_start ( servo_t *ctx )
{
    digital_out_low( &ctx->oe );
}

void servo_soft_reset ( servo_t *ctx )
{
    uint8_t write_reg[ 1 ];

    servo_generic_write_of_pca9685( ctx, SERVO_SOFT_RESET, write_reg, 0 );
    
    Delay_100ms( );
}

void servo_sleep ( servo_t *ctx )
{
    servo_set_mode( ctx, SERVO_REG_MODE_1,
                   SERVO_MODE1_RESTART_ENABLE |
                   SERVO_MODE1_EXTCLK_PIN_CLOCK |
                   SERVO_MODE1_LOW_POWER_MODE |
                   SERVO_MODE1_AUTO_INCREMENT_ENABLE |
                   SERVO_MODE1_USE_ALL_CALL_ADR );
}

void servo_set_mode ( servo_t *ctx, uint8_t mode, uint8_t w_data )
{    
    servo_start( ctx );
    servo_generic_write_of_pca9685( ctx, mode, &w_data, 1 );
    Delay_100ms( );
}

void servo_set_position ( servo_t *ctx, uint8_t motor, uint8_t position )
{
    uint8_t write_reg[ 4 ];
    uint16_t set_map;
    uint16_t on = 0x0000;
    servo_map_t map; 
    
    map.x = position;
    map.in_min = ctx->min_pos ;
    map.in_max = ctx->max_pos;
    map.out_min = ctx->low_res;
    map.out_max = ctx->high_res;

    set_map = map_priv( map ) ;
    if ( set_map < 70 )
    {
        set_map = 70;
    }
        
    write_reg[ 0 ] = on;
    write_reg[ 1 ] = on >> 8;
    write_reg[ 2 ] = set_map;
    write_reg[ 3 ] = set_map >> 8;

    servo_start( ctx );
    servo_generic_write_of_pca9685( ctx, motor, write_reg, 4 );
}

void servo_set_freq ( servo_t *ctx, uint16_t freq )
{
    uint32_t prescale_val;
    uint8_t write_buf[ 1 ];
    
    prescale_val = 25000000;
    prescale_val /= 4096;
    prescale_val /= freq;
    prescale_val -= 1;
    
    write_buf[ 0 ] = prescale_val;
    
    servo_start( ctx );
    servo_generic_write_of_pca9685( ctx, SERVO_REG_PRE_SCALE, write_buf, 1 );

    Delay_100ms( );
}

uint32_t servo_get_channel ( servo_t *ctx, uint8_t channel )
{
    uint8_t read_reg[ 3 ];
    uint32_t adc_value;

    servo_start( ctx );
    servo_generic_read_of_ltc2497( ctx, channel, read_reg, 3 );
    
    adc_value = read_reg[ 0 ];
    adc_value = adc_value << 8;
    adc_value = adc_value | read_reg[ 1 ];
    adc_value = adc_value << 8;
    adc_value = adc_value | read_reg[ 2 ];
    
    adc_value = adc_value & 0x00FFFFC0;
    adc_value = adc_value >> 5;

    return adc_value;
}

uint16_t setvo_get_current ( servo_t *ctx, uint8_t channel )
{
    uint32_t adc_value;
    uint16_t current;

    adc_value = servo_get_channel( ctx, channel );
    adc_value = adc_value & 0x00003FFF;
    current = ( adc_value * ctx->vref ) / 65535;
    
    return  current;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t map_priv ( servo_map_t map )
{
    uint16_t val;

    val = ( map.x - map.in_min ) * ( map.out_max - map.out_min ) / ( map.in_max - map.in_min );
    val = val + map.out_min + 10 ;

    return val;
}

// ------------------------------------------------------------------------- END

