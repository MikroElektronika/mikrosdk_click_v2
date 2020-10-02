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

#include "accel3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ACCEL3_DUMMY           0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static int16_t dev_get_axis ( accel3_t *ctx, uint8_t adr_reg_msb, uint8_t adr_reg_lsb );

static void accel3_i2c_write ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel3_i2c_read  ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel3_spi_write ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel3_spi_read  ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel3_cfg_setup ( accel3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ACCEL3_I2C_ADDRESS;
    cfg->spi_speed   = 100000; 
    cfg->spi_mode    = 0;
    cfg->sel         = ACCEL3_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ACCEL3_RETVAL accel3_init ( accel3_t *ctx, accel3_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == ACCEL3_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return ACCEL3_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f  = accel3_i2c_read;
        ctx->write_f = accel3_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        //spi_cfg.mode        = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  ACCEL3_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, ACCEL3_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->read_f  = accel3_spi_read;
        ctx->write_f = accel3_spi_write;
    }
    
    // Output pins 

    digital_out_init( &ctx->int_pin, cfg->int_pin );

    return ACCEL3_OK;
}

void accel3_default_cfg ( accel3_t *ctx, accel3_cfg_t *cfg )
{
    uint8_t en_ax;
    uint8_t fl_sc;
    
    ctx->master_sel = cfg->sel;
    
    en_ax = ACCEL3_ENABLE_AXIS;
    fl_sc = ACCEL3_FULL_SCALE;

    if ( ctx->master_sel == ACCEL3_MASTER_I2C )
    {
        accel3_generic_write( ctx, ACCEL3_CTRL_REG1, &en_ax, 1 );
        accel3_generic_write( ctx, ACCEL3_CTRL_REG4, &fl_sc, 1 );
    }
    else
    {
        accel3_generic_write( ctx, ACCEL3_CTRL_REG1, &en_ax, 1 );
        accel3_generic_write( ctx, ACCEL3_CTRL_REG4, &fl_sc, 1 );
    } 
}

void accel3_generic_write ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void accel3_generic_read ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t accel3_check_id ( accel3_t *ctx )
{
    uint8_t id;
    uint8_t rx_buf[ 1 ];
    
    accel3_generic_read( ctx, ACCEL3_REG_WHO_AM_I, rx_buf, 1 );
    
    id = rx_buf[ 0 ];

    if ( id != ACCEL3_DEVICE_IDENTIFIER )
    {
        return ACCEL3_FALSE;
    }
    else
    {
        return ACCEL3_TRUE;
    }
}
    
void accel3_read_data ( accel3_t *ctx, accel3_data_t *accel3_data )
{
    accel3_data->x = dev_get_axis( ctx, ACCEL3_OUT_X_H, ACCEL3_OUT_X_L );
    accel3_data->y = dev_get_axis( ctx, ACCEL3_OUT_Y_H, ACCEL3_OUT_Y_L );
    accel3_data->z = dev_get_axis( ctx, ACCEL3_OUT_Z_H, ACCEL3_OUT_Z_L );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static int16_t dev_get_axis ( accel3_t *ctx, uint8_t adr_reg_msb, uint8_t adr_reg_lsb )
{
    uint16_t result;
    uint8_t buf_lbs[ 1 ];
    uint8_t buf_mbs[ 1 ];
    
    accel3_generic_read( ctx, adr_reg_msb, buf_lbs, 1 );
    accel3_generic_read( ctx, adr_reg_lsb, buf_mbs, 1 );

    result = buf_lbs[ 0 ];
    result <<= 8;
    result |= buf_mbs[ 0 ];

    return result;
}

static void accel3_i2c_write ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel3_i2c_read ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void accel3_spi_write ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );      
}

static void accel3_spi_read ( accel3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 
}

// ------------------------------------------------------------------------- END

