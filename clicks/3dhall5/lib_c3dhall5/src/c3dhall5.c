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

#include "c3dhall5.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C3DHALL5_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c3dhall5_i2c_write ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void c3dhall5_i2c_read ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void c3dhall5_spi_write ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
static void c3dhall5_spi_read ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static C3DHALL5_RETVAL wait_status ( c3dhall5_t *ctx, uint8_t status );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c3dhall5_cfg_setup ( c3dhall5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->css = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x1E;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = C3DHALL5_MASTER_I2C;

}

C3DHALL5_RETVAL c3dhall5_init ( c3dhall5_t *ctx, c3dhall5_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set

    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == C3DHALL5_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;
        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return C3DHALL5_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = c3dhall5_i2c_read;
        ctx->write_f = c3dhall5_i2c_write;
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

        spi_cfg.default_write_data = C3DHALL5_DUMMY;

        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  C3DHALL5_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, C3DHALL5_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );  
        spi_master_deselect_device( ctx->chip_select ); 

        
        ctx->read_f = c3dhall5_spi_read;
        ctx->write_f = c3dhall5_spi_write;
    }
    
    // Output pins 

    digital_out_init( &ctx->css, cfg->css );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return C3DHALL5_OK;
}

void c3dhall5_default_cfg ( c3dhall5_t *ctx )
{
    uint8_t reg;

    // Click default configuration

    reg = C3DHALL5_CFG_A_COMP_TEMP_ENABLE;
    ctx->write_f( ctx, C3DHALL5_REG_CONFIG_A, &reg, 1 );

    reg = C3DHALL5_CFG_C_DRDY_ON_PIN;
    ctx->write_f( ctx, C3DHALL5_REG_CONFIG_C, &reg, 1 );
}

void c3dhall5_generic_write ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len );
}

void c3dhall5_generic_read ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t c3dhall5_get_device_id ( c3dhall5_t *ctx )
{
    uint8_t device_id;

    ctx->read_f( ctx, C3DHALL5_REG_WHO_AM_I, &device_id, 1 );
    return device_id;
}

float c3dhall5_get_temperature_data ( c3dhall5_t *ctx )
{
    uint8_t rx_data[ 2 ];
    int16_t raw_data;
    float temp;

    ctx->read_f( ctx, C3DHALL5_REG_TEMP_LSB, rx_data, 2 );

    raw_data = rx_data[ 1 ];
    raw_data <<= 8;
    raw_data |= rx_data[ 0 ];

    temp = (float)(raw_data * 0.5) + 23.0;

    return temp;
}

uint8_t c3dhall5_getint_pinerrupt_state ( c3dhall5_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void c3dhall5_set_offset ( c3dhall5_t *ctx, uint8_t offset_axis, int16_t offset )
{
    uint8_t data_buf[ 2 ];

    data_buf[ 0 ] = (offset & 0x00FF);
    data_buf[ 1 ] = (offset >> 8) & 0x00FF;

    ctx->write_f( ctx, offset_axis, data_buf, 2 );
}

int16_t c3dhall5_get_axis_data ( c3dhall5_t *ctx, uint8_t axis )
{
    int16_t axis_data;
    uint8_t data_buf[ 2 ];
    uint8_t status;

    if ( axis == C3DHALL5_AXIS_X )
    {
       status = wait_status( ctx, C3DHALL5_STATUS_X_NEW_DATA );
    }
    else if ( axis == C3DHALL5_AXIS_Y )
    {
        status = wait_status ( ctx, C3DHALL5_STATUS_Y_NEW_DATA );
    }
    else if ( axis == C3DHALL5_AXIS_Z )
    {
        status = 0;
    }

    if ( status == 0 )
    {
        ctx->read_f( ctx, axis, data_buf, 2 );

        axis_data = data_buf[ 1 ];
        axis_data <<= 8;
        axis_data |= data_buf[ 0 ];

        return axis_data;
    }
    else
    {
        return 1;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c3dhall5_i2c_write ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c3dhall5_i2c_read ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void c3dhall5_spi_write ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    digital_out_high( &ctx->css );
    spi_master_select_device( ctx->chip_select );
    
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

static void c3dhall5_spi_read ( c3dhall5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    digital_out_high( &ctx->css );
    spi_master_write( &ctx->spi, tx_buf, 1 );

    digital_out_low( &ctx->css );

    spi_master_read( &ctx->spi, data_buf, len );

    spi_master_deselect_device( ctx->chip_select ); 

}

static C3DHALL5_RETVAL wait_status ( c3dhall5_t *ctx, uint8_t status )
{
    uint8_t read_data;
    uint8_t cnt = 0;

    for ( cnt = 0; cnt < 10; cnt++ )
    {
        ctx->read_f( ctx, C3DHALL5_REG_STATUS, &read_data, 1 );

        if ( ( read_data & status ) != 0 )
        {
           return C3DHALL5_OK;
        }
    }
    return C3DHALL5_INIT_ERROR;
}


// ------------------------------------------------------------------------- END

