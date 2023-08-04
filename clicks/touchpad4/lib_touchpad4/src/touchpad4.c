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
 * @file touchpad4.c
 * @brief Touchpad 4 Click Driver.
 */

#include "touchpad4.h"

/**
 * @brief Combine two 8 bit macro.
 * @details Macro to combine two 8 bit data's to form a 16 bit data.
 */
#define BYTES_TO_WORD( msb, lsb )   ( ( ( uint16_t ) msb << 8 ) | ( uint16_t ) lsb )

void touchpad4_cfg_setup ( touchpad4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TOUCHPAD4_SET_DEV_ADDR;
}

err_t touchpad4_init ( touchpad4_t *ctx, touchpad4_cfg_t *cfg ) 
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

    digital_out_init( &ctx->mclr, cfg->mclr );
    digital_in_init( &ctx->rdy, cfg->rdy );
    digital_out_high( &ctx->mclr );
    Delay_100ms( );

    return I2C_MASTER_SUCCESS;
}

err_t touchpad4_default_cfg ( touchpad4_t *ctx ) 
{
    err_t error_flag = TOUCHPAD4_OK;
    
    // Settings for registers 0x30 - 0x39
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TRACKPAD_ATI_MULT_DIV, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TP_ATI_MULTIPLIERS_DIVIDERS_1, 
                                                           TOUCHPAD4_TP_ATI_MULTIPLIERS_DIVIDERS_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TRACKPAD_ATI_COMP_DIV, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TP_COMPENSATION_DIV_1, 
                                                           TOUCHPAD4_TP_COMPENSATION_DIV_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TRACKPAD_ATI_TARGET, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TP_ATI_TARGET_1, 
                                                           TOUCHPAD4_TP_ATI_TARGET_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TRACKPAD_REF_DRIFT_LIMIT, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TP_REF_DRIFT_LIMIT_1, 
                                                           TOUCHPAD4_TP_REF_DRIFT_LIMIT_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TRACKPAD_MIN_CNT_REATI_VAL, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TP_MIN_COUNT_REATI_1, 
                                                           TOUCHPAD4_TP_MIN_COUNT_REATI_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_REATI_RETRY_TIME, 
                                           BYTES_TO_WORD ( TOUCHPAD4_REATI_RETRY_TIME_1, 
                                                           TOUCHPAD4_REATI_RETRY_TIME_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_ATI_MULT_DIV, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_ATI_MULTIPLIERS_DIVIDERS_1, 
                                                           TOUCHPAD4_ALP_ATI_MULTIPLIERS_DIVIDERS_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_ATI_COMP_DIV, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_COMPENSATION_DIV_1, 
                                                           TOUCHPAD4_ALP_COMPENSATION_DIV_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_ATI_TARGET, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_ATI_TARGET_1, 
                                                           TOUCHPAD4_ALP_ATI_TARGET_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_ATI_DRIFT_LIMIT, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_LTA_DRIFT_LIMIT_1, 
                                                           TOUCHPAD4_ALP_LTA_DRIFT_LIMIT_0 ) );
    // Settings for registers 0x3A - 0x3B
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_ATI_COMP_A, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_COMPENSATION_A_1, 
                                                           TOUCHPAD4_ALP_COMPENSATION_A_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_ATI_COMP_B, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_COMPENSATION_B_1, 
                                                           TOUCHPAD4_ALP_COMPENSATION_B_0 ) );
    
    // Settings for registers 0x40 - 0x4A
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ACTIVE_MODE_REPORT_RATE, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ACTIVE_MODE_REPORT_RATE_1, 
                                                           TOUCHPAD4_ACTIVE_MODE_REPORT_RATE_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_IDLE_TOUCH_MODE_REPORT_RATE, 
                                           BYTES_TO_WORD ( TOUCHPAD4_IDLE_TOUCH_MODE_REPORT_RATE_1, 
                                                           TOUCHPAD4_IDLE_TOUCH_MODE_REPORT_RATE_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_IDLE_MODE_REPORT_RATE, 
                                           BYTES_TO_WORD ( TOUCHPAD4_IDLE_MODE_REPORT_RATE_1, 
                                                           TOUCHPAD4_IDLE_MODE_REPORT_RATE_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_LP1_MODE_REPORT_RATE, 
                                           BYTES_TO_WORD ( TOUCHPAD4_LP1_MODE_REPORT_RATE_1, 
                                                           TOUCHPAD4_LP1_MODE_REPORT_RATE_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_LP2_MODE_REPORT_RATE, 
                                           BYTES_TO_WORD ( TOUCHPAD4_LP2_MODE_REPORT_RATE_1, 
                                                           TOUCHPAD4_LP2_MODE_REPORT_RATE_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ACTIVE_MODE_TIMEOUT, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ACTIVE_MODE_TIMEOUT_1, 
                                                           TOUCHPAD4_ACTIVE_MODE_TIMEOUT_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_IDLE_TOUCH_MODE_TIMEOUT, 
                                           BYTES_TO_WORD ( TOUCHPAD4_IDLE_TOUCH_MODE_TIMEOUT_1, 
                                                           TOUCHPAD4_IDLE_TOUCH_MODE_TIMEOUT_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_IDLE_MODE_TIMEOUT, 
                                           BYTES_TO_WORD ( TOUCHPAD4_IDLE_MODE_TIMEOUT_1, 
                                                           TOUCHPAD4_IDLE_MODE_TIMEOUT_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_LP1_MODE_TIMEOUT, 
                                           BYTES_TO_WORD ( TOUCHPAD4_LP1_MODE_TIMEOUT_1, 
                                                           TOUCHPAD4_LP1_MODE_TIMEOUT_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_REFERENCE_UPDATE_TIME, 
                                           BYTES_TO_WORD ( TOUCHPAD4_REF_UPDATE_TIME_1, 
                                                           TOUCHPAD4_REF_UPDATE_TIME_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_I2C_TIMEOUT, 
                                           BYTES_TO_WORD ( TOUCHPAD4_I2C_TIMEOUT_1, 
                                                           TOUCHPAD4_I2C_TIMEOUT_0 ) );
    
    // Settings for registers 0x50 - 0x5B
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_SYSTEM_CONTROL, 
                                           BYTES_TO_WORD ( TOUCHPAD4_SYSTEM_CONTROL_1, 
                                                           TOUCHPAD4_SYSTEM_CONTROL_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_CONFIG_SETTINGS, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CONFIG_SETTINGS1, 
                                                           TOUCHPAD4_CONFIG_SETTINGS0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_OTHER_SETTINGS, 
                                           BYTES_TO_WORD ( TOUCHPAD4_OTHER_SETTINGS_1, 
                                                           TOUCHPAD4_OTHER_SETTINGS_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TOUCH_CLEAR_SET_THRESH, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TRACKPAD_TOUCH_CLEAR_THRESHOLD, 
                                                           TOUCHPAD4_TRACKPAD_TOUCH_SET_THRESHOLD ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_THRESH, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_THRESHOLD_1, 
                                                           TOUCHPAD4_ALP_THRESHOLD_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_OPEN_0, 
                                           BYTES_TO_WORD ( TOUCHPAD4_OPEN_0_1, 
                                                           TOUCHPAD4_OPEN_0_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_CLEAR_SET_DEBOUNCE, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_CLEAR_DEBOUNCE, 
                                                           TOUCHPAD4_ALP_SET_DEBOUNCE ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_OPEN_1, 
                                           BYTES_TO_WORD ( TOUCHPAD4_OPEN_1_1, 
                                                           TOUCHPAD4_OPEN_1_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TRACKPAD_CONVER_FREQ, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TP_CONVERSION_FREQUENCY_FRACTION_VALUE, 
                                                           TOUCHPAD4_TP_CONVERSION_FREQUENCY_UP_PASS_LENGTH ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_CONVER_FREQ, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_CONVERSION_FREQUENCY_FRACTION_VALUE, 
                                                           TOUCHPAD4_ALP_CONVERSION_FREQUENCY_UP_PASS_LENGTH ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TRACKPAD_HW_SETTINGS, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TRACKPAD_HARDWARE_SETTINGS_1, 
                                                           TOUCHPAD4_TRACKPAD_HARDWARE_SETTINGS_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_HW_SETTINGS, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_HARDWARE_SETTINGS_1, 
                                                           TOUCHPAD4_ALP_HARDWARE_SETTINGS_0 ) );
    
    // Settings for registers 0x60 - 0x69
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TOTAL_RXS_TRACKPAD_SETTINGS, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TRACKPAD_SETTINGS_0_1, 
                                                           TOUCHPAD4_TRACKPAD_SETTINGS_0_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_MAX_MULTITOUCHES_TOTAL_TXS, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TRACKPAD_SETTINGS_1_1, 
                                                           TOUCHPAD4_TRACKPAD_SETTINGS_1_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_X_RES, 
                                           BYTES_TO_WORD ( TOUCHPAD4_X_RESOLUTION_1, 
                                                           TOUCHPAD4_X_RESOLUTION_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_Y_RES, 
                                           BYTES_TO_WORD ( TOUCHPAD4_Y_RESOLUTION_1, 
                                                           TOUCHPAD4_Y_RESOLUTION_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_XY_DYNAMIC_FILTER_BOT_SPEED, 
                                           BYTES_TO_WORD ( TOUCHPAD4_XY_DYNAMIC_FILTER_BOTTOM_SPEED_1, 
                                                           TOUCHPAD4_XY_DYNAMIC_FILTER_BOTTOM_SPEED_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_XY_DYNAMIC_FILTER_TOP_SPEED, 
                                           BYTES_TO_WORD ( TOUCHPAD4_XY_DYNAMIC_FILTER_TOP_SPEED_1, 
                                                           TOUCHPAD4_XY_DYNAMIC_FILTER_TOP_SPEED_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_STATIC_FILTER_VAL_DYNAMIC_FILTER_BOT, 
                                           BYTES_TO_WORD ( TOUCHPAD4_XY_DYNAMIC_FILTER_STATIC_FILTER_BETA, 
                                                           TOUCHPAD4_XY_DYNAMIC_FILTER_BOTTOM_BETA ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_FINGER_SPLIT_STAT_TOUCH_MOVE_THRESH, 
                                           BYTES_TO_WORD ( TOUCHPAD4_FINGER_SPLIT_FACTOR, 
                                                           TOUCHPAD4_STATIONARY_TOUCH_MOV_THRESHOLD ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_X_TRIM_VALUE, 
                                           BYTES_TO_WORD ( TOUCHPAD4_X_TRIM_VALUE_1, 
                                                           TOUCHPAD4_X_TRIM_VALUE_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_Y_TRIM_VALUE, 
                                           BYTES_TO_WORD ( TOUCHPAD4_Y_TRIM_VALUE_1, 
                                                           TOUCHPAD4_Y_TRIM_VALUE_0 ) );
    
    // Settings for registers 0x70 - 0x73
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_COUNT_FILTER_BETA, 
                                           BYTES_TO_WORD ( TOUCHPAD4_OPEN_0, 
                                                           TOUCHPAD4_ALP_COUNT_FILTER_BETA_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_LP2_LP1_BETA, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_LTA_BETA_LP2, 
                                                           TOUCHPAD4_ALP_LTA_BETA_LP1 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_SETUP, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_SETUP_1, 
                                                           TOUCHPAD4_ALP_SETUP_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_ALP_TX_ENABLE, 
                                           BYTES_TO_WORD ( TOUCHPAD4_ALP_TX_ENABLE_1, 
                                                           TOUCHPAD4_ALP_TX_ENABLE_0 ) );
    
    // Settings for register 0x74
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_SETTINGS_MAJOR_MINOR_VER, 
                                           BYTES_TO_WORD ( TOUCHPAD4_MAJOR_VERSION, 
                                                           TOUCHPAD4_MINOR_VERSION ) );
    
    // Settings for registers 0x80 - 0x87
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_GESTURE_ENABLE, 
                                           BYTES_TO_WORD ( TOUCHPAD4_GESTURE_ENABLE_1, 
                                                           TOUCHPAD4_GESTURE_ENABLE_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TAP_TIME, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TAP_TIME_1, 
                                                           TOUCHPAD4_TAP_TIME_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_TAP_DIST, 
                                           BYTES_TO_WORD ( TOUCHPAD4_TAP_DISTANCE_1, 
                                                           TOUCHPAD4_TAP_DISTANCE_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_HOLD_TIME, 
                                           BYTES_TO_WORD ( TOUCHPAD4_HOLD_TIME_1, 
                                                           TOUCHPAD4_HOLD_TIME_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_SWIPE_TIME, 
                                           BYTES_TO_WORD ( TOUCHPAD4_SWIPE_TIME_1, 
                                                           TOUCHPAD4_SWIPE_TIME_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_SWIPE_X_DIST, 
                                           BYTES_TO_WORD ( TOUCHPAD4_SWIPE_X_DISTANCE_1, 
                                                           TOUCHPAD4_SWIPE_X_DISTANCE_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_SWIPE_Y_DIST, 
                                           BYTES_TO_WORD ( TOUCHPAD4_SWIPE_Y_DISTANCE_1, 
                                                           TOUCHPAD4_SWIPE_Y_DISTANCE_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_SWIPE_ANGLE, 
                                           BYTES_TO_WORD ( TOUCHPAD4_GESTURE_OPEN_0, 
                                                           TOUCHPAD4_SWIPE_ANGLE_0 ) );
    
    // Settings for registers 0x90 - 0x96
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_1_0, 
                                           BYTES_TO_WORD ( TOUCHPAD4_RX_TX_MAP_1, 
                                                           TOUCHPAD4_RX_TX_MAP_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_3_2, 
                                           BYTES_TO_WORD ( TOUCHPAD4_RX_TX_MAP_3, 
                                                           TOUCHPAD4_RX_TX_MAP_2 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_5_4, 
                                           BYTES_TO_WORD ( TOUCHPAD4_RX_TX_MAP_5, 
                                                           TOUCHPAD4_RX_TX_MAP_4 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_7_6, 
                                           BYTES_TO_WORD ( TOUCHPAD4_RX_TX_MAP_7, 
                                                           TOUCHPAD4_RX_TX_MAP_6 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_9_8, 
                                           BYTES_TO_WORD ( TOUCHPAD4_RX_TX_MAP_9, 
                                                           TOUCHPAD4_RX_TX_MAP_8 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_11_10, 
                                           BYTES_TO_WORD ( TOUCHPAD4_RX_TX_MAP_11, 
                                                           TOUCHPAD4_RX_TX_MAP_10 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_RXTX_MAP_13_12, 
                                           BYTES_TO_WORD ( TOUCHPAD4_RX_TX_MAP_13, 
                                                           TOUCHPAD4_RX_TX_MAP_12 ) );
    
    // Settings for registers 0xA0 - 0xAE
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE0, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_1_CYCLE_0, 
                                                           TOUCHPAD4_PLACEHOLDER_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE0, 
                                           BYTES_TO_WORD ( TOUCHPAD4_PLACEHOLDER_1, 
                                                           TOUCHPAD4_CH_2_CYCLE_0 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE1, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_2_CYCLE_1, 
                                                           TOUCHPAD4_CH_1_CYCLE_1 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE2, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_1_CYCLE_2, 
                                                           TOUCHPAD4_PLACEHOLDER_2 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE2, 
                                           BYTES_TO_WORD ( TOUCHPAD4_PLACEHOLDER_3, 
                                                           TOUCHPAD4_CH_2_CYCLE_2 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE3, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_2_CYCLE_3, 
                                                           TOUCHPAD4_CH_1_CYCLE_3 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE4, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_1_CYCLE_4, 
                                                           TOUCHPAD4_PLACEHOLDER_4 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE4, 
                                           BYTES_TO_WORD ( TOUCHPAD4_PLACEHOLDER_5, 
                                                           TOUCHPAD4_CH_2_CYCLE_4 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE5, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_2_CYCLE_5, 
                                                           TOUCHPAD4_CH_1_CYCLE_5 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE6, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_1_CYCLE_6, 
                                                           TOUCHPAD4_PLACEHOLDER_6 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE6, 
                                           BYTES_TO_WORD ( TOUCHPAD4_PLACEHOLDER_7, 
                                                           TOUCHPAD4_CH_2_CYCLE_6 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE7, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_2_CYCLE_7, 
                                                           TOUCHPAD4_CH_1_CYCLE_7 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE8, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_1_CYCLE_8, 
                                                           TOUCHPAD4_PLACEHOLDER_8 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE8, 
                                           BYTES_TO_WORD ( TOUCHPAD4_PLACEHOLDER_9, 
                                                           TOUCHPAD4_CH_2_CYCLE_8 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE9, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_2_CYCLE_9, 
                                                           TOUCHPAD4_CH_1_CYCLE_9 ) );
    
    // Settings for registers 0xB0 - 0xBB
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE10, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_1_CYCLE_10, 
                                                           TOUCHPAD4_PLACEHOLDER_10 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE10, 
                                           BYTES_TO_WORD ( TOUCHPAD4_PLACEHOLDER_11, 
                                                           TOUCHPAD4_CH_2_CYCLE_10 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE11, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_2_CYCLE_11, 
                                                           TOUCHPAD4_CH_1_CYCLE_11 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE12, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_1_CYCLE_12, 
                                                           TOUCHPAD4_PLACEHOLDER_12 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE12, 
                                           BYTES_TO_WORD ( TOUCHPAD4_PLACEHOLDER_13, 
                                                           TOUCHPAD4_CH_2_CYCLE_12 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE13, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_2_CYCLE_13, 
                                                           TOUCHPAD4_CH_1_CYCLE_13 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE14, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_1_CYCLE_14, 
                                                           TOUCHPAD4_PLACEHOLDER_14 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE14, 
                                           BYTES_TO_WORD ( TOUCHPAD4_PLACEHOLDER_15, 
                                                           TOUCHPAD4_CH_2_CYCLE_14 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE15, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_2_CYCLE_15, 
                                                           TOUCHPAD4_CH_1_CYCLE_15 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_1st_CHANNEL_FOR_CYCLE16, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_1_CYCLE_16, 
                                                           TOUCHPAD4_PLACEHOLDER_16 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd_CHANNEL_FOR_CYCLE16, 
                                           BYTES_TO_WORD ( TOUCHPAD4_PLACEHOLDER_17, 
                                                           TOUCHPAD4_CH_2_CYCLE_16 ) );
    error_flag |= touchpad4_generic_write( ctx, TOUCHPAD4_REG_2nd1st_CHANNEL_FOR_CYCLE17, 
                                           BYTES_TO_WORD ( TOUCHPAD4_CH_2_CYCLE_17, 
                                                           TOUCHPAD4_CH_1_CYCLE_17 ) );
    
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );

    return error_flag;
}

err_t touchpad4_generic_write ( touchpad4_t *ctx, uint8_t reg, uint16_t tx_data ) 
{
    uint8_t data_buf[ 3 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_data;
    data_buf[ 2 ] = tx_data >> 8;
    
    if ( ctx->event_enabled )
    {
        while ( digital_in_read( &ctx->rdy ) );
        Delay_1ms( );
    }
    
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 3 );
    
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    
    return error_flag;
}

err_t touchpad4_generic_read ( touchpad4_t *ctx, uint8_t reg, uint16_t *rx_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    
    if ( ctx->event_enabled )
    {
        while ( digital_in_read( &ctx->rdy ) );
        Delay_1ms( );
    }

    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );

    *rx_data = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    
    return error_flag;
}

uint8_t touchpad4_get_ready ( touchpad4_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

void touchpad4_set_rst ( touchpad4_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->mclr );
    }
    else
    {
        digital_out_low( &ctx->mclr );
    }
}

void touchpad4_reset ( touchpad4_t *ctx )
{
    uint16_t temp_data = 0;
    ctx->event_enabled = 0;
    touchpad4_generic_write( ctx, TOUCHPAD4_REG_GESTURES, temp_data );
    
    temp_data = 0x0200;
    touchpad4_generic_write( ctx, TOUCHPAD4_REG_SYSTEM_CONTROL, temp_data );
    do 
    {
        touchpad4_generic_read( ctx, TOUCHPAD4_REG_INFO_FLAGS, &temp_data );
        temp_data &= 0x0080;
    } 
    while ( !temp_data );
    
    ctx->event_enabled = 1;
}

err_t touchpad4_get_touch ( touchpad4_t *ctx, touchpad4_info_t *touch_info )
{
    uint16_t temp_data = 0;
    
    touchpad4_generic_read( ctx, TOUCHPAD4_REG_INFO_FLAGS, &temp_data );
    touch_info->number_of_touches = ( temp_data >> 8 ) & 3;
    
    if ( touch_info->number_of_touches > 0 )
    {
        for ( uint8_t touch_index = 0; touch_index < touch_info->number_of_touches; touch_index++ )
        {
            touchpad4_generic_read( ctx, TOUCHPAD4_REG_FINGER1_X + ( touch_index * 4 ), &temp_data );
            touch_info->touches[ touch_index ].x = temp_data;
            touchpad4_generic_read( ctx, TOUCHPAD4_REG_FINGER1_Y + ( touch_index * 4 ), &temp_data );
            touch_info->touches[ touch_index ].y = temp_data;
            touchpad4_generic_read( ctx, TOUCHPAD4_REG_FINGER1_TOUCH_STR + ( touch_index * 4 ), &temp_data );
            touch_info->touches[ touch_index ].strength = temp_data;
            touchpad4_generic_read( ctx, TOUCHPAD4_REG_FINGER1_AREA + ( touch_index * 4 ), &temp_data );
            touch_info->touches[ touch_index ].area = temp_data;
        }
    }    
    
    return TOUCHPAD4_OK;
}

err_t touchpad_get_channels ( touchpad4_t *ctx, uint32_t *channels )
{
    uint32_t ch_status = 0;
    uint16_t temp_data = 0;
    
    err_t error_flag = touchpad4_generic_read( ctx, TOUCHPAD4_REG_TOUCH_STATUS1, &temp_data );
    ch_status = temp_data;
    ch_status <<= 16;
    error_flag |= touchpad4_generic_read( ctx, TOUCHPAD4_REG_TOUCH_STATUS0, &temp_data );
    ch_status |= temp_data;
    
    *channels = ch_status;
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
