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

#include "c6dofimu.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C6DOFIMU_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c6dofimu_i2c_write ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu_i2c_read ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu_spi_write ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu_spi_read ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static int16_t drv_double_read ( c6dofimu_t *ctx, uint8_t reg );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c6dofimu_cfg_setup ( c6dofimu_cfg_t *cfg )
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
    cfg->i2c_address = C6DOFIMU_SLAVE_ADDRESS;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->sel = C6DOFIMU_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

C6DOFIMU_RETVAL c6dofimu_init ( c6dofimu_t *ctx, c6dofimu_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == C6DOFIMU_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return C6DOFIMU_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        digital_out_init( &ctx->cs, cfg->cs );
        digital_out_high( &ctx->cs );

        ctx->read_f = c6dofimu_i2c_read;
        ctx->write_f = c6dofimu_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode  = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck     = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  C6DOFIMU_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, C6DOFIMU_DUMMY );
        spi_master_set_speed( &ctx->spi, cfg->spi_speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_set_mode( &ctx->spi, cfg->spi_mode );
        spi_master_deselect_device( ctx->chip_select );
        
        ctx->read_f = c6dofimu_spi_read;
        ctx->write_f = c6dofimu_spi_write;
    }

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return C6DOFIMU_OK;
}

void c6dofimu_default_cfg ( c6dofimu_t *ctx )
{
    uint8_t ctrl_1_reg = C6DOFIMU_CFG_BIT_7;
    uint8_t ctrl_2_reg = C6DOFIMU_CFG_BIT_7;
    uint8_t ctrl_3_reg = C6DOFIMU_CFG_BIT_2;

    c6dofimu_generic_write( ctx, C6DOFIMU_CTRL1_XL, &ctrl_1_reg, 1 );
    Delay_10ms( );
    c6dofimu_generic_write( ctx, C6DOFIMU_CTRL2_G, &ctrl_2_reg, 1 );
    Delay_10ms( );
    c6dofimu_generic_write( ctx, C6DOFIMU_CTRL3_C, &ctrl_3_reg, 1 );
    Delay_10ms( );
}

void c6dofimu_generic_write ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void c6dofimu_generic_read ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void c6dofimu_read_axis_data ( c6dofimu_t *ctx, uint8_t read_mode )
{
    if ( read_mode == C6DOFIMU_ACCEL_READ_MODE )
    {
        ctx->accel_axis.x = drv_double_read( ctx, C6DOFIMU_OUTX_L_G );
        ctx->accel_axis.y = drv_double_read( ctx, C6DOFIMU_OUTY_L_G );
        ctx->accel_axis.z = drv_double_read( ctx, C6DOFIMU_OUTZ_L_G ); 
    }
    else if ( read_mode == C6DOFIMU_GYRO_READ_MODE ) 
    {
        ctx->gyro_axis.x = drv_double_read( ctx, C6DOFIMU_OUTX_L_XL );
        ctx->gyro_axis.y = drv_double_read( ctx, C6DOFIMU_OUTY_L_XL );
        ctx->gyro_axis.z = drv_double_read( ctx, C6DOFIMU_OUTZ_L_XL );
    }
} 

float c6dofimu_read_temperature ( c6dofimu_t *ctx ) 
{
    float temperature;

    temperature = ( float ) drv_double_read( ctx, C6DOFIMU_OUT_TEMP_L );
    temperature *= 0.065;
    temperature += 25.0;

    return temperature;
}

uint8_t c6dofimu_digital_read_int ( c6dofimu_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c6dofimu_i2c_write ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c6dofimu_i2c_read ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void c6dofimu_spi_write ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c6dofimu_spi_read ( c6dofimu_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 

}

static int16_t drv_double_read ( c6dofimu_t *ctx, uint8_t reg )
{
    uint16_t value;
    uint8_t read_buf[ 2 ];

    c6dofimu_generic_read( ctx, reg, read_buf, 2 );

    value = read_buf[ 1 ];
    value <<= 8;
    value |= read_buf[ 0 ];

    return value;
}

// ------------------------------------------------------------------------- END

