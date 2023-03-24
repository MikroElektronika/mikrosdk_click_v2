/*!
 * @file      lr1110_modem_wifi.h
 *
 * @brief     Wi-Fi passive scan driver definition for LR1110 modem
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

#ifndef LR1110_MODEM_WIFI_H
#define LR1110_MODEM_WIFI_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdbool.h>
#include <stdint.h>
#include "modem/lr1110_modem_wifi_types.h"
#include "modem/lr1110_modem_common.h"
#include "lriot.h"

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

/*!
 * @brief Reset the internal counters of cumulative timing
 *
 * @param [in] ctx Chip implementation context
 *
 * @returns Operation status
 */
err_t lr1110_modem_wifi_reset_cumulative_timing( lriot_t *ctx );

/*!
 * @brief Read the internal counters of cumulative timing
 *
 * @param [in] ctx Chip implementation context
 * @param [out] timing A pointer to the cumulative timing structure to populate
 *
 * @returns Operation status
 */
err_t lr1110_modem_wifi_read_cumulative_timing( lriot_t *ctx, lr1110_modem_wifi_cumulative_timings_t* timing );

/*!
 * @brief Configure the timestamp used to discriminate mobile access points from gateways.
 *
 * This filtering is based on the hypothesis that mobile access points have timestamp shorter than gateways.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] timestamp_in_s Timestamp value in second
 *
 * @returns Operation status
 */
err_t lr1110_modem_wifi_cfg_timestamp_ap_phone( lriot_t *ctx, uint32_t timestamp_in_s );

/*!
 * @brief Get the internal wifi firmware version
 *
 * @param [in] ctx Chip implementation context
 * @param [out] wifi_version The wifi version structure populated with version numbers
 *
 * @returns Operation status
 */
err_t lr1110_modem_wifi_read_version( lriot_t *ctx, lr1110_modem_wifi_version_t* wifi_version );

/*!
 * @brief Start a Wi-Fi passive scan operation
 *
 * During the complete passive scan operation, the LR1110 remains busy and cannot receive any commands. Using this
 * command **DOES** reset the results already obtained by previous passive scan operations.
 *
 * The result can be read at the end of the passive scan directly in the event and
 * lr1110_modem_wifi_read_basic_complete_results or lr1110_modem_wifi_read_basic_mac_type_channel_results to actually
 * get the result bytes.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] signal_type The type of Wi-Fi Signals to scan for. If LR1110_MODEM_WIFI_TYPE_SCAN_B_G_N is selected, the
 * LR1110 already starts by scanning all selected channels for Wi-Fi signals B. Then the LR1110 scans all selected
 * channels for Wi-Fi signals G/N.
 * @param [in] channels Mask of the Wi-Fi channels to scan
 * @param [in] scan_mode Scan mode to execute
 * @param [in] max_results The maximal number of results to gather. When this limit is reached, the passive scan
 * automatically stop. Range of allowed values is [1:32]. Note that value 0 is forbidden.
 * @param [in] nb_scan_per_channel The number of internal scan sequences per channel scanned. Range of accepted values
 * is [1:255]. Note that value 0 is forbidden.
 * @param [in] timeout_in_ms The maximal duration of a single preamble search. Expressed in ms. Range of allowed values
 * is [1:65535]. Note that value 0 is forbidden.
 * @param [in] abort_on_timeout If true, the beacon search jumps to next configured Wi-Fi channel (or stop if there is
 * no more channel to scan) as soon as a search timeout is encountered
 * @param [in] result_format scanner result format \see lr1110_modem_wifi_result_format_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_wifi_passive_scan( lriot_t *ctx, lr1110_modem_wifi_signal_type_scan_t signal_type,
                                      lr1110_modem_wifi_channel_mask_t channels, lr1110_modem_wifi_mode_t scan_mode,
                                      uint8_t max_results, uint8_t nb_scan_per_channel, uint16_t timeout_in_ms,
                                      bool abort_on_timeout, lr1110_modem_wifi_result_format_t result_format );

/*!
 * @brief Start a Wi-Fi passive scan operation with duration stop conditions
 *
 * This passive scan API does not require the number of scan per channel, so
 * that it searches for Wi-Fi signals until it finds one, or until the
 * exhaustion of timeout_per_scan_ms or timeout_per_channel_ms.
 *
 * The maximal duration of a scan is determined by the number of channels to scan times the timeout_per_channel_ms
 * configured. However, this duration may be exceeded depending on the crystal drift of the clock source and on the
 * instant the last Wi-Fi signal is detected by the device.
 * Therefore the maximal duration of a Wi-Fi scan with this API is provided by the following equations:
 *
 * For signal type being `LR1110_MODEM_WIFI_TYPE_SCAN_B`, `LR1110_MODEM_WIFI_TYPE_SCAN_G` or
 * `LR1110_MODEM_WIFI_TYPE_SCAN_N`:
 *
 * \f$ T_{max} = N_{channel} \times ((1 + Xtal_{precision})timeout\_per\_channel + T_{offset} ) \f$
 *
 * \f$ Xtal_{precision} \f$ depends on the crystal used as clock source.
 * If the clock source is configured with 32kHz internal RC, then \f$ Xtal_{precision} = 1/100 \f$
 *
 * \f$ T_{offset} \f$ depends on the \f$ signal\_type \f$ and the \f$scan\_mode\f$ selected:
 *
 *   - LR1110_MODEM_WIFI_TYPE_SCAN_B:
 *     - if \f$scan\_mode != LR1110\_MODEM\_WIFI\_SCAN\_MODE\_FULL\_BEACON\f$: 2.31 ms
 *     - if \f$scan\_mode == LR1110\_MODEM\_WIFI\_SCAN\_MODE\_FULL\_BEACON\f$: 9.59 ms
 *   - LR1110_MODEM_WIFI_TYPE_SCAN_G:
 *     - if \f$scan\_mode != LR1110\_MODEM\_WIFI\_SCAN\_MODE\_FULL\_BEACON\f$: 52.55 ms
 *     - if \f$scan\_mode == LR1110\_MODEM\_WIFI\_SCAN\_MODE\_FULL\_BEACON\f$: N/A
 *
 * For signal type being `LR1110_MODEM_WIFI_TYPE_SCAN_B_G_N`:
 *
 * \f$ T_{max} = 2 \times N_{channel} \times (1 + Xtal_{precision})timeout\_per\_channel + T_{offset} \f$
 *
 * \f$ T_{offset} \f$ depends on the \f$scan\_mode\f$ selected:
 * - \f$scan\_mode != LR1110\_MODEM\_WIFI\_SCAN\_MODE\_FULL\_BEACON\f$: 54.86 ms
 * - \f$scan\_mode == LR1110\_MODEM\_WIFI\_SCAN\_MODE\_FULL\_BEACON\f$: 9.59 ms.
 *
 * @note With \f$scan\_mode != LR1110\_MODEM\_WIFI\_SCAN\_MODE\_FULL\_BEACON\f$ the T_offset is actually the worst case
 * of Wi-Fi type B and Wi-Fi type G/N. Moreover, the Wi-Fi types G and N are scanned within the same steps (it is not
 * two different scans). So the T_offset is the addition of 2.31 + 52.55 = 54.86.
 *
 * @note With \f$scan\_mode == LR1110\_MODEM\_WIFI\_SCAN\_MODE\_FULL\_BEACON\f$, only Wi-Fi types B can be scanned. So
 * scans for Wi-Fi types G/N are silently discarded. Therefore the T_offset is the same as for scan with Wi-Fi type B.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] signal_type The type of Wi-Fi Signals to scan for. If LR1110_MODEM_WIFI_TYPE_SCAN_B_G_N is selected, the
 * LR1110 already starts by scanning all selected channels for Wi-Fi signals B. Then the LR1110 scans all selected
 * channels for Wi-Fi signals G/N.
 * @param [in] channels Mask of the Wi-Fi channels to scan
 * @param [in] scan_mode Scan mode to execute
 * @param [in] max_results The maximal number of results to gather. When this
 * limit is reached, the passive scan automatically stop. Maximal value is 32
 * @param [in] timeout_per_channel_ms The time to spend scanning one channel. Expressed in ms. Value 0 is forbidden.
 * @param [in] timeout_per_scan_ms The maximal time to spend in preamble detection for each single scan. The time spent
 * on preamble search is reset at each new preamble search. If the time spent on preamble search reach this timeout, the
 * scan on the current channel stops and start on next channel. If set to 0, the command will keep listening until
 * exhaustion of timeout_per_channel_ms or until nb_max_results is reached. Expressed in ms. Range of allowed values is
 * [0:65535].
 * @param [in] result_format scanner result format \see lr1110_modem_wifi_result_format_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_wifi_passive_scan_time_limit( lriot_t *ctx, lr1110_modem_wifi_signal_type_scan_t signal_type,
                                                 lr1110_modem_wifi_channel_mask_t channels, lr1110_modem_wifi_mode_t scan_mode,
                                                 uint8_t max_results, uint16_t timeout_per_channel_ms, uint16_t timeout_per_scan_ms,
                                                 lr1110_modem_wifi_result_format_t result_format );

/*!
 * @brief Start a Wi-Fi passive scan for country codes extraction
 *
 * This command starts a Wi-Fi passive scan operation for Beacons and Probe Responses on Wi-Fi type B only. It is to be
 * used to extract the Country Code fields.
 *
 * During the passive scan, the results are filtered to keep only single MAC addresses.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] channels_mask Mask of the Wi-Fi channels to scan
 * @param [in] nb_max_results The maximum number of country code to gather. When this limit is reached, the passive scan
 * automatically stops. Maximal value is 32
 * @param [in] nb_scan_per_channel Maximal number of scan attempts per channel. Maximal value is 255
 * @param [in] timeout_in_ms The maximal duration of a single beacon search. Expressed in ms. Maximal value is 65535 ms
 * @param [in] abort_on_timeout If true, the beacon search jumps to next configured Wi-Fi channel (or stop if there is
 * no more channel to scan) as soon as a search timeout is encountered
 *
 * @returns Operation status
 */
err_t lr1110_modem_wifi_search_country_code( lriot_t *ctx, lr1110_modem_wifi_channel_mask_t channels_mask,
                                             uint8_t nb_max_results, uint8_t nb_scan_per_channel, 
                                             uint16_t timeout_in_ms, bool abort_on_timeout );

/*!
 * @brief Start a Wi-Fi passive scan for country codes extraction with duration stop conditions
 *
 * This command starts a Wi-Fi passive scan operation for Beacons and Probe Responses on Wi-Fi type B only. It is to be
 * used to extract the Country Code fields.
 * This passive scan API does not require the number of scan per channel, so that it searches for Wi-Fi signals until it
 * finds one, or until the exhaustion of timeout_per_scan_ms or timeout_per_channel_ms.
 *
 * The maximal duration of a scan is determined by the number of channels to scan times the timeout_per_channel_ms
 * configured. However, this duration may be exceeded depending on the crystal drift of the clock source and on the
 * instant the last Wi-Fi signal is detected by the device.
 * Therefore the maximal duration of a Wi-Fi scan with this API is provided by the following equation:
 *
 * \f$ T_{max} = N_{channel} \times ((1 + Xtal_{precision})timeout\_per\_channel + T_{offset} ) \f$
 *
 * \f$ Xtal_{precision} \f$ depends on the crystal used as clock source.
 * If the clock source is configured with 32kHz internal RC, then \f$ Xtal_{precision} = 1/100 \f$
 *
 * \f$ T_{offset} \f$ is always the same: 9.59 ms.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] channels_mask Mask of the Wi-Fi channels to scan
 * @param [in] nb_max_results The maximum number of country code to gather. When this limit is reached, the passive scan
 * automatically stops. Maximal value is 32
 * @param [in] timeout_per_channel_ms The time to spend scanning one channel. Expressed in ms. Value 0 is forbidden.
 * @param [in] timeout_per_scan_ms The maximal time to spend in preamble detection for each single scan. The time spent
 * on preamble search is reset at each new preamble search. If the time spent on preamble search reach this timeout, the
 * scan on the current channel stops and start on next channel. If set to 0, the command will keep listening until
 * exhaustion of timeout_per_channel_ms or until nb_max_results is reached. Expressed in ms. Range of allowed values is
 * [0:65535].
 *
 * @returns Operation status
 */
err_t lr1110_modem_wifi_search_country_code_time_limit( lriot_t *ctx, lr1110_modem_wifi_channel_mask_t channels_mask, 
                                                        uint8_t nb_max_results, uint16_t timeout_per_channel_ms, 
                                                        uint16_t timeout_per_scan_ms );

/*!
 * @brief Read basic MAC, Wi-Fi type and channel results
 *
 * This function is to be used when interpreting the buffer corresponding to the event
 * LR1110_MODEM_LORAWAN_EVENT_WIFI_SCAN_DONE. It does not fetch the result from LR1110 Modem-E but it interpret the
 * buffer already obtained by reading the event with lr1110_modem_get_event.
 *
 * @remark: This result fetching function **MUST** be used only if the scan function call was made with Scan Mode set to
 * LR1110_MODEM_WIFI_SCAN_MODE_BEACON or LR1110_MODEM_WIFI_SCAN_MODE_BEACON_AND_PKT.
 *
 * @param [in] buffer Buffer containing the raw data
 * @param [in] buffer_len Size of the raw data buffer
 * @param [out] results Pointer to an array of result structures to populate. It is up to the caller to ensure this
 * array can hold at least nb_results elements.
 * @param [out] nb_results Number of results read
 */
void lr1110_modem_wifi_read_basic_mac_type_channel_results( uint8_t* buffer, uint16_t buffer_len,
                                                            lr1110_modem_wifi_basic_mac_type_channel_result_t* results,
                                                            uint8_t* nb_results );

/*!
 * @brief Read basic complete results
 *
 * This function is to be used when interpreting the buffer corresponding to the event
 * LR1110_MODEM_LORAWAN_EVENT_WIFI_SCAN_DONE. It does not fetch the result from LR1110 Modem-E but it interpret the
 * buffer already obtained by reading the event with lr1110_modem_get_event.
 *
 * @remark: This result fetching function **MUST** be used only if the scan function call was made with Scan Mode set to
 * LR1110_MODEM_WIFI_SCAN_MODE_BEACON or LR1110_MODEM_WIFI_SCAN_MODE_BEACON_AND_PKT.
 *
 * @param [in] buffer Buffer containing the raw data
 * @param [in] buffer_len Size of the raw data buffer
 * @param [out] results Pointer to an array of result structures to populate. It is up to the caller to ensure this
 * array can hold at least nb_results elements.
 * @param [out] nb_results Number of results read
 */
void lr1110_modem_wifi_read_basic_complete_results( uint8_t* buffer, uint16_t buffer_len,
                                                    lr1110_modem_wifi_basic_complete_result_t* results,
                                                    uint8_t* nb_results );

/*!
 * @brief Read extended complete results
 *
 * This function is to be used when interpreting the buffer corresponding to the event
 * LR1110_MODEM_LORAWAN_EVENT_WIFI_SCAN_DONE. It does not fetch the result from LR1110 Modem-E but it interpret the
 * buffer already obtained by reading the event with lr1110_modem_get_event.
 *
 * @param [in] buffer Buffer containing the raw data
 * @param [in] buffer_len Size of the raw data buffer
 * @param [out] results Pointer to an array of result structures to populate. It is up to the caller to ensure this
 * array can hold at least nb_results elements.
 * @param [out] nb_results Number of results read
 */
void lr1110_modem_wifi_read_extended_full_results( uint8_t* buffer, uint16_t buffer_len,
                                                   lr1110_modem_wifi_extended_full_result_t* results,
                                                   uint8_t* nb_results );

/*!
 * @brief Helper method to retrieve channel from channel info byte
 *
 * @param [in] info_byte The chanel info byte from passive scan result
 *
 * @returns The channel of scanned MAC address
 */
err_t lr1110_modem_extract_channel_from_info_byte( lr1110_modem_wifi_channel_info_byte_t info_byte );

/*!
 * @brief Helper method to retrieve the signal type from data rate info byte
 *
 * @param [in] data_rate_info The data rate info byte from a passive scan result
 *
 * @returns The Signal Type of the scanned frame
 */
err_t lr1110_modem_extract_signal_type_from_data_rate_info( lr1110_modem_wifi_datarate_info_byte_t data_rate_info );

#ifdef __cplusplus
}
#endif

#endif  // LR1110_MODEM_WIFI_H

/* --- EOF ------------------------------------------------------------------ */
