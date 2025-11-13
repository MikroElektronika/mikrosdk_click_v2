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
 * @file charger31.c
 * @brief Charger 31 Click Driver.
 */

#include "charger31.h"

void charger31_cfg_setup ( charger31_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->st_ib = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CHARGER31_DEVICE_ADDRESS;
}

err_t charger31_init ( charger31_t *ctx, charger31_cfg_t *cfg ) 
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

    digital_in_init( &ctx->st_ib, cfg->st_ib );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t charger31_default_cfg ( charger31_t *ctx ) 
{
    err_t error_flag = CHARGER31_OK;
    
    error_flag |= charger31_sw_reset ( ctx );
    Delay_100ms ( );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_CHG_CTRL0, 
                                        CHARGER31_CHG_CTRL0_REG_RST_KEEP | 
                                        CHARGER31_CHG_CTRL0_EN_STAT_IB_STAT | 
                                        CHARGER31_CHG_CTRL0_EN_PG_NTC2_PG | 
                                        CHARGER31_CHG_CTRL0_LOCK_CHG_UNLOCKED | 
                                        CHARGER31_CHG_CTRL0_HOLDOFF_TMR_EN | 
                                        CHARGER31_CHG_CTRL0_SW_FREQ_1M | 
                                        CHARGER31_CHG_CTRL0_EN_VIN_TRK_VBATT );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_IIN, 
                                        CHARGER31_IIN_MODE_LIM | 
                                        CHARGER31_IIN_LIM_MA ( CHARGER31_IIN_LIM_MA_DEFAULT ) );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_CHG_PAR0, 
                                        CHARGER31_CHG_PAR0_VPRE_3_2V | 
                                        CHARGER31_CHG_PAR0_ICC_MA ( CHARGER31_CHG_PAR0_ICC_MA_DEFAULT ) );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_CHG_PAR1, 
                                        CHARGER31_CHG_PAR1_IPRE_MA ( CHARGER31_CHG_PAR1_IPRE_MA_DEFAULT ) | 
                                        CHARGER31_CHG_PAR1_ITERM_MA ( CHARGER31_CHG_PAR1_ITERM_MA_DEFAULT ) );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_CHG_PAR2,
                                        CHARGER31_CHG_PAR2_VRECHG_100MV |
                                        CHARGER31_CHG_PAR2_ITRICKLE_MA ( CHARGER31_CHG_PAR2_ITRICKLE_MA_DEFAULT ) | 
                                        CHARGER31_CHG_PAR2_VIN_LIM_MV ( CHARGER31_CHG_PAR2_VIN_LIM_MV_DEFAULT ) );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_CHG_PAR3,
                                        CHARGER31_CHG_PAR3_TOPOFF_TMR_DIS |
                                        CHARGER31_CHG_PAR3_VBATT_MV ( CHARGER31_CHG_PAR3_VBATT_MV_DEFAULT ) );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_CHG_CTRL1,
                                        CHARGER31_CHG_CTRL1_SYS_MIN_3_588V | CHARGER31_CHG_CTRL1_TREG_100_C );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_CHG_CTRL2,
                                        CHARGER31_CHG_CTRL2_IB_EN_WHEN_SW_ON | 
                                        CHARGER31_CHG_CTRL2_WATCHDOG_RST_RESET | 
                                        CHARGER31_CHG_CTRL2_WATCHDOG_DIS | 
                                        CHARGER31_CHG_CTRL2_EN_TERM_EN | 
                                        CHARGER31_CHG_CTRL2_EN_TMR2X_EN | 
                                        CHARGER31_CHG_CTRL2_CHG_TIMER_10H );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_CHG_CTRL3,
                                        CHARGER31_CHG_CTRL3_BATTFET_DIS_OFF | 
                                        CHARGER31_CHG_CTRL3_BATTFET_DLY_10S | 
                                        CHARGER31_CHG_CTRL3_BATTFET_RST_EN_ON | 
                                        CHARGER31_CHG_CTRL3_OLIM_3A | 
                                        CHARGER31_CHG_CTRL3_VBOOST_5_15V );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_CHG_CTRL4,
                                        CHARGER31_CHG_CTRL4_CC_CFG_DIS | 
                                        CHARGER31_CHG_CTRL4_EN_BOOST_DIS | 
                                        CHARGER31_CHG_CTRL4_EN_BUCK_EN | 
                                        CHARGER31_CHG_CTRL4_EN_CHG_EN );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_VIN_DET,
                                        CHARGER31_VIN_DET_AUTODPDM_EN | 
                                        CHARGER31_VIN_DET_FORCEDPDM_DIS | 
                                        CHARGER31_VIN_DET_FORCE_CC_EN );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_CHG_CTRL5,
                                        CHARGER31_CHG_CTRL5_NTC1_ACTION_ON_CHG | 
                                        CHARGER31_CHG_CTRL5_NTC2_ACTION_ON_CHG | 
                                        CHARGER31_CHG_CTRL5_BATT_OVP_EN_ON | 
                                        CHARGER31_CHG_CTRL5_BATT_LOW_3V | 
                                        CHARGER31_CHG_CTRL5_BOOST_STP_EN_OFF | 
                                        CHARGER31_CHG_CTRL5_BOOST_OTP_EN_ON );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_NTC_ACTION,
                                        CHARGER31_NTC_ACTION_WARM_ACT_VBATT | 
                                        CHARGER31_NTC_ACTION_COOL_ACT_ICC | 
                                        CHARGER31_NTC_ACTION_JEITA_VSET_100_MV | 
                                        CHARGER31_NTC_ACTION_JEITA_ISET_50_PCT );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_NTC_TH,
                                        CHARGER31_NTC_TH_VHOT_60_C | 
                                        CHARGER31_NTC_TH_VWARM_45_C | 
                                        CHARGER31_NTC_TH_VCOOL_10_C | 
                                        CHARGER31_NTC_TH_VCOLD_0_C );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_VIN_IMPD,
                                        CHARGER31_VIN_IMPD_VIN_SRC_EN_OFF | 
                                        CHARGER31_VIN_IMPD_IVIN_SRC_5_UA | 
                                        CHARGER31_VIN_IMPD_VIN_TEST_0_3V );
    error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_INT_MASK,
                                        CHARGER31_INT_MASK_MASK_RESERVED | 
                                        CHARGER31_INT_MASK_MASK_THERM_OFF | 
                                        CHARGER31_INT_MASK_MASK_DPM_OFF | 
                                        CHARGER31_INT_MASK_MASK_TOPOFF_OFF | 
                                        CHARGER31_INT_MASK_MASK_CC_INT_ON | 
                                        CHARGER31_INT_MASK_MASK_BATT_LOW_OFF | 
                                        CHARGER31_INT_MASK_MASK_DEBUG_OFF );

    return error_flag;
}

err_t charger31_write_reg ( charger31_t *ctx, uint8_t reg, uint8_t data_in )
{
    return charger31_write_regs( ctx, reg, &data_in, 1 );
}

err_t charger31_write_regs ( charger31_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ CHARGER31_REG_INT_MASK + 2 ] = { 0 };
    if ( ( reg > CHARGER31_REG_INT_MASK ) ||
         ( ( reg + len ) > ( CHARGER31_REG_INT_MASK + 1 ) ) ||
         ( NULL == data_in ) )
    {
        return CHARGER31_ERROR;
    }
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t charger31_read_reg ( charger31_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return charger31_read_regs( ctx, reg, data_out, 1 );
}

err_t charger31_read_regs ( charger31_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( ( ( reg + len ) > ( CHARGER31_REG_STATUS5 + 1 ) ) || 
         ( NULL == data_out ) )
    {
        return CHARGER31_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t charger31_get_st_ib_pin ( charger31_t *ctx )
{
    return digital_in_read ( &ctx->st_ib );
}

uint8_t charger31_get_int_pin ( charger31_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t charger31_sw_reset ( charger31_t *ctx )
{
    err_t error_flag = CHARGER31_OK;
    uint8_t reg_data = 0;
    error_flag |= charger31_read_reg ( ctx, CHARGER31_REG_CHG_CTRL0, &reg_data );
    if ( CHARGER31_OK == error_flag )
    {
        reg_data |= CHARGER31_CHG_CTRL0_REG_RST_RESET;
        error_flag |= charger31_write_reg ( ctx, CHARGER31_REG_CHG_CTRL0, reg_data );
    }
    return error_flag;
}

err_t charger31_read_status ( charger31_t *ctx, charger31_status_t *status )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = CHARGER31_OK;
    error_flag |= charger31_read_regs ( ctx, CHARGER31_REG_STATUS0, data_buf, 6 );
    if ( ( NULL != status ) && ( CHARGER31_OK == error_flag ) )
    {
        status->status_0 = data_buf[ 0 ];
        status->status_1 = data_buf[ 1 ];
        status->status_2 = data_buf[ 2 ];
        status->status_3 = data_buf[ 3 ];
        status->status_4 = data_buf[ 4 ];
        status->status_5 = data_buf[ 5 ];
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
