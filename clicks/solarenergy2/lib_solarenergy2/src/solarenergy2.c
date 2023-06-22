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
 * @file solarenergy2.c
 * @brief Solar Energy 2 Click Driver.
 */

#include "solarenergy2.h"

/**
 * @brief Solar Energy 2 description calculation coefficient.
 * @details Specified coefficient for calculating 
 * the voltage and sleep VSUP supply period of Solar Energy 2 Click driver.
 */
#define SOLARENERGY2_ABS_VTG_COEF         13.0f
#define SOLARENERGY2_SLEEP_VSUP_COEF    1000.0f

void solarenergy2_cfg_setup ( solarenergy2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->cs   = HAL_PIN_NC;
    cfg->wup   = HAL_PIN_NC;
    cfg->blv = HAL_PIN_NC;
    cfg->hlv = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SOLARENERGY2_DEVICE_ADDRESS;
}

err_t solarenergy2_init ( solarenergy2_t *ctx, solarenergy2_cfg_t *cfg ) 
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

    digital_out_init( &ctx->wup, cfg->wup );
    digital_out_init( &ctx->cs, cfg->cs );

    digital_in_init( &ctx->blv, cfg->blv );
    digital_in_init( &ctx->hlv, cfg->hlv );

    digital_out_high( &ctx->cs );
    digital_out_high( &ctx->wup );

    return I2C_MASTER_SUCCESS;
}

err_t solarenergy2_default_cfg ( solarenergy2_t *ctx ) 
{
    err_t err_flag = solarenergy2_soft_reset( ctx );
    Delay_100ms( );

    // CONFIGURATION OF THE HARVESTING PARAMETERS
    // indicates that the HRV is checked by the current supervisory - Minimum HRV open voltage required to generate energy 
    // HRV check by Ishort-cut - v_hrv_min: 0.146 V 
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_V_HRV_CFG, SOLARENERGY2_SET_HRV_CHECK_VLD_VTG | SOLARENERGY2_SET_HRV_MIN_VTG_GEN );
    Delay_10ms( );
    // CONFIGURATION OF THE HARVESTING PARAMETERS
    err_flag |= solarenergy2_set_mppt_ratio( ctx, SOLARENERGY2_SET_MPPT_RATIO_80 );
    Delay_10ms( );
    
    // HRV period: 8192 ms
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_T_HRV_PERIOD, SOLARENERGY2_SET_T_HRV_PERIOD_8sec );
    Delay_10ms( );
    
    // HRV measurement period: 128 ms
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_T_HRV_MEAS, SOLARENERGY2_SET_T_HRV_MEAS_128ms );
    Delay_10ms( );
    
    // HRV Low period: 256 ms, LTS HRV period: 32 ms
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_T_HRV_LOW_CFG, SOLARENERGY2_SET_T_HRV_LOW_PERIOD_256ms | SOLARENERGY2_SET_T_LTS_LOW_PERIOD_32ms );
    Delay_10ms( );
    
    // VAUX LDO regulated voltage selection 1.8V
    // ULP LDO regulated voltage selection 1.8V
    err_flag |= solarenergy2_set_ldo_cfg( ctx, SOLARENERGY2_SET_VAUX_LDO_CFG_1_8V, SOLARENERGY2_SET_ULP_LDO_CFG_1_8V );
    Delay_10ms( );
    
    // Normal mode on STS
    // Sets the device in secondary cell mode (LTS is rechargeable)
    // Enables the battery protection feature.
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_LTS_CFG, SOLARENERGY2_SET_LTS_CFG_NORMAL_MODE | SOLARENERGY2_SET_LTS_CFG_RECHARGEABLE | SOLARENERGY2_SET_LTS_CFG_BATT_PROT_EN );
    Delay_10ms( );
    
    // Absolute maximum voltage level of the battery: 4.10 V 
    // Maximum voltage of the battery, form an hysteresisi: 4.00 V
    // Minimum battery and application voltage when STS and LTS are disconnected: 2.70 V
    // Minimum battery and application voltage when STS and LTS are connected: 2.65 V 
    // Absolute minimum value of the battery and the application: 2.50 V
    // Absolute maximum voltage of the application: 3.50 V
    // Maximum voltage of the application: 3.40 V
    solarenergy2_abs_vtg_v_t abs_vtg_val;
    abs_vtg_val.v_bat_max_hi = 4.10;
    abs_vtg_val.v_bat_max_lo = 4.00;
    abs_vtg_val.v_bat_min_hi_dis = 2.70;
    abs_vtg_val.v_bat_min_hi_con = 2.65;
    abs_vtg_val.v_bat_min_lo = 2.50;
    abs_vtg_val.v_apl_max_hi = 3.50;
    abs_vtg_val.v_apl_max_lo = 3.40;
    err_flag |= solarenergy2_config_abs_voltage( ctx, abs_vtg_val );
    Delay_10ms( );
    
    // VAUX[2][1][0] - connected to the LDO 
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_VAUX_CFG, SOLARENERGY2_SET_VAUX2_CFG_LDO | SOLARENERGY2_SET_VAUX1_CFG_LDO | SOLARENERGY2_SET_VAUX0_CFG_LDO );
    Delay_10ms( );
    
    // PWR crt source 10 mA - USB power current source selection   
    err_flag |= solarenergy2_set_pwr_current_source( ctx, SOLARENERGY2_SET_CRT_SRC_SEL_10mA );
    Delay_10ms( );
    
    // Set the minimum short-circuit current level (used for Solar Only)
    // Vout range 3V to 3.6V: Ihrv_lim = 15uA
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_HRV_CHECK_LVL, SOLARENERGY2_SET_HRV_CURRENT_LVL_15uA );
    Delay_10ms( );
    
    // Period between two voltage level measurements of LTS 16ms
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_T_LTS_PERIOD, SOLARENERGY2_SET_T_LTS_PERIOD_16ms );
    Delay_10ms( );

    return err_flag;
}

err_t solarenergy2_generic_write ( solarenergy2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = SOLARENERGY2_REG_PROTECT_KEY;
    if ( reg > SOLARENERGY2_REG_PWR_MGT )
    {
        if ( reg == SOLARENERGY2_REG_SOFT_RES_WORD )
        {
            data_buf[ 1 ] = SOLARENERGY2_PROTECT_KEY_SOFT_RESET;  
        }
        else
        {
            data_buf[ 1 ] = SOLARENERGY2_PROTECT_KEY_EEPROM;    
        }
    }
    else
    {
        data_buf[ 1 ] = SOLARENERGY2_PROTECT_KEY_PROTECTED_REG; 
    }
    
    data_buf[ 2 ] = reg; 
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 3 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 3 );
}

err_t solarenergy2_generic_read ( solarenergy2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t solarenergy2_write_reg ( solarenergy2_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = SOLARENERGY2_REG_PROTECT_KEY;
    if ( reg > SOLARENERGY2_REG_PWR_MGT )
    {
        data_buf[ 1 ] = SOLARENERGY2_PROTECT_KEY_SOFT_RESET;
    }
    else
    {
        data_buf[ 1 ] = SOLARENERGY2_PROTECT_KEY_PROTECTED_REG;    
    }
    data_buf[ 2 ] = reg; 
    data_buf[ 3 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 4 );
}

err_t solarenergy2_write_eeprom ( solarenergy2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = SOLARENERGY2_REG_PROTECT_KEY;
    data_buf[ 1 ] = SOLARENERGY2_PROTECT_KEY_EEPROM;    
    data_buf[ 2 ] = reg | SOLARENERGY2_REG_EEPROM_0;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 3 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 3 );
}

err_t solarenergy2_soft_reset ( solarenergy2_t *ctx ) 
{
    uint8_t data_buf = SOLARENERGY2_PROTECT_KEY_SOFT_RESET;
    err_t err_flag = solarenergy2_generic_write( ctx, SOLARENERGY2_REG_SOFT_RES_WORD, &data_buf, 1 );
    return err_flag;
}

err_t solarenergy2_get_status ( solarenergy2_t *ctx, solarenergy2_status_t *status ) 
{
    uint8_t data_buf;
    err_t err_flag = solarenergy2_generic_read( ctx, SOLARENERGY2_REG_STATUS, &data_buf, 1 );
    status->eeprom_data_busy  = ( data_buf >> 7 ) & 0x01;
    status->hrv_lux_busy      = ( data_buf >> 6 ) & 0x01;
    status->hrv_low           = ( data_buf >> 5 ) & 0x01;
    status->bat_low           = ( data_buf >> 4 ) & 0x01;
    status->sw_vdcdc_lts_nsts = ( data_buf >> 3 ) & 0x01;
    status->sw_lts_sts        = ( data_buf >> 2 ) & 0x01;
    status->usb_on            = ( data_buf >> 1 ) & 0x01;
    status->lts_protect       =   data_buf        & 0x01;
    return err_flag;
}

err_t solarenergy2_get_bat_vtg_status ( solarenergy2_t *ctx, solarenergy2_bat_vtg_status_t *bat_vtg_status ) 
{
    uint8_t data_buf;
    err_t err_flag = solarenergy2_generic_read( ctx, SOLARENERGY2_REG_VLD_STATUS, &data_buf, 1 );
    bat_vtg_status->lts_bat_min_hi = ( data_buf >> 7 ) & 0x01;
    bat_vtg_status->lts_bat_min_lo = ( data_buf >> 6 ) & 0x01;
    bat_vtg_status->sts_bat_max_hi = ( data_buf >> 5 ) & 0x01;
    bat_vtg_status->sts_bat_max_lo = ( data_buf >> 4 ) & 0x01;
    bat_vtg_status->sts_apl_max_hi = ( data_buf >> 3 ) & 0x01;
    bat_vtg_status->sts_apl_max_lo = ( data_buf >> 2 ) & 0x01;
    bat_vtg_status->sts_bat_min_hi = ( data_buf >> 1 ) & 0x01;
    bat_vtg_status->sts_bat_min_lo =   data_buf        & 0x01;
    return err_flag;
}

err_t solarenergy2_set_sleep_vsup ( solarenergy2_t *ctx, float sleep_vsup_sec ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    sleep_vsup_sec *= SOLARENERGY2_SLEEP_VSUP_COEF;
    data_buf[ 0 ] = ( uint8_t ) ( ( ( uint32_t ) sleep_vsup_sec & 0x00FF0000 ) >> 16 );
    data_buf[ 1 ] = ( uint8_t ) ( ( ( uint32_t ) sleep_vsup_sec & 0x0000FF00 ) >> 8 );
    data_buf[ 2 ] = ( uint8_t )     ( uint32_t ) sleep_vsup_sec & 0x000000FF;
    return solarenergy2_generic_write( ctx, SOLARENERGY2_REG_T_SLEEP_VSUP_LO, &data_buf, 3 );
}

err_t solarenergy2_set_mppt_ratio ( solarenergy2_t *ctx, uint8_t mppt_ratio ) 
{
    mppt_ratio &= SOLARENERGY2_SET_MPPT_BIT_MASK;
    err_t err_flag = solarenergy2_generic_write( ctx, SOLARENERGY2_REG_MPPT_RATIO, &mppt_ratio, 1 );
    return err_flag;
}

err_t solarenergy2_set_ldo_cfg ( solarenergy2_t *ctx, uint8_t vaux_ldo, uint8_t ulp_ldo ) 
{
    uint8_t data_buf;
    err_t err_flag = solarenergy2_generic_read( ctx, SOLARENERGY2_REG_LDO_CFG, &data_buf, 1 );
    data_buf &= SOLARENERGY2_SET_LDO_CFG_VSUP_BIT_MASK | SOLARENERGY2_SET_LDO_CFG_ULP_BIT_MASK;
    data_buf |= vaux_ldo & SOLARENERGY2_SET_VAUX_LDO_CFG_BIT_MASK;
    data_buf |= ulp_ldo & SOLARENERGY2_SET_ULP_LDO_CFG_BIT_MASK;
    err_flag |= solarenergy2_generic_write( ctx, SOLARENERGY2_REG_LDO_CFG, &data_buf, 1 );
    return err_flag;
}

err_t solarenergy2_config_abs_voltage ( solarenergy2_t *ctx, solarenergy2_abs_vtg_v_t abs_vtg ) 
{
    uint8_t data_buf;
    data_buf = ( uint8_t ) ( abs_vtg.v_bat_max_hi * SOLARENERGY2_ABS_VTG_COEF );
    data_buf &= SOLARENERGY2_V_BATT_APP_VTG_BIT_MASK;
    err_t err_flag = solarenergy2_write_reg( ctx, SOLARENERGY2_REG_V_BAT_MAX_HI, ++data_buf );
    Delay_10ms( );
    data_buf = ( uint8_t ) ( abs_vtg.v_bat_max_lo * SOLARENERGY2_ABS_VTG_COEF );
    data_buf &= SOLARENERGY2_V_BATT_APP_VTG_BIT_MASK;
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_V_BAT_MAX_LO, ++data_buf );
    Delay_10ms( );
    data_buf = ( uint8_t ) ( abs_vtg.v_bat_min_hi_dis * SOLARENERGY2_ABS_VTG_COEF );
    data_buf &= SOLARENERGY2_V_BATT_APP_VTG_BIT_MASK;
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_V_BAT_MIN_HI_DIS, ++data_buf );
    Delay_10ms( );
    data_buf = ( uint8_t ) ( abs_vtg.v_bat_min_hi_con * SOLARENERGY2_ABS_VTG_COEF );
    data_buf &= SOLARENERGY2_V_BATT_APP_VTG_BIT_MASK;
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_V_BAT_MIN_HI_CON, ++data_buf );
    Delay_10ms( );
    data_buf = ( uint8_t ) ( abs_vtg.v_bat_min_lo * SOLARENERGY2_ABS_VTG_COEF );
    data_buf &= SOLARENERGY2_V_BATT_APP_VTG_BIT_MASK;
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_V_BAT_MIN_LO, ++data_buf );
    Delay_10ms( );
    data_buf = ( uint8_t ) ( abs_vtg.v_apl_max_hi * SOLARENERGY2_ABS_VTG_COEF );
    data_buf &= SOLARENERGY2_V_BATT_APP_VTG_BIT_MASK;
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_V_APL_MAX_HI, ++data_buf );
    Delay_10ms( );
    data_buf = ( uint8_t ) ( abs_vtg.v_apl_max_lo * SOLARENERGY2_ABS_VTG_COEF );
    data_buf &= SOLARENERGY2_V_BATT_APP_VTG_BIT_MASK;
    err_flag |= solarenergy2_write_reg( ctx, SOLARENERGY2_REG_V_APL_MAX_LO, ++data_buf );
    return err_flag;
}

err_t solarenergy2_set_pwr_current_source ( solarenergy2_t *ctx, uint8_t crt_src_sel ) 
{
    uint8_t data_buf;
    crt_src_sel &= SOLARENERGY2_CRT_SRC_SEL_BIT_MASK;
    err_t err_flag = solarenergy2_generic_read( ctx, SOLARENERGY2_REG_EXT_CFG, &data_buf, 1 );
    data_buf &= ~SOLARENERGY2_CRT_SRC_SEL_BIT_MASK;
    crt_src_sel |= data_buf;
    return solarenergy2_write_reg( ctx, SOLARENERGY2_REG_EXT_CFG, crt_src_sel );
}

err_t solarenergy2_store_config ( solarenergy2_t *ctx ) 
{
    uint8_t data_buf[ 26 ] = { 0 };
    err_t err_flag = solarenergy2_generic_read( ctx, SOLARENERGY2_REG_T_HRV_PERIOD, data_buf, 26 );
    Delay_10ms( );
    err_flag |= solarenergy2_write_eeprom( ctx, SOLARENERGY2_REG_T_HRV_PERIOD, data_buf, 26 );
    return err_flag;
}

void solarenergy2_set_wup_pin ( solarenergy2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

uint8_t solarenergy2_get_en_hv_cell_low_state ( solarenergy2_t *ctx ) 
{
    return digital_in_read( &ctx->hlv );
}

uint8_t solarenergy2_get_battery_low_state ( solarenergy2_t *ctx ) 
{
    return digital_in_read( &ctx->blv );
}

// ------------------------------------------------------------------------- END
