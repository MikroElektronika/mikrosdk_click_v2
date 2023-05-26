/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file efuse2.c
 * @brief eFuse 2 Click Driver.
 */

#include "efuse2.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Reset delay of 100 milliseconds.
 */
static void dev_reset_delay ( void );

/**
 * @brief Read delay of 1 milliseconds.
 */
static void dev_read_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void efuse2_cfg_setup ( efuse2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address_ad5175 = EFUSE2_I2C_SLAVE_ADDRESS_AD5175_GND;
    cfg->i2c_address_ad5241 = EFUSE2_I2C_SLAVE_ADDRESS_AD5241_0;
}

err_t efuse2_init ( efuse2_t *ctx, efuse2_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address_ad5175 = cfg->i2c_address_ad5175;
    ctx->slave_address_ad5241 = cfg->i2c_address_ad5241;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_ad5175 ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->flt, cfg->flt );

    return I2C_MASTER_SUCCESS;
}

err_t efuse2_default_cfg ( efuse2_t *ctx ) 
{
    err_t error_flag = EFUSE2_OK;
    efuse2_hw_reset ( ctx );
    Delay_100ms ( );
    error_flag |= efuse2_enable_write( ctx );
    error_flag |= efuse2_operating_mode( ctx, EFUSE2_AD5175_NORMAL_MODE );
    return error_flag;
}

err_t efuse2_write_ad5241 ( efuse2_t *ctx, ad5241_instru_t cmd, uint8_t data_byte ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };

    tx_buf[ 0 ]  = cmd.select_rdac;
    tx_buf[ 0 ] |= cmd.midscale_reset;
    tx_buf[ 0 ] |= cmd.active_shutdown;
    tx_buf[ 0 ] |= cmd.output_logic_pin_1;
    tx_buf[ 0 ] |= cmd.output_logic_pin_2;
    tx_buf[ 1 ] = data_byte;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_ad5241 );
    return i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

uint8_t efuse2_read_ad5241 ( efuse2_t *ctx ) 
{
    uint8_t rx_buf[ 1 ] = { 0 };

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_ad5241 );
    i2c_master_read( &ctx->i2c, rx_buf, 1 );

    return rx_buf[ 0 ];
}

void efuse2_hw_reset ( efuse2_t *ctx ) 
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
}

err_t efuse2_set_operating_voltage ( efuse2_t *ctx, float voltage, float *min_voltage, float *max_voltage ) 
{
    uint8_t vol_val = 0;
    float temp = 0;
    ad5241_instru_t instruction;

    if ( voltage < 0.0 ) 
    {
        voltage *= -1.0;
    }

    if ( voltage < 3.7 ) 
    {
        voltage = 3.6473263386;
    }

    if ( voltage > 15.0 ) 
    {
        voltage = 15.01237216;
    }

    instruction.select_rdac        = EFUSE2_AD5241_RDAC0;
    instruction.midscale_reset     = EFUSE2_AD5241_NO_RESET;
    instruction.active_shutdown    = EFUSE2_AD5241_NO_SHUTDOWN;
    instruction.output_logic_pin_1 = EFUSE2_AD5241_O1_LOW;
    instruction.output_logic_pin_2 = EFUSE2_AD5241_O2_LOW;

    vol_val = ( uint8_t ) ( ( voltage - 3.6473263386 ) / 0.078379808 );

    temp = ( ( ( float ) vol_val * 3906.25 + 60.0 ) + 181700.0 ) * 1.2;

    *min_voltage = temp / 80700.0;

    *max_voltage = temp / 47500.0;
    
    return efuse2_write_ad5241( ctx, instruction, vol_val );
}

err_t efuse2_write_ad5175 ( efuse2_t *ctx, uint8_t cmd, uint16_t data_byte ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };

    data_byte &= EFUSE2_10_BIT;

    tx_buf[ 0 ] = cmd;
    tx_buf[ 0 ] |= ( uint8_t ) ( data_byte >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) data_byte;
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_ad5175 );
    return i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

uint16_t efuse2_read_ad5175 ( efuse2_t *ctx, uint8_t cmd, uint8_t wiper_location ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    uint8_t tx_buf[ 2 ] = { 0 };
    uint16_t result = 0;

    if ( 0x14 == cmd ) 
    {
        if ( wiper_location > 0x38 ) 
        {
            wiper_location = 0x38;
        }

        tx_buf[ 1 ] = wiper_location;
    } 
    else 
    {
        tx_buf[ 1 ] = EFUSE2_DUMMY;
    }

    tx_buf[ 0 ] = cmd;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_ad5175 );
    i2c_master_write( &ctx->i2c, tx_buf, 2 );
    dev_read_delay( );
    i2c_master_read( &ctx->i2c, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    result &= EFUSE2_10_BIT;

    return result;
}

uint16_t efuse2_read_rdac ( efuse2_t *ctx ) 
{
    return efuse2_read_ad5175 ( ctx, EFUSE2_AD5175_COMMAND_READ_RDAC, EFUSE2_DUMMY );
}

err_t efuse2_enable_write ( efuse2_t *ctx ) 
{
    return efuse2_write_ad5175( ctx, EFUSE2_AD5175_COMMAND_WRITE_MEMORY, EFUSE2_AD5175_UPDATE_WIPER_POS );
}

err_t efuse2_write_rdac ( efuse2_t *ctx, uint16_t data_byte ) 
{
    return efuse2_write_ad5175 ( ctx, EFUSE2_AD5175_COMMAND_WRITE_RDAC, data_byte );
}

err_t efuse2_set_current_limit ( efuse2_t *ctx, float current ) 
{
    uint16_t current_val = 0;

    if ( current < 0.1259 ) 
    {
        current = 0.1259;
    }

    if ( current < 1.0 ) 
    {
        current += current * 0.04;
    } 
    else 
    {
        current += current * 0.06;
    }
    
    if ( current > 2.0 ) 
    {
        current = 2.12;
    }

    current_val =  ( uint16_t ) ( ( ( 903 / ( current - 0.0112 ) ) - 450 ) / 9.765265 );

    if ( current_val < 1 ) 
    {
        current_val = 1;
    }

    return efuse2_write_rdac( ctx, current_val );
}

err_t efuse2_sw_reset ( efuse2_t *ctx ) 
{
    return efuse2_write_ad5175( ctx, EFUSE2_AD5175_COMMAND_SW_RESET, EFUSE2_DUMMY );
}

err_t efuse2_store_wiper ( efuse2_t *ctx ) 
{
    return efuse2_write_ad5175( ctx, EFUSE2_AD5175_COMMAND_STORE_WIPER, EFUSE2_DUMMY );
}

err_t efuse2_operating_mode ( efuse2_t *ctx, uint8_t mode ) 
{
    mode &= EFUSE2_AD5175_SHUTDOWN_BIT_MASK;

    if ( EFUSE2_AD5175_NORMAL_MODE == mode ) 
    {
        return efuse2_write_ad5175( ctx, EFUSE2_AD5175_COMMAND_SW_SHUTDOWN, EFUSE2_AD5175_NORMAL_MODE );
    } 
    else 
    {
        return efuse2_write_ad5175( ctx, EFUSE2_AD5175_COMMAND_SW_SHUTDOWN, EFUSE2_AD5175_SHUTDOWN_MODE );
    }
}

uint16_t efuse2_next_frame_read ( efuse2_t *ctx, uint8_t wiper_location ) 
{
    return efuse2_read_ad5175 ( ctx, EFUSE2_AD5175_COMMAND_READ_RDAC, wiper_location );
}

uint16_t efuse2_read_memory ( efuse2_t *ctx ) 
{
    return efuse2_read_ad5175 ( ctx, EFUSE2_AD5175_COMMAND_READ_MEMORY, EFUSE2_DUMMY );
}

uint8_t efuse2_read_control ( efuse2_t *ctx ) 
{
    return EFUSE2_AD5175_CTRL_REG_BIT_MASK & 
           efuse2_read_ad5175 ( ctx, EFUSE2_AD5175_COMMAND_READ_CONTROL, EFUSE2_DUMMY );
}

uint8_t efuse2_get_fault ( efuse2_t *ctx ) 
{
    return digital_in_read( &ctx->flt );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_reset_delay ( void ) 
{
    Delay_100ms( );
}

static void dev_read_delay ( void ) 
{
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END
