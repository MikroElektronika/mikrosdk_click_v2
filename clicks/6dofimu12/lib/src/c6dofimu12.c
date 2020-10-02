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

#include "c6dofimu12.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C6DOFIMU12_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c6dofimu12_i2c_write ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

static void c6dofimu12_i2c_read ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

static void c6dofimu12_spi_write ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

static void c6dofimu12_spi_read ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c6dofimu12_cfg_setup ( c6dofimu12_cfg_t *cfg )
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

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x68;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = C6DOFIMU12_MASTER_I2C;
}

C6DOFIMU12_RETVAL c6dofimu12_init ( c6dofimu12_t *ctx, c6dofimu12_cfg_t *cfg )
{
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == C6DOFIMU12_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return C6DOFIMU12_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = c6dofimu12_i2c_read;
        ctx->write_f = c6dofimu12_i2c_write;
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
        
        spi_cfg.default_write_data = C6DOFIMU12_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  C6DOFIMU12_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, C6DOFIMU12_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = c6dofimu12_spi_read;
        ctx->write_f = c6dofimu12_spi_write;
    }
    
    // Input pins

    digital_in_init( &ctx->pwm, cfg->pwm );
    digital_in_init( &ctx->int_pin, cfg->int_pin );


    return C6DOFIMU12_OK;
}

void c6dofimu12_default_cfg ( c6dofimu12_t *ctx )
{
    uint8_t tx_buf;
    tx_buf = C6DOFIMU12_GYR_EN_MASK | C6DOFIMU12_ACC_EN_MASK | C6DOFIMU12_TEMP_EN_MASK;
    c6dofimu12_generic_write( ctx, C6DOFIMU12_REG_PWR_CTRL_ADDR, &tx_buf, 1 );
    tx_buf = C6DOFIMU12_ACC_OSR2_PWR_PERFORMANCE | C6DOFIMU12_ACC_NORMAL_AVG4 | C6DOFIMU12_ACC_ODR_100HZ;
    c6dofimu12_generic_write( ctx, C6DOFIMU12_REG_ACC_CONF_ADDR, &tx_buf, 1 );
    tx_buf = C6DOFIMU12_GYR_PWR_PERFORMANCE | C6DOFIMU12_GYR_NORMAL_MODE | C6DOFIMU12_GYR_NOISE_OPTIMIZED | C6DOFIMU12_GYR_ODR_200HZ;
    c6dofimu12_generic_write( ctx, C6DOFIMU12_REG_GYR_CONF_ADDR, &tx_buf, 1 );
    tx_buf = C6DOFIMU12_FIFO_SELF_WAKE_UP_POS;
    c6dofimu12_generic_write( ctx, C6DOFIMU12_REG_PWR_CONF_ADDR, &tx_buf, 1 );
}

void c6dofimu12_generic_write ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void c6dofimu12_generic_read ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

C6DOFIMU12_RETVAL c6dofimu12_check_id ( c6dofimu12_t *ctx )
{
    uint8_t id_val;
    c6dofimu12_generic_read( ctx, C6DOFIMU12_REG_CHIP_ID_ADDR, &id_val, 1 );
    if ( id_val == C6DOFIMU12_DEVICE_ID_VAL )
    {
        return  C6DOFIMU12_SUCCESS;
    }
    else
    {
        return C6DOFIMU12_ERROR;
    }
}

C6DOFIMU12_RETVAL c6dofimu12_check_init_status ( c6dofimu12_t *ctx )
{
    uint8_t status_val;
    c6dofimu12_generic_read( ctx, C6DOFIMU12_REG_INTERNAL_STATUS_ADDR, &status_val, 1 );
    status_val = status_val & C6DOFIMU12_INIT_OK;
    
    if ( status_val == C6DOFIMU12_INIT_OK )
    {
        return C6DOFIMU12_SUCCESS;
    }
    else
    {
        return C6DOFIMU12_ERROR;
    }
}

void c6dofimu12_get_data ( c6dofimu12_t *ctx, c6dofimu12_accel_t *accel_data, c6dofimu12_gyro_t *gyro_data )
{
    uint8_t rx_buff[ 12 ];
    uint16_t tmp;

    c6dofimu12_generic_read( ctx, C6DOFIMU12_REG_ACC_X_LSB_ADDR, rx_buff, C6DOFIMU12_FIFO_ACC_LENGTH + C6DOFIMU12_FIFO_GYR_LENGTH );
    tmp = rx_buff[ 1 ];
    tmp = tmp << 8;
    tmp = tmp | rx_buff[ 0 ];
    accel_data->x = ( int16_t ) tmp;

    tmp = rx_buff[ 3 ];
    tmp = tmp << 8;
    tmp = tmp | rx_buff[ 2 ];
    accel_data->y = ( int16_t ) tmp;
    
    tmp = rx_buff[ 5 ];
    tmp = tmp << 8;
    tmp = tmp | rx_buff[ 4 ];
    accel_data->z = ( int16_t ) tmp;
    
    tmp = rx_buff[ 7 ];
    tmp = tmp << 8;
    tmp = tmp | rx_buff[ 6 ];
    gyro_data->x = ( int16_t ) tmp;
    
    tmp = rx_buff[ 9 ];
    tmp = tmp << 8;
    tmp = tmp | rx_buff[ 8 ];
    gyro_data->y = ( int16_t ) tmp;
    
    tmp = rx_buff[ 11 ];
    tmp = tmp << 8;
    tmp = tmp | rx_buff[ 10 ];
    gyro_data->z = ( int16_t ) tmp;

}

C6DOFIMU12_RETVAL c6dofimu12_check_int1 ( c6dofimu12_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

C6DOFIMU12_RETVAL c6dofimu12_check_int2 ( c6dofimu12_t *ctx )
{
    return digital_in_read( &ctx->pwm );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c6dofimu12_i2c_write ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    uint8_t tx_buf[ 8193 ];
    uint16_t cnt;
    
    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }

    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

static void c6dofimu12_i2c_read ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void c6dofimu12_spi_write ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &reg,  1 );
    spi_master_write( &ctx->spi, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );     
}

static void c6dofimu12_spi_read ( c6dofimu12_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 265 ] = { 0 };
    uint16_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    tx_buf[ 1 ] = C6DOFIMU12_SPI_COMMUNICATION_DUMMY;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 2, data_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );    

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt + 1 ];
    }
}

// ------------------------------------------------------------------------- END

