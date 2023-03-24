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
 * @file efuse4.c
 * @brief eFuse 4 Click Driver.
 */

#include "efuse4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                                     0

/**
 * @brief Digital potentiometer data.
 * @details Definition of digital potentiometer.
 */
#define EFUSE4_DIGI_POT_5_BIT_DATA           0x001F
#define EFUSE4_DIGI_POT_10_BIT_DATA          0x03FF
#define EFUSE4_DIGI_POT_WIPER_POS_MAX          1023

/**
 * @brief eFuse 4 Resistance data.
 * @details Definition of eFuse 4 resistance data values.
 */
#define EFUSE4_RESISTANCE_116900_Ohm         116900
#define EFUSE4_RESISTANCE_100000_Ohm         100000
#define EFUSE4_RESISTANCE_88700_Ohm           88700
#define EFUSE4_RESISTANCE_42200_Ohm           42200
#define EFUSE4_RESISTANCE_24900_Ohm           24900
#define EFUSE4_RESISTANCE_20000_Ohm           20000
#define EFUSE4_RESISTANCE_16900_Ohm           16900

void efuse4_cfg_setup ( efuse4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->pgd = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->dsv = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EFUSE4_DEVICE_ADDRESS;
}

err_t efuse4_init ( efuse4_t *ctx, efuse4_cfg_t *cfg ) 
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
    digital_out_init( &ctx->dsv, cfg->dsv );

    digital_in_init( &ctx->pgd, cfg->pgd );
    digital_in_init( &ctx->flt, cfg->flt );

    return I2C_MASTER_SUCCESS;
}

err_t efuse4_default_cfg ( efuse4_t *ctx ) 
{  
    efuse4_set_enable( ctx );
    Delay_10ms();
    efuse4_set_normal_mode( ctx );
    Delay_10ms();
    err_t err_flag = efuse4_sw_reset( ctx );
    Delay_10ms();
    err_flag |= efuse4_digi_pot_op_mode( ctx, EFUSE4_SET_NORMAL_MODE );
    Delay_10ms();
    err_flag |= efuse4_enable_write( ctx ); 
    Delay_10ms();
    err_flag |= efuse4_set_current_limit ( ctx, EFUSE4_CURRENT_LIMIT_750_mA );
    
    return err_flag;
}

err_t efuse4_generic_write ( efuse4_t *ctx, uint8_t cmd, uint16_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    
    data_in &= EFUSE4_DIGI_POT_10_BIT_DATA;
    data_buf[ 0 ]  = cmd;
    data_buf[ 0 ] |= ( uint8_t ) ( data_in >> 8 );
    data_buf[ 1 ]  = ( uint8_t ) data_in;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t efuse4_generic_read ( efuse4_t *ctx, uint8_t cmd, uint16_t data_in, uint16_t *data_out ) 
{
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 2 ] ;

    data_in &= EFUSE4_DIGI_POT_5_BIT_DATA;
    tx_buf[ 1 ] = DUMMY;
    if ( cmd == EFUSE4_CMD_READ_CONTENTS )
    {
        tx_buf[ 1 ] = data_in;
    }

    tx_buf[ 0 ]  = cmd;
    tx_buf[ 0 ] |= ( uint8_t ) ( data_in >> 8 );
    tx_buf[ 1 ]  = ( uint8_t ) data_in;

    err_t err_flag = i2c_master_write( &ctx->i2c, tx_buf, 2 );
    err_flag |= i2c_master_read( &ctx->i2c, rx_buf, 2 );

    *data_out = rx_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];
    *data_out &= EFUSE4_DIGI_POT_10_BIT_DATA;

    return err_flag;
}

void efuse4_set_enable ( efuse4_t *ctx )
{
    digital_out_low( &ctx->rst );
}

void efuse4_set_disable ( efuse4_t *ctx )
{
    digital_out_high( &ctx->rst );
}

void efuse4_set_low_power_mode ( efuse4_t *ctx )
{
    digital_out_high( &ctx->dsv );
}

void efuse4_set_normal_mode ( efuse4_t *ctx )
{
    digital_out_low( &ctx->dsv );
}

err_t efuse4_sw_reset ( efuse4_t *ctx )
{
    return efuse4_generic_write( ctx, EFUSE4_CMD_SW_RESET, DUMMY );
}

err_t efuse4_enable_write ( efuse4_t *ctx )
{    
    return efuse4_generic_write( ctx, EFUSE4_CMD_WRITE_MEMORY, EFUSE4_SET_ENABLE_WRITE_MEMORY );
}

err_t efuse4_write_rdac ( efuse4_t *ctx, uint16_t data_in )
{
    return efuse4_generic_write( ctx, EFUSE4_CMD_WRITE_RDAC, data_in );
}

err_t efuse4_read_rdac ( efuse4_t *ctx, uint16_t *data_out )
{    
    return efuse4_generic_read( ctx, EFUSE4_CMD_READ_RDAC, DUMMY, data_out );
}

err_t efuse4_digi_pot_op_mode ( efuse4_t *ctx, uint8_t mode )
{
    return efuse4_generic_write( ctx, EFUSE4_CMD_SW_SHUTDOWN, mode & EFUSE4_SET_NORMAL_MODE );
}

err_t efuse4_store_wiper_pos ( efuse4_t *ctx )
{
    return efuse4_generic_write( ctx, EFUSE4_CMD_STORE_WIPER, DUMMY );
}

err_t efuse4_next_frame_read ( efuse4_t *ctx, uint8_t wiper_location, uint16_t *data_out )
{   
    return efuse4_generic_read( ctx, EFUSE4_CMD_READ_RDAC, wiper_location, data_out );
}

err_t efuse4_read_memory ( efuse4_t *ctx, uint16_t *data_out )
{   
    return efuse4_generic_read( ctx, EFUSE4_CMD_READ_MEMORY, DUMMY, data_out );
}

err_t efuse4_set_digi_pot ( efuse4_t *ctx, uint16_t wiper_pos )
{
    return efuse4_write_rdac( ctx, wiper_pos & EFUSE4_DIGI_POT_10_BIT_DATA );
}

err_t efuse4_set_resistance ( efuse4_t *ctx, uint32_t res_ohm )
{
    err_t err_flag = EFUSE4_ERROR;

    if ( res_ohm <= EFUSE4_RESISTANCE_116900_Ohm )
    {
        float tmp  = ( float ) res_ohm;
        tmp  -= EFUSE4_RESISTANCE_16900_Ohm;
        tmp /= EFUSE4_RESISTANCE_100000_Ohm;
        tmp *= EFUSE4_DIGI_POT_WIPER_POS_MAX;
        err_flag = efuse4_set_digi_pot( ctx, ( uint16_t ) tmp );   
    }
    return err_flag;
}

err_t efuse4_set_current_limit ( efuse4_t *ctx, efuse4_current_limit_t current_limit )
{
    err_t err_flag = EFUSE4_ERROR;
    efuse4_set_normal_mode( ctx );

    switch ( current_limit )
    {
        case EFUSE4_CURRENT_LIMIT_670_mA:
        {
            err_flag = EFUSE4_OK;
            efuse4_set_low_power_mode( ctx );
            break;
        }
        case EFUSE4_CURRENT_LIMIT_750_mA:
        {
            err_flag = efuse4_set_resistance( ctx, EFUSE4_RESISTANCE_116900_Ohm );
            break;
        }
        case EFUSE4_CURRENT_LIMIT_990_mA: 
        {
            err_flag = efuse4_set_resistance( ctx, EFUSE4_RESISTANCE_88700_Ohm );
            break;
        }
        case EFUSE4_CURRENT_LIMIT_2080_mA: 
        {
            err_flag = efuse4_set_resistance( ctx, EFUSE4_RESISTANCE_42200_Ohm );
            break;
        }
        case EFUSE4_CURRENT_LIMIT_3530_mA: 
        {
            err_flag = efuse4_set_resistance( ctx, EFUSE4_RESISTANCE_24900_Ohm );
            break;
        }
        case EFUSE4_CURRENT_LIMIT_4450_mA: 
        {
            err_flag = efuse4_set_resistance( ctx, EFUSE4_RESISTANCE_20000_Ohm );
            break;
        }
        case EFUSE4_CURRENT_LIMIT_5200_mA: 
        {
            err_flag = efuse4_set_resistance( ctx, EFUSE4_RESISTANCE_16900_Ohm );
            break;
        }
        default: 
        {
            err_flag |= efuse4_set_resistance( ctx, EFUSE4_RESISTANCE_116900_Ohm );
            break;
        }    
    }
    return err_flag;
}

uint8_t efuse4_fault_state ( efuse4_t *ctx )
{
    return digital_in_read( &ctx->flt );
}

uint8_t efuse4_pwr_good_state ( efuse4_t *ctx )
{
    return digital_in_read( &ctx->pgd );
}

// ------------------------------------------------------------------------- END
