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
 * @file charger30.c
 * @brief Charger 30 Click Driver.
 */

#include "charger30.h"

void charger30_cfg_setup ( charger30_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ce = HAL_PIN_NC;
    cfg->otg = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CHARGER30_DEVICE_ADDRESS;
}

err_t charger30_init ( charger30_t *ctx, charger30_cfg_t *cfg ) 
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

    digital_out_init( &ctx->ce, cfg->ce );
    digital_out_init( &ctx->otg, cfg->otg );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t charger30_default_cfg ( charger30_t *ctx ) 
{
    err_t error_flag = CHARGER30_OK;
    charger30_disable_charging ( ctx );
    charger30_disable_boost ( ctx );
    Delay_100ms ( );
    if ( CHARGER30_ERROR == charger30_check_communication ( ctx ) )
    {
        return CHARGER30_ERROR;
    }
    error_flag |= charger30_sw_reset ( ctx );
    Delay_100ms ( );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_INPUT_CURRENT_LIMIT, 
                                        CHARGER30_ICL_EN_HIZ_DISABLE | 
                                        CHARGER30_ICL_EN_LIM_ENABLE | 
                                        CHARGER30_ICL_IIN_LIM_MA( CHARGER30_ICL_IIN_LIM_MA_DEFAULT ) );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_INPUT_VOLTAGE_REG, 
                                        CHARGER30_IVR_REG_RESET_KEEP | 
                                        CHARGER30_IVR_VIN_MIN_MV( CHARGER30_IVR_VIN_MIN_MV_DEFAULT ) );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_NTC_CONFIG_THERMAL_REG, 
                                        CHARGER30_NCTR_TSM_DLY_10S | 
                                        CHARGER30_NCTR_NTC_TYPE_STANDARD | 
                                        CHARGER30_NCTR_EN_OTG_NTC_DISABLE | 
                                        CHARGER30_NCTR_EN_CHG_NTC_ENABLE | 
                                        CHARGER30_NCTR_TJ_REG_120C | 
                                        CHARGER30_NCTR_NTC_OPT_PCB | 
                                        CHARGER30_NCTR_AICO_EN_DISABLE );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_ADC_CTRL_OTG_CONFIG, 
                                        CHARGER30_ACOC_ADC_START_ENABLE | 
                                        CHARGER30_ACOC_ADC_RATE_CONTINUOUS | 
                                        CHARGER30_ACOC_VIN_DSCHG_5000MV | 
                                        CHARGER30_ACOC_IIN_DSCHG_500MA );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_CHARGE_CTRL_VSYS_CONFIG, 
                                        CHARGER30_CCVC_BAT_LOADEN_DISABLE | 
                                        CHARGER30_CCVC_STAT_EN_ENABLE | 
                                        CHARGER30_CCVC_CHG_CONFIG_CHARGE_ENABLE | 
                                        CHARGER30_CCVC_VSYS_MIN_3600MV | 
                                        CHARGER30_CCVC_VTRACK_100MV );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_CHARGE_CURRENT_CONFIG, 
                                        CHARGER30_CCC_VBATT_PRE_3000MV | 
                                        CHARGER30_CCC_ICC_MA( CHARGER30_CCC_ICC_MA_DEFAULT ) );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_PRE_CHARGE_TERM_CURRENT, 
                                        CHARGER30_PCTC_IPRE_MA( CHARGER30_PCTC_IPRE_MA_DEFAULT ) | 
                                        CHARGER30_PCTC_ITERM_MA( CHARGER30_PCTC_ITERM_MA_DEFAULT ) );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_CHARGE_VOLTAGE_REG, 
                                        CHARGER30_CVR_VBATT_REG_MV( CHARGER30_CVR_VBATT_REG_MV_DEFAULT ) | 
                                        CHARGER30_CVR_VRECH_100MV );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_TIMER_CONFIG, 
                                        CHARGER30_TC_EN_TERM_ENABLE | 
                                        CHARGER30_TC_WATCHDOG_DISABLE | 
                                        CHARGER30_TC_WATCHDOG_RESET_NORMAL | 
                                        CHARGER30_TC_CHG_TMR_12HRS | 
                                        CHARGER30_TC_EN_TIMER_ENABLE );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_BANDGAP, CHARGER30_BANDGAP_ENABLE );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_BATFET_CONFIG, 
                                        CHARGER30_BC_SW_FREQ_1_35MHZ | 
                                        CHARGER30_BC_TMR2X_EN_ENABLE | 
                                        CHARGER30_BC_BATFET_DIS_ALLOW_ON | 
                                        CHARGER30_BC_SYSRST_SEL_HW | 
                                        CHARGER30_BC_TDISC_H_4S | 
                                        CHARGER30_BC_TDISC_L_8S );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_INT_MASK_USB_DETECTION, 
                                        CHARGER30_IMUD_INT_SAFETY_TIMER_ENABLE | 
                                        CHARGER30_IMUD_INT_BAT_FAULT_ENABLE | 
                                        CHARGER30_IMUD_USB_DET_EN_ENABLE | 
                                        CHARGER30_IMUD_DM_3300MV | 
                                        CHARGER30_IMUD_DP_600MV | 
                                        CHARGER30_IMUD_USB_FAST_CHG_DP_L_DM_HIZ | 
                                        CHARGER30_IMUD_USB_FAST_CHG_RESET_VDP_SRC );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_DPM_MASK, 
                                        CHARGER30_DM_VINPPM_INT_ENABLE | 
                                        CHARGER30_DM_IINPPM_INT_ENABLE );
    error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_JEITA_CONFIG, 
                                        CHARGER30_JC_JEITA_VSET_200MV | 
                                        CHARGER30_JC_JEITA_ISET_16_7PCT | 
                                        CHARGER30_JC_VTH_HOT_55C | 
                                        CHARGER30_JC_VTH_WARM_45C | 
                                        CHARGER30_JC_VTH_COOL_15C | 
                                        CHARGER30_JC_VTH_COLD_0C );
    charger30_enable_charging ( ctx );
    return error_flag;
}

err_t charger30_write_reg ( charger30_t *ctx, uint8_t reg, uint8_t data_in )
{
    return charger30_write_regs( ctx, reg, &data_in, 1 );
}

err_t charger30_write_regs ( charger30_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ CHARGER30_REG_INT_MASK_USB_DETECTION + 4 ] = { 0 };
    if ( ( ( reg > CHARGER30_REG_INT_MASK_USB_DETECTION ) && 
           ( CHARGER30_REG_DPM_MASK != reg ) && 
           ( CHARGER30_REG_JEITA_CONFIG != reg ) ) ||
         ( ( reg + len ) > ( CHARGER30_REG_JEITA_CONFIG + 1 ) ) ||
         ( NULL == data_in ) )
    {
        return CHARGER30_ERROR;
    }
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t charger30_read_reg ( charger30_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return charger30_read_regs( ctx, reg, data_out, 1 );
}

err_t charger30_read_regs ( charger30_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( ( ( reg + len ) > ( CHARGER30_REG_SAFETY_TIMER_STATUS_PART_NUM + 1 ) ) || 
         ( NULL == data_out ) )
    {
        return CHARGER30_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void charger30_enable_boost ( charger30_t *ctx ) 
{
    digital_out_high( &ctx->otg );
}

void charger30_disable_boost ( charger30_t *ctx ) 
{
    digital_out_low( &ctx->otg );
}

void charger30_enable_charging ( charger30_t *ctx ) 
{
    digital_out_low( &ctx->ce );
}

void charger30_disable_charging ( charger30_t *ctx ) 
{
    digital_out_high( &ctx->ce );
}

uint8_t charger30_get_int_pin ( charger30_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t charger30_check_communication ( charger30_t *ctx )
{
    uint8_t part_num = 0;
    if ( CHARGER30_OK == charger30_read_reg ( ctx, CHARGER30_REG_SAFETY_TIMER_STATUS_PART_NUM, &part_num ) )
    {
        if ( CHARGER30_STSPN_PART_NUMBER == ( CHARGER30_STSPN_PART_NUMBER_MASK & part_num ) )
        {
            return CHARGER30_OK;
        }
    }
    return CHARGER30_ERROR;
}

err_t charger30_sw_reset ( charger30_t *ctx )
{
    err_t error_flag = CHARGER30_OK;
    uint8_t reg_data = 0;
    error_flag |= charger30_read_reg ( ctx, CHARGER30_REG_INPUT_VOLTAGE_REG, &reg_data );
    if ( CHARGER30_OK == error_flag )
    {
        reg_data |= CHARGER30_IVR_REG_RESET_RESET;
        error_flag |= charger30_write_reg ( ctx, CHARGER30_REG_INPUT_VOLTAGE_REG, reg_data );
    }
    return error_flag;
}

err_t charger30_read_status ( charger30_t *ctx, charger30_status_t *status )
{
    uint8_t data_buf[ 9 ] = { 0 };
    err_t error_flag = CHARGER30_OK;
    error_flag |= charger30_read_regs ( ctx, CHARGER30_REG_STATUS, data_buf, 9 );
    if ( ( NULL != status ) && ( CHARGER30_OK == error_flag ) )
    {
        status->status = data_buf[ 0 ];
        status->fault = data_buf[ 1 ];
        status->vbat = CHARGER30_VBAT_ADC_TO_MV( data_buf[ 2 ] );
        status->vsys = CHARGER30_VSYS_ADC_TO_MV( data_buf[ 3 ] );
        status->ntc = CHARGER30_NTC_ADC_TO_PCT( data_buf[ 4 ] );
        status->vin = CHARGER30_VIN_ADC_TO_MV( data_buf[ 5 ] );
        status->ichg = CHARGER30_ICHG_ADC_TO_MA( data_buf[ 6 ] );
        status->iin = CHARGER30_IIN_ADC_TO_MA( data_buf[ 7 ] );
        status->iin_dpm = CHARGER30_PMS_IIN_DPM_ADC_TO_MA( data_buf[ 8 ] );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
