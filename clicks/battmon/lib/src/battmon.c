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

#include "battmon.h"
// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static float get_sens ( uint8_t data_sel, uint8_t *n_bytes );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void battmon_cfg_setup ( battmon_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rio = HAL_PIN_NC;
    cfg->alm = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = BATTMON_DEV_ADDR; 
}

BATTMON_RETVAL battmon_init ( battmon_t *ctx, battmon_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return BATTMON_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->rio, cfg->rio );
    digital_in_init( &ctx->alm, cfg->alm );

    return BATTMON_OK;
}

void battmon_default_cfg ( battmon_t *ctx )
{
    battmon_write_byte( ctx, BATTMON_REG_MODE, BATTMON_MIXED_MODE | 
                                              BATTMON_ALM_EN | 
                                              BATTMON_OP_RUN_MODE );
    battmon_write_byte( ctx, BATTMON_REG_CTRL, BATTMON_RST_CONV_CNT | 
                                              BATTMON_DRIVE_ALM_PIN_COND );
    battmon_set_alarm( ctx, BATTMON_REG_ALARM_SOC, 1 );
    battmon_set_alarm( ctx, BATTMON_REG_ALARM_VOLTAGE, 3000 );
}

void battmon_generic_write ( battmon_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void battmon_generic_read ( battmon_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write( &ctx->i2c, &reg, 1 );
    Delay_ms( 100 );
    i2c_master_read( &ctx->i2c, data_buf, len );
    Delay_ms( 100 );
}

uint8_t battmon_read_bytes ( battmon_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_bytes )
{
    uint8_t temp_data;
    
    if ( ( reg_addr > 63 ) || ( reg_addr == 31 ) )
    {
        return BATTMON_INVALID_ADDR;
    }
    if ( ( n_bytes > 63 ) || ( n_bytes == 0 ) )
    {
        return BATTMON_INVALID_NBYTES;
    }
    
    temp_data = reg_addr;
    
    battmon_generic_read( ctx, temp_data, data_out, n_bytes );
    
    return BATTMON_OK;
}

uint8_t battmon_read_word ( battmon_t *ctx, uint8_t reg_addr, uint16_t *data_out )
{
    uint8_t temp_data[ 2 ];
    uint16_t ret_val;
    
    if ( ( reg_addr != 2 ) && ( reg_addr != 4 ) && 
         ( reg_addr != 6 ) && ( reg_addr != 8 ) &&
         ( reg_addr != 13 ) && ( reg_addr != 15 ) && 
         ( reg_addr != 17 ) && ( reg_addr != 27 ) && ( reg_addr != 29 ) )
    {
        return BATTMON_INVALID_ADDR;
    }
    
    battmon_generic_read( ctx, reg_addr, temp_data, 2 );
    
    ret_val = temp_data[ 1 ];
    ret_val <<= 8;
    ret_val |= temp_data[ 0 ];
    *data_out = ret_val;
    
    return BATTMON_OK;
}

uint8_t battmon_write_byte ( battmon_t *ctx, uint8_t reg_addr, uint8_t data_in )
{
    uint8_t temp_data[ 2 ];
    
    if ( ( reg_addr > 63 ) || ( reg_addr == 31 ) )
    {
        return BATTMON_INVALID_ADDR;
    }
    
    battmon_generic_write( ctx, reg_addr, &data_in, 1 );
    
    return BATTMON_OK;
}

uint8_t battmon_write_word ( battmon_t *ctx, uint8_t reg_addr, uint16_t data_in )
{
    uint8_t temp_data[ 2 ];
    
    if ( ( reg_addr != 2 ) && ( reg_addr != 4 ) && 
         ( reg_addr != 6 ) && ( reg_addr != 8 ) &&
         ( reg_addr != 13 ) && ( reg_addr != 15 ) && 
         ( reg_addr != 17 ) && ( reg_addr != 27 ) && ( reg_addr != 29 ) )
    {
        return BATTMON_INVALID_ADDR;
    }
    
    temp_data[ 0 ] = data_in;
    temp_data[ 1 ] = data_in >> 8;
    
    battmon_generic_write( ctx, reg_addr, temp_data, 2 );
    
    return BATTMON_OK;
}

float battmon_get_data ( battmon_t *ctx, uint8_t data_addr )
{
    uint8_t read_data[ 2 ];
    uint8_t n_bytes;
    uint16_t c_data;
    int8_t temp_data;
    float lsb_val;
    float ret_val;
    
    read_data[ 0 ] = DUMMY_BYTE;
    read_data[ 1 ] = DUMMY_BYTE;
    
    lsb_val = get_sens( data_addr, &n_bytes );
    battmon_read_bytes( ctx, data_addr, read_data, n_bytes );
    
    if ( data_addr == BATTMON_REG_TEMPERATURE )
    {
        temp_data = read_data[ 0 ];
        ret_val = temp_data;
    }
    else
    {
        c_data = read_data[ 1 ];
        c_data <<= 8;
        c_data |= read_data[ 0 ];
    
        ret_val = c_data;
    }
    ret_val *= lsb_val;
    
    return ret_val;
}

uint8_t battmon_set_alarm ( battmon_t *ctx, uint8_t alarm_addr, float alarm_value )
{
    uint8_t n_bytes;
    uint8_t c_data;
    float lsb_val;
    float tmp;
    
    if ( ( alarm_addr < 19 ) || ( alarm_addr > 21 ) )
    {
        return BATTMON_INVALID_ADDR;
    }
    
    lsb_val = get_sens( alarm_addr, &n_bytes );
    
    tmp = alarm_value;
    tmp /= lsb_val;
    
    if ( tmp >= 256 )
    {
        return BATTMON_INVALID_ALM_VAL;
    }
    
    c_data = tmp;
    
    battmon_write_byte( ctx, alarm_addr, c_data );
    
    return BATTMON_OK;
}

uint8_t battmon_get_rio_pin ( battmon_t *ctx )
{
    if ( digital_in_read( &ctx->rio ) )
    {
        return BATTMON_LOG_HIGH;
    }
    else
    {
        return BATTMON_LOG_LOW;
    }
}

uint8_t battmon_get_alm_pin ( battmon_t *ctx )
{
    if ( digital_in_read( &ctx->alm ) )
    {
        return BATTMON_LOG_HIGH;
    }
    else
    {
        return BATTMON_LOG_LOW;
    }
}

uint8_t battmon_check_clear_alarm ( battmon_t *ctx )
{
    uint8_t tmp;
    uint8_t ret_val;
    
    battmon_read_bytes( ctx, BATTMON_REG_CTRL, &tmp, 1 );
    
    ret_val = tmp & ( BATTMON_ALM_SOC_DET_MASK | BATTMON_ALM_VOLT_DET_MASK );
    
    if ( ret_val )
    {
        tmp &= 0x9F;
    
        battmon_write_byte( ctx, BATTMON_REG_CTRL, tmp );
    }
    
    return ret_val;
}

void battmon_sw_reset ( battmon_t *ctx )
{
    uint8_t tmp;
    
    battmon_write_byte( ctx, BATTMON_REG_CTRL, BATTMON_SOFT_RST );
    Delay_1sec( );
    Delay_1sec( );
    
    battmon_read_bytes( ctx, BATTMON_REG_CTRL, &tmp, 1 );
    while ( tmp & BATTMON_POR_DET_MASK )
    {
        Delay_100ms( );
        battmon_read_bytes( ctx, BATTMON_REG_CTRL, &tmp, 1 );
    }
}

void battmon_reset_conv_cnt ( battmon_t *ctx )
{
    uint8_t tmp;
    
    battmon_read_bytes( ctx, BATTMON_REG_CTRL, &tmp, 1 );
    tmp |= BATTMON_RST_CONV_CNT;
    battmon_write_byte( ctx, BATTMON_REG_CTRL, tmp );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static float get_sens ( uint8_t data_sel, uint8_t *n_bytes )
{
    float sens;

    switch ( data_sel )
    {
        case BATTMON_REG_SOC :
        {
            sens = 1.0 / 512.0;
            *n_bytes = 2;
        break;
        }
        case BATTMON_REG_COUNTER :
        {
            sens = 0.5;
            *n_bytes = 2;
        break;
        }
        case BATTMON_REG_CURRENT :
        {
            sens = 0.588;
            *n_bytes = 2;
        break;
        }
        case BATTMON_REG_VOLTAGE :
        {
            sens = 2.2;
            *n_bytes = 2;
        break;
        }
        case BATTMON_REG_TEMPERATURE :
        {
            sens = 1;
            *n_bytes = 1;
        break;
        }
        case BATTMON_REG_OCV :
        {
            sens = 0.55;
            *n_bytes = 2;
        break;
        }
        case BATTMON_REG_ALARM_SOC :
        {
            sens = 0.5;
            *n_bytes = 1;
        break;
        }
        case BATTMON_REG_ALARM_VOLTAGE :
        {
            sens = 17.6;
            *n_bytes = 1;
        break;
        }
        case BATTMON_REG_CURRENT_THRES :
        {
            sens = 4.704;
            *n_bytes = 1;
        break;
        }
        default :
        {
            sens = 0;
            *n_bytes = 0;
        break;
        }
    }
    
    return sens;
}

// ------------------------------------------------------------------------- END

