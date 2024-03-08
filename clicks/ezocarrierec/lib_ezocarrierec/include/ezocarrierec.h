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
 * @file ezocarrierec.h
 * @brief This file contains API for EZO Carrier EC Click Driver.
 */

#ifndef EZOCARRIEREC_H
#define EZOCARRIEREC_H

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
#include "drv_i2c_master.h"
#include "drv_uart.h"

/*!
 * @addtogroup ezocarrierec EZO Carrier EC Click Driver
 * @brief API for configuring and manipulating EZO Carrier EC Click driver.
 * @{
 */

/**
 * @defgroup ezocarrierec_cmd EZO Carrier EC Device Settings
 * @brief Settings for registers of EZO Carrier EC Click driver.
 */

/**
 * @addtogroup ezocarrierec_cmd
 * @{
 *

/**
 * @brief EZO Carrier EC control commands.
 * @details Specified setting for control commands of EZO Carrier EC Click driver.
 */
#define EZOCARRIEREC_CMD_BAUD                   "Baud"
#define EZOCARRIEREC_CMD_CONT_READ              "C"
#define EZOCARRIEREC_CMD_CAL                    "Cal"
#define EZOCARRIEREC_CMD_EXPORT                 "Export"
#define EZOCARRIEREC_CMD_FACTORY                "Factory"
#define EZOCARRIEREC_CMD_FIND                   "Find"
#define EZOCARRIEREC_CMD_DEV_INFO               "i"
#define EZOCARRIEREC_CMD_I2C                    "I2C"
#define EZOCARRIEREC_CMD_IMPORT                 "Import"
#define EZOCARRIEREC_CMD_SET_PROBE_TYPE         "K"
#define EZOCARRIEREC_CMD_LED                    "L"
#define EZOCARRIEREC_CMD_NAME                   "Name"
#define EZOCARRIEREC_CMD_PARAMETERS             "O"
#define EZOCARRIEREC_CMD_PROTOCOL_LOCK          "Plock"
#define EZOCARRIEREC_CMD_SINGLE_READ            "R"
#define EZOCARRIEREC_CMD_SLEEP                  "Sleep"
#define EZOCARRIEREC_CMD_STATUS                 "Status"
#define EZOCARRIEREC_CMD_TEMP_COMPENSATION      "T"
#define EZOCARRIEREC_CMD_TDS                    "TDS"
#define EZOCARRIEREC_CMD_RESP_CODES             "*OK"
#define EZOCARRIEREC_CMD_END_COMMAND            "\r"

/**
 * @brief EZO Carrier EC response codes.
 * @details Specified setting for response codes of EZO Carrier EC Click driver.
 */
#define EZOCARRIEREC_RSP_OK                     "*OK"
#define EZOCARRIEREC_RSP_ERROR                  "*ER"
#define EZOCARRIEREC_RSP_OVER_VOLT              "*OV"
#define EZOCARRIEREC_RSP_UNDER_VOLT             "*UV"
#define EZOCARRIEREC_RSP_RESET                  "*RS"
#define EZOCARRIEREC_RSP_READY                  "*RE"
#define EZOCARRIEREC_RSP_SLEEP                  "*SL"
#define EZOCARRIEREC_RSP_WAKE_UP                "*WA"

/**
 * @brief EZO Carrier EC driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define EZOCARRIEREC_TX_DRV_BUFFER_SIZE         100
#define EZOCARRIEREC_RX_DRV_BUFFER_SIZE         300

/*! @} */ // ezocarrierec_cmd

/**
 * @brief EZO Carrier EC device address setting.
 * @details Specified setting for device slave address selection of
 * EZO Carrier EC Click driver.
 */
#define EZOCARRIEREC_DEVICE_ADDRESS             0x61

/**
 * @defgroup ezocarrierec_map EZO Carrier EC MikroBUS Map
 * @brief MikroBUS pin mapping of EZO Carrier EC Click driver.
 */

/**
 * @addtogroup ezocarrierec_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EZO Carrier EC Click to the selected MikroBUS.
 */
#define EZOCARRIEREC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX )

/*! @} */ // ezocarrierec_map
/*! @} */ // ezocarrierec

/**
 * @brief EZO Carrier EC Click driver selector.
 * @details Selects target driver interface of EZO Carrier EC Click driver.
 */
typedef enum
{
    EZOCARRIEREC_DRV_SEL_I2C,       /**< I2C driver descriptor. */
    EZOCARRIEREC_DRV_SEL_UART       /**< UART driver descriptor. */

} ezocarrierec_drv_t;

/**
 * @brief EZO Carrier EC Click context object.
 * @details Context object definition of EZO Carrier EC Click driver.
 */
typedef struct
{
    // Modules
    uart_t uart;                                /**< UART driver object. */
    i2c_master_t i2c;                           /**< I2C driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ EZOCARRIEREC_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ EZOCARRIEREC_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

    ezocarrierec_drv_t drv_sel;                 /**< Master driver interface selector. */

} ezocarrierec_t;

/**
 * @brief EZO Carrier EC Click configuration object.
 * @details Configuration object definition of EZO Carrier EC Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */
    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */
    ezocarrierec_drv_t drv_sel;                 /**< Master driver interface selector. */

} ezocarrierec_cfg_t;

/**
 * @brief EZO Carrier EC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EZOCARRIEREC_OK = 0,
    EZOCARRIEREC_ERROR = -1,
    EZOCARRIEREC_ERROR_TIMEOUT = -2

} ezocarrierec_return_value_t;

/*!
 * @addtogroup ezocarrierec EZO Carrier EC Click Driver
 * @brief API for configuring and manipulating EZO Carrier EC Click driver.
 * @{
 */

/**
 * @brief EZO Carrier EC configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ezocarrierec_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ezocarrierec_cfg_setup ( ezocarrierec_cfg_t *cfg );

/**
 * @brief EZO Carrier EC driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #ezocarrierec_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #ezocarrierec_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void ezocarrierec_drv_interface_sel ( ezocarrierec_cfg_t *cfg, ezocarrierec_drv_t drv_sel ) ;

/**
 * @brief EZO Carrier EC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ezocarrierec_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ezocarrierec_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierec_init ( ezocarrierec_t *ctx, ezocarrierec_cfg_t *cfg );

/**
 * @brief EZO Carrier EC data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ezocarrierec_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierec_generic_write ( ezocarrierec_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief EZO Carrier EC data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ezocarrierec_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierec_generic_read ( ezocarrierec_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #ezocarrierec_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierec_send_cmd ( ezocarrierec_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #ezocarrierec_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierec_send_cmd_with_par ( ezocarrierec_t *ctx, uint8_t *cmd, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ezocarrierec_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierec_send_cmd_check ( ezocarrierec_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // EZOCARRIEREC_H

/*! @} */ // ezocarrierec

// ------------------------------------------------------------------------ END
