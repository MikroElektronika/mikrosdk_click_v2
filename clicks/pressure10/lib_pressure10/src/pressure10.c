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

#include "pressure10.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PRESSURE10_DUMMY 0

// ------------------------------------------------------------------ VARIABLES

static uint8_t dev_slave_addr;
static uint8_t dev_communitation;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void pressure10_i2c_write ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure10_i2c_read ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure10_spi_write ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure10_spi_read ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static uint8_t get_mask ( uint8_t ctrl_reg );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pressure10_cfg_setup ( pressure10_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PRESSURE10_DEVICE_SLAVE_ADDR_0;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = PRESSURE10_MASTER_I2C;
}

PRESSURE10_RETVAL pressure10_init ( pressure10_t *ctx, pressure10_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == PRESSURE10_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return PRESSURE10_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = pressure10_i2c_read;
        ctx->write_f = pressure10_i2c_write;
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
        
        spi_cfg.default_write_data = PRESSURE10_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  PRESSURE10_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, PRESSURE10_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = pressure10_spi_read;
        ctx->write_f = pressure10_spi_write;
    }
    
    // Input pins

    digital_in_init( &ctx->rdy, cfg->rdy );
    
    return PRESSURE10_OK;
}

void pressure10_default_cfg ( pressure10_t *ctx )
{
    pressure10_control_cfg( ctx, PRESSURE10_REG_DRDY_PIN_CRTL, 
                            PRESSURE10_CTRLDRDY_AFEV_DISABLE |
                            PRESSURE10_CTRLDRDY_ATDR_ENABLE |
                            PRESSURE10_CTRLDRDY_APOR_ENABLE |
                            PRESSURE10_CTRLDRDY_APDY_DISABLE );

    pressure10_control_cfg( ctx, PRESSURE10_REG_CONTROL_1, 
                            PRESSURE10_CTRL1_PDRP_HIGH_ACTIVE |
                            PRESSURE10_CTRL1_PTAP_HIGH_ACCURACY );  
                    
    pressure10_control_cfg( ctx, PRESSURE10_REG_CONTROL_2, 
                            PRESSURE10_CTRL2_TMES_ENABLE |
                            PRESSURE10_CTRL2_PMES_ENABLE | 
                            PRESSURE10_CTRL2_ODR_100HZ |
                            PRESSURE10_CTRL2_MODE_CONT_MEAS ); 

    pressure10_control_cfg( ctx, PRESSURE10_REG_ACTION_CONTROL_1, 
                            PRESSURE10_ACTRL1_TEMP_MEAS |
                            PRESSURE10_ACTRL1_PRESS_MEAS );
}

void pressure10_generic_write ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void pressure10_generic_read ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void pressure10_send_cmd ( pressure10_t *ctx, uint8_t cmd )
{
    if ( dev_communitation == I2C_COMMUNICATION )
    { 
        pressure10_generic_write( ctx, dev_slave_addr, &cmd, 1 );
    }
    else
    {
        cmd &= 0x7F;
        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, &cmd, 1 );
        spi_master_deselect_device( ctx->chip_select ); 
    }
}

uint8_t pressure10_check_communication ( pressure10_t *ctx )
{
    uint8_t device_id;

    pressure10_generic_read( ctx, PRESSURE10_REG_WHO_I_AM, &device_id, 1 );
    if ( device_id == PRESSURE10_DEF_WHO_I_AM )
    {
        return DEVICE_OK;
    }
    return DEVICE_ERROR;
}

void pressure10_get_status( pressure10_t *ctx, pressure10_status_t *status_obj )
{
    uint8_t status;
    pressure10_generic_read( ctx, PRESSURE10_REG_STATUS, &status, 1 );
    
    status_obj->busy       = ( status & 0x80 ) >> 7;
    status_obj->temp_meas  = ( status & 0x10 ) >> 4;
    status_obj->data_over  = ( status & 0x04 ) >> 2;
    status_obj->press_meas = ( status & 0x01 );
}

float pressure10_get_temperature ( pressure10_t *ctx )
{
    float temperature;
    int16_t raw_data;
    uint8_t tmp;
 
    pressure10_generic_read( ctx, PRESSURE10_REG_TEMP_OUT_HIGH, &tmp, 1 );
    raw_data = tmp << 8;
    pressure10_generic_read( ctx, PRESSURE10_REG_TEMP_OUT_LOW, &tmp, 1 );
    raw_data |= tmp;

    temperature = ( int16_t )raw_data / 256.0;
    return temperature;
}

float pressure10_get_pressure ( pressure10_t *ctx )
{
    float pressure;
    uint32_t raw_data;
    uint8_t tmp;
 
    pressure10_generic_read( ctx, PRESSURE10_REG_PRESSURE_OUT_HIGH, &tmp, 1 );
    raw_data = tmp;
    raw_data <<= 8;
    pressure10_generic_read( ctx, PRESSURE10_REG_PRESSURE_OUT_MID, &tmp, 1 );
    raw_data |= tmp;
    raw_data <<= 8;
    pressure10_generic_read( ctx, PRESSURE10_REG_PRESSURE_OUT_LOW, &tmp, 1 );
    raw_data |= tmp;

    pressure = ( uint32_t )raw_data & 0x0001FFFF;

    return pressure / 100.0;
}

void pressure10_control_cfg ( pressure10_t *ctx, uint8_t ctrl_reg, uint8_t wr_data )
{
    uint8_t raw_data;
    uint8_t mask_reg;

    pressure10_generic_read( ctx, ctrl_reg, &raw_data, 1 );
    mask_reg = get_mask( ctrl_reg );

    raw_data &= mask_reg;
    raw_data |= wr_data;
    
    pressure10_generic_write( ctx, ctrl_reg, &raw_data, 1 );
}

uint8_t pressure10_get_drdy_pin ( pressure10_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void pressure10_i2c_write ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void pressure10_i2c_read ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void pressure10_spi_write ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg & 0x7F;
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );     
}

static void pressure10_spi_read ( pressure10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg | 0x80;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );  
}

static uint8_t get_mask ( uint8_t ctrl_reg )
{
    switch ( ctrl_reg )
    {
        case PRESSURE10_REG_DRDY_PIN_CRTL:
        {
            return 0x6A;
        }
        case PRESSURE10_REG_CONTROL_1:
        {
            return 0xEC;
        }   
        case PRESSURE10_REG_CONTROL_2:
        {
            return 0x50;
        }        
        case PRESSURE10_REG_ACTION_CONTROL_1:
        {
            return 0xF5;
        }         
        case PRESSURE10_REG_ACTION_CONTROL_2:
        {
            return 0x7F;
        } 
        case PRESSURE10_REG_FIFO_CONTROL:
        {
            return 0x60;
        }
        case PRESSURE10_REG_AVERAGE_CONTROL:
        {
            return 0xC0;
        }  
    }
}

// ------------------------------------------------------------------------- END

