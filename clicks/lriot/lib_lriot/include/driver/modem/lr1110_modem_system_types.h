/*!
 * @file      lr1110_modem_system_types.h
 *
 * @brief     System driver types for LR1110 modem
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

#ifndef LR1110_MODEM_SYSTEM_TYPES_H
#define LR1110_MODEM_SYSTEM_TYPES_H

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

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*!
 * @brief Regulator mode values
 */
typedef enum
{
    LR1110_MODEM_SYSTEM_REG_MODE_LDO  = 0x00,  //!< (Default)
    LR1110_MODEM_SYSTEM_REG_MODE_DCDC = 0x01,
} lr1110_modem_system_reg_mode_t;

/*!
 * @brief RF switch configuration pin
 */
enum lr1110_modem_system_rfswitch_cfg_pin_e
{
    LR1110_MODEM_SYSTEM_RFSW0_HIGH = ( 1 << 0 ),
    LR1110_MODEM_SYSTEM_RFSW1_HIGH = ( 1 << 1 ),
    LR1110_MODEM_SYSTEM_RFSW2_HIGH = ( 1 << 2 ),
    LR1110_MODEM_SYSTEM_RFSW3_HIGH = ( 1 << 3 ),
    LR1110_MODEM_SYSTEM_RFSW4_HIGH = ( 1 << 4 ),
};

/*!
 * @brief Low Frequency clock configurations values
 */
typedef enum
{
    LR1110_MODEM_SYSTEM_LFCLK_RC   = 0x00,  //!<  (Default)
    LR1110_MODEM_SYSTEM_LFCLK_XTAL = 0x01,
    LR1110_MODEM_SYSTEM_LFCLK_EXT  = 0x02
} lr1110_modem_system_lfclk_cfg_t;

/*!
 * @brief TCXO supply voltage values
 */
typedef enum
{
    LR1110_MODEM_SYSTEM_TCXO_CTRL_1_6V = 0x00,  //!< Supply voltage = 1.6v
    LR1110_MODEM_SYSTEM_TCXO_CTRL_1_7V = 0x01,  //!< Supply voltage = 1.7v
    LR1110_MODEM_SYSTEM_TCXO_CTRL_1_8V = 0x02,  //!< Supply voltage = 1.8v
    LR1110_MODEM_SYSTEM_TCXO_CTRL_2_2V = 0x03,  //!< Supply voltage = 2.2v
    LR1110_MODEM_SYSTEM_TCXO_CTRL_2_4V = 0x04,  //!< Supply voltage = 2.4v
    LR1110_MODEM_SYSTEM_TCXO_CTRL_2_7V = 0x05,  //!< Supply voltage = 2.7v
    LR1110_MODEM_SYSTEM_TCXO_CTRL_3_0V = 0x06,  //!< Supply voltage = 3.0v
    LR1110_MODEM_SYSTEM_TCXO_CTRL_3_3V = 0x07,  //!< Supply voltage = 3.3v
} lr1110_modem_system_tcxo_supply_voltage_t;

/*!
 * @brief RF switch configuration parameters
 */
typedef struct
{
    uint8_t enable;   //!< Bit mask of enabled switches
    uint8_t standby;  //!< Bit mask of switches that are on in standby mode
    uint8_t rx_mode;  //!< Bit mask of switches that are on in rx mode
    uint8_t tx_mode;  //!< Bit mask of switches that are on in tx mode
    uint8_t tx_hp;    //!< Bit mask of switches that are on in tx_hp mode
    uint8_t tx_hf;    //!< Bit mask of switches that are on in tx_hf mode
    uint8_t gnss;     //!< Bit mask of switches that are on in gnss mode
    uint8_t wifi;     //!< Bit mask of switches that are on in wifi mode
} lr1110_modem_system_rf_switch_cfg_t;

#ifdef __cplusplus
}
#endif

#endif  // LR1110_MODEM_SYSTEM_TYPES_H
