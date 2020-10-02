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

#include "nfcextend.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

uint8_t drv_single_write ( nfcextend_t *ctx, uint8_t memory_area, 
                          uint16_t reg_addr, uint8_t *write_data );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void nfcextend_cfg_setup ( nfcextend_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = NFCEXTEND_I2C_SLAVE_ADDRESS;
}

NFCEXTEND_RETVAL nfcextend_init ( nfcextend_t *ctx, nfcextend_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return NFCEXTEND_INIT_ERROR;
    }
    
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return NFCEXTEND_OK;
}

uint8_t nfcextend_default_cfg ( nfcextend_t *ctx )
{
    nfcextend_block_t block;

    uint8_t temp_val;

    temp_val = 0x82;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_GPO, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x03;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_IT_TIME, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x01;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_EH_MODE, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x00;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_RF_MNGT, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x00;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_RFA1SS, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x00;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_ENDA1, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x00;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_RFA2SS, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x00;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_RFA3SS, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x00;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_RFA4SS, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x00;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_I2CSS, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x00;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_LOCK_CCFILE, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x01;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_MB_MODE, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x07;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_MB_WDG, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x00;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_SYSTEM, 
                                     NFCEXTEND_SYSTEM_REG_LOCK_CFG, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x82;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_DYNAMIC, 
                                     NFCEXTEND_DYNAMIC_REG_GPO_CTRL, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x01;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_DYNAMIC, 
                                     NFCEXTEND_DYNAMIC_REG_EH_CTRL, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x00;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_DYNAMIC, 
                                     NFCEXTEND_DYNAMIC_REG_RF_MNGT, &temp_val ) )
    {
        return 1;
    }

    temp_val = 0x01;
    if ( 0 != drv_single_write( ctx, NFCEXTEND_MEMORY_DYNAMIC, 
                                     NFCEXTEND_DYNAMIC_REG_MB_CTRL, &temp_val ) )
    {
        return 1;
    }

    return 0;
}

uint8_t nfcextend_password_present ( nfcextend_t *ctx, uint8_t *pass_buf )
{
    nfcextend_block_t block;

    uint8_t temp_buf[ NFCEXTEND_PASSWORD_BUFFER_SIZE ];
    uint8_t cnt;

    for ( cnt = 0; cnt < NFCEXTEND_PASSWORD_LEN; cnt++ )
    {
        temp_buf[ cnt ] = pass_buf[ cnt ];
        temp_buf[ cnt + 9 ] = pass_buf[ cnt ];
    }

    temp_buf[ 8 ] = 0x09; /* validation code */

    block.memory_area = NFCEXTEND_MEMORY_SYSTEM;
    block.reg_addr = NFCEXTEND_SYSTEM_REG_I2C_PWD_1;
    block.data_buf = temp_buf;
    block.len = NFCEXTEND_PASSWORD_BUFFER_SIZE;

    if( 0 != nfcextend_i2c_set( ctx, &block ) )
    {
        return 1;
    }

    return 0;
}

uint8_t nfcextend_i2c_set ( nfcextend_t *ctx, nfcextend_block_t *block )
{
    uint8_t temp_buf[ 258 ];
    uint8_t temp_slave_addr;
    uint16_t cnt;

    if ( block->memory_area > 4 || block->memory_area < 1 || block->len > 256 )
    {
        return 1;
    }

    temp_buf[ 0 ] = block->reg_addr >> 8;
    temp_buf[ 1 ] = block->reg_addr;

    for ( cnt = 0; cnt < block->len; cnt++ )
    {
        temp_buf[ cnt + 2 ] = block->data_buf[ cnt ];
    }

    if ( block->memory_area == 0x04 )
    {
        temp_slave_addr = ctx->slave_address |= 0x04;
    }
    else 
    {
        temp_slave_addr = ctx->slave_address;
    }

    i2c_master_set_slave_address( &ctx->i2c,  temp_slave_addr );
    i2c_master_write( &ctx->i2c, temp_buf,  block->len + 2 );   

    return 0;
}

uint8_t nfcextend_i2c_get ( nfcextend_t *ctx, nfcextend_block_t *block )
{
    uint8_t temp_buf[ 2 ];
    uint8_t temp_slave_addr;

    if ( block->memory_area > 4 || block->memory_area < 1 || block->len > 256 )
    {
        return 1;
    }

    temp_buf[ 0 ] = ( uint8_t ) block->reg_addr >> 8;
    temp_buf[ 1 ] = ( uint8_t ) block->reg_addr;

    if ( block->memory_area == 0x04 )
    {
        temp_slave_addr = ctx->slave_address |= 0x04;
    }
    else 
    {
        temp_slave_addr = ctx->slave_address;
    }

    i2c_master_set_slave_address( &ctx->i2c,  temp_slave_addr );
    i2c_master_write_then_read( &ctx->i2c,temp_buf, 2, block->data_buf, block->len );

    return 0;
}

uint8_t nfcextend_digital_read_int ( nfcextend_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

uint8_t drv_single_write ( nfcextend_t *ctx, uint8_t memory_area, 
                          uint16_t reg_addr, uint8_t *data_buf )
{
    nfcextend_block_t block;

    block.memory_area = memory_area;
    block.reg_addr = reg_addr;
    block.data_buf = data_buf;
    block.len = 1;

    if ( 0 != nfcextend_i2c_set( ctx, &block ) )
    {
        return 1;
    }
    Delay_ms( 10 );

    return 0;
}

// ------------------------------------------------------------------------- END

