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

#include "adapter.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ADAPTER_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void adapter_i2c_write ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void adapter_i2c_read ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void adapter_spi_write ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void adapter_spi_read ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adapter_cfg_setup ( adapter_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = I2C_SLAVE_ADDR_DEMO;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = ADAPTER_MASTER_SPI;
}

ADAPTER_RETVAL adapter_init ( adapter_t *ctx, adapter_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == ADAPTER_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return ADAPTER_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = adapter_i2c_read;
        ctx->write_f = adapter_i2c_write;
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
        
        spi_cfg.default_write_data = ADAPTER_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  ADAPTER_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, ADAPTER_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = adapter_spi_read;
        ctx->write_f = adapter_spi_write;
    }
    
    // Output pins 
    digital_out_init( &ctx->pwm, cfg->pwm );
    digital_out_init( &ctx->rx_pin, cfg->rx_pin );
    digital_out_init( &ctx->tx_pin, cfg->tx_pin );
    
    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return ADAPTER_OK;
}

void adapter_generic_write ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void adapter_generic_read ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void adapter_generic_transfer( adapter_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, wr_buf, wr_len );
    spi_master_read( &ctx->spi, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );
}

void adapter_turn_tx_on ( adapter_t *ctx )
{
    digital_out_high( &ctx->tx_pin );
}

void adapter_turn_rx_on ( adapter_t *ctx )
{
    digital_out_high( &ctx->rx_pin );
}

void adapter_turn_pwm_on ( adapter_t *ctx )
{
    digital_out_high( &ctx->pwm );
}

void adapter_turn_tx_off ( adapter_t *ctx )
{
    digital_out_low( &ctx->tx_pin );
}

void adapter_turn_rx_off ( adapter_t *ctx )
{
    digital_out_low( &ctx->rx_pin );
}

void adapter_turn_pwm_off ( adapter_t *ctx )
{
    digital_out_low( &ctx->pwm );
}

uint8_t adapter_check_int ( adapter_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void adapter_i2c_write ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void adapter_i2c_read ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void adapter_spi_write ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void adapter_spi_read ( adapter_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );
}

// ------------------------------------------------------------------------- END

