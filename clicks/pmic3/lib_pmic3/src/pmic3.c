/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file pmic3.c
 * @brief PMIC 3 Click Driver.
 */

#include "pmic3.h"
#include "math.h"

/**
 * @brief PMIC 3 driver data settings.
 * @details Defines I2C frame positions, register block sizes, and default
 * regulator configuration table lengths.
 */
#define PMIC3_REG_ADDR_INDEX                    0
#define PMIC3_REG_VALUE_INDEX                   1
#define PMIC3_REG_ADDR_SIZE                     1
#define PMIC3_REG_DATA_SIZE                     1
#define PMIC3_REG_WRITE_SIZE                    2
#define PMIC3_DEVICE0_STS_INDEX                 0
#define PMIC3_DEVICE1_STS_INDEX                 1
#define PMIC3_CHARGER0_STS_INDEX                2
#define PMIC3_CHARGER1_STS_INDEX                3
#define PMIC3_CHARGER2_STS_INDEX                4
#define PMIC3_CHARGER3_STS_INDEX                5
#define PMIC3_STATUS_REG_COUNT                  6
#define PMIC3_CHARGER_CFG1_INDEX                0
#define PMIC3_CHARGER_CFG2_INDEX                1
#define PMIC3_CHARGER_CFG_COUNT                 2
#define PMIC3_CHARGER_BURST_ADDR_INDEX          0
#define PMIC3_CHARGER_BURST_LOCK_INDEX          1
#define PMIC3_CHARGER_BURST_CFG1_INDEX          2
#define PMIC3_CHARGER_BURST_CFG2_INDEX          3
#define PMIC3_CHARGER_BURST_CFG3_INDEX          4
#define PMIC3_CHARGER_BURST_WRITE_SIZE          5
#define PMIC3_BUCK_CFG_COUNT                    4
#define PMIC3_LDO_CFG_COUNT                     4

/**
 * @brief PMIC 3 charger restart states.
 * @details Defines the internal states used to request a new battery
 * qualification cycle.
 */
#define PMIC3_RESTART_NOT_REQUIRED              0
#define PMIC3_RESTART_REQUIRED                  1

/**
 * @brief PMIC 3 protected charger register update function.
 * @details This function unlocks the protected charger register block,
 * updates the selected field, verifies the written value, and restores write
 * protection.
 * @param[in] ctx : Click context object.
 * See #pmic3_t object definition for detailed explanation.
 * @param[in] reg : Protected charger register address.
 * @param[in] mask : Register field mask.
 * @param[in] value : Register field value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pmic3_update_charger_reg ( pmic3_t *ctx, uint8_t reg, uint8_t mask, uint8_t value );

void pmic3_cfg_setup ( pmic3_cfg_t *cfg )
{
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->amux = HAL_PIN_NC;
    cfg->on = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PMIC3_DEVICE_ADDRESS;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = PMIC3_VREF;
}

err_t pmic3_init ( pmic3_t *ctx, pmic3_cfg_t *cfg )
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

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->amux;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) )
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) )
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) )
    {
        return ADC_ERROR;
    }

    ctx->vref = cfg->vref;

    // ON is active low; keep it inactive until a deliberate wake pulse is needed.
    digital_out_init( &ctx->on, cfg->on );
    Delay_1ms ( );
    digital_out_high( &ctx->on );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    ctx->battery_state        = PMIC3_BATTERY_UNKNOWN;
    ctx->battery_confirm_cnt  = 0;

    return PMIC3_OK;
}

err_t pmic3_default_cfg ( pmic3_t *ctx )
{
    err_t error_flag = PMIC3_OK;
    err_t lock_flag = PMIC3_OK;
    uint8_t buck_id[ PMIC3_BUCK_CFG_COUNT ] = { PMIC3_BUCK_1, PMIC3_BUCK_2, PMIC3_BUCK_3, PMIC3_BUCK_4 };
    uint16_t buck_voltage[ PMIC3_BUCK_CFG_COUNT ] = { PMIC3_PCA9422M_BUCK1_MV, PMIC3_PCA9422M_BUCK2_MV,
                                                      PMIC3_PCA9422M_BUCK3_MV, PMIC3_PCA9422M_BUCK4_MV };
    uint8_t ldo_id[ PMIC3_LDO_CFG_COUNT ] = { PMIC3_LDO_1, PMIC3_LDO_2, PMIC3_LDO_3, PMIC3_LDO_4 };
    uint16_t ldo_voltage[ PMIC3_LDO_CFG_COUNT ] = { PMIC3_PCA9422M_LDO1_MV, PMIC3_PCA9422M_LDO2_MV,
                                                    PMIC3_PCA9422M_LDO3_MV, PMIC3_PCA9422M_LDO4_MV };
    uint8_t charger_cfg[ PMIC3_CHARGER_CFG_COUNT ] = { PMIC3_CHARGER_CFG1_DEFAULT & ( uint8_t ) ~PMIC3_CHARGER_ENABLE_MASK,
                                                       PMIC3_CHARGER_CFG2_DEFAULT };
    uint8_t charger_verify[ PMIC3_CHARGER_CFG_COUNT ] = { 0 };
    uint8_t cfg_cnt = 0;
    uint8_t power_state = 0;
    uint8_t vin_current_verify = 0;

    // Confirm the expected device before changing power or charger settings.
    error_flag = pmic3_check_communication( ctx );
    if ( PMIC3_OK == error_flag )
    {
        error_flag = pmic3_read_reg( ctx, PMIC3_REG_PWR_STATE, &power_state );
    }

    // Apply a debounced ON pulse only when the PMIC is currently off.
    if ( ( PMIC3_OK == error_flag ) &&
         ( PMIC3_PWR_STATE_OFF == ( power_state & PMIC3_PWR_STATE_STAT_MASK ) ) )
    {
        pmic3_set_on_pin( ctx, PMIC3_ON_ACTIVE );
        Delay_1ms( );
        pmic3_set_on_pin( ctx, PMIC3_ON_INACTIVE );
        Delay_100ms( );
    }

    // Restore the PCA9422M active regulator voltage configuration.
    while ( ( PMIC3_OK == error_flag ) && ( PMIC3_BUCK_CFG_COUNT > cfg_cnt ) )
    {
        error_flag = pmic3_set_buck_voltage( ctx, buck_id[ cfg_cnt ], buck_voltage[ cfg_cnt ] );
        cfg_cnt++;
    }

    cfg_cnt = 0;
    while ( ( PMIC3_OK == error_flag ) && ( PMIC3_LDO_CFG_COUNT > cfg_cnt ) )
    {
        error_flag = pmic3_set_ldo_voltage( ctx, ldo_id[ cfg_cnt ], ldo_voltage[ cfg_cnt ] );
        cfg_cnt++;
    }

    if ( PMIC3_OK == error_flag )
    {
        // Disconnect AMUX from the output while its channel is not being sampled.
        error_flag = pmic3_set_amux_channel( ctx, PMIC3_AMUX_CHANNEL_OFF );
    }

    // Apply and verify the input-current limit independently of charger settings.
    if ( PMIC3_OK == error_flag )
    {
        error_flag = pmic3_write_reg( ctx, PMIC3_REG_VIN_CNTL2, PMIC3_VIN_CURRENT_LIMIT_DEFAULT );
    }
    if ( PMIC3_OK == error_flag )
    {
        error_flag = pmic3_read_reg( ctx, PMIC3_REG_VIN_CNTL2, &vin_current_verify );
    }
    if ( ( PMIC3_OK == error_flag ) &&
         ( PMIC3_VIN_CURRENT_LIMIT_DEFAULT != ( vin_current_verify & PMIC3_VIN_CURRENT_LIMIT_MASK ) ) )
    {
        error_flag = PMIC3_ERROR;
    }

    if ( PMIC3_OK == error_flag )
    {
        // Restore the charger baseline while keeping it disabled.
        error_flag = pmic3_set_charger_lock( ctx, PMIC3_CHARGER_UNLOCKED );
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_write_reg( ctx, PMIC3_REG_CHARGER_CNTL1, charger_cfg[ PMIC3_CHARGER_CFG1_INDEX ] );
        }
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_write_reg( ctx, PMIC3_REG_CHARGER_CNTL2, charger_cfg[ PMIC3_CHARGER_CFG2_INDEX ] );
        }
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_regs( ctx, PMIC3_REG_CHARGER_CNTL1, charger_verify, PMIC3_CHARGER_CFG_COUNT );
        }
        if ( ( PMIC3_OK == error_flag ) &&
             ( ( charger_cfg[ PMIC3_CHARGER_CFG1_INDEX ] != charger_verify[ PMIC3_CHARGER_CFG1_INDEX ] ) ||
               ( charger_cfg[ PMIC3_CHARGER_CFG2_INDEX ] != charger_verify[ PMIC3_CHARGER_CFG2_INDEX ] ) ) )
        {
            error_flag = PMIC3_ERROR;
        }

        lock_flag = pmic3_set_charger_lock( ctx, PMIC3_CHARGER_LOCKED );
        if ( PMIC3_OK == error_flag )
        {
            error_flag = lock_flag;
        }
    }

    if ( PMIC3_OK == error_flag )
    {
        // Set the fast-charge current before starting battery qualification.
        error_flag = pmic3_set_charge_current( ctx, PMIC3_DEFAULT_CHARGE_CURRENT_MA );
    }

    if ( PMIC3_OK == error_flag )
    {
        // Enabling the charger starts a new battery qualification cycle.
        error_flag = pmic3_set_charger( ctx, PMIC3_CHARGER_ENABLED );
    }

    if ( PMIC3_OK == error_flag )
    {
        ctx->battery_state = PMIC3_BATTERY_UNKNOWN;
        ctx->battery_confirm_cnt = 0;
        Delay_100ms( );
    }

    return error_flag;
}

err_t pmic3_write_reg ( pmic3_t *ctx, uint8_t reg, uint8_t data_in )
{
    return pmic3_write_regs( ctx, reg, &data_in, 1 );
}

err_t pmic3_write_regs ( pmic3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t pmic3_read_reg ( pmic3_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return pmic3_read_regs( ctx, reg, data_out, 1 );
}

err_t pmic3_read_regs ( pmic3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t pmic3_read_raw_adc ( pmic3_t *ctx, uint16_t *raw_adc )
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t pmic3_read_voltage ( pmic3_t *ctx, float *voltage )
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t pmic3_read_voltage_avg ( pmic3_t *ctx, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    if ( 0 == num_conv )
    {
        return PMIC3_ERROR;
    }
    while ( cnt < num_conv )
    {
        if ( PMIC3_OK == pmic3_read_voltage ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > PMIC3_TIMEOUT_MS )
        {
            return PMIC3_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / num_conv );
    return PMIC3_OK;
}

err_t pmic3_set_vref ( pmic3_t *ctx, float vref )
{
    ctx->vref = vref;
    return analog_in_set_vref_value( &ctx->adc, vref );
}

void pmic3_set_on_pin ( pmic3_t *ctx, uint8_t state )
{
    if ( PMIC3_PIN_STATE_LOW == state )
    {
        digital_out_low( &ctx->on );
    }
    else
    {
        digital_out_high( &ctx->on );
    }
}

uint8_t pmic3_get_int_pin ( pmic3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t pmic3_check_communication ( pmic3_t *ctx )
{
    err_t error_flag = PMIC3_ERROR;
    uint8_t dev_info = 0;

    if ( ( PMIC3_OK == pmic3_read_reg( ctx, PMIC3_REG_DEV_INFO, &dev_info ) ) &&
         ( PMIC3_DEV_INFO_ID_PCA9422 == ( dev_info & PMIC3_DEV_INFO_ID_MASK ) ) )
    {
        error_flag = PMIC3_OK;
    }

    return error_flag;
}

err_t pmic3_set_buck_voltage ( pmic3_t *ctx, uint8_t buck_id, uint16_t voltage_mv )
{
    err_t    error_flag = PMIC3_ERROR;
    err_t    lock_flag = PMIC3_OK;
    uint8_t  reg = 0;
    uint8_t  voltage_mask = 0;
    uint8_t  voltage_cfg = 0;
    uint8_t  voltage_code = 0;
    uint8_t  voltage_verify = 0;
    uint16_t voltage_min = 0;
    uint16_t voltage_max = 0;
    uint16_t voltage_step = 0;
    uint16_t voltage_round = 0;
    uint32_t voltage_delta = 0;

    switch ( buck_id )
    {
        // Each buck rail has its own output register, range, and code format.
        case PMIC3_BUCK_1:
        {
            reg           = PMIC3_REG_BUCK1_OUT_DVS0;
            voltage_mask  = PMIC3_BUCK13_VOLTAGE_MASK;
            voltage_min   = PMIC3_BUCK13_VOLTAGE_MIN_MV;
            voltage_max   = PMIC3_BUCK13_VOLTAGE_MAX_MV;
            break;
        }
        case PMIC3_BUCK_2:
        {
            reg           = PMIC3_REG_BUCK2_OUT_DVS0;
            voltage_mask  = PMIC3_BUCK2_VOLTAGE_MASK;
            voltage_min   = PMIC3_BUCK2_VOLTAGE_MIN_MV;
            voltage_max   = PMIC3_BUCK2_VOLTAGE_MAX_MV;
            voltage_step  = PMIC3_BUCK2_VOLTAGE_STEP_MV;
            voltage_round = PMIC3_BUCK2_VOLTAGE_ROUND_MV;
            break;
        }
        case PMIC3_BUCK_3:
        {
            reg           = PMIC3_REG_BUCK3_OUT_DVS0;
            voltage_mask  = PMIC3_BUCK13_VOLTAGE_MASK;
            voltage_min   = PMIC3_BUCK13_VOLTAGE_MIN_MV;
            voltage_max   = PMIC3_BUCK13_VOLTAGE_MAX_MV;
            break;
        }
        case PMIC3_BUCK_4:
        {
            reg           = PMIC3_REG_SW4_BB_CFG3;
            voltage_mask  = PMIC3_BUCK4_VOLTAGE_MASK;
            voltage_min   = PMIC3_BUCK4_VOLTAGE_MIN_MV;
            voltage_max   = PMIC3_BUCK4_VOLTAGE_MAX_MV;
            voltage_step  = PMIC3_BUCK4_VOLTAGE_STEP_MV;
            voltage_round = PMIC3_BUCK4_VOLTAGE_ROUND_MV;
            break;
        }
        default:
        {
            break;
        }
    }

    if ( ( 0 != reg ) && ( voltage_min <= voltage_mv ) && ( voltage_max >= voltage_mv ) )
    {
        if ( ( PMIC3_BUCK_1 == buck_id ) || ( PMIC3_BUCK_3 == buck_id ) )
        {
            // BUCK1/3 use a fractional voltage step represented with integer scaling.
            voltage_delta = ( uint32_t ) ( voltage_mv - voltage_min ) * PMIC3_BUCK13_VOLTAGE_SCALE;
            voltage_code = ( uint8_t ) ( ( voltage_delta + PMIC3_BUCK13_ROUND_SCALED ) / PMIC3_BUCK13_STEP_SCALED );
        }
        else
        {
            voltage_code = ( uint8_t ) ( ( voltage_mv - voltage_min + voltage_round ) / voltage_step );
        }

        error_flag = PMIC3_OK;
        if ( PMIC3_BUCK_4 == buck_id )
        {
            // BUCK4 belongs to the protected regulator register bank.
            error_flag = pmic3_write_reg( ctx, PMIC3_REG_LOCK, PMIC3_REGULATOR_UNLOCKED );
        }
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_reg( ctx, reg, &voltage_cfg );
        }
        if ( PMIC3_OK == error_flag )
        {
            // Preserve unrelated fields in the shared output register.
            voltage_cfg &= ( uint8_t ) ~voltage_mask;
            voltage_cfg |= voltage_code & voltage_mask;
            error_flag = pmic3_write_reg( ctx, reg, voltage_cfg );
        }
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_reg( ctx, reg, &voltage_verify );
        }
        if ( ( PMIC3_OK == error_flag ) && ( voltage_code != ( voltage_verify & voltage_mask ) ) )
        {
            error_flag = PMIC3_ERROR;
        }

        if ( PMIC3_BUCK_4 == buck_id )
        {
            // Restore regulator write protection even when verification fails.
            lock_flag = pmic3_write_reg( ctx, PMIC3_REG_LOCK, PMIC3_REGULATOR_LOCKED );
            if ( PMIC3_OK == error_flag )
            {
                error_flag = lock_flag;
            }
        }
    }

    return error_flag;
}

err_t pmic3_set_ldo_voltage ( pmic3_t *ctx, uint8_t ldo_id, uint16_t voltage_mv )
{
    err_t    error_flag = PMIC3_ERROR;
    err_t    lock_flag = PMIC3_OK;
    uint8_t  reg = 0;
    uint8_t  voltage_mask = 0;
    uint8_t  voltage_cfg = 0;
    uint8_t  voltage_code = 0;
    uint8_t  voltage_verify = 0;
    uint16_t voltage_min = 0;
    uint16_t voltage_max = 0;

    switch ( ldo_id )
    {
        // Select the output register and valid range for the requested LDO.
        case PMIC3_LDO_1:
        {
            reg          = PMIC3_REG_LDO1_CFG1;
            voltage_mask = PMIC3_LDO1_VOLTAGE_MASK;
            voltage_min  = PMIC3_LDO1_VOLTAGE_MIN_MV;
            voltage_max  = PMIC3_LDO1_VOLTAGE_MAX_MV;
            break;
        }
        case PMIC3_LDO_2:
        {
            reg          = PMIC3_REG_LDO2_OUT;
            voltage_mask = PMIC3_LDO23_VOLTAGE_MASK;
            voltage_min  = PMIC3_LDO23_VOLTAGE_MIN_MV;
            voltage_max  = PMIC3_LDO23_VOLTAGE_MAX_MV;
            break;
        }
        case PMIC3_LDO_3:
        {
            reg          = PMIC3_REG_LDO3_OUT;
            voltage_mask = PMIC3_LDO23_VOLTAGE_MASK;
            voltage_min  = PMIC3_LDO23_VOLTAGE_MIN_MV;
            voltage_max  = PMIC3_LDO23_VOLTAGE_MAX_MV;
            break;
        }
        case PMIC3_LDO_4:
        {
            reg          = PMIC3_REG_LDO4_OUT;
            voltage_mask = PMIC3_LDO4_VOLTAGE_MASK;
            voltage_min  = PMIC3_LDO4_VOLTAGE_MIN_MV;
            voltage_max  = PMIC3_LDO4_VOLTAGE_MAX_MV;
            break;
        }
        default:
        {
            break;
        }
    }

    if ( ( 0 != reg ) && ( voltage_min <= voltage_mv ) && ( voltage_max >= voltage_mv ) )
    {
        // Round the requested voltage to the nearest supported LDO step.
        voltage_code = ( uint8_t ) ( ( voltage_mv - voltage_min + PMIC3_LDO_VOLTAGE_ROUND_MV ) / PMIC3_LDO_VOLTAGE_STEP_MV );

        // LDO output settings are protected by the regulator lock register.
        error_flag = pmic3_write_reg( ctx, PMIC3_REG_LOCK, PMIC3_REGULATOR_UNLOCKED );
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_reg( ctx, reg, &voltage_cfg );
        }
        if ( PMIC3_OK == error_flag )
        {
            // Preserve mode and enable fields while replacing only the voltage code.
            voltage_cfg &= ( uint8_t ) ~voltage_mask;
            voltage_cfg |= voltage_code & voltage_mask;
            error_flag = pmic3_write_reg( ctx, reg, voltage_cfg );
        }
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_reg( ctx, reg, &voltage_verify );
        }
        if ( ( PMIC3_OK == error_flag ) && ( voltage_code != ( voltage_verify & voltage_mask ) ) )
        {
            error_flag = PMIC3_ERROR;
        }

        // Restore regulator write protection after the readback check.
        lock_flag = pmic3_write_reg( ctx, PMIC3_REG_LOCK, PMIC3_REGULATOR_LOCKED );
        if ( PMIC3_OK == error_flag )
        {
            error_flag = lock_flag;
        }
    }

    return error_flag;
}

err_t pmic3_set_charger_lock ( pmic3_t *ctx, uint8_t lock_state )
{
    err_t error_flag = PMIC3_ERROR;

    if ( ( PMIC3_CHARGER_LOCKED == lock_state ) || ( PMIC3_CHARGER_UNLOCKED == lock_state ) )
    {
        // CHARGER_CNTL0 contains only the lock field; reserved bits stay zero.
        error_flag = pmic3_write_reg( ctx, PMIC3_REG_CHARGER_CNTL0, lock_state );
    }

    return error_flag;
}

err_t pmic3_set_battery_detection ( pmic3_t *ctx, uint8_t detect_state )
{
    err_t error_flag = PMIC3_ERROR;

    if ( ( PMIC3_BATTERY_DETECT_ENABLED == detect_state ) || 
         ( PMIC3_BATTERY_DETECT_DISABLED == detect_state ) )
    {
        error_flag = pmic3_update_charger_reg( ctx, PMIC3_REG_CHARGER_CNTL1,
                                               PMIC3_BATTERY_DETECT_MASK, detect_state );
    }

    return error_flag;
}

err_t pmic3_set_charger ( pmic3_t *ctx, uint8_t charger_state )
{
    err_t error_flag = PMIC3_ERROR;

    if ( ( PMIC3_CHARGER_DISABLED == charger_state ) || 
         ( PMIC3_CHARGER_ENABLED == charger_state ) )
    {
        error_flag = pmic3_update_charger_reg( ctx, PMIC3_REG_CHARGER_CNTL1,
                                               PMIC3_CHARGER_ENABLE_MASK, charger_state );
    }

    return error_flag;
}

err_t pmic3_set_charge_current ( pmic3_t *ctx, float charge_current )
{
    err_t    error_flag = PMIC3_ERROR;
    err_t    lock_flag = PMIC3_OK;
    uint8_t  charger_cfg[ PMIC3_CHARGER_CFG_COUNT ] = { 0 };
    uint8_t  tx_buf[ PMIC3_CHARGER_BURST_WRITE_SIZE ] = { 0 };
    uint8_t  current_cfg = 0;
    uint8_t  charger_verify = 0;
    uint8_t  current_verify = 0;
    uint8_t  current_step_cfg = PMIC3_CHARGE_STEP_2_5MA;
    uint16_t current_step_cnt = 0;
    float    current_step = PMIC3_CHARGE_STEP_2_5MA_VALUE;

    if ( ( PMIC3_CHARGE_CURRENT_MIN_MA <= charge_current ) &&
         ( PMIC3_CHARGE_CURRENT_MAX_MA >= charge_current ) )
    {
        if ( PMIC3_CHARGE_CURRENT_STEP_LIMIT_MA < charge_current )
        {
            // Higher currents use the wider 5 mA code step supported by the PMIC.
            current_step_cfg = PMIC3_CHARGE_STEP_5MA;
            current_step = PMIC3_CHARGE_STEP_5MA_VALUE;
        }

        // The register code is biased, so remove the datasheet-defined offset.
        current_step_cnt = ( uint16_t ) ( charge_current / current_step );
        current_cfg = ( uint8_t ) ( current_step_cnt - PMIC3_FAST_CHARGE_CODE_OFFSET );

        error_flag = pmic3_set_charger_lock( ctx, PMIC3_CHARGER_UNLOCKED );
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_regs( ctx, PMIC3_REG_CHARGER_CNTL1, charger_cfg, PMIC3_CHARGER_CFG_COUNT );
        }
        if ( PMIC3_OK == error_flag )
        {
            charger_cfg[ PMIC3_CHARGER_CFG1_INDEX ] &= ( uint8_t ) ~PMIC3_CHARGE_STEP_MASK;
            charger_cfg[ PMIC3_CHARGER_CFG1_INDEX ] |= current_step_cfg;

            // Keep unlock and protected data in one auto-increment transfer.
            tx_buf[ PMIC3_CHARGER_BURST_ADDR_INDEX ] = PMIC3_REG_CHARGER_CNTL0;
            tx_buf[ PMIC3_CHARGER_BURST_LOCK_INDEX ] = PMIC3_CHARGER_UNLOCKED;
            tx_buf[ PMIC3_CHARGER_BURST_CFG1_INDEX ] = charger_cfg[ PMIC3_CHARGER_CFG1_INDEX ];
            tx_buf[ PMIC3_CHARGER_BURST_CFG2_INDEX ] = charger_cfg[ PMIC3_CHARGER_CFG2_INDEX ];
            tx_buf[ PMIC3_CHARGER_BURST_CFG3_INDEX ] = current_cfg;

            error_flag = i2c_master_write( &ctx->i2c, tx_buf, PMIC3_CHARGER_BURST_WRITE_SIZE );
        }
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_reg( ctx, PMIC3_REG_CHARGER_CNTL1, &charger_verify );
        }
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_reg( ctx, PMIC3_REG_CHARGER_CNTL3, &current_verify );
        }
        if ( ( PMIC3_OK == error_flag ) &&
             ( ( ( charger_cfg[ PMIC3_CHARGER_CFG1_INDEX ] & PMIC3_CHARGE_CFG_VERIFY_MASK ) !=
                 ( charger_verify & PMIC3_CHARGE_CFG_VERIFY_MASK ) ) ||
               ( current_cfg != ( current_verify & PMIC3_FAST_CHARGE_CURRENT_MASK ) ) ) )
        {
            error_flag = PMIC3_ERROR;
        }

        // Restore protection after verification in the unlocked window.
        lock_flag = pmic3_set_charger_lock( ctx, PMIC3_CHARGER_LOCKED );
        if ( PMIC3_OK == error_flag )
        {
            error_flag = lock_flag;
        }
    }

    return error_flag;
}

err_t pmic3_read_charge_current ( pmic3_t *ctx, float *charge_current )
{
    err_t   error_flag = PMIC3_ERROR;
    err_t   lock_flag = PMIC3_OK;
    uint8_t charger_cfg = 0;
    uint8_t current_cfg = 0;
    float   current_step = 0;

    if ( NULL != charge_current )
    {
        error_flag = pmic3_set_charger_lock( ctx, PMIC3_CHARGER_UNLOCKED );
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_reg( ctx, PMIC3_REG_CHARGER_CNTL1, &charger_cfg );
        }
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_reg( ctx, PMIC3_REG_CHARGER_CNTL3, &current_cfg );
        }
        if ( PMIC3_OK == error_flag )
        {
            // Decode both the selected step size and the biased current code.
            if ( charger_cfg & PMIC3_CHARGE_STEP_MASK )
            {
                current_step = PMIC3_CHARGE_STEP_5MA_VALUE;
            }
            else
            {
                current_step = PMIC3_CHARGE_STEP_2_5MA_VALUE;
            }
            current_cfg &= PMIC3_FAST_CHARGE_CURRENT_MASK;
            *charge_current = ( current_cfg + PMIC3_FAST_CHARGE_CODE_OFFSET ) * current_step;
        }

        lock_flag = pmic3_set_charger_lock( ctx, PMIC3_CHARGER_LOCKED );
        if ( PMIC3_OK == error_flag )
        {
            error_flag = lock_flag;
        }
    }

    return error_flag;
}

err_t pmic3_set_amux_channel ( pmic3_t *ctx, uint8_t channel )
{
    err_t error_flag = PMIC3_ERROR;

    if ( PMIC3_AMUX_CHANNEL_VIN >= channel )
    {
        // Clearing the mode bit keeps the selected channel active during ADC reads.
        error_flag = pmic3_update_charger_reg( ctx, PMIC3_REG_CHARGER_CNTL10,
                                               PMIC3_AMUX_MODE_MASK | PMIC3_AMUX_CHANNEL_MASK, channel );
    }

    return error_flag;
}

err_t pmic3_read_amux ( pmic3_t *ctx, uint8_t channel, float *source_voltage )
{
    err_t   error_flag = PMIC3_ERROR;
    err_t   disable_flag = PMIC3_OK;
    err_t   lock_flag = PMIC3_OK;
    uint8_t amux_cfg = 0;
    float   amux_voltage = 0;
    float   channel_gain = 0;

    if ( ( NULL != source_voltage ) && ( PMIC3_AMUX_CHANNEL_OFF < channel ) &&
         ( PMIC3_AMUX_CHANNEL_VIN >= channel ) )
    {
        error_flag = pmic3_set_amux_channel( ctx, channel );
        if ( PMIC3_OK == error_flag )
        {
            // The 1 ms delay exceeds the specified 64 us AMUX settling time.
            Delay_1ms( );
            error_flag = pmic3_set_charger_lock( ctx, PMIC3_CHARGER_UNLOCKED );
        }
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_reg( ctx, PMIC3_REG_CHARGER_CNTL10, &amux_cfg );
        }

        lock_flag = pmic3_set_charger_lock( ctx, PMIC3_CHARGER_LOCKED );
        if ( PMIC3_OK == error_flag )
        {
            error_flag = lock_flag;
        }
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_voltage_avg( ctx, PMIC3_NUM_CONVERSIONS, &amux_voltage );
        }

        if ( PMIC3_OK == error_flag )
        {
            // Select the divider gain reported by the active AMUX configuration.
            switch ( channel )
            {
                case PMIC3_AMUX_CHANNEL_VBAT:
                {
                    if ( amux_cfg & PMIC3_AMUX_VBAT_VSYS_GAIN_MASK )
                    {
                        channel_gain = PMIC3_AMUX_GAIN_VBAT_1_4;
                    }
                    else
                    {
                        channel_gain = PMIC3_AMUX_GAIN_VBAT_1_3;
                    }
                    break;
                }
                case PMIC3_AMUX_CHANNEL_VSYS:
                {
                    if ( amux_cfg & PMIC3_AMUX_VBAT_VSYS_GAIN_MASK )
                    {
                        channel_gain = PMIC3_AMUX_GAIN_VSYS_1_4;
                    }
                    else
                    {
                        channel_gain = PMIC3_AMUX_GAIN_VSYS_1_3;
                    }
                    break;
                }
                case PMIC3_AMUX_CHANNEL_THERM:
                case PMIC3_AMUX_CHANNEL_THERM_BIAS:
                {
                    if ( amux_cfg & PMIC3_AMUX_THERM_GAIN_MASK )
                    {
                        channel_gain = PMIC3_AMUX_GAIN_THERM_1_1_5;
                    }
                    else
                    {
                        channel_gain = PMIC3_AMUX_GAIN_THERM_1;
                    }
                    break;
                }
                case PMIC3_AMUX_CHANNEL_VIN:
                {
                    channel_gain = PMIC3_AMUX_GAIN_VIN;
                    break;
                }
                default:
                {
                    error_flag = PMIC3_ERROR;
                    break;
                }
            }
        }

        if ( ( PMIC3_OK == error_flag ) && ( 0 < channel_gain ) )
        {
            // Reverse the AMUX divider to obtain the selected source voltage.
            *source_voltage = amux_voltage / channel_gain;
        }

        // Disconnect AMUX after sampling to avoid leaving an internal rail exposed.
        disable_flag = pmic3_set_amux_channel( ctx, PMIC3_AMUX_CHANNEL_OFF );
        if ( PMIC3_OK == error_flag )
        {
            error_flag = disable_flag;
        }
    }

    return error_flag;
}

err_t pmic3_read_temperature ( pmic3_t *ctx, float *temperature )
{
    err_t error_flag = PMIC3_ERROR;
    float therm_voltage = 0;
    float therm_bias_voltage = 0;
    float therm_ratio = 0;
    float therm_resistance = 0;

    if ( NULL != temperature )
    {
        error_flag = pmic3_read_amux( ctx, PMIC3_AMUX_CHANNEL_THERM_BIAS, &therm_bias_voltage );
    }
    if ( PMIC3_OK == error_flag )
    {
        error_flag = pmic3_read_amux( ctx, PMIC3_AMUX_CHANNEL_THERM, &therm_voltage );
    }
    if ( ( PMIC3_OK == error_flag ) && ( PMIC3_NTC_BIAS_VOLTAGE_MIN < therm_bias_voltage ) )
    {
        therm_ratio = therm_voltage / therm_bias_voltage;
        if ( ( PMIC3_NTC_RATIO_MIN < therm_ratio ) && ( PMIC3_NTC_RATIO_MAX > therm_ratio ) )
        {
            // Convert the THERM divider ratio to the onboard NTC resistance.
            therm_resistance = PMIC3_NTC_PULLUP_RESISTANCE_OHM * therm_ratio /
                               ( PMIC3_RECIPROCAL - therm_ratio );

            // Apply the NTC beta equation and convert the result to degrees Celsius.
            *temperature = PMIC3_RECIPROCAL / ( ( PMIC3_RECIPROCAL / PMIC3_NTC_REFERENCE_TEMP_K ) +
                           ( log( therm_resistance / PMIC3_NTC_R25_RESISTANCE_OHM ) / PMIC3_NTC_BETA_25_85_K ) ) -
                           PMIC3_KELVIN_OFFSET;
        }
        else
        {
            error_flag = PMIC3_ERROR;
        }
    }
    else if ( PMIC3_OK == error_flag )
    {
        error_flag = PMIC3_ERROR;
    }

    return error_flag;
}

err_t pmic3_read_status ( pmic3_t *ctx, pmic3_status_t *status )
{
    err_t error_flag = PMIC3_ERROR;
    uint8_t charger_status[ PMIC3_STATUS_REG_COUNT ] = { 0 };

    if ( NULL != status )
    {
        status->top_int          = 0;
        status->power_state      = 0;
        status->regulator_status = 0;
        status->device_0_status  = 0;
        status->device_1_status  = 0;
        status->charger_0_status = 0;
        status->charger_1_status = 0;
        status->charger_2_status = 0;
        status->charger_3_status = 0;

        error_flag = pmic3_read_reg( ctx, PMIC3_REG_TOP_INT, &status->top_int );
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_reg( ctx, PMIC3_REG_PWR_STATE, &status->power_state );
        }
        if ( PMIC3_OK == error_flag )
        {
            error_flag = pmic3_read_reg( ctx, PMIC3_REG_REG_STATUS, &status->regulator_status );
        }
        if ( PMIC3_OK == error_flag )
        {
            // DEVICE0_STS through CHARGER3_STS form one contiguous block.
            error_flag = pmic3_read_regs( ctx, PMIC3_REG_DEVICE0_STS, charger_status, PMIC3_STATUS_REG_COUNT );
        }
        if ( PMIC3_OK == error_flag )
        {
            status->device_0_status  = charger_status[ PMIC3_DEVICE0_STS_INDEX ];
            status->device_1_status  = charger_status[ PMIC3_DEVICE1_STS_INDEX ];
            status->charger_0_status = charger_status[ PMIC3_CHARGER0_STS_INDEX ];
            status->charger_1_status = charger_status[ PMIC3_CHARGER1_STS_INDEX ];
            status->charger_2_status = charger_status[ PMIC3_CHARGER2_STS_INDEX ];
            status->charger_3_status = charger_status[ PMIC3_CHARGER3_STS_INDEX ];
        }
    }

    return error_flag;
}

err_t pmic3_detect_battery ( pmic3_t *ctx, pmic3_status_t *status, uint8_t *battery_state )
{
    err_t   error_flag = PMIC3_ERROR;
    err_t   disable_flag = PMIC3_OK;
    err_t   enable_flag = PMIC3_OK;
    uint8_t charger_int = 0;
    uint8_t restart_required = PMIC3_RESTART_NOT_REQUIRED;

    if ( ( NULL != status ) && ( NULL != battery_state ) )
    {
        // Reading the interrupt register also captures completed presence-test events.
        error_flag = pmic3_read_reg( ctx, PMIC3_REG_INT_CHARGER1, &charger_int );
        if ( PMIC3_OK == error_flag )
        {
            // NO_BATTERY is the dedicated result of the internal presence test.
            if ( ( charger_int & PMIC3_INT_CHARGER1_NO_BATTERY ) ||
                 ( status->charger_1_status & PMIC3_CHARGER1_NO_BATTERY ) )
            {
                // Debounce absence and periodically request a fresh qualification test.
                if ( PMIC3_BATTERY_ABSENT != ctx->battery_state )
                {
                    ctx->battery_state = PMIC3_BATTERY_ABSENT;
                    ctx->battery_confirm_cnt = 0;
                }
                if ( PMIC3_BATTERY_RECHECK_COUNT > ctx->battery_confirm_cnt )
                {
                    ctx->battery_confirm_cnt++;
                }
                if ( PMIC3_BATTERY_RECHECK_COUNT == ctx->battery_confirm_cnt )
                {
                    restart_required = PMIC3_RESTART_REQUIRED;
                }
            }
            else
            {
                // Require consecutive clear samples before reporting a present battery.
                if ( PMIC3_BATTERY_ABSENT == ctx->battery_state )
                {
                    ctx->battery_state = PMIC3_BATTERY_UNKNOWN;
                    ctx->battery_confirm_cnt = 0;
                }
                if ( PMIC3_BATTERY_CONFIRM_COUNT > ctx->battery_confirm_cnt )
                {
                    ctx->battery_confirm_cnt++;
                }
                if ( PMIC3_BATTERY_CONFIRM_COUNT == ctx->battery_confirm_cnt )
                {
                    ctx->battery_state = PMIC3_BATTERY_PRESENT;
                }
            }

            if ( PMIC3_RESTART_REQUIRED == restart_required )
            {
                // A disable-enable transition starts a new qualification cycle.
                disable_flag = pmic3_set_charger( ctx, PMIC3_CHARGER_DISABLED );
                Delay_10ms( );
                enable_flag = pmic3_set_charger( ctx, PMIC3_CHARGER_ENABLED );
                Delay_100ms( );
                if ( ( PMIC3_OK == disable_flag ) && ( PMIC3_OK == enable_flag ) )
                {
                    ctx->battery_confirm_cnt = 0;
                }
                else
                {
                    error_flag = PMIC3_ERROR;
                }
            }

            *battery_state = ctx->battery_state;
        }
    }

    return error_flag;
}

static err_t pmic3_update_charger_reg ( pmic3_t *ctx, uint8_t reg, uint8_t mask, uint8_t value )
{
    err_t   error_flag = PMIC3_ERROR;
    err_t   lock_flag = PMIC3_OK;
    uint8_t reg_cfg = 0;
    uint8_t reg_verify = 0;
    uint8_t field_value = value & mask;

    // Protected charger registers can read as zero while write protection is enabled.
    error_flag = pmic3_set_charger_lock( ctx, PMIC3_CHARGER_UNLOCKED );
    if ( PMIC3_OK == error_flag )
    {
        error_flag = pmic3_read_reg( ctx, reg, &reg_cfg );
    }
    if ( PMIC3_OK == error_flag )
    {
        // Update only the requested field and preserve the remaining register bits.
        reg_cfg &= ( uint8_t ) ~mask;
        reg_cfg |= field_value;
        error_flag = pmic3_write_reg( ctx, reg, reg_cfg );
    }
    if ( PMIC3_OK == error_flag )
    {
        error_flag = pmic3_read_reg( ctx, reg, &reg_verify );
    }
    if ( ( PMIC3_OK == error_flag ) && ( field_value != ( reg_verify & mask ) ) )
    {
        error_flag = PMIC3_ERROR;
    }

    // Always restore write protection, including after a failed transaction.
    lock_flag = pmic3_set_charger_lock( ctx, PMIC3_CHARGER_LOCKED );
    if ( PMIC3_OK == error_flag )
    {
        error_flag = lock_flag;
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
