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
 * @file usbcpower3.h
 * @brief This file contains API for USB-C Power 3 Click Driver.
 */

#ifndef USBCPOWER3_H
#define USBCPOWER3_H

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
 * @addtogroup usbcpower3 USB-C Power 3 Click Driver
 * @brief API for configuring and manipulating USB-C Power 3 Click driver.
 * @{
 */

/**
 * @defgroup usbcpower3_reg USB-C Power 3 Registers List
 * @brief List of registers of USB-C Power 3 Click driver.
 */

/**
 * @addtogroup usbcpower3_reg
 * @{
 */

/**
 * @brief USB-C Power 3 PTN USB PD register list.
 * @details Specified register for PTN USB PD register list of USB-C Power 3 Click driver.
 */
#define USBCPOWER3_PTN_REG_VENDOR_ID                    0x00
#define USBCPOWER3_PTN_REG_PRODUCT_ID                   0x02
#define USBCPOWER3_PTN_REG_DEVICE_ID                    0x04
#define USBCPOWER3_PTN_REG_USBTYPEC_REV                 0x06
#define USBCPOWER3_PTN_REG_USBPD_REV_VER                0x08
#define USBCPOWER3_PTN_REG_PD_INTERFACE_REV             0x0A
#define USBCPOWER3_PTN_REG_ALERT                        0x10
#define USBCPOWER3_PTN_REG_ALERT_MASK                   0x12
#define USBCPOWER3_PTN_REG_POWER_STATUS_MASK            0x14
#define USBCPOWER3_PTN_REG_FAULT_STATUS_MASK            0x15
#define USBCPOWER3_PTN_REG_EXTENDED_STATUS_MASK         0x16
#define USBCPOWER3_PTN_REG_ALERT_EXTENDED_MASK          0x17
#define USBCPOWER3_PTN_REG_CONFIGURE_STANDARD_OUTPUT    0x18
#define USBCPOWER3_PTN_REG_TCPC_CONTROL                 0x19
#define USBCPOWER3_PTN_REG_ROLE_CONTROL                 0x1A
#define USBCPOWER3_PTN_REG_FAULT_CONTROL                0x1B
#define USBCPOWER3_PTN_REG_POWER_CONTROL                0x1C
#define USBCPOWER3_PTN_REG_CC_STATUS                    0x1D
#define USBCPOWER3_PTN_REG_POWER_STATUS                 0x1E
#define USBCPOWER3_PTN_REG_FAULT_STATUS                 0x1F
#define USBCPOWER3_PTN_REG_EXTENDED_STATUS              0x20
#define USBCPOWER3_PTN_REG_ALERT_EXTENDED               0x21
#define USBCPOWER3_PTN_REG_COMMAND                      0x23
#define USBCPOWER3_PTN_REG_DEVICE_CAPABILITIES_1        0x24
#define USBCPOWER3_PTN_REG_DEVICE_CAPABILITIES_2        0x26
#define USBCPOWER3_PTN_REG_STANDARD_INPUT_CAPABILITIES  0x28
#define USBCPOWER3_PTN_REG_STANDARD_OUTPUT_CAPABILITIES 0x29
#define USBCPOWER3_PTN_REG_CONFIGURE_EXTENDED1          0x2A
#define USBCPOWER3_PTN_REG_GENERIC_TIMER                0x2C
#define USBCPOWER3_PTN_REG_MESSAGE_HEADER_INFO          0x2E
#define USBCPOWER3_PTN_REG_RECEIVE_DETECT               0x2F
#define USBCPOWER3_PTN_REG_READABLE_BYTE_COUNT          0x30
#define USBCPOWER3_PTN_REG_TRANSMIT                     0x50
#define USBCPOWER3_PTN_REG_I2C_WRITE_BYTE_COUNT         0x51
#define USBCPOWER3_PTN_REG_VBUS_VOLTAGE                 0x70
#define USBCPOWER3_PTN_REG_VBUS_SINK_DISCONNECT_THLD    0x72
#define USBCPOWER3_PTN_REG_VBUS_STOP_DISCHARGE_THLD     0x74
#define USBCPOWER3_PTN_REG_VBUS_VOLTAGE_ALARM_HI_CFG    0x76
#define USBCPOWER3_PTN_REG_VBUS_VOLTAGE_ALARM_LO_CFG    0x78
#define USBCPOWER3_PTN_REG_VBUS_HV_TARGET               0x7A
#define USBCPOWER3_PTN_REG_EXT_CFG_ID                   0x80
#define USBCPOWER3_PTN_REG_EXT_ALERT                    0x82
#define USBCPOWER3_PTN_REG_EXT_ALERT_MASK               0x84
#define USBCPOWER3_PTN_REG_EXT_CONFIG                   0x86
#define USBCPOWER3_PTN_REG_EXT_FAULT_CONFIG             0x88
#define USBCPOWER3_PTN_REG_EXT_CONTROL                  0x8E
#define USBCPOWER3_PTN_REG_EXT_STATUS                   0x90
#define USBCPOWER3_PTN_REG_EXT_GPIO_CONFIG              0x92
#define USBCPOWER3_PTN_REG_EXT_GPIO_CONTROL             0x93
#define USBCPOWER3_PTN_REG_EXT_GPIO_ALERT_CONFIG        0x94
#define USBCPOWER3_PTN_REG_EXT_GPIO_STATUS              0x96
#define USBCPOWER3_PTN_REG_SOURCE_HIGH_VOLTAGE_MB4B_T   0x97
#define USBCPOWER3_PTN_REG_ADC_FILTER_CONTROL_1         0x9A
#define USBCPOWER3_PTN_REG_ADC_FILTER_CONTROL_2         0x9B
#define USBCPOWER3_PTN_REG_VCONN_CONFIG                 0x9C
#define USBCPOWER3_PTN_REG_VCONN_FAULT_DEBOUNCE         0x9D
#define USBCPOWER3_PTN_REG_VCONN_FAULT_RECOVERY         0x9E
#define USBCPOWER3_PTN_REG_VCONN_FAULT_ATTEMPTS         0x9F

/**
 * @brief USB-C Power 3 ACT buck-boost converter register list.
 * @details Specified register for ACT buck-boost converter register list of USB-C Power 3 Click driver.
 */
#define USBCPOWER3_ACT_REG_MASTER_CONTROL_1             0x00
#define USBCPOWER3_ACT_REG_MASTER_CONTROL_2             0x01
#define USBCPOWER3_ACT_REG_GENERAL_STATUS               0x02
#define USBCPOWER3_ACT_REG_THERMAL_STATUS               0x03
#define USBCPOWER3_ACT_REG_FAULT_1                      0x05
#define USBCPOWER3_ACT_REG_FAULT_2                      0x06
#define USBCPOWER3_ACT_REG_ADC_OUTPUT_1                 0x07
#define USBCPOWER3_ACT_REG_ADC_OUTPUT_2                 0x08
#define USBCPOWER3_ACT_REG_ADC_CONFIG_1                 0x09
#define USBCPOWER3_ACT_REG_ADC_CONFIG_2                 0x0A
#define USBCPOWER3_ACT_REG_VREG_CONTROL                 0x0B
#define USBCPOWER3_ACT_REG_CONVERTER_CONTROL_1          0x0E
#define USBCPOWER3_ACT_REG_CONVERTER_CONTROL_2          0x0F
#define USBCPOWER3_ACT_REG_CONVERTER_CONTROL_3          0x10
#define USBCPOWER3_ACT_REG_VREG_VOLTAGE                 0x11
#define USBCPOWER3_ACT_REG_OUTPUT_VOLTAGE_1             0x13
#define USBCPOWER3_ACT_REG_OUTPUT_VOLTAGE_2             0x14
#define USBCPOWER3_ACT_REG_OUTPUT_CURRENT_LIMIT         0x17
#define USBCPOWER3_ACT_REG_VIN_UV                       0x1A
#define USBCPOWER3_ACT_REG_FREQUENCY                    0x1D
#define USBCPOWER3_ACT_REG_IRQ_CONTROL_1                0x1E
#define USBCPOWER3_ACT_REG_IRQ_CONTROL_2                0x1F
#define USBCPOWER3_ACT_REG_VOUT_STATUS                  0x20

/*! @} */ // usbcpower3_reg

/**
 * @defgroup usbcpower3_set USB-C Power 3 Registers Settings
 * @brief Settings for registers of USB-C Power 3 Click driver.
 */

/**
 * @addtogroup usbcpower3_set
 * @{
 */

/**
 * @brief USB-C Power 3 PTN USB PD VENDOR_ID and PRODUCT_ID registers setting.
 * @details Specified setting for PTN USB PD VENDOR_ID and PRODUCT_ID registers of USB-C Power 3 Click driver.
 */
#define USBCPOWER3_PTN_VENDOR_ID                        0x1FC9
#define USBCPOWER3_PTN_PRODUCT_ID                       0x5110

/**
 * @brief USB-C Power 3 PTN USB PD POWER_CONTROL register setting.
 * @details Specified setting for PTN USB PD POWER_CONTROL register of USB-C Power 3 Click driver.
 */
#define USBCPOWER3_PTN_POWER_CONTROL_FRS_DIS            0x00
#define USBCPOWER3_PTN_POWER_CONTROL_FRS_EN             0x80
#define USBCPOWER3_PTN_POWER_CONTROL_FRS_MASK           0x80
#define USBCPOWER3_PTN_POWER_CONTROL_VBUS_V_MON_EN      0x00
#define USBCPOWER3_PTN_POWER_CONTROL_VBUS_V_MON_DIS     0x40
#define USBCPOWER3_PTN_POWER_CONTROL_VBUS_V_MON_MASK    0x40
#define USBCPOWER3_PTN_POWER_CONTROL_DIS_V_ALARM_EN     0x00
#define USBCPOWER3_PTN_POWER_CONTROL_DIS_V_ALARM_DIS    0x20
#define USBCPOWER3_PTN_POWER_CONTROL_DIS_V_ALARM_MASK   0x20
#define USBCPOWER3_PTN_POWER_CONTROL_AUTO_DISCH_DIS     0x00
#define USBCPOWER3_PTN_POWER_CONTROL_AUTO_DISCH_EN      0x10
#define USBCPOWER3_PTN_POWER_CONTROL_AUTO_DISCH_MASK    0x10
#define USBCPOWER3_PTN_POWER_CONTROL_BLEED_DISCH_DIS    0x00
#define USBCPOWER3_PTN_POWER_CONTROL_BLEED_DISCH_EN     0x08
#define USBCPOWER3_PTN_POWER_CONTROL_BLEED_DISCH_MASK   0x08
#define USBCPOWER3_PTN_POWER_CONTROL_FORCE_DISCH_DIS    0x00
#define USBCPOWER3_PTN_POWER_CONTROL_FORCE_DISCH_EN     0x04
#define USBCPOWER3_PTN_POWER_CONTROL_FORCE_DISCH_MASK   0x04
#define USBCPOWER3_PTN_POWER_CONTROL_VCONN_1W           0x00
#define USBCPOWER3_PTN_POWER_CONTROL_VCONN_DEV_CAP      0x02
#define USBCPOWER3_PTN_POWER_CONTROL_VCONN_MASK         0x02
#define USBCPOWER3_PTN_POWER_CONTROL_VCONN_SRC_DIS      0x00
#define USBCPOWER3_PTN_POWER_CONTROL_VCONN_SRC_EN       0x01
#define USBCPOWER3_PTN_POWER_CONTROL_VCONN_SRC_MASK     0x01

/**
 * @brief USB-C Power 3 PTN USB PD CC_STATUS register setting.
 * @details Specified setting for PTN USB PD CC_STATUS register of USB-C Power 3 Click driver.
 */
#define USBCPOWER3_PTN_CC_STATUS_LOOKING_4_CONNECTION   0x20
#define USBCPOWER3_PTN_CC_STATUS_CONNECT_RESULT_SRC     0x00
#define USBCPOWER3_PTN_CC_STATUS_CONNECT_RESULT_SINK    0x10
#define USBCPOWER3_PTN_CC_STATUS_CONNECT_RESULT_MASK    0x10
#define USBCPOWER3_PTN_CC_STATUS_CC2_OPEN               0x00
#define USBCPOWER3_PTN_CC_STATUS_CC2_SRC_RA             0x04
#define USBCPOWER3_PTN_CC_STATUS_CC2_SRC_RD             0x08
#define USBCPOWER3_PTN_CC_STATUS_CC2_SINK_DEFAULT       0x04
#define USBCPOWER3_PTN_CC_STATUS_CC2_SINK_POWER_1_5     0x08
#define USBCPOWER3_PTN_CC_STATUS_CC2_SINK_POWER_3_0     0x0C
#define USBCPOWER3_PTN_CC_STATUS_CC2_MASK               0x0C
#define USBCPOWER3_PTN_CC_STATUS_CC1_OPEN               0x00
#define USBCPOWER3_PTN_CC_STATUS_CC1_SRC_RA             0x01
#define USBCPOWER3_PTN_CC_STATUS_CC1_SRC_RD             0x02
#define USBCPOWER3_PTN_CC_STATUS_CC1_SINK_DEFAULT       0x01
#define USBCPOWER3_PTN_CC_STATUS_CC1_SINK_POWER_1_5     0x02
#define USBCPOWER3_PTN_CC_STATUS_CC1_SINK_POWER_3_0     0x03
#define USBCPOWER3_PTN_CC_STATUS_CC1_MASK               0x03

/**
 * @brief USB-C Power 3 PTN USB PD POWER_STATUS register setting.
 * @details Specified setting for PTN USB PD POWER_STATUS register of USB-C Power 3 Click driver.
 */
#define USBCPOWER3_PTN_POWER_STATUS_DEBUG_CONNECTED     0x80
#define USBCPOWER3_PTN_POWER_STATUS_TCPC_INIT           0x40
#define USBCPOWER3_PTN_POWER_STATUS_SRC_HIGH_V          0x20
#define USBCPOWER3_PTN_POWER_STATUS_SRC_VBUS_EN         0x10
#define USBCPOWER3_PTN_POWER_STATUS_VBUS_DET_EN         0x08
#define USBCPOWER3_PTN_POWER_STATUS_VBUS_PRESENT        0x04
#define USBCPOWER3_PTN_POWER_STATUS_VCONN_PRESENT       0x02
#define USBCPOWER3_PTN_POWER_STATUS_SINKING_VBUS        0x01

/**
 * @brief USB-C Power 3 PTN USB PD COMMAND register setting.
 * @details Specified setting for PTN USB PD COMMAND register of USB-C Power 3 Click driver.
 */
#define USBCPOWER3_PTN_COMMAND_WAKE_I2C                 0x11
#define USBCPOWER3_PTN_COMMAND_DIS_VBUS_DETECT          0x22
#define USBCPOWER3_PTN_COMMAND_EN_VBUS_DETECT           0x33
#define USBCPOWER3_PTN_COMMAND_DIS_SINK_VBUS            0x44
#define USBCPOWER3_PTN_COMMAND_EN_SINK_VBUS             0x55
#define USBCPOWER3_PTN_COMMAND_DIS_SRC_VBUS             0x66
#define USBCPOWER3_PTN_COMMAND_SRC_VBUS_DEF_V           0x77
#define USBCPOWER3_PTN_COMMAND_SRC_VBUS_HIGH_V          0x88
#define USBCPOWER3_PTN_COMMAND_LOOK_4_CONNECTION        0x99
#define USBCPOWER3_PTN_COMMAND_RX_ONE_MORE              0xAA
#define USBCPOWER3_PTN_COMMAND_SEND_FRS_SIGNAL          0xCC
#define USBCPOWER3_PTN_COMMAND_RESET_TRANSMIT_BUFFER    0xDD
#define USBCPOWER3_PTN_COMMAND_RESET_RECEIVE_BUFFER     0xEE
#define USBCPOWER3_PTN_COMMAND_I2C_IDLE                 0xFF

/**
 * @brief USB-C Power 3 PTN USB PD timeout setting.
 * @details Specified setting for PTN USB PD timeout of USB-C Power 3 Click driver.
 */
#define USBCPOWER3_PTN_TIMEOUT_MS                       5000

/**
 * @brief USB-C Power 3 device address setting.
 * @details Specified setting for device slave address selection of
 * USB-C Power 3 Click driver.
 */
#define USBCPOWER3_DEVICE_ADDRESS_PTN_GND               0x50
#define USBCPOWER3_DEVICE_ADDRESS_PTN_10K_BYPASS        0x51
#define USBCPOWER3_DEVICE_ADDRESS_PTN_UNCONNECTED       0x52
#define USBCPOWER3_DEVICE_ADDRESS_PTN_100K_BYPASS       0x53
#define USBCPOWER3_DEVICE_ADDRESS_PTN                   USBCPOWER3_DEVICE_ADDRESS_PTN_GND
#define USBCPOWER3_DEVICE_ADDRESS_ACT                   0x24

/*! @} */ // usbcpower3_set

/**
 * @defgroup usbcpower3_map USB-C Power 3 MikroBUS Map
 * @brief MikroBUS pin mapping of USB-C Power 3 Click driver.
 */

/**
 * @addtogroup usbcpower3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB-C Power 3 Click to the selected MikroBUS.
 */
#define USBCPOWER3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.fen = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.lim = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // usbcpower3_map
/*! @} */ // usbcpower3

/**
 * @brief USB-C Power 3 Click PTN info object.
 * @details PTN info object definition of USB-C Power 3 Click driver.
 */
typedef struct
{
    uint16_t vendor_id;         /**< Vendor ID word. */
    uint16_t product_id;        /**< Product ID word. */
    uint16_t device_id;         /**< Device ID word. */
    uint16_t usbtypec_rev;      /**< USB Type-C Revision. */
    uint16_t usbpd_rev_ver;     /**< USB-PD Revision and Version. */
    uint16_t pd_interface_rev;  /**< USB-PD Inter-Block Specification Revision and Version. */

} usbcpower3_ptn_info_t;

/**
 * @brief USB-C Power 3 Click context object.
 * @details Context object definition of USB-C Power 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Device enable pin (active high). */
    digital_out_t lim;          /**< Current limit selection pin 0.9A to 1.5A/3A. */

    // Input pins
    digital_in_t fen;           /**< FRS enable control pin status. */
    digital_in_t int_pin;       /**< Alert or Buck-boost converter interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    usbcpower3_ptn_info_t info; /**< PTN device info. */

} usbcpower3_t;

/**
 * @brief USB-C Power 3 Click configuration object.
 * @details Configuration object definition of USB-C Power 3 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t fen;             /**< FRS enable control pin status. */
    pin_name_t en;              /**< Device enable pin (active high). */
    pin_name_t lim;             /**< Current limit selection pin 0.9A to 1.5A/3A. */
    pin_name_t int_pin;         /**< Alert or Buck-boost converter interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} usbcpower3_cfg_t;

/**
 * @brief USB-C Power 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBCPOWER3_OK = 0,
    USBCPOWER3_ERROR = -1

} usbcpower3_return_value_t;

/*!
 * @addtogroup usbcpower3 USB-C Power 3 Click Driver
 * @brief API for configuring and manipulating USB-C Power 3 Click driver.
 * @{
 */

/**
 * @brief USB-C Power 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbcpower3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbcpower3_cfg_setup ( usbcpower3_cfg_t *cfg );

/**
 * @brief USB-C Power 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbcpower3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower3_init ( usbcpower3_t *ctx, usbcpower3_cfg_t *cfg );

/**
 * @brief USB-C Power 3 PTN write register byte function.
 * @details This function writes one byte to the selected PTN USB PD register using the block write function.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower3_ptn_write_reg_byte ( usbcpower3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief USB-C Power 3 PTN read register byte function.
 * @details This function reads one byte from the selected PTN USB PD register using the block read function.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location where the read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower3_ptn_read_reg_byte ( usbcpower3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief USB-C Power 3 PTN write register word function.
 * @details This function writes a 16-bit word to the selected PTN USB PD register in little-endian format.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data word to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower3_ptn_write_reg_word ( usbcpower3_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief USB-C Power 3 PTN read register word function.
 * @details This function reads a 16-bit word from the selected PTN USB PD register in little-endian format.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location where the read data word will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The output pointer is updated only if it is not @c NULL and the read is successful.
 */
err_t usbcpower3_ptn_read_reg_word ( usbcpower3_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief USB-C Power 3 PTN write register block function.
 * @details This function writes multiple bytes to the selected PTN USB PD register over I2C.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Pointer to the data buffer to write.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower3_ptn_write_reg_block ( usbcpower3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief USB-C Power 3 PTN read register block function.
 * @details This function reads multiple bytes from the selected PTN USB PD register over I2C.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location where the read data will be stored.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower3_ptn_read_reg_block ( usbcpower3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief USB-C Power 3 ACT write register function.
 * @details This function writes one byte to the selected ACT buck-boost converter register over I2C.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower3_act_write_reg ( usbcpower3_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief USB-C Power 3 ACT read register function.
 * @details This function reads one byte from the selected ACT buck-boost converter register over I2C.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location where the read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcpower3_act_read_reg ( usbcpower3_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief USB-C Power 3 PTN read device information function.
 * @details This function reads device identification and revision information from PTN USB PD registers.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Returns error if device ID values do not match expected values.
 */
err_t usbcpower3_ptn_read_info ( usbcpower3_t *ctx );

/**
 * @brief USB-C Power 3 device enable function.
 * @details This function enables the device by setting the enable pin.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void usbcpower3_enable_device ( usbcpower3_t *ctx );

/**
 * @brief USB-C Power 3 device disable function.
 * @details This function disables the device by clearing the enable pin.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void usbcpower3_disable_device ( usbcpower3_t *ctx );

/**
 * @brief USB-C Power 3 device restart function.
 * @details This function restarts the device by disabling and re-enabling it.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void usbcpower3_restart_device ( usbcpower3_t *ctx );

/**
 * @brief USB-C Power 3 wait TCPC init function.
 * @details This function waits for TCPC initialization to complete.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Returns error if initialization times out.
 */
err_t usbcpower3_wait_tcpc_init ( usbcpower3_t *ctx );

/**
 * @brief USB-C Power 3 set high current function.
 * @details This function sets the current limit pin to a high logic level.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void usbcpower3_set_high_current ( usbcpower3_t *ctx );

/**
 * @brief USB-C Power 3 set low current function.
 * @details This function sets the current limit pin to a low logic level.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void usbcpower3_set_low_current ( usbcpower3_t *ctx );

/**
 * @brief USB-C Power 3 get interrupt pin function.
 * @details This function reads the interrupt pin state.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t usbcpower3_get_int_pin ( usbcpower3_t *ctx );

/**
 * @brief USB-C Power 3 get FEN pin function.
 * @details This function reads the FEN pin state.
 * @param[in] ctx : Click context object.
 * See #usbcpower3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t usbcpower3_get_fen_pin ( usbcpower3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // USBCPOWER3_H

/*! @} */ // usbcpower3

// ------------------------------------------------------------------------ END
