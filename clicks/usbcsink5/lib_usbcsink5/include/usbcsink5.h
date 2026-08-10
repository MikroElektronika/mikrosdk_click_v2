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
 * @file usbcsink5.h
 * @brief This file contains API for USB-C Sink 5 Click Driver.
 */

#ifndef USBCSINK5_H
#define USBCSINK5_H

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
 * @addtogroup usbcsink5 USB-C Sink 5 Click Driver
 * @brief API for configuring and manipulating USB-C Sink 5 Click driver.
 * @{
 */

/**
 * @defgroup usbcsink5_reg USB-C Sink 5 Registers List
 * @brief List of registers of USB-C Sink 5 Click driver.
 */

/**
 * @addtogroup usbcsink5_reg
 * @{
 */

/**
 * @brief USB-C Sink 5 register map.
 * @details Specified register map of USB-C Sink 5 Click driver.
 */
#define USBCSINK5_REG_VID_LOW                           0x00
#define USBCSINK5_REG_VID_HIGH                          0x01
#define USBCSINK5_REG_PID_LOW                           0x02
#define USBCSINK5_REG_PID_HIGH                          0x03
#define USBCSINK5_REG_XID_0                             0x04
#define USBCSINK5_REG_XID_1                             0x05
#define USBCSINK5_REG_XID_2                             0x06
#define USBCSINK5_REG_XID_3                             0x07
#define USBCSINK5_REG_FW_REVISION                       0x08
#define USBCSINK5_REG_HW_REVISION                       0x09
#define USBCSINK5_REG_PD_REVISION                       0x0A
#define USBCSINK5_REG_PD_VERSION                        0x0B
#define USBCSINK5_REG_DEVICE_HW                         0x0C
#define USBCSINK5_REG_ALERT_STATUS                      0x10
#define USBCSINK5_REG_ALERT_STATUS_MASK                 0x11
#define USBCSINK5_REG_PD_STATUS_EVENT                   0x12
#define USBCSINK5_REG_PD_STATUS_EVENT_MASK              0x13
#define USBCSINK5_REG_MONITORING_TRANS                  0x14
#define USBCSINK5_REG_MONITORING_MASK                   0x15
#define USBCSINK5_REG_MONITORING_STATUS                 0x16
#define USBCSINK5_REG_PRL_TRANS                         0x17
#define USBCSINK5_REG_PRL_STATUS_MASK                   0x18
#define USBCSINK5_REG_VBUS_STATUS                       0x19
#define USBCSINK5_REG_CC_STATUS                         0x1A
#define USBCSINK5_REG_PD_STATUS                         0x1B
#define USBCSINK5_REG_HW_FAULT_TRANS                    0x1C
#define USBCSINK5_REG_HW_FAULT_STATUS                   0x1D
#define USBCSINK5_REG_GPIO_STATUS                       0x1E
#define USBCSINK5_REG_NVM_STATUS                        0x1F
#define USBCSINK5_REG_TYPEC_FSM                         0x20
#define USBCSINK5_REG_PE_FSM                            0x21
#define USBCSINK5_REG_VBUS_FSM                          0x22
#define USBCSINK5_REG_MONITORING_DACH_STATUS            0x23
#define USBCSINK5_REG_MONITORING_DACL_STATUS            0x25
#define USBCSINK5_REG_CONNECTION_TRANS                  0x27
#define USBCSINK5_REG_CONNECTION_MASK                   0x28
#define USBCSINK5_REG_COMMAND                           0x31
#define USBCSINK5_REG_RX_MSG_DETECT                     0x32
#define USBCSINK5_REG_RESET_CTRL                        0x33
#define USBCSINK5_REG_VBUS_CTRL                         0x34
#define USBCSINK5_REG_MONITORING_CTRL                   0x35
#define USBCSINK5_REG_MONITORING_DACH_CTRL              0x36
#define USBCSINK5_REG_MONITORING_DACL_CTRL              0x38
#define USBCSINK5_REG_MONITORING_SHIFT_CTRL             0x3A
#define USBCSINK5_REG_VBUS_DISCHARGE_CTRL               0x3B
#define USBCSINK5_REG_VBUS_DISCHARGE_TIME_CTRL          0x3C
#define USBCSINK5_REG_DEVICE_CTRL                       0x3D
#define USBCSINK5_REG_APPLI_CTRL                        0x3E
#define USBCSINK5_REG_DPM_CTRL                          0x3F
#define USBCSINK5_REG_GPIO_CTRL                         0x40
#define USBCSINK5_REG_NVM_CUST_CTRL                     0x41
#define USBCSINK5_REG_GPIO_SETTING                      0x50
#define USBCSINK5_REG_DEVICE_PDP                        0x51
#define USBCSINK5_REG_NUM_PDO                           0x52
#define USBCSINK5_REG_SNK_PDO_PARAMS                    0x53
#define USBCSINK5_REG_SNK_PDO_CAPABILITIES              0x54
#define USBCSINK5_REG_ALGO                              0x56
#define USBCSINK5_REG_SNK_APDO_FILL_1                   0x57
#define USBCSINK5_REG_SNK_APDO_FILL_2                   0x58
#define USBCSINK5_REG_SNK_APDO_FILL_3                   0x59
#define USBCSINK5_REG_DEVICE_SETTING                    0x5A
#define USBCSINK5_REG_REQUEST_SRC_PDP                   0x5C
#define USBCSINK5_REG_RX_BYTE_CNT                       0x60
#define USBCSINK5_REG_RX_FRAME_TYPE                     0x61
#define USBCSINK5_REG_RX_HEADER                         0x62
#define USBCSINK5_REG_RX_DATA_OBJ_224BITS               0x64
#define USBCSINK5_REG_PRT_TX_CTRL                       0x80
#define USBCSINK5_REG_TX_BYTE_CNT                       0x81
#define USBCSINK5_REG_TX_HEADER                         0x82
#define USBCSINK5_REG_TX_DATA_OBJ_224BITS               0x84
#define USBCSINK5_REG_DPM_SRC_PDO1                      0xA0
#define USBCSINK5_REG_DPM_SRC_PDO2                      0xA4
#define USBCSINK5_REG_DPM_SRC_PDO3                      0xA8
#define USBCSINK5_REG_DPM_SRC_PDO4                      0xAC
#define USBCSINK5_REG_DPM_SRC_PDO5                      0xB0
#define USBCSINK5_REG_DPM_SRC_PDO6                      0xB4
#define USBCSINK5_REG_DPM_SRC_PDO7                      0xB8
#define USBCSINK5_REG_DPM_RDO                           0xBC
#define USBCSINK5_REG_DPM_ALGO_RESULT                   0xC0
#define USBCSINK5_REG_DPM_SRC_PDO_NEGOTIATED            0xC4

/*! @} */ // usbcsink5_reg

/**
 * @defgroup usbcsink5_set USB-C Sink 5 Registers Settings
 * @brief Settings for registers of USB-C Sink 5 Click driver.
 */

/**
 * @addtogroup usbcsink5_set
 * @{
 */

/**
 * @brief USB-C Sink 5 VENDOR_ID and PRODUCT_ID registers setting.
 * @details Specified setting for VENDOR_ID and PRODUCT_ID registers of USB-C Sink 5 Click driver.
 */
#define USBCSINK5_VENDOR_ID                             0x0483
#define USBCSINK5_PRODUCT_ID                            0x4531

/**
 * @brief USB-C Sink 5 VBUS_STATUS register setting.
 * @details Specified setting for VBUS_STATUS register of USB-C Sink 5 Click driver.
 */
#define USBCSINK5_VBUS_STATUS_SWITCH_CLOSED             0x02

/**
 * @brief USB-C Sink 5 CC_STATUS register setting.
 * @details Specified setting for CC_STATUS register of USB-C Sink 5 Click driver.
 */
#define USBCSINK5_CC_STATUS_PLUG_ORIENTATION_REVERSED   0x80
#define USBCSINK5_CC_STATUS_DEVICE_ATTACHED             0x40
#define USBCSINK5_CC_STATUS_LOOKING_4_CONNECTION        0x20
#define USBCSINK5_CC_STATUS_CONNECT_RESULT_SINK         0x10
#define USBCSINK5_CC_STATUS_CC2_OPEN                    0x00
#define USBCSINK5_CC_STATUS_CC2_SINK_DEFAULT            0x04
#define USBCSINK5_CC_STATUS_CC2_SINK_POWER_1_5          0x08
#define USBCSINK5_CC_STATUS_CC2_SINK_POWER_3_0          0x0C
#define USBCSINK5_CC_STATUS_CC2_MASK                    0x0C
#define USBCSINK5_CC_STATUS_CC1_OPEN                    0x00
#define USBCSINK5_CC_STATUS_CC1_SINK_DEFAULT            0x01
#define USBCSINK5_CC_STATUS_CC1_SINK_POWER_1_5          0x02
#define USBCSINK5_CC_STATUS_CC1_SINK_POWER_3_0          0x03
#define USBCSINK5_CC_STATUS_CC1_MASK                    0x03

/**
 * @brief USB-C Sink 5 device address setting.
 * @details Specified setting for device slave address selection of
 * USB-C Sink 5 Click driver.
 */
#define USBCSINK5_DEVICE_ADDRESS_0                      0x28
#define USBCSINK5_DEVICE_ADDRESS_1                      0x29

/*! @} */ // usbcsink5_set

/**
 * @defgroup usbcsink5_map USB-C Sink 5 MikroBUS Map
 * @brief MikroBUS pin mapping of USB-C Sink 5 Click driver.
 */

/**
 * @addtogroup usbcsink5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB-C Sink 5 Click to the selected MikroBUS.
 */
#define USBCSINK5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // usbcsink5_map
/*! @} */ // usbcsink5

/**
 * @brief USB-C Sink 5 Click PTN info object.
 * @details PTN info object definition of USB-C Sink 5 Click driver.
 */
typedef struct
{
    uint16_t vendor_id;         /**< Vendor ID (16 bits). */
    uint16_t product_id;        /**< Product ID (16 bits). */
    uint32_t usb_xid;           /**< USB-IF XID (32 bits). */
    uint8_t fw_ver;             /**< Firmware version (8 bits). */
    uint8_t hw_ver;             /**< Hardware version (8 bits). */
    uint8_t pd_rev;             /**< Power delivery revision (8 bits). */
    uint8_t pd_ver;             /**< Power delivery version (8 bits). */

} usbcsink5_info_t;

/**
 * @brief USB-C Sink 5 Click context object.
 * @details Context object definition of USB-C Sink 5 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alert;         /**< Alert pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    usbcsink5_info_t info;      /**< Device info. */

} usbcsink5_t;

/**
 * @brief USB-C Sink 5 Click configuration object.
 * @details Configuration object definition of USB-C Sink 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t alert;           /**< Alert pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} usbcsink5_cfg_t;

/**
 * @brief USB-C Sink 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    USBCSINK5_OK = 0,
    USBCSINK5_ERROR = -1

} usbcsink5_return_value_t;

/*!
 * @addtogroup usbcsink5 USB-C Sink 5 Click Driver
 * @brief API for configuring and manipulating USB-C Sink 5 Click driver.
 * @{
 */

/**
 * @brief USB-C Sink 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbcsink5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbcsink5_cfg_setup ( usbcsink5_cfg_t *cfg );

/**
 * @brief USB-C Sink 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #usbcsink5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbcsink5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink5_init ( usbcsink5_t *ctx, usbcsink5_cfg_t *cfg );

/**
 * @brief USB-C Sink 5 write register byte function.
 * @details This function writes one byte to the selected register using the block write function.
 * @param[in] ctx : Click context object.
 * See #usbcsink5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink5_write_reg_byte ( usbcsink5_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief USB-C Sink 5 read register byte function.
 * @details This function reads one byte from the selected register using the block read function.
 * @param[in] ctx : Click context object.
 * See #usbcsink5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location where the read data will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink5_read_reg_byte ( usbcsink5_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief USB-C Sink 5 write register word function.
 * @details This function writes a 16-bit word to the selected register in little-endian format.
 * @param[in] ctx : Click context object.
 * See #usbcsink5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 16-bit data word to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink5_write_reg_word ( usbcsink5_t *ctx, uint8_t reg, uint16_t data_in );

/**
 * @brief USB-C Sink 5 read register word function.
 * @details This function reads a 16-bit word from the selected register in little-endian format.
 * @param[in] ctx : Click context object.
 * See #usbcsink5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location where the read data word will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The output pointer is updated only if it is not @c NULL and the read is successful.
 */
err_t usbcsink5_read_reg_word ( usbcsink5_t *ctx, uint8_t reg, uint16_t *data_out );

/**
 * @brief USB-C Sink 5 write register dword function.
 * @details This function writes a 32-bit double word to the selected register in little-endian format.
 * @param[in] ctx : Click context object.
 * See #usbcsink5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : 32-bit data double word to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink5_write_reg_dword ( usbcsink5_t *ctx, uint8_t reg, uint32_t data_in );

/**
 * @brief USB-C Sink 5 read register dword function.
 * @details This function reads a 32-bit double word from the selected register in little-endian format.
 * @param[in] ctx : Click context object.
 * See #usbcsink5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location where the read data double word will be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The output pointer is updated only if it is not @c NULL and the read is successful.
 */
err_t usbcsink5_read_reg_dword ( usbcsink5_t *ctx, uint8_t reg, uint32_t *data_out );

/**
 * @brief USB-C Sink 5 write register block function.
 * @details This function writes multiple bytes to the selected register over I2C.
 * @param[in] ctx : Click context object.
 * See #usbcsink5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Pointer to the data buffer to write.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink5_write_reg_block ( usbcsink5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief USB-C Sink 5 read register block function.
 * @details This function reads multiple bytes from the selected register over I2C.
 * @param[in] ctx : Click context object.
 * See #usbcsink5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory location where the read data will be stored.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbcsink5_read_reg_block ( usbcsink5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief USB-C Sink 5 get alert pin function.
 * @details This function reads the alert pin state.
 * @param[in] ctx : Click context object.
 * See #usbcsink5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t usbcsink5_get_alert_pin ( usbcsink5_t *ctx );

/**
 * @brief USB-C Sink 5 read device information function.
 * @details This function reads device identification and revision information from the registers.
 * @param[in] ctx : Click context object.
 * See #usbcsink5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Returns error if device ID values do not match expected values.
 */
err_t usbcsink5_read_info ( usbcsink5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // USBCSINK5_H

/*! @} */ // usbcsink5

// ------------------------------------------------------------------------ END
