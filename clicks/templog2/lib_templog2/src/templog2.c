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
 * \file templog2.c
 *
 */

#include "templog2.h"


// ------------------------------------------------------------- PRIVATE MACROS

//  Temp-Log 2 click device address.
#define TEMPLOG2_ADDR_SEL_0  0x48
#define TEMPLOG2_ADDR_SEL_1  0x49

//  Temp-Log 2 click general call address and reset command.
#define TEMPLOG2_GENERAL_CALL_ADDR  0x00
#define TEMPLOG2_RESET_CMD          0x06

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void
templog2_cfg_setup( templog2_cfg_t *cfg )
{
    cfg->alt = HAL_PIN_NC;
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->addr_sel = false;
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
}

TEMPLOG2_RETVAL
templog2_init( templog2_t *ctx, templog2_cfg_t *cfg )
{
    i2c_master_config_t i2c_config;

    i2c_master_configure_default( &i2c_config );
    i2c_config.speed = cfg->i2c_speed;
    i2c_config.scl = cfg->scl;
    i2c_config.sda = cfg->sda;

    if ( i2c_master_open( &ctx->i2c, &i2c_config ) == I2C_MASTER_ERROR )
    {
        return TEMPLOG2_INIT_DRV_ERROR;
    }

    digital_in_init( &ctx->alt, cfg->alt );

    if ( cfg->addr_sel )
    {
        ctx->slave_addr = TEMPLOG2_ADDR_SEL_1;
    }
    else
    {
        ctx->slave_addr = TEMPLOG2_ADDR_SEL_0;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_addr );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return TEMPLOG2_OK;
}

void
templog2_default_config( templog2_t *ctx )
{
    templog2_write_eeprom( ctx, TEMPLOG2_HIGH_LIMIT_REG, 0x0DD0 );
    templog2_write_eeprom( ctx, TEMPLOG2_LOW_LIMIT_REG,
                           TEMPLOG2_25_CELSIUS_POS );
    templog2_write_eeprom( ctx, TEMPLOG2_CONFIG_REG,
                           TEMPLOG2_250_MILISEC_8_AVG |
                           TEMPLOG2_PIN_DATAREADY_FLAG |
                           TEMPLOG2_POL_ACTIVE_HIGH |
                           0x0410 );
    templog2_reset( ctx );
    templog2_set_mode( ctx, TEMPLOG2_CONT_CONV_OP_MODE,
                       TEMPLOG2_ALERT_MODE );
}

TEMPLOG2_RETVAL
templog2_write_reg( templog2_t *ctx, uint8_t reg_addr, uint16_t transfer_data )
{
    uint8_t buff_data[ 3 ];

    if ( ( reg_addr > 0x08 ) && ( reg_addr != 0x0F ) )
    {
        return TEMPLOG2_INVALID_ADDR;
    }

    buff_data[ 0 ] = reg_addr;
    buff_data[ 1 ] = transfer_data >> 8;
    buff_data[ 2 ] = transfer_data;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_addr );
    i2c_master_write( &ctx->i2c, buff_data, 3 );  

    return TEMPLOG2_OK;
}

TEMPLOG2_RETVAL
templog2_read_reg( templog2_t *ctx, uint8_t reg_addr, uint16_t *data_out )
{
    uint8_t buff_data[ 2 ];
    uint16_t tmp;

    if ( ( reg_addr > 0x08 ) && ( reg_addr != 0x0F ) )
    {
        return TEMPLOG2_INVALID_ADDR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_addr );
    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, buff_data, 2 );

    tmp = buff_data[ 0 ];
    tmp <<= 8;
    tmp |= buff_data[ 1 ];
    *data_out = tmp;

    return TEMPLOG2_OK;
}

uint8_t
templog2_data_ready( templog2_t *ctx )
{
    uint16_t ready_check;

    templog2_read_reg( ctx, TEMPLOG2_CONFIG_REG, &ready_check );

    return ( ready_check >> 13 );
}

uint8_t
templog2_check_alert( templog2_t *ctx )
{
    return digital_in_read( &ctx->alt );
}

float
templog2_read_temp( templog2_t *ctx )
{
    float temp;
    uint16_t temp_data;
    int16_t temp_signed;

    templog2_read_reg( ctx, TEMPLOG2_TEMP_REG, &temp_data );

    temp_signed = temp_data;
    temp        = temp_signed;
    temp        *= 0.0078125;

    return temp;
}

TEMPLOG2_RETVAL
templog2_set_mode( templog2_t *ctx, uint8_t op_mode, uint8_t alert_mode )
{
    uint16_t mode_data;

    templog2_read_reg( ctx, TEMPLOG2_CONFIG_REG, &mode_data );

    if ( op_mode == TEMPLOG2_CONT_CONV_OP_MODE )
    {
        mode_data &= 0xF3FF;
    }
    else if ( op_mode == TEMPLOG2_SHUTDOWN_OP_MODE )
    {
        mode_data &= 0xF3FF;
        mode_data |= 0x0400;
    }
    else if ( op_mode == TEMPLOG2_ONE_SHOT_OP_MODE )
    {
        mode_data &= 0xF3FF;
        mode_data |= 0x0800;
    }
    else
    {
        return TEMPLOG2_INVALID_PARAM;
    }

    if ( alert_mode == TEMPLOG2_ALERT_MODE )
    {
        mode_data &= 0xFFEF;
    }
    else if ( alert_mode == TEMPLOG2_THERM_MODE )
    {
        mode_data |= 0x0010;
    }
    else
    {
        return TEMPLOG2_INVALID_PARAM;
    }

    templog2_write_reg( ctx, TEMPLOG2_CONFIG_REG, mode_data );

    return TEMPLOG2_OK;
}

TEMPLOG2_RETVAL
templog2_write_eeprom( templog2_t *ctx, uint8_t eeprom_addr, uint16_t data_in )
{
    uint8_t addr_check;
    uint16_t busy_check;

    templog2_write_reg( ctx, TEMPLOG2_EEPROM_UNLOCK_REG,
                        TEMPLOG2_UNLOCK_EEPROM );
    addr_check = templog2_write_reg( ctx, eeprom_addr, data_in );

    if ( addr_check )
    {
        return TEMPLOG2_INVALID_ADDR;
    }

    Delay_10ms( );
    templog2_read_reg( ctx, TEMPLOG2_EEPROM_UNLOCK_REG, &busy_check );

    while ( busy_check & TEMPLOG2_BUSY_MASK )
    {
        Delay_10ms( );
        templog2_read_reg( ctx, TEMPLOG2_EEPROM_UNLOCK_REG, &busy_check );
    }

    return TEMPLOG2_OK;
}

void
templog2_reset( templog2_t *ctx )
{
    uint8_t reset_cmd = TEMPLOG2_RESET_CMD;

    i2c_master_set_slave_address( &ctx->i2c, TEMPLOG2_GENERAL_CALL_ADDR );
    i2c_master_write( &ctx->i2c, &reset_cmd, 1 );  

    Delay_1sec( );
}

// ------------------------------------------------------------------------ END
