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
 * @file battman3.c
 * @brief BATT-MAN 3 Click Driver.
 */

#include "battman3.h"
#include "math.h"

/**
 * @brief BATT-MAN 3 Click battery voltage calculation macros.
 * @details Battery voltage macros for calculations.
 */
#define VBAT_LSB_DIV                8.0
#define VBAT_MSB_MLT                32.0
#define CHARGE_TERMINATION_MAX      4.5
#define CHARGE_TERMINATION_MIN      3.5
#define CHARGE_TERMINATION_STEP     0.02
#define CHARGE_THRESHOLD_MAX        3.4
#define CHARGE_THRESHOLD_MIN        2.7
#define CHARGE_THRESHOLD_STEP       0.1
#define CHARGE_CURRENT_LIMIT_MAX    1500
#define CHARGE_CURRENT_LIMIT_MIN    100


void battman3_cfg_setup ( battman3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->pgood   = HAL_PIN_NC;
    cfg->bok = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BATTMAN3_SET_DEV_ADDR;
}

err_t battman3_init ( battman3_t *ctx, battman3_cfg_t *cfg ) 
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

    digital_in_init( &ctx->bok, cfg->bok );
    digital_in_init( &ctx->pgood, cfg->pgood );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t battman3_default_cfg ( battman3_t *ctx ) 
{
    err_t error_flag = BATTMAN3_OK;
    uint8_t temp_data = 0;
    
    error_flag |= battman3_reg_write( ctx, BATTMAN3_REG_SOC_RESET, 0x80 );
    //Enable fuel gauge to enable vbat sens
    error_flag |= battman3_reg_read( ctx, BATTMAN3_REG_FUEL_GAUGE_MODE, &temp_data );
    temp_data &= 0xFE;
    temp_data |= 0x01;
    error_flag |= battman3_reg_write( ctx, BATTMAN3_REG_FUEL_GAUGE_MODE, temp_data );
    //Charging
    error_flag |= battman3_set_charge_state( ctx, BATTMAN3_ENABLE );
    //PGOOD interrupt
    error_flag |= battman3_reg_write( ctx, BATTMAN3_REG_PGOOD_MASK, 0xC );

    return error_flag;
}

err_t battman3_generic_write ( battman3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 0x3F ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t battman3_reg_write ( battman3_t *ctx, uint8_t reg, uint8_t tx_data )
{
    uint8_t data_buf[ 2 ] = { reg, tx_data };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t battman3_generic_read ( battman3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t battman3_reg_read ( battman3_t *ctx, uint8_t reg, uint8_t *rx_data )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_data, 1 );
}

uint8_t battman3_get_battery_ok ( battman3_t *ctx )
{
    return digital_in_read( &ctx->bok );
}

uint8_t battman3_get_power_good ( battman3_t *ctx )
{
    return digital_in_read( &ctx->pgood );
}

uint8_t battman3_get_interrupt ( battman3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t battman3_set_charge_state ( battman3_t *ctx, uint8_t enable )
{
    uint8_t reg_data = 0;
    battman3_reg_read( ctx, BATTMAN3_REG_CHARGER_FUNCTION_SETTING1, &reg_data );
    reg_data &= 0xFE;
    if ( enable )
    {
        reg_data |= 0x01;
    }
    return battman3_reg_write( ctx, BATTMAN3_REG_CHARGER_FUNCTION_SETTING1, reg_data );
}

err_t battman3_set_charge_vbus_current_limit ( battman3_t *ctx, uint16_t current )
{
    if ( ( current < CHARGE_CURRENT_LIMIT_MIN ) || ( current > CHARGE_CURRENT_LIMIT_MAX ) )
    {
        return BATTMAN3_ERROR;
    }
    current -= 50.0;
    uint8_t reg_data = ceil( current / 100.0 );
    return battman3_reg_write( ctx, BATTMAN3_REG_CHARGER_VBUS_ILIM, reg_data );
}

err_t battman3_set_charge_termination_voltage ( battman3_t *ctx, float voltage )
{
    if ( ( voltage > CHARGE_TERMINATION_MAX ) || ( voltage < CHARGE_TERMINATION_MIN ) )
    {
        return BATTMAN3_ERROR;
    }
    
    voltage -= CHARGE_TERMINATION_MIN;
    voltage /= CHARGE_TERMINATION_STEP;
    uint8_t reg_data = 0;
    battman3_reg_read( ctx, BATTMAN3_REG_CHARGER_TERMINATION_SETTING, &reg_data );
    reg_data &= 0x3;
    reg_data |= ( uint8_t )ceil( voltage ) << 2;
    return battman3_reg_write( ctx, BATTMAN3_REG_CHARGER_TERMINATION_SETTING, reg_data );
}

err_t battman3_set_charge_voltage_threshold ( battman3_t *ctx, battman3_vtrk_dead_t vtrk_dead, float vweak )
{
    if ( ( vweak > CHARGE_THRESHOLD_MAX ) || ( vweak < CHARGE_THRESHOLD_MIN ) )
    {
        return BATTMAN3_ERROR;
    }
    
    vweak -= CHARGE_THRESHOLD_MIN;
    vweak /= CHARGE_THRESHOLD_STEP;
    uint8_t reg_data = 0;
    battman3_reg_read( ctx, BATTMAN3_REG_CHARGER_TERMINATION_SETTING, &reg_data );
    reg_data &= 0xE0;
    //weak
    reg_data |= ( uint8_t )ceil( vweak );
    //vtrk
    reg_data |= vtrk_dead << 3;
    return battman3_reg_write( ctx, BATTMAN3_REG_CHARGER_TERMINATION_SETTING, reg_data );
}

err_t battman3_set_ldo_vout ( battman3_t *ctx, battman3_ldo_t ldo, battman3_ldo_vout_t vout )
{
    err_t ret_val = BATTMAN3_OK;
    uint8_t reg_data = 0;
    switch ( ldo )
    {
        case BATTMAN3_LDO1:
        {
            ret_val |= battman3_reg_read( ctx, BATTMAN3_REG_VID_LDO12, &reg_data );
            reg_data &= 0xF0;
            reg_data |= vout;
            ret_val |= battman3_reg_write( ctx, BATTMAN3_REG_VID_LDO12, reg_data );
            break;
        }
        case BATTMAN3_LDO2:
        {
            ret_val |= battman3_reg_read( ctx, BATTMAN3_REG_VID_LDO12, &reg_data );
            reg_data &= 0x0F;
            reg_data |= vout << 4;
            ret_val |= battman3_reg_write( ctx, BATTMAN3_REG_VID_LDO12, reg_data );
            break;
        }
        case BATTMAN3_LDO3:
        {
            reg_data = vout;
            ret_val |= battman3_reg_write( ctx, BATTMAN3_REG_VID_LDO3, reg_data );
            break;
        }
        default:
        {
            ret_val = BATTMAN3_ERROR;
            break;
        }
    }
    return ret_val;
}

err_t battman3_set_ldo_state ( battman3_t *ctx, battman3_ldo_t ldo, uint8_t enable )
{
    err_t ret_val = BATTMAN3_ERROR;
    uint8_t reg_data = 0;
    uint8_t temp_data = 0;
    ret_val |= battman3_reg_read( ctx, BATTMAN3_REG_LDO_CTRL, &reg_data );
    if ( enable )
    {
        reg_data |= 1 << ldo;
    }
    else
    {
        reg_data &= ~( 1 << ldo );
    }
    ret_val |= battman3_reg_write( ctx, BATTMAN3_REG_LDO_CTRL, reg_data );
    return ret_val;
}

err_t battman3_get_battery_voltage ( battman3_t *ctx, float *vout )
{
    uint8_t temp_buf[ 2 ] = { 0 };
    err_t ret_val = battman3_generic_read( ctx, BATTMAN3_REG_VBAT_READ_H, temp_buf, 2 );
    *vout = temp_buf[ 0 ] * VBAT_MSB_MLT + temp_buf[ 1 ] / VBAT_LSB_DIV; 
    return ret_val;
}

// ------------------------------------------------------------------------- END
