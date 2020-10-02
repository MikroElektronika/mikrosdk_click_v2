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

#include "c6dofimu2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C6DOFIMU2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c6dofimu2_i2c_write ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu2_i2c_read ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu2_spi_write ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu2_spi_read ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c6dofimu2_cfg_setup ( c6dofimu2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin     = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = C6DOFIMU2_I2C_ADDR;
    cfg->spi_speed   = 100000; 
    cfg->spi_mode    = 0;
    cfg->sel         = C6DOFIMU2_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
     
}

C6DOFIMU2_RETVAL c6dofimu2_init ( c6dofimu2_t *ctx, c6dofimu2_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;
    
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  C6DOFIMU2_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, C6DOFIMU2_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );
        
        ctx->read_f  = c6dofimu2_spi_read;
        ctx->write_f = c6dofimu2_spi_write;

    if ( ctx->master_sel == C6DOFIMU2_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return C6DOFIMU2_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f  = c6dofimu2_i2c_read;
        ctx->write_f = c6dofimu2_i2c_write;
    }
    
    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return C6DOFIMU2_OK;
}

void c6dofimu2_default_cfg ( c6dofimu2_t *ctx, c6dofimu2_cfg_t *cfg )
{
    uint8_t buf;
    
    // Recognizes type of communication
    
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == C6DOFIMU2_MASTER_I2C )
    {
        buf = C6DOFIMU2_CMD_SEL_I2C;
        c6dofimu2_generic_write( ctx, C6DOFIMU2_REG_NV_CONF, &buf, 1 );
    }
    else
    {
        buf = C6DOFIMU2_CMD_SEL_SPI;
        c6dofimu2_generic_write( ctx, C6DOFIMU2_REG_NV_CONF, &buf, 1 ); 
    }

    // Set Accel in their normal state of performance
    
    buf = C6DOFIMU2_CMD_ACCEL_NORMAL;
    c6dofimu2_generic_write( ctx, C6DOFIMU2_CFG_COMMAND, &buf, 1 );

    // Set Gyro in their normal state of performance
    
    buf = C6DOFIMU2_CMD_GYRO_NORMAL;
    c6dofimu2_generic_write( ctx, C6DOFIMU2_CFG_COMMAND, &buf, 1 );
}

void c6dofimu2_generic_write ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void c6dofimu2_generic_read ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

int16_t c6dofimu2_get_axis ( c6dofimu2_t *ctx, uint8_t adr_reg_low, uint8_t adr_reg_high )
{
    uint16_t result;
    uint8_t buf_msb;
    uint8_t buf_lsb;

    c6dofimu2_generic_read( ctx, adr_reg_low, &buf_lsb, 1 );
    Delay_100ms( );
    c6dofimu2_generic_read( ctx, adr_reg_high, &buf_msb, 1 );

    result = buf_msb;
    result <<= 8;
    result |= buf_lsb;

    return result;
}

void c6dofimu2_read_accel ( c6dofimu2_t *ctx, c6dofimu2_accel_data_t *accel_data )
{
    accel_data->accel_x = c6dofimu2_get_axis( ctx, C6DOFIMU2_ACCEL_X_L, C6DOFIMU2_ACCEL_X_H );
    accel_data->accel_y = c6dofimu2_get_axis( ctx, C6DOFIMU2_ACCEL_Y_L, C6DOFIMU2_ACCEL_Y_H );
    accel_data->accel_z = c6dofimu2_get_axis( ctx, C6DOFIMU2_ACCEL_Z_L, C6DOFIMU2_ACCEL_Z_H );
}

void c6dofimu2_read_gyro ( c6dofimu2_t *ctx, c6dofimu2_gyro_data_t *gyro_data )
{
    gyro_data->gyro_x = c6dofimu2_get_axis( ctx, C6DOFIMU2_GYRO_X_L, C6DOFIMU2_GYRO_X_H );
    gyro_data->gyro_y = c6dofimu2_get_axis( ctx, C6DOFIMU2_GYRO_Y_L, C6DOFIMU2_GYRO_Y_H );
    gyro_data->gyro_z = c6dofimu2_get_axis( ctx, C6DOFIMU2_GYRO_Z_L, C6DOFIMU2_GYRO_Z_H );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c6dofimu2_i2c_write ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c6dofimu2_i2c_read ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void c6dofimu2_spi_write ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c6dofimu2_spi_read ( c6dofimu2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt + 1];
    }
}

// ------------------------------------------------------------------------- END

