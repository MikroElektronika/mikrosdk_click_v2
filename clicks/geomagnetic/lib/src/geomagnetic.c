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

#include "geomagnetic.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define GEOMAGNETIC_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void geomagnetic_i2c_write ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void geomagnetic_i2c_read ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void geomagnetic_spi_write ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void geomagnetic_spi_read ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void geomagnetic_cfg_setup ( geomagnetic_cfg_t *cfg )
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
    cfg->i2c_address = GEOMAG_DEV_ADDR;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = GEOMAGNETIC_MASTER_SPI;
}

GEOMAGNETIC_RETVAL geomagnetic_init ( geomagnetic_t *ctx, geomagnetic_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == GEOMAGNETIC_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return GEOMAGNETIC_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = geomagnetic_i2c_read;
        ctx->write_f = geomagnetic_i2c_write;
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
        
        spi_cfg.default_write_data = GEOMAGNETIC_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  GEOMAGNETIC_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, GEOMAGNETIC_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = geomagnetic_spi_read;
        ctx->write_f = geomagnetic_spi_write;
    }

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return GEOMAGNETIC_OK;
}

void geomagnetic_default_cfg ( geomagnetic_t *ctx )
{
    geomagnetic_power_on_reset( ctx );
    geomagnetic_write_byte( ctx, GEOMAG_DATAREADY_ACTIVE_HIGH, GEOMAG_INTERR_AND_CHANNEL_EN_REG );  
}

void geomagnetic_generic_write ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void geomagnetic_generic_read ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

GEOMAGNETIC_RETVAL geomagnetic_write_byte ( geomagnetic_t *ctx, uint8_t input_data, uint8_t address )
{
    if ( ( address < 0x40 ) || ( address > 0x52 ) )
    {
        return GEOMAG_ADDR_ERR;
    }

    geomagnetic_generic_write( ctx, address, &input_data, 1 );

    return GEOMAG_OK;
}

GEOMAGNETIC_RETVAL geomagnetic_read_data ( geomagnetic_t *ctx, uint8_t *out_buf, uint8_t address, uint8_t len )
{
    if ( ( address < 0x40 ) || ( address > 0x52 ) )
    {
        return GEOMAG_ADDR_ERR;
    }

    if ( len > 19 )
    {
        return GEOMAG_NBYTES_ERR;
    }

    geomagnetic_generic_read( ctx, address, out_buf, len );

    return GEOMAG_OK;
}

uint8_t geomagnetic_check_ready ( geomagnetic_t *ctx )
{
    uint8_t tmp;

    geomagnetic_read_data( ctx, &tmp, GEOMAG_RHALL_LSB_REG, 1 );

    tmp &= GEOMAG_DATA_READY;

    return tmp;
}

void geomagnetic_read_axis_data ( geomagnetic_t *ctx, geomagnetic_axis_t *geomag_axis, uint16_t *resolution_hall )
{
    uint8_t data_buf[ 8 ];
    uint16_t temp;

    geomagnetic_read_data( ctx, data_buf, GEOMAG_DATAX_LSB_REG, 8 );

    temp = data_buf[ 1 ];
    temp <<= 5;
    temp |= data_buf[ 0 ] >> 3;
    geomag_axis->x_axis = temp;
    
    if ( geomag_axis->x_axis & 0x1000 )
    {
        geomag_axis->x_axis |= 0xE000;
    }

    temp = data_buf[ 3 ];
    temp <<= 5;
    temp |= data_buf[ 2 ] >> 3;
    geomag_axis->y_axis = temp;
    
    if ( geomag_axis->y_axis & 0x1000 )
    {
        geomag_axis->y_axis |= 0xE000;
    }

    temp = data_buf[ 5 ];
    temp <<= 7;
    temp |= data_buf[ 4 ] >> 1;
    geomag_axis->z_axis = temp;
    
    if ( geomag_axis->z_axis & 0x4000 )
    {
        geomag_axis->z_axis |= 0x8000;
    }

    temp = data_buf[ 7 ];
    temp <<= 6;
    temp |= data_buf[ 6 ] >> 2;
    *resolution_hall = temp;
}

GEOMAGNETIC_RETVAL geomagnetic_check_interrupt ( geomagnetic_t *ctx )
{
    if ( get_interrupt( ctx ) )
    {
        return GEOMAG_INTERRUPT_OCCURED;
    }
    else
    {
        return GEOMAG_OK;
    }
}

uint8_t get_interrupt ( geomagnetic_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

void geomagnetic_software_reset ( geomagnetic_t *ctx )
{
    geomagnetic_write_byte( ctx, GEOMAG_SOFT_RESET_EN | GEOMAG_SLEEP_MODE, GEOMAG_POWER_AND_RESET_CON_REG );
    Delay_100ms();
    geomagnetic_write_byte( ctx, GEOMAG_NORMAL_OPMODE_DR_10HZ, GEOMAG_DATARATE_AND_OPMODE_CON_REG );
    Delay_1sec();
}

void geomagnetic_power_on_reset ( geomagnetic_t *ctx )
{
    geomagnetic_write_byte( ctx, GEOMAG_SUSPEND_MODE_SPI4_EN, GEOMAG_POWER_AND_RESET_CON_REG );      
    Delay_100ms();    
    geomagnetic_write_byte( ctx, GEOMAG_SLEEP_MODE, GEOMAG_POWER_AND_RESET_CON_REG );      
    Delay_100ms();    
    geomagnetic_write_byte( ctx, GEOMAG_NORMAL_OPMODE_DR_10HZ, GEOMAG_DATARATE_AND_OPMODE_CON_REG );  
    Delay_1sec();
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void geomagnetic_i2c_write ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void geomagnetic_i2c_read ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void geomagnetic_spi_write ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void geomagnetic_spi_read ( geomagnetic_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );  
}

// ------------------------------------------------------------------------- END

