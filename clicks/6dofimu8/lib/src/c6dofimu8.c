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

#include "c6dofimu8.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C6DOFIMU8_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void c6dofimu8_i2c_write ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu8_i2c_read ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu8_spi_write ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void c6dofimu8_spi_read ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void get_resolution ( c6dofimu8_t *ctx, double *gyro_lsb, double *accel_lsb );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c6dofimu8_cfg_setup ( c6dofimu8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->it2   = HAL_PIN_NC;
    cfg->it1 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = C6DOFIMU8_DEVICE_ADDR_LSB_HIGH;
    cfg->spi_speed = 100000; 
    cfg->spi_mode = 0;
    cfg->sel = C6DOFIMU8_MASTER_I2C;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

C6DOFIMU8_RETVAL c6dofimu8_init ( c6dofimu8_t *ctx, c6dofimu8_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == C6DOFIMU8_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed    = cfg->i2c_speed;
        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) != I2C_MASTER_SUCCESS )
        {
            return C6DOFIMU8_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = c6dofimu8_i2c_read;
        ctx->write_f = c6dofimu8_i2c_write;
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

        if (  spi_master_open( &ctx->spi, &spi_cfg ) != SPI_MASTER_SUCCESS )
        {
            return  C6DOFIMU8_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, C6DOFIMU8_DUMMY );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        
        ctx->read_f = c6dofimu8_spi_read;
        ctx->write_f = c6dofimu8_spi_write;
    }

    // Input pins

    digital_in_init( &ctx->it2, cfg->it2 );
    digital_in_init( &ctx->it1, cfg->it1 );

    return C6DOFIMU8_OK;
}

void c6dofimu8_default_cfg ( c6dofimu8_t *ctx )
{
    c6dofimu8_reset( ctx );
    c6dofimu8_set_odr( ctx, C6DOFIMU8_ODR_104_HZ, C6DOFIMU8_ODR_104_HZ );
    c6dofimu8_set_fsr( ctx, C6DOFIMU8_FS_G_500DPS, C6DOFIMU8_FS_XL_8G );
    c6dofimu8_write_byte( ctx, C6DOFIMU8_INT1_CTRL_REG, C6DOFIMU8_INT_PIN_G_DRDY_FLAG_EN );
    c6dofimu8_write_byte( ctx, C6DOFIMU8_INT2_CTRL_REG, C6DOFIMU8_INT_PIN_XL_DRDY_FLAG_EN ); 
}

void c6dofimu8_generic_write ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void c6dofimu8_generic_read ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

uint8_t c6dofimu8_write_byte ( c6dofimu8_t *ctx, uint8_t reg_addr, uint8_t data_in )
{
    if ( reg_addr & 0x80 )
    {
        return C6DOFIMU8_ADDR_ERROR;
    }
    
    c6dofimu8_generic_write( ctx, reg_addr, &data_in, 1 );
    
    return C6DOFIMU8_OK;
}

uint8_t  c6dofimu8_read_byte ( c6dofimu8_t *ctx, uint8_t reg_addr, uint8_t *data_out )
{
    if ( reg_addr & 0x80 )
    {
        return C6DOFIMU8_ADDR_ERROR;
    }
    
    c6dofimu8_generic_read( ctx, reg_addr, data_out, 1 );
    
    return C6DOFIMU8_OK;
}

uint8_t c6dofimu8_write_word ( c6dofimu8_t *ctx, uint8_t reg_addr, uint16_t data_in )
{
    uint8_t buff_in[ 3 ];

    if ( reg_addr & 0x80 )
    {
        return C6DOFIMU8_ADDR_ERROR;
    }

    buff_in[ 0 ] = data_in;
    buff_in[ 1 ] = data_in >> 8;

    c6dofimu8_generic_write( ctx, reg_addr, buff_in, 2 );

    return C6DOFIMU8_OK;
}

uint8_t c6dofimu8_read_word ( c6dofimu8_t *ctx, uint8_t reg_addr, uint16_t *data_out )
{
    uint8_t buff_out[ 3 ];

    if ( reg_addr & 0x80 )
    {
        return C6DOFIMU8_ADDR_ERROR;
    }

    c6dofimu8_generic_read( ctx, reg_addr, buff_out, 2 );

    *data_out = buff_out[ 1 ];
    *data_out <<= 8;
    *data_out |= buff_out[ 0 ];

    return C6DOFIMU8_OK;
}

uint8_t c6dofimu8_write_bytes ( c6dofimu8_t *ctx, uint8_t start_addr, uint8_t *data_in, uint8_t n_bytes )
{
    if ( start_addr & 0x80 )
    {
        return C6DOFIMU8_ADDR_ERROR;
    }

    c6dofimu8_generic_write( ctx, start_addr, data_in, n_bytes );

    return C6DOFIMU8_OK;
}

uint8_t c6dofimu8_read_bytes ( c6dofimu8_t *ctx, uint8_t start_addr, uint8_t *data_out, uint8_t n_bytes )
{
    if ( start_addr & 0x80 )
    {
        return C6DOFIMU8_ADDR_ERROR;
    }

    c6dofimu8_generic_read( ctx, start_addr, data_out, n_bytes );

    return C6DOFIMU8_OK;
}

void c6dofimu8_reset ( c6dofimu8_t *ctx )
{
    uint8_t temp_data;

    c6dofimu8_read_byte( ctx, C6DOFIMU8_CTRL3_C_REG, &temp_data );
    temp_data |= C6DOFIMU8_SW_RESET_CMD;
    c6dofimu8_write_byte( ctx, C6DOFIMU8_CTRL3_C_REG, temp_data );
    Delay_1sec( );
}

uint8_t c6dofimu8_get_int_1_pin ( c6dofimu8_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->it1 );

    if ( state )
    {
        return C6DOFIMU8_INT_OCCURED;
    }
    else
    {
        return C6DOFIMU8_OK;
    }
}

uint8_t c6dofimu8_get_int_2_pin ( c6dofimu8_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->it2 );

    if ( state )
    {
        return C6DOFIMU8_INT_OCCURED;
    }
    else
    {
        return C6DOFIMU8_OK;
    }
}

uint8_t c6dofimu8_get_drdy_status ( c6dofimu8_t *ctx, uint8_t bit_mask )
{
    uint8_t temp_data;

    c6dofimu8_read_byte( ctx, C6DOFIMU8_STATUS_REG, &temp_data );
    temp_data &= bit_mask;

    return temp_data;
}

void c6dofimu8_get_data ( c6dofimu8_t *ctx, t_c6dofimu8_axis *accel_out, t_c6dofimu8_axis *gyro_out, int8_t *temp_out )
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

    c6dofimu8_read_bytes( ctx, C6DOFIMU8_OUT_TEMP_REG, temp_data, 14 );
    get_resolution( ctx, &gyro_lsb, &accel_lsb );

    check_var = 0;
    tmp_idx = 0;
    for ( count = 0; count < 14; count++ )
    {
        if ( count < 2 )
        {
            if ( check_var == 0 )
            {
                temp = temp_data[ count ];
                check_var = 1;
            }
            else
            {
                temp |= (int16_t)temp_data[ count ] << 8;
                check_var = 0;
            }
        }
        else if ( ( count >= 2 ) && ( count < 8 ) )
        {
            if ( check_var == 0 )
            {
                gyro_tmp[ tmp_idx ] = temp_data[ count ];
                check_var = 1;
            }
            else
            {
                gyro_tmp[ tmp_idx ] |= (int16_t)temp_data[ count ] << 8;
                tmp_idx++;
                check_var = 0;
                
                if ( count == 7 )
                {
                    tmp_idx = 0;
                }
            }
        }
        else
        {
            if ( check_var == 0 )
            {
                accel_tmp[ tmp_idx ] = temp_data[ count ];
                check_var = 1;
            }
            else
            {
                accel_tmp[ tmp_idx ] |= (int16_t)temp_data[ count ] << 8;
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

uint8_t c6dofimu8_set_fsr ( c6dofimu8_t *ctx, uint8_t gyro_fsr, uint8_t accel_fsr )
{
    uint8_t fsr_data[ 2 ];

    if ( ( gyro_fsr > 4 ) || ( accel_fsr > 3 ) )
    {
        return C6DOFIMU8_FULL_SCALE_ERROR;
    }

    c6dofimu8_read_bytes( ctx, C6DOFIMU8_CTRL1_XL_REG, fsr_data, 2 );
    fsr_data[ 0 ] &= 0xF3;
    fsr_data[ 1 ] &= 0xF1;
    fsr_data[ 0 ] |= accel_fsr << 2;
    
    if ( gyro_fsr == C6DOFIMU8_FS_G_125DPS )
    {
        fsr_data[ 1 ] |= 0x02;
    }
    else
    {
        fsr_data[ 1 ] |= gyro_fsr << 2;
    }
    
    c6dofimu8_write_bytes( ctx, C6DOFIMU8_CTRL1_XL_REG, fsr_data, 2 );

    ctx->gyro_res = gyro_fsr;
    ctx->accel_res = accel_fsr;

    return C6DOFIMU8_OK;
}

uint8_t c6dofimu8_set_odr ( c6dofimu8_t *ctx, uint8_t gyro_odr, uint8_t accel_odr )
{
    uint8_t odr_data[ 2 ];
    
    if ( ( gyro_odr > 0x0B ) || ( accel_odr > 0x0B ) )
    {
        return C6DOFIMU8_DATA_RATE_ERROR;
    }
    
    c6dofimu8_read_bytes( ctx, C6DOFIMU8_CTRL1_XL_REG, odr_data, 2 );
    odr_data[ 0 ] &= 0x0F;
    odr_data[ 1 ] &= 0x0F;
    odr_data[ 0 ] |= accel_odr << 4;
    odr_data[ 1 ] |= gyro_odr << 4;
    c6dofimu8_write_bytes( ctx, C6DOFIMU8_CTRL1_XL_REG, odr_data, 2 );
    
    return C6DOFIMU8_OK;
}

void c6dofimu8_get_magnetometer_data ( c6dofimu8_t *ctx, t_c6dofimu8_axis *magneto_out )
{
    uint8_t temp_data[ 6 ];
    int16_t magneto_tmp[ 3 ];
    uint8_t tmp_idx;
    uint8_t count;
    uint8_t check_var;
    
    c6dofimu8_read_bytes( ctx, C6DOFIMU8_OUT_MAG_RAW_X_REG, temp_data, 6 );
    
    tmp_idx = 0;
    check_var = 0;
    for ( count = 0; count < 6; count++ )
    {
        if ( check_var == 0 )
        {
            magneto_tmp[ tmp_idx ] = temp_data[ count ];
            check_var = 1;
        }
        else
        {
            magneto_tmp[ tmp_idx ] |= (int16_t)temp_data[ count ] << 8;
            tmp_idx++;
            check_var = 0;
        }
    }
    
    magneto_out->x = magneto_tmp[ 0 ];
    magneto_out->y = magneto_tmp[ 1 ];
    magneto_out->z = magneto_tmp[ 2 ];
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void c6dofimu8_i2c_write ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c6dofimu8_i2c_read ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void c6dofimu8_spi_write ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void c6dofimu8_spi_read ( c6dofimu8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void get_resolution ( c6dofimu8_t *ctx, double *gyro_lsb, double *accel_lsb )
{
    switch ( ctx->gyro_res )
    {
        case C6DOFIMU8_FS_G_250DPS :
        {
            *gyro_lsb = 0.00762939453125;
            break;
        }
        case C6DOFIMU8_FS_G_500DPS :
        {
            *gyro_lsb = 0.0152587890625;
            break;
        }
        case C6DOFIMU8_FS_G_1000DPS :
        {
            *gyro_lsb = 0.030517578125;
            break;
        }
        case C6DOFIMU8_FS_G_2000DPS :
        {
            *gyro_lsb = 0.06103515625;
            break;
        }
        case C6DOFIMU8_FS_G_125DPS :
        {
            *gyro_lsb = 0.003814697265625;
            break;
        }
    }

    switch ( ctx->accel_res )
    {
        case C6DOFIMU8_FS_XL_2G :
        {
            *accel_lsb = 0.00006103515625;
            break;
        }
        case C6DOFIMU8_FS_XL_16G :
        {
            *accel_lsb = 0.00048828125;
            break;
        }
        case C6DOFIMU8_FS_XL_4G :
        {
            *accel_lsb = 0.0001220703125;
            break;
        }
        case C6DOFIMU8_FS_XL_8G :
        {
            *accel_lsb = 0.000244140625;
            break;
        }
    }
}

// ------------------------------------------------------------------------- END

