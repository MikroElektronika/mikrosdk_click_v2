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

#include "nfctag4.h"

// ------------------------------------------------ PRIVATE FUNCTION DEFINITIONS

void transfer_delay( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void nfctag4_cfg_setup ( nfctag4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = NFCTAG4_DEVICE_ADDRESS;
}

NFCTAG4_RETVAL nfctag4_init ( nfctag4_t *ctx, nfctag4_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return NFCTAG4_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return NFCTAG4_OK;
}

void nfctag4_default_cfg ( nfctag4_t *ctx )
{
    uint8_t aux_buf[ 1 ];
    transfer_info dev;
    uint8_t default_password[ 8 ] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    nfctag4_password_present( ctx, default_password );
    Delay_100ms();

    aux_buf[ 0 ] = 0x82;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_GPO;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x03;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_IT_TIME;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x01;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_EH_MODE;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x00;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_RF_MNGT;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x00;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_RFA1SS;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x3F;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_ENDA1;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x00;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_RFA2SS;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x00;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_RFA3SS;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[0] = 0x00;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_RFA4SS;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x00;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_I2CSS;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x00;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_LOCK_CCFILE;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x01;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_MB_MODE;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x07;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_MB_WDG;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x00;
    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_LOCK_CFG;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x82;
    dev.memory_area = NFCTAG4_MEMORY_DYNAMIC;
    dev.register_address = NFCTAG4_DYNAMIC_REG_GPO_CTRL;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x01;
    dev.memory_area = NFCTAG4_MEMORY_DYNAMIC;
    dev.register_address = NFCTAG4_DYNAMIC_REG_EH_CTRL;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );

    aux_buf[ 0 ] = 0x00;
    dev.memory_area = NFCTAG4_MEMORY_DYNAMIC;
    dev.register_address = NFCTAG4_DYNAMIC_REG_RF_MNGT;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    Delay_10ms();

    aux_buf[ 0 ] = 0x01;
    dev.memory_area = NFCTAG4_MEMORY_DYNAMIC;
    dev.register_address = NFCTAG4_DYNAMIC_REG_MB_CTRL;
    dev.n_registers = 1;
    nfctag4_i2c_set( ctx, &dev, aux_buf );
    transfer_delay( );
}

uint8_t nfctag4_int_get ( nfctag4_t* ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t nfctag4_i2c_get ( nfctag4_t* ctx, transfer_info* dev, uint8_t* register_buffer )
{
    uint8_t aux_buf[ 2 ];
    uint8_t aux_slave_address;

    if ( dev->memory_area > 4 )
    {
        return 1;
    }
    else if ( dev->memory_area < 1 )
    {
        return 1;
    }
    else if ( dev->n_registers > 256 )
    {
        return 1;
    }

    aux_buf[ 0 ] = ( uint8_t )( dev->register_address >> 8 );
    aux_buf[ 1 ] = ( uint8_t )( dev->register_address >> 0 );

    aux_slave_address = ctx->slave_address;

    if ( dev->memory_area == 0x04 )
    {
        aux_slave_address |= 0x04;
    }

    i2c_master_set_slave_address( &ctx->i2c, aux_slave_address );
    i2c_master_write_then_read( &ctx->i2c, aux_buf, 2, register_buffer, dev->n_registers );

    return 0;
}

uint8_t nfctag4_i2c_set ( nfctag4_t* ctx, transfer_info* dev, uint8_t* register_buffer )
{
    uint8_t aux_buf[ 258 ];
    uint8_t aux_slave_address;
    uint16_t i;

    if ( dev->memory_area > 4 )
    {
        return 1;
    }
    else if ( dev->memory_area < 1 )
    {
        return 1;
    }
    else if ( dev->n_registers > 256 )
    {
        return 1;
    }

    aux_buf[ 0 ] = ( uint8_t )( dev->register_address >> 8 );
    aux_buf[ 1 ] = ( uint8_t )( dev->register_address >> 0 );

    for ( i = 0; i < dev->n_registers; i++ )
    {
        aux_buf[ i + 2 ] = register_buffer[ i ];
    }

    aux_slave_address = ctx->slave_address;

    if ( dev->memory_area == 0x04 )
    {
        aux_slave_address |= 0x04;
    }

    i2c_master_set_slave_address( &ctx->i2c, aux_slave_address );
    i2c_master_write( &ctx->i2c, aux_buf, dev->n_registers + 2 );

    return 0;
}

uint8_t nfctag4_password_present ( nfctag4_t* ctx, uint8_t* password_bytes )
{
    uint8_t aux_buf[ 17 ];
    transfer_info dev;
    uint8_t i;

    for ( i = 0; i < 8; i++ )
    {
        aux_buf[ i + 0 ] = password_bytes[ i ];
        aux_buf[ i + 9 ] = password_bytes[ i ];
    }

    aux_buf[ 8 ] = 0x09; // validation code 

    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_I2C_PWD_1;
    dev.n_registers = 17;

    if ( 0 != nfctag4_i2c_set( ctx, &dev, aux_buf ) )
    {
        return 1;
    }

    return 0;
}

uint8_t nfctag4_password_write ( nfctag4_t* ctx, uint8_t* password_bytes )
{
    uint8_t aux_buf[ 17 ];
    transfer_info dev;
    uint8_t i;

    for ( i = 0; i < 8; i++ )
    {
        aux_buf[ i + 0 ] = password_bytes[ i ];
        aux_buf[ i + 9 ] = password_bytes[ i ];
    }

    aux_buf[ 8 ] = 0x07; // validation code 

    dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
    dev.register_address = NFCTAG4_SYSTEM_REG_I2C_PWD_1;
    dev.n_registers = 17;
    if ( 0 != nfctag4_i2c_set( ctx, &dev, aux_buf ) )
    {
        return 1;
    }

    return 0;
}

uint8_t nfctag4_enable_mailbox ( nfctag4_t* ctx, uint8_t enable_mailbox )
{
    uint8_t aux_buf[ 1 ];
    transfer_info dev;

    switch ( enable_mailbox )
    {
        case NFCTAG4_MAILBOX_DISABLE:
        {
            aux_buf[ 0 ] = 0x00;

            dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
            dev.register_address = NFCTAG4_SYSTEM_REG_MB_MODE;
            dev.n_registers = 1;
            if ( 0 != nfctag4_i2c_set( ctx, &dev, aux_buf ) )
            {
                return 1;
            }

            break;
        }
        case NFCTAG4_MAILBOX_ENABLE:
        {
            aux_buf[ 0 ] = 0x01;

            dev.memory_area = NFCTAG4_MEMORY_SYSTEM;
            dev.register_address = NFCTAG4_SYSTEM_REG_MB_MODE;
            dev.n_registers = 1;
            if ( 0 != nfctag4_i2c_set( ctx, &dev, aux_buf ) )
            {
                return 1;
            }

            aux_buf[ 0 ] = 0x01;

            dev.memory_area = NFCTAG4_MEMORY_DYNAMIC;
            dev.register_address = NFCTAG4_DYNAMIC_REG_MB_CTRL;
            dev.n_registers = 1;
            if ( 0 != nfctag4_i2c_set( ctx, &dev, aux_buf ) )
            {
                return 1;
            }

            break;
        }
        default:
        {
            break;
        }
    }
    return 0;
}

uint8_t nfctag4_enable_rf ( nfctag4_t* ctx, uint8_t enable_rf )
{
    uint8_t aux_buf[ 1 ];
    transfer_info dev;

    switch ( enable_rf )
    {
        case NFCTAG4_RF_DISABLE:
        {
            aux_buf[ 0 ] = 0x03;

            dev.memory_area = NFCTAG4_MEMORY_DYNAMIC;
            dev.register_address = NFCTAG4_DYNAMIC_REG_RF_MNGT;
            dev.n_registers = 1;
            if ( 0 != nfctag4_i2c_set( ctx, &dev, aux_buf ) )
            {
                return 1;
            }

            break;
        }
        case NFCTAG4_RF_ENABLE:
        {
            aux_buf[ 0 ] = 0x00;

            dev.memory_area = NFCTAG4_MEMORY_DYNAMIC;
            dev.register_address = NFCTAG4_DYNAMIC_REG_RF_MNGT;
            dev.n_registers = 1;
            if ( 0 != nfctag4_i2c_set( ctx, &dev, aux_buf ) )
            {
                return 1;
            }

            break;
        }
        default:
        {
            break;
        }
    }
    return 0;
}

// -------------------------------------------------------------PRIVATE FUNCTIONS

void transfer_delay ( void )
{
    Delay_10ms();
}

// ------------------------------------------------------------------------- END

