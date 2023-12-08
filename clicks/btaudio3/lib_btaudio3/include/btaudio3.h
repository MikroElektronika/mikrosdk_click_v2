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
 * @file btaudio3.h
 * @brief This file contains API for BT Audio 3 Click Driver.
 */

#ifndef BTAUDIO3_H
#define BTAUDIO3_H

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
#include "drv_uart.h"

/*!
 * @addtogroup btaudio3 BT Audio 3 Click Driver
 * @brief API for configuring and manipulating BT Audio 3 Click driver.
 * @{
 */

/**
 * @defgroup btaudio3_cmd BT Audio 3 Device Settings
 * @brief Settings for registers of BT Audio 3 Click driver.
 */

/**
 * @addtogroup btaudio3_cmd
 * @{
 */

/**
 * @brief BT Audio 3 commands OP code list.
 * @details Specified commands OP code list of BT Audio 3 Click driver.
 */
#define BTAUDIO3_CMD_MAKE_CALL                                  0x00
#define BTAUDIO3_CMD_MAKE_EXTENSION_CALL                        0x01
#define BTAUDIO3_CMD_MMI_ACTION                                 0x02
#define BTAUDIO3_CMD_EVENT_MASK_SETTING                         0x03
#define BTAUDIO3_CMD_MUSIC_CONTROL                              0x04
#define BTAUDIO3_CMD_CHANGE_DEVICE_NAME                         0x05
#define BTAUDIO3_CMD_CHANGE_PIN_CODE                            0x06
#define BTAUDIO3_CMD_SET_BTM_PARAM                              0x07
#define BTAUDIO3_CMD_GET_BTM_VERSION                            0x08
#define BTAUDIO3_CMD_VENDOR_AT_CMD                              0x0A
#define BTAUDIO3_CMD_AVRCP_SPEC_CMD                             0x0B
#define BTAUDIO3_CMD_AVRCP_GROUP_NAVIGATION                     0x0C
#define BTAUDIO3_CMD_READ_LINK_STATUS                           0x0D
#define BTAUDIO3_CMD_READ_PAIRING_RECORD                        0x0E
#define BTAUDIO3_CMD_READ_LOCAL_BD_ADDR                         0x0F
#define BTAUDIO3_CMD_READ_LOCAL_DEVICE_NAME                     0x10
#define BTAUDIO3_CMD_SEND_SPP_DATA                              0x12
#define BTAUDIO3_CMD_BTM_UTILITY_FUNCTION                       0x13
#define BTAUDIO3_CMD_EVENT_ACK                                  0x14
#define BTAUDIO3_CMD_ADDITIONAL_PROFILE_LINK_SETUP              0x15
#define BTAUDIO3_CMD_READ_LINKED_DEVICE_INFO                    0x16
#define BTAUDIO3_CMD_PROFILE_LINK_BACK                          0x17
#define BTAUDIO3_CMD_DISCONNECT                                 0x18
#define BTAUDIO3_CMD_USER_CONFIRM_SPP_REQ_REPLY                 0x1A
#define BTAUDIO3_CMD_SET_HF_GAIN_LEVEL                          0x1B
#define BTAUDIO3_CMD_EQ_MODE_SETTING                            0x1C
#define BTAUDIO3_CMD_DSP_NR_CTRL                                0x1D
#define BTAUDIO3_CMD_GPIO_CTRL                                  0x1E
#define BTAUDIO3_CMD_BT_MCU_UART_RX_BUFF_SIZE                   0x1F
#define BTAUDIO3_CMD_VOICE_PROMPT_CMD                           0x20
#define BTAUDIO3_CMD_SET_OVERALL_GAIN                           0x23
#define BTAUDIO3_CMD_READ_BTM_SETTING                           0x24
#define BTAUDIO3_CMD_READ_BTM_BATTERY_CHARGE_STATUS             0x25
#define BTAUDIO3_CMD_MCU_UPDATE                                 0x26
#define BTAUDIO3_CMD_REPORT_BATTERY_CAPACITY                    0x27
#define BTAUDIO3_CMD_LE_ANCS_SERVICE                            0x28
#define BTAUDIO3_CMD_LE_SIGNALING                               0x29
#define BTAUDIO3_CMD_MSPK_VENDOR                                0x2A
#define BTAUDIO3_CMD_READ_MSPK_LINK_STATUS                      0x2B
#define BTAUDIO3_CMD_MSPK_SYNC_AUDIO_EFFECT                     0x2C
#define BTAUDIO3_CMD_LE_GATT                                    0x2D
#define BTAUDIO3_CMD_LE_APP                                     0x2F
#define BTAUDIO3_CMD_DSP_RUNTIME_PROGRAM                        0x30
#define BTAUDIO3_CMD_READ_VENDOR_EEPROM                         0x31
#define BTAUDIO3_CMD_READ_IC_VERSION                            0x32
#define BTAUDIO3_CMD_READ_LINK_MODE                             0x34
#define BTAUDIO3_CMD_CONFIGURE_VENDOR_PARAM                     0x35
#define BTAUDIO3_CMD_MSPK_EXCHANGE_LINK_INFO                    0x37
#define BTAUDIO3_CMD_MSPK_SET_GIAC                              0x38
#define BTAUDIO3_CMD_READ_FEATURE_LIST                          0x39
#define BTAUDIO3_CMD_PERSONAL_MSPK_GROUP_CTRL                   0x3A
#define BTAUDIO3_CMD_TEST_DEVICE                                0x3B
#define BTAUDIO3_CMD_READ_EEPROM                                0x3C
#define BTAUDIO3_CMD_WRITE_EEPROM                               0x3D
#define BTAUDIO3_CMD_LE_SIGNALING_2                             0x3E
#define BTAUDIO3_CMD_PBAPC                                      0x3F
#define BTAUDIO3_CMD_TWS                                        0x40
#define BTAUDIO3_CMD_AVRCP_BROWSING                             0x41
#define BTAUDIO3_CMD_READ_PAIRED_LINK_KEY_INFO                  0x42
#define BTAUDIO3_CMD_AUDIO_TRANSCEIVER                          0x44
#define BTAUDIO3_CMD_BUTTON_MMI_SETTING                         0x46
#define BTAUDIO3_CMD_BUTTON_OPERATION                           0x47
#define BTAUDIO3_CMD_READ_BUTTON_MMI_SETTING                    0x48
#define BTAUDIO3_CMD_DFU                                        0x49
#define BTAUDIO3_CMD_AVRCP_VENDOR_DEPENDENT                     0x4A
#define BTAUDIO3_CMD_CONCERT_MODE_ENDLESS_GROUPING              0x4B
#define BTAUDIO3_CMD_READ_RUNTIME_LATENCY                       0x4C
#define BTAUDIO3_CMD_TOGGLE_AUDIO_SOURCE                        0xCC

/**
 * @brief BT Audio 3 events OP code list.
 * @details Specified events OP code list of BT Audio 3 Click driver.
 */
#define BTAUDIO3_EVT_CMD_ACK                                    0x00
#define BTAUDIO3_EVT_BTM_STATE                                  0x01
#define BTAUDIO3_EVT_CALL_STATUS                                0x02
#define BTAUDIO3_EVT_CALL_ID                                    0x03
#define BTAUDIO3_EVT_SMS_INDICATION                             0x04
#define BTAUDIO3_EVT_MISS_CALL_INDICATION                       0x05
#define BTAUDIO3_EVT_PHONE_MAX_BATTERY_LEVEL                    0x06
#define BTAUDIO3_EVT_PHONE_BATTERY_LEVEL                        0x07
#define BTAUDIO3_EVT_PHONE_ROAMING_STATUS                       0x08
#define BTAUDIO3_EVT_PHONE_MAX_SIGNAL_STRENGTH                  0x09
#define BTAUDIO3_EVT_PHONE_SIGNAL_STRENGTH                      0x0A
#define BTAUDIO3_EVT_PHONE_SERVICE_STATUS                       0x0B
#define BTAUDIO3_EVT_BATTERY_LEVEL                              0x0C
#define BTAUDIO3_EVT_CHARGER_STATUS                             0x0D
#define BTAUDIO3_EVT_RESET_TO_DEFAULT                           0x0E
#define BTAUDIO3_EVT_VOLUME_LEVEL                               0x0F
#define BTAUDIO3_EVT_EQ_MODE                                    0x10
#define BTAUDIO3_EVT_LINKED_DEVICE_INFO                         0x17
#define BTAUDIO3_EVT_BTM_VERSION                                0x18
#define BTAUDIO3_EVT_CALL_LIST_REPORT                           0x19
#define BTAUDIO3_EVT_AVRCP_SPEC_RSP                             0x1A
#define BTAUDIO3_EVT_BTM_UTILITY_REQ                            0x1B
#define BTAUDIO3_EVT_VENDOR_AT_CMD_RSP                          0x1C
#define BTAUDIO3_EVT_UNKNOW_AT_RESULT                           0x1D
#define BTAUDIO3_EVT_REPORT_LINK_STATUS                         0x1E
#define BTAUDIO3_EVT_REPORT_PAIRING_RECORD                      0x1F
#define BTAUDIO3_EVT_REPORT_LOCAL_BD_ADDR                       0x20
#define BTAUDIO3_EVT_REPORT_LOCAL_DEVICE_NAME                   0x21
#define BTAUDIO3_EVT_REPORT_SPP_DATA                            0x22
#define BTAUDIO3_EVT_REPORT_LINK_BACK_STATUS                    0x23
#define BTAUDIO3_EVT_RINGTONE_FINISH_INDICATION                 0x24
#define BTAUDIO3_EVT_USER_CONFIRM_SSP_REQ                       0x25
#define BTAUDIO3_EVT_REPORT_AVRCP_VOL_CTRL                      0x26
#define BTAUDIO3_EVT_REPORT_INPUT_SIGNAL_LEVEL                  0x27
#define BTAUDIO3_EVT_REPORT_IAP_INFO                            0x28
#define BTAUDIO3_EVT_REPORT_AVRCP_ABS_VOL_CTRL                  0x29
#define BTAUDIO3_EVT_REPORT_VOICE_PROMPT_STATUS                 0x2A
#define BTAUDIO3_EVT_REPORT_TYPE_CODEC                          0x2D
#define BTAUDIO3_EVT_REPORT_TYPE_BTM_SETTING                    0x2E
#define BTAUDIO3_EVT_REPORT_MCU_UPDATE_REPLY                    0x2F
#define BTAUDIO3_EVT_REPORT_BTM_INITIAL_STATUS                  0x30
#define BTAUDIO3_EVT_REPORT_LE_ANCS_EVENT                       0x31
#define BTAUDIO3_EVT_REPORT_LE_EVENT                            0x32
#define BTAUDIO3_EVT_REPORT_MSPK_STATUS                         0x33
#define BTAUDIO3_EVT_REPORT_MSPK_VENDOR_EVENT                   0x34
#define BTAUDIO3_EVT_REPORT_MSPK_AUDIO_SETTING                  0x35
#define BTAUDIO3_EVT_REPORT_MSPK_EFFECT_STATUS                  0x36
#define BTAUDIO3_EVT_REPORT_VENDOR_EEPROM                       0x37
#define BTAUDIO3_EVT_REPORT_IC_VERSION_INFO                     0x38
#define BTAUDIO3_EVT_REPORT_CUSTOMER_GATT_ATTRIBUTE_DATA        0x39
#define BTAUDIO3_EVT_REPORT_LINK_MODE                           0x3A
#define BTAUDIO3_EVT_REPORT_MSPK_EXCHANGE_LINK_INFO             0x3D
#define BTAUDIO3_EVT_REPORT_BT_CLK                              0x3F
#define BTAUDIO3_EVT_REPORT_FEATURE_LIST                        0x40
#define BTAUDIO3_EVT_REPORT_TEST_RESULT                         0x41
#define BTAUDIO3_EVT_REPORT_READ_EEPROM_DATA                    0x42
#define BTAUDIO3_EVT_PBAPC_EVENT                                0x43
#define BTAUDIO3_EVT_AVRCP_BROWSING_EVENT                       0x44
#define BTAUDIO3_EVT_REPORT_PAIRED_LINK_KEY_INFO                0x45
#define BTAUDIO3_EVT_REPORT_TWS_RX_VENDOR_EVENT                 0x53
#define BTAUDIO3_EVT_REPORT_TWS_LOCAL_DEVICE_STATUS             0x54
#define BTAUDIO3_EVT_REPORT_TWS_VAD_DATA                        0x55
#define BTAUDIO3_EVT_REPORT_TWS_RADIO_CONDITION                 0x56
#define BTAUDIO3_EVT_REPORT_TWS_EAR_BUD_POSITION                0x57
#define BTAUDIO3_EVT_REPORT_TWS_SECONDARY_DEVICE_STATUS         0x58
#define BTAUDIO3_EVT_AUDIO_TRANSCEIVER_EVENT_STATUS             0x5A
#define BTAUDIO3_EVT_READ_BUTTON_MMI_SETTING_REPLY              0x5C
#define BTAUDIO3_EVT_AVRCP_VENDOR_DEPENDENT_RSP                 0x5D
#define BTAUDIO3_EVT_RUNTIME_LATENCY                            0x5E

/**
 * @brief BT Audio 3 MMI actions list.
 * @details Specified MMI actions list of BT Audio 3 Click driver.
 */
#define BTAUDIO3_MMI_ADD_REMOVE_SCO_LINK                        0x01
#define BTAUDIO3_MMI_ENABLE_TEST_MODE                           0x03
#define BTAUDIO3_MMI_ACCEPT_CALL                                0x04
#define BTAUDIO3_MMI_REJECT_CALL                                0x05
#define BTAUDIO3_MMI_ENDCALL_OR_TRANSFER_TO_HEADSET             0x06
#define BTAUDIO3_MMI_MIC_MUTE_TOGGLE                            0x07
#define BTAUDIO3_MMI_MUTE_MIC                                   0x08
#define BTAUDIO3_MMI_UNMUTE_MIC                                 0x09
#define BTAUDIO3_MMI_VOICE_DIAL                                 0x0A
#define BTAUDIO3_MMI_CANCEL_VOICE_DIAL                          0x0B
#define BTAUDIO3_MMI_LAST_NUMBER_REDIAL                         0x0C
#define BTAUDIO3_MMI_ACTIVE_CALL_HOLD_ACCEPT_HELD_CALL          0x0D
#define BTAUDIO3_MMI_VOICE_TRANSFER                             0x0E
#define BTAUDIO3_MMI_QUERY_CALL_LIST                            0x0F
#define BTAUDIO3_MMI_THREE_WAY_CALL                             0x10
#define BTAUDIO3_MMI_RELEASE_CALL                               0x11
#define BTAUDIO3_MMI_ACCEPT_WAITING_HOLD_CALL_RLS_ACTIVE_CALL   0x12
#define BTAUDIO3_MMI_DISCONNECT_HF_LINK                         0x17
#define BTAUDIO3_MMI_ENABLE_AEC                                 0x1E
#define BTAUDIO3_MMI_DISABLE_AEC                                0x1F
#define BTAUDIO3_MMI_SWITCH_AEC                                 0x20
#define BTAUDIO3_MMI_ENABLE_AEC_RX_NOISE_REDUCTION              0x21
#define BTAUDIO3_MMI_DISABLE_AEC_RX_NOISE_REDUCTION             0x22
#define BTAUDIO3_MMI_SWITCH_AEC_RX_NOISE_REDUCTION              0x23
#define BTAUDIO3_MMI_INC_MIC_GAIN                               0x24
#define BTAUDIO3_MMI_DEC_MIC_GAIN                               0x25
#define BTAUDIO3_MMI_SWITCH_PRIMARY_SECONDARY_HF_DEVICE         0x26
#define BTAUDIO3_MMI_LOCK_BUTTON                                0x3A
#define BTAUDIO3_MMI_DISCONNECT_A2DP                            0x3B
#define BTAUDIO3_MMI_NEXT_AUDIO_EFFECT                          0x3C
#define BTAUDIO3_MMI_PREVIOUS_AUDIO_EFFECT                      0x3D
#define BTAUDIO3_MMI_REPORT_CURRENT_EQ_MODE                     0x3F
#define BTAUDIO3_MMI_REPORT_CURRENT_AUDIO_EFFECT_STATUS         0x40
#define BTAUDIO3_MMI_TOGGLE_AUDIO_PLAYBACK                      0x41
#define BTAUDIO3_MMI_POWER_ON_BUTTON_PRESS                      0x51
#define BTAUDIO3_MMI_POWER_ON_BUTTON_RELEASE                    0x52
#define BTAUDIO3_MMI_POWER_OFF_BUTTON_PRESS                     0x53
#define BTAUDIO3_MMI_POWER_OFF_BUTTON_RELEASE                   0x54
#define BTAUDIO3_MMI_RESET_EEPROM_SETTING                       0x56
#define BTAUDIO3_MMI_FORCE_SPEAKER_GAIN_TOGGLE                  0x57
#define BTAUDIO3_MMI_TOGGLE_BUTTON_IND                          0x58
#define BTAUDIO3_MMI_COMBINE_FUNCTION_0                         0x59
#define BTAUDIO3_MMI_COMBINE_FUNCTION_1                         0x5A
#define BTAUDIO3_MMI_COMBINE_FUNCTION_2                         0x5B
#define BTAUDIO3_MMI_COMBINE_FUNCTION_3                         0x5C
#define BTAUDIO3_MMI_ENTER_PAIRING_MODE                         0x5D
#define BTAUDIO3_MMI_SWITCH_POWER_OFF                           0x5E
#define BTAUDIO3_MMI_DISABLE_LED                                0x5F
#define BTAUDIO3_MMI_BUZZER_TOGGLE                              0x60
#define BTAUDIO3_MMI_DISABLE_BUZZER                             0x61
#define BTAUDIO3_MMI_ENABLE_BUZZER                              0x62
#define BTAUDIO3_MMI_TONE_CHANGE                                0x63
#define BTAUDIO3_MMI_SHS_SEND_USER_DATA_1                       0x72
#define BTAUDIO3_MMI_SHS_SEND_USER_DATA_2                       0x73
#define BTAUDIO3_MMI_SHS_SEND_USER_DATA_3                       0x74
#define BTAUDIO3_MMI_SHS_SEND_USER_DATA_4                       0x75
#define BTAUDIO3_MMI_SHS_SEND_USER_DATA_5                       0x76
#define BTAUDIO3_MMI_REPORT_CURRENT_RX_NR_STATUS                0x77
#define BTAUDIO3_MMI_REPORT_CURRENT_TX_NR_STATUS                0x78
#define BTAUDIO3_MMI_CANCEL_ALL_BT_PAGING                       0x7A
#define BTAUDIO3_MMI_DISCONNECT_SPP_LINK                        0x7D
#define BTAUDIO3_MMI_ENABLE_A2DP_MIX_LINE_IN                    0x80
#define BTAUDIO3_MMI_DISABLE_A2DP_MIX_LINE_IN                   0x81
#define BTAUDIO3_MMI_INCREASE_LINE_IN_INPUT_GAIN                0x82
#define BTAUDIO3_MMI_DECREASE_LINE_IN_INPUT_GAIN                0x83
#define BTAUDIO3_MMI_TRIGGER_MSPK_CENTRAL                       0xE0
#define BTAUDIO3_MMI_TRIGGER_MSPK_PERIPHERAL                    0xE1
#define BTAUDIO3_MMI_MSPK_ONE_KEY_CONNECT                       0xE2
#define BTAUDIO3_MMI_CANCEL_MSPK_CREATION                       0xE3
#define BTAUDIO3_MMI_TERMINATE_MSPK_LINK                        0xE4
#define BTAUDIO3_MMI_TERMINATE_MSPK_CONNECTION                  0xE5
#define BTAUDIO3_MMI_MSPK_CENTRAL_ENTER_AUX_IN_44p1K_PCM_MODE   0xE6
#define BTAUDIO3_MMI_MSPK_CENTRAL_ENTER_AUX_IN_48K_PCM_MODE     0xE7
#define BTAUDIO3_MMI_MSPK_CENTRAL_EXIT_AUX_IN_PCM_MODE          0xE8
#define BTAUDIO3_MMI_MSPK_SWITCH_CHANNEL                        0xEC
#define BTAUDIO3_MMI_MSPK_POWER_OFF_ALL_SPEAKERS                0xED
#define BTAUDIO3_MMI_MSPK_ERASE_CONCERT_MODE_RECORD             0xEF
#define BTAUDIO3_MMI_MSPK_ENTER_STEREO_MODE                     0xF4
#define BTAUDIO3_MMI_MSPK_ENTER_CONCERT_MODE                    0xF5
#define BTAUDIO3_MMI_MSPK_ADD_THIRD_SPK                         0xF6
#define BTAUDIO3_MMI_MSPK_SOUND_SYNC                            0xF7
#define BTAUDIO3_MMI_MSPK_CSB_CONNECTED_MODE_SWITCH             0xF8
#define BTAUDIO3_MMI_MSPK_BACK_TO_LAST_MODE                     0xF9
#define BTAUDIO3_MMI_MSPK_ONE_KEY_CONNECT_WITH_LINK_BACK        0xFA
#define BTAUDIO3_MMI_MSPK_ONE_KEY_OP_STEREO_MODE                0xFB
#define BTAUDIO3_MMI_MSPK_ONE_KEY_OP_CONCERT_MODE               0xFC

/**
 * @brief BT Audio 3 command ACK status bytes.
 * @details Specified command ACK status bytes of BT Audio 3 Click driver.
 */
#define BTAUDIO3_ACK_STATUS_CMD_COMPLETE                        0x00
#define BTAUDIO3_ACK_STATUS_CMD_DISALLOW                        0x01
#define BTAUDIO3_ACK_STATUS_CMD_UNKNOWN                         0x02
#define BTAUDIO3_ACK_STATUS_CMD_PARAM_ERR                       0x03
#define BTAUDIO3_ACK_STATUS_CMD_BTM_BUSY                        0x04
#define BTAUDIO3_ACK_STATUS_CMD_BTM_FULL                        0x05

/**
 * @brief BT Audio 3 BTM status bytes.
 * @details Specified BTM status bytes of BT Audio 3 Click driver.
 */
#define BTAUDIO3_BTM_STATE_POWER_OFF                            0x00
#define BTAUDIO3_BTM_STATE_PAIRING_STATE                        0x01
#define BTAUDIO3_BTM_STATE_POWER_ON                             0x02
#define BTAUDIO3_BTM_STATE_PAIRING_SUCCESSFULL                  0x03
#define BTAUDIO3_BTM_STATE_PAIRING_FAILED                       0x04
#define BTAUDIO3_BTM_STATE_HFHS_LINK_ESTABLISHED                0x05
#define BTAUDIO3_BTM_STATE_A2DP_LINK_ESTABLISHED                0x06
#define BTAUDIO3_BTM_STATE_HF_LINK_DISCONNECTED                 0x07
#define BTAUDIO3_BTM_STATE_A2DP_LINK_DISCONNECTED               0x08
#define BTAUDIO3_BTM_STATE_SCO_LINK_CONNECTED                   0x09
#define BTAUDIO3_BTM_STATE_SCO_LINK_DISCONNECTED                0x0A
#define BTAUDIO3_BTM_STATE_AVRCP_LINK_ESTABLISHED               0x0B
#define BTAUDIO3_BTM_STATE_AVRCP_LINK_DISCONNECTED              0x0C
#define BTAUDIO3_BTM_STATE_STANDARD_SPP_CONNECTED               0x0D
#define BTAUDIO3_BTM_STATE_STANDARD_SPP_IAP_DISCONNECTED        0x0E
#define BTAUDIO3_BTM_STATE_STANDBY_STATE                        0x0F
#define BTAUDIO3_BTM_STATE_IAP_CONNECTED                        0x10
#define BTAUDIO3_BTM_STATE_ACL_DISCONNECTED                     0x11
#define BTAUDIO3_BTM_STATE_MAP_CONNECTED                        0x12
#define BTAUDIO3_BTM_STATE_MAP_OPERATION_FORBIDDEN              0x13
#define BTAUDIO3_BTM_STATE_MAP_DISCONNECTED                     0x14
#define BTAUDIO3_BTM_STATE_ACL_CONNECTED                        0x15
#define BTAUDIO3_BTM_STATE_SPP_IAP_DISCONNECTED_NO_PROFILE      0x16
#define BTAUDIO3_BTM_STATE_LINK_BACK_ACL                        0x17
#define BTAUDIO3_BTM_STATE_INQUIRY_STATE                        0x18
#define BTAUDIO3_BTM_STATE_UNKNOWN_AUDIO_SOURCE                 0x80
#define BTAUDIO3_BTM_STATE_AUX_IN_AUDIO_SOURCE                  0x81
#define BTAUDIO3_BTM_STATE_A2DP_AUDIO_SOURCE                    0x82

/**
 * @brief BT Audio 3 Volume control mask bytes.
 * @details Specified Volume control mask bytes of BT Audio 3 Click driver.
 */
#define BTAUDIO3_VOLUME_MASK_A2DP                               0x01
#define BTAUDIO3_VOLUME_MASK_HF                                 0x02
#define BTAUDIO3_VOLUME_MASK_LINE_IN                            0x04
#define BTAUDIO3_VOLUME_MASK_PCM                                0x08
#define BTAUDIO3_VOLUME_MASK_LINE_IN_INPUT                      0x10  

/**
 * @brief BT Audio 3 header byte.
 * @details Specified header byte of BT Audio 3 Click driver.
 */
#define BTAUDIO3_START_HEADER                                   0xAA

/**
 * @brief BT Audio 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                                         512

/*! @} */ // btaudio3_cmd

/**
 * @defgroup btaudio3_map BT Audio 3 MikroBUS Map
 * @brief MikroBUS pin mapping of BT Audio 3 Click driver.
 */

/**
 * @addtogroup btaudio3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BT Audio 3 Click to the selected MikroBUS.
 */
#define BTAUDIO3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sm = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.mfb = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.mod = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // btaudio3_map
/*! @} */ // btaudio3

/**
 * @brief BT Audio 3 Click command/event packet structure object.
 * @details Command/event packet structure object definition of BT Audio 3 Click driver.
 */
typedef struct
{
    uint8_t opcode;
    uint8_t param_buf[ 256 ];
    uint8_t param_len;
    
} btaudio3_packet_t;

/**
 * @brief BT Audio 3 Click context object.
 * @details Context object definition of BT Audio 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t sm;                       /**< Soft mute pin. */
    digital_out_t rst;                      /**< Reset pin. */
    digital_out_t mfb;                      /**< Multi-function button pin. */
    digital_out_t mod;                      /**< System config pin. */

    // Modules
    uart_t uart;                            /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ]; /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ]; /**< Buffer size. */
    
    btaudio3_packet_t command_packet;
    btaudio3_packet_t event_packet;

} btaudio3_t;

/**
 * @brief BT Audio 3 Click configuration object.
 * @details Configuration object definition of BT Audio 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                      /**< RX pin. */
    pin_name_t tx_pin;                      /**< TX pin. */

    // Additional gpio pins
    pin_name_t sm;                          /**< Soft mute pin. */
    pin_name_t rst;                         /**< Reset pin. */
    pin_name_t mfb;                         /**< Multi-function button pin. */
    pin_name_t mod;                         /**< System config pin. */

    // Static variable
    uint32_t          baud_rate;            /**< Clock speed. */
    bool              uart_blocking;        /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;             /**< Data bits. */
    uart_parity_t     parity_bit;           /**< Parity bit. */
    uart_stop_bits_t  stop_bit;             /**< Stop bits. */

} btaudio3_cfg_t;

/**
 * @brief BT Audio 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BTAUDIO3_OK = 0,
    BTAUDIO3_ERROR = -1

} btaudio3_return_value_t;

/**
 * @brief BT Audio 3 Click music control values.
 * @details Predefined enum values for music control.
 */
typedef enum
{
    BTAUDIO3_STOP_FAST_FORWARD_OR_REWIND = 0,
    BTAUDIO3_FAST_FORWARD,
    BTAUDIO3_FAST_FORWARD_WITH_REPEAT,
    BTAUDIO3_REWIND,
    BTAUDIO3_REWIND_WITH_REPEAT,
    BTAUDIO3_PLAY,
    BTAUDIO3_PAUSE,
    BTAUDIO3_PLAY_PAUSE_TOGGLE,
    BTAUDIO3_STOP,
    BTAUDIO3_NEXT_SONG,
    BTAUDIO3_PREVIOUS_SONG

} btaudio3_music_control_t;

/**
 * @brief BT Audio 3 Click equalizer mode selection values.
 * @details Predefined enum values for equalizer mode selection.
 */
typedef enum
{
    BTAUDIO2_EQ_MODE_OFF = 0,
    BTAUDIO2_EQ_MODE_SOFT,
    BTAUDIO2_EQ_MODE_BASS,
    BTAUDIO2_EQ_MODE_TREBLE,
    BTAUDIO2_EQ_MODE_CLASSIC,
    BTAUDIO2_EQ_MODE_ROCK,
    BTAUDIO2_EQ_MODE_JAZZ,
    BTAUDIO2_EQ_MODE_POP,
    BTAUDIO2_EQ_MODE_DANCE,
    BTAUDIO2_EQ_MODE_RNB,
    BTAUDIO2_EQ_MODE_USER1

} btaudio3_eq_mode_t;

/*!
 * @addtogroup btaudio3 BT Audio 3 Click Driver
 * @brief API for configuring and manipulating BT Audio 3 Click driver.
 * @{
 */

/**
 * @brief BT Audio 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #btaudio3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void btaudio3_cfg_setup ( btaudio3_cfg_t *cfg );

/**
 * @brief BT Audio 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #btaudio3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_init ( btaudio3_t *ctx, btaudio3_cfg_t *cfg );

/**
 * @brief BT Audio 3 default configuration function.
 * @details This function executes a default configuration of BT Audio 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t btaudio3_default_cfg ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_generic_write ( btaudio3_t *ctx, uint8_t *data_buf, uint16_t len );

/**
 * @brief BT Audio 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_generic_read ( btaudio3_t *ctx, uint8_t *data_buf, uint16_t max_len );

/**
 * @brief BT Audio 3 set MFB pin function.
 * @details This function sets the MFB pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void btaudio3_set_mfb_pin ( btaudio3_t *ctx, uint8_t state );

/**
 * @brief BT Audio 3 set RST pin function.
 * @details This function sets the RST pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void btaudio3_set_rst_pin ( btaudio3_t *ctx, uint8_t state );

/**
 * @brief BT Audio 3 set application mode function.
 * @details This function enters the application mode by setting the MOD pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void btaudio3_set_application_mode ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 set test mode function.
 * @details This function enters the test mode by setting the MOD pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void btaudio3_set_test_mode ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 reset device function.
 * @details This function resets the device via the RST pin.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void btaudio3_reset_device ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 soft mute output function.
 * @details This function soft mutes output by setting the SM pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void btaudio3_soft_mute_output ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 soft unmute output function.
 * @details This function soft unmutes output by setting the SM pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void btaudio3_soft_unmute_output ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 send command function.
 * @details This function sends a desired command from the click context object.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void btaudio3_send_command ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 send command with ack check function.
 * @details This function sends a desired command from the click context object, and waits for
 * the command acknowledge event, if there's no ACK event received it resends the command once again.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_send_command_with_ack_check ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 read event function.
 * @details This function reads an event from the ring buffer and stores it in the click context object.
 * It waits 200ms for an event, and if there's no event received it returns an error.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return @li @c  0 - Correct event received,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_read_event ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 wait for event function.
 * @details This function waits for the desired event to occur and stores it in the click context object.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] opcode : Expected event opcode.
 * @return None.
 * @note None.
 */
void btaudio3_wait_for_event ( btaudio3_t *ctx, uint8_t opcode );

/**
 * @brief BT Audio 3 clear events function.
 * @details This function clears all events from the ring buffer. The last cleared event will be stored in the
 * click context object.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void btaudio3_clear_events ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 send MMI action function.
 * @details This function sends a desired MMI action to specific index database.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] database_index : Database index.
 * @param[in] action : MMI action byte.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_send_mmi_action ( btaudio3_t *ctx, uint8_t database_index, uint8_t action );

/**
 * @brief BT Audio 3 power ON device function.
 * @details This function powers ON the device and waits for the power ON BTM event to occur.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_power_on_device ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 power OFF device function.
 * @details This function powers OFF the device and waits for the power OFF BTM event to occur.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_power_off_device ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 enter pairing mode function.
 * @details This function enters pairing mode and waits for the pairing state BTM event to occur.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_enter_pairing_mode ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 reset to default function.
 * @details This function resets the device to default state and waits for an appropriate event to occur.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_reset_to_default ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 set device name function.
 * @details This function sets the local device name.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] device_name : Device name (up to 32 characters).
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_set_device_name ( btaudio3_t *ctx, uint8_t *device_name );

/**
 * @brief BT Audio 3 music control function.
 * @details This function sends a music control command with a desired action.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] action : Action for music control command.
 * See #btaudio3_music_control_t enum definition for detailed explanation.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_music_control ( btaudio3_t *ctx, btaudio3_music_control_t action );

/**
 * @brief BT Audio 3 make call function.
 * @details This function makes a call to the specified phone number.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] database_index : Database index.
 * @param[in] phone_number : Phone number (up to 19 characters).
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_make_call ( btaudio3_t *ctx, uint8_t database_index, uint8_t *phone_number );

/**
 * @brief BT Audio 3 volume up function.
 * @details This function increases the volume of a specified gain mask.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] database_index : Database index.
 * @param[in] mask : Gain mask.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_volume_up ( btaudio3_t *ctx, uint8_t database_index, uint8_t mask );

/**
 * @brief BT Audio 3 volume down function.
 * @details This function decreases the volume of a specified gain mask.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] database_index : Database index.
 * @param[in] mask : Gain mask.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_volume_down ( btaudio3_t *ctx, uint8_t database_index, uint8_t mask );

/**
 * @brief BT Audio 3 enable advertising function.
 * @details This function enables advertising of LE signaling.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_enable_advertising ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 disable advertising function.
 * @details This function disables advertising of LE signaling.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_disable_advertising ( btaudio3_t *ctx );

/**
 * @brief BT Audio 3 set equalizer mode function.
 * @details This function sets the equalizer mode.
 * @param[in] ctx : Click context object.
 * See #btaudio3_t object definition for detailed explanation.
 * @param[in] eq_mode : Equalizer mode byte.
 * See #btaudio3_eq_mode_t enum definition for detailed explanation.
 * @return @li @c  >=0 - Command ACK event response,
 *         @li @c   -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t btaudio3_set_eq_mode ( btaudio3_t *ctx, btaudio3_eq_mode_t eq_mode );

#ifdef __cplusplus
}
#endif
#endif // BTAUDIO3_H

/*! @} */ // btaudio3

// ------------------------------------------------------------------------ END
