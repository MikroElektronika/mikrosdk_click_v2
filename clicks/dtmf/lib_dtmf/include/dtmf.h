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
 * @file dtmf.h
 * @brief This file contains API for DTMF Click Driver.
 */

#ifndef DTMF_H
#define DTMF_H

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
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup dtmf DTMF Click Driver
 * @brief API for configuring and manipulating DTMF Click driver.
 * @{
 */

/**
 * @defgroup dtmf_reg DTMF Registers List
 * @brief List of registers of DTMF Click driver.
 */

/**
 * @addtogroup dtmf_reg
 * @{
 */

/**
 * @brief DTMF description register.
 * @details Specified register for description of DTMF Click driver.
 */
#define DTMF_CMD_GENERAL_RESET          0x01
#define DTMF_CMD_GENERAL_CONTROL        0xE0
#define DTMF_CMD_TRANSMIT_MODE          0xE1
#define DTMF_CMD_RECEIVE_MODE           0xE2
#define DTMF_CMD_TRANSMIT_DATA          0xE3
#define DTMF_CMD_RECEIVE_DATA           0xE5
#define DTMF_CMD_STATUS                 0xE6
#define DTMF_CMD_PROGRAMMING            0xE8

/*! @} */ // dtmf_reg

/**
 * @defgroup dtmf_set DTMF Registers Settings
 * @brief Settings for registers of DTMF Click driver.
 */

/**
 * @addtogroup dtmf_set
 * @{
 */

/**
 * @brief DTMF general control register setting.
 * @details Specified setting for general control register of DTMF Click driver.
 */
#define DTMF_CONTROL_TXAN_OFF           0x8000u
#define DTMF_CONTROL_TXA_OFF            0x4000u
#define DTMF_CONTROL_LB                 0x0800u
#define DTMF_CONTROL_EQU                0x0400u
#define DTMF_CONTROL_PWR                0x0100u
#define DTMF_CONTROL_RST                0x0080u
#define DTMF_CONTROL_IRQN_EN            0x0040u
#define DTMF_CONTROL_IRQ_PROG_FLAG      0x0010u
#define DTMF_CONTROL_IRQ_TX_RDY_UNF     0x0008u
#define DTMF_CONTROL_IRQ_ENERGY_RX_CP   0x0004u
#define DTMF_CONTROL_IRQ_CONT_10        0x0002u
#define DTMF_CONTROL_IRQ_RX_RDY_OVF     0x0001u
#define DTMF_CONTROL_IRQ_MASK           0x001Fu

/**
 * @brief DTMF transmit mode register setting.
 * @details Specified setting for transmit mode register of DTMF Click driver.
 */
#define DTMF_TX_MODE_V21_FSK_HIGH       0x9000u
#define DTMF_TX_MODE_V21_FSK_LOW        0x8000u
#define DTMF_TX_MODE_BELL_103_FSK_HIGH  0x7000u
#define DTMF_TX_MODE_BELL_103_FSK_LOW   0x6000u
#define DTMF_TX_MODE_V23_FSK_1200       0x5000u
#define DTMF_TX_MODE_V23_FSK_75         0x4000u
#define DTMF_TX_MODE_BELL_202_FSK_1200  0x3000u
#define DTMF_TX_MODE_BELL_202_FSK_150   0x2000u
#define DTMF_TX_MODE_DTMF_TONES         0x1000u
#define DTMF_TX_MODE_DISABLED           0x0000u
#define DTMF_TX_MODE_MASK               0xF000u
#define DTMF_TX_LEVEL_0_DB              0x0E00u
#define DTMF_TX_LEVEL_MIN_1_5_DB        0x0C00u
#define DTMF_TX_LEVEL_MIN_3_DB          0x0A00u
#define DTMF_TX_LEVEL_MIN_4_5_DB        0x0800u
#define DTMF_TX_LEVEL_MIN_6_DB          0x0600u
#define DTMF_TX_LEVEL_MIN_7_5_DB        0x0400u
#define DTMF_TX_LEVEL_MIN_9_DB          0x0200u
#define DTMF_TX_LEVEL_MIN_10_5_DB       0x0000u
#define DTMF_TX_LEVEL_MASK              0x0E00u
#define DTMF_TX_DTMF_TWIST_2_DB         0x00E0u
#define DTMF_TX_DTMF_TWIST_1_DB         0x00C0u
#define DTMF_TX_DTMF_TWIST_1_5_DB       0x00A0u
#define DTMF_TX_DTMF_TWIST_2_5_DB       0x0080u
#define DTMF_TX_DTMF_TWIST_3_DB         0x0060u
#define DTMF_TX_DTMF_TWIST_3_5_DB       0x0040u
#define DTMF_TX_DTMF_TWIST_4_DB         0x0020u
#define DTMF_TX_DTMF_TWIST_4_5_DB       0x0000u
#define DTMF_TX_DTMF_TWIST_MASK         0x00E0u
#define DTMF_TX_DATA_FORMAT_SYNC        0x0018u
#define DTMF_TX_DATA_FORMAT_SS_NO_PAR   0x0010u
#define DTMF_TX_DATA_FORMAT_SS_EVEN_PAR 0x0008u
#define DTMF_TX_DATA_FORMAT_SS_ODD_PAR  0x0000u
#define DTMF_TX_DATA_FORMAT_MASK        0x0018u
#define DTMF_TX_DATA_STOP_8_2           0x0007u
#define DTMF_TX_DATA_STOP_8_1           0x0006u
#define DTMF_TX_DATA_STOP_7_2           0x0005u
#define DTMF_TX_DATA_STOP_7_1           0x0004u
#define DTMF_TX_DATA_STOP_6_2           0x0003u
#define DTMF_TX_DATA_STOP_6_1           0x0002u
#define DTMF_TX_DATA_STOP_5_2           0x0001u
#define DTMF_TX_DATA_STOP_5_1           0x0000u
#define DTMF_TX_DATA_STOP_MASK          0x0007u
#define DTMF_TX_DATA_SOURCE_TX_BUF      0x0004u
#define DTMF_TX_DATA_SOURCE_CONT_1S     0x0003u
#define DTMF_TX_DATA_SOURCE_CONT_0S     0x0002u
#define DTMF_TX_DATA_SOURCE_CONT_ALT    0x0000u
#define DTMF_TX_DATA_SOURCE_MASK        0x0007u
#define DTMF_TX_TONE_FIXED_NO_TONE      0x0000u
#define DTMF_TX_TONE_FIXED_PAIR_697     0x0001u
#define DTMF_TX_TONE_FIXED_PAIR_770     0x0002u
#define DTMF_TX_TONE_FIXED_PAIR_852     0x0003u
#define DTMF_TX_TONE_FIXED_PAIR_941     0x0004u
#define DTMF_TX_TONE_FIXED_PAIR_1209    0x0005u
#define DTMF_TX_TONE_FIXED_PAIR_1336    0x0006u
#define DTMF_TX_TONE_FIXED_PAIR_1477    0x0007u
#define DTMF_TX_TONE_FIXED_PAIR_1633    0x0008u
#define DTMF_TX_TONE_FIXED_PAIR_1300    0x0009u
#define DTMF_TX_TONE_FIXED_PAIR_2100    0x000Au
#define DTMF_TX_TONE_FIXED_PAIR_2225    0x000Bu
#define DTMF_TX_TONE_FIXED_PAIR_TA      0x000Cu
#define DTMF_TX_TONE_FIXED_PAIR_TB      0x000Du
#define DTMF_TX_TONE_FIXED_PAIR_TC      0x000Eu
#define DTMF_TX_TONE_FIXED_PAIR_TD      0x000Fu
#define DTMF_TX_TONE_D	                0x0010u
#define DTMF_TX_TONE_1	                0x0011u
#define DTMF_TX_TONE_2	                0x0012u
#define DTMF_TX_TONE_3	                0x0013u
#define DTMF_TX_TONE_4	                0x0014u
#define DTMF_TX_TONE_5	                0x0015u
#define DTMF_TX_TONE_6	                0x0016u
#define DTMF_TX_TONE_7	                0x0017u
#define DTMF_TX_TONE_8	                0x0018u
#define DTMF_TX_TONE_9	                0x0019u
#define DTMF_TX_TONE_0	                0x001Au
#define DTMF_TX_TONE_STAR               0x001Bu
#define DTMF_TX_TONE_HASH               0x001Cu
#define DTMF_TX_TONE_A	                0x001Du
#define DTMF_TX_TONE_B	                0x001Eu
#define DTMF_TX_TONE_C	                0x001Fu
#define DTMF_TX_TONE_MASK               0x001Fu

/**
 * @brief DTMF receive mode register setting.
 * @details Specified setting for receive mode register of DTMF Click driver.
 */
#define DTMF_RX_MODE_V21_FSK_HIGH       0x9000u
#define DTMF_RX_MODE_V21_FSK_LOW        0x8000u
#define DTMF_RX_MODE_BELL_103_FSK_HIGH  0x7000u
#define DTMF_RX_MODE_BELL_103_FSK_LOW   0x6000u
#define DTMF_RX_MODE_V23_FSK_1200       0x5000u
#define DTMF_RX_MODE_V23_FSK_75         0x4000u
#define DTMF_RX_MODE_BELL_202_FSK_1200  0x3000u
#define DTMF_RX_MODE_BELL_202_FSK_150   0x2000u
#define DTMF_RX_MODE_DTMF_TONES         0x1000u
#define DTMF_RX_MODE_DISABLED           0x0000u
#define DTMF_RX_MODE_MASK               0xF000u
#define DTMF_RX_LEVEL_0_DB              0x0E00u
#define DTMF_RX_LEVEL_MIN_1_5_DB        0x0C00u
#define DTMF_RX_LEVEL_MIN_3_DB          0x0A00u
#define DTMF_RX_LEVEL_MIN_4_5_DB        0x0800u
#define DTMF_RX_LEVEL_MIN_6_DB          0x0600u
#define DTMF_RX_LEVEL_MIN_7_5_DB        0x0400u
#define DTMF_RX_LEVEL_MIN_9_DB          0x0200u
#define DTMF_RX_LEVEL_MIN_10_5_DB       0x0000u
#define DTMF_RX_LEVEL_MASK              0x0E00u
#define DTMF_RX_USART_SYNC              0x0038u
#define DTMF_RX_USART_START_STOP        0x0030u
#define DTMF_RX_USART_DISABLED          0x0000u
#define DTMF_RX_USART_MASK              0x0038u
#define DTMF_RX_DATA_PARITY_8_PAR       0x0007u
#define DTMF_RX_DATA_PARITY_8_NO_PAR    0x0006u
#define DTMF_RX_DATA_PARITY_7_PAR       0x0005u
#define DTMF_RX_DATA_PARITY_7_NO_PAR    0x0004u
#define DTMF_RX_DATA_PARITY_6_PAR       0x0003u
#define DTMF_RX_DATA_PARITY_6_NO_PAR    0x0002u
#define DTMF_RX_DATA_PARITY_5_PAR       0x0001u
#define DTMF_RX_DATA_PARITY_5_NO_PAR    0x0000u
#define DTMF_RX_DATA_PARITY_MASK        0x0007u
#define DTMF_RX_TONE_DETECT_PROG_PAIR   0x0004u
#define DTMF_RX_TONE_DETECT_CALL_PROG   0x0003u
#define DTMF_RX_TONE_DETECT_ANSWER      0x0002u
#define DTMF_RX_TONE_DETECT_DTMF        0x0001u
#define DTMF_RX_TONE_DETECT_DISABLE     0x0007u
#define DTMF_RX_TONE_DETECT_MASK        0x0007u

/**
 * @brief DTMF status register setting.
 * @details Specified setting for status register of DTMF Click driver.
 */
#define DTMF_STATUS_IRQ                 0x8000u
#define DTMF_STATUS_PROG_FLAG           0x2000u
#define DTMF_STATUS_TX_READY            0x1000u
#define DTMF_STATUS_TX_UNDERFLOW        0x0800u
#define DTMF_STATUS_ENERGY_RX_CP        0x0400u
#define DTMF_STATUS_1010_PATTERN        0x0200u
#define DTMF_STATUS_CONT_0S             0x0100u
#define DTMF_STATUS_CONT_1S             0x0080u
#define DTMF_STATUS_RX_READY            0x0040u
#define DTMF_STATUS_RX_OVERFLOW         0x0020u
#define DTMF_STATUS_RX_FRAMING_ERROR    0x0010u
#define DTMF_STATUS_RX_EVEN_PARITY      0x0008u
#define DTMF_STATUS_FSK_OUT             0x0001u
#define DTMF_STATUS_TONE_D	            0x0000u
#define DTMF_STATUS_TONE_1	            0x0001u
#define DTMF_STATUS_TONE_2	            0x0002u
#define DTMF_STATUS_TONE_3	            0x0003u
#define DTMF_STATUS_TONE_4	            0x0004u
#define DTMF_STATUS_TONE_5	            0x0005u
#define DTMF_STATUS_TONE_6	            0x0006u
#define DTMF_STATUS_TONE_7	            0x0007u
#define DTMF_STATUS_TONE_8	            0x0008u
#define DTMF_STATUS_TONE_9	            0x0009u
#define DTMF_STATUS_TONE_0	            0x000Au
#define DTMF_STATUS_TONE_STAR           0x000Bu
#define DTMF_STATUS_TONE_HASH           0x000Cu
#define DTMF_STATUS_TONE_A	            0x000Du
#define DTMF_STATUS_TONE_B	            0x000Eu
#define DTMF_STATUS_TONE_C	            0x000Fu
#define DTMF_STATUS_TONE_MASK           0x000Fu

/**
 * @brief DTMF timeout and timing setting.
 * @details Specified setting for timeout and timing in milliseconds of DTMF Click driver.
 */
#define DTMF_TIMEOUT_CLEAR_IRQ          2000u
#define DTMF_TIMEOUT_TX_READY           2000u
#define DTMF_TIMEOUT_CALL_PROGRESS      60000u
#define DTMF_TIMING_BUSY                50u
#define DTMF_TIMING_DISCONNECTED        250u
#define DTMF_TIMING_RINGING             2000u
#define DTMF_TIMING_CALL_PROGRESS       6000u
#define DTMF_TIMING_SEND_MESSAGE        2000u
#define DTMF_TIMING_RX_READY            10u
#define DTMF_TIMING_WAIT_FOR_MESSAGE    10000u

/**
 * @brief DTMF state setting.
 * @details Specified setting for state of DTMF Click driver.
 */
#define DTMF_STATE_IDLE                 0
#define DTMF_STATE_IRQ_SET              1
#define DTMF_STATE_RINGING              2
#define DTMF_STATE_CALL_IN_PROGRESS     3

/**
 * @brief DTMF dial number setting.
 * @details Specified setting for dial number of DTMF Click driver.
 */
#define DTMF_DIAL_NUMBER_MAX_LEN        16

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b dtmf_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define DTMF_SET_DATA_SAMPLE_EDGE       SET_SPI_DATA_SAMPLE_EDGE
#define DTMF_SET_DATA_SAMPLE_MIDDLE     SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // dtmf_set

/**
 * @defgroup dtmf_map DTMF MikroBUS Map
 * @brief MikroBUS pin mapping of DTMF Click driver.
 */

/**
 * @addtogroup dtmf_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DTMF Click to the selected MikroBUS.
 */
#define DTMF_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rdn  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.hsw  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.irq  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // dtmf_map
/*! @} */ // dtmf

/**
 * @brief DTMF Click context object.
 * @details Context object definition of DTMF Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t hsw;              /**< Hookswitch pin (0-OFF, 1-ON). */

    // Input pins
    digital_in_t rdn;               /**< Ring detect notification pin (Active low). */
    digital_in_t irq;               /**< Interrupt request pin (Active low). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */

    uint16_t control;               /**< Contains the control register last set value. */
    uint16_t tx_mode;               /**< Contains the tx mode register last set value. */
    uint16_t rx_mode;               /**< Contains the rx mode register last set value. */
    uint16_t status;                /**< Contains the status register last read value. */

} dtmf_t;

/**
 * @brief DTMF Click configuration object.
 * @details Configuration object definition of DTMF Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t rdn;                 /**< Ring detect notification pin. */
    pin_name_t hsw;                 /**< Hookswitch pin. */
    pin_name_t irq;                 /**< Interrupt request pin. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} dtmf_cfg_t;

/**
 * @brief DTMF Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DTMF_OK = 0,
    DTMF_ERROR = -1,
    DTMF_TIMEOUT = -2

} dtmf_return_value_t;

/*!
 * @addtogroup dtmf DTMF Click Driver
 * @brief API for configuring and manipulating DTMF Click driver.
 * @{
 */

/**
 * @brief DTMF configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dtmf_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dtmf_cfg_setup ( dtmf_cfg_t *cfg );

/**
 * @brief DTMF initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dtmf_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_init ( dtmf_t *ctx, dtmf_cfg_t *cfg );

/**
 * @brief DTMF general reset function.
 * @details This function resets the device and clears all bits of the General Control,
 * Transmit Mode and Receive Mode Registers and b15 and b13-0 of the Status Register.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_general_reset ( dtmf_t *ctx );

/**
 * @brief DTMF set control function.
 * @details This function controls general features of the CMX865A such as the Powersave,
 * Loopback mode and the IRQ mask bits. It also allows the fixed compromise equalisers in
 * the Tx and Rx signal paths to be disabled if desired.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @param[in] data_in : Control register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_set_control ( dtmf_t *ctx, uint16_t data_in );

/**
 * @brief DTMF set transmit mode function.
 * @details This function controls the CMX865A transmit signal type and level.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @param[in] data_in : Transmit mode register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_set_transmit_mode ( dtmf_t *ctx, uint16_t data_in );

/**
 * @brief DTMF set receive mode function.
 * @details This function controls the CMX865A receive signal type and level.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @param[in] data_in : Receive mode register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_set_receive_mode ( dtmf_t *ctx, uint16_t data_in );

/**
 * @brief DTMF transmit data function.
 * @details In Tx Synchronous mode, this function sets the next 8 data bits to be transmitted.
 * b0 is transmitted first. In Tx Start-Stop mode, the specified number of data bits will be transmitted (b0 first). 
 * A Start bit, a Parity bit (if required) and Stop bit(s) will be added automatically.
 * This function should only be called when the Tx Data Ready bit of the Status Register is set.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @param[in] data_in : Data to be transmitted.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_transmit_data ( dtmf_t *ctx, uint8_t data_in );

/**
 * @brief DTMF receive data function.
 * @details In Rx synchronous mode, this function reads 8 received data bits, b0 of the register holding the earliest
 * received bit, b7 the latest. In Rx Start-Stop mode, this function reads the specified number of data bits from
 * a received character, b0 holding the first received bit. Unused bits are set to 0.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_receive_data ( dtmf_t *ctx, uint8_t *data_out );

/**
 * @brief DTMF get status function.
 * @details This function reads the 16-bit status register data.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @param[out] data_out : 16-bit status register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_get_status ( dtmf_t *ctx, uint16_t *data_out );

/**
 * @brief DTMF set programming function.
 * @details This function is used to program the transmit and receive programmed tone pairs by writing appropriate
 * values to RAM locations within the CMX865A.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @param[in] data_in : Programming register data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_set_programming ( dtmf_t *ctx, uint16_t data_in );

/**
 * @brief DTMF set hsw pin function.
 * @details This function sets the hookswitch (HSW) pin logic state.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void dtmf_set_hsw_pin ( dtmf_t *ctx, uint8_t state );

/**
 * @brief DTMF hook off function.
 * @details This function sets hookswitch to OFF state which closes the line interface.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dtmf_hook_off ( dtmf_t *ctx );

/**
 * @brief DTMF hook on function.
 * @details This function sets hookswitch to ON state which opens the line interface.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void dtmf_hook_on ( dtmf_t *ctx );

/**
 * @brief DTMF get rdn pin function.
 * @details This function returns the ring detection notification (RDN) pin logic state.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t dtmf_get_rdn_pin ( dtmf_t *ctx );

/**
 * @brief DTMF get irq pin function.
 * @details This function returns the interrupt request (IRQ) pin logic state.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t dtmf_get_irq_pin ( dtmf_t *ctx );

/**
 * @brief DTMF tx ready function.
 * @details This function reads the status register and returns the tx ready flag.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @return @li @c 0 - Not ready,
 *         @li @c 1 - Ready.
 * @note None.
 */
uint8_t dtmf_tx_ready ( dtmf_t *ctx );

/**
 * @brief DTMF rx ready function.
 * @details This function reads the status register and returns the rx ready flag.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @return @li @c 0 - Not ready,
 *         @li @c 1 - Ready.
 * @note None.
 */
uint8_t dtmf_rx_ready ( dtmf_t *ctx );

/**
 * @brief DTMF call progress function.
 * @details This function reads the status register and returns the rx energy or call progress flag.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @return @li @c 0 - Flag is not set,
 *         @li @c 1 - Flag is set.
 * @note None.
 */
uint8_t dtmf_call_progress ( dtmf_t *ctx );

/**
 * @brief DTMF unscram 1s det function.
 * @details This function reads the status register and sets the return flag if continuous ones
 * and rx energy flags are detected.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @return @li @c 0 - Flag is not set,
 *         @li @c 1 - Flag is set.
 * @note None.
 */
uint8_t dtmf_unscram_1s_det ( dtmf_t *ctx );

/**
 * @brief DTMF clear interrupts function.
 * @details This function reads the status register in a loop until the IRQ flag is cleared.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * @note None.
 */
err_t dtmf_clear_interrupts ( dtmf_t *ctx );

/**
 * @brief DTMF handshake init function.
 * @details This function performs a handshake init which resets the device settings to default.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_handshake_init ( dtmf_t *ctx );

/**
 * @brief DTMF dial function.
 * @details This function dials the selected number by alternating between DTMF and No-tone.
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @param[in] dial_num : Dial number string [up to 16 digits].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_dial ( dtmf_t *ctx, uint8_t *dial_num );

/**
 * @brief DTMF send message function.
 * @details This function sends an array of bytes via V.23 FSK 1200bps modem in start-stop 8.1 mode. 
 * @param[in] ctx : Click context object.
 * See #dtmf_t object definition for detailed explanation.
 * @param[in] data_in : Array of bytes.
 * @param[in] len : Number of bytes to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dtmf_send_message ( dtmf_t *ctx, uint8_t *data_in, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif // DTMF_H

/*! @} */ // dtmf

// ------------------------------------------------------------------------ END
