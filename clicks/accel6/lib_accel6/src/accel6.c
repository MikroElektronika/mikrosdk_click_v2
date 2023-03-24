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

#include "accel6.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define ACCEL6_DUMMY          0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void accel6_i2c_write ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel6_i2c_read ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel6_spi_write ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void accel6_spi_read ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void wait_offset ( accel6_t *ctx );

static int16_t accel6_read_data( accel6_t *ctx, uint8_t reg );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void accel6_cfg_setup ( accel6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x18;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = 0;
    cfg->sel = ACCEL6_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->dev_gaus = 2.0;
    cfg->dev_freq = 7.81;
}

ACCEL6_RETVAL accel6_init ( accel6_t *ctx, accel6_cfg_t *cfg )
{
    
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == ACCEL6_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return ACCEL6_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = accel6_i2c_read;
        ctx->write_f = accel6_i2c_write;
    }
    else
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );
        //spi_cfg.mode        = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  ACCEL6_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, ACCEL6_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_mode( &ctx->spi, cfg->spi_mode );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->read_f = accel6_spi_read;
        ctx->write_f = accel6_spi_write;

    }
    ctx->device_gaus = cfg->dev_gaus;
    ctx->device_freq = cfg->dev_freq;
    

    return ACCEL6_OK;
}

void accel6_generic_write ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void accel6_generic_read ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void accel6_soft_reset ( accel6_t *ctx )
{
    uint8_t temp;
    temp = ACCEL6_SOFT_RESET;
    accel6_generic_write( ctx, ACCEL6_REG_BGW_SOFTRESET, &temp, 1 );
}

void accel6_default_cfg ( accel6_t *ctx, uint8_t range_data, uint8_t bw_data, uint8_t lpw_data )
{
    uint8_t temp;
    
    accel6_generic_write( ctx, ACCEL6_REG_PMU_RANGE, &range_data, 1 );
    accel6_generic_write( ctx, ACCEL6_REG_PMU_BW, &bw_data, 1 );
    accel6_generic_write( ctx, ACCEL6_REG_PMU_LPW, &lpw_data, 1 );
    
    Delay_100ms();
    temp = ACCEL6_I2C_ENABLE | ACCEL6_I2C_WTD_50ms;

    accel6_generic_write( ctx, ACCEL6_REG_BGW_SPI3_WDT, &temp, 1 );
    
    temp = ACCEL6_INT_EN_1_DATA_ENABLE;
    accel6_generic_write( ctx, ACCEL6_REG_INT_EN_1, &temp, 1 );
    temp = ACCEL6_INT1_MAP_DATA_ENABLE;
    accel6_generic_write( ctx, ACCEL6_REG_INT_MAP_1, &temp, 1 );
   
    Delay_100ms();
    
    temp = ACCEL6_INT_EN_0_SINGLE_TAP_ENABLE |
           ACCEL6_INT_EN_0_DOUBLE_TAP_ENABLE |
           ACCEL6_INT_EN_0_ORIENT_ENABLE |
           ACCEL6_INT_EN_0_SLOPE_X_ENABLE |
           ACCEL6_INT_EN_0_SLOPE_Y_ENABLE |
           ACCEL6_INT_EN_0_SLOPE_Z_ENABLE |
           ACCEL6_INT_EN_0_FLAT_ENABLE;

    accel6_generic_write( ctx, ACCEL6_REG_INT_EN_0, &temp, 1 );

    temp = ACCEL6_INT1_MAP_ORIENT_ENABLE |
           ACCEL6_INT1_MAP_SINGLE_TAP_ENABLE | 
           ACCEL6_INT1_MAP_DOUBLE_TAP_ENABLE |
           ACCEL6_INT1_MAP_SLOPE_ENABLE;

    accel6_generic_write( ctx, ACCEL6_REG_INT_MAP_0, &temp, 1 );
    Delay_100ms();
    
    temp = 0x0A;
    accel6_generic_write( ctx, ACCEL6_REG_INT9, &temp, 1 );

    temp = ACCEL6_INT2_CTRL_ACTIVE_HIGH_LEVEL | ACCEL6_INT1_CTRL_ACTIVE_HIGH_LEVEL;

    accel6_generic_write( ctx, ACCEL6_REG_INT_OUT_CTRL, &temp, 1 );
    
    // storage accel range
    
    if ( range_data == ACCEL6_PMU_RANGE_2g )
    {
        ctx->device_gaus = 2.0;
    }
    else if ( range_data == ACCEL6_PMU_RANGE_4g )
    {
        ctx->device_gaus = 4.0;
    }
    else if ( range_data == ACCEL6_PMU_RANGE_8g )
    {
        ctx->device_gaus = 8.0;
    }
    else if ( range_data == ACCEL6_PMU_RANGE_16g )
    {
        ctx->device_gaus = 16.0;
    }
    
    // storage bandwidth data
    
    if ( bw_data == ACCEL6_PMU_BW_7_81Hz )
    {
        ctx->device_freq = 7.81;
    }
    else if ( bw_data == ACCEL6_PMU_BW_15_63Hz )
    {
        ctx->device_freq = 15.63;
    }
    else if ( bw_data == ACCEL6_PMU_BW_31_25Hz )
    {
        ctx->device_freq = 31.25;
    }
    else if ( bw_data == ACCEL6_PMU_BW_62_5Hz )
    {
        ctx->device_freq = 62.50;
    }
    else if ( bw_data == ACCEL6_PMU_BW_125Hz )
    {
        ctx->device_freq = 125.0;
    }
    else if ( bw_data == ACCEL6_PMU_BW_250Hz )
    {
        ctx->device_freq = 250.0;
    }
    else if ( bw_data == ACCEL6_PMU_BW_500Hz )
    {
        ctx->device_freq = 500.0;
    }
}

void accel6_data_offset ( accel6_t *ctx, uint8_t set_offset, float *offset_data )
{
    uint16_t offset_x = 0;
    uint16_t offset_y = 0;
    uint16_t offset_z = 0;
    uint8_t temp;
    
    accel6_generic_write( ctx, ACCEL6_REG_OFC_SETTINGS, &set_offset, 1 );
                                              
    temp = ACCEL6_OFFSET_TRIGGER_X_AXIS;
    accel6_generic_write( ctx, ACCEL6_REG_OFC_CTRL, &temp, 1 );
    wait_offset( ctx );
    temp = ACCEL6_OFFSET_TRIGGER_Y_AXIS;
    accel6_generic_write( ctx, ACCEL6_REG_OFC_CTRL, &temp, 1 );
    wait_offset( ctx );
    temp = ACCEL6_OFFSET_TRIGGER_Z_AXIS;
    accel6_generic_write( ctx, ACCEL6_REG_OFC_CTRL, &temp, 1 );
    wait_offset( ctx ); 
    
    offset_x = accel6_read_data( ctx, ACCEL6_REG_OFC_OFFSET_X );
    offset_x = offset_x << 8;
    offset_data[ 0 ] = offset_x * ( ctx->device_freq / 256.0 );
    
    offset_y = accel6_read_data( ctx, ACCEL6_REG_OFC_OFFSET_Y );
    offset_y = offset_y << 8;
    offset_data[ 1 ] = offset_y * (  ctx->device_freq / 256.0);
    
    offset_z = accel6_read_data( ctx, ACCEL6_REG_OFC_OFFSET_Z );
    offset_z = offset_z << 8;
    offset_data[ 2 ] = offset_z * (  ctx->device_freq / 256.0);
}

uint8_t accel6_get_tap_status ( accel6_t *ctx )
{
    uint8_t tap;
    
    accel6_generic_read( ctx, ACCEL6_REG_INT_STATUS_2, &tap, 1 );
    
     if ( ( tap & 0x80 ) != 0 )
     {
         if ( ( tap & 0x40 ) != 0 )
         {
             return TAP_X_NEGATIVE;
         }
         if ( ( tap & 0x20 ) != 0 )
         {
             return TAP_Y_NEGATIVE;
         }
         if ( ( tap & 0x10 ) != 0 )
         {
             return TAP_Z_NEGATIVE;
         }
     }
     else 
     {
         if ( ( tap & 0x40 ) != 0 )
         {
              return TAP_X_POSITIVE;
         }
         if ( ( tap & 0x20 ) != 0 )
         {
              return TAP_Y_POSITIVE;
         }
         if ( ( tap & 0x10 ) != 0 )
         {
              return TAP_Z_POSITIVE;
         }
     }
     return NON_TAP;
}

uint8_t accel6_get_slope_status ( accel6_t *ctx )
{
    uint8_t slope;

    accel6_generic_read( ctx, ACCEL6_REG_INT_STATUS_2, &slope, 1 );

    if ( ( slope & 0x08 ) != 0 )
    {
        if ( ( slope & 0x04 ) != 0 )
        {
            return SLOPE_X_NEGATIVE;
        }
        if ( ( slope & 0x02 ) != 0 )
        {
           return SLOPE_Y_NEGATIVE;
        }
        if ( ( slope & 0x01 ) != 0 )
        {
            return SLOPE_Z_NEGATIVE;
        }
    }
    else
    {
        if ( ( slope & 0x04 ) != 0 )
        {
             return SLOPE_X_POSITIVE;
        }
        if ( ( slope & 0x02 ) != 0 )
        {
             return SLOPE_Y_POSITIVE;
        }
        if ( ( slope & 0x01 ) != 0 )
        {
             return SLOPE_Z_POSITIVE;
        }
    }
    return NON_SLOPE;
}

void accel6_get_orient ( accel6_t *ctx, uint8_t *z_orient, uint8_t *xy_orient )
{
    uint8_t orient;
    
    accel6_generic_read( ctx, ACCEL6_REG_INT_STATUS_3, &orient, 1);
    
    if ( ( orient & 0x40 ) != 0 )
    {
        z_orient[ 0 ] = Z_ORIENT_UPWARD_LOOKING;
    }
    else
    {
        z_orient[ 0 ] = Z_ORIENT_DOWNWARD_LOOKING;
    }
    
    if  ( ( orient & 0x30 ) == 0x30 )
    {
        xy_orient[ 0 ] = XY_ORIENT_LANDSCAPE_RIGHT;
    }
    else if ( ( orient & 0x20 ) != 0 )
    {
        xy_orient[ 0 ] = XY_ORIENT_LANDSCAPE_LEFT;
    }
    else if ( ( orient & 0x10 ) != 0 )
    {
        xy_orient[ 0 ] = XY_ORIENT_UPSIDE_DOWN;
    }
    else
    {
        xy_orient[ 0 ] = XY_ORIENT_UPRIGHT;
    }
}

float accel6_get_axis ( accel6_t *ctx, uint8_t axis )
{
    int16_t axis_data;
    float f_axis;
    
    axis_data = accel6_read_data( ctx, axis );
    axis_data = axis_data >> 2;
    f_axis = axis_data * ( ctx->device_gaus / 8192.0 ) / 4.0;
    f_axis = f_axis * 1000;
    
    return f_axis;
}

float accel6_get_temperature ( accel6_t *ctx )
{
    int16_t data_temp;
    float f_temp;
    
    data_temp = accel6_read_data( ctx, ACCEL6_REG_TEMPERATURE );
    f_temp = 0.5 * ( float )data_temp + 23.0;

    return f_temp;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void accel6_i2c_write ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel6_i2c_read ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void accel6_spi_write ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void accel6_spi_read ( accel6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select ); 

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt + 1];
    }
}

static void wait_offset ( accel6_t *ctx )
{
   uint8_t read_data = 0;
   
   accel6_generic_read( ctx, ACCEL6_REG_OFC_CTRL, &read_data, 1 );
   
   while ( ! ( read_data & 0x10 ) )
   {
       accel6_generic_read( ctx, ACCEL6_REG_OFC_CTRL, &read_data, 1 );
   }
}

static int16_t accel6_read_data ( accel6_t *ctx, uint8_t reg )
{
    uint8_t read_reg[ 2 ];
    int16_t read_data;
    
    accel6_generic_read( ctx, reg, read_reg, 2 );
    
    read_data = read_reg[ 1 ];
    read_data = read_data << 8;
    read_data = read_data | read_reg[ 0 ];
    
    return read_data;
}

// ------------------------------------------------------------------------- END

