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
 * @file eposmodule.h
 * @brief This file contains API for EPOS Module Click Driver.
 */

#ifndef EPOSMODULE_H
#define EPOSMODULE_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup eposmodule EPOS Module Click Driver
 * @brief API for configuring and manipulating EPOS Module Click driver.
 * @{
 */

/**
 * @defgroup eposmodule_reg EPOS Module Registers List
 * @brief List of registers of EPOS Module Click driver.
 */

/**
 * @addtogroup eposmodule_reg
 * @{
 */

/**
 * @brief EPOS Module register list.
 * @details Specified register list of EPOS Module Click driver.
 */
#define EPOSMODULE_CMD_GENERAL_RESET            0x01
#define EPOSMODULE_CMD_GENERAL_CONTROL          0xE0
#define EPOSMODULE_CMD_TRANSMIT_MODE            0xE1
#define EPOSMODULE_CMD_RECEIVE_MODE             0xE2
#define EPOSMODULE_CMD_TRANSMIT_DATA            0xE3
#define EPOSMODULE_CMD_ALT_TRANSMIT_DATA        0xE4
#define EPOSMODULE_CMD_RECEIVE_DATA             0xE5
#define EPOSMODULE_CMD_STATUS                   0xE6
#define EPOSMODULE_CMD_PROGRAMMING              0xE8
#define EPOSMODULE_CMD_QAM_MODEM_CMD            0xEA
#define EPOSMODULE_CMD_QAM_MODEM_STATUS         0xEB

/*! @} */ // eposmodule_reg

/**
 * @defgroup eposmodule_set EPOS Module Registers Settings
 * @brief Settings for registers of EPOS Module Click driver.
 */

/**
 * @addtogroup eposmodule_set
 * @{
 */

/**
 * @brief EPOS Module general control register setting.
 * @details Specified setting for general control register of EPOS Module Click driver.
 */
#define EPOSMODULE_CONTROL_EQU                  0x8000
#define EPOSMODULE_CONTROL_HI_GAIN              0x4000
#define EPOSMODULE_CONTROL_PAT_DET              0x2000
#define EPOSMODULE_CONTROL_LB                   0x0800
#define EPOSMODULE_CONTROL_2C                   0x0400
#define EPOSMODULE_CONTROL_RLY_DRV              0x0200
#define EPOSMODULE_CONTROL_PWR                  0x0100
#define EPOSMODULE_CONTROL_RST                  0x0080
#define EPOSMODULE_CONTROL_IRQN_EN              0x0040
#define EPOSMODULE_CONTROL_IRQ_RING             0x0020
#define EPOSMODULE_CONTROL_IRQ_PROG_FLAG        0x0010
#define EPOSMODULE_CONTROL_IRQ_TX_RDY_UNF       0x0008
#define EPOSMODULE_CONTROL_IRQ_ENERGY_RX_CP     0x0004
#define EPOSMODULE_CONTROL_IRQ_CONT_10          0x0002
#define EPOSMODULE_CONTROL_IRQ_RX_RDY_OVF       0x0001
#define EPOSMODULE_CONTROL_IRQ_MASK             0x001F

/**
 * @brief EPOS Module transmit mode register setting.
 * @details Specified setting for transmit mode register of EPOS Module Click driver.
 */
#define EPOSMODULE_TX_MODE_QAM                  0xF000
#define EPOSMODULE_TX_MODE_V22_BIS_2400_HIGH    0xD000
#define EPOSMODULE_TX_MODE_V22_BIS_2400_LOW     0xC000
#define EPOSMODULE_TX_MODE_V22_1200_HIGH        0xB000
#define EPOSMODULE_TX_MODE_V22_1200_LOW         0xA000
#define EPOSMODULE_TX_MODE_V21_FSK_HIGH         0x9000
#define EPOSMODULE_TX_MODE_V21_FSK_LOW          0x8000
#define EPOSMODULE_TX_MODE_BELL_103_FSK_HIGH    0x7000
#define EPOSMODULE_TX_MODE_BELL_103_FSK_LOW     0x6000
#define EPOSMODULE_TX_MODE_V23_FSK_1200         0x5000
#define EPOSMODULE_TX_MODE_V23_FSK_75           0x4000
#define EPOSMODULE_TX_MODE_BELL_202_FSK_1200    0x3000
#define EPOSMODULE_TX_MODE_BELL_202_FSK_150     0x2000
#define EPOSMODULE_TX_MODE_DTMF_TONES           0x1000
#define EPOSMODULE_TX_MODE_DISABLED             0x0000
#define EPOSMODULE_TX_MODE_MASK                 0xF000
#define EPOSMODULE_TX_LEVEL_0_DB                0x0E00
#define EPOSMODULE_TX_LEVEL_MIN_1_5_DB          0x0C00
#define EPOSMODULE_TX_LEVEL_MIN_3_DB            0x0A00
#define EPOSMODULE_TX_LEVEL_MIN_4_5_DB          0x0800
#define EPOSMODULE_TX_LEVEL_MIN_6_DB            0x0600
#define EPOSMODULE_TX_LEVEL_MIN_7_5_DB          0x0400
#define EPOSMODULE_TX_LEVEL_MIN_9_DB            0x0200
#define EPOSMODULE_TX_LEVEL_MIN_10_5_DB         0x0000
#define EPOSMODULE_TX_LEVEL_MASK                0x0E00
#define EPOSMODULE_TX_GUARD_TONE_550            0x0180
#define EPOSMODULE_TX_GUARD_TONE_1800           0x0100
#define EPOSMODULE_TX_GUARD_TONE_DIS            0x0000
#define EPOSMODULE_TX_GUARD_TONE_MASK           0x0180
#define EPOSMODULE_TX_SCRAMBLER_EN_64_EN        0x0060
#define EPOSMODULE_TX_SCRAMBLER_EN_64_DIS       0x0040
#define EPOSMODULE_TX_SCRAMBLER_DIS             0x0000
#define EPOSMODULE_TX_SCRAMBLER_MASK            0x0060
#define EPOSMODULE_TX_DTMF_TWIST_2_DB           0x0000
#define EPOSMODULE_TX_DTMF_TWIST_1_DB           0x0020
#define EPOSMODULE_TX_DTMF_TWIST_1_5_DB         0x0040
#define EPOSMODULE_TX_DTMF_TWIST_2_5_DB         0x0060
#define EPOSMODULE_TX_DTMF_TWIST_3_DB           0x0080
#define EPOSMODULE_TX_DTMF_TWIST_3_5_DB         0x00A0
#define EPOSMODULE_TX_DTMF_TWIST_4_DB           0x00C0
#define EPOSMODULE_TX_DTMF_TWIST_4_5_DB         0x00E0
#define EPOSMODULE_TX_DTMF_TWIST_MASK           0x00E0
#define EPOSMODULE_TX_DATA_FORMAT_SPECIAL       0x0018
#define EPOSMODULE_TX_DATA_FORMAT_SS_NO_PAR     0x0010
#define EPOSMODULE_TX_DATA_FORMAT_SS_EVEN_PAR   0x0008
#define EPOSMODULE_TX_DATA_FORMAT_SS_ODD_PAR    0x0000
#define EPOSMODULE_TX_DATA_FORMAT_MASK          0x0018
#define EPOSMODULE_TX_DATA_STOP_8_2             0x0007
#define EPOSMODULE_TX_DATA_STOP_8_1             0x0006
#define EPOSMODULE_TX_DATA_STOP_7_2             0x0005
#define EPOSMODULE_TX_DATA_STOP_7_1             0x0004
#define EPOSMODULE_TX_DATA_STOP_6_2             0x0003
#define EPOSMODULE_TX_DATA_STOP_6_1             0x0002
#define EPOSMODULE_TX_DATA_STOP_5_2             0x0001
#define EPOSMODULE_TX_DATA_STOP_5_1             0x0000
#define EPOSMODULE_TX_DATA_STOP_MASK            0x0007
#define EPOSMODULE_TX_DATA_SOURCE_TX_BUF        0x0007
#define EPOSMODULE_TX_DATA_SOURCE_HDLC_MODE     0x0006
#define EPOSMODULE_TX_DATA_SOURCE_HDLC_ABORT    0x0005
#define EPOSMODULE_TX_DATA_SOURCE_CONT_1S       0x0003
#define EPOSMODULE_TX_DATA_SOURCE_CONT_0S       0x0002
#define EPOSMODULE_TX_DATA_SOURCE_CONT_ALT      0x0001
#define EPOSMODULE_TX_DATA_SOURCE_MASK          0x0007
#define EPOSMODULE_TX_TONE_FIXED_NO_TONE        0x0000
#define EPOSMODULE_TX_TONE_FIXED_PAIR_697       0x0001
#define EPOSMODULE_TX_TONE_FIXED_PAIR_770       0x0002
#define EPOSMODULE_TX_TONE_FIXED_PAIR_852       0x0003
#define EPOSMODULE_TX_TONE_FIXED_PAIR_941       0x0004
#define EPOSMODULE_TX_TONE_FIXED_PAIR_1209      0x0005
#define EPOSMODULE_TX_TONE_FIXED_PAIR_1336      0x0006
#define EPOSMODULE_TX_TONE_FIXED_PAIR_1477      0x0007
#define EPOSMODULE_TX_TONE_FIXED_PAIR_1633      0x0008
#define EPOSMODULE_TX_TONE_FIXED_PAIR_1300      0x0009
#define EPOSMODULE_TX_TONE_FIXED_PAIR_2100      0x000A
#define EPOSMODULE_TX_TONE_FIXED_PAIR_2225      0x000B
#define EPOSMODULE_TX_TONE_FIXED_PAIR_TA        0x000C
#define EPOSMODULE_TX_TONE_FIXED_PAIR_TB        0x000D
#define EPOSMODULE_TX_TONE_FIXED_PAIR_TC        0x000E
#define EPOSMODULE_TX_TONE_FIXED_PAIR_TD        0x000F
#define EPOSMODULE_TX_DTMF_TONE_D               0x0010
#define EPOSMODULE_TX_DTMF_TONE_1               0x0011
#define EPOSMODULE_TX_DTMF_TONE_2               0x0012
#define EPOSMODULE_TX_DTMF_TONE_3               0x0013
#define EPOSMODULE_TX_DTMF_TONE_4               0x0014
#define EPOSMODULE_TX_DTMF_TONE_5               0x0015
#define EPOSMODULE_TX_DTMF_TONE_6               0x0016
#define EPOSMODULE_TX_DTMF_TONE_7               0x0017
#define EPOSMODULE_TX_DTMF_TONE_8               0x0018
#define EPOSMODULE_TX_DTMF_TONE_9               0x0019
#define EPOSMODULE_TX_DTMF_TONE_0               0x001A
#define EPOSMODULE_TX_DTMF_TONE_STAR            0x001B
#define EPOSMODULE_TX_DTMF_TONE_HASH            0x001C
#define EPOSMODULE_TX_DTMF_TONE_A               0x001D
#define EPOSMODULE_TX_DTMF_TONE_B               0x001E
#define EPOSMODULE_TX_DTMF_TONE_C               0x001F
#define EPOSMODULE_TX_DTMF_TONE_MASK            0x001F

/**
 * @brief EPOS Module receive mode register setting.
 * @details Specified setting for receive mode register of EPOS Module Click driver.
 */
#define EPOSMODULE_RX_MODE_QAM                  0xF000
#define EPOSMODULE_RX_MODE_V22_BIS_2400_HIGH    0xD000
#define EPOSMODULE_RX_MODE_V22_BIS_2400_LOW     0xC000
#define EPOSMODULE_RX_MODE_V22_1200_HIGH        0xB000
#define EPOSMODULE_RX_MODE_V22_1200_LOW         0xA000
#define EPOSMODULE_RX_MODE_V21_FSK_HIGH         0x9000
#define EPOSMODULE_RX_MODE_V21_FSK_LOW          0x8000
#define EPOSMODULE_RX_MODE_BELL_103_FSK_HIGH    0x7000
#define EPOSMODULE_RX_MODE_BELL_103_FSK_LOW     0x6000
#define EPOSMODULE_RX_MODE_V23_FSK_1200         0x5000
#define EPOSMODULE_RX_MODE_V23_FSK_75           0x4000
#define EPOSMODULE_RX_MODE_BELL_202_FSK_1200    0x3000
#define EPOSMODULE_RX_MODE_BELL_202_FSK_150     0x2000
#define EPOSMODULE_RX_MODE_DTMF_TONES           0x1000
#define EPOSMODULE_RX_MODE_DISABLED             0x0000
#define EPOSMODULE_RX_MODE_MASK                 0xF000
#define EPOSMODULE_RX_LEVEL_0_DB                0x0E00
#define EPOSMODULE_RX_LEVEL_MIN_1_5_DB          0x0C00
#define EPOSMODULE_RX_LEVEL_MIN_3_DB            0x0A00
#define EPOSMODULE_RX_LEVEL_MIN_4_5_DB          0x0800
#define EPOSMODULE_RX_LEVEL_MIN_6_DB            0x0600
#define EPOSMODULE_RX_LEVEL_MIN_7_5_DB          0x0400
#define EPOSMODULE_RX_LEVEL_MIN_9_DB            0x0200
#define EPOSMODULE_RX_LEVEL_MIN_10_5_DB         0x0000
#define EPOSMODULE_RX_LEVEL_MASK                0x0E00
#define EPOSMODULE_RX_AUTO_EQU_EN               0x0100
#define EPOSMODULE_RX_AUTO_EQU_MASK             0x0100
#define EPOSMODULE_RX_DESCRAMBLER_EN_64_EN      0x0060
#define EPOSMODULE_RX_DESCRAMBLER_EN_64_DIS     0x0040
#define EPOSMODULE_RX_DESCRAMBLER_DIS           0x0000
#define EPOSMODULE_RX_DESCRAMBLER_MASK          0x0060
#define EPOSMODULE_RX_DATA_FORMAT_SPECIAL       0x0038
#define EPOSMODULE_RX_DATA_FORMAT_SS_NO_OVS     0x0030
#define EPOSMODULE_RX_DATA_FORMAT_SS_1PCT_OVS   0x0028
#define EPOSMODULE_RX_DATA_FORMAT_SS_2_3PCT_OVS 0x0020
#define EPOSMODULE_RX_DATA_FORMAT_USART_DIS     0x0000
#define EPOSMODULE_RX_DATA_FORMAT_MASK          0x0038
#define EPOSMODULE_RX_DATA_PARITY_8_PAR         0x0007
#define EPOSMODULE_RX_DATA_PARITY_8_NO_PAR      0x0006
#define EPOSMODULE_RX_DATA_PARITY_7_PAR         0x0005
#define EPOSMODULE_RX_DATA_PARITY_7_NO_PAR      0x0004
#define EPOSMODULE_RX_DATA_PARITY_6_PAR         0x0003
#define EPOSMODULE_RX_DATA_PARITY_6_NO_PAR      0x0002
#define EPOSMODULE_RX_DATA_PARITY_5_PAR         0x0001
#define EPOSMODULE_RX_DATA_PARITY_5_NO_PAR      0x0000
#define EPOSMODULE_RX_DATA_PARITY_MASK          0x0007
#define EPOSMODULE_RX_DATA_SOURCE_SYNC          0x0007
#define EPOSMODULE_RX_DATA_SOURCE_HDLC_MODE     0x0006
#define EPOSMODULE_RX_DATA_SOURCE_MASK          0x0007
#define EPOSMODULE_RX_TONE_DETECT_PROG_PAIR     0x0004
#define EPOSMODULE_RX_TONE_DETECT_CALL_PROG     0x0003
#define EPOSMODULE_RX_TONE_DETECT_ANSWER        0x0002
#define EPOSMODULE_RX_TONE_DETECT_DTMF          0x0001
#define EPOSMODULE_RX_TONE_DETECT_DISABLE       0x0000
#define EPOSMODULE_RX_TONE_DETECT_MASK          0x0007

/**
 * @brief EPOS Module status register setting.
 * @details Specified setting for status register of EPOS Module Click driver.
 */
#define EPOSMODULE_STATUS_IRQ                   0x8000
#define EPOSMODULE_STATUS_RING                  0x4000
#define EPOSMODULE_STATUS_PROG_FLAG             0x2000
#define EPOSMODULE_STATUS_TX_READY              0x1000
#define EPOSMODULE_STATUS_TX_UNDERFLOW          0x0800
#define EPOSMODULE_STATUS_ENERGY_RX_CP          0x0400
#define EPOSMODULE_STATUS_1010_PATTERN          0x0200
#define EPOSMODULE_STATUS_CONT_0S               0x0100
#define EPOSMODULE_STATUS_CONT_1S               0x0080
#define EPOSMODULE_STATUS_RX_READY              0x0040
#define EPOSMODULE_STATUS_RX_OVERFLOW           0x0020
#define EPOSMODULE_STATUS_RX_FRAMING_ERROR      0x0010
#define EPOSMODULE_STATUS_RX_EVEN_PARITY        0x0008
#define EPOSMODULE_STATUS_HLDC_ABORT            0x0004
#define EPOSMODULE_STATUS_RX_2C_MODE            0x0002
#define EPOSMODULE_STATUS_FSK_OUT               0x0001
#define EPOSMODULE_STATUS_TONE_D                0x0000
#define EPOSMODULE_STATUS_TONE_1                0x0001
#define EPOSMODULE_STATUS_TONE_2                0x0002
#define EPOSMODULE_STATUS_TONE_3                0x0003
#define EPOSMODULE_STATUS_TONE_4                0x0004
#define EPOSMODULE_STATUS_TONE_5                0x0005
#define EPOSMODULE_STATUS_TONE_6                0x0006
#define EPOSMODULE_STATUS_TONE_7                0x0007
#define EPOSMODULE_STATUS_TONE_8                0x0008
#define EPOSMODULE_STATUS_TONE_9                0x0009
#define EPOSMODULE_STATUS_TONE_0                0x000A
#define EPOSMODULE_STATUS_TONE_STAR             0x000B
#define EPOSMODULE_STATUS_TONE_HASH             0x000C
#define EPOSMODULE_STATUS_TONE_A                0x000D
#define EPOSMODULE_STATUS_TONE_B                0x000E
#define EPOSMODULE_STATUS_TONE_C                0x000F
#define EPOSMODULE_STATUS_TONE_MASK             0x000F

/**
 * @brief EPOS Module QAM command register setting.
 * @details Specified setting for QAM command register of EPOS Module Click driver.
 */
#define EPOSMODULE_QAM_CMD_STOP_MODEM           0x0000
#define EPOSMODULE_QAM_CMD_INIT_RETRAIN         0x0008
#define EPOSMODULE_QAM_CMD_START_CALLING        0x0010
#define EPOSMODULE_QAM_CMD_START_ANSWER         0x0018
#define EPOSMODULE_QAM_CMD_INIT_RATE_RENEG      0x0020
#define EPOSMODULE_QAM_CMD_FAST_TRAIN_MASK      0x0020
#define EPOSMODULE_QAM_CMD_MAX_BITRATE_14400    0x0007
#define EPOSMODULE_QAM_CMD_MAX_BITRATE_12000    0x0006
#define EPOSMODULE_QAM_CMD_MAX_BITRATE_9600_TR  0x0005
#define EPOSMODULE_QAM_CMD_MAX_BITRATE_9600     0x0004
#define EPOSMODULE_QAM_CMD_MAX_BITRATE_7200     0x0003
#define EPOSMODULE_QAM_CMD_MAX_BITRATE_4800     0x0002
#define EPOSMODULE_QAM_CMD_MAX_BITRATE_2400     0x0001
#define EPOSMODULE_QAM_CMD_MAX_BITRATE_1200     0x0000
#define EPOSMODULE_QAM_CMD_MAX_BITRATE_MASK     0x0007

/**
 * @brief EPOS Module QAM status register setting.
 * @details Specified setting for QAM status register of EPOS Module Click driver.
 */
#define EPOSMODULE_QAM_STATUS_MSG_MASK          0xFC00
#define EPOSMODULE_QAM_STATUS_SNR_MASK          0x0070
#define EPOSMODULE_QAM_STATUS_MODE_MASK         0x000F

/**
 * @brief EPOS Module timeout and timing setting.
 * @details Specified setting for timeout and timing in milliseconds of EPOS Module Click driver.
 */
#define EPOSMODULE_TIMEOUT_CLEAR_IRQ            2000
#define EPOSMODULE_TIMEOUT_TX_READY             2000
#define EPOSMODULE_TIMEOUT_CALL_PROGRESS        60000
#define EPOSMODULE_TIMING_BUSY                  50
#define EPOSMODULE_TIMING_DISCONNECTED          250
#define EPOSMODULE_TIMING_RINGING               2000
#define EPOSMODULE_TIMING_CALL_PROGRESS         6000
#define EPOSMODULE_TIMING_SEND_MESSAGE          2000
#define EPOSMODULE_TIMING_RX_READY              10
#define EPOSMODULE_TIMING_WAIT_FOR_MESSAGE      10000

/**
 * @brief EPOS Module state setting.
 * @details Specified setting for state of EPOS Module Click driver.
 */
#define EPOSMODULE_STATE_IDLE                   0
#define EPOSMODULE_STATE_IRQ_SET                1
#define EPOSMODULE_STATE_RINGING                2
#define EPOSMODULE_STATE_CALL_IN_PROGRESS       3
#define EPOSMODULE_STATE_CALL_IN_PROGRESS       3

/**
 * @brief EPOS Module dial number setting.
 * @details Specified setting for dial number of EPOS Module Click driver.
 */
#define EPOSMODULE_DIAL_NUMBER_MAX_LEN          16

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b eposmodule_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define EPOSMODULE_SET_DATA_SAMPLE_EDGE         SET_SPI_DATA_SAMPLE_EDGE
#define EPOSMODULE_SET_DATA_SAMPLE_MIDDLE       SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // eposmodule_set

/**
 * @defgroup eposmodule_map EPOS Module MikroBUS Map
 * @brief MikroBUS pin mapping of EPOS Module Click driver.
 */

/**
 * @addtogroup eposmodule_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EPOS Module Click to the selected MikroBUS.
 */
#define EPOSMODULE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // eposmodule_map
/*! @} */ // eposmodule

/**
 * @brief EPOS Module Click context object.
 * @details Context object definition of EPOS Module Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t irq;               /**< Interrupt request pin (Active low). */

    // Modules
    spi_master_t spi;               /**< SPI driver object. */

    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */

    uint16_t control;               /**< Contains the control register last set value. */
    uint16_t tx_mode;               /**< Contains the tx mode register last set value. */
    uint16_t rx_mode;               /**< Contains the rx mode register last set value. */
    uint16_t status;                /**< Contains the status register last read value. */

} eposmodule_t;

/**
 * @brief EPOS Module Click configuration object.
 * @details Configuration object definition of EPOS Module Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t irq;                 /**< Interrupt request pin (Active low). */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} eposmodule_cfg_t;

/**
 * @brief EPOS Module Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EPOSMODULE_OK = 0,
    EPOSMODULE_ERROR = -1,
    EPOSMODULE_TIMEOUT = -2

} eposmodule_return_value_t;

/*!
 * @addtogroup eposmodule EPOS Module Click Driver
 * @brief API for configuring and manipulating EPOS Module Click driver.
 * @{
 */

/**
 * @brief EPOS Module configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #eposmodule_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void eposmodule_cfg_setup ( eposmodule_cfg_t *cfg );

/**
 * @brief EPOS Module initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #eposmodule_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_init ( eposmodule_t *ctx, eposmodule_cfg_t *cfg );

/**
 * @brief EPOS Module general reset function.
 * @details This function resets the device and clears all bits of the General Control,
 * Transmit Mode and Receive Mode Registers and b15 and b13-0 of the Status Register.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_general_reset ( eposmodule_t *ctx );

/**
 * @brief EPOS Module set control function.
 * @details This function controls general features of the CMX869B such as the Powersave,
 * Loopback mode and the IRQ mask bits. It also allows the fixed compromise equalisers in
 * the Tx and Rx signal paths to be disabled if desired.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @param[in] data_in : Control register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_set_control ( eposmodule_t *ctx, uint16_t data_in );

/**
 * @brief EPOS Module set transmit mode function.
 * @details This function controls the CMX869B transmit signal type and level.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @param[in] data_in : Transmit mode register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_set_transmit_mode ( eposmodule_t *ctx, uint16_t data_in );

/**
 * @brief EPOS Module set receive mode function.
 * @details This function controls the CMX869B receive signal type and level.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @param[in] data_in : Receive mode register data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_set_receive_mode ( eposmodule_t *ctx, uint16_t data_in );

/**
 * @brief EPOS Module transmit data function.
 * @details In Synchronous and HDLC Tx data modes all 8 bits of a byte are transmitted, bit 0 of each byte being 
 * transmitted first b0 is transmitted first. In Tx Start-Stop mode, the specified number of data bits will be
 * taken from the byte in the Tx Data Register (b0 of the byte first). A Start bit, a Parity bit (if required
 * and Stop bit(s) will be added automatically. This function should only be called when the Tx Data Ready bit
 * of the Status Register is set.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @param[in] data_in : Data to be transmitted.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function may be set to operate in 8- or 16-bit mode by b10 of the General Control Register.
 * This setting should not be changed once data transmission has started.
 */
err_t eposmodule_transmit_data ( eposmodule_t *ctx, uint16_t data_in );

/**
 * @brief EPOS Module receive data function.
 * @details In Synchronous and HDLC Rx data modes each byte contains 8 received data bits, b0 of the byte holding
 * the earliest received bit, b7 the latest. In Start-Stop modes each byte contains the specified number of data
 * bits from a received character, b0 of the byte holding the first received bit. Unused bits are set to 0. 
 * In HDLC mode, the FCS will be output in this register: it follows the last received data character. 
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @param[out] data_out : Output read data (two bytes in 16-bit mode).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function may be set to operate in 8- or 16-bit mode by b10 of the General Control Register.
 * This setting is only actioned following a reset or power-on.
 */
err_t eposmodule_receive_data ( eposmodule_t *ctx, uint8_t *data_out );

/**
 * @brief EPOS Module get status function.
 * @details This function reads the 16-bit status register data.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @param[out] data_out : 16-bit status register.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_get_status ( eposmodule_t *ctx, uint16_t *data_out );

/**
 * @brief EPOS Module set programming function.
 * @details This function is used to program the transmit and receive programmed tone pairs by writing appropriate
 * values to RAM locations within the CMX869B.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @param[in] data_in : Programming register data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_set_programming ( eposmodule_t *ctx, uint16_t data_in );

/**
 * @brief EPOS Module hook off function.
 * @details This function sets hookswitch to OFF state which closes the line interface.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_hook_off ( eposmodule_t *ctx );

/**
 * @brief EPOS Module hook on function.
 * @details This function sets hookswitch to ON state which opens the line interface.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_hook_on ( eposmodule_t *ctx );

/**
 * @brief EPOS Module get irq pin function.
 * @details This function returns the interrupt request (IRQ) pin logic state.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t eposmodule_get_irq_pin ( eposmodule_t *ctx );

/**
 * @brief EPOS Module ring detect function.
 * @details This function reads the status register and returns the ring detect flag.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @return @li @c 0 - Not ready,
 *         @li @c 1 - Ready.
 * @note None.
 */
uint8_t eposmodule_ring_detect ( eposmodule_t *ctx );

/**
 * @brief EPOS Module tx ready function.
 * @details This function reads the status register and returns the tx ready flag.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @return @li @c 0 - Not ready,
 *         @li @c 1 - Ready.
 * @note None.
 */
uint8_t eposmodule_tx_ready ( eposmodule_t *ctx );

/**
 * @brief EPOS Module rx ready function.
 * @details This function reads the status register and returns the rx ready flag.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @return @li @c 0 - Not ready,
 *         @li @c 1 - Ready.
 * @note None.
 */
uint8_t eposmodule_rx_ready ( eposmodule_t *ctx );

/**
 * @brief EPOS Module call progress function.
 * @details This function reads the status register and returns the rx energy or call progress flag.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @return @li @c 0 - Flag is not set,
 *         @li @c 1 - Flag is set.
 * @note None.
 */
uint8_t eposmodule_call_progress ( eposmodule_t *ctx );

/**
 * @brief EPOS Module unscram 1s det function.
 * @details This function reads the status register and sets the return flag if continuous ones
 * and rx energy flags are detected.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @return @li @c 0 - Flag is not set,
 *         @li @c 1 - Flag is set.
 * @note None.
 */
uint8_t eposmodule_unscram_1s_det ( eposmodule_t *ctx );

/**
 * @brief EPOS Module clear interrupts function.
 * @details This function reads the status register in a loop until the IRQ flag is cleared.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * @note None.
 */
err_t eposmodule_clear_interrupts ( eposmodule_t *ctx );

/**
 * @brief EPOS Module handshake init function.
 * @details This function performs a handshake init which resets the device settings to default.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_handshake_init ( eposmodule_t *ctx );

/**
 * @brief EPOS Module dial function.
 * @details This function dials the selected number by alternating between DTMF and No-tone.
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @param[in] dial_num : Dial number string [up to 16 digits].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_dial ( eposmodule_t *ctx, uint8_t *dial_num );

/**
 * @brief EPOS Module send message function.
 * @details This function sends an array of bytes via V.23 FSK 1200bps modem in start-stop 8.1 mode. 
 * @param[in] ctx : Click context object.
 * See #eposmodule_t object definition for detailed explanation.
 * @param[in] data_in : Array of bytes.
 * @param[in] len : Number of bytes to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t eposmodule_send_message ( eposmodule_t *ctx, uint8_t *data_in, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif // EPOSMODULE_H

/*! @} */ // eposmodule

// ------------------------------------------------------------------------ END
