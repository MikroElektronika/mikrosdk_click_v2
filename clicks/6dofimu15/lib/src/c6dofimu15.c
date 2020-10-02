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

#include "c6dofimu15.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C6DOFIMU15_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c6dofimu15_i2c_write ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu15_i2c_read ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu15_spi_write ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu15_spi_read ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c6dofimu15_cfg_setup ( c6dofimu15_cfg_t *cfg )
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
    cfg->i2c_address = C6DOFIMU15_I2C_ADR_GND;
    cfg->sel = C6DOFIMU15_MASTER_I2C;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

C6DOFIMU15_RETVAL c6dofimu15_init ( c6dofimu15_t *ctx, c6dofimu15_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == C6DOFIMU15_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return C6DOFIMU15_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = c6dofimu15_i2c_read;
        ctx->write_f = c6dofimu15_i2c_write;

        digital_out_high( &ctx->cs );
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
        
        spi_cfg.default_write_data = C6DOFIMU15_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;
        

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  C6DOFIMU15_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, C6DOFIMU15_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 

        ctx->read_f = c6dofimu15_spi_read;
        ctx->write_f = c6dofimu15_spi_write;

        digital_out_high( &ctx->cs );
    }

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return C6DOFIMU15_OK;
}

void c6dofimu15_generic_write ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void c6dofimu15_generic_read ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t c6dofimu15_check_int_pin ( c6dofimu15_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

int16_t c6dofimu15_read_gyro_x ( c6dofimu15_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu15_generic_read( ctx, C6DOFIMU15_OUTX_L_G, rx_buf, 2 );

    result = rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 0 ];

    return result;
}

int16_t c6dofimu15_read_gyro_y ( c6dofimu15_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu15_generic_read( ctx, C6DOFIMU15_OUTY_L_G, rx_buf, 2 );

    result = rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 0 ];

    return result;
}
int16_t c6dofimu15_read_gyro_z ( c6dofimu15_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu15_generic_read( ctx, C6DOFIMU15_OUTZ_L_G, rx_buf, 2 );

    result = rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 0 ];

    return result;
}
void c6dofimu15_read_gyroscope ( c6dofimu15_t *ctx, int16_t *gyro_x
                               , int16_t *gyro_y
                               , int16_t *gyro_z )
{
    *gyro_x = c6dofimu15_read_gyro_x( ctx );
    *gyro_y = c6dofimu15_read_gyro_y( ctx );
    *gyro_z = c6dofimu15_read_gyro_z( ctx );
}

void c6dofimu15_angular_rate ( c6dofimu15_t *ctx, float *x_ang_rte
                             , float *y_ang_rte
                             , float *z_ang_rte )
{
    int16_t x_gyro = 0;
    int16_t y_gyro = 0;
    int16_t z_gyro = 0;
    uint8_t fs_sel = 0;

    c6dofimu15_generic_read ( ctx, C6DOFIMU15_CTL2_G, &fs_sel, 1 );
    fs_sel &= 0x0F;

    switch ( fs_sel )
    {
        case C6DOFIMU15_FS_125:
        {
            c6dofimu15_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro * C6DOFIMU15_G_FS_125_DPS;
            *y_ang_rte = y_gyro * C6DOFIMU15_G_FS_125_DPS;
            *z_ang_rte = z_gyro * C6DOFIMU15_G_FS_125_DPS;
            break;
        }
        case C6DOFIMU15_FS_G_250_DPS:
        {
            c6dofimu15_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro * C6DOFIMU15_G_FS_250_DPS;
            *y_ang_rte = y_gyro * C6DOFIMU15_G_FS_250_DPS;
            *z_ang_rte = z_gyro * C6DOFIMU15_G_FS_250_DPS;
            break;
        }
        case C6DOFIMU15_FS_G_500_DPS:
        {
            c6dofimu15_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro * C6DOFIMU15_G_FS_500_DPS;
            *y_ang_rte = y_gyro * C6DOFIMU15_G_FS_500_DPS;
            *z_ang_rte = z_gyro * C6DOFIMU15_G_FS_500_DPS;
            break;
        }
        case C6DOFIMU15_FS_G_1000_DPS:
        {
            c6dofimu15_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro * C6DOFIMU15_G_FS_1000_DPS;
            *y_ang_rte = y_gyro * C6DOFIMU15_G_FS_1000_DPS;
            *z_ang_rte = z_gyro * C6DOFIMU15_G_FS_1000_DPS;
            break;
        }
        case C6DOFIMU15_FS_G_2000_DPS:
        {
            c6dofimu15_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro * C6DOFIMU15_G_FS_2000_DPS;
            *y_ang_rte = y_gyro * C6DOFIMU15_G_FS_2000_DPS;
            *z_ang_rte = z_gyro * C6DOFIMU15_G_FS_2000_DPS;
            break;
        }
        case C6DOFIMU15_FS_4000:
        {
            c6dofimu15_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro * C6DOFIMU15_G_FS_4000_DPS;
            *y_ang_rte = y_gyro * C6DOFIMU15_G_FS_4000_DPS;
            *z_ang_rte = z_gyro * C6DOFIMU15_G_FS_4000_DPS;
            break;
        }
        default :
        {
            c6dofimu15_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro * C6DOFIMU15_G_FS_250_DPS;
            *y_ang_rte = y_gyro * C6DOFIMU15_G_FS_250_DPS;
            *z_ang_rte = z_gyro * C6DOFIMU15_G_FS_250_DPS;
            break;
        }
    }
}

int16_t c6dofimu15_read_accel_x ( c6dofimu15_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu15_generic_read( ctx, C6DOFIMU15_OUTX_L_A, rx_buf, 2 );

    result = rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 0 ];

    return result;
}

int16_t c6dofimu15_read_accel_y ( c6dofimu15_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu15_generic_read( ctx, C6DOFIMU15_OUTY_L_A, rx_buf, 2 );

    result = rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 0 ];

    return result;
}

int16_t c6dofimu15_read_accel_z ( c6dofimu15_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu15_generic_read( ctx, C6DOFIMU15_OUTZ_L_A, rx_buf, 2 );

    result = rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 0 ];

    return result;
}

void c6dofimu15_read_accelerometer ( c6dofimu15_t *ctx, int16_t *accel_x
                                   , int16_t *accel_y
                                   , int16_t *accel_z )
{
    *accel_x = c6dofimu15_read_accel_x( ctx );
    *accel_y = c6dofimu15_read_accel_y( ctx );
    *accel_z = c6dofimu15_read_accel_z( ctx );
}

void c6dofimu15_acceleration_rate ( c6dofimu15_t *ctx, float *x_acel_rte
                                  , float *y_acel_rte
                                  , float *z_acel_rte )
{
    int16_t x_acel = 0;
    int16_t y_acel = 0;
    int16_t z_acel = 0;
    uint8_t fs_sel = 0;

    c6dofimu15_generic_read ( ctx, C6DOFIMU15_CTL1_XL, &fs_sel, 1 );
    fs_sel &= 0x0C;

    switch ( fs_sel )
    {
        case C6DOFIMU15_FS_XL_2_G:
        {
            c6dofimu15_read_accelerometer( ctx, &x_acel, &y_acel, &z_acel );
            *x_acel_rte = (float)x_acel * C6DOFIMU15_LA_FS_2_G;
            *y_acel_rte = (float)y_acel * C6DOFIMU15_LA_FS_2_G;
            *z_acel_rte = (float)z_acel * C6DOFIMU15_LA_FS_2_G;
            break;
        }
        case C6DOFIMU15_FS_XL_4_G:
        {
            c6dofimu15_read_accelerometer( ctx, &x_acel, &y_acel, &z_acel );
            *x_acel_rte = (float)x_acel * C6DOFIMU15_LA_FS_4_G;
            *y_acel_rte = (float)y_acel * C6DOFIMU15_LA_FS_4_G;
            *z_acel_rte = (float)z_acel * C6DOFIMU15_LA_FS_4_G;
            break;
        }
        case C6DOFIMU15_FS_XL_8_G:
        {
            c6dofimu15_read_accelerometer( ctx, &x_acel, &y_acel, &z_acel );
            *x_acel_rte = (float)x_acel * C6DOFIMU15_LA_FS_8_G;
            *y_acel_rte = (float)y_acel * C6DOFIMU15_LA_FS_8_G;
            *z_acel_rte = (float)z_acel * C6DOFIMU15_LA_FS_8_G;
            break;
        }
        case C6DOFIMU15_FS_XL_16_G:
        {
            c6dofimu15_read_accelerometer( ctx, &x_acel, &y_acel, &z_acel );
            *x_acel_rte = (float)x_acel * C6DOFIMU15_LA_FS_16_G;
            *y_acel_rte = (float)y_acel * C6DOFIMU15_LA_FS_16_G;
            *z_acel_rte = (float)z_acel * C6DOFIMU15_LA_FS_16_G;
            break;
        }
        default :
        {
            c6dofimu15_read_accelerometer( ctx, &x_acel, &y_acel, &z_acel );
            *x_acel_rte = (float)x_acel * C6DOFIMU15_LA_FS_2_G;
            *y_acel_rte = (float)y_acel * C6DOFIMU15_LA_FS_2_G;
            *z_acel_rte = (float)z_acel * C6DOFIMU15_LA_FS_2_G;
            break;
        }
    }
}

float c6dofimu15_read_temp_out ( c6dofimu15_t *ctx )
{
    float result;
    int16_t t_dout;
    uint8_t rx_buf[ 2 ];

    c6dofimu15_generic_read( ctx, C6DOFIMU15_OUT_TEMP_L, rx_buf, 2 );

    t_dout = rx_buf[ 1 ];
    t_dout <<= 8;
    t_dout |= rx_buf[ 0 ];

    result = ( (float)t_dout / 256.0 ) + 25.0;

    return result;
}

void c6dofimu15_i2c_disable ( c6dofimu15_t *ctx, uint8_t com_sel )
{
    uint8_t aux_reg_val = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_CTL4_C, &aux_reg_val, 1 );

    if ( com_sel == 0 )
    {
        aux_reg_val &= ~C6DOFIMU15_I2C_DIS;
    }
    else if ( com_sel == 1 )
    {
        aux_reg_val |= C6DOFIMU15_I2C_DIS;
    }

    c6dofimu15_generic_write( ctx, C6DOFIMU15_CTL4_C, &aux_reg_val, 1 );
}

void c6dofimu15_device_conf_set ( c6dofimu15_t *ctx, uint8_t dev_cfg )
{
    uint8_t aux_reg_val = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_CTL9_XL, &aux_reg_val, 1 );

    if ( dev_cfg == 0 )
    {
        aux_reg_val &= ~C6DOFIMU15_DEV_CFG;
    }
    else if ( dev_cfg == 1 )
    {
        aux_reg_val |= C6DOFIMU15_DEV_CFG;
    }

    c6dofimu15_generic_write( ctx, C6DOFIMU15_CTL9_XL, &aux_reg_val, 1 );
}

void c6dofimu15_auto_inc_set ( c6dofimu15_t *ctx, uint8_t inc_set )
{
    uint8_t aux_reg_val = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_CTL3_C, &aux_reg_val, 1 );

    if ( inc_set == 0 )
    {
        aux_reg_val &= ~C6DOFIMU15_IF_INC;
    }
    else if ( inc_set == 1 )
    {
        aux_reg_val |= C6DOFIMU15_IF_INC;
    }

    c6dofimu15_generic_write( ctx, C6DOFIMU15_CTL3_C, &aux_reg_val, 1 );
}

void c6dofimu15_sw_rst ( c6dofimu15_t *ctx, uint8_t rst_en )
{
    uint8_t aux_reg_val = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_CTL3_C, &aux_reg_val, 1 );

    if ( rst_en == 0 )
    {
        aux_reg_val &= ~C6DOFIMU15_SW_RESET;
    }
    else if ( rst_en == 1 )
    {
        aux_reg_val |= C6DOFIMU15_SW_RESET;
    }

    c6dofimu15_generic_write( ctx, C6DOFIMU15_CTL3_C, &aux_reg_val, 1 );
}

void c6dofimu15_block_data_update_set ( c6dofimu15_t *ctx, uint8_t blk_set )
{
    uint8_t aux_reg_val = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_CTL3_C, &aux_reg_val, 1 );

    if ( blk_set == 0 )
    {
        aux_reg_val &= ~C6DOFIMU15_BDU;
    }
    else if ( blk_set == 1 )
    {
        aux_reg_val |= C6DOFIMU15_BDU;
    }

    c6dofimu15_generic_write( ctx, C6DOFIMU15_CTL3_C, &aux_reg_val, 1 );
}

void c6dofimu15_fifo_mode_set ( c6dofimu15_t *ctx, uint8_t fifo_set )
{
    uint8_t aux_reg_val = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_FIFO_CTL4, &aux_reg_val, 1 );

    aux_reg_val &= 0xF0;
    aux_reg_val |= fifo_set;

    c6dofimu15_generic_write( ctx, C6DOFIMU15_FIFO_CTL4, &aux_reg_val, 1 );
}

void c6dofimu15_accel_data_rate ( c6dofimu15_t *ctx, uint8_t data_rate )
{
    uint8_t aux_reg_val = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_CTL1_XL, &aux_reg_val, 1 );

    aux_reg_val &= 0x0E;
    aux_reg_val |= data_rate;

    c6dofimu15_generic_write( ctx, C6DOFIMU15_CTL1_XL, &aux_reg_val, 1 );
}

void c6dofimu15_accel_full_scale ( c6dofimu15_t *ctx, uint8_t fs_sel )
{
    uint8_t aux_reg_val = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_CTL1_XL, &aux_reg_val, 1 );

    aux_reg_val &= 0xF2;
    aux_reg_val |= fs_sel;

    c6dofimu15_generic_write( ctx, C6DOFIMU15_CTL1_XL, &aux_reg_val, 1 );
}

void c6dofimu15_gyro_data_rate ( c6dofimu15_t *ctx, uint8_t data_rate )
{
    uint8_t aux_reg_val = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_CTL2_G, &aux_reg_val, 1 );

    aux_reg_val &= 0x0F;
    aux_reg_val |= data_rate;

    c6dofimu15_generic_write( ctx, C6DOFIMU15_CTL2_G, &aux_reg_val, 1 );
}

void c6dofimu15_gyro_full_scale ( c6dofimu15_t *ctx, uint8_t fs_sel )
{
    uint8_t aux_reg_val = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_CTL2_G, &aux_reg_val, 1 );

    aux_reg_val &= 0xF0;
    aux_reg_val |= fs_sel;

    c6dofimu15_generic_write( ctx, C6DOFIMU15_CTL2_G, &aux_reg_val, 1 );
}

uint8_t c6dofimu15_accel_data_rdy ( c6dofimu15_t *ctx )
{
    uint8_t stat_reg = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_STAT_REG, &stat_reg, 1 );

    if ( stat_reg & C6DOFIMU15_XLDA != 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Gyroscope new data available
uint8_t c6dofimu15_gyro_data_rdy ( c6dofimu15_t *ctx )
{
    uint8_t stat_reg = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_STAT_REG, &stat_reg, 1 );

    if ( stat_reg & C6DOFIMU15_GDA != 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t c6dofimu15_temp_data_rdy ( c6dofimu15_t *ctx )
{
    uint8_t stat_reg = 0;

    c6dofimu15_generic_read( ctx, C6DOFIMU15_STAT_REG, &stat_reg, 1 );

    if ( stat_reg & C6DOFIMU15_TDA != 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Who Am I
uint8_t c6dofimu15_who_im_i ( c6dofimu15_t *ctx )
{
    uint8_t id_val = 0;

    c6dofimu15_generic_read ( ctx, C6DOFIMU15_WHO_AM_I, &id_val, 1 );

    if ( id_val & C6DOFIMU15_WHO_AM_I_VAL != 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c6dofimu15_i2c_write ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
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

static void c6dofimu15_i2c_read ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void c6dofimu15_spi_write ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    uint8_t tx_buf[ 265 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] &= C6DOFIMU15_WR_BIT_MASK;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );     
}

static void c6dofimu15_spi_read ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );  
}

// ------------------------------------------------------------------------- END

