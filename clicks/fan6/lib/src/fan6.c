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

#include "fan6.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t fan6_get_data_size ( fan6_t *ctx, const uint8_t reg_addr );

static void fan6_make_data( fan6_t *ctx, const uint16_t data_in, uint8_t *data_out, const uint8_t num_bytes );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void fan6_cfg_setup ( fan6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->io1 = HAL_PIN_NC;
    cfg->sdn = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;
    cfg->io2 = HAL_PIN_NC;
    cfg->alr = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x2E;
}

FAN6_RETVAL fan6_init ( fan6_t *ctx, fan6_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return FAN6_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->io1, cfg->io1 );
    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->sdn, cfg->sdn );
    digital_in_init( &ctx->io2, cfg->io2 );
    digital_in_init( &ctx->alr, cfg->alr );

    return FAN6_OK;
}

void fan6_default_cfg ( fan6_t *ctx )
{
    fan6_write_reg( ctx, FAN6_FAN_STEP_REG, 0x10 );
    fan6_write_reg( ctx, FAN6_FAN_SPINUP_CONFIG_REG, FAN6_SPINUP_DRIVELEVEL_60_PERCENTS | FAN6_SPINUP_TIME_500_MILISEC );
    fan6_write_reg( ctx, FAN6_FAN_CONFIG1_REG, FAN6_RANGE_MIN_1000RPM | FAN6_MIN_5_EDGES | FAN6_UPDATE_TIME_400_MILISEC );
    fan6_write_reg( ctx, FAN6_PWM_DIVIDE_REG, 0x01 );
    fan6_write_reg( ctx, FAN6_PWM_CONFIG_REG, FAN6_NORMAL_POLARITY );
    fan6_write_reg( ctx, FAN6_FAN_MIN_DRIVE_REG, 0x66 );
    fan6_write_reg( ctx, FAN6_FAN_VALID_TACH_COUNT_REG, 0xFF );
    fan6_set_pwm_mode( ctx, FAN6_100_PERCENTS_SPEED );
}

void fan6_generic_write ( fan6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void fan6_generic_read ( fan6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void fan6_write_reg ( fan6_t *ctx, uint8_t register_address, uint16_t transfer_data )
{
    uint8_t n_bytes;
    uint8_t i;      
    uint8_t reg;
    uint8_t buff_data[ 2 ];
    
    n_bytes = fan6_get_data_size( ctx, register_address );
    fan6_make_data( ctx, transfer_data, buff_data, n_bytes );
    for ( i = 0; i < n_bytes; i++ )
    {   
        reg = register_address + i;     
        fan6_generic_write( ctx, reg, &buff_data[ 0 ], 1 );
        buff_data[ 0 ] = buff_data[ 1 ];
    }
   
    if ( register_address == 0x42 )
    {
        ctx->config_byte1 = transfer_data;
    }     
    else if ( register_address == 0x50 )
    {
        ctx->config_byte2 = transfer_data;
    }
}

uint16_t fan6_read_reg ( fan6_t *ctx, uint8_t register_address )
{
    uint8_t n_bytes;
    uint8_t i;
    uint16_t temp = 0;
    uint8_t buff_data[ 2 ];
    uint8_t reg;
    
    n_bytes = fan6_get_data_size( ctx, register_address );
    
    for ( i = 0; i < n_bytes; i++ )
    {
        reg = register_address + i;
        fan6_generic_read( ctx, reg, buff_data, 1 );
    }
    if ( n_bytes == 2 )
    {
        if ( ctx->adc_mode )
        {
            temp = buff_data[ 0 ];
            temp <<= 8;
            temp |= buff_data[ 1 ];
        }
        else
        {
            temp = buff_data[ 1 ];
            temp <<= 8;
            temp |= buff_data[ 0 ];
        }
    }
    else
        temp = buff_data[ 0 ];;
    return temp;
}

uint8_t fan6_receive_byte ( fan6_t *ctx, uint8_t register_address )
{
    uint8_t temp;
    uint8_t reg;

    reg = 0x00;
    
    if ( !( ctx->check_ptr ) )
    {
        fan6_generic_write( ctx, register_address, &temp, 0 );
        
        ctx->check_ptr = 1;
    }                            
    
    fan6_generic_read( ctx, reg, &temp, 1 );
  
    return temp;
}

void fan6_read_eeprom ( fan6_t *ctx, uint8_t *data_out )
{
    uint8_t temp = 0x00;

    fan6_generic_read( ctx, temp, data_out, 256 );

    ctx->check_ptr = 0;
}

void fan6_set_pwm_mode ( fan6_t *ctx, uint8_t pwm_duty )
{
    ctx->config_byte1 &= 0x7F;
    ctx->config_byte2 &= 0xDF;
    fan6_write_reg( ctx, 0x42, ctx->config_byte1 );
    fan6_write_reg( ctx, 0x50, ctx->config_byte2 );
    fan6_write_reg( ctx, 0x40, pwm_duty );
}

void fan6_set_fan_speed_con_mode ( fan6_t *ctx, uint8_t minimum_drive, uint8_t tach_count, uint16_t tach_target )
{
    ctx->config_byte1 |= 0x80;
    ctx->config_byte2 &= 0xDF;
    fan6_write_reg( ctx, 0x42, ctx->config_byte1 );
    fan6_write_reg( ctx, 0x50, ctx->config_byte2 );
    fan6_write_reg( ctx, 0x48, minimum_drive );
    fan6_write_reg( ctx, 0x49, tach_count );
    fan6_write_reg( ctx, 0x4C, tach_target );
}

void fan6_set_pwm_lut_mode ( fan6_t *ctx, uint8_t tach_count )
{
    ctx->config_byte2 |= 0x30;
    fan6_write_reg( ctx, 0x50, ctx->config_byte2 );
    fan6_write_reg( ctx, 0x49, tach_count );
}

void fan6_set_fsc_lut_mode ( fan6_t *ctx, uint8_t minimum_drive, uint8_t tach_count )
{
    ctx->config_byte2 &= 0xEF;
    ctx->config_byte2 |= 0x20;
    fan6_write_reg( ctx, 0x50, ctx->config_byte2 );
    fan6_write_reg( ctx, 0x48, minimum_drive );
    fan6_write_reg( ctx, 0x49, tach_count );
}

uint32_t fan6_read_tachometer ( fan6_t *ctx )
{
    uint16_t tach_value;
    uint8_t fan_config;
    uint8_t fan_config_check;
    uint8_t n_poles;
    uint8_t n_edges;
    uint8_t multiplier_range;
    uint32_t tmp = 0x001E0000;
    
    fan_config = fan6_read_reg( ctx,  0x42 );
    fan_config_check = ( fan_config & 0x60 ) >> 5;
    
    switch ( fan_config_check )
    {
        case 0: 
        {
            multiplier_range = 1;
            break;
        }
        case 1:
        {
            multiplier_range = 2;
            break;
        }  
        case 2:
        {
            multiplier_range = 4;
            break;
        }  
        case 3:
        {
            multiplier_range = 8;
        }   
    }

    fan_config_check = ( fan_config & 0x18 ) >> 3;
    
    switch ( fan_config_check )
    {
        case 0:
        {
            n_edges = 3;
            n_poles = 1;
            break;
        } 
        case 1:
        {
            n_edges = 5;
            n_poles = 2;
            break;
        } 
        case 2:
        {
            n_edges = 7;
            n_poles = 3;
            break; 
        }
        case 3: 
        {
            n_edges = 9;
            n_poles = 4;
        }
    }
    tach_value = fan6_read_reg( ctx, 0x4E );
    tach_value >>= 3;
    tmp *= ( n_edges - 1 ) ;
    tmp /= n_poles;
    tmp *= multiplier_range;
    tmp /= tach_value;
    return tmp;
}

float fan6_get_temperature ( fan6_t *ctx, uint8_t temp_address )
{
    uint16_t temp_value = 0;
    float ret_value = 0;
    
    switch ( temp_address )
    {
        case 0x00: 
        {
            temp_value = fan6_read_reg( ctx, 0x00 );
            break;
        }
        case 0x02:
        {
            temp_value = fan6_read_reg( ctx, 0x02 );
            break;
        } 
        case 0x04: 
        {
            temp_value = fan6_read_reg( ctx, 0x04 );
            break; 
        }
        case 0x06:
        {
            temp_value = fan6_read_reg( ctx, 0x06 );
            break;
        } 
        default:
        {
            return (-1);
        } 
    }
    if ( temp_value < 0x8000 )
    {
        ret_value = temp_value / 0x0020;
        ret_value *= 0.125;
    }
    else if ( temp_value > 0x8000 )
    {
        ret_value = ~temp_value;
        ret_value += 1;
        ret_value = temp_value / 0x0020;
        ret_value *= 0.125;
    }
    return ret_value;
}

void fan6_push_temperature ( fan6_t *ctx, uint8_t temp_address, uint8_t temp_selection )
{
    uint16_t temp_value = 0;
    
    if ( ( temp_selection != 0x0C ) && ( temp_selection != 0x0D ) )
        return;
    switch ( temp_address )
    {
        case 0x00: 
        {
            temp_value = fan6_read_reg( ctx, 0x00 );
            break;
        }
        case 0x02: 
        {
            temp_value = fan6_read_reg( ctx, 0x02 );
            break;
        }
        case 0x04: 
        {
            temp_value = fan6_read_reg( ctx, 0x04 );
            break;
        }
        case 0x06: 
        {
            temp_value = fan6_read_reg( ctx, 0x06 );
            break;
        }
    }
    if ( temp_value < 0x8000 )
    {
        temp_value >>= 8;
        fan6_write_reg(  ctx, temp_selection, temp_value );
    }
    else if ( temp_value > 0x8000 )
    {
        temp_value = ~temp_value;
        temp_value += 1;
        temp_value >>= 8;
        temp_value |= 0x0080;
        fan6_write_reg(  ctx, temp_selection, temp_value );
    }
}

void fan6_enable_device ( fan6_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en, state );
}

uint8_t fan6_indicate_critical_thermal_shutdown ( fan6_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->sdn );

    if ( state )
    {
        return 1;
    } 
    else
    {
        return 0;
    }
}

uint8_t fan6_get_gpio_2 ( fan6_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->io2 );

    if ( state )
    {
        return 1;
    }    
    else
    {
        return 0;
    }
}

void fan6_set_gpio_1 ( fan6_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->io1, state );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t fan6_get_data_size ( fan6_t *ctx, uint8_t reg_addr )
{
    switch ( reg_addr )
    {
        case 0x00:  
        {
            ctx->adc_mode = 1;
            return 2;
        }
        case 0x02:
        {
            ctx->adc_mode = 1;
            return 2;
        } 
        case 0x04:
        {
            ctx->adc_mode = 1;
            return 2;  
        } 
        case 0x06:
        {
            ctx->adc_mode = 1;
            return 2;
        } 
        case 0x4A: 
        {
            ctx->adc_mode = 0;
            return 2;
        }
        case 0x4C:
        {
            ctx->adc_mode = 0;
            return 2;
        } 
        case 0x4E:
        {
            ctx->adc_mode = 1;
            return 2;
        } 
        default:
        {
            return 1;
        } 
    }
    ctx->check_ptr = 0;
}

static void fan6_make_data ( fan6_t *ctx, uint16_t data_in, uint8_t *data_out, uint8_t num_bytes )
{
    if ( num_bytes == 2 )
    {
        data_out[ 0 ] = data_in & 0x00FF;    
        data_out[ 1 ] = data_in >> 8;
    }
    else
    {
        data_out[ 0 ] = data_in & 0x00FF;
    }
}

// ------------------------------------------------------------------------- END

