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

#include "gyro3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define GYRO3_DUMMY 0

// ------------------------------------------------------------------ VARIABLES

static uint8_t rd_buf[ 10 ];

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void gyro3_i2c_write ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void gyro3_i2c_read ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void gyro3_spi_write ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void gyro3_spi_read ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void gyro3_cfg_setup ( gyro3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->di2   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;  
    cfg->i2c_address = GYRO3_DEVICE_ADDR_SA0;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    //cfg->sel = GYRO3_MASTER_I2C;
    cfg->sel = GYRO3_MASTER_SPI;
}

GYRO3_RETVAL gyro3_init ( gyro3_t *ctx, gyro3_cfg_t *cfg )
{
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == GYRO3_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return GYRO3_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = gyro3_i2c_read;
        ctx->write_f = gyro3_i2c_write;
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
        
        spi_cfg.default_write_data = GYRO3_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;
        
        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  GYRO3_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, GYRO3_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = gyro3_spi_read;
        ctx->write_f = gyro3_spi_write;
    }
    
    // Input pins

    digital_in_init( &ctx->di2, cfg->di2 );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return GYRO3_OK;
}

void gyro3_default_cfg ( gyro3_t *ctx )
{
    gyro3_write( ctx, GYRO3_CTRL_REG5, 0x80 );
    gyro3_write( ctx, GYRO3_CTRL_REG1, 0x4F );
    gyro3_write( ctx, GYRO3_CTRL_REG2, 0x39 );
    gyro3_write( ctx, GYRO3_CTRL_REG3, 0xA8 );
    gyro3_write( ctx, GYRO3_CTRL_REG4, 0x30 );
    gyro3_write( ctx, GYRO3_CTRL_REG5, 0x1F );
    gyro3_write( ctx, GYRO3_FIFO_CTRL, 0x00 );
    gyro3_write( ctx, GYRO3_INT1_CFG,  0x40 );
}

void gyro3_generic_write ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void gyro3_generic_read ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t gyro3_int_get ( gyro3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t gyro3_di2_get ( gyro3_t *ctx )
{
    return digital_in_read( &ctx->di2 );
}

void gyro3_read ( gyro3_t *ctx, uint8_t register_address, uint8_t * read_buffer, uint8_t n_bytes )
{    
    gyro3_generic_read( ctx, register_address, read_buffer, n_bytes );       
}

void gyro3_write ( gyro3_t *ctx, uint8_t register_address, uint8_t value )
{
    gyro3_generic_write( ctx, register_address, &value, 1 );       
}

void gyro3_get_temp ( gyro3_t *ctx, uint8_t *temperature_value )
{
    gyro3_read( ctx, GYRO3_OUT_TEMP, temperature_value, 1 );
}

void gyro3_get_axes ( gyro3_t *ctx, float *x_axis, float *y_axis, float *z_axis, uint8_t measurement_range )
{
    float scale_const = 0.0;
    int16_t aux_x = 0;
    int16_t aux_y = 0;
    int16_t aux_z = 0;
    
    *x_axis = 0;
    *y_axis = 0;
    *z_axis = 0;
    
    if ( measurement_range == GYRO3_MEAS_RANGE_245 )
    {
        scale_const = 8.75;
    }
    else if ( measurement_range == GYRO3_MEAS_RANGE_500 )
    {
        scale_const = 17.5;
    }
    else if ( measurement_range == GYRO3_MEAS_RANGE_2000 )
    {
        scale_const = 70.0;
    }
    else
    {
        scale_const = 70.0;
    }
    
    gyro3_read( ctx, GYRO3_OUT_X_L, rd_buf, 6 );

    aux_x |= rd_buf[ 1 ];
    aux_x <<= 8;
    aux_x |= rd_buf[ 0 ];

    aux_y |= rd_buf[ 3 ];
    aux_y <<= 8;
    aux_y |= rd_buf[ 2 ];

    aux_z |= rd_buf[ 5 ];
    aux_z <<= 8;
    aux_z |= rd_buf[ 4 ];

    *x_axis = ( float )( aux_x * scale_const );
    *x_axis /= 1000.0;
    *y_axis = ( float )( aux_y * scale_const );
    *y_axis /= 1000.0;
    *z_axis = ( float )( aux_z * scale_const );
    *z_axis /= 1000.0;
}


void gyro3_get_status ( gyro3_t *ctx, uint8_t * status_register )
{
    gyro3_read( ctx, GYRO3_STATUS_REG, status_register, 1 );
}

void gyro3_get_fifo_data_level ( gyro3_t *ctx, uint8_t * fifo_data_level )
{
    gyro3_read( ctx, GYRO3_FIFO_SRC, fifo_data_level, 1 );
    *fifo_data_level &= 0x1F;
}

void gyro3_set_int1_thresholds ( gyro3_t *ctx, int16_t x_threshold, int16_t y_threshold, int16_t z_threshold )
{
    uint8_t aux_buffer[ 6 ];

    aux_buffer[ 0 ] = x_threshold >> 8;
    aux_buffer[ 1 ] = x_threshold;
    aux_buffer[ 2 ] = y_threshold >> 8;
    aux_buffer[ 3 ] = y_threshold;
    aux_buffer[ 4 ] = z_threshold >> 8;
    aux_buffer[ 5 ] = z_threshold;

    gyro3_write( ctx, GYRO3_INT1_THS_XH, aux_buffer[ 0 ] );
    gyro3_write( ctx, GYRO3_INT1_THS_XL, aux_buffer[ 1 ] );
    gyro3_write( ctx, GYRO3_INT1_THS_YH, aux_buffer[ 2 ] );
    gyro3_write( ctx, GYRO3_INT1_THS_YL, aux_buffer[ 3 ] );
    gyro3_write( ctx, GYRO3_INT1_THS_ZH, aux_buffer[ 4 ] );
    gyro3_write( ctx, GYRO3_INT1_THS_ZL, aux_buffer[ 5 ] );
}

uint8_t gyro3_set_int1_duration ( gyro3_t *ctx, uint8_t wait_enable_bit, uint8_t duration_value )
{
    if ( ( ( wait_enable_bit == 0x80 ) || ( wait_enable_bit == 0x00 ) ) && ( duration_value <= 127 ) )
    {
        gyro3_write( ctx, GYRO3_INT1_DURATION, ( wait_enable_bit | duration_value ) );
        return 0;
    }
    else
    {
        return 1;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void gyro3_i2c_write ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void gyro3_i2c_read ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void gyro3_spi_write ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
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

static void gyro3_spi_read ( gyro3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg | 0xC0;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );   
}

// ------------------------------------------------------------------------- END

