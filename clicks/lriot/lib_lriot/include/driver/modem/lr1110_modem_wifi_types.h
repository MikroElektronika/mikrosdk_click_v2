/*!
 * @file      lr1110_modem_wifi_types.h
 *
 * @brief     Wi-Fi passive scan driver types definition for LR1110 modem
 *
 * Revised BSD License
 * Copyright Semtech Corporation 2020. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Semtech corporation nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LR1110_MODEM_WIFI_TYPES_H
#define LR1110_MODEM_WIFI_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdbool.h>
#include <stdint.h>

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/*!
 * @brief Length of SSID field (in bytes)
 */
#define LR1110_MODEM_WIFI_RESULT_SSID_LENGTH ( 32 )

/*!
 * @brief Maximal number of basic results
 */
#define LR1110_MODEM_WIFI_MAX_RESULTS ( 32 )

/*!
 * @brief Length of MAC address field (in bytes)
 */
#define LR1110_MODEM_WIFI_MAC_ADDRESS_LENGTH ( 6 )

/*!
 * @brief Length of country code field (in bytes)
 */
#define LR1110_MODEM_WIFI_STR_COUNTRY_CODE_SIZE ( 2 )

#define LR1110_MODEM_WIFI_CHANNEL_1_POS ( 0U )  //!< Channel at frequency 2.412 GHz
#define LR1110_MODEM_WIFI_CHANNEL_1_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_1_POS )
#define LR1110_MODEM_WIFI_CHANNEL_2_POS ( 1U )  //!< Channel at frequency 2.417 GHz
#define LR1110_MODEM_WIFI_CHANNEL_2_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_2_POS )
#define LR1110_MODEM_WIFI_CHANNEL_3_POS ( 2U )  //!< Channel at frequency 2.422 GHz
#define LR1110_MODEM_WIFI_CHANNEL_3_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_3_POS )
#define LR1110_MODEM_WIFI_CHANNEL_4_POS ( 3U )  //!< Channel at frequency 2.427 GHz
#define LR1110_MODEM_WIFI_CHANNEL_4_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_4_POS )
#define LR1110_MODEM_WIFI_CHANNEL_5_POS ( 4U )  //!< Channel at frequency 2.432 GHz
#define LR1110_MODEM_WIFI_CHANNEL_5_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_5_POS )
#define LR1110_MODEM_WIFI_CHANNEL_6_POS ( 5U )  //!< Channel at frequency 2.437 GHz
#define LR1110_MODEM_WIFI_CHANNEL_6_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_6_POS )
#define LR1110_MODEM_WIFI_CHANNEL_7_POS ( 6U )  //!< Channel at frequency 2.442 GHz
#define LR1110_MODEM_WIFI_CHANNEL_7_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_7_POS )
#define LR1110_MODEM_WIFI_CHANNEL_8_POS ( 7U )  //!< Channel at frequency 2.447 GHz
#define LR1110_MODEM_WIFI_CHANNEL_8_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_8_POS )
#define LR1110_MODEM_WIFI_CHANNEL_9_POS ( 8U )  //!< Channel at frequency 2.452 GHz
#define LR1110_MODEM_WIFI_CHANNEL_9_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_9_POS )
#define LR1110_MODEM_WIFI_CHANNEL_10_POS ( 9U )  //!< Channel at frequency 2.457 GHz
#define LR1110_MODEM_WIFI_CHANNEL_10_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_10_POS )
#define LR1110_MODEM_WIFI_CHANNEL_11_POS ( 10U )  //!< Channel at frequency 2.462 GHz
#define LR1110_MODEM_WIFI_CHANNEL_11_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_11_POS )
#define LR1110_MODEM_WIFI_CHANNEL_12_POS ( 11U )  //!< Channel at frequency 2.467 GHz
#define LR1110_MODEM_WIFI_CHANNEL_12_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_12_POS )
#define LR1110_MODEM_WIFI_CHANNEL_13_POS ( 12U )  //!< Channel at frequency 2.472 GHz
#define LR1110_MODEM_WIFI_CHANNEL_13_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_13_POS )
#define LR1110_MODEM_WIFI_CHANNEL_14_POS ( 13U )  //!< Channel at frequency 2.484 GHz
#define LR1110_MODEM_WIFI_CHANNEL_14_MASK ( 0x01UL << LR1110_MODEM_WIFI_CHANNEL_14_POS )

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*!
 * @brief Wi-Fi Channels index
 */
typedef enum
{
    LR1110_MODEM_WIFI_NO_CHANNEL   = 0x00,
    LR1110_MODEM_WIFI_CHANNEL_1    = 0x01,  //!< Channel at frequency 2.412 GHz
    LR1110_MODEM_WIFI_CHANNEL_2    = 0x02,  //!< Channel at frequency 2.417 GHz
    LR1110_MODEM_WIFI_CHANNEL_3    = 0x03,  //!< Channel at frequency 2.422 GHz
    LR1110_MODEM_WIFI_CHANNEL_4    = 0x04,  //!< Channel at frequency 2.427 GHz
    LR1110_MODEM_WIFI_CHANNEL_5    = 0x05,  //!< Channel at frequency 2.432 GHz
    LR1110_MODEM_WIFI_CHANNEL_6    = 0x06,  //!< Channel at frequency 2.437 GHz
    LR1110_MODEM_WIFI_CHANNEL_7    = 0x07,  //!< Channel at frequency 2.442 GHz
    LR1110_MODEM_WIFI_CHANNEL_8    = 0x08,  //!< Channel at frequency 2.447 GHz
    LR1110_MODEM_WIFI_CHANNEL_9    = 0x09,  //!< Channel at frequency 2.452 GHz
    LR1110_MODEM_WIFI_CHANNEL_10   = 0x0A,  //!< Channel at frequency 2.457 GHz
    LR1110_MODEM_WIFI_CHANNEL_11   = 0x0B,  //!< Channel at frequency 2.462 GHz
    LR1110_MODEM_WIFI_CHANNEL_12   = 0x0C,  //!< Channel at frequency 2.467 GHz
    LR1110_MODEM_WIFI_CHANNEL_13   = 0x0D,  //!< Channel at frequency 2.472 GHz
    LR1110_MODEM_WIFI_CHANNEL_14   = 0x0E,  //!< Channel at frequency 2.484 GHz
    LR1110_MODEM_WIFI_ALL_CHANNELS = 0x0F,
} lr1110_modem_wifi_channel_t;

/*!
 * @brief Wi-Fi signal type for passive scanning configuration
 *
 * Note it is not possible to configure the Wi-Fi passive scanning to search Wi-Fi type N GreenField. Only Wi-Fi type N
 * Mixed Mode can be scanned by LR1110.
 *
 * @warning LR1110_WIFI_TYPE_SCAN_G and LR1110_WIFI_TYPE_SCAN_N configurations are implemented the same way, and both
 * will scan Wi-Fi type G **AND** Wi-Fi type N.
 */
typedef enum
{
    LR1110_MODEM_WIFI_TYPE_SCAN_B     = 0x01,  //!< WiFi B
    LR1110_MODEM_WIFI_TYPE_SCAN_G     = 0x02,  //!< WiFi G
    LR1110_MODEM_WIFI_TYPE_SCAN_N     = 0x03,  //!< WiFi N
    LR1110_MODEM_WIFI_TYPE_SCAN_B_G_N = 0x04,  //!< Scan WiFi B and WiFi G/N
} lr1110_modem_wifi_signal_type_scan_t;

/*!
 * @brief Wi-Fi signal type for passive scan results
 *
 * Note that the WiFi N detected is Wi-Fi N Mixed mode, and not GreenField.
 */
typedef enum
{
    LR1110_MODEM_WIFI_TYPE_RESULT_B = 0x01,  //!< WiFi B
    LR1110_MODEM_WIFI_TYPE_RESULT_G = 0x02,  //!< WiFi G
    LR1110_MODEM_WIFI_TYPE_RESULT_N = 0x03,  //!< WiFi N
} lr1110_modem_wifi_signal_type_result_t;

/*!
 * @brief Wi-Fi capture mode
 *
 * The result type available depends on the Wi-Fi capture mode selected when calling the Wi-Fi scan API as follows:
 *
 * <table>
 * <tr> <th> Scan Mode <th> Type/Sub-type selected <th> Corresponding read result function
 * <tr> <td> LR1110_MODEM_WIFI_SCAN_MODE_BEACON <td> Management/Beacon and Management/Probe Response <td rowspan="2">
 * @ref lr1110_modem_wifi_read_basic_complete_results, @ref lr1110_modem_wifi_read_basic_mac_type_channel_results <tr>
 * <td> LR1110_MODEM_WIFI_SCAN_MODE_BEACON_AND_PKT <td> Some from Management, Control and Data Types <tr> <td>
 * LR1110_MODEM_WIFI_SCAN_MODE_FULL_BEACON <td> Management/Beacon and Management/Probe Response <td> @ref
 * lr1110_modem_wifi_read_extended_full_results
 * </table>
 *
 * When the LR1110 receives a Wi-Fi frame, it starts demodulating it. Depending on the scan mode selected, only some
 * Wi-Fi frame type/sub-types are to be kept. The demodulation step is stopped as soon as the LR1110 detects the current
 * Wi-Fi frame is not of the required type/sub-types. This saves scan time and consumption.
 *
 * A Wi-Fi frame is never completely demodulated. The LR1110_MODEM_WIFI_SCAN_MODE_FULL_BEACON uses a special
 * configuration allowing to demodulate more fields (until Frame Check Sequence field), at a price of higher scan
 * duration and higher consumption.
 */
typedef enum
{
    LR1110_MODEM_WIFI_SCAN_MODE_BEACON =
        1,  //!< Exposes Beacons and Probe Responses Access Points frames until Period Beacon field (Basic result)
    LR1110_MODEM_WIFI_SCAN_MODE_BEACON_AND_PKT =
        2,  //!< Exposes some Management Access Points frames until Period Beacon field, and some other packets frame
            //!< until third Mac Address field (Basic result)
    LR1110_MODEM_WIFI_SCAN_MODE_FULL_BEACON =
        4,  //!< Exposes Beacons and Probes Responses Access Points frames until Frame Check Sequence (FCS) field
            //!< (Extended result). In this mode, only signal type LR1110_WIFI_TYPE_SCAN_B is executed and other signal
            //!< types are silently discarded.
} lr1110_modem_wifi_mode_t;

typedef enum
{
    LR1110_MODEM_WIFI_RESULT_FORMAT_BASIC_COMPLETE         = 0x01,
    LR1110_MODEM_WIFI_RESULT_FORMAT_BASIC_MAC_TYPE_CHANNEL = 0x04,
} lr1110_modem_wifi_result_format_t;

/*!
 * @brief Type to store a MAC address
 */
typedef uint8_t lr1110_modem_wifi_mac_address_t[LR1110_MODEM_WIFI_MAC_ADDRESS_LENGTH];

/*!
 * @brief Type for datarate info byte
 */
typedef uint8_t lr1110_modem_wifi_datarate_info_byte_t;

/*!
 * @brief Type for channel info byte
 */
typedef uint8_t lr1110_modem_wifi_channel_info_byte_t;

/*!
 * @brief Type for frame type info byte
 */
typedef uint8_t lr1110_modem_wifi_frame_type_info_byte_t;

/*!
 * @brief Type for channel mask
 */
typedef uint16_t lr1110_modem_wifi_channel_mask_t;

/*!
 * @brief Cumulative timings
 *
 * This structure is representing the cumulative time spent in the different modes of Wi-Fi passive scanning procedure.
 * Timing provided in [us].
 * */
typedef struct
{
    uint32_t rx_detection_us;    //!< Cumulative time spent during NFE or TOA
    uint32_t rx_correlation_us;  //!< Cumulative time spent during preamble detection
    uint32_t rx_capture_us;      //!< Cumulative time spent during signal acquisition
    uint32_t demodulation_us;    //!< Cumulative time spent during software
                                 //!< demodulation
} lr1110_modem_wifi_cumulative_timings_t;

/*!
 * @brief Wi-Fi FCS info byte
 */
typedef struct lr1110_modem_wifi_fcs_info_byte_s
{
    bool is_fcs_ok;       //!< True if the LR1110 has checked the FCS and the check succeeded
    bool is_fcs_checked;  //!< True if the LR1110 has checked the FCS
} lr1110_modem_wifi_fcs_info_byte_t;

/*!
 * @brief Basic complete result structure
 *
 * The beacon period is expressed in TU (Time Unit). 1 TU is 1024 microseconds.
 */
typedef struct
{
    lr1110_modem_wifi_datarate_info_byte_t   data_rate_info_byte;   //!< Datarate info byte
    lr1110_modem_wifi_channel_info_byte_t    channel_info_byte;     //!< Channel info byte
    int8_t                                   rssi;                  //!< RSSI of scanned signal
    lr1110_modem_wifi_frame_type_info_byte_t frame_type_info_byte;  //!< Frame type info byte
    lr1110_modem_wifi_mac_address_t          mac_address;           //!< MAC address
    int16_t                                  phi_offset;            //!< Phi offset
    uint32_t timestamp_us_high;  //!< Indicate the up-time of the Access Point transmitting the Beacon [us] - upper 32bits
    uint32_t timestamp_us_low;  //!< Indicate the up-time of the Access Point transmitting the Beacon [us] - lower 32bits
    uint16_t beacon_period_tu;  //!< Beacon period of the corresponding beacon received
} lr1110_modem_wifi_basic_complete_result_t;

/*!
 * @brief Basic MAC, type, channel result structure
 */
typedef struct
{
    lr1110_modem_wifi_datarate_info_byte_t data_rate_info_byte;  //!< Datarate info byte
    lr1110_modem_wifi_channel_info_byte_t  channel_info_byte;    //!< Channel info byte
    int8_t                                 rssi;                 //!< RSSI of scanned signal
    lr1110_modem_wifi_mac_address_t        mac_address;          //!< MAC address
} lr1110_modem_wifi_basic_mac_type_channel_result_t;

/*!
 * @brief Extended full result structure
 *
 * The beacon period is expressed in TU (Time Unit). 1 TU is 1024 microseconds.
 */
typedef struct
{
    lr1110_modem_wifi_datarate_info_byte_t data_rate_info_byte;  //!< Datarate info byte
    lr1110_modem_wifi_channel_info_byte_t  channel_info_byte;    //!< Channel info byte
    int8_t                                 rssi;                 //!< RSSI of scanned signal
    uint8_t                                rate;                 //!< Rate index
    uint16_t                               service;              //!< Service value
    uint16_t                               length;  //!< Length of MPDU (in microseconds for WiFi B, bytes for WiFi G)
    uint16_t                               frame_control;  //!< Frame Control structure
    lr1110_modem_wifi_mac_address_t        mac_address_1;  //!< First MAC address of the frame
    lr1110_modem_wifi_mac_address_t        mac_address_2;  //!< Second MAC address of the frame
    lr1110_modem_wifi_mac_address_t        mac_address_3;  //!< Third MAC address of the frame
    uint32_t timestamp_us_high;  //!< Indicate the up-time of the Access Point transmitting the Beacon [us] - upper 32bits
    uint32_t timestamp_us_low;  //!< Indicate the up-time of the Access Point transmitting the Beacon [us] - lower 32bits
    uint16_t beacon_period_tu;
    uint16_t seq_control;                                       //!< Sequence Control value
    uint8_t  ssid_bytes[LR1110_MODEM_WIFI_RESULT_SSID_LENGTH];  //!< Service Set
                                                                //!< IDentifier
    uint8_t                           current_channel;          //!< Current channel indicated in the Wi-Fi frame
    uint16_t                          country_code;             //!< Country Code
    uint8_t                           io_regulation;            //!< Input Output Regulation
    lr1110_modem_wifi_fcs_info_byte_t fcs_check_byte;           //<! Frame Check Sequence info
    int16_t                           phi_offset;               //!< Phi offset
} lr1110_modem_wifi_extended_full_result_t;

/*!
 * @brief Wi-Fi version parameters
 */
typedef struct
{
    uint8_t major;  //!< Major version number
    uint8_t minor;  //!< Minor version number
} lr1110_modem_wifi_version_t;

#ifdef __cplusplus
}
#endif

#endif  // LR1110_MODEM_WIFI_TYPES_H

/* --- EOF ------------------------------------------------------------------ */
