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
 * @file capslider3.c
 * @brief Cap Slider 3 Click Driver.
 */

#include "capslider3.h"

void capslider3_cfg_setup ( capslider3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CAPSLIDER3_DEVICE_ADDRESS;
}

err_t capslider3_init ( capslider3_t *ctx, capslider3_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    digital_in_init( &ctx->rdy, cfg->rdy );

    return I2C_MASTER_SUCCESS;
}

err_t capslider3_default_cfg ( capslider3_t *ctx ) 
{
    err_t error_flag = CAPSLIDER3_OK;
    uint16_t data_buf[ 10 ] = { 0 };

    if ( CAPSLIDER3_ERROR == capslider3_check_communication ( ctx ) )
    {
        return CAPSLIDER3_ERROR;
    }
    data_buf[ 0 ] = CAPSLIDER3_S0_SETUP_0;
    data_buf[ 1 ] = CAPSLIDER3_S0_CONV_FREQ_SETUP;
    data_buf[ 2 ] = CAPSLIDER3_S0_PROX_CONTROL;
    data_buf[ 3 ] = CAPSLIDER3_S0_PROX_INPUT_CONTROL;
    data_buf[ 4 ] = CAPSLIDER3_S0_PATTERN_DEFINITIONS;
    data_buf[ 5 ] = CAPSLIDER3_S0_PATTERN_SELECT;
    data_buf[ 6 ] = CAPSLIDER3_S0_ATI_SETUP;
    data_buf[ 7 ] = CAPSLIDER3_S0_ATI_BASE;
    data_buf[ 8 ] = CAPSLIDER3_S0_ATI_MULTI_SELECTION;
    data_buf[ 9 ] = CAPSLIDER3_S0_COMPENSATION;
    error_flag |= capslider3_write_regs ( ctx, CAPSLIDER3_REG_S0_SETUP_0, data_buf, 10 );
    data_buf[ 0 ] = CAPSLIDER3_S1_SETUP_0;
    data_buf[ 1 ] = CAPSLIDER3_S1_CONV_FREQ_SETUP;
    data_buf[ 2 ] = CAPSLIDER3_S1_PROX_CONTROL;
    data_buf[ 3 ] = CAPSLIDER3_S1_PROX_INPUT_CONTROL;
    data_buf[ 4 ] = CAPSLIDER3_S1_PATTERN_DEFINITIONS;
    data_buf[ 5 ] = CAPSLIDER3_S1_PATTERN_SELECT;
    data_buf[ 6 ] = CAPSLIDER3_S1_ATI_SETUP;
    data_buf[ 7 ] = CAPSLIDER3_S1_ATI_BASE;
    data_buf[ 8 ] = CAPSLIDER3_S1_ATI_MULTI_SELECTION;
    data_buf[ 9 ] = CAPSLIDER3_S1_COMPENSATION;
    error_flag |= capslider3_write_regs ( ctx, CAPSLIDER3_REG_S1_SETUP_0, data_buf, 10 );
    data_buf[ 0 ] = CAPSLIDER3_S2_SETUP_0;
    data_buf[ 1 ] = CAPSLIDER3_S2_CONV_FREQ_SETUP;
    data_buf[ 2 ] = CAPSLIDER3_S2_PROX_CONTROL;
    data_buf[ 3 ] = CAPSLIDER3_S2_PROX_INPUT_CONTROL;
    data_buf[ 4 ] = CAPSLIDER3_S2_PATTERN_DEFINITIONS;
    data_buf[ 5 ] = CAPSLIDER3_S2_PATTERN_SELECT;
    data_buf[ 6 ] = CAPSLIDER3_S2_ATI_SETUP;
    data_buf[ 7 ] = CAPSLIDER3_S2_ATI_BASE;
    data_buf[ 8 ] = CAPSLIDER3_S2_ATI_MULTI_SELECTION;
    data_buf[ 9 ] = CAPSLIDER3_S2_COMPENSATION;
    error_flag |= capslider3_write_regs ( ctx, CAPSLIDER3_REG_S2_SETUP_0, data_buf, 10 );
    data_buf[ 0 ] = CAPSLIDER3_CH0_SETUP_0;
    data_buf[ 1 ] = CAPSLIDER3_CH0_PROX_SETTINGS;
    data_buf[ 2 ] = CAPSLIDER3_CH0_TOUCH_SETTINGS;
    data_buf[ 3 ] = CAPSLIDER3_CH0_FOLLOWER_WEIGHT;
    error_flag |= capslider3_write_regs ( ctx, CAPSLIDER3_REG_CH0_SETUP_0, data_buf, 4 );
    data_buf[ 0 ] = CAPSLIDER3_CH1_SETUP_0;
    data_buf[ 1 ] = CAPSLIDER3_CH1_PROX_SETTINGS;
    data_buf[ 2 ] = CAPSLIDER3_CH1_TOUCH_SETTINGS;
    data_buf[ 3 ] = CAPSLIDER3_CH1_FOLLOWER_WEIGHT;
    error_flag |= capslider3_write_regs ( ctx, CAPSLIDER3_REG_CH1_SETUP_0, data_buf, 4 );
    data_buf[ 0 ] = CAPSLIDER3_CH2_SETUP_0;
    data_buf[ 1 ] = CAPSLIDER3_CH2_PROX_SETTINGS;
    data_buf[ 2 ] = CAPSLIDER3_CH2_TOUCH_SETTINGS;
    data_buf[ 3 ] = CAPSLIDER3_CH2_FOLLOWER_WEIGHT;
    error_flag |= capslider3_write_regs ( ctx, CAPSLIDER3_REG_CH2_SETUP_0, data_buf, 4 );
    data_buf[ 0 ] = CAPSLIDER3_SLIDER_SETUP_CALIBRATION;
    data_buf[ 1 ] = CAPSLIDER3_SLIDER_CALIBRATION_BOT_SPEED;
    data_buf[ 2 ] = CAPSLIDER3_SLIDER_TOP_SPEED;
    data_buf[ 3 ] = CAPSLIDER3_SLIDER_RESOLUTION;
    data_buf[ 4 ] = CAPSLIDER3_SLIDER_EN_MASK;
    data_buf[ 5 ] = CAPSLIDER3_SLIDER_EN_STATUS_POINTER;
    data_buf[ 6 ] = CAPSLIDER3_SLIDER_DELTA_LINK_0;
    data_buf[ 7 ] = CAPSLIDER3_SLIDER_DELTA_LINK_1;
    data_buf[ 8 ] = CAPSLIDER3_SLIDER_DELTA_LINK_2;
    error_flag |= capslider3_write_regs ( ctx, CAPSLIDER3_REG_SLIDER_SETUP_CALIBRATION, data_buf, 9 );
    data_buf[ 0 ] = CAPSLIDER3_GESTURE_ENABLE;
    data_buf[ 1 ] = CAPSLIDER3_GESTURE_MINIMUM_TIME;
    data_buf[ 2 ] = CAPSLIDER3_GESTURE_MAX_TAP_TIME;
    data_buf[ 3 ] = CAPSLIDER3_GESTURE_MAX_SWIPE_TIME;
    data_buf[ 4 ] = CAPSLIDER3_GESTURE_MIN_HOLD_TIME;
    data_buf[ 5 ] = CAPSLIDER3_GESTURE_MAX_TAP_DISTANCE;
    data_buf[ 6 ] = CAPSLIDER3_GESTURE_MIN_SWIPE_DISTANCE;
    error_flag |= capslider3_write_regs ( ctx, CAPSLIDER3_REG_GESTURE_ENABLE, data_buf, 7 );
    data_buf[ 0 ] = CAPSLIDER3_COUNTS_FILTER_BETA;
    data_buf[ 1 ] = CAPSLIDER3_LTA_FILTER_BETA;
    data_buf[ 2 ] = CAPSLIDER3_LTA_FAST_FILTER_BETA;
    data_buf[ 3 ] = CAPSLIDER3_ACT_MOVE_LTA_FILTER_BETA;
    data_buf[ 4 ] = CAPSLIDER3_FAST_FILTER_BAND;
    error_flag |= capslider3_write_regs ( ctx, CAPSLIDER3_REG_COUNTS_FILTER_BETA, data_buf, 5 );
    data_buf[ 0 ] = CAPSLIDER3_SYSTEM_CONTROL;
    data_buf[ 1 ] = CAPSLIDER3_NORMAL_POWER_REPORT_RATE;
    data_buf[ 2 ] = CAPSLIDER3_LOW_POWER_REPORT_RATE;
    data_buf[ 3 ] = CAPSLIDER3_ULP_REPORT_RATE;
    data_buf[ 4 ] = CAPSLIDER3_HALT_MODE_REPORT_RATE;
    data_buf[ 5 ] = CAPSLIDER3_POWER_MODE_TIMEOUT;
    error_flag |= capslider3_write_regs ( ctx, CAPSLIDER3_REG_SYSTEM_CONTROL, data_buf, 6 );
    data_buf[ 0 ] = CAPSLIDER3_OUTA_MASK;
    data_buf[ 1 ] = CAPSLIDER3_I2C_TRANS_TIMEOUT;
    data_buf[ 2 ] = CAPSLIDER3_EVENT_TIMEOUTS;
    data_buf[ 3 ] = CAPSLIDER3_EVENT_EN_ACTIVATION_THRESHOLD;
    data_buf[ 4 ] = CAPSLIDER3_RELEASE_UI_MOVE_TIMEOUT;
    error_flag |= capslider3_write_regs ( ctx, CAPSLIDER3_REG_OUTA_MASK, data_buf, 5 );

    error_flag |= capslider3_read_reg ( ctx, CAPSLIDER3_REG_SYSTEM_CONTROL, data_buf );
    data_buf[ 0 ] |= CAPSLIDER3_SYSTEM_CONTROL_RE_ATI_TRIGGER;
    error_flag |= capslider3_write_reg ( ctx, CAPSLIDER3_REG_SYSTEM_CONTROL, data_buf[ 0 ] );
    
    error_flag |= capslider3_read_reg ( ctx, CAPSLIDER3_REG_SYSTEM_STATUS, data_buf );
    while ( data_buf[ 0 ] & CAPSLIDER3_SYSTEM_STATUS_ATI_ACTIVE )
    {
        error_flag |= capslider3_read_reg ( ctx, CAPSLIDER3_REG_SYSTEM_STATUS, data_buf );
    }
    
    return error_flag;
}

err_t capslider3_write_reg ( capslider3_t *ctx, uint8_t reg, uint16_t data_in )
{
    return capslider3_write_regs ( ctx, reg, &data_in, 1 );
}

err_t capslider3_write_regs ( capslider3_t *ctx, uint8_t reg, uint16_t *data_in, uint8_t len )
{
    err_t error_flag = CAPSLIDER3_OK;
    uint32_t timeout_cnt = 0;
    uint8_t cnt = 0;
    uint8_t data_buf[ 101 ] = { 0 };
    if ( ( len > 50 ) || ( NULL == data_in ) )
    {
        return CAPSLIDER3_ERROR;
    }
    data_buf[ 0 ] = reg;
    for ( cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt * 2 + 1 ] = ( uint8_t ) ( data_in[ cnt ] & 0xFF );
        data_buf[ cnt * 2 + 2 ] = ( uint8_t ) ( ( data_in[ cnt ] >> 8 ) & 0xFF );
    }
    // Waiting for a communication window entrance
    while ( capslider3_get_rdy_pin ( ctx ) )
    {
        if ( ++timeout_cnt > CAPSLIDER3_RDY_TIMEOUT )
        {
            return CAPSLIDER3_ERROR;
        }
        Delay_1ms ( );
    }
    error_flag |= i2c_master_write( &ctx->i2c, data_buf, len * 2 + 1 );
    Delay_1ms ( );
    return error_flag;
}

err_t capslider3_read_reg ( capslider3_t *ctx, uint8_t reg, uint16_t *data_out )
{
    return capslider3_read_regs ( ctx, reg, data_out, 1 );
}

err_t capslider3_read_regs ( capslider3_t *ctx, uint8_t reg, uint16_t *data_out, uint8_t len )
{
    err_t error_flag = CAPSLIDER3_OK;
    uint32_t timeout_cnt = 0;
    uint8_t cnt = 0;
    uint8_t data_buf[ 100 ] = { 0 };
    if ( ( len > 50 ) || ( NULL == data_out ) )
    {
        return CAPSLIDER3_ERROR;
    }
    // Waiting for a communication window entrance
    while ( capslider3_get_rdy_pin ( ctx ) )
    {
        if ( ++timeout_cnt > CAPSLIDER3_RDY_TIMEOUT )
        {
            return CAPSLIDER3_ERROR;
        }
        Delay_1ms ( );
    }
    error_flag |= i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len * 2 );
    if ( CAPSLIDER3_OK == error_flag )
    {
        for ( cnt = 0; cnt < len; cnt++ )
        {
            data_out[ cnt ] = ( ( uint16_t ) data_buf[ cnt * 2 + 1 ] << 8 ) | data_buf[ cnt * 2 ];
        }
    }
    Delay_1ms ( );
    return error_flag;
}

uint8_t capslider3_get_rdy_pin ( capslider3_t *ctx )
{
    return digital_in_read ( &ctx->rdy ) & 1;
}

err_t capslider3_check_communication ( capslider3_t *ctx )
{
    uint16_t product_num = 0;
    if ( CAPSLIDER3_OK == capslider3_read_reg ( ctx, CAPSLIDER3_REG_PROD_NUM, &product_num ) )
    {
        if ( CAPSLIDER3_PRODUCT_NUM == product_num )
        {
            return CAPSLIDER3_OK;
        }
    }
    return CAPSLIDER3_ERROR;
}

err_t capslider3_sw_reset ( capslider3_t *ctx )
{
    err_t error_flag = CAPSLIDER3_OK;
    uint16_t sys_ctrl = 0;
    uint16_t sys_stat = 0;
    error_flag |= capslider3_read_reg ( ctx, CAPSLIDER3_REG_SYSTEM_CONTROL, &sys_ctrl );
    if ( CAPSLIDER3_OK == error_flag )
    {
        sys_ctrl |= CAPSLIDER3_SYSTEM_CONTROL_SOFT_RESET_TRIGGER;
        error_flag |= capslider3_write_reg ( ctx, CAPSLIDER3_REG_SYSTEM_CONTROL, sys_ctrl );
        Delay_100ms ( );
    }
    if ( CAPSLIDER3_OK == error_flag )
    {
        error_flag |= capslider3_read_reg ( ctx, CAPSLIDER3_REG_SYSTEM_STATUS, &sys_stat );
    }
    if ( CAPSLIDER3_OK == error_flag )
    {
        if ( sys_stat & CAPSLIDER3_SYSTEM_STATUS_RESET_EVENT )
        {
            sys_ctrl &= ( ~CAPSLIDER3_SYSTEM_CONTROL_SOFT_RESET_MASK );
            sys_ctrl |= CAPSLIDER3_SYSTEM_CONTROL_ACK_RESET_ACK;
            error_flag |= capslider3_write_reg ( ctx, CAPSLIDER3_REG_SYSTEM_CONTROL, sys_ctrl );
        }
    }
    return error_flag;
}

err_t capslider3_read_data ( capslider3_t *ctx, capslider3_data_t *data_out )
{
    err_t error_flag = CAPSLIDER3_OK;
    uint16_t sys_info[ 9 ] = { 0 };
    if ( NULL == data_out )
    {
        return CAPSLIDER3_ERROR;
    }
    error_flag |= capslider3_read_regs ( ctx, CAPSLIDER3_REG_SYSTEM_STATUS, sys_info, 9 );
    if ( CAPSLIDER3_OK == error_flag )
    {
        data_out->sys_status = sys_info[ 0 ];
        data_out->gestures = sys_info[ 1 ];
        data_out->slider = sys_info[ 2 ];
        data_out->ch0_counts = sys_info[ 3 ];
        data_out->ch0_lta = sys_info[ 4 ];
        data_out->ch1_counts = sys_info[ 5 ];
        data_out->ch1_lta = sys_info[ 6 ];
        data_out->ch2_counts = sys_info[ 7 ];
        data_out->ch2_lta = sys_info[ 8 ];
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
