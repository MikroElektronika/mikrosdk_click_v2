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

#include "templog3.h"

// ------------------------------------------------------------------ CONSTANTS

#define TEMP_RESOL  0.0625
#define SIGN_BIT    0x1000

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void templog3_cfg_setup ( templog3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TEMPLOG3_SLAVE_ADDR_A0_L;
    cfg->i2c_eeprom = 0x50 | (TEMPLOG3_SLAVE_ADDR_A0_L & 0x07 );

    cfg->dev_resolution = TEMPLOG3_10BIT_RESOLUTION;
    cfg->dev_n_bytes = 2;

}

TEMPLOG3_RETVAL templog3_init ( templog3_t *ctx, templog3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;
    
    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->slave_eeprom = cfg->i2c_eeprom;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPLOG3_INIT_ERROR;
    }

    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    ctx->resolution = cfg->dev_resolution;
    ctx->n_bytes = cfg->dev_n_bytes;

    return TEMPLOG3_OK;
}

void templog3_default_cfg ( templog3_t *ctx )
{
    templog3_write_reg( ctx, TEMPLOG3_CONFIG_REG, TEMPLOG3_TLIMIT_HYST_0_DEG | 
                                             TEMPLOG3_CONT_CONV_MODE | 
                                             TEMPLOG3_EVENT_OUTPUT_EN | 
                                             TEMPLOG3_EVENT_TCRIT_ONLY | 
                                             TEMPLOG3_EVENT_POL_ACT_HIGH | 
                                             TEMPLOG3_EVENT_COMPARATOR_MODE );
    templog3_write_reg( ctx, TEMPLOG3_RESOLUTION_REG, TEMPLOG3_11BIT_RESOLUTION );
    templog3_set_temp( ctx, TEMPLOG3_TEMP_CRITICAL_REG, 30 );
    templog3_set_temp( ctx, TEMPLOG3_TEMP_UPPER_REG, 35 );
    templog3_set_temp( ctx, TEMPLOG3_TEMP_LOWER_REG, -5 );
}

uint8_t templog3_write_reg ( templog3_t *ctx, uint8_t reg_addr, uint16_t data_in )
{
    uint8_t temp_data[ 3 ];
    uint8_t num_bytes;
    
    if ( ( reg_addr < 0x01 ) || ( ( reg_addr > 0x04 ) && ( reg_addr != 0x08 ) ) )
    {
        return TEMPLOG3_ADDR_ERROR;
    }
    
    temp_data[ 0 ] = reg_addr;
    
    if ( reg_addr == TEMPLOG3_RESOLUTION_REG )
    {
        temp_data[ 1 ] = data_in;
        num_bytes = 2;
        ctx->n_bytes = 1;
        ctx->resolution = data_in & 0x03;
    }
    else
    {
        temp_data[ 1 ] = data_in >> 8;
        temp_data[ 2 ] = data_in;
        num_bytes = 3;
        ctx->n_bytes = 2;
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_write( &ctx->i2c, temp_data, num_bytes );   
    
    return TEMPLOG3_OK;
}

uint8_t templog3_read_reg ( templog3_t *ctx, uint8_t reg_addr, uint16_t *data_out )
{
    uint8_t temp_data[ 2 ];
    uint16_t ret_val;
    
    if ( reg_addr > 0x08 )
    {
        return TEMPLOG3_ADDR_ERROR;
    }
    
    if ( reg_addr == TEMPLOG3_RESOLUTION_REG )
    {
        ctx->n_bytes = 1;
    }
    else
    {
        ctx->n_bytes = 2;
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, temp_data, ctx->n_bytes );
    
    ret_val = temp_data[ 0 ];
    
    if ( reg_addr != TEMPLOG3_RESOLUTION_REG )
    {
        ret_val <<= 8;
        ret_val |= temp_data[ 1 ];
    }
    *data_out = ret_val;
    
    return TEMPLOG3_OK;
}

uint8_t templog3_set_addr_ptr ( templog3_t *ctx, uint8_t reg_addr )
{
    uint8_t register_addr;
    uint8_t dummy_buff;
    
    if ( reg_addr > 0x08 )
    {
        return TEMPLOG3_ADDR_ERROR;
    }
    register_addr = reg_addr;
    
    if ( reg_addr == TEMPLOG3_RESOLUTION_REG )
    {
        ctx->n_bytes = 1;
    }
    else
    {
        ctx->n_bytes = 2;
    }
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_write( &ctx->i2c, &register_addr, 1 );

    return TEMPLOG3_OK;
}

void templog3_repeated_read ( templog3_t *ctx, uint16_t *data_out )
{
    uint8_t temp_data[ 2 ];
    uint16_t ret_val;
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_read( &ctx->i2c, temp_data, ctx->n_bytes );
    
    ret_val = temp_data[ 0 ];
    
    if ( ctx->n_bytes == 2 )
    {
        ret_val <<= 8;
        ret_val |= temp_data[ 1 ];
    }
    *data_out = ret_val;
}

uint8_t templog3_get_temp ( templog3_t *ctx, uint8_t temp_sel, float *temp_out )
{
    float temp_res;
    uint16_t temp;
    int16_t temp_val;
    uint8_t limit_stat;
    static uint8_t temp_sel_prev = 0;
    
    if ( ( temp_sel < 0x02 ) || ( temp_sel > 0x05 ) )
    {
        return TEMPLOG3_ADDR_ERROR;
    }
    
    if ( temp_sel_prev != temp_sel )
    {
        templog3_set_addr_ptr( ctx, temp_sel );
        temp_sel_prev = temp_sel;
    }
    
    templog3_repeated_read( ctx, &temp );
    
    limit_stat = ( temp & 0xE000 ) >> 8;
    
    if ( temp & SIGN_BIT )
    {
        temp_val = temp | 0xE000;
    }
    else
    {
        temp_val = temp & 0x1FFF;
    }
    
    temp_res = temp_val * TEMP_RESOL;
    *temp_out = temp_res;
    
    return limit_stat;
}

uint8_t templog3_set_temp ( templog3_t *ctx, uint8_t temp_sel, float temp_in )
{
    float temp_res;
    int16_t temp_val;
    
    if ( ( temp_sel < 0x02 ) || ( temp_sel > 0x04 ) )
    {
        return TEMPLOG3_ADDR_ERROR;
    }
    if ( ( temp_in < -40 ) || ( temp_in > 125 ) )
    {
        return TEMPLOG3_TEMP_RANGE_ERROR;
    }
    
    temp_res = temp_in / TEMP_RESOL;
    temp_val = temp_res;
    temp_val &= 0x1FFC;
    
    templog3_write_reg( ctx, temp_sel, temp_val );
    
    return TEMPLOG3_OK;
}

uint8_t templog3_check_alarm ( templog3_t *ctx )
{
    if ( digital_in_read( &ctx->int_pin ) )
    {
        return TEMPLOG3_ALARMING;
    }
    else
    {
        return TEMPLOG3_OK;
    }
}

void templog3_wait_conv_done ( templog3_t *ctx )
{
    uint8_t time_cnt;
    uint8_t cnt;
    
    switch ( ctx->resolution )
    {
        case TEMPLOG3_9BIT_RESOLUTION :
        {
            time_cnt = 4;
        break;
        }
        case TEMPLOG3_10BIT_RESOLUTION :
        {
            time_cnt = 7;
        break;
        }
        case TEMPLOG3_11BIT_RESOLUTION :
        {
            time_cnt = 14;
        break;
        }
        case TEMPLOG3_12BIT_RESOLUTION :
        {
            time_cnt = 27;
        break;
        }
        default :
        {
            time_cnt = 7;
        break;
        }
    }
    
    for ( cnt = 0; cnt < time_cnt; cnt++ )
    {
        Delay_10ms( );
    }
}

void templog3_eeprom_byte_write ( templog3_t *ctx, uint8_t reg_addr, uint8_t data_in, uint8_t eeprom_mode )
{
    uint8_t slave_addr;
    uint8_t temp_data[ 2 ];
    
    switch ( eeprom_mode )
    {
        case TEMPLOG3_EEPROM_WRITE :
        {
            slave_addr = ctx->slave_eeprom;
        break;
        }
        case TEMPLOG3_SW_WRITE_PROTECT :
        {
            slave_addr = 0x31;
        break;
        }
        case TEMPLOG3_CLEAR_WRITE_PROTECT :
        {
            slave_addr = 0x33;
        break;
        }
        default :
        {
            return;
        }
    }
    
    temp_data[ 0 ] = reg_addr;
    temp_data[ 1 ] = data_in;
    i2c_master_set_slave_address( &ctx->i2c, slave_addr );
    i2c_master_write( &ctx->i2c, temp_data, 2 );
}

void templog3_eeprom_page_write ( templog3_t *ctx, uint8_t reg_addr, uint8_t *data_in )
{
    uint8_t temp_data[ 17 ];
    uint8_t cnt;
    
    temp_data[ 0 ] = reg_addr;
    
    for (cnt = 1; cnt <= 16; cnt++)
    {
        temp_data[ cnt ] = *data_in;
        data_in++;
    }
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_eeprom );
    i2c_master_write( &ctx->i2c, temp_data, 17 );
}

void templog3_eeprom_curr_addr_read ( templog3_t *ctx, uint8_t *current_address )
{
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_eeprom );
    i2c_master_read( &ctx->i2c, current_address, 1 );
}

void templog3_eeprom_byte_read ( templog3_t *ctx, uint8_t reg_addr, uint8_t *data_out )
{
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_eeprom );
    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, data_out, 1 );
}

uint8_t templog3_eeprom_sequential_read ( templog3_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint16_t num_bytes )
{
    if ( ( reg_addr + num_bytes ) > TEMPLOG3_EEPROM_SIZE )
    {
        return TEMPLOG3_NBYTES_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_eeprom );
    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, data_out, num_bytes );
    
    return TEMPLOG3_OK;
}

// ------------------------------------------------------------------------- END

