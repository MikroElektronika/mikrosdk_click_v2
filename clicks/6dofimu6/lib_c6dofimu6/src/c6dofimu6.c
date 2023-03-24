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

#include "c6dofimu6.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C6DOFIMU6_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c6dofimu6_i2c_write ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

static void c6dofimu6_i2c_read ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

static void c6dofimu6_spi_write ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

static void c6dofimu6_spi_read ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

static void dev_pin_stabilisation_delay ( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c6dofimu6_cfg_setup ( c6dofimu6_cfg_t *cfg )
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
    cfg->i2c_address = C6DOFIMU6_I2C_SLAVE_ADR_GND;
    
    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->sel = C6DOFIMU6_MASTER_SPI;
}

C6DOFIMU6_RETVAL c6dofimu6_init ( c6dofimu6_t *ctx, c6dofimu6_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;
    
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode   = cfg->spi_mode;
    spi_cfg.speed  = cfg->spi_speed;
    spi_cfg.sck    = cfg->sck;
    spi_cfg.miso   = cfg->miso;
    spi_cfg.mosi   = cfg->mosi;
        
    spi_cfg.default_write_data = C6DOFIMU6_DUMMY;
    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return  C6DOFIMU6_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, C6DOFIMU6_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    ctx->read_f = c6dofimu6_spi_read;
    ctx->write_f = c6dofimu6_spi_write;
    

    if ( ctx->master_sel == C6DOFIMU6_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return C6DOFIMU6_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = c6dofimu6_i2c_read;
        ctx->write_f = c6dofimu6_i2c_write;
    }

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );


    return C6DOFIMU6_OK;
}

void c6dofimu6_default_cfg ( c6dofimu6_t *ctx )
{
    uint8_t tx_buf;

    tx_buf = C6DOFIMU6_PWR_MGMT_1_CLKSEL_1;
    c6dofimu6_generic_write( ctx, C6DOFIMU6_PWR_MGMT_1, &tx_buf, 1 );
    tx_buf = C6DOFIMU6_PWR_MGMT_2_LP_DIS;
    c6dofimu6_generic_write( ctx, C6DOFIMU6_PWR_MGMT_2, &tx_buf, 1 );
    tx_buf = C6DOFIMU6_INT_ENABLE_RAW_RDY_EN;
    c6dofimu6_generic_write( ctx, C6DOFIMU6_INT_ENABLE, &tx_buf, 1 );
    tx_buf = C6DOFIMU6_USER_CTL_DMP_EN | C6DOFIMU6_USER_CTL_SIG_COND_RST;
    c6dofimu6_generic_write( ctx, C6DOFIMU6_USER_CTL, &tx_buf, 1 );
    tx_buf = 0x00;
    c6dofimu6_generic_write( ctx, C6DOFIMU6_FIFO_EN, &tx_buf, 1 );
    tx_buf = 0x00;
    c6dofimu6_generic_write( ctx, C6DOFIMU6_CFG, &tx_buf, 1 );
    tx_buf = C6DOFIMU6_GYRO_CFG_FS_SEL_2000;
    c6dofimu6_generic_write( ctx, C6DOFIMU6_GYRO_CFG, &tx_buf, 1 );
    tx_buf = C6DOFIMU6_ACCEL_CFG_FS_SEL_4G;
    c6dofimu6_generic_write( ctx, C6DOFIMU6_ACCEL_CFG, &tx_buf, 1 );
    tx_buf = C6DOFIMU6_ACCEL2_CFG_DEC2_CFG_4;
    c6dofimu6_generic_write( ctx, C6DOFIMU6_ACCEL_CFG_2, &tx_buf, 1 );
}

void c6dofimu6_generic_write ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void c6dofimu6_generic_read ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

// Power up function
void c6dofimu6_power ( c6dofimu6_t *ctx, uint8_t on_off )
{
    uint8_t pwr_mgmt_1 = 0;

    if ( on_off == C6DOFIMU6_POWER_ON )
        {
        c6dofimu6_generic_read( ctx, C6DOFIMU6_PWR_MGMT_1, &pwr_mgmt_1, 1 );
        pwr_mgmt_1 &= ~C6DOFIMU6_PWR_MGMT_1_SLEEP;
        c6dofimu6_generic_write( ctx, C6DOFIMU6_PWR_MGMT_1, &pwr_mgmt_1, 1 );
        dev_pin_stabilisation_delay ( );
    }
    else
    {
        c6dofimu6_generic_read( ctx, C6DOFIMU6_PWR_MGMT_1, &pwr_mgmt_1, 1 );
        pwr_mgmt_1 |= C6DOFIMU6_PWR_MGMT_1_SLEEP;
        c6dofimu6_generic_write( ctx, C6DOFIMU6_PWR_MGMT_1, &pwr_mgmt_1, 1 );
        dev_pin_stabilisation_delay ( );
    }
}

// Read Gyroscope X-axis data
int16_t c6dofimu6_read_gyro_x ( c6dofimu6_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu6_generic_read( ctx, C6DOFIMU6_GYRO_XOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

// Read Gyroscope Y-axis data
int16_t c6dofimu6_read_gyro_y ( c6dofimu6_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu6_generic_read( ctx, C6DOFIMU6_GYRO_YOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

// Read Gyroscope Z-axis data
int16_t c6dofimu6_read_gyro_z ( c6dofimu6_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu6_generic_read( ctx, C6DOFIMU6_GYRO_ZOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

// Read gyroscope data
void c6dofimu6_read_gyroscope ( c6dofimu6_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z )
{
    *gyro_x = c6dofimu6_read_gyro_x( ctx );
    *gyro_y = c6dofimu6_read_gyro_y( ctx );
    *gyro_z = c6dofimu6_read_gyro_z( ctx );
}

// Read Angular Rate
void c6dofimu6_angular_rate ( c6dofimu6_t *ctx, float *x_ang_rte, float *y_ang_rte, float *z_ang_rte )
{
    int16_t x_gyro = 0;
    int16_t y_gyro = 0;
    int16_t z_gyro = 0;
    uint8_t fs_sel = 0;

    c6dofimu6_generic_read ( ctx, C6DOFIMU6_GYRO_CFG, &fs_sel, 1 );
    fs_sel &= 0x18;

    switch ( fs_sel )
    {
        case C6DOFIMU6_GYRO_CFG_FS_SEL_250:
        {
            c6dofimu6_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = ( float ) x_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_250;
            *y_ang_rte = ( float ) y_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_250;
            *z_ang_rte = ( float ) z_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_250;
            break;
        }
        case C6DOFIMU6_GYRO_CFG_FS_SEL_500:
        {
            c6dofimu6_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = ( float ) x_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_500;
            *y_ang_rte = ( float ) y_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_500;
            *z_ang_rte = ( float ) z_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_500;
            break;
        }
        case C6DOFIMU6_GYRO_CFG_FS_SEL_1000:
        {
            c6dofimu6_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = ( float ) x_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_1000;
            *y_ang_rte = ( float ) y_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_1000;
            *z_ang_rte = ( float ) z_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_1000;
            break;
        }
        case C6DOFIMU6_GYRO_CFG_FS_SEL_2000:
        {
            c6dofimu6_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = ( float ) x_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_2000;
            *y_ang_rte = ( float ) y_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_2000;
            *z_ang_rte = ( float ) z_gyro / C6DOFIMU6_GYRO_SENS_FS_SEL_2000;
            break;
        }
        default :
        {
            break;
        }
    }
}

// Read Accelerometer X-axis data
int16_t c6dofimu6_read_accel_x ( c6dofimu6_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu6_generic_read( ctx, C6DOFIMU6_ACCEL_XOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

// Read Accelerometer Y-axis data
int16_t c6dofimu6_read_accel_y( c6dofimu6_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu6_generic_read( ctx, C6DOFIMU6_ACCEL_YOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

// Read Accelerometer Z-axis data
int16_t c6dofimu6_read_accel_z( c6dofimu6_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu6_generic_read( ctx, C6DOFIMU6_ACCEL_ZOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

// Read Accelerometer Data
void c6dofimu6_read_accelerometer ( c6dofimu6_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z )
{
    *accel_x = c6dofimu6_read_accel_x( ctx );
    *accel_y = c6dofimu6_read_accel_y( ctx );
    *accel_z = c6dofimu6_read_accel_z( ctx );
}

// Read acceleration Rate
void c6dofimu6_acceleration_rate ( c6dofimu6_t *ctx, float *x_accel_rte, float *y_accel_rte, float *z_accel_rte )
{
    int16_t x_accel = 0;
    int16_t y_accel = 0;
    int16_t z_accel = 0;
    uint8_t fs_sel = 0;

    c6dofimu6_generic_read ( ctx, C6DOFIMU6_ACCEL_CFG, &fs_sel, 1 );
    fs_sel &= 0x18;

    switch ( fs_sel )
    {
        case C6DOFIMU6_ACCEL_CFG_FS_SEL_2G:
        {
            c6dofimu6_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = ( float )x_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_2G;
            *y_accel_rte = ( float )y_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_2G;
            *z_accel_rte = ( float )z_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_2G;
            break;
        }
        case C6DOFIMU6_ACCEL_CFG_FS_SEL_4G:
        {
            c6dofimu6_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = ( float )x_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_4G;
            *y_accel_rte = ( float )y_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_4G;
            *z_accel_rte = ( float )z_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_4G;
            break;
        }
        case C6DOFIMU6_ACCEL_CFG_FS_SEL_8G:
        {
            c6dofimu6_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = ( float )x_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_8G;
            *y_accel_rte = ( float )y_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_8G;
            *z_accel_rte = ( float )z_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_8G;
            break;
        }
        case C6DOFIMU6_ACCEL_CFG_FS_SEL_16G:
        {
            c6dofimu6_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = ( float )x_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_16G;
            *y_accel_rte = ( float )y_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_16G;
            *z_accel_rte = ( float )z_accel / C6DOFIMU6_ACCEL_SENS_FS_SEL_16G;
            break;
        }
        default :
        {
            break;
        }
    }
}

// Read temperature
float c6dofimu6_read_temp_out ( c6dofimu6_t *ctx )
{
    float result;
    int16_t t_dout;
    uint8_t rx_buf[ 2 ];

    c6dofimu6_generic_read( ctx, C6DOFIMU6_TEMP_OUT_H, rx_buf, 2 );

    t_dout = rx_buf[ 0 ];
    t_dout <<= 8;
    t_dout |= rx_buf[ 1 ];

    result =  ( float )t_dout / 100.0;

    return result;
}

uint8_t c6dofimu6_check_int_pin ( c6dofimu6_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c6dofimu6_i2c_write ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    uint8_t tx_buf[ 512 ];
    uint16_t cnt;
    
    tx_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }

    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

static void c6dofimu6_i2c_read ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void c6dofimu6_spi_write ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    uint8_t tx_buf[ 512 ];
    uint16_t cnt;

    tx_buf[ 0 ] = reg; 
    tx_buf[ 0 ] &= C6DOFIMU6_WRITE_BIT_MASK;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );     
}

static void c6dofimu6_spi_read ( c6dofimu6_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg; 
    tx_buf[ 0 ] |= C6DOFIMU6_READ_BIT_MASK;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );  
}

static void dev_pin_stabilisation_delay ( )
{
    Delay_50us( );
    Delay_50us( );
}

// ------------------------------------------------------------------------- END

