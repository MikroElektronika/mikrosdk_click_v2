/*!
 * @file      lr1110_modem_gnss.h
 *
 * @brief     GNSS scan driver definition for LR1110 modem
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

#ifndef LR1110_MODEM_GNSS_H
#define LR1110_MODEM_GNSS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include <stdbool.h>
#include <stdint.h>
#include "modem/lr1110_modem_gnss_types.h"
#include "modem/lr1110_modem_common.h"
#include "lriot.h"

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

/*!
 * @brief Activate the GNSS scan constellation
 *
 * @param [in] ctx Chip implementation context
 * @param [in] constellation_mask Bit mask of the constellations to use. See @ref lr1110_modem_gnss_constellation_mask_t
 * for the possible values
 *
 * @see lr1110_gnss_read_used_constellations
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_set_constellations_to_use( lriot_t *ctx, lr1110_modem_gnss_constellation_mask_t constellation_to_use );

/*!
 * @brief Read constellation used by the GNSS scanner from the almanac update configuration
 *
 * @param [in] ctx Chip implementation context
 * @param [out] constellations_used Bit mask of the constellations used. See @ref lr1110_modem_gnss_constellation_mask_t
 * for the possible values
 *
 * @see lr1110_modem_gnss_set_constellations_to_use
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_read_used_constellations( lriot_t *ctx, lr1110_modem_gnss_constellation_mask_t* constellations_used );

/*!
 * @brief Activate the almanac update
 *
 * @param [in] ctx Chip implementation context
 * @param [in] constellations_to_update Bit mask of the constellations to mark to update. See @ref
 * lr1110_modem_gnss_constellation_t for the possible values
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_set_almanac_update( lriot_t *ctx, lr1110_modem_gnss_constellation_mask_t constellations_to_update );

/*!
 * @brief Function to read the almanac update configuration
 *
 * @param [in] ctx Chip implementation context
 * @param [out] constellations_to_update Bit mask of the constellations to mark to update. See @ref
 * lr1110_modem_gnss_constellation_t for the possible values
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_read_almanac_update( lriot_t *ctx, lr1110_modem_gnss_constellation_mask_t* constellations_to_update );

/*!
 * @brief Set the GNSS frequency search
 *
 * @param [in] ctx Chip implementation context
 * @param [in] frequency_search_space Bit mask of the frequency search space to use. See @ref
 * lr1110_modem_gnss_frequency_search_space_mask_t for the possible values
 *
 * @see lr1110_modem_gnss_frequency_search_space_mask
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_set_frequency_search( lriot_t *ctx, lr1110_modem_gnss_frequency_search_space_mask_t frequency_search_space );

/*!
 * @brief Read constellation used by the GNSS scanner from the almanac update configuration
 *
 * @param [in] ctx Chip implementation context
 * @param [out] frequency_search_space Bit mask of the frequency search space used. See @ref
 * lr1110_modem_gnss_frequency_search_space_mask_t for the possible values
 *
 * @see lr1110_modem_gnss_frequency_search_space_mask
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_read_frequency_search( lriot_t *ctx, lr1110_modem_gnss_frequency_search_space_mask_t* frequency_search_space );

/*!
 * @brief Function to read the GNSS firmware version
 *
 * @param [in] ctx Chip implementation context
 * @param [out] version GNSS Firmware version currently running on the chip
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_read_firmware_version( lriot_t *ctx, lr1110_modem_gnss_version_t* version );

/*!
 * @brief Function to read the supported constellation, GPS or BEIDOU other constellations
 *
 * @param [in] ctx Chip implementation context
 * @param [out] supported_constellations Bit mask of the constellations used. See @ref
 * lr1110_modem_gnss_constellation_mask_t for the possible values
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_read_supported_constellations( lriot_t *ctx, lr1110_modem_gnss_constellation_mask_t* supported_constellations );

/*!
 * @brief Update full almanac for all satellites
 *
 * This function is to be used to update satellites almanac. Note that all 128 satellite almanacs must be update in a
 * row. Therefore, this function must be called 128 times in a row without any other calls in between.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] almanac_bytestream Almanac buffer to update all almanac of the LR1110. It is up to the application to
 * ensure that the buffer almanac_bytestream is indeed of size LR1110_MODEM_GNSS_FULL_ALMANAC_WRITE_BUFFER_SIZE
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_almanac_full_update( lriot_t *ctx, lr1110_modem_gnss_almanac_full_update_bytestream_t almanac_bytestream );

/*!
 * @brief One chunk almanac update
 *
 * This function is to be used to update a single chunk almanac. Note that all 129 chunks almanacs must be updated in a
 * row. Therefore, this function must be called 129 times in a row without any other calls in between.
 *
 * On the contrary, lr1110_gnss_almanac_full_update can be used to update all almanacs in one call, but the application
 * must be able to provide a buffer that holds all almanac (>2kB).
 *
 * @param [in] ctx Chip implementation context
 * @param [in] almanac_one_chunk_bytestream Almanac buffer to update one chunk almanac of the LR1110. It is up to the
 * application to ensure that bytestream is at least LR1110_MODEM_GNSS_SINGLE_ALMANAC_WRITE_SIZE long.
 *
 * @returns Status of the driver call
 */
err_t lr1110_modem_gnss_one_chunk_almanac_update( lriot_t *ctx, lr1110_modem_gnss_almanac_one_chunk_bytestream_t almanac_one_chunk_bytestream );

/*!
 * @brief Function to set the assistance position.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] assistance_position latitude 12 bits and longitude 12 bits @ref
 * lr1110_modem_gnss_solver_assistance_position_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_set_assistance_position( lriot_t *ctx, lr1110_modem_gnss_solver_assistance_position_t* assistance_position );

/*!
 * @brief Function to read the assistance position.
 *
 * The assistance position read may be different from the one set beforehand
 * with lr1110_modem_gnss_set_assistance_position due to a scaling computation.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] assistance_position latitude 12 bits and longitude 12 bits @ref
 * lr1110_modem_gnss_solver_assistance_position_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_read_assistance_position( lriot_t *ctx, lr1110_modem_gnss_solver_assistance_position_t* assistance_position );

/*!
 * @brief Function to set the Xtal error.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] xtal_error_in_ppm value in +/-40ppm
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_set_xtal_error( lriot_t *ctx, float xtal_error_in_ppm );

/*!
 * @brief Function to read the Xtal error.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] xtal_error_in_ppm value returned between +/-30ppm
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_read_xtal_error( lriot_t *ctx, float* xtal_error_in_ppm );

/*!
 * @brief Function to read context status.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] gnss_context @ref lr1110_modem_gnss_context_t
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_get_context( lriot_t *ctx, lr1110_modem_gnss_context_t* gnss_context );

/*!
 * @brief Get the number of detected satellites during last scan
 *
 * @param [in] ctx Chip implementation context
 * @param [out] nb_detected_satellites Number of satellites detected
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_get_nb_detected_satellites( lriot_t *ctx, uint8_t* nb_detected_satellites );

/*!
 * @brief Get the satellites detected on last scan with their IDs and C/N (aka.
 * CNR)
 *
 * @param [in] ctx Chip implementation context
 * @param [in] nb_detected_satellites Number of detected satellites on last scan (obtained by calling
 * lr1110_gnss_get_nb_detected_satellites)
 * @param [out] detected_satellite_id_snr Pointer to an array of structures of size big enough to contain
 * nb_detected_satellites elements
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_get_detected_satellites( lriot_t *ctx, uint8_t nb_detected_satellites,
                                                 lr1110_modem_gnss_detected_satellite_t* detected_satellite_id_snr );

/*!
 * @brief Get the timings spent in signal acquisition and signal analyzis
 *
 * These timings allow to compute the current timings of the last GNSS scan.
 *
 * @param [in] ctx Chip implementation context
 * @param [out] timings GNSS timings of last GNSS scan
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_get_timings( lriot_t *ctx, lr1110_modem_gnss_timings_t* timings );

/*!
 * @brief Read at maximum 11 sv’s Almanac, starting from sv id
 *
 * @param [in] ctx Chip implementation context
 * @param [in] sv_id Satellite ID
 * @param [in] nb_sv Number of satellites @note the maximum nb sv readable is 11.
 * @param [out] almanac_read The almanac buffer @note the minimal size of the buffer to provide is nb_sv * 22 bytes
 * @param [in] buffer_len Buffer len of the almanac_read buffer.
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_almanac_read_by_index( lriot_t *ctx, uint8_t sv_id, uint8_t nb_sv,
                                               uint8_t* almanac_read, uint8_t buffer_len );

/*!
 * @brief GNSS scan with no assisted parameters needed
 *
 * @warning Parameter effort_mode can only be set to LR1110_MODEM_GNSS_OPTION_DEFAULT
 *
 * @param [in] ctx Chip implementation context
 * @param [in] effort_mode Effort mode @ref lr1110_modem_gnss_search_mode_t
 * @param [in] gnss_result_mask Bit mask indicating which information is added in the output payload @ref
 * lr1110_modem_gnss_result_mask_e
 * @param [in] nb_sat The expected number of satellite to provide. This value must be in the range [0:128]
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_scan_autonomous( lriot_t *ctx, lr1110_modem_gnss_search_mode_t effort_mode,
                                         uint8_t gnss_result_mask, uint8_t nb_sat );

/*!
 * @brief GNSS scan with assisted parameters.
 *
 * @param [in] ctx Chip implementation context
 * @param [in] effort_mode Effort mode @ref lr1110_modem_gnss_search_mode_t
 * @param [in] gnss_result_mask Bit mask indicating which information is added in the output payload @ref
 * lr1110_modem_gnss_result_mask_e
 * @param [in] nb_sat The expected number of satellite to provide. This value must be in the range [0:128]
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_scan_assisted( lriot_t *ctx, lr1110_modem_gnss_search_mode_t effort_mode,
                                       uint8_t gnss_result_mask, uint8_t nb_sat );

/*!
 * @brief Push data received from solver to LR1110 modem
 *
 * @param [in] ctx Chip implementation context
 * @param [in] payload Payload received from solver
 * @param [in] payload_size Size of the payload received from solver (in bytes)
 *
 * @returns Operation status
 */
err_t lr1110_modem_gnss_push_solver_msg( lriot_t *ctx, uint8_t* payload, uint16_t payload_size );

#ifdef __cplusplus
}
#endif

#endif  // LR1110_MODEM_GNSS_H

/* --- EOF ------------------------------------------------------------------ */
