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

#include "dac5.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dac5_cfg_setup ( dac5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->lda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = DAC5_SLAVE_ADDRESS_GND;
}

DAC5_RETVAL dac5_init ( dac5_t *ctx, dac5_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return DAC5_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->lda, cfg->lda );

    return DAC5_OK;
}

void dac5_generic_write ( dac5_t *ctx, uint8_t reg, uint16_t data_buf )
{
    uint8_t write_buf[ 3 ];

    write_buf[ 0 ] = reg;
    write_buf[ 1 ] = ( data_buf >> 8 ) & 0x00FF;
    write_buf[ 2 ] = data_buf & 0x00FF;

    i2c_master_write( &ctx->i2c, write_buf, 3 );   
}

uint16_t dac5_generic_read ( dac5_t *ctx, uint8_t reg )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 2 ];
    uint16_t temp_data;

    tx_buf [ 0 ] = reg;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 2 );

    temp_data = rx_buf[ 0 ];
    temp_data <<= 8;
    temp_data += rx_buf[ 1 ];

    return temp_data;
}

void dac5_config ( dac5_t *ctx, uint16_t config_data )
{
    dac5_generic_write( ctx, DAC5_REG_CONFIG, config_data );
}

uint16_t dac5_get_device_id ( dac5_t *ctx )
{
    return dac5_generic_read( ctx, DAC5_REG_STATUS_TRIGGER );
}

void dac5_software_reset ( dac5_t *ctx )
{
    dac5_generic_write( ctx, DAC5_REG_STATUS_TRIGGER, DAC5_SOFTWARE_RESET );
}

void dac5_clear ( dac5_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_1ms(  );
    digital_out_low( &ctx->rst );
    Delay_10ms(  );
    digital_out_high( &ctx->rst );
}

uint8_t dac5_set_ldac_pin ( dac5_t *ctx, uint8_t status )
{
    if ( status == DAC5_ASYNCHRONOUS )
    {
        digital_out_low( &ctx->lda );
        return DAC5_SUCCESS;
    }
    else if ( status == DAC5_SYNCHRONOUS )
    {
        digital_out_high( &ctx->lda );
        return DAC5_SUCCESS;
    }
    else
    {
        return DAC5_ERROR;
    }
}

uint8_t dac5_send_data ( dac5_t *ctx, uint8_t data_reg, uint16_t data_buf )
{
    if ( ( data_buf < DAC5_MIN_DATA ) || ( data_buf > DAC5_MAX_DATA ) )
    {
        return DAC5_ERROR;
    }

    if ( ( ( data_reg & DAC5_REG_DAC_A_DATA ) == DAC5_REG_DAC_A_DATA ) ||
         ( ( data_reg & DAC5_REG_DAC_B_DATA ) == DAC5_REG_DAC_B_DATA ) ||
         ( ( data_reg & DAC5_REG_DAC_C_DATA ) == DAC5_REG_DAC_C_DATA ) ||
         ( ( data_reg & DAC5_REG_DAC_D_DATA ) == DAC5_REG_DAC_D_DATA ) ||
         ( ( data_reg & DAC5_REG_DAC_E_DATA ) == DAC5_REG_DAC_E_DATA ) ||
         ( ( data_reg & DAC5_REG_DAC_F_DATA ) == DAC5_REG_DAC_F_DATA ) ||
         ( ( data_reg & DAC5_REG_DAC_G_DATA ) == DAC5_REG_DAC_G_DATA ) ||
         ( ( data_reg & DAC5_REG_DAC_H_DATA ) == DAC5_REG_DAC_H_DATA ) )
    {
        dac5_generic_write( ctx, data_reg, data_buf );

        return DAC5_SUCCESS;
    }
    else
    {
        return DAC5_ERROR;
    }
}

// ------------------------------------------------------------------------- END

