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
 * @file spirit.h
 * @brief This file contains API for SPIRIT Click Driver.
 */

#ifndef SPIRIT_H
#define SPIRIT_H

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

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define SPIRIT_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.cmd = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.shd = MIKROBUS( mikrobus, MIKROBUS_PWM )
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define SPIRIT_MODULE_POWER_ON   1
#define SPIRIT_MODULE_POWER_OFF  0
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
#define DRV_TX_BUFFER_SIZE 200
/** \} */

/**
 * \defgroup mode  Mode
 * \{
 */
#define SPIRIT_OPERATING_MODE     0x01
#define SPIRIT_COMMAND_MODE       0x00

#define SPIRIT_MODULE_WAKE_UP     0x01
#define SPIRIT_MODULE_SHUTDOWN    0x00
/** \} */
 
/**
 * \defgroup  spirit_at_command_standard  Spirit at command standard
 * \{
 */
#define SPIRIT_CMD_ENTER_COMMAND_MODE    "+++"
#define SPIRIT_CMD_ENTER_OPERATING_MODE  "ATO"
#define SPIRIT_CMD_READ_MODULE_VERSION   "AT/V"
#define SPIRIT_CMD_READ_ALL_CONFIG_REG   "AT/S"
#define SPIRIT_CMD_STORE_CURRENT_CONFIG  "AT/C"
#define SPIRIT_CMD_RESET_CONFIG          "ATR"
#define SPIRIT_CMD_RESET_MODULE          "ATZ"
/** \} */
 
/**
 * \defgroup information_register Information register
 * \{
 */
#define SPIRIT_CMD_READ_INFO_PER             "ATI0"
#define SPIRIT_CMD_READ_INFO_PSSI            "ATI1"
#define SPIRIT_CMD_READ_INFO_LQI             "ATI2"
#define SPIRIT_CMD_READ_INFO_PQI             "ATI3"
#define SPIRIT_CMD_READ_INFO_SQI             "ATI4"
#define SPIRIT_CMD_READ_INFO_PACKET_COUNT    "ATI5"
#define SPIRIT_CMD_READ_INFO_PACKETS_LOST    "ATI6"
/** \} */
 
/**
 * \defgroup configuration_register  Configuration register
 * \{
 */
#define SPIRIT_CMD_CFG_BAUD_RATE               "ATS00"
#define SPIRIT_CMD_CFG_FREQUENCY               "ATS01"
#define SPIRIT_CMD_CFG_DATA_RATE               "ATS02"
#define SPIRIT_CMD_CFG_MODULATION              "ATS03"
#define SPIRIT_CMD_CFG_OUTPUT_POWER            "ATS04"
#define SPIRIT_CMD_CFG_FREQ_DEVIATION          "ATS05"
#define SPIRIT_CMD_CFG_RX_FILTER               "ATS06"
#define SPIRIT_CMD_CFG_CS_MODE                 "ATS07"
#define SPIRIT_CMD_CFG_RSSI_THRESHOLD          "ATS08"
#define SPIRIT_CMD_CFG_PREAMBLE_LEN            "ATS09"
#define SPIRIT_CMD_CFG_SYNC_LENGTH             "ATS10"
#define SPIRIT_CMD_CFG_SYNC_VALUE              "ATS11"
#define SPIRIT_CMD_CFG_CRC_MODE                "ATS12"
#define SPIRIT_CMD_CFG_WHITENING               "ATS13"
#define SPIRIT_CMD_CFG_FEC                     "ATS14"
#define SPIRIT_CMD_CFG_SOURCE_ADDR             "ATS15"
#define SPIRIT_CMD_CFG_DESTINATION_ADDR        "ATS16"
#define SPIRIT_CMD_CFG_MULTICAST_ADDR          "ATS17"
#define SPIRIT_CMD_CFG_BROADCAST_ADDR          "ATS18"
#define SPIRIT_CMD_CFG_FILTER_CRC              "ATS19"
#define SPIRIT_CMD_CFG_FILTER_SOURCE           "ATS20"
#define SPIRIT_CMD_CFG_FILTER_DESTINATION      "ATS21"
#define SPIRIT_CMD_CFG_FILTER_MULTICAST        "ATS22"
#define SPIRIT_CMD_CFG_FILTER_BROADCAST        "ATS23"
#define SPIRIT_CMD_CFG_TXRX_LED                "ATS24"
#define SPIRIT_CMD_CFG_ESCAPE_SEQ              "ATS26"
#define SPIRIT_CMD_CFG_SOURCE_FILT_MASK        "ATS27"
#define SPIRIT_CMD_CFG_PAYLOAD_SIZE            "ATS28"
/** \} */

/**
 * \defgroup config_parameters  Config parameters
 * \{
 */
#define SPIRIT_PCFG_ENABLE    "1"
#define SPIRIT_PCFG_DISABLE   "0"
/** \} */
 
/**
 * \defgroup baud_rate Baud rate
 * \{
 */
#define SPIRIT_PCFG_BAUD_RATE_9600     "9600"
#define SPIRIT_PCFG_BAUD_RATE_19200    "19200"
#define SPIRIT_PCFG_BAUD_RATE_38400    "38400"
#define SPIRIT_PCFG_BAUD_RATE_56000    "56000"
#define SPIRIT_PCFG_BAUD_RATE_57600    "57600"
#define SPIRIT_PCFG_BAUD_RATE_115200   "115200"
#define SPIRIT_PCFG_BAUD_RATE_128000   "128000"
#define SPIRIT_PCFG_BAUD_RATE_256000   "256000"
/** \} */
 
/**
 * \defgroup cs_mode  CS mode
 * \{
 */
#define SPIRIT_PCFG_CSMODE_STATIC_SENSING          "0"
#define SPIRIT_PCFG_CSMODE_DYNAMIC_SENSING_6dB     "1"
#define SPIRIT_PCFG_CSMODE_DYNAMIC_SENSING_12dB    "2"
#define SPIRIT_PCFG_CSMODE_DYNAMIC_SENSING_18dB    "3"
/** \} */
 
/**
 * \defgroup crc_mode  CRC mode
 * \{
 */
#define SPIRIT_PCFG_CRCMODE_POLY_0x07       "1"
#define SPIRIT_PCFG_CRCMODE_POLY_0x8005     "2"
#define SPIRIT_PCFG_CRCMODE_POLY_0x1021     "3"
#define SPIRIT_PCFG_CRCMODE_POLY_0x864CFB   "4"
/** \} */
 
/**
 * \defgroup tx_rx_led  TX RX led
 * \{
 */
#define SPIRIT_PCFG_TXRXLED_DISABLED        "0"
#define SPIRIT_PCFG_TXRXLED_OPEN_DRAIN      "1"
#define SPIRIT_PCFG_TXRXLED_PUSH_PULL       "2"
/** \} */
 
/**
 * \defgroup modulation  Modulation
 * \{
 */
#define SPIRIT_PCFG_MODULATION_2_FSK        "0"
#define SPIRIT_PCFG_MODULATION_GFSK05       "1"
#define SPIRIT_PCFG_MODULATION_GFSK1        "2"
#define SPIRIT_PCFG_MODULATION_GMSK         "3"
#define SPIRIT_PCFG_MODULATION_OOK          "4"
#define SPIRIT_PCFG_MODULATION_ASK          "5"
/** \} */
 
/**
 * \defgroup test_mode  Test mode
 * \{
 */
#define SPIRIT_CMD_SET_RF_TEST_MODE_DISABLE  "AT/T0"
#define SPIRIT_CMD_SET_RF_TEST_MODE_PN9      "AT/T1"
#define SPIRIT_CMD_SET_RF_TEST_MODE_CW       "AT/T2"
/** \} */

/**
 * @brief SPIRIT Click context object.
 * @details Context object definition of SPIRIT Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;     /**< Description. */
    digital_out_t cmd;       /**< Description. */
    digital_out_t shd;     /**< Description. */

    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];         /**< Buffer size. */

} spirit_t;

/**
 * @brief SPIRIT Click configuration object.
 * @details Configuration object definition of SPIRIT Click driver.
 */
typedef struct
{
    // Communication gpio pins
    
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
    
    pin_name_t rst;        /**< Description. */
    pin_name_t cmd;          /**< Description. */
    pin_name_t shd;        /**< Description. */

    // Static variable
    
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} spirit_cfg_t;

/**
 * @brief SPIRIT Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   SPIRIT_OK = 0,
   SPIRIT_ERROR = -1

} spirit_return_value_t;

/*!
 * @addtogroup spirit SPIRIT Click Driver
 * @brief API for configuring and manipulating SPIRIT Click driver.
 * @{
 */

/**
 * @brief SPIRIT configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #spirit_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void spirit_cfg_setup ( spirit_cfg_t *cfg );

/**
 * @brief SPIRIT initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #spirit_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #spirit_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t spirit_init ( spirit_t *ctx, spirit_cfg_t *cfg );

/**
 * @brief Power module function.
 * @details Function for power mode of SPIRIT click.
 * @param ctx           Click object.
 * @param power_state   State of PWM pin
 * @return Nothing.
 * @note None.
 */
void spirit_power_module ( spirit_t *ctx, uint8_t power_state );

/**
 * @brief Software reset function.
 * @details Function for reseting SPIRIT click.
 * @param ctx           Click object.
 * @return Nothing.
 * @note None.
 */
void spirit_reset ( spirit_t *ctx );

/**
 * @brief Set mode function.
 * @details Function for setting mode of SPIRIT click.
 * @param ctx           Click object.
 * @param mode          Set mode.
 * @return Nothing.
 * @note None.
 */
void spirit_set_mode ( spirit_t *ctx, uint8_t mode );

/**
 * @brief SPIRIT data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #spirit_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void spirit_generic_write ( spirit_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief SPIRIT data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #spirit_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
int32_t spirit_generic_read ( spirit_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #spirit_t object definition for detailed explanation.
 * @param[in] cmd  Command variable.
 *
 * @return Nothing.
 */
void spirit_send_cmd ( spirit_t *ctx, char *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends commands to the click module.
 * @param[in] ctx : Click context object.
 * See #spirit_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @param[in] param_buf  Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void spirit_send_cmd_with_parameter ( spirit_t *ctx, char *at_cmd_buf, char *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #spirit_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void spirit_send_cmd_check ( spirit_t *ctx, char *at_cmd_buf );

/**
 * @brief Check the command parameters.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #spirit_t object definition for detailed explanation.
 * @param[in] at_cmd_buf  Command buffer.
 * @return Nothing.
 * @note None.
 */
void spirit_send_cmd_parameter_check ( spirit_t *ctx, char *at_cmd_buf );

#ifdef __cplusplus
}
#endif
#endif // SPIRIT_H

/*! @} */ // spirit

// ------------------------------------------------------------------------ END
