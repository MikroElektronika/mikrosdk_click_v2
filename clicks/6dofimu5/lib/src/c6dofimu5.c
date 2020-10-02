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

#include "c6dofimu5.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C6DOFIMU5_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c6dofimu5_i2c_write ( c6dofimu5_t *ctx, uint8_t *data_buf, uint16_t len );

static void c6dofimu5_i2c_read ( c6dofimu5_t *ctx, uint8_t *reg_buf, uint8_t *data_buf, uint16_t len );

static void c6dofimu5_spi_write ( c6dofimu5_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

static void c6dofimu5_spi_read ( c6dofimu5_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len );

static void c6dofimu5_i2c_aux_read ( c6dofimu5_t *ctx, uint8_t *data_buf, uint16_t len );

static void dev_pin_stabilisation_delay ( );

static void dev_read_otp_from_i2c ( c6dofimu5_t *ctx, uint8_t *output );

static void dev_init_base ( c6dofimu5_t *ctx, uint8_t *otp );

static void dev_calc_init ( c6dofimu5_t *ctx );

static void dev_calc_conv_const ( c6dofimu5_t *ctx, float *p_lut, float *output );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c6dofimu5_cfg_setup ( c6dofimu5_cfg_t *cfg )
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
    cfg->i2c_address = C6DOFIMU5_I2C_SLAVE_ADR;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

C6DOFIMU5_RETVAL c6dofimu5_init ( c6dofimu5_t *ctx, c6dofimu5_cfg_t *cfg )
{
        i2c_master_config_t i2c_cfg;
        spi_master_config_t spi_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl      = cfg->scl;
        i2c_cfg.sda      = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return C6DOFIMU5_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        spi_master_configure_default( &spi_cfg );
        spi_cfg.mode   = cfg->spi_mode;
        spi_cfg.speed  = cfg->spi_speed;
        spi_cfg.sck    = cfg->sck;
        spi_cfg.miso   = cfg->miso;
        spi_cfg.mosi   = cfg->mosi;
        
        spi_cfg.default_write_data = C6DOFIMU5_DUMMY;
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  C6DOFIMU5_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, C6DOFIMU5_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return C6DOFIMU5_OK;
}

void c6dofimu5_default_cfg ( c6dofimu5_t *ctx )
{
    uint8_t tx_buf;
    
    tx_buf = C6DOFIMU5_PWR_MGMT_1_CLKSEL_1;
    c6dofimu5_write_bytes( ctx, C6DOFIMU5_PWR_MGMT_1, &tx_buf, 1 );
    tx_buf = C6DOFIMU5_PWR_MGMT_2_LP_DIS;
    c6dofimu5_write_bytes( ctx, C6DOFIMU5_PWR_MGMT_2, &tx_buf, 1 );
    tx_buf = C6DOFIMU5_INT_ENABLE_RAW_RDY_EN;
    c6dofimu5_write_bytes( ctx, C6DOFIMU5_INT_ENABLE, &tx_buf, 1 );
    tx_buf = C6DOFIMU5_USER_CTL_DMP_EN | C6DOFIMU5_USER_CTL_SIG_COND_RST;
    c6dofimu5_write_bytes( ctx, C6DOFIMU5_USER_CTL, &tx_buf, 1 );
    tx_buf = 0x00;
    c6dofimu5_write_bytes( ctx, C6DOFIMU5_FIFO_EN, &tx_buf, 1 );
    tx_buf = 0x00;
    c6dofimu5_write_bytes( ctx, C6DOFIMU5_CFG, &tx_buf, 1 );
    tx_buf = C6DOFIMU5_GYRO_CFG_FS_SEL_2000;
    c6dofimu5_write_bytes( ctx, C6DOFIMU5_GYRO_CFG, &tx_buf, 1 );
    tx_buf = C6DOFIMU5_ACCEL_CFG_FS_SEL_4G;
    c6dofimu5_write_bytes( ctx, C6DOFIMU5_ACCEL_CFG, &tx_buf, 1 );
    tx_buf = C6DOFIMU5_ACCEL2_CFG_DEC2_CFG_4;
    c6dofimu5_write_bytes( ctx, C6DOFIMU5_ACCEL_CFG_2, &tx_buf, 1 );
}

void c6dofimu5_write_bytes ( c6dofimu5_t *ctx, uint8_t reg, uint8_t *wr_data, uint16_t n_bytes )
{
    uint8_t reg_data;

    reg_data = reg;
    reg_data &= C6DOFIMU5_WRITE_BIT_MASK;

    c6dofimu5_spi_write( ctx, reg_data, wr_data, n_bytes );
}

void c6dofimu5_read_bytes ( c6dofimu5_t *ctx, uint8_t reg, uint8_t *rd_data, uint16_t n_bytes )
{
    uint8_t reg_data;

    reg_data = reg;
    reg_data |= C6DOFIMU5_READ_BIT_MASK;
    
    c6dofimu5_spi_read( ctx, reg_data, rd_data, n_bytes );
}

void c6dofimu5_power ( c6dofimu5_t *ctx, uint8_t on_off )
{
    uint8_t pwr_mgmt_1 = 0;

    if ( on_off == C6DOFIMU5_POWER_ON )
        {
        c6dofimu5_read_bytes ( ctx, C6DOFIMU5_PWR_MGMT_1, &pwr_mgmt_1, 1 );
        pwr_mgmt_1 &= ~C6DOFIMU5_PWR_MGMT_1_SLEEP;
        c6dofimu5_write_bytes ( ctx, C6DOFIMU5_PWR_MGMT_1, &pwr_mgmt_1, 1 );
        dev_pin_stabilisation_delay ( );
    }
    else
    {
        c6dofimu5_read_bytes ( ctx, C6DOFIMU5_PWR_MGMT_1, &pwr_mgmt_1, 1 );
        pwr_mgmt_1 |= C6DOFIMU5_PWR_MGMT_1_SLEEP;
        c6dofimu5_write_bytes ( ctx, C6DOFIMU5_PWR_MGMT_1, &pwr_mgmt_1, 1 );
        dev_pin_stabilisation_delay ( );
    }
}

int16_t c6dofimu5_read_gyro_x ( c6dofimu5_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu5_read_bytes( ctx, C6DOFIMU5_GYRO_XOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

int16_t c6dofimu5_read_gyro_y ( c6dofimu5_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu5_read_bytes( ctx, C6DOFIMU5_GYRO_YOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

int16_t c6dofimu5_read_gyro_z ( c6dofimu5_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu5_read_bytes( ctx, C6DOFIMU5_GYRO_ZOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

void c6dofimu5_read_gyroscope ( c6dofimu5_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z )
{
    *gyro_x = c6dofimu5_read_gyro_x( ctx );
    *gyro_y = c6dofimu5_read_gyro_y( ctx );
    *gyro_z = c6dofimu5_read_gyro_z( ctx );
}

void c6dofimu5_angular_rate ( c6dofimu5_t *ctx, float *x_ang_rte, float *y_ang_rte, float *z_ang_rte )
{
    int16_t x_gyro = 0;
    int16_t y_gyro = 0;
    int16_t z_gyro = 0;
    uint8_t fs_sel = 0;
    
    c6dofimu5_read_bytes ( ctx, C6DOFIMU5_GYRO_CFG, &fs_sel, 1 );
    fs_sel &= 0x18;
    
    switch ( fs_sel )
    {
        case C6DOFIMU5_GYRO_CFG_FS_SEL_250:
        {
            c6dofimu5_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_250;
            *y_ang_rte = y_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_250;
            *z_ang_rte = z_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_250;
            break;
        }
        case C6DOFIMU5_GYRO_CFG_FS_SEL_500:
        {
            c6dofimu5_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_500;
            *y_ang_rte = y_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_500;
            *z_ang_rte = z_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_500;
            break;
        }
        case C6DOFIMU5_GYRO_CFG_FS_SEL_1000:
        {
            c6dofimu5_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_1000;
            *y_ang_rte = y_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_1000;
            *z_ang_rte = z_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_1000;
            break;
        }
        case C6DOFIMU5_GYRO_CFG_FS_SEL_2000:
        {
            c6dofimu5_read_gyroscope( ctx, &x_gyro, &y_gyro, &z_gyro );
            *x_ang_rte = x_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_2000;
            *y_ang_rte = y_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_2000;
            *z_ang_rte = z_gyro / C6DOFIMU5_GYRO_SENS_FS_SEL_2000;
            break;
        }
        default :
        {
            break;
        }
    }
}

int16_t c6dofimu5_read_accel_x ( c6dofimu5_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu5_read_bytes( ctx, C6DOFIMU5_ACCEL_XOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

int16_t c6dofimu5_read_accel_y ( c6dofimu5_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu5_read_bytes( ctx, C6DOFIMU5_ACCEL_YOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

int16_t c6dofimu5_read_accel_z ( c6dofimu5_t *ctx )
{
    int16_t result;
    uint8_t rx_buf[ 2 ];

    c6dofimu5_read_bytes( ctx, C6DOFIMU5_ACCEL_ZOUT_H, rx_buf, 2 );

    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];

    return result;
}

void c6dofimu5_read_accelerometer ( c6dofimu5_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z )
{
    *accel_x = c6dofimu5_read_accel_x( ctx );
    *accel_y = c6dofimu5_read_accel_y( ctx );
    *accel_z = c6dofimu5_read_accel_z( ctx );
}

void c6dofimu5_acceleration_rate ( c6dofimu5_t *ctx, float *x_accel_rte, float *y_accel_rte, float *z_accel_rte )
{
    int16_t x_accel = 0;
    int16_t y_accel = 0;
    int16_t z_accel = 0;
    uint8_t fs_sel = 0;
    
    c6dofimu5_read_bytes ( ctx, C6DOFIMU5_ACCEL_CFG, &fs_sel, 1 );
    fs_sel &= 0x18;
    
    switch ( fs_sel )
    {
        case C6DOFIMU5_ACCEL_CFG_FS_SEL_2G:
        {
            c6dofimu5_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = (float)x_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_2G;
            *y_accel_rte = (float)y_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_2G;
            *z_accel_rte = (float)z_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_2G;
            break;
        }
        case C6DOFIMU5_ACCEL_CFG_FS_SEL_4G:
        {
            c6dofimu5_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = (float)x_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_4G;
            *y_accel_rte = (float)y_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_4G;
            *z_accel_rte = (float)z_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_4G;
            break;
        }
        case C6DOFIMU5_ACCEL_CFG_FS_SEL_8G:
        {
            c6dofimu5_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = (float)x_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_8G;
            *y_accel_rte = (float)y_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_8G;
            *z_accel_rte = (float)z_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_8G;
            break;
        }
        case C6DOFIMU5_ACCEL_CFG_FS_SEL_16G:
        {
            c6dofimu5_read_accelerometer( ctx, &x_accel, &y_accel, &z_accel );
            *x_accel_rte = (float)x_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_16G;
            *y_accel_rte = (float)y_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_16G;
            *z_accel_rte = (float)z_accel / C6DOFIMU5_ACCEL_SENS_FS_SEL_16G;
            break;
        }
        default :
        {
            break;
        }
    }
}

float c6dofimu5_read_temp_out ( c6dofimu5_t *ctx )
{
    float result;
    int16_t t_dout;
    uint8_t rx_buf[ 2 ];

    c6dofimu5_read_bytes( ctx, C6DOFIMU5_TEMP_OUT_H, rx_buf, 2 );
    
    t_dout = rx_buf[ 0 ];
    t_dout <<= 8;
    t_dout |= rx_buf[ 1 ];

    result =  (float)t_dout / 100.0;

    return result;
}

void c6dofimu5_baro_read ( c6dofimu5_t *ctx, uint16_t cmd, uint8_t *data_out, uint16_t n_bytes )
{
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = ( uint8_t ) ( cmd >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) cmd;

    c6dofimu5_i2c_read( ctx, tx_buf, data_out, n_bytes );
}

void c6dofimu5_baro_write ( c6dofimu5_t *ctx, uint8_t *data_in, uint16_t n_bytes )
{
    c6dofimu5_i2c_write( ctx, data_in, n_bytes );
}

void c6dofimu5_baro_settings ( c6dofimu5_t *ctx )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = 0x01;
    c6dofimu5_write_bytes( ctx, C6DOFIMU5_INT_PIN_CFG, tx_buf, 1 );
    tx_buf[ 0 ] = 0x00;
    c6dofimu5_write_bytes( ctx, C6DOFIMU5_USER_CTL, tx_buf, 1 );
}

uint8_t c6dofimu5_baro_id_read ( c6dofimu5_t *ctx )
{
    uint8_t result;
    uint8_t rx_buf [ 2 ];
    
    c6dofimu5_baro_read ( ctx, C6DOFIMU5_READ_ID_REGISTER, rx_buf, 2 );
    
    result = rx_buf[ 1 ];
    result &= 0x3F;
    
    return result;
}

void c6dofimu5_baro_soft_rst ( c6dofimu5_t *ctx )
{
    uint8_t tx_buf [ 2 ];
    uint16_t rst_cmd;

    rst_cmd = C6DOFIMU5_DEVICE_SOFT_RESET_CMD;

    tx_buf[ 0 ] = ( uint8_t ) ( rst_cmd >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) rst_cmd;

    c6dofimu5_i2c_write( ctx, tx_buf, 2 ); 
}

void c6dofimu5_process_data ( c6dofimu5_t *ctx, c6dofimu5_process_data_t *process_data )
{
    float coef_t;
    float s1_coef;
    float s2_coef;
    float s3_coef;
    float input[ 3 ];
    float output[ 3 ];
    float coef_a;
    float coef_b;
    float coef_c;

    coef_t = ( float )( process_data->t_raw - 32768 );
    
    s1_coef = C6DOFIMU5_LUT_LOWER + ( float )( ctx->sens_const_0 * coef_t * coef_t ) 
            * C6DOFIMU5_QUADR_FACTOR;

    s2_coef = C6DOFIMU5_OFFST_FACTOR * ctx->sens_const_3 + ( float )( ctx->sens_const_1 * coef_t 
            * coef_t ) * C6DOFIMU5_QUADR_FACTOR;

    s3_coef = C6DOFIMU5_LUT_UPPER + ( float )( ctx->sens_const_2 * coef_t * coef_t )
            * C6DOFIMU5_QUADR_FACTOR;

    input[ 0 ] = s1_coef;
    input[ 1 ] = s2_coef;
    input[ 2 ] = s3_coef;
    
    dev_calc_conv_const( ctx, input, &output );
    
    coef_a = output[ 0 ];
    coef_b = output[ 1 ];
    coef_c = output[ 2 ];

    process_data->pressure = coef_a + coef_b / ( coef_c + ( float )process_data->p_raw );
    process_data->temperature = ( -45.0 ) + ( ( 175.0 / 65536.0 ) * process_data->t_raw );
}

void c6dofimu5_read_raw_data ( c6dofimu5_t *ctx, uint32_t *pres, uint16_t *temp )
{
    uint32_t p_raw = 0;
    uint16_t t_raw = 0;
    uint8_t rx_buf[ 10 ];
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = 0x50;
    tx_buf[ 1 ] = 0x59;
    c6dofimu5_i2c_write( ctx, tx_buf, 2 );
    Delay_100ms(  );
    c6dofimu5_i2c_aux_read( ctx, rx_buf , 9 );

    p_raw = rx_buf[ 0 ];
    p_raw <<= 8;
    p_raw |= rx_buf[ 1 ];
    p_raw <<= 8;
    p_raw |= rx_buf[ 3 ];
    p_raw <<= 8;
    p_raw |= rx_buf[ 4 ];
    *pres = p_raw;

    t_raw = rx_buf[ 6 ];
    t_raw <<= 8;
    t_raw |= rx_buf[ 7 ];
    *temp = t_raw;
}

uint8_t c6dofimu5_check_int_pin ( c6dofimu5_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c6dofimu5_i2c_write ( c6dofimu5_t *ctx, uint8_t *data_buf, uint16_t len )
{
    i2c_master_write( &ctx->i2c, data_buf, len );       
}

static void c6dofimu5_i2c_read ( c6dofimu5_t *ctx, uint8_t *reg_buff, uint8_t *data_buf, uint16_t len )
{
    i2c_master_write_then_read( &ctx->i2c, reg_buff, 2, data_buf, len );
}

static void c6dofimu5_spi_write ( c6dofimu5_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
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

static void c6dofimu5_spi_read ( c6dofimu5_t *ctx, uint8_t reg, uint8_t *data_buf, uint16_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select );  
}

static void c6dofimu5_i2c_aux_read ( c6dofimu5_t *ctx, uint8_t *data_buf, uint16_t len )
{  
    i2c_master_read( &ctx->i2c, data_buf, len );
}

static void dev_pin_stabilisation_delay ( )
{
    Delay_50us( );
    Delay_50us( );
}

static void dev_read_otp_from_i2c ( c6dofimu5_t *ctx, uint8_t *output )
{
    uint8_t tx_buf[ 10 ];
    uint8_t rx_buf[ 10 ] = { 0 };
    uint8_t i;

    tx_buf[ 0 ] = 0xC5;
    tx_buf[ 1 ] = 0x95;
    tx_buf[ 2 ] = 0x00;
    tx_buf[ 3 ] = 0x66;
    tx_buf[ 4 ] = 0x9C;

    c6dofimu5_baro_write( ctx, tx_buf, 5 );

    for ( i = 0; i < 4; i++ )
    {
        c6dofimu5_baro_read ( ctx, C6DOFIMU5_INCREMENTAL_READ, rx_buf, 3 );
        output[ i ] = rx_buf[ 0 ];
        output[ i ] <<= 8;
        output[ i ] |= rx_buf[ 1 ];
    }
}

static void dev_init_base ( c6dofimu5_t *ctx, uint8_t *otp )
{
    float sens_const[ 4 ];

    uint8_t i;
    for( i = 0; i < 4; i++ )
    {
        sens_const[ i ] = ( float )otp[ i ];
    }
    ctx->sens_const_0 = sens_const[ 0 ];
    ctx->sens_const_1 = sens_const[ 1 ];
    ctx->sens_const_2 = sens_const[ 2 ];
    ctx->sens_const_3 = sens_const[ 3 ];
}

static void dev_calc_init ( c6dofimu5_t *ctx )
{
    uint8_t otp[ 4 ];

    dev_read_otp_from_i2c( ctx, &otp );
    dev_init_base( ctx, otp );
}

static void dev_calc_conv_const ( c6dofimu5_t *ctx, float *p_lut, float *output )
{
    float coef_a;
    float coef_b;
    float coef_c;

    coef_c = ( p_lut[ 0 ] * p_lut[ 1 ] * ( C6DOFIMU5_P_PA_CALIB_0 - C6DOFIMU5_P_PA_CALIB_1 ) +
    p_lut[ 1 ] * p_lut[ 2 ] * ( C6DOFIMU5_P_PA_CALIB_1 - C6DOFIMU5_P_PA_CALIB_2 ) + p_lut[ 2 ] *
    p_lut[ 0 ] * ( C6DOFIMU5_P_PA_CALIB_2 - C6DOFIMU5_P_PA_CALIB_0 ) ) / ( p_lut[ 2 ] *
    ( C6DOFIMU5_P_PA_CALIB_0 - C6DOFIMU5_P_PA_CALIB_1 ) + p_lut[ 0 ] * ( C6DOFIMU5_P_PA_CALIB_1 -
    C6DOFIMU5_P_PA_CALIB_2 ) + p_lut[ 1 ] * ( C6DOFIMU5_P_PA_CALIB_2 - C6DOFIMU5_P_PA_CALIB_0 ) );

    coef_a = (  C6DOFIMU5_P_PA_CALIB_0 * p_lut[ 0 ] - C6DOFIMU5_P_PA_CALIB_1 * p_lut[ 1 ] -
    ( C6DOFIMU5_P_PA_CALIB_1 -  C6DOFIMU5_P_PA_CALIB_0 ) * coef_c ) / ( p_lut[ 0 ] -
     p_lut[ 1 ] );

    coef_b = (  C6DOFIMU5_P_PA_CALIB_0 - coef_a ) * ( p_lut[ 0 ] + coef_c );

    output[ 0 ] = coef_a;
    output[ 1 ] = coef_b;
    output[ 2 ] = coef_c;
}

// ------------------------------------------------------------------------- END

