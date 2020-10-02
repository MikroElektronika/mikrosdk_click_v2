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

#include "i2cmux3.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_reset_delay ( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void i2cmux3_cfg_setup ( i2cmux3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = I2CMUX3_DEV_ADR_0;
}

I2CMUX3_RETVAL i2cmux3_init ( i2cmux3_t *ctx, i2cmux3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return I2CMUX3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    return I2CMUX3_OK;
}

void i2cmux3_generic_write ( i2cmux3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
}

void i2cmux3_generic_read ( i2cmux3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void i2cmux3_write_ctl ( i2cmux3_t *ctx, uint8_t wr_data )
{
    i2c_master_write( &ctx->i2c, &wr_data, 1 ); 
}

uint8_t i2cmux3_read_ctl ( i2cmux3_t *ctx )
{
    uint8_t buf[ 1 ];

    i2c_master_write_then_read( &ctx->i2c, 0, 0, buf, 1 );

    return buf[ 0 ];
}

void i2cmux3_ch_sel ( i2cmux3_t *ctx, uint8_t sel_ch )
{
    switch ( sel_ch )
    {
        case 0:
        {
            i2cmux3_write_ctl( ctx, I2CMUX3_SEL_CH_0 );
            break;
        }
        case 1:
        {
            i2cmux3_write_ctl( ctx, I2CMUX3_SEL_CH_1 );
            break;
        }
        case 2:
        {
            i2cmux3_write_ctl( ctx, I2CMUX3_SEL_CH_2 );
            break;
        }
        case 3:
        {
            i2cmux3_write_ctl( ctx, I2CMUX3_SEL_CH_3 );
            break;
        }
        case 4:
        {
            i2cmux3_write_ctl( ctx, I2CMUX3_SEL_CH_4 );
            break;
        }
        case 5:
        {
            i2cmux3_write_ctl( ctx, I2CMUX3_SEL_CH_5 );
            break;
        }
        case 6:
        {
            i2cmux3_write_ctl( ctx, I2CMUX3_SEL_CH_6 );
            break;
        }
        case 7:
        {
            i2cmux3_write_ctl( ctx, I2CMUX3_SEL_CH_7 );
            break;
        }
        default:
        {
            i2cmux3_write_ctl( ctx, I2CMUX3_DIS_ALL_CH );
            break;
        }
    }
}

// Slave Device Write
void i2cmux3_wr_slv ( i2cmux3_t *ctx, uint8_t slv_sel_adr, uint8_t reg, uint8_t *p_wr_data, 
                      uint8_t n_bytes )
{
    i2c_master_set_slave_address( &ctx->i2c, slv_sel_adr );
    i2cmux3_generic_write( ctx, reg, p_wr_data, n_bytes );
}

// Slave Device Read
void i2cmux3_rd_slv ( i2cmux3_t *ctx, uint8_t slv_sel_adr, uint8_t reg, uint8_t *p_rd_data, 
                      uint8_t n_bytes )
{
    i2c_master_set_slave_address( &ctx->i2c, slv_sel_adr );
    i2cmux3_generic_read( ctx, reg, p_rd_data, n_bytes );
}

// Device enable
void i2cmux3_dev_enable ( i2cmux3_t *ctx, uint8_t stat )
{
    if ( stat == I2CMUX3_DEV_EN )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

// Hardware reset
void i2cmux3_hw_rst ( i2cmux3_t *ctx )
{
    digital_out_low( &ctx->rst );
    dev_reset_delay( );
    digital_out_high( &ctx->rst );
    dev_reset_delay( );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

