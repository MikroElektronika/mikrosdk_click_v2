/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file nfc2.h
 * @brief This file contains API for NFC 2 Click Driver.
 */

#ifndef NFC2_H
#define NFC2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup nfc2 NFC 2 Click Driver
 * @brief API for configuring and manipulating NFC 2 Click driver.
 * @{
 */

/**
 * @defgroup nfc2_set NFC 2 Registers Settings
 * @brief Settings for registers of NFC 2 Click driver.
 */

/**
 * @addtogroup nfc2_set
 * @{
 */

/**
 * @brief NFC 2 description setting.
 * @details Specified setting for description of NFC 2 Click driver.
 */
#define NFC2_RF_DISCOVER_MAP_CMD                                    0x00
#define NFC2_RF_DISCOVER_MAP_RSP                                    0x00
#define NFC2_RF_SET_LISTEN_MODE_ROUTING_CMD                         0x01
#define NFC2_RF_SET_LISTEN_MODE_ROUTING_RSP                         0x01
#define NFC2_RF_GET_LISTEN_MODE_ROUTING_CMD                         0x02
#define NFC2_RF_GET_LISTEN_MODE_ROUTING_RSP                         0x02
#define NFC2_RF_GET_LISTEN_MODE_ROUTING_NTF                         0x02
#define NFC2_RF_DISCOVER_CMD                                        0x03
#define NFC2_RF_DISCOVER_RSP                                        0x03
#define NFC2_RF_DISCOVER_NTF                                        0x03
#define NFC2_RF_DISCOVER_SELECT_CMD                                 0x04
#define NFC2_RF_DISCOVER_SELECT_RSP                                 0x04
#define NFC2_RF_INTF_ACTIVATED_NTF                                  0x05
#define NFC2_RF_DEACTIVATE_CMD                                      0x06
#define NFC2_RF_DEACTIVATE_RSP                                      0x06
#define NFC2_RF_DEACTIVATE_NTF                                      0x06
#define NFC2_RF_FIELD_INFO_NTF                                      0x07
#define NFC2_RF_T3T_POLLING_CMD                                     0x08
#define NFC2_RF_T3T_POLLING_RSP                                     0x08
#define NFC2_RF_T3T_POLLING_NTF                                     0x08
#define NFC2_RF_NFCEE_ACTION_NTF                                    0x09
#define NFC2_RF_NFCEE_DISCOVERY_REQ_NTF                             0x0A
#define NFC2_RF_PARAMETER_UPDATE_CMD                                0x0B
#define NFC2_RF_PARAMETER_UPDATE_RSP                                0x0B

#define NFC2_NFCEE_DISCOVER_CMD                                     0x00
#define NFC2_NFCEE_DISCOVER_RSP                                     0x00
#define NFC2_NFCEE_DISCOVER_NTF                                     0x00
#define NFC2_NFCEE_MODE_SET_CMD                                     0x01
#define NFC2_NFCEE_MODE_SET_RSP                                     0x01

#define NFC2_NCI_PROPRIETARY_ACT_CMD                                0x02
#define NFC2_NCI_PROPRIETARY_ACT_RSP                                0x02
#define NFC2_RESET_KEEP_CONFIG                                      0x00
#define NFC2_RESET_CLEAR_CONFIG                                     0x01

/**
 * @brief NFC 2 generic status codes.
 * @details Specified generic status codes of NFC 2 Click driver.
 */
#define NFC2_STATUS_OK                                              0x00
#define NFC2_STATUS_REJECTED                                        0x01
#define NFC2_STATUS_RF_FRAME_CORRUPTED                              0x02
#define NFC2_STATUS_FAILED                                          0x03
#define NFC2_STATUS_NOT_INITIALIZED                                 0x04
#define NFC2_STATUS_SYNTAX_ERROR                                    0x05
#define NFC2_STATUS_SEMANTIC_ERROR                                  0x06

#define NFC2_STATUS_INVALID_PARAM                                   0x09
#define NFC2_STATUS_MESSAGE_SIZE_EXCEEDED                           0x0A

#define NFC2_DISCOVERY_ALREADY_STARTED                              0xA0
#define NFC2_DISCOVERY_TARGET_ACTIVATION_FAILED                     0xA1
#define NFC2_DISCOVERY_TEAR_DOWN                                    0xA2

#define NFC2_RF_TRANSMISSION_ERROR                                  0xB0
#define NFC2_RF_PROTOCOL_ERROR                                      0xB1
#define NFC2_RF_TIMEOUT_ERROR                                       0xB2

#define NFC2_NFCEE_INTERFACE_ACTIVATION_FAILED                      0xC0
#define NFC2_NFCEE_TRANSMISSION_ERROR                               0xC1
#define NFC2_NFCEE_PROTOCOL_ERROR                                   0xC2
#define NFC2_NFCEE_TIMEOUT_ERROR                                    0xC3

#define NFC2_NFC_RF_TECHNOLOGY_A                                    0x00
#define NFC2_NFC_RF_TECHNOLOGY_B                                    0x01
#define NFC2_NFC_RF_TECHNOLOGY_F                                    0x02
#define NFC2_NFC_RF_TECHNOLOGY_15693                                0x03

/**
 * @brief NFC 2 passive poll mode.
 * @details Specified passive poll mode of NFC 2 Click driver.
 */
#define NFC2_NFC_A_PASSIVE_POLL_MODE                                0x00
#define NFC2_NFC_B_PASSIVE_POLL_MODE                                0x01
#define NFC2_NFC_F_PASSIVE_POLL_MODE                                0x02
#define NFC2_NFC_A_ACTIVE_POLL_MODE                                 0x03
#define NFC2_NFC_F_ACTIVE_POLL_MODE                                 0x05
#define NFC2_NFC_15693_PASSIVE_POLL_MODE                            0x06

#define NFC2_NFC_A_PASSIVE_LISTEN_MODE                              0x80
#define NFC2_NFC_B_PASSIVE_LISTEN_MODE                              0x81
#define NFC2_NFC_F_PASSIVE_LISTEN_MODE                              0x82
#define NFC2_NFC_A_ACTIVE_LISTEN_MODE                               0x83
#define NFC2_NFC_F_ACTIVE_LISTEN_MODE                               0x85
#define NFC2_NFC_15693_PASSIVE_LISTEN_MODE                          0x86

/**
 * @brief NFC 2 RF protocols.
 * @details Specified RF protocols of NFC 2 Click driver.
 */
#define NFC2_PROTOCOL_UNDETERMINED                                  0x00
#define NFC2_PROTOCOL_T1T                                           0x01
#define NFC2_PROTOCOL_T2T                                           0x02
#define NFC2_PROTOCOL_T3T                                           0x03
#define NFC2_PROTOCOL_ISO_DEP                                       0x04
#define NFC2_PROTOCOL_NFC_DEP                                       0x05

#define NFC2_NFCEE_DIRECT_RF_INTERFACE                              0x00
#define NFC2_FRAME_RF_INTERFACE                                     0x01
#define NFC2_ISO_DEP_RF_INTERFACE                                   0x02
#define NFC2_NFC_DEP_RF_INTERFACE                                   0x03

/**
 * @brief NFC 2 NFCEE protocol.
 * @details Specified NFCEE protocol of NFC 2 Click driver.
 */
#define NFC2_APDU                                                   0x00
#define NFC2_HCI_ACCES                                              0x01
#define NFC2_TYPE_3_TAG_COMMAND_SET                                 0x02
#define NFC2_TRANSPARENT                                            0x03

/**
 * @brief NFC 2 bit rates.
 * @details Specified bit rates of NFC 2 Click driver.
 */
#define NFC2_NFC_BIT_RATE_106                                       0x00
#define NFC2_NFC_BIT_RATE_212                                       0x01
#define NFC2_NFC_BIT_RATE_424                                       0x02
#define NFC2_NFC_BIT_RATE_848                                       0x03
#define NFC2_NFC_BIT_RATE_1695                                      0x04
#define NFC2_NFC_BIT_RATE_3390                                      0x05
#define NFC2_NFC_BIT_RATE_6780                                      0x06

/**
 * @brief NFC 2 IRQ state.
 * @details Specified IRQ state of NFC 2 Click driver.
 */
#define NFC2_IRQ_STATE_LOW                                          0x00
#define NFC2_IRQ_STATE_HIGH                                         0x01

/**
 * @brief NFC 2 Group Identifier ( GID ).
 * @details Specified Group Identifier ( GID ) of NFC 2 Click driver.
 */
#define NFC2_GROUP_ID_CORE                                          0x00
#define NFC2_GROUP_ID_RF_MANAGEMENT                                 0x01
#define NFC2_GROUP_ID_NFC_MANAGEMENT                                0x02
#define NFC2_GROUP_ID_PROPRIETARY                                   0x0F

/**
 * @brief NFC 2 OpCode Identifier ( OID ).
 * @details Specified OpCode Identifier ( OID ) of NFC 2 Click driver.
 */
#define NFC2_CORE_RESET_CMD                                         0x00
#define NFC2_CORE_RESET_RSP                                         0x00
#define NFC2_CORE_RESET_NTF                                         0x00
#define NFC2_CORE_INIT_CMD                                          0x01
#define NFC2_CORE_INIT_RSP                                          0x01
#define NFC2_CORE_SET_CONFIG_CMD                                    0x02
#define NFC2_CORE_SET_CONFIG_RSP                                    0x02
#define NFC2_CORE_GET_CONFIG_CMD                                    0x03
#define NFC2_CORE_GET_CONFIG_RSP                                    0x03
#define NFC2_CORE_CONN_CREATE_CMD                                   0x04
#define NFC2_CORE_CONN_CREATE_RSP                                   0x04
#define NFC2_CORE_CONN_CLOSE_CMD                                    0x05
#define NFC2_CORE_CONN_CLOSE_RSP                                    0x05
#define NFC2_CORE_CONN_CREDITS_NTF                                  0x06
#define NFC2_CORE_GENERIC_ERROR_NTF                                 0x07
#define NFC2_CORE_INTERFACE_ERROR_NTF                               0x08

/**
 * @brief NFC 2 device address setting.
 * @details Specified setting for device slave address selection of
 * NFC 2 Click driver.
 */
#define NFC2_I2C_ADDR_0                                             0x28
#define NFC2_I2C_ADDR_1                                             0x29
#define NFC2_I2C_ADDR_2                                             0x2A
#define NFC2_I2C_ADDR_3                                             0x2B

/*! @} */ // nfc2_set

/**
 * @defgroup nfc2_map NFC 2 MikroBUS Map
 * @brief MikroBUS pin mapping of NFC 2 Click driver.
 */

/**
 * @addtogroup nfc2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NFC 2 Click to the selected MikroBUS.
 */
#define NFC2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nfc2_map
/*! @} */ // nfc2

/**
 * @brief NFC 2 Click context object.
 * @details Context object definition of NFC 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;                             /**< Reset. */

    // Input pins
    digital_in_t  int_pin;                          /**< Interrupt. */

    // Modules
    i2c_master_t i2c;                               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                          /**< Device slave address (used for I2C driver). */

} nfc2_t;

/**
 * @brief NFC 2 Click configuration object.
 * @details Configuration object definition of NFC 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;            /**< Reset. */
    pin_name_t  int_pin;        /**< Interrupt. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} nfc2_cfg_t;

/**
 * @brief NFC 2 Click control packet object.
 * @details Control packet object definition of NFC 2 Click driver.
 */
typedef struct
{
    uint8_t message_type;
    uint8_t pck_bound_flag;
    uint8_t group_ident;
    uint8_t opcode_ident;
    uint8_t payload_length;
    uint8_t payload[ 256 ];
} control_packet_t;

/**
 * @brief NFC 2 Click data packet object.
 * @details Data packet object definition of NFC 2 Click driver.
 */
typedef struct
{
    uint8_t message_type;
    uint8_t pck_bound_flag;
    uint8_t conn_ident;
    uint8_t payload_length;
    uint8_t payload[ 256 ];
} data_packet_t;

/**
 * @brief NFC 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   NFC2_OK = 0,
   NFC2_ERROR = -1

} nfc2_return_value_t;

/*!
 * @addtogroup nfc2 NFC 2 Click Driver
 * @brief API for configuring and manipulating NFC 2 Click driver.
 * @{
 */

/**
 * @brief NFC 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nfc2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nfc2_cfg_setup ( nfc2_cfg_t *cfg );

/**
 * @brief NFC 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nfc2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t nfc2_init ( nfc2_t *ctx, nfc2_cfg_t *cfg );

/**
 * @brief NFC 2 default configuration function.
 * @details This function executes a default configuration of NFC 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @param[out] ctrl_pck : Pointer to the memory location of structure.
 * @return Nothing. 
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void nfc2_default_cfg ( nfc2_t *ctx, control_packet_t *ctrl_pck );

/**
 * @brief NFC 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @param[in] p_tx_data : Data to be written.
 * @param[in] n_bytes : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t nfc2_generic_write ( nfc2_t *ctx, uint8_t *p_tx_data, uint8_t n_bytes );

/**
 * @brief NFC 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @param[out] p_rx_h_data : Pointer to the memory location where header data be stored.
 * @param[out] p_rx_p_data : Pointer to the memory location where payload data be stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t nfc2_generic_read ( nfc2_t *ctx, uint8_t *p_rx_h_data, uint8_t *p_rx_p_data );

/**
 * @brief HW reset function.
 * @details The function hw reset 
 * @param[out] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * the PN7150 High performance NFC controller on the NFC 2 click board.
 * @return Nothing.
 */
void nfc2_hw_reset( nfc2_t *ctx );

/**
 * @brief Get data function.
 * @details The function read a sequential data starting
 * of the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @param[out] p_rx_data : Pointer to the memory location where data be stored.
 * @return Number od data.
 */
uint8_t nfc2_get_data ( nfc2_t *ctx, uint8_t *p_rx_data );

/**
 * @brief Read control packet data function.
 * @details The function read control packet data
 * of the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @param[in] ctrl_pck : Pointer to the memory location of structure.
 * @return Nothing.
 */
void nfc2_read_ctrl_packet_data ( nfc2_t *ctx, control_packet_t *ctrl_pck );

/**
 * @brief Write control packet data function.
 * @details The function write control packet data
 * to the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @param[in] ctrl_pck : Structure where data be stored.
 * @return Nothing.
 */
void nfc2_write_ctrl_packet_data ( nfc2_t *ctx, control_packet_t ctrl_pck );

/**
 * @brief Check IRQ ststus function.
 * @details The function check interrupt state and 
 * return state of the INT pin
 * of the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @return @li @c  0 - No active,
 *         @li @c  1 - Active.
 */
uint8_t nfc2_check_irq ( nfc2_t *ctx );

/**
 * @brief Core reset command function.
 * @details The function set core reset command
 * to the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @return Nothing.
 */
void nfc2_cmd_core_reset ( nfc2_t *ctx );

/**
 * @brief Core init command function.
 * @details The function set core init command
 * to the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @return Nothing.
 */
void nfc2_cmd_core_init ( nfc2_t *ctx );

/**
 * @brief Disable standby mode command function.
 * @details The function set disable standby mode command
 * to the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 */
void nfc2_cmd_disable_standby_mode ( nfc2_t *ctx );

/**
 * @brief Antenna test function.
 * @details The function set antenna test
 * to the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @param[in] sel_ant : Presence of the antenna components.
 * @return Nothing.
 */
void nfc2_cmd_antenna_test ( nfc2_t *ctx, uint8_t sel_ant );

/**
 * @brief NFC test procedure command function.
 * @details The function set test procedure command
 * to the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @return Nothing.
 */
void nfc2_cmd_test_procedure ( nfc2_t *ctx );

/**
 * @brief Core reset command function.
 * @details The function set core reset command
 * to the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @return Nothing.
 */
void nfc2_core_reset ( nfc2_t *ctx );

/**
 * @brief Core initialization command function.
 * @details The function set core initialization command
 * to the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @return Nothing.
 */
void nfc2_init_core ( nfc2_t *ctx );

/**
 * @brief Set default configuration function.
 * @details The function set default configuration
 * of the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @return Nothing.
 */
void nfc2_core_set_default_config ( nfc2_t *ctx );

/**
 * @brief Set protocol configuration function.
 * @details The function set protocol configuration
 * of the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @return Nothing.
 */
void nfc2_core_set_protocol_config ( nfc2_t *ctx );

/**
 * @brief Start discovery command function.
 * @details The function set start discovery command
 * of the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @return Nothing.
 */
void nfc2_cmd_start_discovery ( nfc2_t *ctx );

/**
 * @brief Activate remote mifare card command function.
 * @details The function set activate remote mifare card command
 * of the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @return Nothing.
 */
void nfc2_activate_rmt_mifare_card ( nfc2_t *ctx );

/**
 * @brief Authenticate sector command function.
 * @details The function set authenticate sector command
 * of the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @param[in] sel_sect_addr : Sector authenticate address.
 * @return Nothing.
 */
void nfc2_cmd_authenticate_sector ( nfc2_t *ctx, uint8_t sel_sect_addr );

/**
 * @brief Card disconnected command function.
 * @details The function set card disconnected command
 * of the PN7150 High performance NFC controller on the NFC 2 click board.
 * @param[in] ctx : Click context object.
 * See #nfc2_t object definition for detailed explanation.
 * @return Nothing.
 */
void nfc2_cmd_card_disconnected ( nfc2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // NFC2_H

/*! @} */ // nfc2

// ------------------------------------------------------------------------ END
