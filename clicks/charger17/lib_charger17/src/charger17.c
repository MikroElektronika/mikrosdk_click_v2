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
 * @file charger17.c
 * @brief Charger 17 Click Driver.
 */

#include "charger17.h"

void charger17_cfg_setup ( charger17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ce   = HAL_PIN_NC;
    cfg->qon  = HAL_PIN_NC;
    cfg->psel = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CHARGER17_DEVICE_ADDRESS;
}

err_t charger17_init ( charger17_t *ctx, charger17_cfg_t *cfg ) 
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

    digital_out_init( &ctx->qon, cfg->qon );
    digital_out_init( &ctx->ce, cfg->ce );
    digital_out_init( &ctx->psel, cfg->psel );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t charger17_default_cfg ( charger17_t *ctx ) 
{
    err_t error_flag = CHARGER17_OK;
    charger17_set_qon_pin ( ctx, 1 );
    charger17_set_psel_2400mA ( ctx );
    charger17_disable_charging ( ctx );
    Delay_100ms ( );
    if ( CHARGER17_ERROR == charger17_check_communication ( ctx ) )
    {
        return CHARGER17_ERROR;
    }
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_OTG_CONFIG, CHARGER17_OTG_CV_5p15V | 
                                                                            CHARGER17_OTG_LBP_2p8V | 
                                                                            CHARGER17_OTG_CC_1p2A );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_TOP, CHARGER17_TOP_QON_RST_EN | 
                                                                     CHARGER17_TOP_STAT_EN | 
                                                                     CHARGER17_TOP_WDT_DISABLE );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_FUNCTION, CHARGER17_FUNCTION_BATFET_DIS_DLY_12S | 
                                                                          CHARGER17_FUNCTION_CHG_EN );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_IBUS, CHARGER17_IBUS_AUTO_AICR |
                                                                      CHARGER17_IBUS_IAICR( 500 ) );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_VBUS, CHARGER17_VBUS_VAC_OVP_6p5V | 
                                                                      CHARGER17_VBUS_VMIVR_BAT_TRACK_4300mV | 
                                                                      CHARGER17_VBUS_VMIVR( 4500 ) );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_PRECHG, CHARGER17_PRECHG_V( 3100 ) | 
                                                                        CHARGER17_PRECHG_I( 150 ) );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_REGU, CHARGER17_REGU_THREG_120_DEGC | 
                                                                      CHARGER17_REGU_VSYS_MIN( 3500 ) );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_VCHG, CHARGER17_VCHG_VPRE_CHG_200mV | 
                                                                      CHARGER17_VCHG_VBAT_REG( 4200 ) );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_ICHG, CHARGER17_ICHG_REG( 2000 ) );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_CHG_TIMER, CHARGER17_CHG_TIMER_CHG_SAFE_TMR_EN | 
                                                                           CHARGER17_CHG_TIMER_CHG_SAFE_TMR_2XT |
                                                                           CHARGER17_CHG_TIMER_CHG_SAFE_TMR_10HR );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_EOC, CHARGER17_EOC_IEOC_CHG( 200 ) |
                                                                     CHARGER17_EOC_BG_CHG_TMR_0MIN |
                                                                     CHARGER17_EOC_TE );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_JEITA, CHARGER17_JEITA_EN | 
                                                                       CHARGER17_JEITA_COOL_ISET_25PCT | 
                                                                       CHARGER17_JEITA_COOL_VSET_VBAT_REG | 
                                                                       CHARGER17_JEITA_WARM_ISET_ICHG_REG );
    error_flag |= charger17_write_register ( ctx, CHARGER17_REG_DPDM_DET, CHARGER17_DPDM_DET_BC12_EN | 
                                                                          CHARGER17_DPDM_DET_SPEC_TA_EN );
    charger17_enable_charging ( ctx );
    return error_flag;
}

err_t charger17_generic_write ( charger17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    if ( len > 32 )
    {
        return CHARGER17_ERROR;
    }
    uint8_t data_buf[ 33 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t charger17_generic_read ( charger17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t charger17_write_register ( charger17_t *ctx, uint8_t reg, uint8_t data_in )
{
    return charger17_generic_write ( ctx, reg, &data_in, 1 );
}

err_t charger17_read_register ( charger17_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return charger17_generic_read ( ctx, reg, data_out, 1 );
}

err_t charger17_check_communication ( charger17_t *ctx )
{
    uint8_t device_id;
    if ( CHARGER17_OK == charger17_read_register ( ctx, CHARGER17_REG_INFO, &device_id ) )
    {
        if ( CHARGER17_INFO_DEVICE_ID == ( device_id & CHARGER17_INFO_DEVICE_ID_MASK ) )
        {
            return CHARGER17_OK;
        }
    }
    return CHARGER17_ERROR;
}

void charger17_set_qon_pin ( charger17_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->qon, state );
}

void charger17_enable_charging ( charger17_t *ctx )
{
    digital_out_low ( &ctx->ce );
}

void charger17_disable_charging ( charger17_t *ctx )
{
    digital_out_high ( &ctx->ce );
}

void charger17_set_psel_500mA ( charger17_t *ctx )
{
    digital_out_high ( &ctx->psel );
}

void charger17_set_psel_2400mA ( charger17_t *ctx )
{
    digital_out_low ( &ctx->psel );
}

uint8_t charger17_get_int_pin ( charger17_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
