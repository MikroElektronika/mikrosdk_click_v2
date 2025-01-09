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
 * @file nfc7i2c.h
 * @brief This file contains API for NFC 7 I2C Click Driver.
 */

#ifndef NFC7I2C_H
#define NFC7I2C_H

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
 * @addtogroup nfc7i2c NFC 7 I2C Click Driver
 * @brief API for configuring and manipulating NFC 7 I2C Click driver.
 * @{
 */

/**
 * @defgroup nfc7i2c_reg NFC 7 I2C Registers List
 * @brief List of registers of NFC 7 I2C Click driver.
 */

/**
 * @addtogroup nfc7i2c_reg
 * @{
 */

/**
 * @brief NFC 7 I2C NCI packet format.
 * @details Specified register for NCI packet format of NFC 7 I2C Click driver.
 */
#define NFC7I2C_NCI_PKT_MT_DATA                 0x00
#define NFC7I2C_NCI_PKT_MT_CTRL_CMD             0x01
#define NFC7I2C_NCI_PKT_MT_CTRL_RSP             0x02
#define NFC7I2C_NCI_PKT_MT_CTRL_NTF             0x03
#define NFC7I2C_NCI_PKT_MT_SHIFT                5
#define NFC7I2C_NCI_PKT_MT_MASK                 0xE0
#define NFC7I2C_NCI_PKT_PBF_COMPLETE            0x00
#define NFC7I2C_NCI_PKT_PBF_NOT_COMPLETE        0x01
#define NFC7I2C_NCI_PKT_PBF_SHIFT               4
#define NFC7I2C_NCI_PKT_PBF_MASK                0x10
#define NFC7I2C_NCI_PKT_CTRL_GID_MASK           0x0F
#define NFC7I2C_NCI_PKT_CTRL_OID_MASK           0x3F
#define NFC7I2C_NCI_PKT_DATA_CID_MASK           0x0F
#define NFC7I2C_NCI_PKT_DATA_RFU                0x00

/**
 * @brief NFC 7 I2C NCI GID values.
 * @details Specified register for NCI GID values of NFC 7 I2C Click driver.
 */
#define NFC7I2C_NCI_GID_CORE                    0x00
#define NFC7I2C_NCI_GID_RF_MGMT                 0x01
#define NFC7I2C_NCI_GID_PROP                    0x0F

/**
 * @brief NFC 7 I2C NCI OID values.
 * @details Specified register for NCI OID values of NFC 7 I2C Click driver.
 */
#define NFC7I2C_NCI_OID_CORE_RESET              0x00
#define NFC7I2C_NCI_OID_CORE_INIT               0x01
#define NFC7I2C_NCI_OID_CORE_SET_CONFIG         0x02
#define NFC7I2C_NCI_OID_CORE_GET_CONFIG         0x03
#define NFC7I2C_NCI_OID_CORE_CONN_CREATE        0x04
#define NFC7I2C_NCI_OID_CORE_CONN_CLOSE         0x05
#define NFC7I2C_NCI_OID_CORE_CONN_CREDITS       0x06
#define NFC7I2C_NCI_OID_CORE_GEN_ERR_STAT       0x07
#define NFC7I2C_NCI_OID_CORE_INTF_ERR_STAT      0x08
#define NFC7I2C_NCI_OID_RF_DISCOVER_MAP         0x00
#define NFC7I2C_NCI_OID_RF_SET_ROUTING          0x01
#define NFC7I2C_NCI_OID_RF_GET_ROUTING          0x02
#define NFC7I2C_NCI_OID_RF_DISCOVER             0x03
#define NFC7I2C_NCI_OID_RF_DISCOVER_SELECT      0x04
#define NFC7I2C_NCI_OID_RF_INTF_ACTIVATED       0x05
#define NFC7I2C_NCI_OID_RF_DEACTIVATE           0x06
#define NFC7I2C_NCI_OID_RF_FIELD                0x07
#define NFC7I2C_NCI_OID_RF_T3T_POLLING          0x08
#define NFC7I2C_NCI_OID_RF_EE_ACTION            0x09
#define NFC7I2C_NCI_OID_RF_EE_DISCOVERY_REQ     0x0A
#define NFC7I2C_NCI_OID_RF_PARAMETER_UPDATE     0x0B
#define NFC7I2C_NCI_OID_PROP_SET_PWR_MODE       0x00
#define NFC7I2C_NCI_OID_PROP_ACT                0x02
#define NFC7I2C_NCI_OID_PROP_RF_PRES_CHECK      0x11
#define NFC7I2C_NCI_OID_PROP_RF_LPCD_TRACE      0x13
#define NFC7I2C_NCI_OID_PROP_RF_GET_TRANSIT     0x14
#define NFC7I2C_NCI_OID_PROP_TEST_PRBS          0x30
#define NFC7I2C_NCI_OID_PROP_TEST_ANTENNA       0x3D

/*! @} */ // nfc7i2c_reg

/**
 * @defgroup nfc7i2c_set NFC 7 I2C Registers Settings
 * @brief Settings for registers of NFC 7 I2C Click driver.
 */

/**
 * @addtogroup nfc7i2c_set
 * @{
 */

/**
 * @brief NFC 7 I2C NCI parameter values.
 * @details Specified register for NCI parameter values of NFC 7 I2C Click driver.
 */
#define NFC7I2C_NCI_CORE_RESET_KEEP_CFG         0x00
#define NFC7I2C_NCI_CORE_RESET_RESET_CFG        0x01
#define NFC7I2C_NCI_CORE_RESET_NTF_NCI_VER_20   0x20
#define NFC7I2C_NCI_CORE_INIT_FEATURE_DIS       0x00
#define NFC7I2C_NCI_CORE_STANDBY_DISABLE        0x00
#define NFC7I2C_NCI_CORE_STANDBY_ENABLE         0x01
#define NFC7I2C_NCI_CORE_STANDBY_AUTO           0x02

/**
 * @brief NFC 7 I2C NCI status values.
 * @details Specified register for NCI status values of NFC 7 I2C Click driver.
 */
#define NFC7I2C_NCI_STAT_OK                     0x00
#define NFC7I2C_NCI_STAT_REJECTED               0x01
#define NFC7I2C_NCI_STAT_RF_FRAME_CORRUPTED     0x02
#define NFC7I2C_NCI_STAT_FAILED                 0x03
#define NFC7I2C_NCI_STAT_NOT_INITIALIZED        0x04
#define NFC7I2C_NCI_STAT_SYNTAX_ERROR           0x05
#define NFC7I2C_NCI_STAT_SEMANTIC_ERROR         0x06
#define NFC7I2C_NCI_STAT_UNK_GID                0x07
#define NFC7I2C_NCI_STAT_UNK_OID                0x08
#define NFC7I2C_NCI_STAT_INVALID_PARAM          0x09
#define NFC7I2C_NCI_STAT_MSG_SIZE_EXCEEDED      0x0A
#define NFC7I2C_NCI_STAT_DISC_ALRDY_STARTED     0xA0
#define NFC7I2C_NCI_STAT_DISC_T_ACT_FAILED      0xA1
#define NFC7I2C_NCI_STAT_DISC_TEAR_DOWN         0xA2
#define NFC7I2C_NCI_STAT_RF_TX_ERROR            0xB0
#define NFC7I2C_NCI_STAT_RF_PROTOCOL_ERROR      0xB1
#define NFC7I2C_NCI_STAT_RF_TIMEOUT_ERROR       0xB2

/**
 * @brief NFC 7 I2C RF technologies and mode setting.
 * @details Specified settings of RF technologies and mode of NFC 7 I2C Click driver.
 */
#define NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_NFC_A  0x00
#define NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_NFC_B  0x01
#define NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_NFC_F  0x02
#define NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_15693  0x06
#define NFC7I2C_NCI_RF_EXE_EVERY_DISC_PERIOD    0x01

/**
 * @brief NFC 7 I2C RF protocols setting.
 * @details Specified settings of RF protocols of NFC 7 I2C Click driver.
 */
#define NFC7I2C_NCI_RF_PROT_UNDETERMINED        0x00
#define NFC7I2C_NCI_RF_PROT_T1T                 0x01
#define NFC7I2C_NCI_RF_PROT_T2T                 0x02
#define NFC7I2C_NCI_RF_PROT_T3T                 0x03
#define NFC7I2C_NCI_RF_PROT_ISODEP              0x04
#define NFC7I2C_NCI_RF_PROT_NFCDEP              0x05
#define NFC7I2C_NCI_RF_PROT_T5T                 0x06
#define NFC7I2C_NCI_RF_PROT_MIFARE              0x80

/**
 * @brief NFC 7 I2C RF interface setting.
 * @details Specified settings of RF interface of NFC 7 I2C Click driver.
 */
#define NFC7I2C_NCI_RF_INTF_UNDETERMINED        0x00
#define NFC7I2C_NCI_RF_INTF_FRAME               0x01
#define NFC7I2C_NCI_RF_INTF_ISODEP              0x02
#define NFC7I2C_NCI_RF_INTF_NFCDEP              0x03
#define NFC7I2C_NCI_RF_INTF_TAGCMD              0x80
#define NFC7I2C_NCI_RF_MAP_POLL_MODE            0x01

/**
 * @brief NFC 7 I2C RF deactivate CMD setting.
 * @details Specified settings of RF deactivate CMD of NFC 7 I2C Click driver.
 */
#define NFC7I2C_NCI_RF_DEACTIVATE_IDLE          0x00
#define NFC7I2C_NCI_RF_DEACTIVATE_SLEEP         0x01
#define NFC7I2C_NCI_RF_DEACTIVATE_SLEEP_AF      0x02
#define NFC7I2C_NCI_RF_DEACTIVATE_DISCOVERY     0x03

/**
 * @brief NFC 7 I2C RF discover CMD setting.
 * @details Specified settings of RF discover CMD of NFC 7 I2C Click driver.
 */
#define NFC7I2C_NCI_RF_CONN_ID_STATIC           0x00
#define NFC7I2C_NCI_RF_CONN_ID_1                0x01
#define NFC7I2C_NCI_RF_CONN_ID_2                0x02
#define NFC7I2C_NCI_RF_DISC_MORE_NTF_FOLLOW     0x02

/**
 * @brief NFC 7 I2C T1T commands setting.
 * @details Specified settings of T1T commands of NFC 7 I2C Click driver.
 */
#define NFC7I2C_T1T_CMD_RID                     0x78
#define NFC7I2C_T1T_CMD_RALL                    0x00
#define NFC7I2C_T1T_CMD_READ                    0x01
#define NFC7I2C_T1T_CMD_WRITE_E                 0x53
#define NFC7I2C_T1T_CMD_WRITE_NE                0x1A
#define NFC7I2C_T1T_CMD_RSEG                    0x10
#define NFC7I2C_T1T_CMD_READ8                   0x02
#define NFC7I2C_T1T_CMD_WRITE_E8                0x54
#define NFC7I2C_T1T_CMD_WRITE_NE8               0x1B

/**
 * @brief NFC 7 I2C T2T commands setting.
 * @details Specified settings of T2T commands of NFC 7 I2C Click driver.
 */
#define NFC7I2C_T2T_CMD_READ                    0x30
#define NFC7I2C_T2T_CMD_WRITE                   0xA2
#define NFC7I2C_T2T_CMD_SECTOR_SELECT           0xC2
#define NFC7I2C_T2T_ACK                         0x0A

/**
 * @brief NFC 7 I2C T4T commands setting.
 * @details Specified settings of T4T commands of NFC 7 I2C Click driver.
 */
#define NFC7I2C_T4T_RSP_COMPLETE_1              0x90
#define NFC7I2C_T4T_RSP_COMPLETE_2              0x00
#define NFC7I2C_T4T_CLA_NO_SECURE               0x00
#define NFC7I2C_T4T_INS_SELECT                  0xA4
#define NFC7I2C_T4T_P1_SELECT_BY_NAME           0x04
#define NFC7I2C_T4T_P2_ONLY_OCCURANCE           0x00
#define NFC7I2C_T4T_LE_RSP_MAY_PRESENT          0x00
#define NFC7I2C_T4T_PPSE_APDU                   "2PAY.SYS.DDF01"

/**
 * @brief NFC 7 I2C ISO15693 commands setting.
 * @details Specified settings of ISO15693 commands of NFC 7 I2C Click driver.
 */
#define NFC7I2C_ISO15693_FLAG_DR_HIGH           0x02
#define NFC7I2C_ISO15693_CMD_READ_SINGLE        0x20
#define NFC7I2C_ISO15693_CMD_WRITE_SINGLE       0x21
#define NFC7I2C_ISO15693_RSP_OK                 0x00

/**
 * @brief NFC 7 I2C MIFARE commands setting.
 * @details Specified settings of MIFARE commands of NFC 7 I2C Click driver.
 */
#define NFC7I2C_MFC_REQ_XCHG_DATA               0x10
#define NFC7I2C_MFC_REQ_SECTOR_SEL              0x32
#define NFC7I2C_MFC_REQ_AUTHENTICATE            0x40
#define NFC7I2C_MFC_KEY_SELECTOR_A_EMB          0x10
#define NFC7I2C_MFC_CMD_READ                    0x30
#define NFC7I2C_MFC_CMD_WRITE                   0xA0
#define NFC7I2C_MFC_ACK                         0x0A

/**
 * @brief NFC 7 I2C core config default setting.
 * @details Specified default setting of core config of NFC 7 I2C Click driver.
 */
#define NFC7I2C_NCI_CORE_TOTAL_DURATION_510MS   { 0x01, 0x00, 0x02, 0xFE, 0x01 }
#define NFC7I2C_NCI_CORE_TAG_DETECTOR_DIS       { 0x01, 0xA0, 0x40, 0x01, 0x00 }
#define NFC7I2C_NCI_CORE_CLOCK_SEL_XTAL         { 0x01, 0xA0, 0x03, 0x01, 0x08 }
#define NFC7I2C_NCI_CORE_PMU_IRQ_EN_TVDD_3V3    { 0x01, 0xA0, 0x0E, 0x0B, 0x11, 0x01, 0x01, 0x01, \
                                                  0x00, 0x00, 0x00, 0x10, 0x00, 0xD0, 0x0C }
#define NFC7I2C_NCI_CORE_RF_CONF                { 0x09, \
                                                  0xA0, 0x0D, 0x03, 0x78, 0x0D, 0x02, \
                                                  0xA0, 0x0D, 0x03, 0x78, 0x14, 0x02, \
                                                  0xA0, 0x0D, 0x06, 0x4C, 0x44, 0x65, 0x09, 0x00, 0x00, \
                                                  0xA0, 0x0D, 0x06, 0x4C, 0x2D, 0x05, 0x35, 0x1E, 0x01, \
                                                  0xA0, 0x0D, 0x06, 0x82, 0x4A, 0x55, 0x07, 0x00, 0x07, \
                                                  0xA0, 0x0D, 0x06, 0x44, 0x44, 0x03, 0x04, 0xC4, 0x00, \
                                                  0xA0, 0x0D, 0x06, 0x46, 0x30, 0x50, 0x00, 0x18, 0x00, \
                                                  0xA0, 0x0D, 0x06, 0x48, 0x30, 0x50, 0x00, 0x18, 0x00, \
                                                  0xA0, 0x0D, 0x06, 0x4A, 0x30, 0x50, 0x00, 0x08, 0x00 }

/**
 * @brief NFC 7 I2C timeout setting.
 * @details Specified setting for timeout of NFC 7 I2C Click driver.
 */
#define NFC7I2C_MAX_NCI_FRAME_SIZE              258
#define NFC7I2C_TIMEOUT_INFINITE                0
#define NFC7I2C_TIMEOUT_100MS                   100
#define NFC7I2C_TIMEOUT_1S                      1000
#define NFC7I2C_TIMEOUT_2S                      2000

/**
 * @brief NFC 7 I2C device address setting.
 * @details Specified setting for device slave address selection of
 * NFC 7 I2C Click driver.
 */
#define NFC7I2C_DEVICE_ADDRESS_0                0x28
#define NFC7I2C_DEVICE_ADDRESS_1                0x29
#define NFC7I2C_DEVICE_ADDRESS_2                0x2A
#define NFC7I2C_DEVICE_ADDRESS_3                0x2B

/*! @} */ // nfc7i2c_set

/**
 * @defgroup nfc7i2c_map NFC 7 I2C MikroBUS Map
 * @brief MikroBUS pin mapping of NFC 7 I2C Click driver.
 */

/**
 * @addtogroup nfc7i2c_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NFC 7 I2C Click to the selected MikroBUS.
 */
#define NFC7I2C_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ven = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nfc7i2c_map
/*! @} */ // nfc7i2c

/**
 * @brief NFC 7 I2C Click poll passive type A object.
 * @details Definition of discovered NFC-A remote device properties information of NFC 7 I2C Click driver.
 */
typedef struct
{
    uint8_t sens_res[ 2 ];
    uint8_t nfc_id_len;
    uint8_t nfc_id[ 10 ];
    uint8_t sel_res_len;
    uint8_t sel_res[ 1 ];
    uint8_t rats_len;
    uint8_t rats[ 20 ];

} nfc7i2c_rf_intf_info_app_t;

/**
 * @brief NFC 7 I2C Click poll passive type B object.
 * @details Definition of discovered NFC-B remote device properties information of NFC 7 I2C Click driver.
 */
typedef struct
{
    uint8_t sens_res_len;
    uint8_t sens_res[ 12 ];
    uint8_t attrib_res_len;
    uint8_t attrib_res[ 17 ];

} nfc7i2c_rf_intf_info_bpp_t;

/**
 * @brief NFC 7 I2C Click poll passive type F object.
 * @details Definition of discovered NFC-F remote device properties information of NFC 7 I2C Click driver.
 */
typedef struct
{
    uint8_t bitrate;
    uint8_t sens_res_len;
    uint8_t sens_res[ 18 ];

} nfc7i2c_rf_intf_info_fpp_t;

/**
 * @brief NFC 7 I2C Click poll passive type V/ISO15693 object.
 * @details Definition of discovered ISO15693 remote device properties information of NFC 7 I2C Click driver.
 */
typedef struct
{
    uint8_t afi;
    uint8_t dsf_id;
    uint8_t id[ 8 ];

} nfc7i2c_rf_intf_info_vpp_t;

/**
 * @brief NFC 7 I2C Click discovered remote device properties information object.
 * @details Definition of discovered remote device properties information of NFC 7 I2C Click driver.
 */
typedef union
{
    nfc7i2c_rf_intf_info_app_t nfc_app;
    nfc7i2c_rf_intf_info_bpp_t nfc_bpp;
    nfc7i2c_rf_intf_info_fpp_t nfc_fpp;
    nfc7i2c_rf_intf_info_vpp_t nfc_vpp;

} nfc7i2c_rf_intf_info_t;

/**
 * @brief NFC 7 I2C Click discovered remote device properties object.
 * @details Definition of discovered remote device properties of NFC 7 I2C Click driver.
 */
typedef struct
{
    uint8_t intf;                   /**< RF Interface. */
    uint8_t protocol;               /**< RF Protocol. */
    uint8_t mode_tech;              /**< RF technology and mode. */
    uint8_t more_tags;              /**< More tags discovered flag (true or false). */
    nfc7i2c_rf_intf_info_t info;    /**< Discovered remote device properties information. */

} nfc7i2c_rf_intf_t;

/**
 * @brief NFC 7 I2C Click control packet object.
 * @details Control packet object definition of NFC 7 I2C Click driver.
 */
typedef struct
{
    uint8_t msg_type;               /**< Message type field (MT). */
    uint8_t gid;                    /**< Group Identifier (GID). */
    uint8_t oid;                    /**< Opcode Identifier (OID). */
    uint8_t payload_len;            /**< Payload Length (L). */
    uint8_t payload[ NFC7I2C_MAX_NCI_FRAME_SIZE - 3 ];  /**< Payload. */

} nfc7i2c_pkt_ctrl_t;

/**
 * @brief NFC 7 I2C Click data packet object.
 * @details Data packet object definition of NFC 7 I2C Click driver.
 */
typedef struct
{
    uint8_t cid;                    /**< Connection Identifier (Conn ID). */
    uint8_t payload_len;            /**< Payload Length (L). */
    uint8_t payload[ NFC7I2C_MAX_NCI_FRAME_SIZE - 3 ];  /**< Payload. */

} nfc7i2c_pkt_data_t;

/**
 * @brief NFC 7 I2C Click context object.
 * @details Context object definition of NFC 7 I2C Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t ven;              /**< Reset pin (active low). */

    // Input pins
    digital_in_t irq;               /**< Interrupt request pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

    nfc7i2c_pkt_ctrl_t pkt_ctrl;    /**< NCI Packet control. */
    nfc7i2c_pkt_data_t pkt_data;    /**< NCI Packet data. */
    uint8_t cmd[ NFC7I2C_MAX_NCI_FRAME_SIZE ];  /**< NCI command buffer. */
    uint8_t rsp[ NFC7I2C_MAX_NCI_FRAME_SIZE ];  /**< NCI response buffer. */
    uint16_t rsp_len;               /**< NCI response length. */

    uint8_t fw_version[ 3 ];        /**< FW version (ROM.major.minor). */
    uint8_t next_tag_protocol;      /**< Next discovered tag protocol. */

} nfc7i2c_t;

/**
 * @brief NFC 7 I2C Click configuration object.
 * @details Configuration object definition of NFC 7 I2C Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t ven;                 /**< Reset pin (active low). */
    pin_name_t irq;                 /**< Interrupt request pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} nfc7i2c_cfg_t;

/**
 * @brief NFC 7 I2C Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NFC7I2C_OK = 0,
    NFC7I2C_ERROR = -1

} nfc7i2c_return_value_t;

/*!
 * @addtogroup nfc7i2c NFC 7 I2C Click Driver
 * @brief API for configuring and manipulating NFC 7 I2C Click driver.
 * @{
 */

/**
 * @brief NFC 7 I2C configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nfc7i2c_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nfc7i2c_cfg_setup ( nfc7i2c_cfg_t *cfg );

/**
 * @brief NFC 7 I2C initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nfc7i2c_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_init ( nfc7i2c_t *ctx, nfc7i2c_cfg_t *cfg );

/**
 * @brief NFC 7 I2C default configuration function.
 * @details This function executes a default configuration of NFC 7 I2C
 * Click board.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t nfc7i2c_default_cfg ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C enable device function.
 * @details This function enables the device by setting the VEN pin to HIGH logic state.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void nfc7i2c_enable_device ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C disable device function.
 * @details This function disables the device by setting the VEN pin to LOW logic state.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void nfc7i2c_disable_device ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C reset device function.
 * @details This function resets the device by toggling the VEN pin.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void nfc7i2c_reset_device ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C get IRQ pin function.
 * @details This function returns the IRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nfc7i2c_get_irq_pin ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C TX function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_tx ( nfc7i2c_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NFC 7 I2C RX function.
 * @details This function waits a desired period for a data received flag and reads the data 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[out] len : Number of bytes read.
 * @param[in] timeout : Waiting data timeout in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_rx ( nfc7i2c_t *ctx, uint8_t *data_out, uint16_t *len, uint16_t timeout );

/**
 * @brief NFC 7 I2C TRX function.
 * @details This function sends data using nfc7i2c_tx function and reads the response using nfc7i2c_rx
 * with a 1 second timeout.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of bytes to be written.
 * @param[out] data_out : Output read data.
 * @param[out] out_len : Number of bytes read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_trx ( nfc7i2c_t *ctx, uint8_t *data_in, uint16_t in_len, uint8_t *data_out, uint16_t *out_len );

/**
 * @brief NFC 7 I2C packet control TX function.
 * @details This function sends a desired NCI control packet data.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in] pkt : NCI control packet data structure to be sent.
 * See #nfc7i2c_pkt_ctrl_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_pkt_ctrl_tx ( nfc7i2c_t *ctx, nfc7i2c_pkt_ctrl_t *pkt );

/**
 * @brief NFC 7 I2C packet control RX function.
 * @details This function waits a desired period for a NCI control packet response to arrive and reads it.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[out] pkt : NCI control packet data structure read.
 * See #nfc7i2c_pkt_ctrl_t object definition for detailed explanation.
 * @param[in] timeout : Waiting data timeout in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_pkt_ctrl_rx ( nfc7i2c_t *ctx, nfc7i2c_pkt_ctrl_t *pkt, uint16_t timeout );

/**
 * @brief NFC 7 I2C packet control TRX function.
 * @details This function sends a NCI control packet using nfc7i2c_pkt_ctrl_tx function and reads
 * the response using nfc7i2c_pkt_ctrl_rx with a 1 second timeout.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in,out] pkt : NCI control packet data structure to write (response packet is populated here).
 * See #nfc7i2c_pkt_ctrl_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_pkt_ctrl_trx ( nfc7i2c_t *ctx, nfc7i2c_pkt_ctrl_t *pkt );

/**
 * @brief NFC 7 I2C packet data TX function.
 * @details This function sends a desired NCI data packet data.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in] pkt : NCI data packet data structure to be sent.
 * See #nfc7i2c_pkt_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_pkt_data_tx ( nfc7i2c_t *ctx, nfc7i2c_pkt_data_t *pkt );

/**
 * @brief NFC 7 I2C packet data RX function.
 * @details This function waits a desired period for a NCI data packet response to arrive and reads it.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[out] pkt : NCI data packet data structure read.
 * See #nfc7i2c_pkt_data_t object definition for detailed explanation.
 * @param[in] timeout : Waiting data timeout in milliseconds.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_pkt_data_rx ( nfc7i2c_t *ctx, nfc7i2c_pkt_data_t *pkt, uint16_t timeout );

/**
 * @brief NFC 7 I2C packet data TRX function.
 * @details This function sends a NCI data packet using nfc7i2c_pkt_data_tx function and reads
 * the response using nfc7i2c_pkt_data_rx with a 1 second timeout.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in,out] pkt : NCI data packet data structure to write (response packet is populated here).
 * See #nfc7i2c_pkt_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_pkt_data_trx ( nfc7i2c_t *ctx, nfc7i2c_pkt_data_t *pkt );

/**
 * @brief NFC 7 I2C core reset function.
 * @details This function resets the device core and reads the FW version.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_core_reset ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C core init function.
 * @details This function resets and initializes the device core.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_core_init ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C core standby function.
 * @details This function sets the core standby mode.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Standby mode disabled,
 *                   @li @c 1 - Standby mode enabled,
 *                   @li @c 2 - Autonomous mode enabled.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_core_standby ( nfc7i2c_t *ctx, uint8_t mode );

/**
 * @brief NFC 7 I2C core total duration function.
 * @details This function sets the core total duration of the single discovery period
 * to NFC7I2C_NCI_CORE_TOTAL_DURATION_510MS.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_core_total_duration ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C core tag detector function.
 * @details This function sets the core tag detector to NFC7I2C_NCI_CORE_TAG_DETECTOR_DIS.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_core_tag_detector ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C core clock sel function.
 * @details This function sets the core clock selection to NFC7I2C_NCI_CORE_CLOCK_SEL_XTAL.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_core_clock_sel ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C core PMU function.
 * @details This function sets the core power management unit to NFC7I2C_NCI_CORE_PMU_IRQ_EN_TVDD_3V3.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_core_pmu ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C core RF config function.
 * @details This function sets the core RF config to NFC7I2C_NCI_CORE_RF_CONF.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_core_rf_config ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C config settings function.
 * @details This function sets the default core config settings.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_config_settings ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C map RF interface function.
 * @details This function enables all RF protocols and interface in poll mode.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_map_rf_interface ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C start discovery function.
 * @details This function starts RF discovery for NFC-A, NFC-B, NFC-F, and NFC-V technologies.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_start_discovery ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C stop discovery function.
 * @details This function stops the RF discovery process.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_stop_discovery ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C wait discovery function.
 * @details This function waits until remote NFC device is discovered.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[out] rf_intf : Filled with discovered NFC remote device properties.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_wait_discovery ( nfc7i2c_t *ctx, nfc7i2c_rf_intf_t *rf_intf );

/**
 * @brief NFC 7 I2C presence check function.
 * @details This function waits until the discovered target device is removed.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in] rf_intf : Filled with discovered NFC remote device properties.
 * @return None.
 * @note None.
 */
void nfc7i2c_presence_check ( nfc7i2c_t *ctx, nfc7i2c_rf_intf_t *rf_intf );

/**
 * @brief NFC 7 I2C reader activate next function.
 * @details This function performs activation of the next tag (in case of multiple tag
 * detection or multi-protocol tag).
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in,out] rf_intf : Filled with discovered NFC remote device properties.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_reader_act_next ( nfc7i2c_t *ctx, nfc7i2c_rf_intf_t *rf_intf );

/**
 * @brief NFC 7 I2C reader reactivate next function.
 * @details This function performs reactivation of the current tag.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in] rf_intf : Filled with discovered NFC remote device properties.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_reader_re_act ( nfc7i2c_t *ctx, nfc7i2c_rf_intf_t *rf_intf );

/**
 * @brief NFC 7 I2C reader tag cmd function.
 * @details This function performs RAW data packet transceive operation (send then receive)
 * with the remote tag.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @param[in,out] pkt : NCI data packet data structure to write (response packet is populated here).
 * See #nfc7i2c_pkt_data_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc7i2c_reader_tag_cmd ( nfc7i2c_t *ctx, nfc7i2c_pkt_data_t *pkt );

#ifdef __cplusplus
}
#endif
#endif // NFC7I2C_H

/*! @} */ // nfc7i2c

// ------------------------------------------------------------------------ END
