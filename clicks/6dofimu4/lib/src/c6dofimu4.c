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

#include "c6dofimu4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C6DOFIMU4_DUMMY 0
#define SPI_RD_CMD  0x80
#define TEMP_LSB_RES  326.8
#define TEMP_OFFSET  25

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c6dofimu4_i2c_write ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu4_i2c_read ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu4_spi_write ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu4_spi_read ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void get_resolution ( c6dofimu4_t *ctx, double *gyro_lsb, double *accel_lsb );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c6dofimu4_cfg_setup ( c6dofimu4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->syn = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = C6DOFIMU4_DEVICE_ADDR;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = 0;
    cfg->sel = C6DOFIMU4_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
     
    cfg->dev_gyro_res = C6DOFIMU4_GYRO_FS_SEL_250_DPS;
    cfg->dev_accel_res = C6DOFIMU4_ACCEL_FS_SEL_2_G;
}

C6DOFIMU4_RETVAL c6dofimu4_init ( c6dofimu4_t *ctx, c6dofimu4_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == C6DOFIMU4_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return C6DOFIMU4_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = c6dofimu4_i2c_read;
        ctx->write_f = c6dofimu4_i2c_write;
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

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  C6DOFIMU4_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, C6DOFIMU4_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->read_f = c6dofimu4_spi_read;
        ctx->write_f = c6dofimu4_spi_write;
        
        ctx->gyro_res = cfg->dev_gyro_res;
        ctx->accel_res = cfg->dev_accel_res;
 
    }
    
    spi_master_deselect_device( ctx->chip_select ); 
    
    // Output pins 

    digital_out_init( &ctx->syn, cfg->syn );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return C6DOFIMU4_OK;
}

void c6dofimu4_default_cfg ( c6dofimu4_t *ctx )
{
    c6dofimu4_write_byte( ctx, C6DOFIMU4_I2C_IF_REG, C6DOFIMU4_I2C_IF_EN );
    c6dofimu4_write_byte( ctx, C6DOFIMU4_PWR_MGMT_2_REG, C6DOFIMU4_ALL_AXIS_EN );
    c6dofimu4_write_byte( ctx, C6DOFIMU4_PWR_MGMT_1_REG, C6DOFIMU4_CLKSEL_INTERNAL_20_MHZ );
    c6dofimu4_write_byte( ctx, C6DOFIMU4_INT_PIN_CFG_REG, C6DOFIMU4_INT_DRDY_PIN_ACT_HIGH | 
                                                          C6DOFIMU4_INT_DRDY_PIN_STAT_CLEARED | 
                                                          C6DOFIMU4_INT_STAT_CLEARED_STAT_REG_READ );
    c6dofimu4_set_fsr( ctx, C6DOFIMU4_GYRO_FS_SEL_2000_DPS, C6DOFIMU4_ACCEL_FS_SEL_16_G );
}

void c6dofimu4_generic_write ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void c6dofimu4_generic_read ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t c6dofimu4_write_byte ( c6dofimu4_t *ctx, uint8_t reg_addr, uint8_t data_in )
{
    if ( reg_addr & 0x80 )
    {
        return C6DOFIMU4_ADDR_ERROR;
    }

    c6dofimu4_generic_write( ctx, reg_addr, &data_in, 1 );

    return C6DOFIMU4_OK;
}

uint8_t c6dofimu4_read_byte ( c6dofimu4_t *ctx, uint8_t reg_addr, uint8_t *data_out )
{
    if ( reg_addr & 0x80 )
    {
        return C6DOFIMU4_ADDR_ERROR;
    }

    c6dofimu4_generic_read( ctx, reg_addr, data_out, 1 );
}

uint8_t c6dofimu4_write_word ( c6dofimu4_t *ctx, uint8_t reg_addr, uint16_t data_in )
{
    uint8_t buff_in[ 2 ];
    
    if ( reg_addr & 0x80 )
    {
        return C6DOFIMU4_ADDR_ERROR;
    }

    buff_in[ 0 ] = data_in >> 8;
    buff_in[ 1 ] = data_in;

    c6dofimu4_generic_write( ctx, reg_addr, buff_in, 2 );

    return C6DOFIMU4_OK;
}

uint8_t c6dofimu4_read_word( c6dofimu4_t *ctx, uint8_t reg_addr, uint16_t *data_out )
{
    uint8_t buff_out[ 2 ];
    
    if ( reg_addr & 0x80 )
    {
        return C6DOFIMU4_ADDR_ERROR;
    }

    reg_addr |= SPI_RD_CMD;

    c6dofimu4_generic_read( ctx, reg_addr, buff_out, 2 );
    
    *data_out = buff_out[ 0 ];
    *data_out <<= 8;
    *data_out |= buff_out[ 1 ];
    
    return C6DOFIMU4_OK;
}

uint8_t c6dofimu4_write_bytes ( c6dofimu4_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_bytes )
{
    uint8_t buff_in[ 256 ];
    uint16_t cnt;
    
    if ( start_addr & 0x80 )
    {
        return C6DOFIMU4_ADDR_ERROR;
    }
    
    for ( cnt = 0; cnt <= n_bytes; cnt++ )
    {
        buff_in[ cnt ] = *data_in;
        data_in++;
    }
    
    c6dofimu4_generic_write( ctx, start_addr, buff_in, n_bytes );
    
    return C6DOFIMU4_OK;
}

uint8_t c6dofimu4_read_bytes ( c6dofimu4_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_bytes )
{
    uint8_t buff_out[ 256 ];
    uint16_t cnt;
    
    if ( start_addr & 0x80 )
    {
        return C6DOFIMU4_ADDR_ERROR;
    }

    start_addr |= SPI_RD_CMD;

    c6dofimu4_generic_read( ctx, start_addr, buff_out, n_bytes );
    
    for (cnt = 0; cnt <= n_bytes; cnt++)
    {
        *data_out = buff_out[ cnt ];
        data_out++;
    }
    
    return C6DOFIMU4_OK;
}

void c6dofimu4_reset ( c6dofimu4_t *ctx )
{
    uint8_t temp_data;
    
    c6dofimu4_read_byte( ctx, C6DOFIMU4_PWR_MGMT_1_REG, &temp_data );
    temp_data |= C6DOFIMU4_DEVICE_RST;
    c6dofimu4_write_byte( ctx, C6DOFIMU4_PWR_MGMT_1_REG, temp_data );
    Delay_1sec( );
}

void c6dofimu4_set_sync_pin ( c6dofimu4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->syn, state );
}

uint8_t c6dofimu4_get_int_pin ( c6dofimu4_t *ctx )
{
    if ( digital_in_read( &ctx->int_pin ) )
    {
        return C6DOFIMU4_INT_OCCURED;
    }
    else
    {
        return C6DOFIMU4_OK;
    }
}

uint8_t c6dofimu4_get_status ( c6dofimu4_t *ctx, uint8_t bit_mask )
{
    uint8_t temp_data;
    
    c6dofimu4_read_byte( ctx, C6DOFIMU4_INT_STATUS_REG, &temp_data );
    temp_data &= bit_mask;
    
    return temp_data;
}

void c6dofimu4_get_data ( c6dofimu4_t *ctx, c6dofimu4_axis_t *accel_out, c6dofimu4_axis_t *gyro_out, int8_t *temp_out )
{
    uint8_t temp_data[ 14 ];
    int16_t temp;
    int16_t accel_tmp[ 3 ];
    int16_t gyro_tmp[ 3 ];
    uint8_t tmp_idx;
    uint8_t count;
    uint8_t check_var;
    double res;
    double gyro_lsb;
    double accel_lsb;
    
    c6dofimu4_read_bytes( ctx, C6DOFIMU4_ACCEL_XOUT_REG, temp_data, 14 );
    get_resolution( ctx, &gyro_lsb, &accel_lsb );
    
    check_var = 0;
    tmp_idx = 0;
    for ( count = 0; count < 14; count++ )
    {
        if ( count < 6 )
        {
            if ( check_var == 0 )
            {
                accel_tmp[ tmp_idx ] = temp_data[ count ];
                accel_tmp[ tmp_idx ] <<= 8;
                check_var = 1;
            }
            else
            {
                accel_tmp[ tmp_idx ] |= temp_data[ count ];
                tmp_idx++;
                check_var = 0;
            }
        }
        else if ( ( count >= 6 ) && ( count < 8 ) )
        {
            if ( check_var == 0 )
            {
                temp = temp_data[ count ];
                temp <<= 8;
                check_var = 1;
            }
            else
            {
                temp |= temp_data[ count ];
                check_var = 0;
                tmp_idx = 0;
            }
        }
        else
        {
            if ( check_var == 0 )
            {
                gyro_tmp[ tmp_idx ] = temp_data[ count ];
                gyro_tmp[ tmp_idx ] <<= 8;
                check_var = 1;
            }
            else
            {
                gyro_tmp[ tmp_idx ] |= temp_data[ count ];
                tmp_idx++;
                check_var = 0;
            }
        }
    }
    
    res = temp;
    res /= TEMP_LSB_RES;
    res += TEMP_OFFSET;
    *temp_out = res;
    
    accel_out->x = accel_tmp[ 0 ];
    accel_out->x *= accel_lsb;
    accel_out->y = accel_tmp[ 1 ];
    accel_out->y *= accel_lsb;
    accel_out->z = accel_tmp[ 2 ];
    accel_out->z *= accel_lsb;
    
    gyro_out->x = gyro_tmp[ 0 ];
    gyro_out->x *= gyro_lsb;
    gyro_out->y = gyro_tmp[ 1 ];
    gyro_out->y *= gyro_lsb;
    gyro_out->z = gyro_tmp[ 2 ];
    gyro_out->z *= gyro_lsb;
}

uint8_t c6dofimu4_set_fsr ( c6dofimu4_t *ctx, uint8_t gyro_resol, uint8_t accel_resol )
{
    uint8_t temp_data[ 2 ];
    
    if ( ( gyro_resol > C6DOFIMU4_GYRO_FS_SEL_2000_DPS ) || ( accel_resol > C6DOFIMU4_ACCEL_FS_SEL_16_G ) )
    {
        return C6DOFIMU4_SENS_RESOLUTION_ERROR;
    }
    
    c6dofimu4_read_bytes( ctx, C6DOFIMU4_GYRO_CONFIG_REG, temp_data, 2 );
    temp_data[ 0 ] &= 0xE7;
    temp_data[ 1 ] &= 0xE7;
    temp_data[ 0 ] |= gyro_resol << 3;
    temp_data[ 1 ] |= accel_resol << 3;
    c6dofimu4_write_bytes( ctx, C6DOFIMU4_GYRO_CONFIG_REG, temp_data, 2 );
    
    ctx->gyro_res = gyro_resol;
    ctx->accel_res = accel_resol;
    
    return C6DOFIMU4_OK;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c6dofimu4_i2c_write ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c6dofimu4_i2c_read ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void c6dofimu4_spi_write ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c6dofimu4_spi_read ( c6dofimu4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 
}

static void get_resolution ( c6dofimu4_t *ctx, double *gyro_lsb, double *accel_lsb )
{
    switch ( ctx->gyro_res )
    {
        case C6DOFIMU4_GYRO_FS_SEL_250_DPS:
        {
            *gyro_lsb = 0.00762939453125;
        break;
        }
        case C6DOFIMU4_GYRO_FS_SEL_500_DPS:
        {
            *gyro_lsb = 0.0152587890625;
        break;
        }
        case C6DOFIMU4_GYRO_FS_SEL_1000_DPS:
        {
            *gyro_lsb = 0.030517578125;
        break;
        }
        case C6DOFIMU4_GYRO_FS_SEL_2000_DPS:
        {
            *gyro_lsb = 0.06103515625;
        break;
        }
    }
    
    switch ( ctx->accel_res )
    {
        case C6DOFIMU4_ACCEL_FS_SEL_2_G:
        {
            *accel_lsb = 0.00006103515625;
        break;
        }
        case C6DOFIMU4_ACCEL_FS_SEL_4_G:
        {
            *accel_lsb = 0.0001220703125;
        break;
        }
        case C6DOFIMU4_ACCEL_FS_SEL_8_G:
        {
            *accel_lsb = 0.000244140625;
        break;
        }
        case C6DOFIMU4_ACCEL_FS_SEL_16_G:
        {
            *accel_lsb = 0.00048828125;
        break;
        }
    }
}

// ------------------------------------------------------------------------- END

