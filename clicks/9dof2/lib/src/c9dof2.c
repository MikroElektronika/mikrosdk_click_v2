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

#include "c9dof2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C9DOF2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_pin_stabilisation_delay ( );

static void dev_comunication_delay ( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c9dof2_cfg_setup ( c9dof2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->snc = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

C9DOF2_RETVAL c9dof2_init ( c9dof2_t *ctx, c9dof2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = C9DOF2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return C9DOF2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, C9DOF2_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->snc, cfg->snc );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    spi_master_deselect_device( ctx->chip_select );
    digital_out_low( &ctx->snc );

    return C9DOF2_OK;

}

void c9dof2_generic_transfer 
( 
    c9dof2_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void c9dof2_write_byte ( c9dof2_t *ctx, uint8_t reg, uint8_t wr_data )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 4 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] &= C9DOF2_WRITE_BIT_MASK;
    tx_buf[ 1 ] = wr_data;

    c9dof2_generic_transfer( ctx, tx_buf, 2, 0, 0 );
}

void c9dof2_write_data ( c9dof2_t *ctx, uint8_t reg, int16_t wr_data )
{
    uint8_t msb_buf;
    uint8_t lsb_buf;

    msb_buf = (uint8_t)( wr_data >> 8 );
    lsb_buf = (uint8_t)( wr_data & 0xFF );
    
    c9dof2_write_byte( ctx, reg, msb_buf );
    c9dof2_write_byte( ctx, reg + 1, lsb_buf );


}

uint8_t c9dof2_read_byte ( c9dof2_t *ctx, uint8_t reg )
{
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= C9DOF2_READ_BIT_MASK;

    c9dof2_generic_transfer( ctx, &tx_buf, 1, rx_buf, 1 );

    return rx_buf[ 0 ];
}

int16_t c9dof2_read_data ( c9dof2_t *ctx, uint8_t reg )
{
    uint8_t msb_buf;
    uint8_t lsb_buf;
    int16_t result;

    msb_buf = c9dof2_read_byte( ctx, reg );
    lsb_buf = c9dof2_read_byte( ctx, reg + 1 );
   
    result = msb_buf;
    result <<= 8;
    result |= lsb_buf;

    return result;
}

void c9dof2_dev_rst ( c9dof2_t *ctx )
{
    uint8_t tx_buf;

    tx_buf = C9DOF2_REG_BANK_0;
    c9dof2_write_byte( ctx, C9DOF2_REG_BANK_SEL, tx_buf );

    tx_buf = C9DOF2_PWR_MGMT_1_DEV_RST;
    c9dof2_write_byte( ctx, C9DOF2_PWR_MGMT_1, tx_buf );
}

void c9dof2_power ( c9dof2_t *ctx, uint8_t on_off )
{
    uint8_t pwr_mgmt_1 = 0;
    uint8_t tx_buf;
    
    tx_buf = C9DOF2_REG_BANK_0;
    c9dof2_write_byte( ctx, C9DOF2_REG_BANK_SEL, tx_buf );

    if ( on_off == C9DOF2_POWER_ON )
    {
        pwr_mgmt_1 = c9dof2_read_byte( ctx, C9DOF2_PWR_MGMT_1 );
        pwr_mgmt_1 &= ~( C9DOF2_PWR_MGMT_1_SLP );
        c9dof2_write_byte( ctx, C9DOF2_PWR_MGMT_1, pwr_mgmt_1 );
        dev_pin_stabilisation_delay( );
    }
    else
    {
        pwr_mgmt_1 = c9dof2_read_byte( ctx, C9DOF2_PWR_MGMT_1 );
        pwr_mgmt_1 |= C9DOF2_PWR_MGMT_1_SLP;
        c9dof2_write_byte( ctx, C9DOF2_PWR_MGMT_1, pwr_mgmt_1 );
        dev_pin_stabilisation_delay( );
    }
}

void c9dof2_def_settings ( c9dof2_t *ctx )
{
    uint8_t tx_buf;

    tx_buf = C9DOF2_PWR_MGMT_1_CLKSEL_1;
    c9dof2_write_byte( ctx, C9DOF2_PWR_MGMT_1, C9DOF2_PWR_MGMT_1_CLKSEL_1 );

    tx_buf = C9DOF2_USER_CTL_DMP_EN | C9DOF2_USER_CTL_I2C_IF_DIS;
    dev_comunication_delay( );
    c9dof2_write_byte( ctx, C9DOF2_USER_CTRL, tx_buf );

    tx_buf = C9DOF2_GYRO_CFG_1_FS_SEL_2000;
    dev_comunication_delay( );
    c9dof2_write_byte( ctx, C9DOF2_GYRO_CFG_1, tx_buf );
    tx_buf = C9DOF2_ACCEL_CFG_FS_SEL_4G;
    dev_comunication_delay( );
    c9dof2_write_byte( ctx, C9DOF2_ACCEL_CFG, tx_buf );
}

void c9dof2_read_gyroscope ( c9dof2_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z )
{
    *gyro_x = c9dof2_read_data( ctx, C9DOF2_GYRO_XOUT_H );
    *gyro_y = c9dof2_read_data( ctx, C9DOF2_GYRO_YOUT_H );
    *gyro_z = c9dof2_read_data( ctx, C9DOF2_GYRO_ZOUT_H );
}

void c9dof2_angular_rate ( c9dof2_t *ctx, float *x_ang_rte, float *y_ang_rte, float *z_ang_rte )
{
    int16_t x_gyro = 0;
    int16_t y_gyro = 0;
    int16_t z_gyro = 0;
    uint8_t fs_sel = 0;

    fs_sel = c9dof2_read_byte( ctx, C9DOF2_GYRO_CFG_1 );
    fs_sel &= 0x18;

    switch ( fs_sel )
    {
        case C9DOF2_GYRO_CFG_1_FS_SEL_250:
        {
            c9dof2_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro / C9DOF2_GYRO_SENS_FS_SEL_250;
            *y_ang_rte = y_gyro / C9DOF2_GYRO_SENS_FS_SEL_250;
            *z_ang_rte = z_gyro / C9DOF2_GYRO_SENS_FS_SEL_250;
            break;
        }
        case C9DOF2_GYRO_CFG_1_FS_SEL_500:
        {
            c9dof2_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro / C9DOF2_GYRO_SENS_FS_SEL_500;
            *y_ang_rte = y_gyro / C9DOF2_GYRO_SENS_FS_SEL_500;
            *z_ang_rte = z_gyro / C9DOF2_GYRO_SENS_FS_SEL_500;
            break;
        }
        case C9DOF2_GYRO_CFG_1_FS_SEL_1000:
        {
            c9dof2_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro / C9DOF2_GYRO_SENS_FS_SEL_1000;
            *y_ang_rte = y_gyro / C9DOF2_GYRO_SENS_FS_SEL_1000;
            *z_ang_rte = z_gyro / C9DOF2_GYRO_SENS_FS_SEL_1000;
            break;
        }
        case C9DOF2_GYRO_CFG_1_FS_SEL_2000:
        {
            c9dof2_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro / C9DOF2_GYRO_SENS_FS_SEL_2000;
            *y_ang_rte = y_gyro / C9DOF2_GYRO_SENS_FS_SEL_2000;
            *z_ang_rte = z_gyro / C9DOF2_GYRO_SENS_FS_SEL_2000;
            break;
        }
        default :
        {
            break;
        }
    }
}

void c9dof2_read_accelerometer ( c9dof2_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z )
{
    *accel_x = c9dof2_read_data( ctx, C9DOF2_ACCEL_XOUT_H );
    *accel_y = c9dof2_read_data( ctx, C9DOF2_ACCEL_YOUT_H );
    *accel_z = c9dof2_read_data( ctx, C9DOF2_ACCEL_ZOUT_H );
}

void c9dof2_acceleration_rate ( c9dof2_t *ctx, float *x_accel_rte, float *y_accel_rte, float *z_accel_rte )
{
    int16_t x_accel = 0;
    int16_t y_accel = 0;
    int16_t z_accel = 0;
    uint8_t fs_sel = 0;

    fs_sel = c9dof2_read_byte ( ctx, C9DOF2_ACCEL_CFG );
    fs_sel &= 0x18;

    switch ( fs_sel )
    {
        case C9DOF2_ACCEL_CFG_FS_SEL_2G:
        {
            c9dof2_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = ( float )x_accel / C9DOF2_ACCEL_SENS_FS_SEL_2G;
            *y_accel_rte = ( float )y_accel / C9DOF2_ACCEL_SENS_FS_SEL_2G;
            *z_accel_rte = ( float )z_accel / C9DOF2_ACCEL_SENS_FS_SEL_2G;
            break;
        }
        case C9DOF2_ACCEL_CFG_FS_SEL_4G:
        {
            c9dof2_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = ( float )x_accel / C9DOF2_ACCEL_SENS_FS_SEL_4G;
            *y_accel_rte = ( float )y_accel / C9DOF2_ACCEL_SENS_FS_SEL_4G;
            *z_accel_rte = ( float )z_accel / C9DOF2_ACCEL_SENS_FS_SEL_4G;
            break;
        }
        case C9DOF2_ACCEL_CFG_FS_SEL_8G:
        {
            c9dof2_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = ( float )x_accel / C9DOF2_ACCEL_SENS_FS_SEL_8G;
            *y_accel_rte = ( float )y_accel / C9DOF2_ACCEL_SENS_FS_SEL_8G;
            *z_accel_rte = ( float )z_accel / C9DOF2_ACCEL_SENS_FS_SEL_8G;
            break;
        }
        case C9DOF2_ACCEL_CFG_FS_SEL_16G:
        {
            c9dof2_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = ( float )x_accel / C9DOF2_ACCEL_SENS_FS_SEL_16G;
            *y_accel_rte = ( float )y_accel / C9DOF2_ACCEL_SENS_FS_SEL_16G;
            *z_accel_rte = ( float )z_accel / C9DOF2_ACCEL_SENS_FS_SEL_16G;
            break; 
        }
        default :
        {
            break;
        }
    }
}

float c9dof2_read_temperature ( c9dof2_t *ctx, float temp_offs )
{
    float result;
    int16_t t_dout;
    
    t_dout = c9dof2_read_data( ctx, C9DOF2_TEMP_OUT_H );

    result = ( float )t_dout - temp_offs;
    result /= 333.87;
    result += 21.0;

    return result;
}

uint8_t c9dof2_check_int ( c9dof2_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->int_pin );

    return state;
}

void c9dof2_snc_pin ( c9dof2_t *ctx, uint8_t state )
{
    if ( state == C9DOF2_SNC_HIGH )
    {
        digital_out_write( &ctx->snc, C9DOF2_SNC_HIGH );
    }
    else if ( state == C9DOF2_SNC_LOW )
    {
        digital_out_write( &ctx->snc, C9DOF2_SNC_LOW );
    }
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_pin_stabilisation_delay ( )
{
    Delay_50us( );
    Delay_50us( );
}

static void dev_comunication_delay ( )
{
    Delay_22us( );
}

// ------------------------------------------------------------------------- END

