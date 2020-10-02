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

#include "gyro5.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define GYRO5_DUMMY 0

#define GYRO5_SPI_READ                  0x80

#define GYRO5_TEMP_CALC_DEV             321.4
#define GYRO5_TEMP_CALC_ADD             21.0
#define GYRO5_CALC_RES_FS_SEL_500       0.0152587890625
#define GYRO5_CALC_RES_FS_SEL_1000      0.030517578125
#define GYRO5_CALC_RES_FS_SEL_2000      0.06103515625
#define GYRO5_CALC_RES_FS_SEL_4000      0.1220703125

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void gyro5_i2c_write ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void gyro5_i2c_read ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void gyro5_spi_write ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void gyro5_spi_read ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void gyro5_cfg_setup ( gyro5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = GYRO5_I2C_DEV_ADR_GND;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = GYRO5_MASTER_I2C;
}

GYRO5_RETVAL gyro5_init ( gyro5_t *ctx, gyro5_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == GYRO5_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;
 
        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return GYRO5_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        digital_out_high( &ctx->cs );

        ctx->read_f =  gyro5_i2c_read;
        ctx->write_f =  gyro5_i2c_write;
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
        
        spi_cfg.default_write_data = GYRO5_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  GYRO5_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, GYRO5_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f =  gyro5_spi_read;
        ctx->write_f =  gyro5_spi_write;
    }
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );    

    return GYRO5_OK;
}

void gyro5_default_cfg ( gyro5_t *ctx )
{
    // Click default configuration
    uint8_t tmp_data;
    
    tmp_data = GYRO5_CFG_PWR_MGMT_1_DEV_RST;
    gyro5_generic_write( ctx, GYRO5_REG_PWR_MGMT_1, &tmp_data, 1 );
    
    Delay_1sec( );
   
    if ( ctx->master_sel == GYRO5_MASTER_SPI )
    {
        tmp_data = GYRO5_CFG_USER_CTRL_I2C_IF_DIS;
        gyro5_generic_write( ctx, GYRO5_REG_USER_CTRL, &tmp_data, 1 );
    }
    
    tmp_data = GYRO5_CFG_SMPLRT_DIV_DEF;
    gyro5_generic_write( ctx, GYRO5_REG_SMPLRT_DIV, &tmp_data, 1 );
    
    tmp_data = GYRO5_CFG_CONFIG_DEF;
    gyro5_generic_write( ctx, GYRO5_REG_CONFIG, &tmp_data, 1 );
    
    tmp_data = GYRO5_CFG_GYRO_CONFIG_FS_SEL_4000;
    gyro5_generic_write( ctx, GYRO5_REG_GYRO_CONFIG, &tmp_data, 1 );
    
    tmp_data = GYRO5_CFG_FIFO_EN_DIS_ALL;
    gyro5_generic_write( ctx, GYRO5_REG_FIFO_EN, &tmp_data, 1 );
    
    tmp_data = GYRO5_CFG_INT_PIN_CFG_INT_LEVEL;
    tmp_data |= GYRO5_CFG_INT_PIN_CFG_INT_RD_CLEAR;
    tmp_data |= GYRO5_CFG_INT_PIN_CFG_FSYNC_INT_LEVEL;
    gyro5_generic_write( ctx, GYRO5_REG_INT_PIN_CFG, &tmp_data, 1 );
    
    tmp_data = GYRO5_CFG_INT_ENABLE_DATA_RDY_EN;
    gyro5_generic_write( ctx, GYRO5_REG_INT_ENABLE, &tmp_data, 1 );
    
    tmp_data = GYRO5_CFG_PWR_MGMT_1_CLKSEL_PLL;
    gyro5_generic_write( ctx, GYRO5_REG_PWR_MGMT_1, &tmp_data, 1 );
    
    tmp_data = GYRO5_CFG_PWR_MGMT_2_DIS_ALL;
    gyro5_generic_write( ctx, GYRO5_REG_PWR_MGMT_2, &tmp_data, 1 ); 
}

void gyro5_generic_write ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void gyro5_generic_read ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t gyro5_get_int ( gyro5_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t gyro5_int_status ( gyro5_t *ctx, uint8_t int_type )
{
    uint8_t tmp_data;
    
    gyro5_generic_read( ctx, GYRO5_REG_INT_STATUS, &tmp_data, 1 );
    
    if ( int_type == GYRO5_STATUS_INT_TYPES_INT_DATA_RDY )
    {
        tmp_data &= GYRO5_STATUS_INT_DATA_RDY;
        
        if ( tmp_data == GYRO5_STATUS_INT_DATA_RDY )
        {
            return GYRO5_STATUS_INT_DATA_RDY;
        }
        else
        {
            return GYRO5_STATUS_INT_NOT_DATA_RDY;
        }
    }
    else if ( int_type == GYRO5_STATUS_INT_TYPES_INT_FSYNC )
    {
        tmp_data &= GYRO5_STATUS_INT_FSYNC;
        
        if ( tmp_data == GYRO5_STATUS_INT_FSYNC )
        {
            return GYRO5_STATUS_INT_DATA_RDY;
        }
        else
        {
            return GYRO5_STATUS_INT_NOT_DATA_RDY;
        }
    }
    else if ( int_type == GYRO5_STATUS_INT_TYPES_SEL_FIFO_OFLOW )
    {
        tmp_data &= GYRO5_STATUS_INT_FIFO_OFLOW;
        
        if ( tmp_data == GYRO5_STATUS_INT_FIFO_OFLOW )
        {
            return GYRO5_STATUS_INT_DATA_RDY;
        }
        else
        {
            return GYRO5_STATUS_INT_NOT_DATA_RDY;
        }
    }
}

void gyro5_get_temperature ( gyro5_t *ctx, float *temperature )
{
    uint8_t tmp_buf[ 2 ];
    int16_t aux_temp;
    float res_temp;
    
    gyro5_generic_read( ctx, GYRO5_REG_TEMP_OUT_H, &tmp_buf, 2 );

    aux_temp = 0;
    aux_temp |= tmp_buf[ 0 ];
    aux_temp <<= 8;
    aux_temp |= tmp_buf[ 1 ];

    res_temp = ( float ) aux_temp;
    res_temp /= GYRO5_TEMP_CALC_DEV;
    res_temp += GYRO5_TEMP_CALC_ADD;
    
    *temperature = res_temp;
}

void gyro5_get_axes ( gyro5_t *ctx, float *x_axis, float *y_axis, float *z_axis )
{
    uint8_t tmp_buf[ 6 ];
    
    int16_t aux_x_axis;
    int16_t aux_y_axis;
    int16_t aux_z_axis;
    
    float aux_resolution;
    
    gyro5_generic_read( ctx, GYRO5_REG_GYRO_CONFIG, &tmp_buf, 1 );
    
    tmp_buf[ 0 ] &= GYRO5_CFG_GYRO_CONFIG_FS_SEL_4000;
    
    switch ( tmp_buf[ 0 ] )
    { 
        case GYRO5_CFG_GYRO_CONFIG_FS_SEL_500 :
        {
            aux_resolution = GYRO5_CALC_RES_FS_SEL_500; // 500.0 / 32768.0
            break;
        }
        case GYRO5_CFG_GYRO_CONFIG_FS_SEL_1000 :
        {
            aux_resolution = GYRO5_CALC_RES_FS_SEL_1000; // 1000.0 / 32768.0
            break;
        }
        case GYRO5_CFG_GYRO_CONFIG_FS_SEL_2000 :
        {
            aux_resolution = GYRO5_CALC_RES_FS_SEL_2000; // 2000.0 / 32768.0
            break;
        }
        case GYRO5_CFG_GYRO_CONFIG_FS_SEL_4000 :
        {
            aux_resolution = GYRO5_CALC_RES_FS_SEL_4000; // 4000.0 / 32768.0
            break;
        }
        default :
        {
            break;
        }
    }

    gyro5_generic_read( ctx, GYRO5_REG_GYRO_XOUT_H, &tmp_buf, 6 );

    aux_x_axis = 0;
    aux_x_axis |= tmp_buf[ 0 ];
    aux_x_axis <<= 8;
    aux_x_axis |= tmp_buf[ 1 ];

    aux_y_axis = 0;
    aux_y_axis |= tmp_buf[ 2 ];
    aux_y_axis <<= 8;
    aux_y_axis |= tmp_buf[ 3 ];

    aux_z_axis = 0;
    aux_z_axis |= tmp_buf[ 4 ];
    aux_z_axis <<= 8;
    aux_z_axis |= tmp_buf[ 5 ];
    
    *x_axis = ( float ) ( ( aux_x_axis ) * aux_resolution );
    *y_axis = ( float ) ( ( aux_y_axis ) * aux_resolution );
    *z_axis = ( float ) ( ( aux_z_axis ) * aux_resolution );
}

void gyro5_sleep ( gyro5_t *ctx, uint8_t en_sleep )
{
    uint8_t tmp_data;
    
    gyro5_generic_read( ctx, GYRO5_REG_PWR_MGMT_1, &tmp_data, 1 );
    
    if ( en_sleep == GYRO5_SLEEP_STATUS_DIS )
    {
        tmp_data &= ~GYRO5_CFG_PWR_MGMT_1_SLEEP;
    }
    else if ( en_sleep == GYRO5_SLEEP_STATUS_EN )
    {
        tmp_data |= GYRO5_CFG_PWR_MGMT_1_SLEEP;
    }
    
    gyro5_generic_write( ctx, GYRO5_REG_PWR_MGMT_1, &tmp_data, 1 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void gyro5_i2c_write ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void gyro5_i2c_read ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void gyro5_spi_write ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void gyro5_spi_read ( gyro5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg | GYRO5_SPI_READ;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 
}

// ------------------------------------------------------------------------- END

