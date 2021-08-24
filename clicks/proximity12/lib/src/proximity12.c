/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file proximity12.c
 * @brief Proximity 12 Click Driver.
 */

#include "proximity12.h"

void proximity12_cfg_setup ( proximity12_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->syn  = HAL_PIN_NC;
    cfg->gp1  = HAL_PIN_NC;
    cfg->gp2  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY12_SET_DEV_ADDR;
}

err_t proximity12_init ( proximity12_t *ctx, proximity12_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->gp1, cfg->gp1 );
    digital_out_init( &ctx->gp2, cfg->gp2 );
    digital_out_init( &ctx->syn, cfg->syn );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t proximity12_default_cfg ( proximity12_t *ctx ) 
{
    err_t error_flag = proximity12_check_device_id( ctx );

    error_flag |= proximity12_enable ( ctx, PROXIMITY12_ENABLE_ALS | 
                                            PROXIMITY12_ENABLE_PROX );

    error_flag |= proximity12_set_proximity_filter ( ctx, PROXIMITY12_PROX_FILTER_ENABLE |
                                                          PROXIMITY12_PROX_FILTER_8 );

    error_flag |= proximity12_set_led_isink ( ctx, PROXIMITY12_ISINK_SCALER_1,
                                                   PROXIMITY12_ISINK_CURRENT_5mA );

    error_flag |= proximity12_set_proximity_gain ( ctx, PROXIMITY12_PROX_GAIN_8X );

    error_flag |= proximity12_set_agc_mod_gain ( ctx, PROXIMITY12_AGC_DISABLE_ALL_MOD, 
                                                      PROXIMITY12_MOD_GAIN_2X );

    error_flag |= proximity12_enable_measurement ( ctx, PROXIMITY12_MEAS_MODE0_EN_PROX_DIODE | 
                                                        PROXIMITY12_MEAS_MODE0_ALS_SET_A_DIODE |
                                                        PROXIMITY12_MEAS_MODE0_EN_ALS_DIODE );

    error_flag |= proximity12_enable ( ctx, PROXIMITY12_ENABLE_ALS | 
                                            PROXIMITY12_ENABLE_PROX |
                                            PROXIMITY12_ENABLE_POWER );
    Delay_1sec( );

    return error_flag;
}

err_t proximity12_generic_write ( proximity12_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };
    uint8_t cnt;
    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) 
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t proximity12_generic_read ( proximity12_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t proximity12_check_device_id ( proximity12_t *ctx )
{
    uint8_t dev_id;
    err_t error_flag = proximity12_generic_read( ctx, PROXIMITY12_REG_ID, &dev_id, 1 );

    if ( PROXIMITY12_ID != dev_id )
    {
        return PROXIMITY12_ERROR;
    }

    return error_flag;
}

err_t proximity12_read_proximity ( proximity12_t *ctx, uint16_t *prox_data )
{
    #define PROX_EVAL_CH_1 0x80
    uint8_t rx_buf[ 2 ] = { 0 };

    err_t error_flag = proximity12_generic_read( ctx, PROXIMITY12_REG_PSTATUS, rx_buf, 1 );

    error_flag |= proximity12_wait_ptime( ctx );

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_PCFG6, rx_buf, 1 );

    if ( PROX_EVAL_CH_1 & rx_buf[ 0 ] )
    {
        error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_PDATA1, rx_buf, 2 );
    }
    else
    {
        error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_PDATA0, rx_buf, 2 );
    }

    *prox_data = ( uint16_t ) rx_buf[ 1 ] << 8;
    *prox_data |= ( rx_buf[ 0 ] & 0xFF );

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_PDATAR, rx_buf, 2 );

    return error_flag;
}

err_t proximity12_read_als ( proximity12_t *ctx, proximity12_als_data_t *als )
{
    uint8_t rx_buf[ 3 ] = { 0 };

    err_t error_flag = proximity12_generic_read( ctx, PROXIMITY12_REG_ASTATUS, rx_buf, 1 );

    error_flag |= proximity12_wait_atime( ctx );

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_ADATA0, rx_buf, 3 );

    als->clear = ( uint32_t ) rx_buf[ 2 ] << 16;
    als->clear |= ( uint32_t ) rx_buf[ 1 ] << 8;
    als->clear |= ( rx_buf[ 0 ] & 0xFF );
    als->clear >>= 2;

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_ADATA1, rx_buf, 3 );

    als->red = ( uint32_t ) rx_buf[ 2 ] << 16;
    als->red |= ( uint32_t ) rx_buf[ 1 ] << 8;
    als->red |= ( rx_buf[ 0 ] & 0xFF );
    als->red >>= 2;

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_ADATA2, rx_buf, 3 );

    als->green = ( uint32_t ) rx_buf[ 2 ] << 16;
    als->green |= ( uint32_t ) rx_buf[ 1 ] << 8;
    als->green |= ( rx_buf[ 0 ] & 0xFF );
    als->green >>= 2;

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_ADATA3, rx_buf, 3 );

    als->blue = ( uint32_t ) rx_buf[ 2 ] << 16;
    als->blue |= ( uint32_t ) rx_buf[ 1 ] << 8;
    als->blue |= ( rx_buf[ 0 ] & 0xFF );
    als->blue >>= 2;

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_ADATA4, rx_buf, 3 );

    als->leakage = ( uint32_t ) rx_buf[ 2 ] << 16;
    als->leakage |= ( uint32_t ) rx_buf[ 1 ] << 8;
    als->leakage |= ( rx_buf[ 0 ] & 0xFF );
    als->leakage >>= 2;

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_ADATA5, rx_buf, 3 );

    als->wideband = ( uint32_t ) rx_buf[ 2 ] << 16;
    als->wideband |= ( uint32_t ) rx_buf[ 1 ] << 8;
    als->wideband |= ( rx_buf[ 0 ] & 0xFF );
    als->wideband >>= 2;

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_ADATA6, rx_buf, 3 );

    als->ir1 = ( uint32_t ) rx_buf[ 2 ] << 16;
    als->ir1 |= ( uint32_t ) rx_buf[ 1 ] << 8;
    als->ir1 |= ( rx_buf[ 0 ] & 0xFF );
    als->ir1 >>= 2;

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_ADATA7, rx_buf, 3 );

    als->ir2 = ( uint32_t ) rx_buf[ 2 ] << 16;
    als->ir2 |= ( uint32_t ) rx_buf[ 1 ] << 8;
    als->ir2 |= ( rx_buf[ 0 ] & 0xFF );
    als->ir2 >>= 2;

    return error_flag;
}

err_t proximity12_wait_atime ( proximity12_t *ctx )
{
    #define SINGLE_STEP 2.7127
    uint8_t rx_buf[ 2 ] = { 0 };
    uint16_t astep = 0;
    err_t error_flag = proximity12_generic_read( ctx, PROXIMITY12_REG_ASTEP, rx_buf, 2 );

    astep = ( uint16_t ) rx_buf[ 1 ] << 8;
    astep |= ( rx_buf[ 0 ] & 0xFF );

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_ATIME, rx_buf, 1 );

    float atime = astep * SINGLE_STEP * rx_buf[ 0 ];

    for ( uint32_t cnt = 0; cnt < ( uint32_t ) atime; cnt++ )
    {
        Delay_1us( );
    }
    return error_flag;
}

err_t proximity12_wait_ptime ( proximity12_t *ctx )
{
    #define SINGLE_PULSE_LEN 4
    #define PULSE_LEN_MASK   0x07
    uint8_t rx_buf = 0;
    uint16_t ppulse_len = 0;
    uint16_t ppulse = 0;
    uint32_t ptime = 0;
    err_t error_flag = proximity12_generic_read( ctx, PROXIMITY12_REG_PCFG7, &rx_buf, 1 );

    ppulse_len = SINGLE_PULSE_LEN << ( rx_buf & PULSE_LEN_MASK );

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_PCFG5, &rx_buf, 1 );
    ppulse = rx_buf + 1;

    error_flag |= proximity12_generic_read( ctx, PROXIMITY12_REG_PTIME, &rx_buf, 1 );
    ptime = ppulse_len * ppulse * rx_buf;

    for ( uint32_t cnt = 0; cnt < ptime; cnt++ )
    {
        Delay_1us( );
    }
    return error_flag;
}

err_t proximity12_enable ( proximity12_t *ctx, uint8_t en_mask )
{
    uint8_t tx_data = en_mask & ( PROXIMITY12_ENABLE_FLICKER |
                                  PROXIMITY12_ENABLE_ALS | 
                                  PROXIMITY12_ENABLE_PROX |
                                  PROXIMITY12_ENABLE_POWER );
    return proximity12_generic_write ( ctx, PROXIMITY12_REG_ENABLE, &tx_data, 1 );
}

err_t proximity12_enable_measurement ( proximity12_t *ctx, uint8_t en_mask )
{
    uint8_t tx_data = en_mask & ( PROXIMITY12_MEAS_MODE0_CL_APF_VSYNC |
                                  PROXIMITY12_MEAS_MODE0_EN_PROX_DIODE | 
                                  PROXIMITY12_MEAS_MODE0_ALS_SET_B_DIODE |
                                  PROXIMITY12_MEAS_MODE0_EN_ALS_DIODE );
    return proximity12_generic_write ( ctx, PROXIMITY12_REG_MEAS_MODE0, &tx_data, 1 );
}

err_t proximity12_proximity_calibration ( proximity12_t *ctx )
{
    #define CALIB_TIMEOUT       300
    #define CALIB_START         0x01
    #define CALIB_FINISHED      0x01

    uint8_t tx_buf = CALIB_START;
    err_t error_flag = proximity12_generic_write ( ctx, PROXIMITY12_REG_CALIB, &tx_buf, 1 );
    Delay_100ms( );

    for ( uint16_t cnt = 0; cnt < CALIB_TIMEOUT; cnt++ )
    {
        error_flag |= proximity12_generic_read ( ctx, PROXIMITY12_REG_CALIBSTAT, &tx_buf, 1 );

        if ( tx_buf & CALIB_FINISHED )
        {
            tx_buf = CALIB_FINISHED;
            error_flag |= proximity12_generic_write ( ctx, PROXIMITY12_REG_CALIBSTAT, &tx_buf, 1 );
            return error_flag;
        }
        Delay_10ms( );
    }

    return PROXIMITY12_ERROR;
}

err_t proximity12_set_proximity_filter ( proximity12_t *ctx, uint8_t filter )
{
    filter &= ( PROXIMITY12_PROX_FILTER_ENABLE | PROXIMITY12_PROX_FILTER_8 );
    uint8_t pcfg1 = filter;

    return proximity12_generic_write ( ctx, PROXIMITY12_REG_PCFG1, &pcfg1, 1 );
}

err_t proximity12_set_led_isink ( proximity12_t *ctx, uint8_t scaler, uint8_t current )
{
    scaler &= PROXIMITY12_ISINK_SCALER_2;
    current &= PROXIMITY12_ISINK_CURRENT_7mA;
    uint8_t pcfg2 = ( scaler << 6 ) | ( scaler << 4 ) | current;
    uint8_t pcfg3 = current | ( current << 4 );
    err_t error_flag = proximity12_generic_write ( ctx, PROXIMITY12_REG_PCFG2, &pcfg2, 1 );
    error_flag |= proximity12_generic_write ( ctx, PROXIMITY12_REG_PCFG3, &pcfg3, 1 );

    return error_flag;
}

err_t proximity12_set_proximity_gain ( proximity12_t *ctx, uint8_t gain )
{
    gain &= PROXIMITY12_PROX_GAIN_8X;
    uint8_t pcfg4 = gain | ( gain << 2 );

    return proximity12_generic_write ( ctx, PROXIMITY12_REG_PCFG4, &pcfg4, 1 );
}

err_t proximity12_set_agc_mod_gain ( proximity12_t *ctx, uint8_t en_mask, uint8_t gain )
{
    if ( gain > PROXIMITY12_MOD_GAIN_4096X )
    {
        gain = PROXIMITY12_MOD_GAIN_4096X;
    }
    uint8_t mod_gain = gain | ( gain << 4 );
    err_t error_flag = proximity12_generic_write ( ctx, PROXIMITY12_REG_MOD_GAIN_0_1, &mod_gain, 1 );
    error_flag |= proximity12_generic_write ( ctx, PROXIMITY12_REG_MOD_GAIN_2_3, &mod_gain, 1 );
    error_flag |= proximity12_generic_write ( ctx, PROXIMITY12_REG_MOD_GAIN_4_5, &mod_gain, 1 );
    error_flag |= proximity12_generic_write ( ctx, PROXIMITY12_REG_MOD_GAIN_6_7, &mod_gain, 1 );
    error_flag |= proximity12_generic_write ( ctx, PROXIMITY12_REG_AGC_ENABLE, &en_mask, 1 );

    return error_flag;
}

void proximity12_set_syn_pin ( proximity12_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->syn, state );
}

void proximity12_set_gp1_pin ( proximity12_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->gp1, state );
}

void proximity12_set_gp2_pin ( proximity12_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->gp2, state );
}

uint8_t proximity12_get_int_pin ( proximity12_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
