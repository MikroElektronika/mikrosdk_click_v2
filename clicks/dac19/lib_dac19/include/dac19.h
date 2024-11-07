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
 * @file dac19.h
 * @brief This file contains API for DAC 19 Click Driver.
 */

#ifndef DAC19_H
#define DAC19_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup dac19 DAC 19 Click Driver
 * @brief API for configuring and manipulating DAC 19 Click driver.
 * @{
 */

/**
 * @defgroup dac19_reg DAC 19 Registers List
 * @brief List of registers of DAC 19 Click driver.
 */

/**
 * @addtogroup dac19_reg
 * @{
 */

/**
 * @brief DAC 19 Register Map.
 * @details List of registers of DAC 19 Click driver.
 */
#define DAC19_REG_STATUS                                0xD0
#define DAC19_REG_GENERAL_CONFIG                        0xD1
#define DAC19_REG_CONFIG2                               0xD2
#define DAC19_REG_TRIGGER                               0xD3
#define DAC19_REG_DAC_DATA                              0x21
#define DAC19_REG_DAC_MARGIN_HIGH                       0x25
#define DAC19_REG_DAC_MARGIN_LOW                        0x26
#define DAC19_REG_PMBUS_OPERATION                       0x01
#define DAC19_REG_PMBUS_STATUS_BYTE                     0x78
#define DAC19_REG_PMBUS_VERSION                         0x98

/*! @} */ // dac19_reg

/**
 * @defgroup dac19_set DAC 19 Registers Settings
 * @brief Settings for registers of DAC 19 Click driver.
 */

/**
 * @addtogroup dac19_set
 * @{
 */

/**
 * @brief DAC 19 status register values.
 * @details Specified values for status register of DAC 19 Click driver.
 */
#define DAC19_STATUS_NVM_CRC_ALARM_USER                 0x8000
#define DAC19_STATUS_NVM_CRC_ALARM_INTERNAL             0x4000
#define DAC19_STATUS_NVM_BUSY                           0x2000
#define DAC19_STATUS_DAC_UPDATE_BUSY                    0x1000
#define DAC19_STATUS_DEVICE_ID                          0x000C
#define DAC19_STATUS_DEVICE_ID_MASK                     0x003C
#define DAC19_STATUS_VERSION_ID_MASK                    0x0003

/**
 * @brief DAC 19 general config register setting.
 * @details Specified settings for general config register of DAC 19 Click driver.
 */
#define DAC19_GEN_CONFIG_FCFG_TRIANGLE_WAVE             0x0000
#define DAC19_GEN_CONFIG_FCFG_SAW_TOOTH_WAVE_RISING     0x4000
#define DAC19_GEN_CONFIG_FCFG_SAW_TOOTH_WAVE_FALLING    0x8000
#define DAC19_GEN_CONFIG_FCFG_SQUARE_WAVE               0xC000
#define DAC19_GEN_CONFIG_FCFG_CLR_MASK                  0xC000
#define DAC19_GEN_CONFIG_DEVICE_LOCKED                  0x2000
#define DAC19_GEN_CONFIG_DEVICE_NOT_LOCKED              0x0000
#define DAC19_GEN_CONFIG_DEVICE_LOCK_MASK               0x2000
#define DAC19_GEN_CONFIG_PMBUS_ENABLE                   0x1000
#define DAC19_GEN_CONFIG_PMBUS_DISABLE                  0x0000
#define DAC19_GEN_CONFIG_PMBUS_EN_MASK                  0x1000
#define DAC19_GEN_CONFIG_CODE_STEP_1LSB                 0x0000
#define DAC19_GEN_CONFIG_CODE_STEP_2LSB                 0x0200
#define DAC19_GEN_CONFIG_CODE_STEP_3LSB                 0x0400
#define DAC19_GEN_CONFIG_CODE_STEP_4LSB                 0x0600
#define DAC19_GEN_CONFIG_CODE_STEP_6LSB                 0x0800
#define DAC19_GEN_CONFIG_CODE_STEP_8LSB                 0x0A00
#define DAC19_GEN_CONFIG_CODE_STEP_16LSB                0x0C00
#define DAC19_GEN_CONFIG_CODE_STEP_32LSB                0x0E00
#define DAC19_GEN_CONFIG_CODE_STEP_MASK                 0x0E00
#define DAC19_GEN_CONFIG_SLEW_RATE_25_6US               0x0000
#define DAC19_GEN_CONFIG_SLEW_RATE_32US                 0x0020
#define DAC19_GEN_CONFIG_SLEW_RATE_38_4US               0x0040
#define DAC19_GEN_CONFIG_SLEW_RATE_44_8US               0x0060
#define DAC19_GEN_CONFIG_SLEW_RATE_204_8US              0x0080
#define DAC19_GEN_CONFIG_SLEW_RATE_256US                0x00A0
#define DAC19_GEN_CONFIG_SLEW_RATE_307_2US              0x00C0
#define DAC19_GEN_CONFIG_SLEW_RATE_819_2US              0x00E0
#define DAC19_GEN_CONFIG_SLEW_RATE_1_6384MS             0x0100
#define DAC19_GEN_CONFIG_SLEW_RATE_2_4576MS             0x0120
#define DAC19_GEN_CONFIG_SLEW_RATE_3_2768MS             0x0140
#define DAC19_GEN_CONFIG_SLEW_RATE_4_9152MS             0x0160
#define DAC19_GEN_CONFIG_SLEW_RATE_12US                 0x0180
#define DAC19_GEN_CONFIG_SLEW_RATE_8US                  0x01A0
#define DAC19_GEN_CONFIG_SLEW_RATE_4US                  0x01C0
#define DAC19_GEN_CONFIG_SLEW_RATE_NO_SLEW              0x01E0
#define DAC19_GEN_CONFIG_SLEW_RATE_MASK                 0x01E0
#define DAC19_GEN_CONFIG_DAC_PDN_POWER_UP               0x0000
#define DAC19_GEN_CONFIG_DAC_PDN_POWER_DOWN_10K         0x0008
#define DAC19_GEN_CONFIG_DAC_PDN_POWER_DOWN_HIGH_Z      0x0010
#define DAC19_GEN_CONFIG_DAC_PDN_MASK                   0x0018
#define DAC19_GEN_CONFIG_INT_REF_ENABLE                 0x0004
#define DAC19_GEN_CONFIG_INT_REF_DISABLE                0x0000
#define DAC19_GEN_CONFIG_INT_REF_EN_MASK                0x0004
#define DAC19_GEN_CONFIG_DAC_SPAN_GAIN_1_5X             0x0000
#define DAC19_GEN_CONFIG_DAC_SPAN_GAIN_2X               0x0001
#define DAC19_GEN_CONFIG_DAC_SPAN_GAIN_3X               0x0002
#define DAC19_GEN_CONFIG_DAC_SPAN_GAIN_4X               0x0003
#define DAC19_GEN_CONFIG_DAC_SPAN_MASK                  0x0003

/**
 * @brief DAC 19 config2 register setting.
 * @details Specified settings for config2 register of DAC 19 Click driver.
 */
#define DAC19_CONFIG2_TARGET_ADDRESS_MASK               0xC000
#define DAC19_CONFIG2_GPI_CONFIG_MASK                   0x3800
#define DAC19_CONFIG2_FB_IMP_MASK                       0x003F

/**
 * @brief DAC 19 trigger register setting.
 * @details Specified settings for trigger register of DAC 19 Click driver.
 */
#define DAC19_TRIGGER_DEVICE_UNLOCK_CODE                0x5000
#define DAC19_TRIGGER_DEVICE_UNLOCK_CODE_MASK           0xF000
#define DAC19_TRIGGER_GPI_EN_ENABLE                     0x0400
#define DAC19_TRIGGER_GPI_EN_DISABLE                    0x0000
#define DAC19_TRIGGER_GPI_EN_MASK                       0x0400
#define DAC19_TRIGGER_DEVICE_CONFIG_RESET_INITIATED     0x0200
#define DAC19_TRIGGER_DEVICE_CONFIG_RESET_NOT_INITIATED 0x0000
#define DAC19_TRIGGER_DEVICE_CONFIG_RESET_MASK          0x0200
#define DAC19_TRIGGER_START_FUNC_GEN_ENABLE             0x0100
#define DAC19_TRIGGER_START_FUNC_GEN_DISABLE            0x0000
#define DAC19_TRIGGER_START_FUNC_GEN_MASK               0x0100
#define DAC19_TRIGGER_PMBUS_MARGIN_HIGH_INITIATED       0x0080
#define DAC19_TRIGGER_PMBUS_MARGIN_HIGH_NOT_INITIATED   0x0000
#define DAC19_TRIGGER_PMBUS_MARGIN_HIGH_MASK            0x0080
#define DAC19_TRIGGER_PMBUS_MARGIN_LOW_INITIATED        0x0040
#define DAC19_TRIGGER_PMBUS_MARGIN_LOW_NOT_INITIATED    0x0000
#define DAC19_TRIGGER_PMBUS_MARGIN_LOW_MASK             0x0040
#define DAC19_TRIGGER_NWM_RELOAD_INITIATED              0x0020
#define DAC19_TRIGGER_NWM_RELOAD_NOT_INITIATED          0x0000
#define DAC19_TRIGGER_NWM_RELOAD_MASK                   0x0020
#define DAC19_TRIGGER_NWM_PROG_INITIATED                0x0010
#define DAC19_TRIGGER_NWM_PROG_NOT_INITIATED            0x0000
#define DAC19_TRIGGER_NWM_PROG_MASK                     0x0010
#define DAC19_TRIGGER_SW_RESET_INITIATED                0x0008
#define DAC19_TRIGGER_SW_RESET_NOT_INITIATED            0x000A
#define DAC19_TRIGGER_SW_RESET_MASK                     0x000F

/**
 * @brief DAC 19 PMBus operation register setting.
 * @details Specified settings for PMBus operation register of DAC 19 Click driver.
 */
#define DAC19_PMBUS_OPERATION_CMD_TURN_OFF              0x0000
#define DAC19_PMBUS_OPERATION_CMD_TURN_ON               0x8000
#define DAC19_PMBUS_OPERATION_CMD_MARGIN_HIGH           0xA400
#define DAC19_PMBUS_OPERATION_CMD_MARGIN_LOW            0x9400
#define DAC19_PMBUS_OPERATION_CMD_MASK                  0xFF00

/**
 * @brief DAC 19 PMBus status byte register setting.
 * @details Specified settings for PMBus status byte register of DAC 19 Click driver.
 */
#define DAC19_PMBUS_STATUS_BYTE_CML_NO_FAULT            0x0000
#define DAC19_PMBUS_STATUS_BYTE_CML_FAULT               0x0200
#define DAC19_PMBUS_STATUS_BYTE_CML_MASK                0x0200

/**
 * @brief DAC 19 PMBus version register setting.
 * @details Specified settings for PMBus version register of DAC 19 Click driver.
 */
#define DAC19_PMBUS_VERSION_DEFAULT                     0x2200
#define DAC19_PMBUS_VERSION_MASK                        0xFF00

/**
 * @brief DAC 19 range values.
 * @details DAC range values of DAC 19 Click driver.
 */
#define DAC19_MIN_DAC_VALUE                             0x0000
#define DAC19_MAX_DAC_VALUE                             0x03FF

/**
 * @brief DAC 19 vref values.
 * @details DAC vref values of DAC 19 Click driver.
 */
#define DAC19_VREF_3V3                                  3300
#define DAC19_VREF_5V                                   5000
#define DAC19_VREF_INT                                  1210

/**
 * @brief DAC 19 device address setting.
 * @details Specified setting for device slave address selection of
 * DAC 19 Click driver.
 */
#define DAC19_DEVICE_ADDRESS_GND                        0x48
#define DAC19_DEVICE_ADDRESS_VCC                        0x49
#define DAC19_DEVICE_ADDRESS_SDA                        0x4A
#define DAC19_DEVICE_ADDRESS_SCL                        0x4B
#define DAC19_DEVICE_ADDRESS_BROADCAST                  0x47

/*! @} */ // dac19_set

/**
 * @defgroup dac19_map DAC 19 MikroBUS Map
 * @brief MikroBUS pin mapping of DAC 19 Click driver.
 */

/**
 * @addtogroup dac19_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DAC 19 Click to the selected MikroBUS.
 */
#define DAC19_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.gpi = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // dac19_map
/*! @} */ // dac19

/**
 * @brief DAC 19 Click context object.
 * @details Context object definition of DAC 19 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t gpi;          /**< General-purpose input. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} dac19_t;

/**
 * @brief DAC 19 Click configuration object.
 * @details Configuration object definition of DAC 19 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t gpi;             /**< General-purpose input. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} dac19_cfg_t;

/**
 * @brief DAC 19 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DAC19_OK = 0,
    DAC19_ERROR = -1

} dac19_return_value_t;

/*!
 * @addtogroup dac19 DAC 19 Click Driver
 * @brief API for configuring and manipulating DAC 19 Click driver.
 * @{
 */

/**
 * @brief DAC 19 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dac19_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dac19_cfg_setup ( dac19_cfg_t *cfg );

/**
 * @brief DAC 19 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dac19_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac19_init ( dac19_t *ctx, dac19_cfg_t *cfg );

/**
 * @brief DAC 19 default configuration function.
 * @details This function executes a default configuration of DAC 19
 * Click board.
 * @param[in] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dac19_default_cfg ( dac19_t *ctx );

/**
 * @brief DAC 19 reg write function.
 * @details This function writes a two bytes of data to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac19_reg_write ( dac19_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief DAC 19 reg read function.
 * @details This function reads two bytes of data from the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_in : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac19_reg_read ( dac19_t *ctx, uint8_t reg, uint16_t *data_in );

/**
 * @brief DAC 19 set gpi pin function.
 * @details This function sets the GPI pin logic state.
 * @param[in] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dac19_set_gpi_pin ( dac19_t *ctx, uint8_t state );

/**
 * @brief DAC 19 set value function.
 * @details This function sets the DAC DATA register to a desired value.
 * @param[in] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @param[in] data_in : 10-bit DAC data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac19_set_value ( dac19_t *ctx, uint16_t data_in );

/**
 * @brief DAC 19 set voltage function.
 * @details This function sets the output voltage depending on the vref value defined by
 * the VCC SEL on-board jumper. VREF and Voltage values can be either in Volts or Milivolts.
 * @param[in] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @param[in] vref_mv : VREF value in millivolts defined by VCC SEL on-board jumper.
 * @param[in] voltage_mv : Value in millivolts to be set as output voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac19_set_voltage ( dac19_t *ctx, uint16_t vref_mv, uint16_t voltage_mv );

/**
 * @brief DAC 19 set voltage with internal reference function.
 * @details This function sets the output voltage with the internal reference enabled. 
 * @param[in] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @param[in] voltage_mv : Value in millivolts to be set as output voltage.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac19_set_voltage_int_vref ( dac19_t *ctx, uint16_t voltage_mv );

/**
 * @brief DAC 19 set margin high function.
 * @details This function sets the DAC MARGIH HIGH register to a desired value.
 * @param[in] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @param[in] data_in : 10-bit data input.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac19_set_margin_high ( dac19_t *ctx, uint16_t data_in );

/**
 * @brief DAC 19 set margin low function.
 * @details This function sets the DAC MARGIH LOW register to a desired value.
 * @param[in] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @param[in] data_in : 10-bit data input.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac19_set_margin_low ( dac19_t *ctx, uint16_t data_in );

/**
 * @brief DAC 19 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac19_check_communication ( dac19_t *ctx );

/**
 * @brief DAC 19 enable output function.
 * @details This function enables the DAC output.
 * @param[in] ctx : Click context object.
 * See #dac19_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dac19_enable_output ( dac19_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DAC19_H

/*! @} */ // dac19

// ------------------------------------------------------------------------ END
