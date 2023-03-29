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

#include "adac.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adac_cfg_setup ( adac_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ADAC_I2C_SLAVE_ADDR;
}

ADAC_RETVAL adac_init ( adac_t *ctx, adac_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ADAC_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    return ADAC_OK;
}

void adac_generic_write ( adac_t *ctx, uint8_t cmd, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = cmd;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

void adac_generic_read ( adac_t *ctx, uint8_t cmd, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &cmd, 1, data_buf, len );
}

void adac_write_data ( adac_t *ctx, uint8_t addr, uint16_t w_data )
{
    uint8_t w_buf[ 3 ];

    w_buf[ 0 ] = addr;
    w_buf[ 1 ] = w_data >> 8;
    w_buf[ 2 ] = w_data;

    i2c_master_write( &ctx->i2c, w_buf, 3 );
}

uint16_t adac_read_data ( adac_t *ctx, uint8_t addr )
{
    uint16_t r_data;
    uint8_t r_buf[ 2 ];

    i2c_master_write_then_read( &ctx->i2c, &addr, 1, r_buf, 2 );

    r_data = r_buf[ 0 ];
    r_data <<= 8;
    r_data |= r_buf[ 1 ];

    return r_data;
}

void adac_set_configuration ( adac_t *ctx, uint8_t ptr, uint8_t msb, uint8_t lsb )
{
    uint8_t w_buf[ 3 ];

    w_buf[ 0 ] = ptr;
    w_buf[ 1 ] = msb;
    w_buf[ 2 ] = lsb;

    i2c_master_write( &ctx->i2c, w_buf, 3 );  
}

void adac_write_dac ( adac_t *ctx, uint8_t chan, uint8_t msb, uint8_t lsb )
{
    uint8_t w_buf[ 3 ];

    msb &= 0x0F;
    w_buf[ 0 ] = ADAC_DAC_WRITE | chan;
    chan <<= 4;
    w_buf[ 1 ] = 0x80 | chan | msb;
    w_buf[ 2 ] = lsb;

    i2c_master_write( &ctx->i2c, w_buf, 3 );  
}

void adac_write_dac_data ( adac_t *ctx, uint8_t chan, uint16_t w_data )
{
    uint8_t w_buf[ 3 ];

    w_buf[ 0 ] = ADAC_DAC_WRITE | chan;
    chan <<= 4;
    w_buf[ 1 ] = 0x80 | chan | ( ( uint8_t ) w_data >> 8 );
    w_buf[ 2 ] = w_data;

    i2c_master_write( &ctx->i2c, w_buf, 3 );  
}

uint16_t adac_read_adc( adac_t *ctx, uint8_t *chan )
{
    uint8_t cmd;
    uint8_t r_buf[ 2 ];
    uint16_t r_data;

    cmd = ADAC_ADC_READ;

    i2c_master_write_then_read( &ctx->i2c, &cmd, 1, r_buf, 2 );

    *chan = r_buf[ 0 ] >> 4;
    r_buf[ 0 ] &= 0x0F;

    r_data = r_buf[ 0 ] << 8;
    r_data |= r_buf[ 1 ];

    return r_data;
}

uint16_t adac_read_dac ( adac_t *ctx, uint8_t *chan )
{
    uint8_t cmd;
    uint8_t r_buf[ 2 ];
    uint16_t r_data;

    cmd = ADAC_DAC_READ;

    i2c_master_write_then_read( &ctx->i2c, &cmd, 1, r_buf, 2 );

    *chan = r_buf[ 0 ] >> 4;
    r_buf[ 0 ] &= 0x0F;

    r_data = r_buf[ 0 ] << 8;
    r_data |= r_buf[ 1 ];

    return r_data;
}

uint8_t adac_read_gpio ( adac_t *ctx )
{
    uint16_t r_data;

    r_data = adac_read_data( ctx, ADAC_GPIO_READ );

    return r_data >> 8;
}

void adac_write_gpio ( adac_t *ctx, uint8_t w_data )
{
    uint8_t w_buf[ 2 ];

    w_buf[ 0 ] = ADAC_GPIO_WR_DATA;
    w_buf[ 1 ] = w_data;

    i2c_master_write( &ctx->i2c, w_buf, 2 ); 
}

uint16_t adac_read_config( adac_t *ctx )
{
    return adac_read_data( ctx, ADAC_REG_READ );
}

void adac_general_purpose_settings ( adac_t *ctx, uint16_t settings )
{
    adac_write_data( ctx, ADAC_GP_CONTROL, settings );
}

void adac_power_down_settings ( adac_t *ctx, uint16_t settings )
{
    adac_write_data( ctx, ADAC_POWER_REF_CTRL, settings );
}

void adac_software_reset ( adac_t *ctx, uint16_t cmd )
{
    adac_write_data( ctx, ADAC_SOFT_RESET, cmd );
}

void adac_hardware_reset ( adac_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
}

// ------------------------------------------------------------------------- END

