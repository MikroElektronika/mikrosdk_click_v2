/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file eeprom12.c
 * @brief EEPROM 12 Click Driver.
 */

#include "eeprom12.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY    0x00

void eeprom12_cfg_setup ( eeprom12_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wc = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EEPROM12_DEVICE_ADDRESS_MEMORY;
}

err_t eeprom12_init ( eeprom12_t *ctx, eeprom12_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->chip_en_addr = EEPROM12_DEFAULT_CHIP_ENABLE_ADDRESS;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->wc, cfg->wc );
    
    return I2C_MASTER_SUCCESS;
}

void eeprom12_write_enable ( eeprom12_t *ctx )
{
    digital_out_low( &ctx->wc );
}

void eeprom12_write_disable ( eeprom12_t *ctx )
{
    digital_out_high( &ctx->wc );
}

err_t eeprom12_generic_write ( eeprom12_t *ctx, uint16_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( reg >> 8 );
    data_buf[ 1 ] = ( uint8_t ) reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    err_t err_flag = i2c_master_write( &ctx->i2c, data_buf, len + 2 );
    return err_flag;
}

err_t eeprom12_generic_read ( eeprom12_t *ctx, uint16_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( reg >> 8 );
    data_buf[ 1 ] = ( uint8_t ) reg;
    err_t err_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    err_flag |= i2c_master_read( &ctx->i2c, data_out, len );
    return err_flag;
}

err_t eeprom12_memory_write ( eeprom12_t *ctx, uint16_t mem_addr, uint8_t *data_in, uint8_t len ) 
{
    err_t err_flag = EEPROM12_ERROR;
    if ( EEPROM12_MEMORY_ADDRESS_MAX >= ( mem_addr + len ) )
    {
        err_flag = i2c_master_set_slave_address( &ctx->i2c, EEPROM12_DEVICE_ADDRESS_MEMORY | 
                                                            ctx->chip_en_addr );
        Delay_1ms( );
        eeprom12_write_enable( ctx );
        Delay_1ms( );
        err_flag |= eeprom12_generic_write( ctx, mem_addr, data_in, len );
        Delay_1ms( );
        eeprom12_write_disable( ctx );
    }
    return err_flag;
}

err_t eeprom12_memory_read ( eeprom12_t *ctx, uint16_t mem_addr, uint8_t *data_out, uint8_t len ) 
{
    err_t err_flag = EEPROM12_ERROR;
    if ( EEPROM12_MEMORY_ADDRESS_MAX >= ( mem_addr + len ) )
    {
        err_flag = i2c_master_set_slave_address( &ctx->i2c, EEPROM12_DEVICE_ADDRESS_MEMORY | 
                                                            ctx->chip_en_addr );
        Delay_1ms( );
        err_flag |= eeprom12_generic_read( ctx, mem_addr, data_out, len );
    }
    return err_flag;
}

err_t eeprom12_memory_page_write ( eeprom12_t *ctx, uint16_t page_addr, uint8_t *data_in, uint8_t len ) 
{
    err_t err_flag = EEPROM12_ERROR;
    if ( ( EEPROM12_PAGE_SIZE >= len ) && ( EEPROM12_PAGE_MAX >= page_addr ) )
    {
        page_addr *= EEPROM12_PAGE_SIZE;
        err_flag = i2c_master_set_slave_address( &ctx->i2c, EEPROM12_DEVICE_ADDRESS_PAGE | 
                                                            ctx->chip_en_addr );
        Delay_1ms( );
        eeprom12_write_enable( ctx );
        Delay_1ms( );
        err_flag |= eeprom12_generic_write( ctx, page_addr, data_in, len );
        Delay_1ms( );
        eeprom12_write_disable( ctx );
    }
    return err_flag;
}

err_t eeprom12_memory_page_read ( eeprom12_t *ctx, uint16_t page_addr, uint8_t *data_out, uint8_t len ) 
{
    err_t err_flag = EEPROM12_ERROR;
    if ( ( EEPROM12_PAGE_SIZE >= len ) && ( EEPROM12_PAGE_MAX > page_addr ) )
    {
        err_flag = i2c_master_set_slave_address( &ctx->i2c, EEPROM12_DEVICE_ADDRESS_PAGE | 
                                                            ctx->chip_en_addr );
        Delay_1ms( );
        err_flag |= eeprom12_generic_read( ctx, page_addr, data_out, len );
    }
    return err_flag;
}

err_t eeprom12_id_page_write ( eeprom12_t *ctx, uint16_t id_page_addr, uint8_t *data_in ) 
{
    err_t err_flag = EEPROM12_ERROR;
    if ( EEPROM12_PAGE_SIZE > id_page_addr )
    {
        uint16_t data_buf = EEPROM12_REG_IDENTIFICATION_PAGE;
        data_buf |= id_page_addr;
        err_flag = i2c_master_set_slave_address( &ctx->i2c, EEPROM12_DEVICE_ADDRESS_PAGE | 
                                                            ctx->chip_en_addr );
        Delay_1ms( );
        eeprom12_write_enable( ctx );
        Delay_1ms( );
        err_flag |= eeprom12_generic_write( ctx, id_page_addr, data_in, EEPROM12_PAGE_SIZE - id_page_addr );
        Delay_1ms( );
        eeprom12_write_disable( ctx );
    }
    return err_flag;
}

err_t eeprom12_id_page_read ( eeprom12_t *ctx, uint16_t id_page_addr, uint8_t *data_out ) 
{
    err_t err_flag = EEPROM12_ERROR;
    if ( EEPROM12_PAGE_SIZE >= id_page_addr )
    {
        uint16_t data_buf = EEPROM12_REG_IDENTIFICATION_PAGE;
        data_buf |= id_page_addr;
        err_flag = i2c_master_set_slave_address( &ctx->i2c, EEPROM12_DEVICE_ADDRESS_PAGE | 
                                                            ctx->chip_en_addr );
        Delay_1ms( );
        err_flag |= eeprom12_generic_read( ctx, data_buf, data_out, EEPROM12_PAGE_SIZE - id_page_addr );
    }
    return err_flag;
}

err_t eeprom12_config_dev_addr ( eeprom12_t *ctx, uint8_t cda, uint8_t dal ) 
{
    uint8_t data_buf = DUMMY;
    cda &= EEPROM12_CDA_CEA_BIT_MASK;
    dal &= EEPROM12_CDA_DAL_BIT_MASK;
    data_buf = cda << 1;
    data_buf |= dal;
    err_t err_flag = i2c_master_set_slave_address( &ctx->i2c, EEPROM12_DEVICE_ADDRESS_PAGE | 
                                                              ctx->chip_en_addr );
    Delay_1ms( );
    eeprom12_write_enable( ctx );
    Delay_1ms( );
    err_flag |= eeprom12_generic_write( ctx, EEPROM12_REG_CONFIG_DEVICE_ADDRESS, &data_buf, 1 );
    Delay_1ms( );
    eeprom12_write_disable( ctx );
    ctx->chip_en_addr = cda;
    return err_flag;
}

err_t eeprom12_read_lock_status ( eeprom12_t *ctx, uint8_t *lock_status ) 
{
    uint8_t data_buf = DUMMY;

    err_t err_flag = i2c_master_set_slave_address( &ctx->i2c, EEPROM12_DEVICE_ADDRESS_PAGE | 
                                                              ctx->chip_en_addr );
    Delay_1ms( );
    err_flag |= eeprom12_generic_write( ctx, EEPROM12_REG_IDENTIFICATION_PAGE_LOCK, lock_status, 1 );
    return err_flag;
}

// ------------------------------------------------------------------------- END
