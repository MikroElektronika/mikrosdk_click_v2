/*!
 * @file      lr1110_modem_lorawan_types.h
 *
 * @brief     Modem lorawan types for LR1110
 *
 * The Clear BSD License
 * Copyright Semtech Corporation 2021. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LR1110_MODEM_LORAWAN_TYPES_H
#define LR1110_MODEM_LORAWAN_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdint.h>
#include <stdbool.h>
#include "modem/lr1110_modem_common.h"

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/*!
 * @brief Length in bytes of a chip eui
 */
#define LR1110_MODEM_CHIP_EUI_LENGTH ( 8 )

/*!
 * @brief Length in bytes of a LoRaWAN device eui
 */
#define LR1110_MODEM_DEV_EUI_LENGTH ( 8 )

/*!
 * @brief Length in bytes of a LoRaWAN join eui
 */
#define LR1110_MODEM_JOIN_EUI_LENGTH ( 8 )

/*!
 * @brief Length in bytes of a LoRaWAN application key
 */
#define LR1110_MODEM_APP_KEY_LENGTH ( 16 )

/*!
 * @brief Number of regions available
 */
#define LR1110_MODEM_REGIONS_NUMBER ( 10 )

/*!
 * @brief Number of output power config blocks
 */
#define LR1110_MODEM_NB_OUTPUT_POWER_CONFIG_BLOCKS ( 6 )

/*!
 * @brief Power config block length
 */
#define LR1110_MODEM_OUTPUT_POWER_CONFIG_BLOCK_LENGTH ( 5 )

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*!
 * @brief Power Amplifier Selection values
 *
 * - Low-power Power Amplifier can reach up to 14dBm
 * - High-power Power Amplifier can reach up to 22 dBm
 */
typedef enum
{
    LR1110_MODEM_RADIO_PA_SEL_LP       = 0x00,  //!< Low-power Power Amplifier
    LR1110_MODEM_RADIO_PA_SEL_HP       = 0x01,  //!< High-power Power Amplifier
    LR1110_MODEM_RADIO_PA_SEL_LP_HP_LF = 0x02,  //!< Low-power & High-power Power Amplifier
} lr1110_modem_radio_pa_selection_t;

/*!
 * @brief functionality values
 */
typedef enum
{
    LR1110_MODEM_FUNCTIONALITY_TRX                   = 0x01,
    LR1110_MODEM_FUNCTIONALITY_MODEM_WIFI            = 0x02,
    LR1110_MODEM_FUNCTIONALITY_MODEM_WIFI_GPS        = 0x03,
    LR1110_MODEM_FUNCTIONALITY_MODEM_WIFI_GPS_BEIDOU = 0x04,
} lr1110_modem_functionality_t;

/*!
 * @brief LoRaWAN class type
 */
typedef enum
{
    LR1110_LORAWAN_CLASS_A = 0x00,
    LR1110_LORAWAN_CLASS_C = 0x01,
} lr1110_modem_classes_t;

/*!
 * @brief Modem status bits
 */
typedef enum
{
    LR1110_LORAWAN_CRASH   = 0x02,
    LR1110_LORAWAN_MUTE    = 0x04,
    LR1110_LORAWAN_JOINED  = 0x08,
    LR1110_LORAWAN_SUSPEND = 0x10,
    LR1110_LORAWAN_UPLOAD  = 0x20,
    LR1110_LORAWAN_JOINING = 0x40,
    LR1110_LORAWAN_STREAM  = 0x80,
} lr1110_modem_status_t;

/*!
 * @brief LoRaWAN region type
 */
typedef enum
{
    LR1110_LORAWAN_REGION_EU868      = 0x01,
    LR1110_LORAWAN_REGION_AS923_GRP1 = 0x02,
    LR1110_LORAWAN_REGION_US915      = 0x03,
    LR1110_LORAWAN_REGION_AU915      = 0x04,
    LR1110_LORAWAN_REGION_CN470      = 0x05,
    LR1110_LORAWAN_REGION_AS923_GRP2 = 0x07,
    LR1110_LORAWAN_REGION_AS923_GRP3 = 0x08,
    LR1110_LORAWAN_REGION_IN865      = 0x09,
    LR1110_LORAWAN_REGION_KR920      = 0x0A,
    LR1110_LORAWAN_REGION_RU864      = 0x0B,
} lr1110_modem_regions_t;

/*!
 * @brief Adaptative Data Rate profiles type
 */
typedef enum
{
    LR1110_MODEM_ADR_PROFILE_NETWORK_SERVER_CONTROLLED = 0x00,  //!< Network Server Controlled
    LR1110_MODEM_ADR_PROFILE_MOBILE_LONG_RANGE = 0x01,  //!< Mobile Long Range : 50% MinDr, 25% MinDr + 1, 25% MinDr + 2
    LR1110_MODEM_ADR_PROFILE_MOBILE_LOW_POWER =
        0x02,  //!< Mobile Low Power : 25% MaxDr, 25% MaxDr - 1, 25% MaxDr - 2, 25% MaxDr - 3
    LR1110_MODEM_ADR_PROFILE_CUSTOM =
        0x03,  //!< Custom List A custom ADR profile consists of a list of 16 preferred data rates.
               //!< For every transmission, a random entry in that list is selected.
} lr1110_modem_adr_profiles_t;

/*!
 * @brief DM reporting internal format
 */
typedef enum
{
    LR1110_MODEM_REPORTING_INTERVAL_IN_SECOND = 0x00,
    LR1110_MODEM_REPORTING_INTERVAL_IN_DAY    = 0x01,
    LR1110_MODEM_REPORTING_INTERVAL_IN_HOUR   = 0x02,
    LR1110_MODEM_REPORTING_INTERVAL_IN_MINUTE = 0x03,
} lr1110_modem_reporting_interval_format_t;

/*!
 * @brief DM status information code
 */
typedef enum
{
    LR1110_MODEM_DM_INFO_TYPE_STATUS                                  = 0x00,
    LR1110_MODEM_DM_INFO_TYPE_CHARGE                                  = 0x01,
    LR1110_MODEM_DM_INFO_TYPE_VOLTAGE                                 = 0x02,
    LR1110_MODEM_DM_INFO_TYPE_TEMPERATURE                             = 0x03,
    LR1110_MODEM_DM_INFO_TYPE_SIGNAL                                  = 0X04,
    LR1110_MODEM_DM_INFO_TYPE_UPTIME                                  = 0x05,
    LR1110_MODEM_DM_INFO_TYPE_RXTIME                                  = 0x06,
    LR1110_MODEM_DM_INFO_TYPE_FIRMWARE                                = 0x07,
    LR1110_MODEM_DM_INFO_TYPE_ADR_MODE                                = 0x08,
    LR1110_MODEM_DM_INFO_TYPE_JOIN_EUI                                = 0x09,
    LR1110_MODEM_DM_INFO_TYPE_INTERVAL                                = 0x0A,
    LR1110_MODEM_DM_INFO_TYPE_REGION                                  = 0x0B,
    LR1110_MODEM_DM_INFO_TYPE_CRASH_LOG                               = 0x0D,
    LR1110_MODEM_DM_INFO_TYPE_UPLOAD                                  = 0x0E,
    LR1110_MODEM_DM_INFO_TYPE_RESET_COUNT                             = 0x0F,
    LR1110_MODEM_DM_INFO_TYPE_DEV_EUI                                 = 0x10,
    LR1110_MODEM_DM_INFO_TYPE_SESSION_ID                              = 0x12,
    LR1110_MODEM_DM_INFO_TYPE_CHIP_EUI                                = 0x13,
    LR1110_MODEM_DM_INFO_TYPE_STREAM                                  = 0x14,
    LR1110_MODEM_DM_INFO_TYPE_STREAM_PARAMETERS                       = 0x15,
    LR1110_MODEM_DM_INFO_TYPE_APPLICATION_SPECIFIC_STATUS             = 0x16,
    LR1110_MODEM_DM_INFO_TYPE_APPLICATION_LAYER_CLOCK_SYNCHRONISATION = 0x17,
    LR1110_MODEM_DM_INFO_TYPE_GNSS_ALMANAC_STATUS                     = 0x18,
    LR1110_MODEM_DM_INFO_TYPE_GNSS_DEBUG_RESPONSE                     = 0x19,
    LR1110_MODEM_DM_INFO_TYPE_GNSS_LOC                                = 0x1A,
    LR1110_MODEM_DM_INFO_TYPE_WIFI_LOC                                = 0x1B,
} lr1110_modem_dm_info_type_t;

/*!
 * @brief LoRaWAN uplink type
 */
typedef enum
{
    LR1110_MODEM_UPLINK_UNCONFIRMED = 0x00,
    LR1110_MODEM_UPLINK_CONFIRMED   = 0x01,
} lr1110_modem_uplink_type_t;

/*!
 * @brief Radio test mode type
 */
typedef enum
{
    LR1110_MODEM_TEST_MODE_TST_START                       = 0x00,
    LR1110_MODEM_TEST_MODE_TST_NOP                         = 0x01,
    LR1110_MODEM_TEST_MODE_TST_TX_SINGLE                   = 0x02,
    LR1110_MODEM_TEST_MODE_TST_TX_CONT                     = 0x03,
    LR1110_MODEM_TEST_MODE_TST_CW                          = 0x06,
    LR1110_MODEM_TEST_MODE_TST_RX_CONT                     = 0x07,
    LR1110_MODEM_TEST_MODE_TST_RSSI_SUBGHZ                 = 0x08,
    LR1110_MODEM_TEST_MODE_TST_RADIO_RST                   = 0x09,
    LR1110_MODEM_TEST_MODE_TST_EXIT                        = 0x0B,
    LR1110_MODEM_TEST_MODE_TST_TX_SINGLE_PREAM             = 0x14,
    LR1110_MODEM_TEST_MODE_READ_RSSI                       = 0x15,
    LR1110_MODEM_TEST_MODE_TST_RSSI_2G4                    = 0x16,
    LR1110_MODEM_TEST_MODE_TST_RSSI_GNSS                   = 0x17,
    LR1110_MODEM_TEST_MODE_TST_READ_RX_PKT_COUNTER_RX_CONT = 0x18,
} lr1110_modem_test_mode_t;

/*!
 * @brief Spreading factor for test mode
 */
typedef enum
{
    LR1110_MODEM_TST_MODE_FSK  = 0x00,
    LR1110_MODEM_TST_MODE_SF7  = 0x01,
    LR1110_MODEM_TST_MODE_SF8  = 0x02,
    LR1110_MODEM_TST_MODE_SF9  = 0x03,
    LR1110_MODEM_TST_MODE_SF10 = 0x04,
    LR1110_MODEM_TST_MODE_SF11 = 0x05,
    LR1110_MODEM_TST_MODE_SF12 = 0x06,
} lr1110_modem_tst_mode_sf_t;

/*!
 * @brief Bandwidth for test mode
 */
typedef enum
{
    LR1110_MODEM_TST_MODE_125_KHZ = 0x00,
    LR1110_MODEM_TST_MODE_250_KHZ = 0x01,
    LR1110_MODEM_TST_MODE_500_KHZ = 0x02,
    LR1110_MODEM_TST_MODE_12_MHZ  = 0x0F,
    LR1110_MODEM_TST_MODE_18_MHZ  = 0x10,
    LR1110_MODEM_TST_MODE_24_MHZ  = 0x11,
} lr1110_modem_tst_mode_bw_t;

/*!
 * @brief Coding rate for test mode
 */
typedef enum
{
    LR1110_MODEM_TST_MODE_4_5 = 0x00,
    LR1110_MODEM_TST_MODE_4_6 = 0x01,
    LR1110_MODEM_TST_MODE_4_7 = 0x02,
    LR1110_MODEM_TST_MODE_4_8 = 0x03,
} lr1110_modem_tst_mode_cr_t;

/*!
 * @brief Coding rate for test mode
 */
typedef enum
{
    LR1110_MODEM_TST_MODE_CONSTELLATION_GNSS   = 0x00,
    LR1110_MODEM_TST_MODE_CONSTELLATION_BEIDOU = 0x01,
} lr1110_modem_tst_mode_constellation_t;

/*!
 * @brief Encryption mode values
 */
typedef enum
{
    LR1110_MODEM_SERVICES_ENCRYPTION_DISABLE = 0x00,
    LR1110_MODEM_SERVICES_ENCRYPTION_ENABLE  = 0x01,
} lr1110_modem_encryption_mode_t;

/*!
 * @brief LoRaWAN state values
 */
typedef enum
{
    LR1110_MODEM_LORAWAN_IDLE = 0x00,
    LR1110_MODEM_LORAWAN_BUSY = 0x01
} lr1110_modem_lorawan_state_t;

/*!
 * @brief TX status values
 */
typedef enum
{
    LR1110_MODEM_TX_ERROR       = 0x00,
    LR1110_MODEM_UNCONFIRMED_TX = 0x01,
    LR1110_MODEM_CONFIRMED_TX   = 0x02,
} lr1110_modem_tx_done_event_t;

/*!
 * @brief RX flags encoding
 */
typedef enum
{
    LR1110_MODEM_DOWN_DATA_EVENT_DNW1 = 0x01,  //!< received in 1st DN slot
    LR1110_MODEM_DOWN_DATA_EVENT_DNW2 = 0x02,  //!< received in 2dn DN slot
    LR1110_MODEM_DOWN_DATA_EVENT_RXC  = 0x03,  //!< received in Class C DN slot
} lr1110_modem_down_data_flag_t;

/*!
 * @brief Upload status values
 */
typedef enum
{
    LR1110_MODEM_UPLOAD_ERROR   = 0x00,
    LR1110_MODEM_UPLOAD_SUCCESS = 0x01,
} lr1110_modem_upload_event_t;

/*!
 * @brief Modem charge type
 */
typedef enum
{
    LR1110_MODEM_CHARGE_TYPE_MODEM        = 0x00,
    LR1110_MODEM_CHARGE_TYPE_USER_DEFINED = 0x01,
} lr1110_modem_charge_type_t;

/*!
 * @brief LoRaWAN Duty Cycle activation type
 */
typedef enum
{
    LR1110_MODEM_DUTY_CYCLE_DISABLE = 0x00,
    LR1110_MODEM_DUTY_CYCLE_ENABLE  = 0x01,
} lr1110_modem_duty_cycle_t;

/*!
 * @brief LoRaWAN Duty Cycle activation type
 */
typedef enum
{
    LR1110_MODEM_CERTIFICATION_MODE_DISABLE = 0x00,
    LR1110_MODEM_CERTIFICATION_MODE_ENABLE  = 0x01,
} lr1110_modem_certification_mode_t;

/*!
 * @brief ALC Sync service activation mode
 */
typedef enum
{
    LR1110_MODEM_ALC_SYNC_MODE_DISABLE = 0x00,
    LR1110_MODEM_ALC_SYNC_MODE_ENABLE  = 0x01,
} lr1110_modem_alc_sync_mode_t;

/*!
 * @brief ALC Sync state
 */
typedef enum
{
    LR1110_MODEM_ALC_SYNC_DESYNCHRONIZED = 0x00,
    LR1110_MODEM_ALC_SYNC_SYNCHRONIZED   = 0x01,
} lr1110_modem_alc_sync_state_t;

/*!
 * @brief Modem mute type
 */
typedef enum
{
    LR1110_MODEM_UNMUTED = 0x00,
    LR1110_MODEM_MUTED   = 0x01,
} lr1110_modem_mute_t;

/*!
 * @brief Modem suspend type
 */
typedef enum
{
    LR1110_MODEM_RESUMED = 0x00,
    LR1110_MODEM_SUSPEND = 0x01,
} lr1110_modem_suspend_t;

/**
 * @brief Modem set conf type
 */
typedef enum
{
    LR1110_MODEM_EVENT_SETCONF_ADR_MODE_UPDATED    = LR1110_MODEM_DM_INFO_TYPE_ADR_MODE,
    LR1110_MODEM_EVENT_SETCONF_JOIN_EUI_UPDATED    = LR1110_MODEM_DM_INFO_TYPE_JOIN_EUI,
    LR1110_MODEM_EVENT_SETCONF_DM_INTERVAL_UPDATED = LR1110_MODEM_DM_INFO_TYPE_INTERVAL,
} lr1110_modem_event_setconf_tag_t;

/*!
 * @brief Ramping time for PA
 *
 * This parameter is the ramping time of the PA. A high value improves spectral quality.
 */
typedef enum
{
    LR1110_MODEM_RAMP_16_US  = 0x00,  //!< 16 us Ramp Time
    LR1110_MODEM_RAMP_32_US  = 0x01,  //!< 32 us Ramp Time
    LR1110_MODEM_RAMP_48_US  = 0x02,  //!< 48 us Ramp Time (Default)
    LR1110_MODEM_RAMP_64_US  = 0x03,  //!< 64 us Ramp Time
    LR1110_MODEM_RAMP_80_US  = 0x04,  //!< 80 us Ramp Time
    LR1110_MODEM_RAMP_96_US  = 0x05,  //!< 96 us Ramp Time
    LR1110_MODEM_RAMP_112_US = 0x06,  //!< 112 us Ramp Time
    LR1110_MODEM_RAMP_128_US = 0x07,  //!< 128 us Ramp Time
    LR1110_MODEM_RAMP_144_US = 0x08,  //!< 144 us Ramp Time
    LR1110_MODEM_RAMP_160_US = 0x09,  //!< 160 us Ramp Time
    LR1110_MODEM_RAMP_176_US = 0x0A,  //!< 176 us Ramp Time
    LR1110_MODEM_RAMP_192_US = 0x0B,  //!< 192 us Ramp Time
    LR1110_MODEM_RAMP_208_US = 0x0C,  //!< 208 us Ramp Time
    LR1110_MODEM_RAMP_240_US = 0x0D,  //!< 240 us Ramp Time
    LR1110_MODEM_RAMP_272_US = 0x0E,  //!< 272 us Ramp Time
    LR1110_MODEM_RAMP_304_US = 0x0F,  //!< 304 us Ramp Time
} lr1110_modem_ramp_time_t;

/*!
 * @brief Select power amplifier supply source
 */
typedef enum
{
    LR1110_MODEM_PA_REG_SUPPLY_VREG = 0x00,  //!< Power amplifier supplied by the main regulator
    LR1110_MODEM_PA_REG_SUPPLY_VBAT = 0x01   //!< Power amplifier supplied by the battery
} lr1110_modem_pa_reg_supply_t;

/*!
 * @brief Select the LoRaWAN network type
 */
typedef enum
{
    LR1110_MODEM_LORAWAN_PRIVATE_NETWORK = 0x00,  //!< LoRaWAN private network
    LR1110_MODEM_LORAWAN_PUBLIC_NETWORK  = 0x01   //!< LoRaWAN public network
} lr1110_modem_network_type_t;

/*!
 * @brief Listen Before Talk (LBT) activation type
 */
typedef enum
{
    LR1110_MODEM_LBT_MODE_DISABLE = 0x00,
    LR1110_MODEM_LBT_MODE_ENABLE  = 0x01,
} lr1110_modem_lbt_mode_t;

/*!
 * @brief modem event fields structure
 */
typedef struct
{
    uint8_t   event_type;           //!< Event type
    uint8_t   missed_events_count;  //!< Counter of missed events of type event_type
    uint8_t   buffer[LR1110_MODEM_EVENT_MAX_LENGTH_BUFFER];  //!< Buffer if the current event
    uint16_t  buffer_len;                                    //!< Length of buffer
} lr1110_modem_event_fields_t;

/*!
 * @brief LR1110 modem version structure
 */
typedef struct
{
    uint32_t  bootloader;     //!< Bootloader version
    uint8_t   functionality;  //!< Functionality identifier
    uint32_t  firmware;       //!< Firmware version
    uint16_t  lorawan;        //!< LoRaWAN version
} lr1110_modem_version_t;

/*!
 * @brief DM info fields structure
 *
 * @remark The array dm_info_field is to be populated with values from lr1110_modem_dm_info_type_t
 */
typedef struct
{
    uint8_t  dm_info_field[20];  //!< Array of DM info field values
    uint16_t dm_info_length;     //!< Length of the DM info field array
} lr1110_modem_dm_info_fields_t;

/*!
 * @brief stream status structure
 */
typedef struct
{
    uint16_t pending;  //!< number of bytes pending for transmission
    uint16_t free;     //!< number of bytes still free in the buffer
} lr1110_modem_stream_status_t;

/*!
 * @brief Output Power Config structure
 *
 * @ref pa_duty_cycle controls the duty cycle of Power Amplifier according to:
 * \f$ dutycycle = 0.2 + 0.04 \times pa_duty_cycle \f$
 * It can be used to adapt the TX multi-band operation using a single-matching network.
 *
 * The allowed duty cycle values for LPA are from 0.2 to 0.48 (by step of 0.04). Therefore possible values for
 * pa_duty_cycle go from 0 to 7.
 *
 * The allowed duty cycle values for HPA go from 0.2 to 0.36 (by step of 0.04). Therefore in this case, the possible
 * values for pa_duty_cycle go from 0 to 4.
 *
 * @ref pa_hp_sel controls the number of slices for HPA according to: \f$ \#slices = pa_hp_sel + 1 \f$
 */
typedef struct
{
    uint8_t     expected_power;    //!< Expected power in dBm
    uint8_t     configured_power;  //!< Configured power in dBm
    uint8_t     pa_sel;            //!< Power Amplifier selection
    uint8_t     pa_supply;         //!< Power Amplifier regulator supply source
    uint8_t     pa_duty_cycle;     //!< Power Amplifier duty cycle (Default 0x04)
    uint8_t     pa_hp_sel;         //!< Number of slices for HPA (Default 0x07)
    uint8_t     pa_ramp_time;      //!< Power amplifier ramp time
} lr1110_modem_output_power_config_t;

/*!
 * @brief Chip EUI type
 */
typedef uint8_t lr1110_modem_chip_eui_t[LR1110_MODEM_CHIP_EUI_LENGTH];

/*!
 * @brief Join EUI type
 */
typedef uint8_t lr1110_modem_join_eui_t[LR1110_MODEM_JOIN_EUI_LENGTH];

/*!
 * @brief Device EUI type
 */
typedef uint8_t lr1110_modem_dev_eui_t[LR1110_MODEM_DEV_EUI_LENGTH];

/*!
 * @brief Application key type
 */
typedef uint8_t lr1110_modem_app_key_t[LR1110_MODEM_APP_KEY_LENGTH];

/*!
 * @brief LoRaWAN list of regions type
 */
typedef lr1110_modem_regions_t lr1110_modem_regions_list_t[LR1110_MODEM_REGIONS_NUMBER];

/*!
 * @brief Output power config type
 */
typedef lr1110_modem_output_power_config_t
    lr1110_modem_output_power_config_list_t[LR1110_MODEM_NB_OUTPUT_POWER_CONFIG_BLOCKS];

#ifdef __cplusplus
}
#endif

#endif  // LR1110_MODEM_LORAWAN_TYPES_H

/* --- EOF ------------------------------------------------------------------ */
