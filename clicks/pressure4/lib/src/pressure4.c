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

#include "pressure4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PRESSURE4_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void pressure4_i2c_write ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure4_i2c_read ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure4_spi_write ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static void pressure4_spi_read ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

static double pressure4_dig_t1_calc ( pressure4_t *ctx );

static double pressure4_dig_p3_calc ( pressure4_t *ctx );

static uint8_t pressure4_conv_status ( pressure4_t *ctx );

static uint16_t pressure4_read_reg_16_bit ( pressure4_t *ctx, uint8_t r_reg );

static int16_t pressure4_read_reg_s_16_bit ( pressure4_t *ctx, uint8_t r_reg );

static uint32_t pressure4_read_reg_24_bit ( pressure4_t *ctx, uint8_t r_reg );

static uint16_t pressure4_read_const ( pressure4_t *ctx, uint8_t addr );

static void pressure4_read_constants ( pressure4_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pressure4_cfg_setup ( pressure4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PRESSURE4_ADDR0;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->sel = PRESSURE4_MASTER_SPI;
}

PRESSURE4_RETVAL pressure4_init ( pressure4_t *ctx, pressure4_cfg_t *cfg )
{
    // Only in case it is necessary to check somewhere which communication is set
    ctx->master_sel = cfg->sel;

    if ( ctx->master_sel == PRESSURE4_MASTER_I2C )
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );
        i2c_cfg.speed   = cfg->i2c_speed;
        i2c_cfg.scl     = cfg->scl;
        i2c_cfg.sda     = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
        {
            return PRESSURE4_INIT_ERROR;
        }

        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
        i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

        ctx->read_f = pressure4_i2c_read;
        ctx->write_f = pressure4_i2c_write;
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
        spi_cfg.default_write_data = PRESSURE4_DUMMY;
        
        digital_out_init( &ctx->cs, cfg->cs );
        ctx->chip_select = cfg->cs;

        if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
        {
            return  PRESSURE4_INIT_ERROR;
        }

        spi_master_set_default_write_data( &ctx->spi, PRESSURE4_DUMMY );
        spi_master_set_mode( &ctx->spi, spi_cfg.mode );
        spi_master_set_speed( &ctx->spi, spi_cfg.speed );
        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select ); 
        
        ctx->read_f = pressure4_spi_read;
        ctx->write_f = pressure4_spi_write;
    }

    return PRESSURE4_OK;
}

void pressure4_default_cfg ( pressure4_t *ctx )
{
    pressure4_write_reg_8_bit( ctx, PRESSURE4_RESET, 0xB6 );
    pressure4_read_constants( ctx );
    pressure4_write_reg_8_bit( ctx, PRESSURE4_CTL_MEAS & 0x7F, 0x3F );
    ctx->t1_calc_1 = pressure4_dig_t1_calc( ctx );
    ctx->p3_calc_1 = pressure4_dig_p3_calc( ctx ); 
}

void pressure4_generic_write ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->write_f( ctx, reg, data_buf, len ); 
}

void pressure4_generic_read ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    ctx->read_f( ctx, reg, data_buf, len );
}

void pressure4_write_reg_8_bit ( pressure4_t *ctx, uint8_t w_reg, uint8_t w_data )
{
    uint8_t dummy[ 3 ];

    pressure4_generic_write( ctx, w_reg, &w_data, 1 );
}

uint8_t pressure4_read_reg_8_bit ( pressure4_t *ctx, uint8_t r_reg )
{
    static uint8_t reg_read[ 5 ];

    pressure4_generic_read( ctx, r_reg, reg_read, 1 );

    return reg_read[ 0 ];
}

uint8_t pressure4_read_id ( pressure4_t *ctx )
{
    pressure4_write_reg_8_bit( ctx, PRESSURE4_RESET, 0xB6 );
    return pressure4_read_reg_8_bit( ctx, PRESSURE4_ID );
}

uint8_t pressure4_get_status ( pressure4_t *ctx )
{
    return pressure4_read_reg_8_bit( ctx, PRESSURE4_STATUS );
}

double pressure4_get_temperature ( pressure4_t *ctx )
{
    int32_t adc_t;
    double var_1, var_2, t;
 
    if ( pressure4_conv_status( ctx ) )
    {
      adc_t = pressure4_read_reg_24_bit( ctx, PRESSURE4_TEMP_MSB );
      var_1 = ( ( ( double )adc_t ) / 16384.0 - ( ( double )ctx->dig_t1 ) / 1024.0 ) * ( ( double )ctx->dig_t2 );
      var_2 = ( ( ( ( double )adc_t ) / 131072.0 - ( ( double )ctx->dig_t1 ) / 8192.0 ) * ( ( ( double ) adc_t ) / 131072.0 - ( ( double )ctx->dig_t1 ) / 8192.0 ) ) * ( ( double )ctx->dig_t3 );
      ctx->t_fine = ( int32_t )( var_1 + var_2 );
      t = ( var_1 + var_2 ) / 5120.0;
    }
    return t;
}

double pressure4_get_pressure ( pressure4_t *ctx )
{
    double var1, var2, p123;
    double adc_p;

    pressure4_get_temperature( ctx );

    adc_p = pressure4_read_reg_24_bit( ctx, PRESSURE4_PRESS_MSB );

    var1 = ( ( double )ctx->t_fine / 2.0 ) - 64000.0;
    var2 = var1 * var1 * ( ( double )ctx->dig_p6 ) / 32768.0;
    var2 = var2 + var1 * ( ( double )ctx->dig_p5 ) * 2.0;
    var2 = ( var2 / 4.0 ) + ( ( ( double )ctx->dig_p4 ) * 65536.0 );
    var1 = ( ( ( double )ctx->dig_p3 ) * var1 * var1 / 524288.0 + ( ( double )ctx->dig_p2 ) * var1 ) / 524288.0;
    var1 = ( 1.0 + var1 / 32768.0 )*( ( double )ctx->dig_p1 );
    if( var1 == 0.0 )
    {
      return 0;
    }

    p123 = 1048576.0 - ( double )adc_p;
    p123 = ( p123 - ( var2  / 4096.0 ) ) * 6250 / var1;
    var1 = ( ( double )ctx->dig_p9 ) * p123 * p123 / 2147483648.0;
    var2 = p123 * ( ( double )ctx->dig_p8) / 32768.0;
    p123 = p123 + ( var1 + var2 + ( ( double )ctx->dig_p7 ) ) / 16.0;

    return p123 / 100;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void pressure4_i2c_write ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

static void pressure4_i2c_read ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

static void pressure4_spi_write ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
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

static void pressure4_spi_read ( pressure4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 256 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg | 0x80;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, len );
    spi_master_deselect_device( ctx->chip_select ); 

    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt ] = rx_buf [ cnt ];
    }
}

static double pressure4_dig_t1_calc ( pressure4_t *ctx )
{
    return ( ( ( double )ctx->dig_t1 ) / 8192.0 );
}

static double pressure4_dig_p3_calc ( pressure4_t *ctx )
{
    return ( ( ( double )ctx->dig_p3 ) / 524288.0 );
}

static uint8_t pressure4_conv_status ( pressure4_t *ctx )
{
    return ( ( pressure4_get_status( ctx ) & 1 << 3 ) >> 3 );
}

static uint16_t pressure4_read_reg_16_bit ( pressure4_t *ctx, uint8_t r_reg )
{
    static uint8_t reg_read[ 5 ];
    uint16_t tmp;

    pressure4_generic_read( ctx, r_reg, reg_read, 2 );
    tmp = ( uint16_t )( reg_read[ 0 ] << 8 ) | reg_read[ 1 ];
    return tmp;
}

static int16_t pressure4_read_reg_s_16_bit ( pressure4_t *ctx, uint8_t r_reg )
{
    int16_t tmp;

    tmp = ( int16_t )pressure4_read_reg_16_bit( ctx, r_reg );

    return tmp;
}

static uint32_t pressure4_read_reg_24_bit ( pressure4_t *ctx, uint8_t r_reg )
{
    uint32_t tmp;

    tmp = ( uint32_t )pressure4_read_reg_16_bit( ctx, r_reg );
    tmp <<= 8;
    tmp |= ( uint32_t )pressure4_read_reg_8_bit( ctx, r_reg + 2 );
    return tmp >> 4 ;
}

static uint16_t pressure4_read_const ( pressure4_t *ctx, uint8_t addr )
{
    uint8_t reg_read[ 5 ];
    uint16_t tmp;

    pressure4_generic_read( ctx, addr, reg_read, 2 );
    tmp = ( uint16_t )( reg_read[ 1 ] << 8 ) | reg_read[ 0 ];

    return tmp;
}

static void pressure4_read_constants ( pressure4_t *ctx )
{
    ctx->dig_t1 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_T1 );
    ctx->dig_t2 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_T2 );
    ctx->dig_t3 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_T3 );

    ctx->dig_p1 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_P1 );
    ctx->dig_p2 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_P2 );
    ctx->dig_p3 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_P3 );
    ctx->dig_p4 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_P4 );
    ctx->dig_p5 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_P5 );
    ctx->dig_p6 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_P6 );
    ctx->dig_p7 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_P7 );
    ctx->dig_p8 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_P8 );
    ctx->dig_p9 = pressure4_read_const( ctx, PRESSURE4_CALLIBRATION_DIG_P9 );
}

// ------------------------------------------------------------------------- END

