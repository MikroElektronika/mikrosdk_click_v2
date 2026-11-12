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
 * @file pmic4.c
 * @brief PMIC 4 Click Driver.
 */

#include "pmic4.h"
#include "math.h"

/**
 * @brief PMIC 4 transfer and polling settings.
 * @details The writable bank contains 23 registers. Polling allows 100 waits
 * of 10 ms; total elapsed time also includes the I2C transfers.
 */
#define PMIC4_WRITE_BUFFER_SIZE                 24
#define PMIC4_PART_NUMBER_SIZE                  5
#define PMIC4_POLL_COUNT                        100
#define PMIC4_REGISTER_PAIR_SIZE                2

/**
 * @brief PMIC 4 voltage conversion settings.
 * @details STO uses a 4.8 V full scale divided by 256. Source codes use five
 * separate ranges from AEM13921 datasheet Table 73, not a linear ADC scale.
 */
#define PMIC4_STORAGE_VOLTAGE_LSB               0.01875f
#define PMIC4_SOURCE_FLOOR_CODE                 0x06
#define PMIC4_SOURCE_RANGE_1_MAX                0x12
#define PMIC4_SOURCE_RANGE_2_MAX                0x39
#define PMIC4_SOURCE_RANGE_3_MIN                0x68
#define PMIC4_SOURCE_RANGE_3_MAX                0x79
#define PMIC4_SOURCE_RANGE_4_MIN                0x9F
#define PMIC4_SOURCE_RANGE_4_MAX                0xB9
#define PMIC4_SOURCE_FLOOR_V                    0.113f
#define PMIC4_SOURCE_CODE_MULTIPLIER            2.0f
#define PMIC4_SOURCE_FINE_BASE_V                0.09f
#define PMIC4_SOURCE_FINE_STEP_V                0.0075f
#define PMIC4_SOURCE_COARSE_BASE_V              0.3f
#define PMIC4_SOURCE_COARSE_STEP_V              0.015f
#define PMIC4_SOURCE_RANGE_1_OFFSET             9.0f
#define PMIC4_SOURCE_RANGE_2_OFFSET             37.0f
#define PMIC4_SOURCE_RANGE_3_OFFSET             165.0f
#define PMIC4_SOURCE_RANGE_4_OFFSET             293.0f
#define PMIC4_SOURCE_RANGE_3_DIVIDER            0.67f
#define PMIC4_SOURCE_RANGE_4_DIVIDER            0.33f

/**
 * @brief PMIC 4 onboard NTC conversion settings.
 * @details RT1 is Murata NCP18XH103F03RB: 10 kohm at 25 C, B25/50 = 3380 K.
 * R29 is the 22 kohm divider resistor. TEMP is an 8-bit ratio with a 256
 * full scale (AEM13921 Section 9.22), not a direct Celsius reading.
 */
#define PMIC4_NTC_R25_OHM                       10000.0f
#define PMIC4_NTC_DIVIDER_OHM                   22000.0f
#define PMIC4_NTC_BETA_K                        3380.0f
#define PMIC4_NTC_REFERENCE_K                   298.15f
#define PMIC4_NTC_KELVIN_OFFSET                 273.15f
#define PMIC4_NTC_ADC_FULL_SCALE                256.0f
#define PMIC4_NTC_ADC_CODE_MIN                  0x01
#define PMIC4_NTC_ADC_CODE_MAX                  0xFE

/**
 * @brief PMIC 4 APM transfer and conversion settings.
 * @details Configuration spans SRC1REGU0 through IRQEN1; the sample burst
 * spans APM0SRC1 through STO. Power data contains a 19-bit mantissa and
 * 5-bit exponent. Charger duty divides its count by the maximum count minus
 * one, not by the APM duration. See datasheet Sections 9.17 and 9.21.
 */
#define PMIC4_APM_CONFIG_SIZE                   ( PMIC4_REG_IRQEN1 - PMIC4_REG_SRC1REGU0 + 1 )
#define PMIC4_APM_SAMPLE_SIZE                   ( PMIC4_REG_STO - PMIC4_REG_APM0SRC1 + 1 )
#define PMIC4_APM_CONVERTER_SIZE                3
#define PMIC4_APM_MANTISSA_HIGH_BYTE            2
#define PMIC4_APM_MANTISSA_HIGH_SHIFT           ( PMIC4_APM_MANTISSA_HIGH_BYTE * PMIC4_REGISTER_BYTE_BITS )
#define PMIC4_APM_CHANNEL_ENABLE_MASK           0x0F
#define PMIC4_APM_MANTISSA_HIGH_MASK            0x07
#define PMIC4_APM_EXPONENT_SHIFT                3
#define PMIC4_MPPT_PERIOD_MASK                  0x38
#define PMIC4_APM_CHARGER_COUNT_116_MS          64
#define PMIC4_APM_CHARGER_COUNT_233_MS          128
#define PMIC4_CHARGER_CURRENT_MIN_MA            13.5f
#define PMIC4_CHARGER_CURRENT_MAX_MA            135.0f
#define PMIC4_MILLIAMPS_PER_AMP                 1000.0f

/**
 * @brief PMIC 4 register synchronization function.
 * @details This function waits for the CTRL.SYNCBUSY bit to clear.
 * @param[in] ctx : Click context object.
 * See #pmic4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - I2C error,
 *         @li @c -2 - Synchronization timeout.
 * See #err_t definition for detailed explanation.
 * @note The wait is bounded. I2C errors stop polling immediately.
 */
static err_t pmic4_wait_sync ( pmic4_t *ctx );

void pmic4_cfg_setup ( pmic4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->stl = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PMIC4_DEVICE_ADDRESS;
}

err_t pmic4_init ( pmic4_t *ctx, pmic4_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;
    err_t error_flag;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    error_flag = i2c_master_open( &ctx->i2c, &i2c_cfg );
    if ( I2C_MASTER_ERROR != error_flag )
    {
        error_flag = i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }

    if ( I2C_MASTER_ERROR != error_flag )
    {
        error_flag = i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    }

    if ( I2C_MASTER_ERROR != error_flag )
    {
        digital_in_init( &ctx->stl, cfg->stl );
        digital_in_init( &ctx->int_pin, cfg->int_pin );
    }

    return error_flag;
}

err_t pmic4_default_cfg ( pmic4_t *ctx ) 
{
    uint8_t part_number[ PMIC4_PART_NUMBER_SIZE ];
    uint8_t cnt;
    err_t error_flag = PMIC4_ERROR;

    // A successful identity read proves readiness even if I2CRDY was cleared
    // before the MCU restarted. Polling also wakes a disabled I2C interface.
    for ( cnt = 0; cnt < PMIC4_POLL_COUNT; cnt++ )
    {
        error_flag = pmic4_read_regs( ctx, PMIC4_REG_PN0, part_number, PMIC4_PART_NUMBER_SIZE );
        if ( PMIC4_OK == error_flag )
        {
            break;
        }
        Delay_10ms();
    }

    if ( PMIC4_OK == error_flag )
    {
        // PN0 contains the last digit; the five bytes identify AEM13921.
        if ( ( '1' != part_number[ 0 ] ) || ( '2' != part_number[ 1 ] ) ||
             ( '9' != part_number[ 2 ] ) || ( '3' != part_number[ 3 ] ) ||
             ( '1' != part_number[ 4 ] ) )
        {
            error_flag = PMIC4_ERROR_DEVICE;
        }
    }

    if ( PMIC4_OK == error_flag )
    {
        // Keep source, storage, load, and thermal settings under strap control.
        // Applying I2C defaults here would replace the board's charging limits.
        error_flag = pmic4_set_config_mode( ctx, PMIC4_CONFIG_GPIO );
    }

    return error_flag;
}

err_t pmic4_write_reg ( pmic4_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return pmic4_write_regs( ctx, reg, &data_in, 1 );
}

err_t pmic4_write_regs ( pmic4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ PMIC4_WRITE_BUFFER_SIZE ];
    uint8_t cnt;
    err_t error_flag = PMIC4_ERROR;

    // Reject read-only/reserved addresses and transfers that would overflow
    // the writable bank or wrap the register pointer.
    if ( ctx && data_in && len && ( reg >= PMIC4_REG_SRC1REGU0 ) &&
         ( ( ( uint16_t ) reg + len ) <= ( PMIC4_REG_CTRL + 1 ) ) )
    {
        data_buf[ 0 ] = reg;
        for ( cnt = 0; cnt < len; cnt++ )
        {
            data_buf[ cnt + 1 ] = data_in[ cnt ];
        }
        error_flag = i2c_master_write( &ctx->i2c, data_buf, len + 1 );
    }

    return error_flag;
}

err_t pmic4_read_reg ( pmic4_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return pmic4_read_regs( ctx, reg, data_out, 1 );
}

err_t pmic4_read_regs ( pmic4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    err_t error_flag = PMIC4_ERROR;

    // Auto-increment is valid only inside a documented contiguous bank.
    if ( ctx && data_out && len &&
         ( ( ( ( uint16_t ) reg + len ) <= ( PMIC4_REG_SRC2 + 1 ) ) ||
           ( ( reg >= PMIC4_REG_PN0 ) &&
             ( ( ( uint16_t ) reg + len ) <= ( PMIC4_REG_PN4 + 1 ) ) ) ) )
    {
        error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
    }

    return error_flag;
}

err_t pmic4_set_config_mode ( pmic4_t *ctx, uint8_t mode )
{
    uint8_t ctrl;
    err_t error_flag = PMIC4_ERROR;

    if ( ( PMIC4_CONFIG_GPIO == mode ) || ( PMIC4_CONFIG_I2C == mode ) )
    {
        error_flag = pmic4_wait_sync( ctx );
        if ( PMIC4_OK == error_flag )
        {
            // Write only UPDATE; SYNCBUSY is read-only and reserved bits stay zero.
            error_flag = pmic4_write_reg( ctx, PMIC4_REG_CTRL, mode );
        }
        if ( PMIC4_OK == error_flag )
        {
            error_flag = pmic4_wait_sync( ctx );
        }
        if ( PMIC4_OK == error_flag )
        {
            error_flag = pmic4_read_reg( ctx, PMIC4_REG_CTRL, &ctrl );
            if ( ( PMIC4_OK == error_flag ) &&
                 ( ( ctrl & PMIC4_CTRL_UPDATE ) != mode ) )
            {
                error_flag = PMIC4_ERROR_CONFIG;
            }
        }
    }

    return error_flag;
}

err_t pmic4_configure_apm ( pmic4_t *ctx )
{
    uint8_t profile[ PMIC4_APM_CONFIG_SIZE ] =
    {
        PMIC4_SOURCE_MODE_MPPT | PMIC4_MPPT_RATIO_80,                 // SRC1REGU0
        PMIC4_MPPT_WAIT_29_MS | PMIC4_MPPT_PERIOD_1862_MS,           // SRC1REGU1
        PMIC4_SOURCE_MODE_MPPT | PMIC4_MPPT_RATIO_80,                 // SRC2REGU0
        PMIC4_MPPT_WAIT_29_MS | PMIC4_MPPT_PERIOD_1862_MS,           // SRC2REGU1
        PMIC4_STORAGE_DISCHARGE_3_00_V,                             // VOVDIS
        PMIC4_STORAGE_READY_3_21_V,                                 // VCHRDY
        PMIC4_STORAGE_UPPER_4_13_V,                                 // VOVCH
        PMIC4_BOOST_ENABLE | PMIC4_BOOST_HIGH_POWER_ENABLE |
        PMIC4_BOOST_TIMING_X3,                                      // BST1CFG
        PMIC4_BOOST_ENABLE | PMIC4_BOOST_HIGH_POWER_ENABLE |
        PMIC4_BOOST_TIMING_X3,                                      // BST2CFG
        PMIC4_LOAD_2_5_V | PMIC4_BUCK_TIMING_X2,                     // BUCKCFG
        PMIC4_STORAGE_READY_3_21_V,                                 // VCHRDYBUCK
        PMIC4_CHARGER_ENABLE,                                       // CHG5V: CC only
        PMIC4_TEMPERATURE_COLD_0_C,                                 // TEMPCOLDCH
        PMIC4_TEMPERATURE_HOT_45_C,                                 // TEMPHOTCH
        PMIC4_TEMPERATURE_COLD_0_C,                                 // TEMPCOLDDIS
        PMIC4_TEMPERATURE_HOT_45_C,                                 // TEMPHOTDIS
        PMIC4_THERMAL_PROTECTION_ENABLE,                            // TEMPPROTECT
        PMIC4_SOURCE_LOW_0_113_V,                                   // SRCLOW
        PMIC4_APM_CHANNEL_ENABLE_MASK | PMIC4_APM_POWER_METER |
        PMIC4_APM_WINDOW_233_MS,                                    // APM
        PMIC4_APM_ACC_DISABLED,                                    // APMACC: one window
        PMIC4_IRQ_I2C_READY,                                        // IRQEN0
        ( PMIC4_IRQ_APM_DONE | PMIC4_IRQ_APM_ERROR ) >> PMIC4_REGISTER_BYTE_BITS // IRQEN1
    };
    uint8_t readback[ PMIC4_APM_CONFIG_SIZE ];
    uint8_t cnt;
    err_t error_flag;

    // Stage the whole profile before UPDATE. Applying only the APM bits
    // would also apply unrelated register defaults, including LOAD_OFF.
    error_flag = pmic4_wait_sync( ctx );
    if ( PMIC4_OK == error_flag )
    {
        error_flag = pmic4_write_regs( ctx, PMIC4_REG_SRC1REGU0, profile, PMIC4_APM_CONFIG_SIZE );
    }
    if ( PMIC4_OK == error_flag )
    {
        error_flag = pmic4_read_regs( ctx, PMIC4_REG_SRC1REGU0, readback, PMIC4_APM_CONFIG_SIZE );
    }
    if ( PMIC4_OK == error_flag )
    {
        // Do not commit a partial or unexpectedly modified charging profile.
        for ( cnt = 0; cnt < PMIC4_APM_CONFIG_SIZE; cnt++ )
        {
            if ( readback[ cnt ] != profile[ cnt ] )
            {
                error_flag = PMIC4_ERROR_CONFIG;
                break;
            }
        }
    }
    if ( PMIC4_OK == error_flag )
    {
        error_flag = pmic4_set_config_mode( ctx, PMIC4_CONFIG_I2C );
    }

    return error_flag;
}

err_t pmic4_get_currents ( pmic4_t *ctx, pmic4_current_cfg_t *cfg, pmic4_currents_t *currents )
{
    uint8_t settings[ PMIC4_APM_CONFIG_SIZE ];
    uint8_t buff[ PMIC4_APM_SAMPLE_SIZE ];
    uint8_t ctrl;
    uint8_t irq;
    uint8_t cnt;
    uint8_t channel;
    uint8_t exponent;
    uint8_t mask;
    uint16_t charger_count;
    uint16_t charger_max;
    uint32_t mantissa;
    pmic4_currents_t sample;
    err_t error_flag = PMIC4_ERROR;

    if ( ctx && cfg && currents )
    {
        // A bad conversion setup must not be reported as a bus failure.
        error_flag = PMIC4_ERROR_CONFIG;
    }
    if ( ctx && cfg && currents &&
         ( cfg->alpha[ PMIC4_CURRENT_SOURCE_1 ] >= 0.0f ) &&
         ( cfg->alpha[ PMIC4_CURRENT_SOURCE_2 ] >= 0.0f ) &&
         ( cfg->alpha[ PMIC4_CURRENT_LOAD ] >= 0.0f ) &&
         ( ( 0.0f == cfg->charger_current ) ||
           ( ( cfg->charger_current >= PMIC4_CHARGER_CURRENT_MIN_MA ) &&
             ( cfg->charger_current <= PMIC4_CHARGER_CURRENT_MAX_MA ) ) ) )
    {
        // Read the staged settings and check the active mode. GPIO mode or
        // a PMIC reset would otherwise expose stale APM values as measurements.
        error_flag = pmic4_read_regs( ctx, PMIC4_REG_SRC1REGU0, settings, PMIC4_APM_CONFIG_SIZE );
        if ( PMIC4_OK == error_flag )
        {
            error_flag = pmic4_read_reg( ctx, PMIC4_REG_CTRL, &ctrl );
        }
        if ( PMIC4_OK == error_flag )
        {
            if ( ( ( ctrl & ( PMIC4_CTRL_UPDATE | PMIC4_CTRL_SYNCBUSY ) ) != PMIC4_CTRL_UPDATE ) ||
                 ( ( settings[ PMIC4_REG_APM - PMIC4_REG_SRC1REGU0 ] &
                     ( PMIC4_APM_CHANNEL_ENABLE_MASK | PMIC4_APM_POWER_METER ) ) !=
                   ( PMIC4_APM_CHANNEL_ENABLE_MASK | PMIC4_APM_POWER_METER ) ) ||
                 !( settings[ PMIC4_REG_IRQEN1 - PMIC4_REG_SRC1REGU0 ] &
                    ( PMIC4_IRQ_APM_DONE >> PMIC4_REGISTER_BYTE_BITS ) ) ||
                 ( settings[ PMIC4_REG_APMACC - PMIC4_REG_SRC1REGU0 ] != PMIC4_APM_ACC_DISABLED ) ||
                 ( settings[ PMIC4_REG_CHG5V - PMIC4_REG_SRC1REGU0 ] & PMIC4_CHARGER_CV_ENABLE ) )
            {
                error_flag = PMIC4_ERROR_CONFIG;
            }
        }
        if ( PMIC4_OK == error_flag )
        {
            // Either source's shortest MPPT period forces a 116 ms window,
            // even when the corresponding boost converter is disabled.
            charger_max = PMIC4_APM_CHARGER_COUNT_233_MS;
            if ( ( settings[ PMIC4_REG_APM - PMIC4_REG_SRC1REGU0 ] & PMIC4_APM_WINDOW_116_MS ) ||
                 ( ( settings[ PMIC4_REG_SRC1REGU1 - PMIC4_REG_SRC1REGU0 ] &
                     PMIC4_MPPT_PERIOD_MASK ) == PMIC4_MPPT_PERIOD_116_MS ) ||
                 ( ( settings[ PMIC4_REG_SRC2REGU1 - PMIC4_REG_SRC1REGU0 ] &
                     PMIC4_MPPT_PERIOD_MASK ) == PMIC4_MPPT_PERIOD_116_MS ) )
            {
                charger_max = PMIC4_APM_CHARGER_COUNT_116_MS;
            }

            charger_max--;
        }
        if ( PMIC4_OK == error_flag )
        {
            // Discard latched completion flags, then wait for a new window.
            // No IRQFLG0 read is needed to consume the APM event.
            error_flag = pmic4_read_reg( ctx, PMIC4_REG_IRQFLG1, &irq );
        }
        if ( PMIC4_OK == error_flag )
        {
            error_flag = PMIC4_NOT_READY;
            for ( cnt = 0; cnt < PMIC4_POLL_COUNT; cnt++ )
            {
                error_flag = pmic4_read_reg( ctx, PMIC4_REG_IRQFLG1, &irq );
                if ( PMIC4_OK != error_flag )
                {
                    break;
                }
                if ( irq & ( PMIC4_IRQ_APM_DONE >> PMIC4_REGISTER_BYTE_BITS ) )
                {
                    // Read all channels, APM errors, and STO in one burst.
                    error_flag = pmic4_read_regs( ctx, PMIC4_REG_APM0SRC1, buff, PMIC4_APM_SAMPLE_SIZE );
                    if ( PMIC4_OK == error_flag )
                    {
                        error_flag = pmic4_read_reg( ctx, PMIC4_REG_IRQFLG1, &irq );
                    }
                    if ( PMIC4_OK != error_flag )
                    {
                        break;
                    }
                    if ( !( irq & ( PMIC4_IRQ_APM_DONE >> PMIC4_REGISTER_BYTE_BITS ) ) )
                    {
                        break;
                    }
                    // A new window arrived during the burst. Wait and retry
                    // instead of mixing bytes from different measurements.
                }
                error_flag = PMIC4_NOT_READY;
                Delay_10ms();
            }
        }
        if ( PMIC4_OK == error_flag )
        {
            // The charger count is little-endian and independent of alpha.
            charger_count = ( ( uint16_t ) buff[ PMIC4_REG_APM1CHG5V - PMIC4_REG_APM0SRC1 ] <<
                               PMIC4_REGISTER_BYTE_BITS ) |
                             buff[ PMIC4_REG_APM0CHG5V - PMIC4_REG_APM0SRC1 ];
            sample.storage_voltage = buff[ PMIC4_REG_STO - PMIC4_REG_APM0SRC1 ] * PMIC4_STORAGE_VOLTAGE_LSB;
            if ( ( 0 == sample.storage_voltage ) || ( charger_count > charger_max ) )
            {
                error_flag = PMIC4_ERROR_SAMPLE;
            }
        }
        if ( PMIC4_OK == error_flag )
        {
            sample.valid = 0;
            sample.activity = 0;
            sample.errors = buff[ PMIC4_REG_APMERR - PMIC4_REG_APM0SRC1 ];
            for ( channel = 0; channel < PMIC4_CURRENT_CHANNEL_COUNT; channel++ )
            {
                sample.current[ channel ] = 0.0f;
            }
            for ( channel = 0; channel < PMIC4_CURRENT_CONVERTER_COUNT; channel++ )
            {
                mask = ( uint8_t ) ( 1 << channel );
                // Byte 2 holds the high mantissa bits and the shift exponent.
                mantissa = ( ( uint32_t ) ( buff[ channel * PMIC4_APM_CONVERTER_SIZE +
                                                 PMIC4_APM_MANTISSA_HIGH_BYTE ] &
                                           PMIC4_APM_MANTISSA_HIGH_MASK ) << PMIC4_APM_MANTISSA_HIGH_SHIFT ) |
                           ( ( uint32_t ) buff[ channel * PMIC4_APM_CONVERTER_SIZE + 1 ] <<
                             PMIC4_REGISTER_BYTE_BITS ) |
                           buff[ channel * PMIC4_APM_CONVERTER_SIZE ];
                exponent = buff[ channel * PMIC4_APM_CONVERTER_SIZE + PMIC4_APM_MANTISSA_HIGH_BYTE ] >>
                           PMIC4_APM_EXPONENT_SHIFT;

                // Scale in floating point: a 19-bit mantissa shifted by up
                // to 31 bits does not fit in a 32-bit integer.
                sample.apm_value[ channel ] = ( float ) mantissa;
                while ( exponent )
                {
                    sample.apm_value[ channel ] *= 2.0f;
                    exponent--;
                }
                // Raw units remain available with zero alpha; validity here
                // describes current conversion, not calibration accuracy.
                if ( !( sample.errors & ( PMIC4_APM_CHANNEL_ERROR_MASK <<
                                           ( channel * PMIC4_APM_ERROR_BITS_PER_CHANNEL ) ) ) )
                {
                    if ( mantissa )
                    {
                        sample.activity |= mask;
                    }
                    if ( cfg->alpha[ channel ] > 0.0f )
                    {
                        // P / VSTO is the average current at STO. It is not
                        // the current at a source input or the LOAD terminal.
                        sample.current[ channel ] = sample.apm_value[ channel ] *
                                                    cfg->alpha[ channel ] * PMIC4_MILLIAMPS_PER_AMP /
                                                    sample.storage_voltage;
                        sample.valid |= mask;
                    }
                }
            }

            // Activity follows charging duty even without current calibration.
            // A zero CC current must not expose an assumed charging current.
            if ( charger_count )
            {
                sample.activity |= PMIC4_CURRENT_CHARGER_VALID;
            }
            // CC calibration does not apply to the limited precharge current.
            // Leave that conversion unavailable rather than use a nominal value.
            if ( ( cfg->charger_current > 0.0f ) &&
                 !( sample.errors & PMIC4_APM_CHARGER_LIMITED ) )
            {
                sample.current[ PMIC4_CURRENT_CHARGER ] = cfg->charger_current * charger_count / charger_max;
                sample.valid |= PMIC4_CURRENT_CHARGER_VALID;
            }
            // Do not overwrite the caller's last sample after a failed read.
            *currents = sample;
        }
    }

    return error_flag;
}

err_t pmic4_get_status ( pmic4_t *ctx, pmic4_status_t *status )
{
    uint8_t buff[ PMIC4_REGISTER_PAIR_SIZE ];
    err_t error_flag = PMIC4_ERROR;

    if ( status )
    {
        // Read STATUSx, not the clear-on-read IRQFLGx registers.
        error_flag = pmic4_read_regs( ctx, PMIC4_REG_STATUS0, buff, PMIC4_REGISTER_PAIR_SIZE );
        if ( PMIC4_OK == error_flag )
        {
            status->power = buff[ 0 ];
            status->temperature = buff[ 1 ];
        }
    }

    return error_flag;
}

err_t pmic4_get_voltage ( pmic4_t *ctx, uint8_t channel, float *voltage )
{
    uint8_t raw;
    err_t error_flag = PMIC4_ERROR;

    if ( voltage && ( channel <= PMIC4_VOLTAGE_SOURCE_2 ) )
    {
        // STO, SRC1, and SRC2 are consecutive registers. No conversion is
        // requested: these registers hold the latest autonomous measurements.
        error_flag = pmic4_read_reg( ctx, PMIC4_REG_STO + channel, &raw );
        if ( PMIC4_OK == error_flag )
        {
            if ( PMIC4_VOLTAGE_STORAGE == channel )
            {
                *voltage = raw * PMIC4_STORAGE_VOLTAGE_LSB;
            }
            else if ( raw <= PMIC4_SOURCE_FLOOR_CODE )
            {
                *voltage = PMIC4_SOURCE_FLOOR_V;
            }
            else if ( raw <= PMIC4_SOURCE_RANGE_1_MAX )
            {
                *voltage = PMIC4_SOURCE_FINE_BASE_V +
                           ( PMIC4_SOURCE_CODE_MULTIPLIER * raw - PMIC4_SOURCE_RANGE_1_OFFSET ) *
                           PMIC4_SOURCE_FINE_STEP_V;
            }
            else if ( raw <= PMIC4_SOURCE_RANGE_2_MAX )
            {
                *voltage = PMIC4_SOURCE_COARSE_BASE_V +
                           ( PMIC4_SOURCE_CODE_MULTIPLIER * raw - PMIC4_SOURCE_RANGE_2_OFFSET ) *
                           PMIC4_SOURCE_COARSE_STEP_V;
            }
            else if ( ( raw >= PMIC4_SOURCE_RANGE_3_MIN ) &&
                      ( raw <= PMIC4_SOURCE_RANGE_3_MAX ) )
            {
                // Upper ranges use different divider ratios and code offsets.
                *voltage = ( PMIC4_SOURCE_COARSE_BASE_V +
                             ( PMIC4_SOURCE_CODE_MULTIPLIER * raw - PMIC4_SOURCE_RANGE_3_OFFSET ) *
                             PMIC4_SOURCE_COARSE_STEP_V ) / PMIC4_SOURCE_RANGE_3_DIVIDER;
            }
            else if ( ( raw >= PMIC4_SOURCE_RANGE_4_MIN ) &&
                      ( raw <= PMIC4_SOURCE_RANGE_4_MAX ) )
            {
                *voltage = ( PMIC4_SOURCE_COARSE_BASE_V +
                             ( PMIC4_SOURCE_CODE_MULTIPLIER * raw - PMIC4_SOURCE_RANGE_4_OFFSET ) *
                             PMIC4_SOURCE_COARSE_STEP_V ) / PMIC4_SOURCE_RANGE_4_DIVIDER;
            }
            else
            {
                // Gaps between valid code ranges must not become plausible voltages.
                error_flag = PMIC4_ERROR;
            }
        }
    }

    return error_flag;
}

err_t pmic4_get_temperature ( pmic4_t *ctx, float *temperature )
{
    uint8_t raw;
    float resistance;
    err_t error_flag = PMIC4_ERROR;

    if ( ctx && temperature )
    {
        error_flag = pmic4_read_reg( ctx, PMIC4_REG_TEMP, &raw );
        if ( PMIC4_OK == error_flag )
        {
            // Reject reset/zero and full-scale codes before evaluating log.
            // Endpoint codes cannot provide a trustworthy NTC measurement.
            if ( ( raw >= PMIC4_NTC_ADC_CODE_MIN ) && ( raw <= PMIC4_NTC_ADC_CODE_MAX ) )
            {
                resistance = PMIC4_NTC_DIVIDER_OHM * raw /
                             ( PMIC4_NTC_ADC_FULL_SCALE - raw );
                // Solve the NTC beta equation in kelvin, then convert to Celsius.
                *temperature = PMIC4_NTC_BETA_K /
                               ( log( resistance / PMIC4_NTC_R25_OHM ) +
                                 PMIC4_NTC_BETA_K / PMIC4_NTC_REFERENCE_K ) -
                               PMIC4_NTC_KELVIN_OFFSET;
            }
            else
            {
                error_flag = PMIC4_ERROR_SAMPLE;
            }
        }
    }

    return error_flag;
}

err_t pmic4_get_interrupt_flags ( pmic4_t *ctx, uint16_t *flags )
{
    uint8_t buff[ PMIC4_REGISTER_PAIR_SIZE ];
    err_t error_flag = PMIC4_ERROR;

    if ( flags )
    {
        // Reading both bytes acknowledges the causes that hold IRQ high.
        error_flag = pmic4_read_regs( ctx, PMIC4_REG_IRQFLG0, buff, PMIC4_REGISTER_PAIR_SIZE );
        if ( PMIC4_OK == error_flag )
        {
            *flags = ( ( uint16_t ) buff[ 1 ] << PMIC4_REGISTER_BYTE_BITS ) | buff[ 0 ];
        }
    }

    return error_flag;
}

uint8_t pmic4_get_stl_pin ( pmic4_t *ctx )
{
    // Q2 pulls mikroBUS AN low when the PMIC asserts ST_LOAD.
    return ( 0 == digital_in_read( &ctx->stl ) );
}

uint8_t pmic4_get_int_pin ( pmic4_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static err_t pmic4_wait_sync ( pmic4_t *ctx )
{
    uint8_t ctrl;
    uint8_t cnt;
    err_t error_flag = PMIC4_ERROR;

    for ( cnt = 0; cnt < PMIC4_POLL_COUNT; cnt++ )
    {
        error_flag = pmic4_read_reg( ctx, PMIC4_REG_CTRL, &ctrl );
        if ( PMIC4_OK != error_flag )
        {
            break;
        }
        if ( !( ctrl & PMIC4_CTRL_SYNCBUSY ) )
        {
            break;
        }
        error_flag = PMIC4_NOT_READY;
        Delay_10ms();
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
