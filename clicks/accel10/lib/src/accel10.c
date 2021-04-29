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

#include "accel10.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ACCEL10_DUMMY                                        0

#define ACCEL10_SPI_CMD_WRITE                                0x00
#define ACCEL10_SPI_CMD_READ                                 0x80


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void accel10_i2c_write ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel10_i2c_read ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel10_spi_write ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel10_spi_read ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel10_cfg_setup ( accel10_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->it1 = HAL_PIN_NC;
    cfg->it2 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ACCEL10_SLAVE_ADDRESS_GND;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = ACCEL10_MASTER_I2C;
}

ACCEL10_RETVAL accel10_init ( accel10_t *ctx, accel10_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == ACCEL10_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return ACCEL10_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
        
        digital_out_init( &ctx->cs, cfg->cs );
        digital_out_high( &ctx->cs );

        ctx->read_f = accel10_i2c_read;
        ctx->write_f = accel10_i2c_write;
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
        
        spi_cfg.default_write_data = ACCEL10_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;
        
        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  ACCEL10_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, ACCEL10_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 

        ctx->read_f = accel10_spi_read;
        ctx->write_f = accel10_spi_write;
    }

    // Input pins

    digital_in_init( &ctx->it1, cfg->it1 );
    digital_in_init( &ctx->it2, cfg->it2 );

    return ACCEL10_OK;
}

void accel10_default_cfg ( accel10_t *ctx )
{
    uint8_t tx_data;
    
    // Click default configuration 
    
    tx_data = ACCEL10_LP_MODE_2
            | ACCEL10_MODE_LOW_POWER
            | ACCEL10_ODR_100Hz;
    accel10_generic_write ( ctx, ACCEL10_REG_CTRL1, &tx_data , 1 );
    
    tx_data = ACCEL10_LOW_NOISE_DISABLE
            | ACCEL10_FSD_LOW_PASS
            | ACCEL10_FS_2G
            | ACCEL10_BW_FILT_ODR2;
    accel10_generic_write ( ctx, ACCEL10_REG_CTRL6, &tx_data, 1 );
}

void accel10_generic_write ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void accel10_generic_read ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

ACCEL10_RETVAL accel10_check_id ( accel10_t *ctx )
{
    uint8_t id_val;

    accel10_generic_read( ctx, ACCEL10_REG_WHO_AM_I, &id_val, 1 );

    if ( id_val == ACCEL10_WHO_AM_I_DEFAULT_VALUE )
    {
        return ACCEL10_SUCCESS;
    }
    else
    {
        return ACCEL10_ERROR;
    }
}

uint8_t accel10_check_data_ready ( accel10_t *ctx )
{
    uint8_t status_val;

    accel10_generic_read( ctx, ACCEL10_REG_STATUS, &status_val, 1 );
    status_val &= ACCEL10_STATUS_DATA_READY;

    return status_val;
}

void accel10_soft_reset ( accel10_t *ctx )
{
    uint8_t tmp;

    accel10_generic_read ( ctx, ACCEL10_REG_CTRL2, &tmp, 1 );
    
    tmp |= ACCEL10_SOFT_RESET_ENABLE;
    
    accel10_generic_write ( ctx, ACCEL10_REG_CTRL2, &tmp, 1 );
}

void accel10_get_data ( accel10_t *ctx, accel10_data_t *p_accel_data )
{
    uint8_t rx_buf[ 6 ];
    uint16_t tmp;
    int16_t s_tmp;
    uint8_t ctrl1_val;
    
    accel10_generic_read ( ctx, ACCEL10_REG_CTRL1, &ctrl1_val, 1 );
    ctrl1_val &= ACCEL10_LP_MODE_2 | ACCEL10_LP_MODE_3 | ACCEL10_MODE_LOW_POWER;

    accel10_generic_read( ctx, ACCEL10_REG_OUT_X_L, rx_buf, 6 );

    tmp = rx_buf[ 1 ];
    tmp <<= 8;
    tmp |= rx_buf[ 0 ];
    s_tmp = ( int16_t ) tmp;
    
    if ( ctrl1_val == ACCEL10_LP_MODE_1 | ACCEL10_MODE_LOW_POWER )
    {
        s_tmp >>= 4;
    }
    else
    {
        s_tmp >>= 2;
    }

    p_accel_data->x = s_tmp;

    tmp = rx_buf[ 3 ];
    tmp <<= 8;
    tmp |= rx_buf[ 2 ];
    s_tmp = ( int16_t ) tmp;
    
   if ( ctrl1_val == ACCEL10_LP_MODE_1 | ACCEL10_MODE_LOW_POWER )
    {
        s_tmp >>= 4;
    }
    else
    {
        s_tmp >>= 2;
    }
    
    p_accel_data->y = s_tmp;

    tmp = rx_buf[ 5 ];
    tmp <<= 8;
    tmp |= rx_buf[ 4 ];
    s_tmp = ( int16_t ) tmp;

    if ( ctrl1_val == ACCEL10_LP_MODE_1 | ACCEL10_MODE_LOW_POWER )
    {
        s_tmp >>= 4;
    }
    else
    {
        s_tmp >>= 2;
    }
    
    p_accel_data->z = s_tmp;
}

int8_t accel10_read_temperature ( accel10_t *ctx )
{
    uint8_t tmp;
    int8_t temperature;

    accel10_generic_read ( ctx, ACCEL10_REG_OUT_T, &tmp, 1 );
    
    temperature = ( int8_t ) tmp; 
    
    temperature += 25;

    return temperature;
}

uint8_t accel10_check_it1 ( accel10_t *ctx )
{
    return digital_in_read( &ctx->it1 );
}

uint8_t accel10_check_it2 ( accel10_t *ctx )
{
    return digital_in_read( &ctx->it2 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void accel10_i2c_write ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel10_i2c_read ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void accel10_spi_write ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel10_spi_read ( accel10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | ACCEL10_SPI_CMD_READ;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );  
}

// ------------------------------------------------------------------------- END

