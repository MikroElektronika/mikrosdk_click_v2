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
 * @file charger29.c
 * @brief Charger 29 Click Driver.
 */

#include "charger29.h"

void charger29_cfg_setup ( charger29_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CHARGER29_DEVICE_ADDRESS;
}

err_t charger29_init ( charger29_t *ctx, charger29_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t charger29_default_cfg ( charger29_t *ctx ) 
{
    err_t error_flag = CHARGER29_OK;
    if ( CHARGER29_ERROR == charger29_check_communication ( ctx ) )
    {
        return CHARGER29_ERROR;
    }
    error_flag |= charger29_sw_reset ( ctx );
    Delay_100ms ( );
    error_flag |= charger29_disable_charging ( ctx );
    error_flag |= charger29_set_charging_current ( ctx, CHARGER29_ICHG_DEFAULT );
    error_flag |= charger29_set_vbat_reg ( ctx, CHARGER29_VBAT_DEFAULT );
    error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_CHARGECTRL0, CHARGER29_CHARGECTRL0_EN_FC_MODE_DIS | 
                                                                        CHARGER29_CHARGECTRL0_IPRECHG_2X_TERM | 
                                                                        CHARGER29_CHARGECTRL0_ITERM_10PCT_ICHG | 
                                                                        CHARGER29_CHARGECTRL0_VINDPM_DISABLE | 
                                                                        CHARGER29_CHARGECTRL0_THERM_REG_100C );
    
    error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_CHARGECTRL1, CHARGER29_CHARGECTRL1_IBAT_OCP_1000MA | 
                                                                        CHARGER29_CHARGECTRL1_BUVLO_3_0V | 
                                                                        CHARGER29_CHARGECTRL1_ILIM_INT_MASK | 
                                                                        CHARGER29_CHARGECTRL1_VINDPM_INT_MASK );
    
    error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_IC_CTRL, CHARGER29_IC_CTRL_TS_EN_DISABLE | 
                                                                    CHARGER29_IC_CTRL_VLOWV_SEL_3V | 
                                                                    CHARGER29_IC_CTRL_VRCH_100MV | 
                                                                    CHARGER29_IC_CTRL_2XTMR_EN_DISABLE | 
                                                                    CHARGER29_IC_CTRL_SAFETY_TIMER_6H | 
                                                                    CHARGER29_IC_CTRL_WATCHDOG_SEL_DISABLE );
    
    error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_TMR_ILIM, CHARGER29_TMR_ILIM_MR_LPRESS_10S | 
                                                                     CHARGER29_TMR_ILIM_AUTOWAKE_1S | 
                                                                     CHARGER29_TMR_ILIM_ILIM_500MA );
    
    error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_SHIP_RST, CHARGER29_SHIP_RST_REG_RST_NOTHING | 
                                                                     CHARGER29_SHIP_RST_EN_RST_SHIP_NOTHING | 
                                                                     CHARGER29_SHIP_RST_PB_LPRESS_ACTION_RESET | 
                                                                     CHARGER29_SHIP_RST_WAKE1_TMR_300MS | 
                                                                     CHARGER29_SHIP_RST_WAKE2_TMR_2S | 
                                                                     CHARGER29_SHIP_RST_EN_PUSH_ENABLE );
    
    error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_SYS_REG, CHARGER29_SYS_REG_SYS_REG_CTRL_4_5V | 
                                                                    CHARGER29_SYS_REG_PG_GPO_HIGH_Z | 
                                                                    CHARGER29_SYS_REG_SYS_MODE_VIN | 
                                                                    CHARGER29_SYS_REG_WATCHDOG_15S_ENABLE_DIS | 
                                                                    CHARGER29_SYS_REG_VDPPM_DIS_DISABLE );
    
    error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_TS_CONTROL, CHARGER29_TS_CONTROL_TS_HOT_60C | 
                                                                       CHARGER29_TS_CONTROL_TS_COLD_0C | 
                                                                       CHARGER29_TS_CONTROL_TS_WARM_DIS_45C | 
                                                                       CHARGER29_TS_CONTROL_TS_COOL_DIS_10C | 
                                                                       CHARGER29_TS_CONTROL_TS_ICHG_0_5_ICHG | 
                                                                       CHARGER29_TS_CONTROL_TS_VRCG_VBATREG_100MV );
    
    error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_MASK_ID, CHARGER29_MASK_ID_TS_INT_MASK | 
                                                                    CHARGER29_MASK_ID_TREG_INT_MASK | 
                                                                    CHARGER29_MASK_ID_BAT_INT_MASK | 
                                                                    CHARGER29_MASK_ID_PG_INT_MASK );
    error_flag |= charger29_enable_charging ( ctx );
    return error_flag;
}

err_t charger29_write_reg ( charger29_t *ctx, uint8_t reg, uint8_t data_in )
{
    return charger29_write_regs( ctx, reg, &data_in, 1 );
}

err_t charger29_write_regs ( charger29_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ CHARGER29_REG_MASK_ID - CHARGER29_REG_VBAT_CTRL + 2 ] = { 0 };
    if ( ( reg < CHARGER29_REG_VBAT_CTRL ) || 
         ( ( reg + len ) > ( CHARGER29_REG_MASK_ID + 1 ) ) ||
         ( NULL == data_in ) )
    {
        return CHARGER29_ERROR;
    }
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t charger29_read_reg ( charger29_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return charger29_read_regs( ctx, reg, data_out, 1 );
}

err_t charger29_read_regs ( charger29_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( ( ( reg + len ) > ( CHARGER29_REG_MASK_ID + 1 ) ) || 
         ( NULL == data_out ) )
    {
        return CHARGER29_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t charger29_get_int_pin ( charger29_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t charger29_check_communication ( charger29_t *ctx )
{
    uint8_t mask_id = 0;
    if ( CHARGER29_OK == charger29_read_reg ( ctx, CHARGER29_REG_MASK_ID, &mask_id ) )
    {
        if ( CHARGER29_MASK_ID_DEVICE_ID == ( CHARGER29_MASK_ID_DEVICE_ID_MASK & mask_id ) )
        {
            return CHARGER29_OK;
        }
    }
    return CHARGER29_ERROR;
}

err_t charger29_sw_reset ( charger29_t *ctx )
{
    err_t error_flag = CHARGER29_OK;
    uint8_t reg_data = 0;
    error_flag |= charger29_read_reg ( ctx, CHARGER29_REG_SHIP_RST, &reg_data );
    if ( CHARGER29_OK == error_flag )
    {
        reg_data |= CHARGER29_SHIP_RST_REG_RST_RESET;
        error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_SHIP_RST, reg_data );
    }
    return error_flag;
}

err_t charger29_enable_charging ( charger29_t *ctx )
{
    err_t error_flag = CHARGER29_OK;
    uint8_t reg_data = 0;
    error_flag |= charger29_read_reg ( ctx, CHARGER29_REG_ICHG_CTRL, &reg_data );
    if ( CHARGER29_OK == error_flag )
    {
        reg_data &= ( ~CHARGER29_ICHG_CTRL_CHG_DIS_MASK );
        error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_ICHG_CTRL, reg_data );
    }
    return error_flag;
}

err_t charger29_disable_charging ( charger29_t *ctx )
{
    err_t error_flag = CHARGER29_OK;
    uint8_t reg_data = 0;
    error_flag |= charger29_read_reg ( ctx, CHARGER29_REG_ICHG_CTRL, &reg_data );
    if ( CHARGER29_OK == error_flag )
    {
        reg_data |= CHARGER29_ICHG_CTRL_CHG_DIS_MASK;
        error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_ICHG_CTRL, reg_data );
    }
    return error_flag;
}

err_t charger29_set_charging_current ( charger29_t *ctx, uint16_t ichg )
{
    err_t error_flag = CHARGER29_OK;
    uint8_t reg_data = 0;
    uint8_t ichgcode = 0;
    if ( ( ichg <= CHARGER29_ICHG_RES_POINT ) && ( ichg >= CHARGER29_ICHG_MIN ) )
    {
        ichgcode = ichg - CHARGER29_ICHG_MIN;
    }
    else if ( ( ichg > CHARGER29_ICHG_RES_POINT ) && ( ichg <= CHARGER29_ICHG_MAX ) )
    {
        ichgcode = ( ( ichg - CHARGER29_ICHG_RES_POINT ) / CHARGER29_ICHG_RES_DIVIDER + CHARGER29_ICHG_RES_OFFSET );
    }
    else
    {
        return CHARGER29_ERROR;
    }
    error_flag |= charger29_read_reg ( ctx, CHARGER29_REG_ICHG_CTRL, &reg_data );
    if ( CHARGER29_OK == error_flag )
    {
        reg_data &= ( ~CHARGER29_ICHG_CTRL_ICHG_MASK );
        reg_data |= ichgcode;
        error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_ICHG_CTRL, reg_data );
    }
    return error_flag;
}

err_t charger29_set_vbat_reg ( charger29_t *ctx, uint16_t vbat_mv )
{
    err_t error_flag = CHARGER29_OK;
    uint8_t reg_data = 0;
    uint8_t vbatreg = 0;
    if ( ( vbat_mv < CHARGER29_VBAT_MIN ) || ( vbat_mv > CHARGER29_VBAT_MAX ) )
    {
        return CHARGER29_ERROR;
    }
    vbatreg = ( vbat_mv - CHARGER29_VBAT_MIN ) / CHARGER29_VBAT_RES_DIVIDER;
    error_flag |= charger29_read_reg ( ctx, CHARGER29_REG_VBAT_CTRL, &reg_data );
    if ( CHARGER29_OK == error_flag )
    {
        reg_data &= ( ~CHARGER29_VBAT_CTRL_VBATREG_MASK );
        reg_data |= vbatreg;
        error_flag |= charger29_write_reg ( ctx, CHARGER29_REG_VBAT_CTRL, reg_data );
    }
    return error_flag;
}

err_t charger29_read_status ( charger29_t *ctx, charger29_status_t *status )
{
    err_t error_flag = CHARGER29_OK;
    error_flag |= charger29_read_reg ( ctx, CHARGER29_REG_STAT0, &status->stat0 );
    error_flag |= charger29_read_reg ( ctx, CHARGER29_REG_STAT1, &status->stat1 );
    error_flag |= charger29_read_reg ( ctx, CHARGER29_REG_FLAG0, &status->flag0 );
    return error_flag;
}

// ------------------------------------------------------------------------- END
