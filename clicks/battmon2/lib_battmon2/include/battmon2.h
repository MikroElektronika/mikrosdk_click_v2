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
 * @file battmon2.h
 * @brief This file contains API for BATT-MON 2 Click Driver.
 */

#ifndef BATTMON2_H
#define BATTMON2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup battmon2 BATT-MON 2 Click Driver
 * @brief API for configuring and manipulating BATT-MON 2 Click driver.
 * @{
 */

/**
 * @defgroup battmon2_reg BATT-MON 2 Registers List
 * @brief List of registers of BATT-MON 2 Click driver.
 */

/**
 * @addtogroup battmon2_reg
 * @{
 */

/**
 * @brief BATT-MON 2 Register Map.
 * @details Specified register map of BATT-MON 2 Click driver.
 */
#define BATTMON2_REG_STATUS                 0x00
#define BATTMON2_REG_V_ALRT_TH              0x01
#define BATTMON2_REG_T_ALRT_TH              0x02
#define BATTMON2_REG_S_ALRT_TH              0x03
#define BATTMON2_REG_AT_RATE                0x04
#define BATTMON2_REG_REP_CAP                0x05
#define BATTMON2_REG_REP_SOC                0x06
#define BATTMON2_REG_AGE                    0x07
#define BATTMON2_REG_TEMP                   0x08
#define BATTMON2_REG_V_CELL                 0x09
#define BATTMON2_REG_CURRENT                0x0A
#define BATTMON2_REG_AVG_CURRENT            0x0B
#define BATTMON2_REG_Q_RESIDUAL             0x0C
#define BATTMON2_REG_MIX_SOC                0x0D
#define BATTMON2_REG_AV_SOC                 0x0E
#define BATTMON2_REG_MIX_CAP                0x0F
#define BATTMON2_REG_FULL_CAP_REP           0x10
#define BATTMON2_REG_TTE                    0x11
#define BATTMON2_REG_QR_TABLE_00            0x12
#define BATTMON2_REG_FULL_SOC_THR           0x13
#define BATTMON2_REG_R_CELL                 0x14
#define BATTMON2_REG_AVG_TA                 0x16
#define BATTMON2_REG_CYCLES                 0x17
#define BATTMON2_REG_DESIGN_CAP             0x18
#define BATTMON2_REG_AVG_V_CELL             0x19
#define BATTMON2_REG_MAX_MIN_TEMP           0x1A
#define BATTMON2_REG_MAX_MIN_VOLT           0x1B
#define BATTMON2_REG_MAX_MIN_CURR           0x1C
#define BATTMON2_REG_CONFIG                 0x1D
#define BATTMON2_REG_I_CHG_TERM             0x1E
#define BATTMON2_REG_AV_CAP                 0x1F
#define BATTMON2_REG_TTF                    0x20
#define BATTMON2_REG_DEV_NAME               0x21
#define BATTMON2_REG_QR_TABLE_10            0x22
#define BATTMON2_REG_FULL_CAP_NOM           0x23
#define BATTMON2_REG_AIN                    0x27
#define BATTMON2_REG_LEARN_CFG              0x28
#define BATTMON2_REG_FILTER_CFG             0x29
#define BATTMON2_REG_RELAX_CFG              0x2A
#define BATTMON2_REG_MISC_CFG               0x2B
#define BATTMON2_REG_T_GAIN                 0x2C
#define BATTMON2_REG_T_OFF                  0x2D
#define BATTMON2_REG_C_GAIN                 0x2E
#define BATTMON2_REG_C_OFF                  0x2F
#define BATTMON2_REG_QR_TABLE_20            0x32
#define BATTMON2_REG_DIE_TEMP               0x34
#define BATTMON2_REG_FULL_CAP               0x35
#define BATTMON2_REG_R_COMP_0               0x38
#define BATTMON2_REG_TEMP_CO                0x39
#define BATTMON2_REG_V_EMPTY                0x3A
#define BATTMON2_REG_F_STAT                 0x3D
#define BATTMON2_REG_TIMER                  0x3E
#define BATTMON2_REG_SHDN_TIMER             0x3F
#define BATTMON2_REG_QR_TABLE_30            0x42
#define BATTMON2_REG_R_GAIN                 0x43
#define BATTMON2_REG_DQ_ACC                 0x45
#define BATTMON2_REG_DP_ACC                 0x46
#define BATTMON2_REG_CONVG_CFG              0x49
#define BATTMON2_REG_V_F_REM_CAP            0x4A
#define BATTMON2_REG_QH                     0x4D
#define BATTMON2_REG_SOFT_WAKEUP            0x60
#define BATTMON2_REG_STATUS_2               0xB0
#define BATTMON2_REG_POWER                  0xB1
#define BATTMON2_REG_ID_USER_MEM_2          0xB2
#define BATTMON2_REG_AVG_POWER              0xB3
#define BATTMON2_REG_I_ALRT_TH              0xB4
#define BATTMON2_REG_TTF_CFG                0xB5
#define BATTMON2_REG_C_V_MIX_CAP            0xB6
#define BATTMON2_REG_C_V_HALF_TIME          0xB7
#define BATTMON2_REG_C_G_TEMP_CO            0xB8
#define BATTMON2_REG_CURVE                  0xB9
#define BATTMON2_REG_HIB_CFG                0xBA
#define BATTMON2_REG_CONFIG_2               0xBB
#define BATTMON2_REG_V_RIPPLE               0xBC
#define BATTMON2_REG_RIPPLE_CFG             0xBD
#define BATTMON2_REG_TIMER_H                0xBE
#define BATTMON2_REG_R_SENSE_USER_MEM_3     0xD0
#define BATTMON2_REG_SC_OCV_LIM             0xD1
#define BATTMON2_REG_V_GAIN                 0xD2
#define BATTMON2_REG_SOC_HOLD               0xD3
#define BATTMON2_REG_MAX_PEAK_POWER         0xD4
#define BATTMON2_REG_SUS_PEAK_POWER         0xD5
#define BATTMON2_REG_PACK_RESISTANCE        0xD6
#define BATTMON2_REG_SYS_RESISTANCE         0xD7
#define BATTMON2_REG_MIN_SYS_VOLTAGE        0xD8
#define BATTMON2_REG_MPP_CURRENT            0xD9
#define BATTMON2_REG_SPP_CURRENT            0xDA
#define BATTMON2_REG_MODEL_CFG              0xDB
#define BATTMON2_REG_AT_Q_RESIDUAL          0xDC
#define BATTMON2_REG_AT_TTE                 0xDD
#define BATTMON2_REG_AT_AV_SOC              0xDE
#define BATTMON2_REG_AT_AV_CAP              0xDF

/*! @} */ // battmon2_reg

/**
 * @defgroup battmon2_set BATT-MON 2 Registers Settings
 * @brief Settings for registers of BATT-MON 2 Click driver.
 */

/**
 * @addtogroup battmon2_set
 * @{
 */

/**
 * @brief BATT-MON 2 standard resolutions.
 * @details Specified standard resolutions of BATT-MON 2 Click driver.
 */
#define BATTMON2_CAPACITY_RESOLUTION        0.5
#define BATTMON2_PERCENTAGE_RESOLUTION      ( 1.0 / 256.0 )
#define BATTMON2_VOLTAGE_RESOLUTION         ( 1.25 / 16.0 )
#define BATTMON2_CURRENT_RESOLUTION         0.15625
#define BATTMON2_TEMPERATURE_RESOLUTION     ( 1.0 / 256.0 )
#define BATTMON2_TIME_RESOLUTION            5.625

/**
 * @brief BATT-MON 2 device ID value.
 * @details Specified device ID value of BATT-MON 2 Click driver.
 */
#define BATTMON2_DEVICE_ID                  0x4039

/**
 * @brief BATT-MON 2 device address setting.
 * @details Specified setting for device slave address selection of
 * BATT-MON 2 Click driver.
 */
#define BATTMON2_SET_DEV_ADDR               0x36

/*! @} */ // battmon2_set

/**
 * @defgroup battmon2_map BATT-MON 2 MikroBUS Map
 * @brief MikroBUS pin mapping of BATT-MON 2 Click driver.
 */

/**
 * @addtogroup battmon2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BATT-MON 2 Click to the selected MikroBUS.
 */
#define BATTMON2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // battmon2_map
/*! @} */ // battmon2

/**
 * @brief BATT-MON 2 Click context object.
 * @details Context object definition of BATT-MON 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  alert;        /**< Alert pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} battmon2_t;

/**
 * @brief BATT-MON 2 Click configuration object.
 * @details Configuration object definition of BATT-MON 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  alert;          /**< Alert pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} battmon2_cfg_t;

/**
 * @brief BATT-MON 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BATTMON2_OK = 0,
    BATTMON2_ERROR = -1

} battmon2_return_value_t;

/*!
 * @addtogroup battmon2 BATT-MON 2 Click Driver
 * @brief API for configuring and manipulating BATT-MON 2 Click driver.
 * @{
 */

/**
 * @brief BATT-MON 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #battmon2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void battmon2_cfg_setup ( battmon2_cfg_t *cfg );

/**
 * @brief BATT-MON 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #battmon2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon2_init ( battmon2_t *ctx, battmon2_cfg_t *cfg );

/**
 * @brief BATT-MON 2 I2C writing function.
 * @details This function writes a desired number of data words starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon2_generic_write ( battmon2_t *ctx, uint8_t reg, uint16_t *tx_buf, uint8_t tx_len );

/**
 * @brief BATT-MON 2 I2C reading function.
 * @details This function reads a desired number of data words starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon2_generic_read ( battmon2_t *ctx, uint8_t reg, uint16_t *rx_buf, uint8_t rx_len );

/**
 * @brief BATT-MON 2 write register function.
 * @details This function writes a desired data to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon2_write_register ( battmon2_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief BATT-MON 2 read register function.
 * @details This function reads data from the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon2_read_register ( battmon2_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief BATT-MON 2 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon2_check_communication ( battmon2_t *ctx );

/**
 * @brief BATT-MON 2 get alert pin function.
 * @details This function returns the alert pin logic state.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t battmon2_get_alert_pin ( battmon2_t *ctx );

/**
 * @brief BATT-MON 2 get die temperature function.
 * @details This function reads the chip internal (die) temperature.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon2_get_die_temperature ( battmon2_t *ctx, float *temperature );

/**
 * @brief BATT-MON 2 get battery capacity function.
 * @details This function reads the battery remaining capacity in mAh.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[out] capacity : Battery capacity in mAh.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon2_get_battery_capacity ( battmon2_t *ctx, float *capacity );

/**
 * @brief BATT-MON 2 get battery percentage function.
 * @details This function reads the battery remaining SOC percentage.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[out] percentage : SOC percentage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon2_get_battery_percentage ( battmon2_t *ctx, float *percentage );

/**
 * @brief BATT-MON 2 get battery voltage function.
 * @details This function reads the battery voltage in mV.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[out] voltage : Voltage in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon2_get_battery_voltage ( battmon2_t *ctx, float *voltage );

/**
 * @brief BATT-MON 2 get battery current function.
 * @details This function reads the battery current in mA.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[out] current : Current in mA.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t battmon2_get_battery_current ( battmon2_t *ctx, float *current );

/**
 * @brief BATT-MON 2 get battery tte function.
 * @details This function reads the battery estimating time to empty.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[out] time_to_empty : Time to empty in seconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Valid only when current is negative, ie. when a load is attached to VSYS.
 */
err_t battmon2_get_battery_tte ( battmon2_t *ctx, uint32_t *time_to_empty );

/**
 * @brief BATT-MON 2 get battery ttf function.
 * @details This function reads the battery estimating time to full.
 * @param[in] ctx : Click context object.
 * See #battmon2_t object definition for detailed explanation.
 * @param[out] time_to_full : Time to full in seconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Valid only when current is positive, ie. when a charger is attached to VSYS.
 */
err_t battmon2_get_battery_ttf ( battmon2_t *ctx, uint32_t *time_to_full );

#ifdef __cplusplus
}
#endif
#endif // BATTMON2_H

/*! @} */ // battmon2

// ------------------------------------------------------------------------ END
