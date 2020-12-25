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

#include "pressure11.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PRESSURE11_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void pressure11_i2c_write ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure11_i2c_read ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure11_spi_write ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure11_spi_read ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pressure11_cfg_setup ( pressure11_cfg_t *cfg )
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
    cfg->i2c_address = PRESSURE11_DEVICE_SLAVE_ADDR_GND;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = PRESSURE11_MASTER_I2C;
}

PRESSURE11_RETVAL pressure11_init ( pressure11_t *ctx, pressure11_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == PRESSURE11_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return PRESSURE11_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
        
        digital_out_init( &ctx->cs, cfg->cs );
        digital_out_high( &ctx->cs );

        ctx->read_f = pressure11_i2c_read;
        ctx->write_f = pressure11_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        spi_cfg.default_write_data = PRESSURE11_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  PRESSURE11_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, PRESSURE11_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = pressure11_spi_read;
        ctx->write_f = pressure11_spi_write;
    }

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PRESSURE11_OK;
}

void pressure11_generic_write ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void pressure11_generic_read ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t pressure11_check_id ( pressure11_t *ctx )
{
    uint8_t device_id;
    uint8_t w_buff;

    pressure11_generic_read( ctx, PRESSURE11_REG_WHO_AM_I, &device_id, 1 );

    if ( device_id != PRESSURE11_I_AM )
    {
        return DEVICE_ERROR;
    }

    w_buff = PRESSURE11_CTRL_1_ODR_75_HZ;

    pressure11_generic_write( ctx, PRESSURE11_REG_CTRL_REG1, &w_buff, 1 );

    return DEVICE_OK;
}

float pressure11_get_temperature ( pressure11_t *ctx )
{
  int32_t temperature = 0;
  uint8_t temperature_bytes[ 2 ];

  pressure11_generic_read( ctx, PRESSURE11_REG_TEMP_OUT_L, &temperature_bytes[ 0 ], 1 );
  pressure11_generic_read( ctx, PRESSURE11_REG_TEMP_OUT_H, &temperature_bytes[ 1 ], 1 );

  temperature = temperature_bytes[ 1 ];
  temperature <<= 8;
  temperature |= temperature_bytes[ 0 ];

   
  return temperature / 100.00;
}

float pressure11_get_pressure ( pressure11_t *ctx )
{
   int32_t pressure = 0;
   uint8_t pressure_bytes[ 10 ];

   pressure11_generic_read( ctx, PRESSURE11_REG_PRESS_OUT_XL, &pressure_bytes[ 0 ], 1 );
   pressure11_generic_read( ctx, PRESSURE11_REG_PRESS_OUT_L, &pressure_bytes[ 1 ], 1 );
   pressure11_generic_read( ctx, PRESSURE11_REG_PRESS_OUT_H, &pressure_bytes[ 2 ], 1 );

   pressure = pressure_bytes[ 2 ];
   pressure <<= 8;
   pressure |= pressure_bytes[ 1 ];
   pressure <<= 8;
   pressure |= pressure_bytes[ 0 ];

   return pressure / 4096.00;
}

uint8_t pressure11_get_interrupt ( pressure11_t *ctx )
{
    return digital_in_read( &ctx->int_pin ); 
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void pressure11_i2c_write ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void pressure11_i2c_read ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write( &ctx->i2c, &reg, 1 ); 
    i2c_master_read( &ctx->i2c, data_buf, len );
}

static void pressure11_spi_write ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void pressure11_spi_read ( pressure11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );  
}

// ------------------------------------------------------------------------- END

