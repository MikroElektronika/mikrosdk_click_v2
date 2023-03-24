/*!
 * @file      lr1110_modem_hal.h
 *
 * @brief     Hardware Abstraction Layer (HAL) interface for LR1110 modem
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

#ifndef LR1110_MODEM_HAL_H
#define LR1110_MODEM_HAL_H

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
#include "lriot.h"

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*!
 * @brief Status reported by the HAL layer
 */
typedef enum lr1110_modem_hal_status_e
{
    LR1110_MODEM_HAL_STATUS_OK           = 0x00,  //!< Operation terminated successfully
    LR1110_MODEM_HAL_STATUS_ERROR        = 0x01,  //!< Operation terminated with error
    LR1110_MODEM_HAL_STATUS_BAD_FRAME    = 0x0F,  //!< Bad frame detected in the exchange
    LR1110_MODEM_HAL_STATUS_BUSY_TIMEOUT = 0xFF,  //!< Timeout occured while waiting for Busy line state
} lr1110_modem_hal_status_t;

/*
 * ============================================================================
 * API definitions to be implemented by the user
 * ============================================================================
 */

/*!
 * Radio data transfer - write
 *
 * @remark Must be implemented by the upper layer
 *
 * @param [in] ctx              Radio implementation parameters
 * @param [in] command          Pointer to the buffer to be transmitted
 * @param [in] command_length   Buffer size to be transmitted
 * @param [in] data_buf         Pointer to the buffer to be transmitted
 * @param [in] data_length      Buffer size to be transmitted
 *
 * @returns Operation status
 */
err_t lr1110_modem_hal_write( lriot_t *ctx, uint8_t* command, uint16_t command_length,
                                            uint8_t* data_buf, uint16_t data_length );

/*!
 * Radio data transfer - read
 *
 * @remark Must be implemented by the upper layer
 *
 * @param [in] ctx              Radio implementation parameters
 * @param [in] command          Pointer to the buffer to be transmitted
 * @param [in] command_length   Buffer size to be transmitted
 * @param [out] data_buf        Pointer to the buffer to be received
 * @param [in] data_length      Buffer size to be received
 *
 * @returns Operation status
 */
err_t lr1110_modem_hal_read( lriot_t *ctx, uint8_t* command, uint16_t command_length,
                                           uint8_t* data_buf, uint16_t data_length );

/*!
 * @brief  Radio data transfer - write & read in single operation
 *
 * @remark Must be implemented by the upper layer
 * @remark Only required by lr1110_system_get_status command
 *
 * @param [in] ctx              Radio implementation parameters
 * @param [in] command          Pointer to the buffer to be transmitted
 * @param [out] data_buf        Pointer to the buffer to be received
 * @param [in] data_length      Buffer size to be received
 *
 * @returns Operation status
 */
err_t lr1110_modem_hal_write_read( lriot_t *ctx, uint8_t* command, uint8_t* data_buf, uint16_t data_length );

/*!
 * Radio data transfer - write without wait the return code - this API is dedicated to the functions which reset the
 * Modem-E
 *
 * @remark Must be implemented by the upper layer
 *
 * @param [in] ctx              Radio implementation parameters
 * @param [in] command          Pointer to the buffer to be transmitted
 * @param [in] command_length   Buffer size to be transmitted
 * @param [in] data_buf         Pointer to the buffer to be transmitted
 * @param [in] data_length      Buffer size to be transmitted
 *
 * @returns Operation status
 */
err_t lr1110_modem_hal_write_without_rc( lriot_t *ctx, uint8_t* command, uint16_t command_length,
                                                       uint8_t* data_buf, uint16_t data_length );

/*!
 * Reset the chip
 *
 * @remark Must be implemented by the upper layer
 *
 * @param [in] ctx Chip implementation parameters
 *
 * @returns Operation status
 */
err_t lr1110_modem_hal_reset( lriot_t *ctx );

/*!
 * Wake the chip up.
 *
 * @remark Must be implemented by the upper layer
 *
 * @param [in] ctx chip implementation parameters

 * @returns Operation status
 */
err_t lr1110_modem_hal_wakeup( lriot_t *ctx );

#ifdef __cplusplus
}
#endif

#endif  // LR1110_MODEM_HAL_H
