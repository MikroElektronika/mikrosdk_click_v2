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
 * @file speedradar.h
 * @brief This file contains API for Speed Radar Click Driver.
 */

#ifndef SPEEDRADAR_H
#define SPEEDRADAR_H

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
 * @addtogroup speedradar Speed Radar Click Driver
 * @brief API for configuring and manipulating Speed Radar Click driver.
 * @{
 */

/**
 * @defgroup speedradar_cmd Speed Radar Device Settings
 * @brief Settings for command of Speed Radar Click driver.
 */

/**
 * @addtogroup speedradar_cmd
 * @{
 */

/**
 * @brief Speed Radar control commands.
 * @details Specified setting for control commands of Speed Radar Click driver.
 */
#define SPEEDRADAR_CMD_PREFIX               "$"
#define SPEEDRADAR_CMD_ENTER                "\r\n"
#define SPEEDRADAR_CMD_RSP_PREFIX_VAL        0x40
#define SPEEDRADAR_ASCII_CHAR_0              48
#define SPEEDRADAR_NO_DET                    0
#define SPEEDRADAR_MLP_TENS                  10
#define SPEEDRADAR_MLP_HUNDREDS              100

/**
 * @brief Speed Radar class S 8-Bit system parameters.
 * @details Specified setting for class S 8-Bit system parameters 
 * of Speed Radar Click driver.
 */
#define SPEEDRADAR_CMD_SAMPLING_RATE        "S04"
#define SPEEDRADAR_CMD_START_UP_LEARN       "S05"
#define SPEEDRADAR_CMD_FUN_MISC_OUT         "S06"
#define SPEEDRADAR_CMD_THOLD_OFFSET_MIN     "S07"
#define SPEEDRADAR_CMD_THOLD_OFFSET_MAX     "S08"
#define SPEEDRADAR_CMD_THOLD_NOISE          "S09"
#define SPEEDRADAR_CMD_FFT_AVERAGE          "S0A"
#define SPEEDRADAR_CMD_SENS_POT             "S0B"
#define SPEEDRADAR_CMD_HOLD_TIME_POT        "S0C"
#define SPEEDRADAR_CMD_MICRO_DETECTION      "S0D"

/**
 * @brief Speed Radar class D 8-Bit detection parameters.
 * @details Specified setting for class D 8-Bit detection parameters 
 * of Speed Radar Click driver.
 */
#define SPEEDRADAR_CMD_HOLD_TIME            "D00"
#define SPEEDRADAR_CMD_SENSITIVITY          "D01"
#define SPEEDRADAR_CMD_IMMUNITY             "D02"
#define SPEEDRADAR_CMD_DIR_DETECT           "D03"
#define SPEEDRADAR_CMD_SPEED_LIM_LOW        "D04"
#define SPEEDRADAR_CMD_SPEED_LIM_HIGH       "D05"
#define SPEEDRADAR_CMD_THOLD_SPEED_RANGE    "D06"
#define SPEEDRADAR_CMD_THOLD_MICRO_DET      "D07"
#define SPEEDRADAR_CMD_FFT_FILTER_WIDTH     "D08"

/**
 * @brief Speed Radar class A 16-Bit array parameters.
 * @details Specified setting for class A 16-Bit array parameters 
 * of Speed Radar Click driver.
 */
#define SPEEDRADAR_CMD_HOLD_TIME_0          "A00"
#define SPEEDRADAR_CMD_HOLD_TIME_1          "A01"
#define SPEEDRADAR_CMD_HOLD_TIME_2          "A02"
#define SPEEDRADAR_CMD_HOLD_TIME_3          "A03"
#define SPEEDRADAR_CMD_HOLD_TIME_4          "A04"
#define SPEEDRADAR_CMD_HOLD_TIME_5          "A05"
#define SPEEDRADAR_CMD_HOLD_TIME_6          "A06"
#define SPEEDRADAR_CMD_HOLD_TIME_7          "A07"
#define SPEEDRADAR_CMD_HOLD_TIME_8          "A08"
#define SPEEDRADAR_CMD_HOLD_TIME_9          "A09"
#define SPEEDRADAR_CMD_HOLD_TIME_10         "A10"
#define SPEEDRADAR_CMD_HOLD_TIME_11         "A11"
#define SPEEDRADAR_CMD_HOLD_TIME_12         "A12"
#define SPEEDRADAR_CMD_HOLD_TIME_13         "A13"
#define SPEEDRADAR_CMD_HOLD_TIME_14         "A14"
#define SPEEDRADAR_CMD_HOLD_TIME_15         "A15"
#define SPEEDRADAR_CMD_HOLD_TIME_16         "A16"
#define SPEEDRADAR_CMD_HOLD_TIME_17         "A17"
#define SPEEDRADAR_CMD_HOLD_TIME_18         "A18"
#define SPEEDRADAR_CMD_HOLD_TIME_19         "A19"
#define SPEEDRADAR_CMD_HOLD_TIME_20         "A20"
#define SPEEDRADAR_CMD_HOLD_TIME_21         "A21"
#define SPEEDRADAR_CMD_HOLD_TIME_22         "A22"
#define SPEEDRADAR_CMD_HOLD_TIME_23         "A23"
#define SPEEDRADAR_CMD_HOLD_TIME_24         "A24"
#define SPEEDRADAR_CMD_HOLD_TIME_25         "A25"
#define SPEEDRADAR_CMD_HOLD_TIME_26         "A26"
#define SPEEDRADAR_CMD_HOLD_TIME_27         "A27"
#define SPEEDRADAR_CMD_HOLD_TIME_28         "A28"
#define SPEEDRADAR_CMD_HOLD_TIME_29         "A29"

/**
 * @brief Speed Radar class F 16-Bit flash read parameters.
 * @details Specified setting for class F 16-Bit flash read parameters 
 * of Speed Radar Click driver.
 */
#define SPEEDRADAR_CMD_GET_SW_VERSION       "F00"
#define SPEEDRADAR_CMD_GET_TYPE_OF_DEVICE   "F01"

/**
 * @brief Speed Radar class R 8-Bit real-time read parameters.
 * @details Specified setting for class R 8-Bit real-time read parameters 
 * of Speed Radar Click driver.
 */
#define SPEEDRADAR_CMD_GET_DET_REG          "R00"
#define SPEEDRADAR_CMD_GET_DET_SPEED        "R01"
#define SPEEDRADAR_CMD_GET_DET_MAG          "R02"
#define SPEEDRADAR_CMD_GET_NOISE_LVL        "R03"
#define SPEEDRADAR_CMD_GET_OP_STATE         "R04"
#define SPEEDRADAR_CMD_GET_H_TIME_POT_IDX   "R05"
#define SPEEDRADAR_CMD_GET_SENS_POT_IDX     "R06"

/**
 * @brief Speed Radar class W 8-Bit basic write parameters.
 * @details Specified setting for class W 8-Bit basic write parameters 
 * of Speed Radar Click driver.
 */
#define SPEEDRADAR_CMD_RESET_PROCESSOR      "W00"
#define SPEEDRADAR_CMD_RST_FAC_STG          "W01"
#define SPEEDRADAR_CMD_SET_UART_BAUD_RATE   "W02"

/**
 * @brief Speed Radar class C variable length complex read parameters.
 * @details Specified setting for class C variable length complex read parameters 
 * of Speed Radar Click driver.
 */
#define SPEEDRADAR_CMD_GET_DETECTION_STR    "C00"
#define SPEEDRADAR_CMD_GET_TARGET_STR       "C01"
#define SPEEDRADAR_CMD_GET_EEPROM           "C02"
#define SPEEDRADAR_CMD_GET_FFT_SPECTRUM     "C03"
#define SPEEDRADAR_CMD_GET_ADC_IQ           "C04"
#define SPEEDRADAR_CMD_GET_ADC_IQ_ADD_PARAM "C05"
#define SPEEDRADAR_CMD_GET_ALL_DATA         "C06"

/**
 * @brief Speed Radar class T 8-Bit testing parameters.
 * @details Specified setting for class T 8-Bit testing parameters 
 * of Speed Radar Click driver.
 */
#define SPEEDRADAR_CMD_ACT_TEST_MODE        "T00"
#define SPEEDRADAR_CMD_FORCE_DET_OUT        "T01"
#define SPEEDRADAR_CMD_FORCE_MISC_OUT       "T02"

/**
 * @brief Speed Radar sampling rate parameters.
 * @details Specified sampling rate parameters of Speed Radar Click driver.
 */
#define SPEEDRADAR_SET_SAMPLING_RATE_X1     "01"
#define SPEEDRADAR_SET_SAMPLING_RATE_X2     "02"
#define SPEEDRADAR_SET_SAMPLING_RATE_X3     "03"
#define SPEEDRADAR_SET_SAMPLING_RATE_X4     "04"
#define SPEEDRADAR_SET_SAMPLING_RATE_X5     "05"
#define SPEEDRADAR_SET_SAMPLING_RATE_X6     "06"
#define SPEEDRADAR_SET_SAMPLING_RATE_X7     "07"
#define SPEEDRADAR_SET_SAMPLING_RATE_X8     "08"
#define SPEEDRADAR_SET_SAMPLING_RATE_X9     "09"
#define SPEEDRADAR_SET_SAMPLING_RATE_X10    "0A"

/**
 * @brief Speed Radar sampling rate values.
 * @details Specified sampling rate values of Speed Radar Click driver.
 */
#define SPEEDRADAR_SAMPLING_RATE_1280_HZ    1280.0f
#define SPEEDRADAR_SAMPLING_RATE_2560_HZ    2560.0f
#define SPEEDRADAR_SAMPLING_RATE_3840_HZ    3840.0f
#define SPEEDRADAR_SAMPLING_RATE_5120_HZ    5120.0f
#define SPEEDRADAR_SAMPLING_RATE_6400_HZ    6400.0f
#define SPEEDRADAR_SAMPLING_RATE_7680_HZ    7680.0f
#define SPEEDRADAR_SAMPLING_RATE_8960_HZ    8960.0f
#define SPEEDRADAR_SAMPLING_RATE_10240_HZ   10240.0f
#define SPEEDRADAR_SAMPLING_RATE_11520_HZ   11520.0f
#define SPEEDRADAR_SAMPLING_RATE_12800_HZ   12800.0f

/**
 * @brief Speed Radar miscellaneous output parameters.
 * @details Specified function of miscellaneous output parameters of Speed Radar Click driver.
 */
#define SPEEDRADAR_SET_MISC_OUT_DET         "00"
#define SPEEDRADAR_SET_MISC_OUT_DIR         "01"
#define SPEEDRADAR_SET_MISC_OUT_RNG         "02"
#define SPEEDRADAR_SET_MISC_OUT_MDET        "03"

/**
 * @brief Speed Radar class R 8-Bit real-time read parameters, respond values bit mask.
 * @details Specified respond values of class R 8-Bit real-time read parameters of Speed Radar Click driver.
 */
#define SPEEDRADAR_R00_DET_NO               0x00
#define SPEEDRADAR_R00_DET_VALID            0x01
#define SPEEDRADAR_R00_DIR_BACKWARD         0x00
#define SPEEDRADAR_R00_DIR_FORWARD          0x02
#define SPEEDRADAR_R00_RANGE_LOW_SPEED      0x00
#define SPEEDRADAR_R00_RANGE_HIGH_SPEED     0x04
#define SPEEDRADAR_R00_MICRO_DET_NO         0x00
#define SPEEDRADAR_R00_MICRO_DET_VALID      0x08

/**
 * @brief Speed Radar error messages parameters.
 * @details Specified error messages parameters of Speed Radar Click driver.
 */
#define SPEEDRADAR_ERR_MSG                  "@E0"
#define SPEEDRADAR_ERR_VAL_OUT_LIM          "@E01"
#define SPEEDRADAR_ERR_PAR_NUM_NOT_EXIST    "@E02"
#define SPEEDRADAR_ERR_CMD_NOT_EXIST        "@E03"
#define SPEEDRADAR_ERR_WR_EEPROM            "@E04"
#define SPEEDRADAR_ERR_CMD_FORMAT           "@E05"
#define SPEEDRADAR_ERR_UART_COMM            "@E06"

/**
 * @brief Speed Radar driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define SPEEDRADAR_TX_DRV_BUFFER_SIZE       100
#define SPEEDRADAR_RX_DRV_BUFFER_SIZE       200

/*! @} */ // speedradar_cmd

/**
 * @defgroup speedradar_map Speed Radar MikroBUS Map
 * @brief MikroBUS pin mapping of Speed Radar Click driver.
 */

/**
 * @addtogroup speedradar_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Speed Radar Click to the selected MikroBUS.
 */
#define SPEEDRADAR_MAP_MIKROBUS( cfg, mikrobus )     \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN );     \
    cfg.det = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // speedradar_map
/*! @} */ // speedradar

/**
 * @brief Speed Radar Click context object.
 * @details Context object definition of Speed Radar Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t dir;    /**< Digital miscellaneous pin. */
    digital_in_t det;    /**< Digital detection pin. */

    // Modules
    uart_t uart;         /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ SPEEDRADAR_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ SPEEDRADAR_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} speedradar_t;

/**
 * @brief Speed Radar Click configuration object.
 * @details Configuration object definition of Speed Radar Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;    /**< RX pin. */
    pin_name_t tx_pin;    /**< TX pin. */

    // Additional gpio pins
    pin_name_t dir;       /**< Digital miscellaneous pin. */
    pin_name_t det;       /**< Digital detection pin. */

    // Static variable
    uint32_t         baud_rate;        /**< Clock speed. */
    bool             uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;         /**< Data bits. */
    uart_parity_t    parity_bit;       /**< Parity bit. */
    uart_stop_bits_t stop_bit;         /**< Stop bits. */

} speedradar_cfg_t;

/**
 * @brief Speed Radar Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SPEEDRADAR_OK = 0,
    SPEEDRADAR_ERROR = -1

} speedradar_return_value_t;

/*!
 * @addtogroup speedradar Speed Radar Click Driver
 * @brief API for configuring and manipulating Speed Radar Click driver.
 * @{
 */

/**
 * @brief Speed Radar configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #speedradar_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void speedradar_cfg_setup ( speedradar_cfg_t *cfg );

/**
 * @brief Speed Radar initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #speedradar_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #speedradar_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speedradar_init ( speedradar_t *ctx, speedradar_cfg_t *cfg );

/**
 * @brief Speed Radar default configuration function.
 * @details This function executes a default configuration of Speed Radar
 * click board.
 * @param[in] ctx : Click context object.
 * See #speedradar_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t speedradar_default_cfg ( speedradar_t *ctx );

/**
 * @brief Speed Radar data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #speedradar_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speedradar_generic_write ( speedradar_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief Speed Radar data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #speedradar_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speedradar_generic_read ( speedradar_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Speed Radar send command function.
 * @details This function sends a desired command 
 * of the K-LD2, radar transceiver on the Speed Radar click board™. 
 * @param[in] ctx : Click context object.
 * See #speedradar_t object definition for detailed explanation.
 * @param[in] cmd : Command data array.
 * See #speedradar_cmd definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speedradar_send_command ( speedradar_t *ctx, uint8_t *cmd );

/**
 * @brief Speed Radar send command function.
 * @details This function sends a desired command 
 * of the K-LD2, radar transceiver on the Speed Radar click board™. 
 * @param[in] ctx : Click context object.
 * See #speedradar_t object definition for detailed explanation.
 * @param[in] cmd : Command data array.
 * See #speedradar_cmd definition for detailed explanation.
 * @param[in] cmd_value : Command value data [(Hex) 8-Bit or 16-Bit wide].
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t speedradar_send_command_value ( speedradar_t *ctx, uint8_t *cmd, uint8_t *cmd_value );

/**
 * @brief Speed Radar get direction function.
 * @details This function return state of the direction of a movement
 * of the K-LD2, radar transceiver on the Speed Radar click board™. 
 * @param[in] ctx : Click context object.
 * See #speedradar_t object definition for detailed explanation.
 * @return @li @c 0 - Backward/receding movement,
 *         @li @c 1 - Forward/approaching movement.
 * @note Detection of the direction of a movement is default configuration 
 * of the miscellaneous output pin. 
 * Supported configurations: 
 *         @li @c Detection,
 *         @li @c Direction,
 *         @li @c Range,
 *         @li @c Micro-Detection.
 */
uint8_t speedradar_get_direction ( speedradar_t *ctx );

/**
 * @brief Speed Radar get detection function.
 * @details This function return state of the detection of a movement
 * of the K-LD2, radar transceiver on the Speed Radar click board™. 
 * @param[in] ctx : Click context object.
 * See #speedradar_t object definition for detailed explanation.
 * @return @li @c 0 - No detection,
 *         @li @c 1 - Valid detection.
 * @note None.
 */
uint8_t speedradar_get_detection ( speedradar_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SPEEDRADAR_H

/*! @} */ // speedradar

// ------------------------------------------------------------------------ END
