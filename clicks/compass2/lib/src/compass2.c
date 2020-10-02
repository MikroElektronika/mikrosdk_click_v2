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

#include "compass2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define COMPASS2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void compass2_i2c_write ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void compass2_i2c_read ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void compass2_spi_write ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void compass2_spi_read ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void compass2_cfg_setup ( compass2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x0F;
    cfg->sel = COMPASS2_MASTER_I2C;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

}

COMPASS2_RETVAL compass2_init ( compass2_t *ctx, compass2_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == COMPASS2_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return COMPASS2_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = compass2_i2c_read;
        ctx->write_f = compass2_i2c_write;
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
        
        spi_cfg.default_write_data = COMPASS2_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;
        

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  COMPASS2_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, COMPASS2_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 

        ctx->read_f = compass2_spi_read;
        ctx->write_f = compass2_spi_write;
    }
    
    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return COMPASS2_OK;
}

void compass2_default_cfg ( compass2_t *ctx )
{
    // Click default configuration

    ctx->output_resolution = 1;

    compass2_write_byte( ctx, COMPASS2_REG_CNTRL1, COMPASS2_MODE_POWER_DOWN ); 
}

void compass2_generic_write ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void compass2_generic_read ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void compass2_write_byte ( compass2_t *ctx, uint8_t reg, uint8_t data_buf ) 
{
    uint8_t write_reg[ 1 ];
    
    write_reg[ 0 ] = data_buf;
    compass2_generic_write( ctx, reg, write_reg, 1 );
}

uint8_t compass2_read_byte ( compass2_t *ctx, uint8_t reg ) 
{
    uint8_t read_reg[ 1 ];

    compass2_generic_read( ctx, reg, read_reg, 1 );

    return read_reg[ 0 ];
}

void compass2_reset ( compass2_t *ctx ) 
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

void compass2_i2c_disable ( compass2_t *ctx ) 
{
    compass2_write_byte( ctx, COMPASS2_REG_I2C_DISABLE, 0x1B );
}

void compass2_software_reset ( compass2_t *ctx ) 
{
    compass2_write_byte( ctx, COMPASS2_REG_CNTRL2, 0x01 );
}

float compass2_get_resolution_parameter ( uint8_t res ) 
{
    float retval = 0;

    switch ( res )
    {
        case COMPASS2_SET_RESOLUTION_14bit: 
        {
            retval = 10 * 4219 / 8190;
            break;
        }
        case COMPASS2_SET_RESOLUTION_16bit:
        {
            retval = 10 * 4219 / 32760;
            break;
        }    
        default:
        {
            return 0;
        }
    }

    return retval;
}

uint8_t compass2_get_rdy ( compass2_t *ctx ) 
{
    uint8_t ready;

    ready = compass2_read_byte( ctx, COMPASS2_REG_STATUS_1 );
    ready &= 1;

    return ready;
}

uint8_t compass2_get_data_overrun ( compass2_t *ctx ) 
{
    uint8_t data_over;

    data_over = compass2_read_byte( ctx, COMPASS2_REG_STATUS_1 );
    data_over &= 2;

    return data_over;
}

void compass2_get_adjustment( compass2_t *ctx, uint8_t *x, uint8_t *y, uint8_t *z ) 
{
    compass2_write_byte( ctx, COMPASS2_REG_CNTRL1, COMPASS2_MODE_FUSE_ROM );
    Delay_10ms( );

    *x = compass2_read_byte( ctx, COMPASS2_REG_X_AXIS_SENS ); 
    *y = compass2_read_byte( ctx, COMPASS2_REG_Y_AXIS_SENS );
    *z = compass2_read_byte( ctx, COMPASS2_REG_Z_AXIS_SENS );
    
    compass2_write_byte( ctx, COMPASS2_REG_CNTRL1, COMPASS2_MODE_POWER_DOWN );
    Delay_10ms( );
}

void compass2_set_out_resolution ( compass2_t *ctx, uint8_t res ) 
{
    ctx->output_resolution = res;
    
    compass2_write_byte( ctx, COMPASS2_REG_CNTRL1, res );
}

void compass2_set_mode ( compass2_t *ctx, uint8_t mode )
{
    ctx->output_resolution &= 0xF0;
    ctx->output_resolution |= mode;
    
    compass2_write_byte( ctx, COMPASS2_REG_CNTRL1, ctx->output_resolution );
    Delay_10ms( );
}

void compass2_get_all_data ( compass2_t *ctx, int16_t *x, int16_t *y, int16_t *z ) 
{
    uint8_t lsb  = 0;
    uint8_t msb  = 0;
    int16_t axis_data;

    lsb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_X_LOW );
    msb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_X_HIGH );
    axis_data = msb;
    axis_data <<= 8;
    axis_data |= lsb;
    *x = axis_data;
    
    lsb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_Y_LOW );
    msb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_Y_HIGH );
    axis_data = msb;
    axis_data <<= 8;
    axis_data |= lsb;
    *y = axis_data;

    lsb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_Z_LOW );
    msb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_Z_HIGH );
    axis_data = msb;
    axis_data <<= 8;
    axis_data |= lsb;
    *z = axis_data;
}

int16_t compass2_get_axis_data ( compass2_t *ctx, uint8_t axis ) 
{
    uint8_t lsb  = 0;
    uint8_t msb  = 0;
    int16_t axis_data;

    compass2_write_byte( ctx, COMPASS2_REG_CNTRL1, COMPASS2_MODE_FUSE_ROM );
    Delay_10ms( );

    if ( axis == COMPASS2_X_AXIS )
    {
        lsb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_X_LOW );
        msb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_X_HIGH );
    }
    else if (axis == COMPASS2_Y_AXIS)
    {
        lsb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_Y_LOW );
        msb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_Y_HIGH );
    }
    else
    {
        lsb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_Z_LOW );
        msb = compass2_read_byte( ctx, COMPASS2_REG_AXIS_Z_HIGH );
    }

    compass2_write_byte( ctx, COMPASS2_REG_CNTRL1, COMPASS2_MODE_POWER_DOWN );
    Delay_10ms( );
    
    axis_data = msb;
    axis_data <<= 8;
    axis_data |= lsb;
    
    return  axis_data;
}

void compass2_new_measurement ( compass2_t *ctx ) 
{
    compass2_reset( ctx );
    Delay_10ms( );

    compass2_set_out_resolution( ctx, ctx->output_resolution );
    compass2_set_mode( ctx, COMPASS2_MODE_CONT_MEAS_2 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void compass2_i2c_write ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void compass2_i2c_read ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void compass2_spi_write ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void compass2_spi_read ( compass2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, len );
    spi_master_deselect_device( ctx->chip_select );  

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt ];
    }
}

// ------------------------------------------------------------------------- END

