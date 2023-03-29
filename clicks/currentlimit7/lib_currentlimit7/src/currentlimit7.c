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
 * @file currentlimit7.c
 * @brief Current Limit 7 Click Driver.
 */

#include "currentlimit7.h"

#define DUMMY                                            0
#define CURRENTLIMIT7_SEL_RESISTANCE_53_6_kOhm       53600
#define CURRENTLIMIT7_SEL_RESISTANCE_300_kOhm       300000
#define CURRENTLIMIT7_OP_0_CURRENT_LIMIT_MIN           260
#define CURRENTLIMIT7_OP_0_CURRENT_LIMIT_MAX           450
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_MIN           500
#define CURRENTLIMIT7_OP_1_CURRENT_LIMIT_MAX          2500
#define CURRENTLIMIT7_RESISTANCE_53_6_kOhm           53600
#define CURRENTLIMIT7_RESISTANCE_57_6_kOhm           57600
#define CURRENTLIMIT7_RESISTANCE_64_kOhm             64000
#define CURRENTLIMIT7_RESISTANCE_75_kOhm             75000
#define CURRENTLIMIT7_RESISTANCE_85_kOhm             85000
#define CURRENTLIMIT7_RESISTANCE_90_kOhm             90000
#define CURRENTLIMIT7_RESISTANCE_100_kOhm           100000
#define CURRENTLIMIT7_RESISTANCE_150_kOhm           150000
#define CURRENTLIMIT7_RESISTANCE_200_kOhm           200000
#define CURRENTLIMIT7_RESISTANCE_261_kOhm           251000
#define CURRENTLIMIT7_RESISTANCE_301_kOhm           301000
#define CURRENTLIMIT7_RESISTANCE_420_kOhm           402000
#define CURRENTLIMIT7_RESISTANCE_470_kOhm           470000
#define CURRENTLIMIT7_RESISTANCE_510_kOhm           501000
#define CURRENTLIMIT7_DIGI_POT_5_BIT_DATA           0x001F
#define CURRENTLIMIT7_DIGI_POT_10_BIT_DATA          0x03FF
#define CURRENTLIMIT7_DIGI_POT_WIPER_POS_MAX          2047

/**
 * @brief Current Limit 7 reset delay function.
 * @details This function executes a reset delay of the 100 milliseconds. 
 */
static void dev_reset_delay ( void );

/**
 * @brief Current Limit 7 config delay function.
 * @details This function executes a configuration delay of the 100 milliseconds. 
 */
static void dev_cfg_delay ( void );

/**
 * @brief Current Limit 7 addr sel delay function.
 * @details This function executes a slave address selection delay of the 10 milliseconds. 
 */
static void dev_addr_sel_delay ( void );

/**
 * @brief Current Limit 7 read delay function.
 * @details This function executes a read delay of the 1 milliseconds. 
 */
static void dev_read_delay ( void );

void currentlimit7_cfg_setup ( currentlimit7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->flg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CURRENTLIMIT7_SET_DEV_ADDR_0;
}

err_t currentlimit7_init ( currentlimit7_t *ctx, currentlimit7_cfg_t *cfg ) 
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
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->flg, cfg->flg );

    return I2C_MASTER_SUCCESS;
}

err_t currentlimit7_default_cfg ( currentlimit7_t *ctx ) 
{   
    err_t error_flag = currentlimit7_hw_reset( ctx );
    
    error_flag |= currentlimit7_set_enable( ctx );
    dev_cfg_delay( );
    
    error_flag |= currentlimit7_set_slave_address( ctx, CURRENTLIMIT7_SET_DEV_ADDR_0 );
    error_flag |= currentlimit7_sw_reset( ctx );
    dev_cfg_delay( );
    
    error_flag |= currentlimit7_set_slave_address( ctx, CURRENTLIMIT7_SET_DEV_ADDR_1 );
    error_flag |= currentlimit7_sw_reset( ctx );
    dev_cfg_delay( );

    error_flag |= currentlimit7_set_slave_address( ctx, CURRENTLIMIT7_SET_DEV_ADDR_0 );
    error_flag |= currentlimit7_enable_write( ctx );
    dev_cfg_delay( );
    
    error_flag |= currentlimit7_set_slave_address( ctx, CURRENTLIMIT7_SET_DEV_ADDR_1 );
    error_flag |= currentlimit7_enable_write( ctx );
    dev_cfg_delay( );
    
    error_flag |= currentlimit7_set_current_limit( ctx, CURRENTLIMIT7_OP_MODE_500_mA_2500_mA, CURRENTLIMIT7_OP_1_CURRENT_LIMIT_510_mA );
    
    return error_flag;
}

err_t currentlimit7_set_slave_address ( currentlimit7_t *ctx, uint16_t slave_address )
{
    if ( ( slave_address != CURRENTLIMIT7_SET_DEV_ADDR_0 ) && ( slave_address != CURRENTLIMIT7_SET_DEV_ADDR_1 ) )
    {
        return CURRENTLIMIT7_ERROR;    
    }
    
    err_t error_flag = i2c_master_set_slave_address( &ctx->i2c, slave_address );
    dev_addr_sel_delay( );
    
    return error_flag;
}

err_t currentlimit7_hw_reset ( currentlimit7_t *ctx ) 
{
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );

    return CURRENTLIMIT7_OK;
}

err_t currentlimit7_set_enable ( currentlimit7_t *ctx ) 
{
    digital_out_high( &ctx->en );

    return CURRENTLIMIT7_OK;
}

err_t currentlimit7_set_disable ( currentlimit7_t *ctx ) 
{
    digital_out_low( &ctx->en );

    return CURRENTLIMIT7_OK;
}

err_t currentlimit7_generic_write ( currentlimit7_t *ctx, uint8_t cmd, uint16_t data_byte ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    
    data_byte &= CURRENTLIMIT7_DIGI_POT_10_BIT_DATA;

    data_buf[ 0 ]  = cmd;
    data_buf[ 0 ] |= ( uint8_t ) ( data_byte >> 8 );
    data_buf[ 1 ]  = ( uint8_t ) data_byte;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t currentlimit7_generic_read ( currentlimit7_t *ctx, uint8_t cmd, uint16_t data_in, uint16_t *data_out ) 
{
    uint8_t rx_buf[ 2 ];
    uint8_t tx_buf[ 2 ] ;
    
    data_in &= CURRENTLIMIT7_DIGI_POT_5_BIT_DATA;
    
    if ( cmd == CURRENTLIMIT7_CMD_READ_CONTENTS )
    {
        tx_buf[ 1 ] = data_in;
    }
    else
    {
        tx_buf[ 1 ] = DUMMY;
    }

    tx_buf[ 0 ]  = cmd;
    tx_buf[ 0 ] |= ( uint8_t ) ( data_in >> 8 );
    tx_buf[ 1 ]  = ( uint8_t ) data_in;
    
    err_t error_flag = i2c_master_write( &ctx->i2c, tx_buf, 2 );
    dev_read_delay( );
    error_flag |= i2c_master_read( &ctx->i2c, rx_buf, 2 );
    
    *data_out = rx_buf[ 0 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 1 ];
    *data_out &= CURRENTLIMIT7_DIGI_POT_10_BIT_DATA;
    
    return error_flag;
}

err_t currentlimit7_enable_write ( currentlimit7_t *ctx )
{    
    return currentlimit7_generic_write( ctx, CURRENTLIMIT7_CMD_WRITE_MEMORY, CURRENTLIMIT7_SET_ENABLE_WRITE_MEMORY );
}

err_t currentlimit7_write_rdac ( currentlimit7_t *ctx, uint16_t data_in )
{
    return currentlimit7_generic_write( ctx, CURRENTLIMIT7_CMD_WRITE_RDAC, data_in );
}

err_t currentlimit7_read_rdac ( currentlimit7_t *ctx, uint16_t *data_out )
{
    return currentlimit7_generic_read( ctx, CURRENTLIMIT7_CMD_READ_RDAC, DUMMY, data_out );
}

err_t currentlimit7_sw_reset ( currentlimit7_t *ctx )
{
    return currentlimit7_generic_write( ctx, CURRENTLIMIT7_CMD_SW_RESET, DUMMY );
}

err_t currentlimit7_store_wiper ( currentlimit7_t *ctx )
{
    return currentlimit7_generic_write( ctx, CURRENTLIMIT7_CMD_STORE_WIPER, DUMMY );
}

err_t currentlimit7_next_frame_read ( currentlimit7_t *ctx, uint8_t wiper_location, uint16_t *data_out )
{   
    return currentlimit7_generic_read( ctx, CURRENTLIMIT7_CMD_READ_RDAC, wiper_location, data_out );
}

err_t currentlimit7_read_memory ( currentlimit7_t *ctx, uint8_t wiper_location, uint16_t *data_out )
{   
    return currentlimit7_generic_read( ctx, CURRENTLIMIT7_CMD_READ_MEMORY, DUMMY, data_out );
}

err_t currentlimit7_operating_mode ( currentlimit7_t *ctx, uint8_t mode )
{
    mode &= CURRENTLIMIT7_SET_NORMAL_MODE;
    
    return currentlimit7_generic_write( ctx, CURRENTLIMIT7_CMD_SW_SHUTDOWN, mode );
}

err_t currentlimit7_set_digi_pot ( currentlimit7_t *ctx, uint16_t wiper_pos )
{
    wiper_pos &= CURRENTLIMIT7_DIGI_POT_WIPER_POS_MAX;
    
    err_t error_flag = i2c_master_set_slave_address( &ctx->i2c, CURRENTLIMIT7_SET_DEV_ADDR_1 );
    dev_read_delay( );
    currentlimit7_write_rdac( ctx, wiper_pos / 2 );
    
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, CURRENTLIMIT7_SET_DEV_ADDR_0 );
    dev_read_delay( );
    currentlimit7_write_rdac( ctx, wiper_pos / 2 );
    
    return error_flag;
}

err_t currentlimit7_set_resistance ( currentlimit7_t *ctx, uint32_t res_ohm )
{
    uint16_t wiper_pos;
    float tmp;
    
    if ( res_ohm > CURRENTLIMIT7_RESISTANCE_200_kOhm )
    {
        return CURRENTLIMIT7_ERROR;    
    }
    
    tmp  = ( float ) res_ohm;
    tmp /= CURRENTLIMIT7_RESISTANCE_200_kOhm;
    tmp *= CURRENTLIMIT7_DIGI_POT_WIPER_POS_MAX;
    
    wiper_pos = ( uint16_t ) tmp;
    
    err_t error_flag = currentlimit7_set_digi_pot( ctx, wiper_pos );
    
    return error_flag;
}

err_t currentlimit7_set_current_limit ( currentlimit7_t *ctx, uint8_t op_mode, uint16_t current_limit_ma )
{
    uint32_t res_ohm;
    uint32_t sel_res_ohm;
    
    if ( op_mode == CURRENTLIMIT7_OP_MODE_500_mA_2500_mA )
    {
        if ( ( current_limit_ma > CURRENTLIMIT7_OP_1_CURRENT_LIMIT_MAX ) || ( current_limit_ma < CURRENTLIMIT7_OP_1_CURRENT_LIMIT_MIN ) )
        {
            return CURRENTLIMIT7_ERROR;   
        }   
        
        sel_res_ohm = CURRENTLIMIT7_SEL_RESISTANCE_53_6_kOhm;
    }
    else
    {
        if ( ( current_limit_ma > CURRENTLIMIT7_OP_0_CURRENT_LIMIT_MAX ) || ( CURRENTLIMIT7_OP_0_CURRENT_LIMIT_MIN < CURRENTLIMIT7_OP_0_CURRENT_LIMIT_MIN ) )
        {
            return CURRENTLIMIT7_ERROR;   
        }
        
        sel_res_ohm = CURRENTLIMIT7_SEL_RESISTANCE_300_kOhm;
    }
    
    switch ( current_limit_ma )
    {
        case CURRENTLIMIT7_OP_1_CURRENT_LIMIT_2500_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_53_6_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_1_CURRENT_LIMIT_2260_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_57_6_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_1_CURRENT_LIMIT_2020_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_64_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1750_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_75_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1550_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_85_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1450_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_90_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_1_CURRENT_LIMIT_1320_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_100_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_1_CURRENT_LIMIT_860_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_150_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_1_CURRENT_LIMIT_625_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_200_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_1_CURRENT_LIMIT_510_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_261_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_0_CURRENT_LIMIT_450_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_301_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_0_CURRENT_LIMIT_330_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_420_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_0_CURRENT_LIMIT_280_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_470_kOhm;
            break;
        }
        case CURRENTLIMIT7_OP_0_CURRENT_LIMIT_260_mA: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_510_kOhm;
            break;
        }
        default: 
        {
            res_ohm = CURRENTLIMIT7_RESISTANCE_261_kOhm; 
            break;
        }
    }
    
    res_ohm -= sel_res_ohm;
    
    return currentlimit7_set_resistance( ctx, ( uint32_t ) res_ohm );
}

uint8_t currentlimit7_get_fault ( currentlimit7_t *ctx )
{
    return digital_in_read( &ctx->flg );
}

static void dev_reset_delay ( void )
{
    Delay_100ms( );
}

static void dev_cfg_delay ( void )
{
    Delay_100ms( );
}

static void dev_addr_sel_delay ( void )
{
    Delay_10ms( );
}

static void dev_read_delay ( void )
{
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END
