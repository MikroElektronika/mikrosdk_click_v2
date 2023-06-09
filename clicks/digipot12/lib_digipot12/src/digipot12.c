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
 * @file digipot12.c
 * @brief DIGI POT 12 Click Driver.
 */

#include "digipot12.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                                       0x00

/**
 * @brief DIGI POT 12 check address bit selection function.
 * @details This function checks address bit selection.
 * @param[in] addr : Address bit value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t digipot12_check_addr ( uint8_t addr );

void digipot12_cfg_setup ( digipot12_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DIGIPOT12_DEVICE_ADDRESS_0;
}

err_t digipot12_init ( digipot12_t *ctx, digipot12_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

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

    digital_out_init( &ctx->rst, cfg->rst );
    
    return I2C_MASTER_SUCCESS;
}

err_t digipot12_default_cfg ( digipot12_t *ctx ) 
{
    digipot12_device_enable( ctx );
    Delay_100ms( );
    err_t err_flag = digipot12_set_wiper_1( ctx, DIGIPOT12_WIPER_POS_MIDDLE );
    Delay_1ms( );
    err_flag |= digipot12_set_wiper_2( ctx, DIGIPOT12_WIPER_POS_MIDDLE );
    Delay_1ms( );
    return err_flag;
}

void digipot12_device_enable ( digipot12_t *ctx ) 
{
    digital_out_high( &ctx->rst );
}

void digipot12_hw_reset ( digipot12_t *ctx ) 
{
    digital_out_low( &ctx->rst );
    Delay_10ms( );
    digital_out_high( &ctx->rst );
    Delay_10ms( );
}

err_t digipot12_write_data ( digipot12_t *ctx, uint8_t ctrl, uint8_t addr, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = DIGIPOT12_ERROR;
    if ( DIGIPOT12_OK == digipot12_check_addr( addr ) )
    {
        ctrl &= DIGIPOT12_CTRL_BIT_MASK;
        data_buf[ 0 ] = ctrl | addr;
        data_buf[ 1 ] = data_in;
        err_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    }
    return err_flag;
}

err_t digipot12_read_data ( digipot12_t *ctx, uint8_t addr, uint8_t mask, uint8_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = DIGIPOT12_ERROR;
    if ( DIGIPOT12_OK == digipot12_check_addr( addr ) )
    {
        data_buf[ 0 ] = DIGIPOT12_CTRL_BIT_READ | addr;
        data_buf[ 1 ] = mask;
        err_flag = i2c_master_write_then_read( &ctx->i2c, data_buf, 2, data_out, 1 );
    }
    return err_flag;
}

err_t digipot12_write_rdac ( digipot12_t *ctx, uint8_t addr, uint8_t data_in ) 
{
    err_t err_flag = DIGIPOT12_ERROR;
    if ( DIGIPOT12_OK == digipot12_check_addr( addr ) )
    {
        err_flag = digipot12_write_data( ctx, DIGIPOT12_CTRL_BIT_WRITE_RDAC, addr, data_in );
    }
    return err_flag;
}

err_t digipot12_read_rdac ( digipot12_t *ctx, uint8_t addr, uint8_t *data_out ) 
{
    err_t err_flag = DIGIPOT12_ERROR;
    if ( DIGIPOT12_OK == digipot12_check_addr( addr ) )
    {
        err_flag = digipot12_read_data( ctx, addr, DIGIPOT12_ADDR_BIT_READ_RDAC, data_out );
    }
    return err_flag;
}

err_t digipot12_set_wiper_1 ( digipot12_t *ctx, uint8_t wiper_pos ) 
{
    return digipot12_write_rdac( ctx, DIGIPOT12_ADDR_BIT_RDAC1, wiper_pos );
}

err_t digipot12_set_wiper_2 ( digipot12_t *ctx, uint8_t wiper_pos ) 
{
    return digipot12_write_rdac( ctx, DIGIPOT12_ADDR_BIT_RDAC2, wiper_pos );
}

err_t digipot12_set_resistance ( digipot12_t *ctx, uint8_t wiper_sel, float res_kohm ) 
{
    err_t err_flag = DIGIPOT12_OK;
    if ( ( res_kohm > DIGIPOT12_RES_10_KOHM ) || 
         ( DIGIPOT12_ERROR == digipot12_check_addr( wiper_sel ) ) )
    {
         err_flag = DIGIPOT12_ERROR;  
    }
    else
    {
        float wiper_pos = ( float ) res_kohm;
        wiper_pos *= ( float ) DIGIPOT12_WIPER_POS_MAX;
        wiper_pos /= ( float ) DIGIPOT12_RES_10_KOHM;
        err_flag |= digipot12_write_rdac( ctx, wiper_sel, ( uint8_t ) wiper_pos ); 
    }
    return err_flag;
}

err_t digipot12_get_resistance ( digipot12_t *ctx, uint8_t wiper_sel, float *res_kohm ) 
{
    err_t err_flag = DIGIPOT12_OK;
    uint8_t data_buf = DUMMY; 
    if ( DIGIPOT12_ERROR == digipot12_check_addr( wiper_sel ) )
    {
         err_flag = DIGIPOT12_ERROR;  
    }
    else
    {
        err_flag |= digipot12_read_rdac( ctx, wiper_sel, &data_buf );
        *res_kohm =  ( float ) DIGIPOT12_RES_10_KOHM;
        *res_kohm /= ( float ) DIGIPOT12_WIPER_POS_MAX;
        *res_kohm *= ( float ) data_buf;
    }
    return err_flag;
}

static err_t digipot12_check_addr ( uint8_t addr ) 
{
    err_t err_flag = DIGIPOT12_ERROR;
    if ( ( DIGIPOT12_ADDR_BIT_RDAC1 == addr ) || 
         ( DIGIPOT12_ADDR_BIT_RDAC2 == addr ) ||
         ( DIGIPOT12_ADDR_BIT_ALL_CHANNELS == addr ) )
    {
        err_flag = DIGIPOT12_OK;
    }
    return err_flag;
}

// ------------------------------------------------------------------------- END
