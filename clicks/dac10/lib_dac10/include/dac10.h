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
 * @file dac10.h
 * @brief This file contains API for DAC 10 Click Driver.
 */

#ifndef DAC10_H
#define DAC10_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup dac10 DAC 10 Click Driver
 * @brief API for configuring and manipulating DAC 10 Click driver.
 * @{
 */

/**
 * @defgroup dac10_reg DAC 10 Registers List
 * @brief List of registers of DAC 10 Click driver.
 */

/**
 * @addtogroup dac10_reg
 * @{
 */

/**
 * @brief DAC 10 Register Map.
 * @details List of registers of DAC 10 Click driver.
 */
#define DAC10_REG_STATUS                                0xD0
#define DAC10_REG_GENERAL_CONFIG                        0xD1
#define DAC10_REG_TRIGGER                               0xD3
#define DAC10_REG_DAC_DATA                              0x21
#define DAC10_REG_DAC_MARGIN_HIGH                       0x25
#define DAC10_REG_DAC_MARGIN_LOW                        0x26
#define DAC10_REG_PMBUS_OPERATION                       0x01
#define DAC10_REG_PMBUS_STATUS_BYTE                     0x78
#define DAC10_REG_PMBUS_VERSION                         0x98

/*! @} */ // dac10_reg

/**
 * @defgroup dac10_set DAC 10 Registers Settings
 * @brief Settings for registers of DAC 10 Click driver.
 */

/**
 * @addtogroup dac10_set
 * @{
 */

/**
 * @brief DAC 10 status register values.
 * @details Specified values for status register of DAC 10 Click driver.
 */
#define DAC10_STATUS_NVM_CRC_ALARM_USER                 0x8000
#define DAC10_STATUS_NVM_CRC_ALARM_INTERNAL             0x4000
#define DAC10_STATUS_NVM_BUSY                           0x2000
#define DAC10_STATUS_DAC_UPDATE_BUSY                    0x1000
#define DAC10_STATUS_DEVICE_ID                          0x000C
#define DAC10_STATUS_DEVICE_ID_MASK                     0x003C
#define DAC10_STATUS_VERSION_ID_MASK                    0x0003

/**
 * @brief DAC 10 general config register setting.
 * @details Specified settings for general config register of DAC 10 Click driver.
 */
#define DAC10_GEN_CONFIG_FCFG_TRIANGLE_WAVE             0x0000
#define DAC10_GEN_CONFIG_FCFG_SAW_TOOTH_WAVE_RISING     0x4000
#define DAC10_GEN_CONFIG_FCFG_SAW_TOOTH_WAVE_FALLING    0x8000
#define DAC10_GEN_CONFIG_FCFG_SQUARE_WAVE               0xC000
#define DAC10_GEN_CONFIG_FCFG_CLR_MASK                  0xC000
#define DAC10_GEN_CONFIG_DEVICE_LOCKED                  0x2000
#define DAC10_GEN_CONFIG_DEVICE_NOT_LOCKED              0x0000
#define DAC10_GEN_CONFIG_DEVICE_LOCK_MASK               0x2000
#define DAC10_GEN_CONFIG_PMBUS_ENABLE                   0x1000
#define DAC10_GEN_CONFIG_PMBUS_DISABLE                  0x0000
#define DAC10_GEN_CONFIG_PMBUS_EN_MASK                  0x1000
#define DAC10_GEN_CONFIG_CODE_STEP_1LSB                 0x0000
#define DAC10_GEN_CONFIG_CODE_STEP_2LSB                 0x0200
#define DAC10_GEN_CONFIG_CODE_STEP_3LSB                 0x0400
#define DAC10_GEN_CONFIG_CODE_STEP_4LSB                 0x0600
#define DAC10_GEN_CONFIG_CODE_STEP_6LSB                 0x0800
#define DAC10_GEN_CONFIG_CODE_STEP_8LSB                 0x0A00
#define DAC10_GEN_CONFIG_CODE_STEP_16LSB                0x0C00
#define DAC10_GEN_CONFIG_CODE_STEP_32LSB                0x0E00
#define DAC10_GEN_CONFIG_CODE_STEP_MASK                 0x0E00
#define DAC10_GEN_CONFIG_SLEW_RATE_25p6US               0x0000
#define DAC10_GEN_CONFIG_SLEW_RATE_25p6USx1p25          0x0020
#define DAC10_GEN_CONFIG_SLEW_RATE_25p6USx1p50          0x0040
#define DAC10_GEN_CONFIG_SLEW_RATE_25p6USx1p75          0x0060
#define DAC10_GEN_CONFIG_SLEW_RATE_204p8US              0x0080
#define DAC10_GEN_CONFIG_SLEW_RATE_204p8USx1p25         0x00A0
#define DAC10_GEN_CONFIG_SLEW_RATE_204p8USx1p50         0x00C0
#define DAC10_GEN_CONFIG_SLEW_RATE_204p8USx1p75         0x00E0
#define DAC10_GEN_CONFIG_SLEW_RATE_1p6384MS             0x0100
#define DAC10_GEN_CONFIG_SLEW_RATE_1p6384MSx1p25        0x0120
#define DAC10_GEN_CONFIG_SLEW_RATE_1p6384MSx1p50        0x0140
#define DAC10_GEN_CONFIG_SLEW_RATE_1p6384MSx1p75        0x0160
#define DAC10_GEN_CONFIG_SLEW_RATE_12US                 0x0180
#define DAC10_GEN_CONFIG_SLEW_RATE_8US                  0x01A0
#define DAC10_GEN_CONFIG_SLEW_RATE_4US                  0x01C0
#define DAC10_GEN_CONFIG_SLEW_RATE_NO_SLEW              0x01E0
#define DAC10_GEN_CONFIG_SLEW_RATE_MASK                 0x01E0
#define DAC10_GEN_CONFIG_DAC_PDN_POWER_UP               0x0000
#define DAC10_GEN_CONFIG_DAC_PDN_POWER_DOWN_10K         0x0008
#define DAC10_GEN_CONFIG_DAC_PDN_POWER_DOWN_HIGH_Z      0x0010
#define DAC10_GEN_CONFIG_DAC_PDN_MASK                   0x0018
#define DAC10_GEN_CONFIG_INT_REF_ENABLE                 0x0004
#define DAC10_GEN_CONFIG_INT_REF_DISABLE                0x0000
#define DAC10_GEN_CONFIG_INT_REF_EN_MASK                0x0004
#define DAC10_GEN_CONFIG_DAC_SPAN_GAIN_1p5X             0x0000
#define DAC10_GEN_CONFIG_DAC_SPAN_GAIN_2X               0x0001
#define DAC10_GEN_CONFIG_DAC_SPAN_GAIN_3X               0x0002
#define DAC10_GEN_CONFIG_DAC_SPAN_GAIN_4X               0x0003
#define DAC10_GEN_CONFIG_DAC_SPAN_MASK                  0x0003

/**
 * @brief DAC 10 trigger register setting.
 * @details Specified settings for trigger register of DAC 10 Click driver.
 */
#define DAC10_TRIGGER_DEVICE_UNLOCK_CODE                0x5000
#define DAC10_TRIGGER_DEVICE_UNLOCK_CODE_MASK           0xF000
#define DAC10_TRIGGER_DEVICE_CONFIG_RESET_INITIATED     0x0200
#define DAC10_TRIGGER_DEVICE_CONFIG_RESET_NOT_INITIATED 0x0000
#define DAC10_TRIGGER_DEVICE_CONFIG_RESET_MASK          0x0200
#define DAC10_TRIGGER_START_FUNC_GEN_ENABLE             0x0100
#define DAC10_TRIGGER_START_FUNC_GEN_DISABLE            0x0000
#define DAC10_TRIGGER_START_FUNC_GEN_MASK               0x0100
#define DAC10_TRIGGER_PMBUS_MARGIN_HIGH_INITIATED       0x0080
#define DAC10_TRIGGER_PMBUS_MARGIN_HIGH_NOT_INITIATED   0x0000
#define DAC10_TRIGGER_PMBUS_MARGIN_HIGH_MASK            0x0080
#define DAC10_TRIGGER_PMBUS_MARGIN_LOW_INITIATED        0x0040
#define DAC10_TRIGGER_PMBUS_MARGIN_LOW_NOT_INITIATED    0x0000
#define DAC10_TRIGGER_PMBUS_MARGIN_LOW_MASK             0x0040
#define DAC10_TRIGGER_NWM_RELOAD_INITIATED              0x0020
#define DAC10_TRIGGER_NWM_RELOAD_NOT_INITIATED          0x0000
#define DAC10_TRIGGER_NWM_RELOAD_MASK                   0x0020
#define DAC10_TRIGGER_NWM_PROG_INITIATED                0x0010
#define DAC10_TRIGGER_NWM_PROG_NOT_INITIATED            0x0000
#define DAC10_TRIGGER_NWM_PROG_MASK                     0x0010
#define DAC10_TRIGGER_SW_RESET_INITIATED                0x0008
#define DAC10_TRIGGER_SW_RESET_NOT_INITIATED            0x000A
#define DAC10_TRIGGER_SW_RESET_MASK                     0x000F

/**
 * @brief DAC 10 PMBus operation register setting.
 * @details Specified settings for PMBus operation register of DAC 10 Click driver.
 */
#define DAC10_PMBUS_OPERATION_CMD_TURN_OFF              0x0000
#define DAC10_PMBUS_OPERATION_CMD_TURN_ON               0x8000
#define DAC10_PMBUS_OPERATION_CMD_MARGIN_HIGH           0xA400
#define DAC10_PMBUS_OPERATION_CMD_MARGIN_LOW            0x9400
#define DAC10_PMBUS_OPERATION_CMD                       0xFF00

/**
 * @brief DAC 10 PMBus status byte register setting.
 * @details Specified settings for PMBus status byte register of DAC 10 Click driver.
 */
#define DAC10_PMBUS_STATUS_BYTE_CML_NO_FAULT            0x0000
#define DAC10_PMBUS_STATUS_BYTE_CML_FAULT               0x0200
#define DAC10_PMBUS_STATUS_BYTE_CML_MASK                0x0200

/**
 * @brief DAC 10 PMBus version register setting.
 * @details Specified settings for PMBus version register of DAC 10 Click driver.
 */
#define DAC10_PMBUS_VERSION_DEFAULT                     0x2200
#define DAC10_PMBUS_VERSION_MASK                        0xFF00

/**
 * @brief DAC 10 range values.
 * @details DAC range values of DAC 10 Click driver.
 */
#define DAC10_MIN_DAC_VALUE                             0x0000
#define DAC10_MAX_DAC_VALUE                             0x03FF

/**
 * @brief DAC 10 vref values.
 * @details DAC vref values of DAC 10 Click driver.
 */
#define DAC10_VREF_3V3                                  3.3
#define DAC10_VREF_5V                                   5
#define DAC10_VREF_INT                                  1.21

/**
 * @brief DAC 10 device address setting.
 * @details Specified setting for device slave address selection of
 * DAC 10 Click driver.
 */
#define DAC10_DEV_ADDR_GND                              0x48
#define DAC10_DEV_ADDR_VCC                              0x49
#define DAC10_DEV_ADDR_SDA                              0x4A
#define DAC10_DEV_ADDR_SCL                              0x4B
#define DAC10_DEV_ADDR_BROADCAST                        0x47


/*! @} */ // dac10_set

/**
 * @defgroup dac10_map DAC 10 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 10 Click driver.
 */

/**
 * @addtogroup dac10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 10 Click to the selected MikroBUS.
 */
#define DAC10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );

/*! @} */ // dac10_map
/*! @} */ // dac10

/**
 * @brief DAC 10 Click context object.
 * @details Context object definition of DAC 10 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

} dac10_t;

/**
 * @brief DAC 10 Click configuration object.
 * @details Configuration object definition of DAC 10 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} dac10_cfg_t;

/**
 * @brief DAC 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC10_OK = 0,
    DAC10_ERROR = -1

} dac10_return_value_t;

/*!
 * @addtogroup dac10 DAC 10 Click Driver
 * @brief API for configuring and manipulating DAC 10 Click driver.
 * @{
 */

/**
 * @brief DAC 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac10_cfg_setup ( dac10_cfg_t *cfg );

/**
 * @brief DAC 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dac10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac10_init ( dac10_t *ctx, dac10_cfg_t *cfg );

/**
 * @brief DAC 10 I2C writing function.
 * @details This function writes a two bytes of data to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac10_reg_write ( dac10_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 10 I2C reading function.
 * @details This function reads two bytes of data from the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac10_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_in : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac10_reg_read ( dac10_t *ctx, uint8_t reg, uint16_t *data_in );

/**
 * @brief DAC 10 set dac value function.
 * @details This function sets the DAC DATA register to a desired value.
 * @param[in] ctx : Click context object.
 * See #dac10_t object definition for detailed explanation.
 * @param[in] data_in : 10-bit DAC data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac10_set_dac_value ( dac10_t *ctx, uint16_t data_in );

/**
 * @brief DAC 10 set output voltage function.
 * @details This function sets the output voltage depending on the vref value defined by
 * the VCC SEL on-board jumper. VREF and Voltage values can be either in Volts or Milivolts.
 * @param[in] ctx : Click context object.
 * See #dac10_t object definition for detailed explanation.
 * @param[in] vref : VREF value defined by VCC SEL on-board jumper.
 * @param[in] voltage : Float value to be set as output voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac10_set_output_voltage ( dac10_t *ctx, float vref, float voltage );

/**
 * @brief DAC 10 set output voltage with internal reference function.
 * @details This function sets the output voltage with the internal reference enabled. 
 * @param[in] ctx : Click context object.
 * See #dac10_t object definition for detailed explanation.
 * @param[in] voltage : Float value to be set as output voltage ( in Volts ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac10_set_output_voltage_int_vref ( dac10_t *ctx, float voltage );

/**
 * @brief DAC 10 set dac margin high function.
 * @details This function sets the DAC MARGIH HIGH register to a desired value.
 * @param[in] ctx : Click context object.
 * See #dac10_t object definition for detailed explanation.
 * @param[in] data_in : 10-bit data input.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac10_set_dac_margin_high ( dac10_t *ctx, uint16_t data_in );

/**
 * @brief DAC 10 set dac margin low function.
 * @details This function sets the DAC MARGIH LOW register to a desired value.
 * @param[in] ctx : Click context object.
 * See #dac10_t object definition for detailed explanation.
 * @param[in] data_in : 10-bit data input.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac10_set_dac_margin_low ( dac10_t *ctx, uint16_t data_in );

/**
 * @brief DAC 10 check device ID function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #dac10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac10_check_device_id ( dac10_t *ctx );

/**
 * @brief DAC 10 enable DAC output function.
 * @details This function enables the DAC output.
 * @param[in] ctx : Click context object.
 * See #dac10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac10_enable_dac ( dac10_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DAC10_H

/*! @} */ // dac10

// ------------------------------------------------------------------------ END
