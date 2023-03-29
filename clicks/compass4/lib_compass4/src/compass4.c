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

#include "compass4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define COMPASS4_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void compass4_i2c_write ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void compass4_i2c_read ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void compass4_spi_write ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void compass4_spi_read ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static uint8_t drdy_wait ( compass4_t *ctx );

static void communication_delay ( void );
// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void compass4_cfg_setup ( compass4_cfg_t *cfg )
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
    cfg->i2c_address = COMPASS4_SLAVE_ADDRESS_GND_GND;
    cfg->sel = COMPASS4_MASTER_I2C;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

COMPASS4_RETVAL compass4_init ( compass4_t *ctx, compass4_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == COMPASS4_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return COMPASS4_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = compass4_i2c_read;
        ctx->write_f = compass4_i2c_write;

        digital_out_high( &ctx->cs );
        digital_out_high( &ctx->rst );
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
        
        spi_cfg.default_write_data = COMPASS4_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;
        
        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  COMPASS4_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, COMPASS4_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 

        ctx->read_f = compass4_spi_read;
        ctx->write_f = compass4_spi_write;

        digital_out_high( &ctx->rst );
        digital_out_low( &ctx->cs );
        Delay_100ms( );
        digital_out_high( &ctx->cs );
    }
    
    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return COMPASS4_OK;
}

void compass4_generic_write ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void compass4_generic_read ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void compass4_hardware_reset ( compass4_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

void compass4_set_rst_pin_state ( compass4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void compass4_software_reset ( compass4_t *ctx )
{
    uint8_t tmp;
    
    tmp = COMPASS4_CTRL3_SOFT_RESET;
    compass4_generic_write( ctx, COMPASS4_REG_CONTROL_3, &tmp, 1 );
}

void compass4_configuration ( compass4_t *ctx, uint8_t cfg1, uint8_t cfg2 )
{
    compass4_generic_write( ctx, COMPASS4_REG_CONTROL_2, &cfg2, 1 );
    compass4_generic_write( ctx, COMPASS4_REG_CONTROL_1, &cfg1, 1 );
}

uint8_t compass4_get_status( compass4_t *ctx, uint8_t status )
{
    uint8_t read_tmp;

    if ( status == COMPASS4_GET_STATUS_1 )
    {
        compass4_generic_read( ctx, COMPASS4_REG_STATUS_1, &read_tmp, 1 );
        return read_tmp;
    }
    else if ( status == COMPASS4_GET_STATUS_2 )
    {
        compass4_generic_read( ctx, COMPASS4_REG_STATUS_2, &read_tmp, 1 );
        return read_tmp;
    }
    return 0;
}

uint8_t compass4_check_device ( compass4_t *ctx )
{
    static volatile uint8_t id = 0;
    uint8_t err = 0;
    
    // Company ID
    compass4_generic_read( ctx, COMPASS4_REG_COMPANY_ID, &id, 1 );
    if ( id != COMPASS4_DEF_COMPANY_ID )
    {
        err |= 0x01;
    }
    // Device ID
    compass4_generic_read( ctx, COMPASS4_REG_DEVICE_ID, &id, 1 );
    if ( id != COMPASS4_DEF_DEVICE_ID )
    {
        err |= 0x02;
    }
    return err;
}

uint8_t compass4_get_interrupt ( compass4_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t compass4_get_axis ( compass4_t *ctx, compass4_axis_t *axis )
{
    int16_t raw_data;
    uint8_t err;
    uint8_t temp[ 2 ];
                                                 
    err = drdy_wait( ctx );

    compass4_generic_read( ctx, COMPASS4_REG_X_AXIS_MSB, &temp[ 0 ], 1 );
    raw_data = temp[ 0 ];
    raw_data <<= 8;
    compass4_generic_read( ctx, COMPASS4_REG_X_AXIS_LSB, &temp[ 1 ], 1 );
    raw_data |= temp[ 1 ]; 
    axis->x = raw_data; 

    compass4_generic_read( ctx, COMPASS4_REG_Y_AXIS_MSB, &temp[ 0 ], 1 );
    raw_data = temp[ 0 ];
    raw_data <<= 8;
    compass4_generic_read( ctx, COMPASS4_REG_Y_AXIS_LSB, &temp[ 1 ], 1 );
    raw_data |= temp[ 1 ]; 
    axis->y = raw_data; 

    compass4_generic_read( ctx, COMPASS4_REG_Z_AXIS_MSB, &temp[ 0 ], 1 );
    raw_data = temp[ 0 ];
    raw_data <<= 8;
    compass4_generic_read( ctx, COMPASS4_REG_Z_AXIS_LSB, &temp[ 1 ], 1 );
    raw_data |= temp[ 1 ]; 
    axis->z = raw_data; 

    return err;
}

uint8_t compass4_get_single_axis ( compass4_t *ctx, uint8_t axis_reg, int16_t *axis_data )
{
    int16_t raw_data;
    uint8_t err;
    uint8_t temp[ 2 ];
    
    err = drdy_wait( ctx ); 

    compass4_generic_read( ctx, axis_reg + 1, &temp[ 0 ], 1 );
    raw_data = temp[ 0 ];
    raw_data <<= 8;
    compass4_generic_read( ctx, axis_reg, &temp[ 1 ], 1 );
    raw_data |= temp[ 1 ];
    *axis_data = raw_data; 

    return err;
}

uint8_t compass4_get_magnetic_flux ( compass4_t *ctx, compass4_flux_t *flux )
{
    compass4_axis_t axis;
    uint8_t err;

    err = compass4_get_axis( ctx, &axis );
    flux->x = axis.x * FLUX_CONSTANT;
    flux->y = axis.y * FLUX_CONSTANT;
    flux->z = axis.z * FLUX_CONSTANT;

    return err;
}

uint8_t compass4_get_single_magnetic_flux ( compass4_t *ctx, uint8_t axis, float *flux_data )
{
    uint8_t err;
    int16_t raw_data;

    err = compass4_get_single_axis( ctx, axis, &raw_data );
    *flux_data = raw_data * FLUX_CONSTANT;

    return err;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void compass4_i2c_write ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void compass4_i2c_read ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void compass4_spi_write ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void compass4_spi_read ( compass4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );  
}

static uint8_t drdy_wait ( compass4_t *ctx )
{
    uint8_t drdy_timeout = 0;
    
    while ( compass4_get_interrupt( ctx ) != 1 )
    {
        if ( drdy_timeout > 100 )
        {
            return 1;
        }
        drdy_timeout++;
        Delay_10ms();
    }
    return 0;
}

static void communication_delay ( void )
{
    Delay_1ms();
}

// ------------------------------------------------------------------------- END

