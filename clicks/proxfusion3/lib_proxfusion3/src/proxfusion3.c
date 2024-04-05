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
 * @file proxfusion3.c
 * @brief ProxFusion 3 Click Driver.
 */

#include "proxfusion3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define PROXFUSION3_DUMMY            0x00

/**
 * @brief Most significants byte.
 * @details Definition of 5 most significants byte.
 */
#define PROXFUSION3_BITS_7_5         0xF8

/**
 * @brief Low significant byte.
 * @details Definition of low significant byte.
 */
#define PROXFUSION3_LSB              0x00FF

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Touch delay.
 * @details Touch delay for 5 milliseconds.
 */
static void dev_touch_delay ( void );

/**
 * @brief Reset delay.
 * @details Reset delay for 100 milliseconds.
 */
static void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proxfusion3_cfg_setup ( proxfusion3_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->gp = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXFUSION3_SET_DEV_ADDR;
}

err_t proxfusion3_init ( proxfusion3_t *ctx, proxfusion3_cfg_t *cfg ) {
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) {
        return I2C_MASTER_ERROR;
    }

    digital_out_init( &ctx->int_pin, cfg->int_pin );

    digital_in_init( &ctx->gp, cfg->gp );

    return I2C_MASTER_SUCCESS;
}

err_t proxfusion3_default_cfg ( proxfusion3_t *ctx ) {
    uint8_t tx_buf[ 20 ];
    err_t status;
    
    status = 0;
    
    // Click default configuration.
    
    digital_out_high( &ctx->int_pin );
    
    // Power mode settings
    
    tx_buf[ 0 ] = PROXFUSION3_PMU_GENERAL_SETTINGS;
    tx_buf[ 1 ] = PROXFUSION3_I2C_GENERAL_SETTINGS;
    tx_buf[ 2 ] = PROXFUSION3_SYS_CHB_ACTIVE;
    tx_buf[ 3 ] = PROXFUSION3_ACF_LTA_FILTER_SETTINGS;
    tx_buf[ 4 ] = PROXFUSION3_LTA_CHB_RESEED_ENABLED;
    tx_buf[ 5 ] = PROXFUSION3_UIS_GLOBAL_EVENTS_MASK;
    status |= proxfusion3_generic_write( ctx, PROXFUSION3_PMU_SETTINGS, tx_buf, 6 );
    
    // Report Rate
    
    tx_buf[ 0 ] = PROXFUSION3_PMU_REPORT_RATE_NP;
    tx_buf[ 1 ] = PROXFUSION3_PMU_REPORT_RATE_LP;
    tx_buf[ 2 ] = PROXFUSION3_PMU_REPORT_RATE_ULP;
    tx_buf[ 3 ] = PROXFUSION3_PMU_MODE_TIMOUT;
    tx_buf[ 4 ] = PROXFUSION3_I2C_WINDOW_TIMEOUT;
    tx_buf[ 5 ] = PROXFUSION3_LTA_HALT_TIMEOUT;
    status |= proxfusion3_generic_write( ctx, PROXFUSION3_REPORT_RATES, tx_buf, 6 );
    
    // General Settings
    
    tx_buf[ 0 ]  = PROXFUSION3_PXS_GENERAL_SETTINGS0;
    tx_buf[ 1 ]  = PROXFUSION3_PXS_GENERAL_SETTINGS1;
    tx_buf[ 2 ]  = PROXFUSION3_UIS_ABSOLUTE_CAPACITANCE;
    tx_buf[ 3 ]  = PROXFUSION3_UIS_DCF_GENERAL_SETTINGS;
    tx_buf[ 4 ]  = PROXFUSION3_GEM_CHB_BLOCK_NFOLLOW;
    tx_buf[ 5 ]  = PROXFUSION3_MOV_CHB_MOVEMENT_CHANNEL;
    tx_buf[ 6 ]  = PROXFUSION3_UIS_CHB_SLIDER0;
    tx_buf[ 7 ]  = PROXFUSION3_UIS_CHB_SLIDER1;
    tx_buf[ 8 ]  = PROXFUSION3_UIS_GESTURE_TAP_TIMEOUT;
    tx_buf[ 9 ]  = PROXFUSION3_UIS_GESTURE_SWIPE_TIMEOUT;
    tx_buf[ 10 ] = PROXFUSION3_UIS_GESTURE_THRESHOLD;
    tx_buf[ 11 ] = PROXFUSION3_LTA_CHB_RESEED;
    status |= proxfusion3_generic_write( ctx, PROXFUSION3_GEN_SETINGS, tx_buf, 12 );
    
    // Channel 0 settings
    
    tx_buf[ 0 ]  = PROXFUSION3_PXS_CRXSEL_CH0;
    tx_buf[ 1 ]  = PROXFUSION3_PXS_CTXSEL_CH0;
    tx_buf[ 2 ]  = PROXFUSION3_PXS_PROXCTRL_CH0;
    tx_buf[ 3 ]  = PROXFUSION3_PXS_PROXCFG0_CH0;
    tx_buf[ 4 ]  = PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH0;
    tx_buf[ 5 ]  = PROXFUSION3_ATI_BASE_AND_TARGET_CH0;
    tx_buf[ 6 ]  = PROXFUSION3_ATI_MIRROR_CH0;
    tx_buf[ 7 ]  = PROXFUSION3_ATI_PCC_CH0;
    tx_buf[ 8 ]  = PROXFUSION3_PXS_PROX_THRESHOLD_CH0;
    tx_buf[ 9 ]  = PROXFUSION3_PXS_TOUCH_THRESHOLD_CH0;
    tx_buf[ 10 ] = PROXFUSION3_PXS_DEEP_THRESHOLD_CH0;
    tx_buf[ 11 ] = PROXFUSION3_PXS_HYSTERESIS_CH0;
    tx_buf[ 12 ] = PROXFUSION3_DCF_CHB_ASSOCIATION_CH0;
    tx_buf[ 13 ] = PROXFUSION3_DCF_WEIGHT_CH0;
    status |= proxfusion3_generic_write( ctx, PROXFUSION3_CH0_SETTINGS, tx_buf, 14 );
    
    // Channel 1 settings
    
    tx_buf[ 0 ]  = PROXFUSION3_PXS_CRXSEL_CH1;
    tx_buf[ 1 ]  = PROXFUSION3_PXS_CTXSEL_CH1;
    tx_buf[ 2 ]  = PROXFUSION3_PXS_PROXCTRL_CH1;
    tx_buf[ 3 ]  = PROXFUSION3_PXS_PROXCFG0_CH1;
    tx_buf[ 4 ]  = PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH1;
    tx_buf[ 5 ]  = PROXFUSION3_ATI_BASE_AND_TARGET_CH1;
    tx_buf[ 6 ]  = PROXFUSION3_ATI_MIRROR_CH1;
    tx_buf[ 7 ]  = PROXFUSION3_ATI_PCC_CH1;
    tx_buf[ 8 ]  = PROXFUSION3_PXS_PROX_THRESHOLD_CH1;
    tx_buf[ 9 ]  = PROXFUSION3_PXS_TOUCH_THRESHOLD_CH1;
    tx_buf[ 10 ] = PROXFUSION3_PXS_DEEP_THRESHOLD_CH1;
    tx_buf[ 11 ] = PROXFUSION3_PXS_HYSTERESIS_CH1;
    tx_buf[ 12 ] = PROXFUSION3_DCF_CHB_ASSOCIATION_CH1;
    tx_buf[ 13 ] = PROXFUSION3_DCF_WEIGHT_CH1;
    status |= proxfusion3_generic_write( ctx, PROXFUSION3_CH1_SETTINGS, tx_buf, 14 );
    
    // Channel 2 settings
    
    tx_buf[ 0 ]  = PROXFUSION3_PXS_CRXSEL_CH2;
    tx_buf[ 1 ]  = PROXFUSION3_PXS_CTXSEL_CH2;
    tx_buf[ 2 ]  = PROXFUSION3_PXS_PROXCTRL_CH2;
    tx_buf[ 3 ]  = PROXFUSION3_PXS_PROXCFG0_CH2;
    tx_buf[ 4 ]  = PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH2;
    tx_buf[ 5 ]  = PROXFUSION3_ATI_BASE_AND_TARGET_CH2;
    tx_buf[ 6 ]  = PROXFUSION3_ATI_MIRROR_CH2;
    tx_buf[ 7 ]  = PROXFUSION3_ATI_PCC_CH2;
    tx_buf[ 8 ]  = PROXFUSION3_PXS_PROX_THRESHOLD_CH2;
    tx_buf[ 9 ]  = PROXFUSION3_PXS_TOUCH_THRESHOLD_CH2;
    tx_buf[ 10 ] = PROXFUSION3_PXS_DEEP_THRESHOLD_CH2;
    tx_buf[ 11 ] = PROXFUSION3_PXS_HYSTERESIS_CH2;
    tx_buf[ 12 ] = PROXFUSION3_DCF_CHB_ASSOCIATION_CH2;
    tx_buf[ 13 ] = PROXFUSION3_DCF_WEIGHT_CH2;
    status |= proxfusion3_generic_write( ctx, PROXFUSION3_CH3_SETTINGS, tx_buf, 14 );
    
    // Channel 3 settings
    
    tx_buf[ 0 ]  = PROXFUSION3_PXS_CRXSEL_CH3;
    tx_buf[ 1 ]  = PROXFUSION3_PXS_CTXSEL_CH3;
    tx_buf[ 2 ]  = PROXFUSION3_PXS_PROXCTRL_CH3;
    tx_buf[ 3 ]  = PROXFUSION3_PXS_PROXCFG0_CH3;
    tx_buf[ 4 ]  = PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH3;
    tx_buf[ 5 ]  = PROXFUSION3_ATI_BASE_AND_TARGET_CH3;
    tx_buf[ 6 ]  = PROXFUSION3_ATI_MIRROR_CH3;
    tx_buf[ 7 ]  = PROXFUSION3_ATI_PCC_CH3;
    tx_buf[ 8 ]  = PROXFUSION3_PXS_PROX_THRESHOLD_CH3;
    tx_buf[ 9 ]  = PROXFUSION3_PXS_TOUCH_THRESHOLD_CH3;
    tx_buf[ 10 ] = PROXFUSION3_PXS_DEEP_THRESHOLD_CH3;
    tx_buf[ 11 ] = PROXFUSION3_PXS_HYSTERESIS_CH3;
    tx_buf[ 12 ] = PROXFUSION3_DCF_CHB_ASSOCIATION_CH3;
    tx_buf[ 13 ] = PROXFUSION3_DCF_WEIGHT_CH3;
    status |= proxfusion3_generic_write( ctx, PROXFUSION3_CH4_SETTINGS, tx_buf, 14 );
    
    // Channel 4 settings
    
    tx_buf[ 0 ]  = PROXFUSION3_PXS_CRXSEL_CH4;
    tx_buf[ 1 ]  = PROXFUSION3_PXS_CTXSEL_CH4;
    tx_buf[ 2 ]  = PROXFUSION3_PXS_PROXCTRL_CH4;
    tx_buf[ 3 ]  = PROXFUSION3_PXS_PROXCFG0_CH4;
    tx_buf[ 4 ]  = PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH4;
    tx_buf[ 5 ]  = PROXFUSION3_ATI_BASE_AND_TARGET_CH4;
    tx_buf[ 6 ]  = PROXFUSION3_ATI_MIRROR_CH4;
    tx_buf[ 7 ]  = PROXFUSION3_ATI_PCC_CH4;
    tx_buf[ 8 ]  = PROXFUSION3_PXS_PROX_THRESHOLD_CH4;
    tx_buf[ 9 ]  = PROXFUSION3_PXS_TOUCH_THRESHOLD_CH4;
    tx_buf[ 10 ] = PROXFUSION3_PXS_DEEP_THRESHOLD_CH4;
    tx_buf[ 11 ] = PROXFUSION3_PXS_HYSTERESIS_CH4;
    tx_buf[ 12 ] = PROXFUSION3_DCF_CHB_ASSOCIATION_CH4;
    tx_buf[ 13 ] = PROXFUSION3_DCF_WEIGHT_CH4;
    status |= proxfusion3_generic_write( ctx, PROXFUSION3_CH5_SETTINGS, tx_buf, 14 );
    
    // Channel 5 settings
    
    tx_buf[ 0 ]  = PROXFUSION3_PXS_CRXSEL_CH5;
    tx_buf[ 1 ]  = PROXFUSION3_PXS_CTXSEL_CH5;
    tx_buf[ 2 ]  = PROXFUSION3_PXS_PROXCTRL_CH5;
    tx_buf[ 3 ]  = PROXFUSION3_PXS_PROXCFG0_CH5;
    tx_buf[ 4 ]  = PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH5;
    tx_buf[ 5 ]  = PROXFUSION3_ATI_BASE_AND_TARGET_CH5;
    tx_buf[ 6 ]  = PROXFUSION3_ATI_MIRROR_CH5;
    tx_buf[ 7 ]  = PROXFUSION3_ATI_PCC_CH5;
    tx_buf[ 8 ]  = PROXFUSION3_PXS_PROX_THRESHOLD_CH5;
    tx_buf[ 9 ]  = PROXFUSION3_PXS_TOUCH_THRESHOLD_CH5;
    tx_buf[ 10 ] = PROXFUSION3_PXS_DEEP_THRESHOLD_CH5;
    tx_buf[ 11 ] = PROXFUSION3_PXS_HYSTERESIS_CH5;
    tx_buf[ 12 ] = PROXFUSION3_DCF_CHB_ASSOCIATION_CH5;
    tx_buf[ 13 ] = PROXFUSION3_DCF_WEIGHT_CH5;
    status |= proxfusion3_generic_write( ctx, PROXFUSION3_CH6_SETTINGS, tx_buf, 14 );
    
    // Channel 6 settings
    
    tx_buf[ 0 ]  = PROXFUSION3_PXS_CRXSEL_CH6;
    tx_buf[ 1 ]  = PROXFUSION3_PXS_CTXSEL_CH6;
    tx_buf[ 2 ]  = PROXFUSION3_PXS_PROXCTRL_CH6;
    tx_buf[ 3 ]  = PROXFUSION3_PXS_PROXCFG0_CH6;
    tx_buf[ 4 ]  = PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH6;
    tx_buf[ 5 ]  = PROXFUSION3_ATI_BASE_AND_TARGET_CH6;
    tx_buf[ 6 ]  = PROXFUSION3_ATI_MIRROR_CH6;
    tx_buf[ 7 ]  = PROXFUSION3_ATI_PCC_CH6;
    tx_buf[ 8 ]  = PROXFUSION3_PXS_PROX_THRESHOLD_CH6;
    tx_buf[ 9 ]  = PROXFUSION3_PXS_TOUCH_THRESHOLD_CH6;
    tx_buf[ 10 ] = PROXFUSION3_PXS_DEEP_THRESHOLD_CH6;
    tx_buf[ 11 ] = PROXFUSION3_PXS_HYSTERESIS_CH6;
    tx_buf[ 12 ] = PROXFUSION3_DCF_CHB_ASSOCIATION_CH6;
    tx_buf[ 13 ] = PROXFUSION3_DCF_WEIGHT_CH6;
    status |= proxfusion3_generic_write( ctx, PROXFUSION3_CH7_SETTINGS, tx_buf, 14 );
    
    // Channel 7 settings
    
    tx_buf[ 0 ]  = PROXFUSION3_PXS_CRXSEL_CH7;
    tx_buf[ 1 ]  = PROXFUSION3_PXS_CTXSEL_CH7;
    tx_buf[ 2 ]  = PROXFUSION3_PXS_PROXCTRL_CH7;
    tx_buf[ 3 ]  = PROXFUSION3_PXS_PROXCFG0_CH7;
    tx_buf[ 4 ]  = PROXFUSION3_PXS_PROXCFG1_TESTREG0_CH7;
    tx_buf[ 5 ]  = PROXFUSION3_ATI_BASE_AND_TARGET_CH7;
    tx_buf[ 6 ]  = PROXFUSION3_ATI_MIRROR_CH7;
    tx_buf[ 7 ]  = PROXFUSION3_ATI_PCC_CH7;
    tx_buf[ 8 ]  = PROXFUSION3_PXS_PROX_THRESHOLD_CH7;
    tx_buf[ 9 ]  = PROXFUSION3_PXS_TOUCH_THRESHOLD_CH7;
    tx_buf[ 10 ] = PROXFUSION3_PXS_DEEP_THRESHOLD_CH7;
    tx_buf[ 11 ] = PROXFUSION3_PXS_HYSTERESIS_CH7;
    tx_buf[ 12 ] = PROXFUSION3_DCF_CHB_ASSOCIATION_CH7;
    tx_buf[ 13 ] = PROXFUSION3_DCF_WEIGHT_CH7;
    status |= proxfusion3_generic_write( ctx, PROXFUSION3_CH8_SETTINGS, tx_buf, 14 );
    
    // Software reset
    
    proxfusion3_sw_reset( ctx );
    dev_reset_delay( );
    
    // Enable all channels
    
    proxfusion3_enable_channels( ctx );
    dev_reset_delay( );
    
    // Remap channels
    
    proxfusion3_channel_remap( ctx );
    dev_reset_delay( );
    
    // Touch Thesholds
    
    proxfusion3_adjust_touch_thresholds( ctx );
    dev_reset_delay( );
    
    // Deep Touch Thesholds
    
    proxfusion3_adjust_deep_touch_thresholds( ctx );
    dev_reset_delay( );
    
    // Auto tune
    
    proxfusion3_auto_tune( ctx );
    dev_reset_delay( );
    
    return status;
}

void proxfusion3_set_state_int_pin ( proxfusion3_t *ctx, uint8_t pin_state ) {
    digital_out_write( &ctx->int_pin, pin_state );
}

uint8_t proxfusion3_get_state_gp_pin ( proxfusion3_t *ctx ) {
    return digital_in_read( &ctx->gp ); 
}

err_t proxfusion3_generic_write ( proxfusion3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) {
    uint8_t data_buf[ 257 ];
    uint8_t cnt;
    err_t status;
    
    status = 0;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }
    
    digital_out_low( &ctx->int_pin );
    status |= i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
    digital_out_high( &ctx->int_pin );
    
    Delay_ms ( 1 );

    return status;
}

err_t proxfusion3_generic_read ( proxfusion3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) {
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void proxfusion3_write_reg ( proxfusion3_t *ctx, uint8_t reg, uint16_t tx_data ) {
    uint8_t tx_buf[ 3 ];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = ( uint8_t ) ( tx_data >> 8 );
    tx_buf[ 2 ] = ( uint8_t ) tx_data;
    
    digital_out_low( &ctx->int_pin );
    i2c_master_write( &ctx->i2c, tx_buf, 3 );
    digital_out_high( &ctx->int_pin );
}

uint16_t proxfusion3_read_reg ( proxfusion3_t *ctx, uint8_t reg ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 2 ];
    uint16_t result;
    
    tx_buf[ 0 ] = reg;
    
    digital_out_low( &ctx->int_pin );
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 2 );
    digital_out_high( &ctx->int_pin );
    
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    
    return result;
}

err_t proxfusion3_get_version_info ( proxfusion3_t *ctx, uint8_t *product_number, uint8_t *software_version ) {
    err_t status;
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 2 ];
    
    status = 0;
    
    tx_buf[ 0 ] = PROXFUSION3_DUMMY;
    
    digital_out_low( &ctx->int_pin );
    status |= i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 2 );
    digital_out_high( &ctx->int_pin );
    
    *product_number = rx_buf[ 0 ];
    *software_version = rx_buf[ 1 ];
    
    return status;
}

void proxfusion3_sw_reset ( proxfusion3_t *ctx ) {
    uint8_t tx_rx_buf[ 2 ];

    proxfusion3_generic_read( ctx, PROXFUSION3_PMU_SETTINGS, tx_rx_buf, 2 );
    
    tx_rx_buf[ 1 ] |= PROXFUSION3_ACK_RESET_BIT;

    proxfusion3_generic_write( ctx, PROXFUSION3_PMU_SETTINGS, tx_rx_buf, 2 );
}

void proxfusion3_enable_channels ( proxfusion3_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    
    tx_buf[ 0 ] = PROXFUSION3_SYS_CHB_ACTIVE;  
    proxfusion3_generic_write( ctx, PROXFUSION3_ACTIVE_CHANNELS, tx_buf, 1 );
}

void proxfusion3_channel_remap ( proxfusion3_t *ctx ) {
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = PROXFUSION3_TOUCH_CRX_6; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH0_CRX, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_TOUCH_CRX_4; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH1_CRX, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_TOUCH_CRX_2; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH2_CRX, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_TOUCH_CRX_1; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH3_CRX, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_TOUCH_CRX_7; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH4_CRX, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_TOUCH_CRX_5; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH5_CRX, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_TOUCH_CRX_3; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH6_CRX, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_TOUCH_CRX_0; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH7_CRX, tx_buf, 1 );
}

void proxfusion3_adjust_touch_thresholds ( proxfusion3_t *ctx ) {
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = PROXFUSION3_PROX_THRESHOLD; 
    tx_buf[ 1 ] = PROXFUSION3_TOUCH_THRESHOLD_CH0;
    proxfusion3_generic_write( ctx, PROXFUSION3_CH0_PT_T, tx_buf, 2 );
  
    tx_buf[ 1 ] = PROXFUSION3_TOUCH_THRESHOLD_CH1; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH1_PT_T, tx_buf, 2 );
    
    tx_buf[ 1 ] = PROXFUSION3_TOUCH_THRESHOLD_CH2; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH2_PT_T, tx_buf, 2 );
  
    tx_buf[ 1 ] = PROXFUSION3_TOUCH_THRESHOLD_CH3; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH3_PT_T, tx_buf, 2 );
    
    tx_buf[ 1 ] = PROXFUSION3_TOUCH_THRESHOLD_CH4; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH4_PT_T, tx_buf, 2 );
    
    tx_buf[ 1 ] = PROXFUSION3_TOUCH_THRESHOLD_CH5; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH5_PT_T, tx_buf, 2 );
    
    tx_buf[ 1 ] = PROXFUSION3_TOUCH_THRESHOLD_CH6; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH6_PT_T, tx_buf, 2 );
    
    tx_buf[ 1 ] = PROXFUSION3_TOUCH_THRESHOLD_CH7; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH7_PT_T, tx_buf, 2 );
}

void proxfusion3_adjust_deep_touch_thresholds ( proxfusion3_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    
    tx_buf[ 0 ] = PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH0; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH0_DT_T, tx_buf, 1 );
  
    tx_buf[ 0 ] = PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH1; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH1_DT_T, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH2; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH2_DT_T, tx_buf, 1 );
  
    tx_buf[ 0 ] = PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH3; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH3_DT_T, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH4; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH4_DT_T, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH5; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH5_DT_T, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH6; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH6_DT_T, tx_buf, 1 );
    
    tx_buf[ 0 ] = PROXFUSION3_DEEP_TOUCH_THRESHOLD_CH7; 
    proxfusion3_generic_write( ctx, PROXFUSION3_CH7_DT_T, tx_buf, 1 );
}

void proxfusion3_auto_tune ( proxfusion3_t *ctx ) {
    uint8_t tx_rx_buf[ 2 ]; 
    
    tx_rx_buf[ 0 ] = PROXFUSION3_PMU_SETTINGS;
    tx_rx_buf[ 1 ] = PROXFUSION3_SYS_CHB_ACTIVE;

    proxfusion3_generic_write( ctx, PROXFUSION3_SWIPE_SETTINGS, tx_rx_buf, 2 );

    proxfusion3_generic_read( ctx, PROXFUSION3_PMU_SETTINGS, tx_rx_buf, 2 );

    tx_rx_buf[ 1 ] |= PROXFUSION3_REDO_ATI_BIT;

    proxfusion3_generic_write( ctx, PROXFUSION3_PMU_SETTINGS, tx_rx_buf, 2 );
}

void proxfusion3_set_event ( proxfusion3_t *ctx, uint8_t event )
{
    uint8_t rx_tx_buf[ 2 ];
    
    proxfusion3_generic_read( ctx, PROXFUSION3_CH_RESEED, rx_tx_buf, 2 );
  
    rx_tx_buf[ 1 ] |= event;
    
    proxfusion3_generic_write( ctx, PROXFUSION3_PMU_SETTINGS, rx_tx_buf, 2 );
}

float proxfusion3_get_absolute_measurement ( proxfusion3_t *ctx ) {
    uint8_t rx_buf[ 6 ];
    uint16_t temp[ 3 ];
    float base;
    float counts;
    float counts_c0;
    float cap0;
  
    proxfusion3_generic_read( ctx, PROXFUSION3_CAP_ABS_BASE, rx_buf, 6 );

    rx_buf[ 1 ] &= ~PROXFUSION3_BITS_7_5;
    rx_buf[ 3 ] &= ~PROXFUSION3_BITS_7_5;
    rx_buf[ 5 ] &= ~PROXFUSION3_BITS_7_5;

    temp[ 0 ] = rx_buf[ 1 ];
    temp[ 0 ] <<= 8;
    temp[ 0 ] |= rx_buf[ 0 ];
    
    temp[ 1 ] = rx_buf[ 3 ];
    temp[ 1 ] <<= 8;
    temp[ 1 ] |= rx_buf[ 2 ];
    
    temp[ 2 ] = rx_buf[ 5 ];
    temp[ 2 ] <<= 8;
    temp[ 2 ] |= rx_buf[ 4 ];
    
    base = ( float ) ( temp[ 0 ] );
    counts = ( float ) ( temp[ 1 ] );
    counts_c0 = ( float ) ( temp[ 2 ] );
  
    cap0 = ( 1 / base ) * ( ( 0.5 ) / ( ( 1 / counts_c0 ) - ( 1 / counts ) ) );
  
    return cap0;
}

uint16_t proxfusion3_read_channel_delta ( proxfusion3_t *ctx, uint8_t channel ) {
    uint8_t rx_buf[ 2 ];      
    uint8_t reg;
    uint16_t lta; 
  
    reg = PROXFUSION3_DELTA_CH0;
    reg += channel;

    proxfusion3_generic_read( ctx, reg, rx_buf, 2 );

    lta = rx_buf[ 1 ];
    lta <<= 8;
    lta |= rx_buf[ 0 ];

    return lta;
}

uint8_t proxfusion3_check_touch_event ( proxfusion3_t *ctx ) {
    uint8_t rx_data;
    uint8_t touch_event;
    uint8_t touch_status;
    
    touch_status = PROXFUSION3_EVENT_NO_TOUCH;
    
    rx_data = ( uint8_t ) proxfusion3_read_reg( ctx, PROXFUSION3_SYS_FLAGS );
    rx_data &= PROXFUSION3_TOUCH_EVENT_BIT;
    
    if ( rx_data == PROXFUSION3_TOUCH_EVENT_BIT ) {
        touch_status = PROXFUSION3_EVENT_TOUCH;    
    }

    return PROXFUSION3_EVENT_TOUCH;
}

uint8_t proxfusion3_get_touch ( proxfusion3_t *ctx ) {
    uint16_t rx_buf;
    uint8_t tmp;
    uint8_t touch_pos;
    
    rx_buf = proxfusion3_read_reg( ctx, PROXFUSION3_CH_TOUCH_STATE );
    
    if ( rx_buf == PROXFUSION3_TOUCH_CH_RX_THRESHOLD_7 ) {
        rx_buf = PROXFUSION3_TOUCH_CRX_7;    
    } else {
        rx_buf >>= 8;
        rx_buf &= PROXFUSION3_LSB;    
    }
    
    tmp = ( uint8_t ) rx_buf;
  
    switch ( tmp )
    {
        case PROXFUSION3_TOUCH_CRX_7: {
            touch_pos = PROXFUSION3_TOUCH_POS_8;
            dev_touch_delay( );
            break;
        }
        case PROXFUSION3_TOUCH_CRX_6: {
            touch_pos = PROXFUSION3_TOUCH_POS_7; 
            dev_touch_delay( ); 
            break;
        }
        case PROXFUSION3_TOUCH_CRX_5: {
            touch_pos = PROXFUSION3_TOUCH_POS_6;
            dev_touch_delay( ); 
            break;
        }
        case PROXFUSION3_TOUCH_CRX_4: {
            touch_pos = PROXFUSION3_TOUCH_POS_5;
            dev_touch_delay( );
            break;
        }
        case PROXFUSION3_TOUCH_CRX_3: {
            touch_pos = PROXFUSION3_TOUCH_POS_4;
            dev_touch_delay( ); 
            break;
        }
        case PROXFUSION3_TOUCH_CRX_2: {
            touch_pos = PROXFUSION3_TOUCH_POS_3;
            dev_touch_delay( ); 
            break;
        }
        case PROXFUSION3_TOUCH_CRX_1: {
            touch_pos = PROXFUSION3_TOUCH_POS_2;
            dev_touch_delay( ); 
            break;
        }
        case PROXFUSION3_TOUCH_CRX_0: {
            touch_pos = PROXFUSION3_TOUCH_POS_1;
            dev_touch_delay( ); 
            break;
        }
        default: {
            touch_pos = PROXFUSION3_TOUCH_POS_NO_TOUCH;
            dev_touch_delay( ); 
            break;
        }
    }

    return touch_pos;
}

void proxfusion3_en_abs_cap ( proxfusion3_t *ctx ) {
    uint8_t rx_tx_buf[ 1 ];
  
    proxfusion3_generic_read( ctx, PROXFUSION3_REF_SETTINGS, rx_tx_buf, 1 );

    rx_tx_buf[ 0 ] |= PROXFUSION3_ENABLE_ABSCAP_UI;
    proxfusion3_generic_write( ctx, PROXFUSION3_REF_SETTINGS, rx_tx_buf, 1 );
  
    proxfusion3_generic_read( ctx, PROXFUSION3_REF_SETTINGS, rx_tx_buf, 1 );

    rx_tx_buf[ 0 ] |= PROXFUSION3_DISABLE_AUTO_MODE;
    proxfusion3_generic_write( ctx, PROXFUSION3_REF_SETTINGS, rx_tx_buf, 1 );
}

void proxfusion3_set_work_mode ( proxfusion3_t *ctx, uint8_t mode ) {
    uint8_t rx_tx_buf[ 2 ];

    proxfusion3_generic_read( ctx, PROXFUSION3_PMU_SETTINGS, rx_tx_buf, 2 );
    
    if ( mode == 0 ) {
        rx_tx_buf[ 1 ] &= ~PROXFUSION3_EVENT_MODE_BIT;    
    } else {
        rx_tx_buf[ 1 ] |= PROXFUSION3_EVENT_MODE_BIT;   
    }
    
    proxfusion3_generic_write( ctx, PROXFUSION3_PMU_SETTINGS, rx_tx_buf, 2 );
}

uint8_t proxfusion3_get_events ( proxfusion3_t *ctx ) {
    uint8_t rx_buf[ 2 ];

    proxfusion3_generic_read( ctx, PROXFUSION3_SYS_FLAGS, rx_buf, 2 );

    return rx_buf[ 1 ];
}

uint8_t proxfusion3_get_gestures ( proxfusion3_t *ctx ) {
    uint8_t rx_buf[ 2 ];

    proxfusion3_generic_read( ctx, PROXFUSION3_GESTURE_FLAGS, rx_buf, 2 );

    return rx_buf[ 0 ];
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_touch_delay ( void ) {
    Delay_5ms( );   
}

static void dev_reset_delay ( void ) {
    Delay_100ms( );   
}

// ------------------------------------------------------------------------- END
