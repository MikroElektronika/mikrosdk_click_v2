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
 * @file heartrate5.c
 * @brief Heart Rate 5 Click Driver.
 */

#include "heartrate5.h"

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Reset delay of 50 us.
 */
static void dev_reset_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void heartrate5_cfg_setup ( heartrate5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = HEARTRATE5_SET_DEV_ADDR;
}

err_t heartrate5_init ( heartrate5_t *ctx, heartrate5_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );


    return I2C_MASTER_SUCCESS;
}

err_t heartrate5_default_cfg ( heartrate5_t *ctx ) 
{
    err_t error_flag = HEARTRATE5_OK;
    
    heartrate5_hw_reset( ctx );
    
    heartrate5_write_reg( ctx, HEARTRATE5_REG0H, 0x000000 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG1H, 0x000050 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG2H, 0x00018F );
    heartrate5_write_reg( ctx, HEARTRATE5_REG3H, 0x000320 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG4H, 0x0004AF );
    heartrate5_write_reg( ctx, HEARTRATE5_REG5H, 0x0001E0 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG6H, 0x00031F );
    heartrate5_write_reg( ctx, HEARTRATE5_REG7H, 0x000370 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG8H, 0x0004AF );
    heartrate5_write_reg( ctx, HEARTRATE5_REG9H, 0x000000 );
    heartrate5_write_reg( ctx, HEARTRATE5_REGAH, 0x00018F );
    heartrate5_write_reg( ctx, HEARTRATE5_REGBH, 0x0004FF );
    heartrate5_write_reg( ctx, HEARTRATE5_REGCH, 0x00063E );
    heartrate5_write_reg( ctx, HEARTRATE5_REGDH, 0x000198 );
    heartrate5_write_reg( ctx, HEARTRATE5_REGEH, 0x0005BB );
    heartrate5_write_reg( ctx, HEARTRATE5_REGFH, 0x0005C4 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG10H, 0x0009E7 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG11H, 0x0009F0 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG12H, 0x000E13 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG13H, 0x000E1C );
    heartrate5_write_reg( ctx, HEARTRATE5_REG14H, 0x00123F );
    heartrate5_write_reg( ctx, HEARTRATE5_REG15H, 0x000191 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG16H, 0x000197 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG17H, 0x0005BD );
    heartrate5_write_reg( ctx, HEARTRATE5_REG18H, 0x0005C3 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG19H, 0x0009E9 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG1AH, 0x0009EF );
    heartrate5_write_reg( ctx, HEARTRATE5_REG1BH, 0x000E15 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG1CH, 0x000E1B );
    heartrate5_write_reg( ctx, HEARTRATE5_REG1DH, 0x009C3E );
    heartrate5_write_reg( ctx, HEARTRATE5_REG1EH, 0x000103 ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG20H, 0x008003 ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG21H, 0x000013 ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG22H, 0x01B6D9 ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG23H, 0x104218 ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG29H, 0x000000 ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG31H, 0x000000 ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG32H, 0x00155F ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG33H, 0x00991E ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG34H, 0x000000 );
    heartrate5_write_reg( ctx, HEARTRATE5_REG35H, 0x00000f ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG36H, 0x000190 ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG37H, 0x00031F ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG39H, 0x000000 ); 
    heartrate5_write_reg( ctx, HEARTRATE5_REG3AH, 0x000000 );

    return error_flag;
}

err_t heartrate5_generic_write ( heartrate5_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t heartrate5_generic_read ( heartrate5_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void heartrate5_write_reg( heartrate5_t *ctx, uint8_t reg_addr, uint32_t write_data )
{
    uint8_t hr_storage[ 5 ];
    hr_storage[ 0 ] = reg_addr;
    hr_storage[ 1 ] = write_data>>16;
    hr_storage[ 2 ] = write_data>>8;
    hr_storage[ 3 ] = write_data;

    i2c_master_write( &ctx->i2c, hr_storage, 4 );
}

uint32_t heartrate5_read_reg( heartrate5_t *ctx, uint8_t reg_addr )
{
    uint8_t hr_storage[ 5 ];
    uint32_t return_value = 0;
    hr_storage[ 0 ] = reg_addr;

    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, hr_storage, 3 );
    
    return_value = hr_storage[ 0 ];
    return_value = return_value << 16;
    return_value |= hr_storage[ 1 ] << 8;
    return_value |= hr_storage[ 2 ];
    return return_value;
}

void heartrate5_hw_reset( heartrate5_t *ctx )
{
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
}
void heartrate5_sw_reset( heartrate5_t *ctx )
{
    heartrate5_write_reg( ctx, HEARTRATE5_REG0H, 0x000008 );
}

uint32_t heartrate5_get_led2_val( heartrate5_t *ctx )
{
    uint32_t reg_data;
    reg_data=heartrate5_read_reg( ctx, HEARTRATE5_REG2AH );
    return reg_data;
}

uint32_t heartrate5_get_aled2_val_led3_val( heartrate5_t *ctx )
{
    uint32_t reg_data;
    reg_data = heartrate5_read_reg( ctx, HEARTRATE5_REG2BH );
    return reg_data;
}

uint32_t heartrate5_get_led1_val( heartrate5_t *ctx )
{
    uint32_t reg_data;
    reg_data = heartrate5_read_reg( ctx, HEARTRATE5_REG2CH );
    return reg_data;
}

uint32_t heartrate5_get_aled1_val( heartrate5_t *ctx )
{
    uint32_t reg_data;
    reg_data = heartrate5_read_reg( ctx, HEARTRATE5_REG2DH );
    return reg_data;
}

uint32_t heartrate5_get_led2_aled2_val( heartrate5_t *ctx ) 
{
    uint32_t reg_data;
    reg_data = heartrate5_read_reg( ctx, HEARTRATE5_REG2EH );
    return reg_data;
}

uint32_t heartrate5_get_led1_aled1_val( heartrate5_t *ctx )
{
    uint32_t reg_data;
    reg_data = heartrate5_read_reg( ctx, HEARTRATE5_REG2FH );
    return reg_data;
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void ) 
{
    Delay_50us( );
}

// ------------------------------------------------------------------------- END
