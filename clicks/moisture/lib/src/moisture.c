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

#include "moisture.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MOISTURE_SAMPLE_NUM    16
#define MOISTURE_12_BIT_DATA   0x0FFF;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void cal_wait_period ( );

static void clc_wait_period ( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void moisture_cfg_setup ( moisture_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = MOISTURE_DEV_ADR_GND;
}

MOISTURE_RETVAL moisture_init ( moisture_t *ctx, moisture_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return MOISTURE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    ctx->calib_air_data = 572;

    return MOISTURE_OK;
}

void moisture_default_cfg ( moisture_t *ctx )
{
    moisture_write_word( ctx, MOISTURE_REG_RESET_DEV,
                         MOISTURE_OUTPUT_GAIN_x16 );

    moisture_write_word( ctx, MOISTURE_REG_SETTLE_CNT,
                         MOISTURE_SETTLE_CNT_CFG_DEFAULT );

    moisture_write_word( ctx, MOISTURE_REG_RCNT, MOISTURE_RCNT_CFG_DEFAULT );
    moisture_write_word( ctx, MOISTURE_REG_OFFSET, MOISTURE_DEFAULT_OFFSET );
    moisture_write_word( ctx, MOISTURE_REG_CLOCK_DIVIDERS,
                         MOISTURE_COMBINED_VAL_CH0_DIV |
                         MOISTURE_CLOCK_DIVIDERS_x10 );

    moisture_write_word( ctx, MOISTURE_REG_DRIVE_CURR,
                         MOISTURE_DRIVE_CURR_CH0 );

    moisture_write_word( ctx, MOISTURE_REG_ERR_CFG, MOISTURE_ALL_ERR_ENABLED );
    moisture_write_word( ctx, MOISTURE_REG_CFG,
                         MOISTURE_REG_CFG_DEFAULT_SETTINGS );

    moisture_write_word( ctx, MOISTURE_REG_MUX_CFG,
                         MOISTURE_INPUT_DEGLITCH_FILT_BWDTH_33MHZ );
}

void moisture_generic_write ( moisture_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void moisture_generic_read ( moisture_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void moisture_write_word ( moisture_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = ( data_in >> 8 ) & 0x00FF;
    tx_buf[ 1 ] = data_in & 0x00FF;

    moisture_generic_write ( ctx, reg, tx_buf, 2 );
}

uint16_t moisture_read_word ( moisture_t *ctx, uint8_t reg )
{
    uint16_t data_res;
    uint8_t rx_buf[ 2 ];

    moisture_generic_read ( ctx, reg, rx_buf, 2 );

    data_res = rx_buf[ 0 ];
    data_res <<= 8;
    data_res |= rx_buf[ 1 ];

    return data_res;
}

void moisture_soft_reset ( moisture_t *ctx )
{
    moisture_write_word( ctx, MOISTURE_REG_RESET_DEV, MOISTURE_RESET_DEVICE );
}

void  moisture_cfg( moisture_t *ctx, uint16_t gain, uint16_t offset, uint16_t clk_div )
{
    clk_div = clk_div & 0x000F;

    moisture_write_word( ctx, MOISTURE_REG_RESET_DEV, gain );
    moisture_write_word( ctx, MOISTURE_REG_SETTLE_CNT,
                         MOISTURE_SETTLE_CNT_CFG_DEFAULT );

    moisture_write_word( ctx, MOISTURE_REG_RCNT, MOISTURE_RCNT_CFG_DEFAULT );
    moisture_write_word( ctx, MOISTURE_REG_OFFSET, offset );
    moisture_write_word( ctx, MOISTURE_REG_CLOCK_DIVIDERS,
                         MOISTURE_COMBINED_VAL_CH0_DIV | clk_div );

    moisture_write_word( ctx, MOISTURE_REG_DRIVE_CURR,
                         MOISTURE_DRIVE_CURR_CH0 );

    moisture_write_word( ctx, MOISTURE_REG_ERR_CFG, MOISTURE_ALL_ERR_ENABLED );
    moisture_write_word( ctx, MOISTURE_REG_CFG,
                         MOISTURE_REG_CFG_DEFAULT_SETTINGS );

    moisture_write_word( ctx, MOISTURE_REG_MUX_CFG,
                         MOISTURE_INPUT_DEGLITCH_FILT_BWDTH_33MHZ );
}

uint8_t moisture_get_data ( moisture_t *ctx )
{
    uint8_t n_cnt;
    uint32_t rx_data = 0;
    int16_t moisture_data;
    uint32_t clc_data;
    uint16_t tmp;
    uint8_t moisture;

    for ( n_cnt = 0; n_cnt < MOISTURE_SAMPLE_NUM; n_cnt++ )
    {
         tmp = moisture_read_word( ctx, MOISTURE_REG_DATA );
         tmp &= MOISTURE_12_BIT_DATA;
         rx_data += tmp;
         clc_wait_period( );
    }
    rx_data /= MOISTURE_SAMPLE_NUM;
    moisture_data = ( uint16_t )( rx_data );

    if ( moisture_data > ctx->calib_air_data )
    {
        moisture_data = ctx->calib_air_data;
    }
    moisture_data = ctx->calib_air_data  - moisture_data;

    clc_data = ( uint32_t )( moisture_data * 100 );
    clc_data /= ctx->calib_air_data ;
    clc_wait_period( );

    moisture = ( uint8_t )clc_data;

    return moisture;
}

void moisture_cal ( moisture_t *ctx )
{
    uint8_t cnt;
    uint32_t rx_data;
    uint16_t tmp;

    rx_data = 0;
    for ( cnt = 0; cnt < MOISTURE_SAMPLE_NUM; cnt++ )
    {
         tmp = moisture_read_word( ctx, MOISTURE_REG_DATA );
         tmp &= MOISTURE_12_BIT_DATA;
         rx_data += tmp;
         cal_wait_period( );
    }
    ctx->calib_air_data  = ( uint16_t )( rx_data / MOISTURE_SAMPLE_NUM );
}

uint8_t moisture_check_interrupt ( moisture_t *ctx )
{
     return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void cal_wait_period ( )
{
     Delay_10ms( );
}

static void clc_wait_period ( )
{
     Delay_1ms( );
}

// ------------------------------------------------------------------------ END
