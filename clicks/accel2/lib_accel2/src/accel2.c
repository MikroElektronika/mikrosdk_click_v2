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

#include "accel2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ACCEL2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void accel2_i2c_write ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel2_i2c_read ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel2_spi_write ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel2_spi_read ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel2_cfg_setup ( accel2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x1D;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = 0;
    cfg->sel = ACCEL2_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

ACCEL2_RETVAL accel2_init ( accel2_t *ctx, accel2_cfg_t *cfg )
{
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == ACCEL2_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return ACCEL2_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = accel2_i2c_read;
        ctx->write_f = accel2_i2c_write;
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
            return  ACCEL2_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, ACCEL2_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->read_f = accel2_spi_read;
        ctx->write_f = accel2_spi_write;
    }

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return ACCEL2_OK;
}

void accel2_generic_write ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void accel2_generic_read ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void accel2_setting ( accel2_t *ctx )
{
    uint8_t tmp;
    tmp = 0x77;
    accel2_generic_write( ctx, ACCEL2_CTRL_REG4, &tmp, 1 );
    tmp = 0xC8;
    accel2_generic_write( ctx, ACCEL2_CTRL_REG3, &tmp, 1 );
}

uint8_t accel2_check_id ( accel2_t *ctx )
{
    uint8_t id = 0x00;
    accel2_generic_read( ctx, ACCEL2_WHO_AM_I, &id, 1  );

    if ( id != 0x3F )
    {
        return 0x01;
    }
    else
    {
        return 0x00;
    }
}

int16_t accel2_read_xaxis ( accel2_t *ctx )
{
    uint16_t out_x;
    uint8_t buffer[ 2 ];
    out_x = 0x0000;

    accel2_generic_read( ctx, ACCEL2_OUT_X_H, &buffer[ 0 ], 1 );
    accel2_generic_read( ctx, ACCEL2_OUT_X_L, &buffer[ 1 ], 1 );
    
    out_x = buffer[ 0 ];
    out_x <<= 8;
    out_x |= buffer[ 1 ];
    
    return (int16_t)out_x;
}

int16_t accel2_read_yaxis ( accel2_t *ctx )
{
    uint16_t out_y;
    uint8_t buffer[ 2 ];
    out_y = 0x0000;

    accel2_generic_read( ctx, ACCEL2_OUT_Y_H, &buffer[ 0 ], 1 );
    accel2_generic_read( ctx, ACCEL2_OUT_Y_L, &buffer[ 1 ], 1 );

    out_y = buffer[ 0 ];
    out_y <<= 8;
    out_y |= buffer[ 1 ];

    return (int16_t)out_y;
}

int16_t accel2_read_zaxis ( accel2_t *ctx )
{
    uint16_t out_z;
    uint8_t buffer[ 2 ];
    out_z = 0x0000;

    accel2_generic_read( ctx, ACCEL2_OUT_Z_H, &buffer[ 0 ], 1 );
    accel2_generic_read( ctx, ACCEL2_OUT_Z_L, &buffer[ 1 ], 1 );

    out_z = buffer[ 0 ];
    out_z <<= 8;
    out_z |= buffer[ 1 ];

    return (int16_t)out_z;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void accel2_i2c_write ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel2_i2c_read ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void accel2_spi_write ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel2_spi_read ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len  );
    spi_master_deselect_device( ctx->chip_select ); 
}

// ------------------------------------------------------------------------- END

