/*!
 * @file      lr1110_modem_lorawan.h
 *
 * @brief     LoRaWAN driver for LR1110 modem
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

#ifndef LR1110_MODEM_LORAWAN_H
#define LR1110_MODEM_LORAWAN_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdbool.h>
#include <stdint.h>
#include "modem/lr1110_modem_lorawan_types.h"
#include "lriot.h"

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

/*!
 * @brief This command can be used to retrieve pending events from the modem. Pending events are indicated by the
 * EVENT line. The EVENT line will be de-asserted after all events have been retrieved and no further events are
 * available. When no event is available this command returns with empty response payload.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] event_fields \see lr1110_modem_event_fields_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_event( lriot_t *ctx, lr1110_modem_event_fields_t* event_fields );

/*!
 * @brief This command returns the version of the bootloader and the version of the installed firmware plus the version
 * of the implemented LoRaWAN standard (BCD, e.g. 0x0103 for LoRaWAN 1.0.3).
 *
 * @param [in] ctx Chip implementation context
 * @param [out] version Version of the LR1110 modem
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_version( lriot_t *ctx, lr1110_modem_version_t* version );

/*!
 * @brief This command performs a reset of the LR1110 modem. All transient state (including session information) will be
 * lost and the modem needs to join the network again.
 *
 * @param [in] ctx Chip implementation context
 *
 * @returns Operation status
 */
err_t lr1110_modem_reset( lriot_t *ctx );

/*!
 * @brief This command resets the accumulated charge counter to zero.
 *
 * @param [in] ctx Chip implementation context
 *
 * @returns Operation status
 */
err_t lr1110_modem_reset_charge( lriot_t *ctx );

/*!
 * @brief This command returns the total charge counter of the modem in mAh. This value includes the accumulated charge
 * since the last reset of the modem or since the last invocation of the ResetCharge command.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] charge Charge counter in mAh
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_charge( lriot_t *ctx, uint32_t* charge );

/*!
 * @brief This command gets the board-specific correction offset for transmission power to be used (signed integer in
 * dB).
 *
 * @param [in] ctx Chip implementation context
 * @param [out] tx_power_offset Tx power offset correction in dBm
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_tx_power_offset( lriot_t *ctx, int8_t* tx_power_offset );

/*!
 * @brief This command sets the board-specific correction offset for transmission power to be used. The offset depends
 * on the board design and antenna matching and is expressed in dB (signed integer).
 *
 * @param [in] ctx Chip implementation context
 * @param [in] tx_power_offset Tx power offset correction in dBm
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_tx_power_offset( lriot_t *ctx, int8_t tx_power_offset );

/*!
 * @brief This command is used to implement test functionality for regulatory conformance, certification, and functional
 * testing. With the exception of the TST_START command, test commands are only available if test mode is active. Test
 * mode can only be activated if the modem has not yet received a command that results in a radio operation. Once test
 * mode is active, all other modem commands are disabled.
 *
 * @param [in] ctx Chip implementation context
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_mode_start( lriot_t *ctx );

/*!
 * @brief No operation. This command may be used to terminate an ongoing continuous TX operation.
 *
 * @param [in] ctx Chip implementation context
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_nop( lriot_t *ctx );

/*!
 * @brief Transmit a single packet.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] frequency Frequency in Hz
 * @param [in] tx_power Tx power in dBm
 * @param [in] sf spreading factor @ref lr1110_modem_tst_mode_sf_t
 * @param [in] bw bandwidth @ref lr1110_modem_tst_mode_bw_t
 * @param [in] cr Coding Rate @ref lr1110_modem_tst_mode_cr_t
 * @param [in] payload_length Payload length
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_tx_single( lriot_t *ctx, uint32_t frequency, int8_t tx_power, 
                                   lr1110_modem_tst_mode_sf_t sf, lr1110_modem_tst_mode_bw_t bw,
                                   lr1110_modem_tst_mode_cr_t cr, uint8_t payload_length );

/*!
 * @brief Continuously transmit packets as fast as possible.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] frequency Frequency in Hz
 * @param [in] tx_power Tx power in dBm
 * @param [in] sf spreading factor @ref lr1110_modem_tst_mode_sf_t
 * @param [in] bw bandwidth @ref lr1110_modem_tst_mode_bw_t
 * @param [in] cr Coding Rate @ref lr1110_modem_tst_mode_cr_t
 * @param [in] payload_length Payload length
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_tx_cont( lriot_t *ctx, uint32_t frequency, int8_t tx_power,
                                 lr1110_modem_tst_mode_sf_t sf, lr1110_modem_tst_mode_bw_t bw,
                                 lr1110_modem_tst_mode_cr_t cr, uint8_t payload_length );

/*!
 * @brief Transmit a continuous wave.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] frequency Frequency in Hz
 * @param [in] tx_power Tx power in dBm
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_tx_cw( lriot_t *ctx, uint32_t frequency, int8_t tx_power );

/*!
 * @brief Continuously receive packets.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] frequency Frequency in Hz
 * @param [in] sf spreading factor @ref lr1110_modem_tst_mode_sf_t
 * @param [in] bw bandwidth @ref lr1110_modem_tst_mode_bw_t
 * @param [in] cr Coding Rate @ref lr1110_modem_tst_mode_cr_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_rx_cont( lriot_t *ctx, uint32_t frequency, lr1110_modem_tst_mode_sf_t sf, 
                                 lr1110_modem_tst_mode_bw_t bw, lr1110_modem_tst_mode_cr_t cr );

/*!
 * @brief Read the packet counter received during continuously receive packets test.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] rx_packet_counter The counter of packet received during RX continuous packet test
 *
 * @returns Operation status
 *
 * @see lr1110_modem_test_rx_cont
 */
err_t lr1110_modem_test_read_packet_counter_rx_cont( lriot_t *ctx, uint32_t* rx_packet_counter );

/*!
 * @brief Continuously receive packets on Sub-GHz radio path.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] frequency Frequency in Hz
 * @param [in] time_ms time in millisecond of the radio acquisition
 * @param [in] bw bandwidth @ref lr1110_modem_tst_mode_bw_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_rssi_subghz( lriot_t *ctx, uint32_t frequency, uint16_t time_ms, lr1110_modem_tst_mode_bw_t bw );

/*!
 * @brief Reset the LR1110 radio.
 *
 * @param [in] ctx Chip implementation context
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_radio_rst( lriot_t *ctx );

/*!
 * @brief Exit test mode and reset LR1110 modem.
 *
 * @param [in] ctx Chip implementation context
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_exit( lriot_t *ctx );

/*!
 * @brief Transmit a single packet with the number of preamble configurable.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] frequency Frequency in Hz
 * @param [in] tx_power Tx power in dBm
 * @param [in] sf spreading factor @ref lr1110_modem_tst_mode_sf_t
 * @param [in] bw bandwidth @ref lr1110_modem_tst_mode_bw_t
 * @param [in] cr Coding Rate @ref lr1110_modem_tst_mode_cr_t
 * @param [in] payload_length Payload length
 * @param [in] preamble_length Preamble Length
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_tx_single_preamble( lriot_t *ctx, uint32_t frequency, int8_t tx_power, lr1110_modem_tst_mode_sf_t sf,
                                            lr1110_modem_tst_mode_bw_t bw, lr1110_modem_tst_mode_cr_t cr,
                                            uint8_t payload_length, uint16_t preamble_length );

/*!
 * @brief Read RSSI after a Sub Gig / 2.4 Ghz / GNSS test rssi command.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] rssi RSSI in dBm
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_read_rssi( lriot_t *ctx, int8_t* rssi );

/*!
 * @brief Continuously receive packets on 2.4GHz radio path.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] channel Wi-Fi Channel from 1 to 14
 * @param [in] time_ms time in millisecond of the radio acquisition
 * @param [in] bw bandwidth @ref lr1110_modem_tst_mode_bw_t
 *
 * @note The allowed bandwidths are 12MHz and 24MH
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_rssi_2g4( lriot_t *ctx, uint8_t channel, uint16_t time_ms, lr1110_modem_tst_mode_bw_t bw );

/*!
 * @brief Continuously receive packets on GNSS radio path.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] constellation_modulation constellation used @ref lr1110_modem_tst_mode_constellation_t
 * @param [in] time_ms time in millisecond of the radio acquisition
 * @param [in] bw bandwidth @ref lr1110_modem_tst_mode_bw_t
 *
 * @note The allowed bandwidth is 12MHz
 *
 * @returns Operation status
 */
err_t lr1110_modem_test_rssi_gnss( lriot_t *ctx, lr1110_modem_tst_mode_constellation_t constellation_modulation, 
                                   uint16_t time_ms, lr1110_modem_tst_mode_bw_t bw );

/*!
 * @brief Query the current GPS time. The application layer clock synchronization protocol is used to link the device
 * clock to GPS time. The returned time specifies the seconds since GPS epoch (00:00:00, Sunday 6th of January 1980). If
 * the device is not yet synchronized to GPS time then the returned value is zero. This may happen if the server has not
 * yet answered time sync requests. The accuracy of the synchronization is in the range of seconds and depends on
 * latencies in the network infrastructure.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] time Time in seconds
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_gps_time( lriot_t *ctx, uint32_t* time );

/*!
 * @brief This command returns the modem status which may indicate one or more notification conditions.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] status LR1110 mode status but mask @ref lr1110_modem_status_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_status( lriot_t *ctx, lr1110_modem_status_t* status );

/*!
 * @brief This command sets an application alarm timer (in seconds). When the timer has expired an Alarm event is
 * generated. If this command is applied again before the timer has expired, the timer will be started again with the
 * new period. A value of 0 will cancel an possibly pending previous alarm timer.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] seconds Seconds
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_alarm_timer( lriot_t *ctx, uint32_t seconds );

/*!
 * @brief This command returns the device registration PIN
 *
 * @param [in] ctx Chip implementation context
 * @param [out] pin Device registration PIN on 4 bytes
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_pin( lriot_t *ctx, uint32_t* pin );

/*!
 * @brief This command returns the ChipEUI. The ChipEUI is also the default DeviceEUI. It is programmed during
 * manufacturing and is immutable.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] chip_eui Chip EUI buffer on 8 bytes
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_chip_eui( lriot_t *ctx, lr1110_modem_chip_eui_t chip_eui );

/*!
 * @brief This command returns the join EUI.
 *
 * @remark Join EUI is also known as Application Identifier (AppEUI) in LoRaWan v1.0.3.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] join_eui Join EUI buffer on 8 bytes
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_join_eui( lriot_t *ctx, lr1110_modem_join_eui_t join_eui );

/*!
 * @brief This command sets the Join EUI.
 *
 * @remark Join EUI is also known as Application Identifier (AppEUI) in LoRaWan v1.0.3.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] join_eui Join EUI buffer on 8 bytes
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_join_eui( lriot_t *ctx, lr1110_modem_join_eui_t join_eui );

/*!
 * @brief This command returns the DeviceEUI.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] dev_eui Device EUI buffer on 8 bytes
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_dev_eui( lriot_t *ctx, lr1110_modem_dev_eui_t dev_eui );

/*!
 * @brief This command sets the DeviceEUI.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] dev_eui Device EUI buffer on 8 bytes
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_dev_eui( lriot_t *ctx, lr1110_modem_dev_eui_t dev_eui );

/*!
 * @brief This command sets the LoRaWAN 1.0.3 application key. Note that a factory reset will erase this information.
 * The device is required to rejoin the network.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] app_key Application Key buffer on 16 bytes
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_app_key( lriot_t *ctx, lr1110_modem_app_key_t app_key );

/*!
 * @brief This command gets the LoRaWAN device class.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] modem_class LoRaWAN device class @ref lr1110_modem_classes_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_class( lriot_t *ctx, lr1110_modem_classes_t* modem_class );

/*!
 * @brief This command sets the LoRaWAN device class. Currently only class A and class C are supported. If the command
 * is successful, a change from class A to class C is effective after a completed TX transaction. The network server
 * should also be informed about the class change, typically on a separate channel for LoRaWAN 1.0.3. For a change from
 * class C to class A, the RX remains enabled until the next TX transaction.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] modem_class LoRaWAN device class @ref lr1110_modem_classes_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_class( lriot_t *ctx, lr1110_modem_classes_t modem_class );

/*!
 * @brief This command returns the regulatory region.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] region LoRaWAN regulatory region @ref lr1110_modem_regions_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_region( lriot_t *ctx, lr1110_modem_regions_t* region );

/*!
 * @brief This command sets the regulatory region. Additionally this command resets the ADR profile to Network Server
 * Controlled. If different ADR profile is desired, the profile needs to be set again.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] region LoRaWAN regulatory region @ref lr1110_modem_regions_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_region( lriot_t *ctx, lr1110_modem_regions_t region );

/*!
 * @brief This command returns the regulatory regions supported by the LR1110 modem
 *
 * @param [in] ctx Chip implementation context
 * @param [out] region_codes Regions supported by the LR1110 modem
 * @param [out] region_codes_size size of the regions list
 *
 * @returns Operation status
 */
err_t lr1110_modem_list_regions( lriot_t *ctx, uint8_t *region_codes, uint8_t* region_codes_size );

/*!
 * @brief This command returns the ADR profile type.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] adr_profile ADR profile type @ref lr1110_modem_adr_profiles_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_adr_profile( lriot_t *ctx, lr1110_modem_adr_profiles_t* adr_profile );

/*!
 * @brief This command sets the ADR profile and parameters.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] adr_profile ADR profile type @ref lr1110_modem_adr_profiles_t
 * @param [in] adr_custom_list custom ADR profile consisting of a list of 16 preferred data rates
 *
 * @remark each call to the function reinitialize the data rate distribution.
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_adr_profile( lriot_t *ctx, lr1110_modem_adr_profiles_t adr_profile, uint8_t* adr_custom_list );

/*!
 * @brief This command gets the device management port.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] port Device management port
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_dm_port( lriot_t *ctx, uint8_t* port );

/*!
 * @brief This command sets the device management port. Port 0 and ports from 224 and 255 must not be used since they
 * are reserved for future standardized application extensions.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] port Device management port
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_dm_port( lriot_t *ctx, uint8_t port );

/*!
 * @brief This command returns the device management reporting interval. The interval is specified in seconds, minutes,
 * hours or days.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] format reporting interval format @ref lr1110_modem_reporting_interval_format_t
 * @param [out] interval interval specified in seconds, minutes, hours or days
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_dm_info_interval( lriot_t *ctx, uint8_t* format, uint8_t* interval );

/*!
 * @brief This command sets the device management reporting interval. The interval is specified in seconds, minutes,
 * hours or days.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] format reporting interval format @ref lr1110_modem_reporting_interval_format_t
 * @param [in] interval interval specified in seconds, minutes, hours or days
 *
 * @remark Any value of 0 (seconds, minutes, hours, or days) disables device management reporting. The periodic status
 * reporting interval field is encoded in one byte where the two top-most bits specify the unit (sec/min/hour/day), and
 * the lower six bits the value 0-63. A value of zero disables the periodic status reporting.
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_dm_info_interval( lriot_t *ctx, lr1110_modem_reporting_interval_format_t format, uint8_t interval );

/*!
 * @brief This command lists the info fields to be included in the periodic DM status messages.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] dm_info_fields list of tag bytes @ref lr1110_modem_dm_info_fields_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_dm_info_field( lriot_t *ctx, lr1110_modem_dm_info_fields_t* dm_info_fields );

/*!
 * @brief This command sets the default info fields to be included in the periodic DM status messages. The set is
 * specified as list of field codes as defined in Uplink Message Format. Duplicate and invalid fields will be rejected
 * An empty set is valid and will effectively disable the DM status message.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] dm_info_fields list of tag bytes @ref lr1110_modem_dm_info_fields_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_dm_info_field( lriot_t *ctx, lr1110_modem_dm_info_fields_t* dm_info_fields );

/*!
 * @brief This command sends the specified set of information fields in one or more DM status messages immediately. The
 * set is specified as list of field codes as defined in Uplink Message Format. Duplicate and invalid fields will be
 * rejected (see note in Periodic Status Reporting).
 *
 * @param [in] ctx Chip implementation context
 * @param [in] dm_info_fields list of tag bytes @ref lr1110_modem_dm_info_fields_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_send_dm_status( lriot_t *ctx, lr1110_modem_dm_info_fields_t* dm_info_fields );

/*!
 * @brief This commands sets application-specific status information to be reported to the DM service. This information
 * is an application-defined, arbitrary 8-byte data blob. Once set, it is included in the appstatus info field sent as
 * part of the periodic status reports to the DM service. On the cloud side, this information can then be retrieved from
 * the service.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] app_status Application-specific status information
 *
 * @remark Note that this command does not trigger an immediate status report. If the application desires
 * to send the status immediately, it can issue the SendDmStatus command with the appstatus tag.
 * The application status is not stored persistently, i.e. after reset no application status will be reported.
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_app_status( lriot_t *ctx, uint8_t* app_status );

/*!
 * @brief This command starts joining the network. During the join procedure no further transmissions can occur. When
 * the network has been successfully joined, a Joined event is generated. If the device is already joined to a network,
 * or is in the process of joining, this command has no effect.
 *
 * @param [in] ctx Chip implementation context
 *
 * @returns Operation status
 */
err_t lr1110_modem_join( lriot_t *ctx );

/*!
 * @brief This command leaves the network if already joined, or cancels an ongoing join process. After leaving the
 * network, no further transmissions can occur.
 *
 * @param [in] ctx Chip implementation context
 *
 * @returns Operation status
 */
err_t lr1110_modem_leave_network( lriot_t *ctx );

/*!
 * @brief This command temporarily suspends or resumes the modem’s radio operations. It can be used to prevent extra
 * power consumption by the modem in case the application MCU temporarily needs more power itself and wants to prevent
 * exceeding limits.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] suspend Operations are suspended with parameter value 0x01 and resumed with parameter value 0x00 @ref
 * lr1110_modem_suspend_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_suspend( lriot_t *ctx, lr1110_modem_suspend_t suspend );

/*!
 * @brief This command returns the maximum application payload size possible according to the LoRaWAN regional
 * parameters for the next transmission using the current data rate, while assuming no FOpts are present and that a
 * device is not behind a repeater.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] tx_max_payload Maximum application payload size possible
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_next_tx_max_payload( lriot_t *ctx, uint8_t* tx_max_payload );

/*!
 * @brief This command requests sending the given data on the specified port as an unconfirmed (0x00) or confirmed
 * (0x01) frame. The request will be queued and the frame will be sent as soon as the current bandwidth usage of the
 * regulatory region permits. A TxDone event is generated when the frame either has been sent, or if it couldn’t be sent
 * because the specified data exceeded the maximum possible payload size.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] port LoRaWAN port
 * @param [in] uplink_type Uplink type unconfirmed (0x00) or confirmed (0x01) @ref lr1110_modem_uplink_type_t
 * @param [in] data_buf Data buffer
 * @param [in] length Data length
 *
 * @remark The application shall not use port 0 or the LoRaWAN test port 224 as well as the ports from 225 to 255 since
 * they are reserved for future standardized application extensions.
 *
 * @returns Operation status
 */
err_t lr1110_modem_request_tx( lriot_t *ctx, uint8_t port, lr1110_modem_uplink_type_t uplink_type, 
                               uint8_t* data_buf, uint8_t length );

/*!
 * @brief This command sends the given data on the specified port as an unconfirmed (0x00) or confirmed (0x01) frame
 * immediately. It has higher priority than all other services and does not take duty cycle or payload size restrictions
 * into account
 *
 * @param [in] ctx Chip implementation context
 * @param [in] port LoRaWAN port
 * @param [in] uplink_type Uplink type unconfirmed (0x00) or confirmed (0x01) @ref lr1110_modem_uplink_type_t
 * @param [in] data_buf Data buffer
 * @param [in] length Data length
 *
 * @remark The application shall not use port 0 or the LoRaWAN test port 224 as well as the ports from 225 to 255 since
 * they are reserved for future standardized application extensions.
 *
 * @returns Operation status
 */
err_t lr1110_modem_emergency_tx( lriot_t *ctx, uint8_t port, lr1110_modem_uplink_type_t uplink_type,
                                 uint8_t* data_buf, uint8_t length );

/*!
 * @brief This command prepares a fragmented file upload. It specifies the port for the subsequent upload, optional
 * encryption mode, file size, and average frame transmission interval (in seconds).
 *
 * @param [in] ctx Chip implementation context
 * @param [in] port LoRaWAN port
 * @param [in] encryption_mode Encryption mode @ref lr1110_modem_encryption_mode_t
 * @param [in] size Upload size
 * @param [in] interval Transmission interval in seconds
 *
 * @returns Operation status
 */
err_t lr1110_modem_upload_init( lriot_t *ctx, uint8_t port, lr1110_modem_encryption_mode_t encryption_mode,
                                uint16_t size, uint16_t interval );

/*!
 * @brief This command can be used to repeatedly set file data to be uploaded. The file data needs to be split into
 * parts of maximum 255 bytes each and the submitted parts will be appended to an internal buffer. In total exactly as
 * many bytes as specified by the UploadInit command have to be provided. The buffer allocated for file uploads is 8K
 * bytes.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] data_buf File data to be uploaded
 * @param [in] length Data length
 *
 * @returns Operation status
 */
err_t lr1110_modem_upload_data( lriot_t *ctx, uint8_t* data_buf, uint8_t length );

/*!
 * @brief After all data bytes indicated to UploadInit have been provided using UploadData this command can be issued to
 * actually start the transmission stream.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] crc CRC parameter which must match the CRC of the supplied data
 *
 * @returns Operation status
 */
err_t lr1110_modem_upload_start( lriot_t *ctx, uint32_t crc );

/*!
 * @brief This command initializes redundant data streaming on a specific port. The StreamInit command can only be
 * issued before the stream has been started using the SendStreamData command
 *
 * @param [in] ctx Chip implementation context
 * @param [in] port Streaming port
 * @param [in] encryption_mode Encryption mode @ref lr1110_modem_encryption_mode_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_stream_init( lriot_t *ctx, uint8_t port, lr1110_modem_encryption_mode_t encryption_mode );

/*!
 * @brief This command adds a new data record to the buffer of the data streaming encoder for the given port. Whenever
 * the buffer contains data records, the modem autonomously retrieves data from the buffer, optionally encrypts it, adds
 * redundancy, and sends uplinks containing the redundant stream
 *
 * @param [in] ctx Chip implementation context
 * @param [in] port Streaming port
 * @param [in] record File data to be streamed
 * @param [in] length Data length. The maximum length is 254 bytes.
 *
 * @returns Operation status
 */
err_t lr1110_modem_send_stream_data( lriot_t *ctx, uint8_t port, uint8_t* record, uint8_t length );

/*!
 * @brief This command queries the status of the data streaming buffer on the specified port. It returns two unsigned 16
 * bit integer values indicating the number of bytes pending for transmission and the number of bytes still free in the
 * buffer.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] port Streaming port
 * @param [in] stream_status Streaming status @ref lr1110_modem_stream_status_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_stream_status( lriot_t *ctx, uint8_t port, lr1110_modem_stream_status_t* stream_status );

/*!
 * @brief This commands sends the GPS time to LR1110 Modem, The time format is 4 bytes, big endian.
 *  It encodes the number of seconds from the 6-Jan 1980 00:00:00.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] gps_time GPS Time in seconds
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_gps_time( lriot_t *ctx, uint32_t gps_time );

/*!
 * @brief Use the previously set of JoinEUI/DevEUI to derive the app keys used in the Semtech join server
 *
 * @param [in] ctx Chip implementation context
 *
 * @returns Operation status
 */
err_t lr1110_modem_derive_keys( lriot_t *ctx );

/*!
 * @brief Configure rf output configuration
 *
 * @param [in] ctx Chip implementation context
 * @param [in] output Rf output @ref lr1110_modem_radio_pa_selection_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_rf_output( lriot_t *ctx, lr1110_modem_radio_pa_selection_t output );

/*!
 * @brief Set the port for application layer clock synchronization
 *
 * @param [in] ctx Chip implementation context
 * @param [in] port Port application
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_alc_sync_port( lriot_t *ctx, uint8_t port );

/*!
 * @brief Get the port for application layer clock synchronization
 *
 * @param [in] ctx Chip implementation context
 * @param [out] port Port application
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_alc_sync_port( lriot_t *ctx, uint8_t* port );

/*!
 * @brief Set the mode for application layer clock synchronization service
 *
 * @param [in] ctx Chip implementation context
 * @param [in] mode application layer clock mode
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_alc_sync_mode( lriot_t *ctx, lr1110_modem_alc_sync_mode_t mode );

/*!
 * @brief Get the mode for application layer clock synchronization service
 *
 * @param [in] ctx Chip implementation context
 * @param [out] mode application layer clock mode
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_alc_sync_mode( lriot_t *ctx, lr1110_modem_alc_sync_mode_t* mode );

/*!
 * @brief Set the number of uplink without ack from network before Modem changes it's ADR or resets
 *
 * @note It is recommended to have the first counter smaller than the second one. The value 0 deactivate the recovery
 * function. Default values are 255 for nb_uplink_mobile_static and 2400 for nb_uplink_reset.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] nb_uplink_mobile_static number of uplink without ack from network before by then the modem adr profile
 * will switch from mobile to static
 * @param [in] nb_uplink_reset number of uplink without ack from network before Modem resets
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_connection_timeout( lriot_t *ctx, uint16_t nb_uplink_mobile_static, uint16_t nb_uplink_reset );

/*!
 * @brief Get the number of uplink without ack from network before Modem changes it's ADR or resets
 *
 * @param [in] ctx Chip implementation context
 * @param [out] nb_uplink_mobile_static number of uplink without ack from network before by then the modem adr profile
 * will switch from mobile to static
 * @param [out] nb_uplink_reset number of uplink without ack from network before Modem resets
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_connection_timeout( lriot_t *ctx, uint16_t* nb_uplink_mobile_static, uint16_t* nb_uplink_reset );

/*!
 * @brief Get the status of the number of uplink without ack from network before Modem changes it's ADR or resets
 *
 * @param [in] ctx Chip implementation context
 * @param [out] nb_uplink_mobile_static number of uplink without ack from network before by then the modem adr profile
 * will switch from mobile to static
 * @param [out] nb_uplink_reset number of uplink without ack from network before Modem resets
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_connection_timeout_status( lriot_t *ctx, uint16_t* nb_uplink_mobile_static, uint16_t* nb_uplink_reset );

/*!
 * @brief Returns the LoRaWAN state Idle or Not Idle.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] lorawan_state LoRaWAN state @ref lr1110_modem_lorawan_state_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_lorawan_state( lriot_t *ctx, lr1110_modem_lorawan_state_t* lorawan_state );

/*!
 * @brief Write a charge value to user defined charger counter.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] charge user defined charger counter
 *
 * @returns Operation status
 */
err_t lr1110_modem_write_user_defined_charge_counter( lriot_t *ctx, uint16_t charge );

/*!
 * @brief Read a charge value to user defined charger counter.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] charge user defined charger counter
 *
 * @returns Operation status
 */
err_t lr1110_modem_read_user_defined_charge_counter( lriot_t *ctx, uint16_t* charge );

/*!
 * @brief Select which charge counter to send.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] charge_type charge type @ref lr1110_modem_charge_type_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_select_charge_uplink( lriot_t *ctx, lr1110_modem_charge_type_t charge_type );

/*!
 * @brief Get Duty cycle status info.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] duty_cycle Time in milliseconds (see notes for explanations)
 *
 * @note The sign determines the meaning of the value:
 * - duty_cycle >= 0: duty_cycle is the time budget in millisecond still available for transmission
 * - duty_cycle < 0: Abs(duty_cycle) is the time in millisecond before it can start transmitting again
 *
 * @note When duty cycle is deactivated, the returned value is 0.
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_duty_cycle_status( lriot_t *ctx, int32_t* duty_cycle );

/*!
 * @brief Activate/deactivate Duty cycle.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] duty_cycle @ref lr1110_modem_duty_cycle_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_activate_duty_cycle( lriot_t *ctx, lr1110_modem_duty_cycle_t duty_cycle );

/*!
 * @brief Activate/deactivate the certification mode.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] enable @ref lr1110_modem_certification_mode_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_certification_mode( lriot_t *ctx, lr1110_modem_certification_mode_t enable );

/*!
 * @brief Get the certification mode.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] enable @ref lr1110_modem_certification_mode_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_certification_mode( lriot_t *ctx, lr1110_modem_certification_mode_t* enable );

/*!
 * @brief Get the available data rate mask. One bit indicates one data rate. Bit n = 1 mean Data Rate n is available.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] available_data_rate Available data rate bit mask
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_available_data_rate( lriot_t *ctx, uint16_t* available_data_rate );

/*!
 * @brief This command sets 6 blocks (at most 6 dedicated power levels) of Tx output power configurations: expected
 * power, configured power, PA, Tx parameters and PA ramp time. For the Tx power levels not defined in the 6 levels with
 * this command, the modem always selects automatically the appropriate PA and Tx parameters configurations.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] output_power_config Tx output power configuration block list, \see
 * lr1110_modem_output_power_config_list_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_output_power_config( lriot_t *ctx, lr1110_modem_output_power_config_list_t output_power_config );

/*!
 * @brief This command gets 6 blocks of Tx output power configurations: expected
 * power, configured power, PA, Tx parameters and PA ramp time. For the Tx power levels not defined in the 6 levels with
 * this command, the modem always selects automatically the appropriate PA and Tx parameters configurations.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] output_power_config Tx output power configuration block list, \see
 * lr1110_modem_output_power_config_list_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_output_power_config( lriot_t *ctx, lr1110_modem_output_power_config_list_t output_power_config );

/*!
 * @brief Get the LoRaWAN network type.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] network_type @ref lr1110_modem_network_type_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_network_type( lriot_t *ctx, lr1110_modem_network_type_t* network_type );

/*!
 * @brief Set the LoRaWAN network type.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] network_type @ref lr1110_modem_network_type_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_network_type( lriot_t *ctx, lr1110_modem_network_type_t network_type );

/*!
 * @brief Activate the listen before talk
 *
 * @param [in] ctx Chip implementation context
 * @param [in] enable @ref lr1110_modem_lbt_mode_t
 * @param [in] threshold LBT treshold in dBm, default value is -80 dBm
 * @param [in] duration LBT duration in ms, default value is 5 ms
 * @param [in] bandwidth LBT bandwidth in Hz, default value is 200000 Hz
 *
 * @returns Operation status
 */
err_t lr1110_modem_activate_lbt( lriot_t *ctx, lr1110_modem_lbt_mode_t enable, int16_t threshold,
                                 uint32_t duration, uint32_t bandwidth );

/*!
 * @brief Set the LoRaWAN number of retransmission.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] nb_trans number of retransmission, the values are allowed between 0 and 15
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_nb_trans( lriot_t *ctx, uint8_t nb_trans );

/*!
 * @brief Get the LoRaWAN number of retransmission.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] nb_trans number of retransmission
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_nb_trans( lriot_t *ctx, uint8_t* nb_trans );

/*!
 * @brief Set the stream redundancy rate.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] stream_redundancy_rate Streaming redundancy rate, the values are allowed between 0 and 110%
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_stream_redundancy_rate( lriot_t *ctx, uint8_t stream_redundancy_rate );

/*!
 * @brief Get the stream redundancy rate.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] stream_redundancy_rate Streaming redundancy rate
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_stream_redundancy_rate( lriot_t *ctx, uint8_t* stream_redundancy_rate );


/*!
 * @brief Set the Crystal error of the MCU to fine adjust the rx window for lorawan ( ex: set 30 for a crystal error =
 * 0.3% ).
 *
 * @param [in] ctx Chip implementation context
 * @param [out] crystal_error Crystal error
 *
 * @returns Operation status
 */
err_t lr1110_modem_set_crystal_error( lriot_t *ctx, uint32_t crystal_error );

/*!
 * @brief Get the Crystal error.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] crystal_error Crystal error
 *
 * @returns Operation status
 */
err_t lr1110_modem_get_crystal_error( lriot_t *ctx, uint32_t* crystal_error );


#ifdef __cplusplus
}
#endif

#endif  // LR1110_MODEM_LORAWAN_H

/* --- EOF ------------------------------------------------------------------ */
