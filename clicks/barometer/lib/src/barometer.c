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

#include "barometer.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BAROMETER_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void barometer_i2c_write ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void barometer_i2c_read ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void barometer_spi_write ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void barometer_spi_read ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void barometer_cfg_setup ( barometer_cfg_t *cfg )
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
    cfg->i2c_address = BAROMETER_I2C_ADDRESS_1;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->sel = BAROMETER_MASTER_I2C;
}

BAROMETER_RETVAL barometer_init ( barometer_t *ctx, barometer_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == BAROMETER_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return BAROMETER_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
        i2c_master_set_timeout( &ctx->i2c, 0 );
        
        digital_out_init( &ctx->cs, cfg->cs );
        digital_out_high( &ctx->cs );

        ctx->read_f = barometer_i2c_read;
        ctx->write_f = barometer_i2c_write;
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
        
        spi_cfg.default_write_data = BAROMETER_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;
        

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  BAROMETER_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, BAROMETER_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 

        ctx->read_f = barometer_spi_read;
        ctx->write_f = barometer_spi_write;
    }

    // Input pins

    digital_in_init( &ctx->rdy, cfg->rdy );

    return BAROMETER_OK;
}

void barometer_default_cfg ( barometer_t *ctx )
{
    uint8_t tmp;
    tmp = BAROMETER_DEFAULT_CONFIG;
    barometer_generic_write( ctx, BAROMETER_CTRL_REG1, &tmp, 1 );
}

void barometer_generic_write ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void barometer_generic_read ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

// Generic read data function
uint8_t barometer_read_data( barometer_t *ctx, uint8_t address )
{
    uint8_t read_reg;

    barometer_i2c_read( ctx, address, &read_reg, 1 );

    return read_reg;
}

// Sets the module active function 
void barometer_set_active( barometer_t *ctx )
{
    uint8_t temp;
    barometer_generic_read( ctx, BAROMETER_CTRL_REG1, &temp, 1 );
    temp |= BAROMETER_CONFIG_ACTIVE_MODE;
    barometer_generic_write( ctx, BAROMETER_CTRL_REG1, &temp, 1 );
}

// Read temperature in degrees of Celsius function
float barometer_get_temperature_c ( barometer_t *ctx )
{
    uint8_t buffer[ 2 ];
    int16_t result;
    float temperature_c;

    buffer[ 0 ] = barometer_read_data( ctx, BAROMETER_TEMP_OUT_H );
    buffer[ 1 ] = barometer_read_data( ctx, BAROMETER_TEMP_OUT_L );
    
    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];
    
    temperature_c = ( ( float ) result / 480.0 ) + 42.5;

    return temperature_c;
}

//Read temperature in degrees of Fahrenheit function
float barometer_get_temperature_f( barometer_t *ctx )
{
    uint8_t buffer[ 2 ];
    int16_t result;
    float temperature_f;

    buffer[ 0 ] = barometer_read_data( ctx, BAROMETER_TEMP_OUT_H );
    buffer[ 1 ] = barometer_read_data( ctx, BAROMETER_TEMP_OUT_L );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    temperature_f = ( ( float ) result / 480.0 * 1.8 ) + 108.5;

    return temperature_f;
}

/* Read pressure in milibars function */
float barometer_get_pressure( barometer_t *ctx )
{
    uint8_t buffer[ 3 ];
    uint32_t result;
    float pressure;
  
    buffer[ 0 ] = barometer_read_data( ctx, BAROMETER_PRESS_OUT_H );
    buffer[ 1 ] = barometer_read_data( ctx, BAROMETER_PRESS_OUT_L );
    buffer[ 2 ] = barometer_read_data( ctx, BAROMETER_PRESS_OUT_XL );
    
    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];
    result <<= 8;
    result |= buffer[ 2 ];

    pressure = ( float ) result / 4096.00;

    return pressure;
}

// Check sensor id - who am I function
uint8_t barometer_check_id ( barometer_t *ctx )
{
    return barometer_read_data( ctx, BAROMETER_WHO_AM_I );
}

// Check sensor status function
uint8_t barometer_check_status ( barometer_t *ctx )
{
    return barometer_read_data( ctx, BAROMETER_STATUS_REG );
}

// State of interrupt pin function
uint8_t barometer_check_interrupt ( barometer_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void barometer_i2c_write ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void barometer_i2c_read ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void barometer_spi_write ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void barometer_spi_read ( barometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

