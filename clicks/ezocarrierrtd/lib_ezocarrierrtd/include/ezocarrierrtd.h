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
 * @file ezocarrierrtd.h
 * @brief This file contains API for EZO Carrier RTD Click Driver.
 */

#ifndef EZOCARRIERRTD_H
#define EZOCARRIERRTD_H

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
 * @addtogroup ezocarrierrtd EZO Carrier RTD Click Driver
 * @brief API for configuring and manipulating EZO Carrier RTD Click driver.
 * @{
 */

/**
 * @defgroup ezocarrierrtd_cmd EZO Carrier RTD Device Settings
 * @brief Settings for registers of EZO Carrier RTD Click driver.
 */

/**
 * @addtogroup ezocarrierrtd_cmd
 * @{
 */

/**
 * @brief EZO Carrier RTD control commands.
 * @details Specified setting for control commands of EZO Carrier RTD Click driver.
 */
#define EZOCARRIERRTD_CMD_BAUD                  "Baud"
#define EZOCARRIERRTD_CMD_CONT_READ             "C"
#define EZOCARRIERRTD_CMD_CAL                   "Cal"
#define EZOCARRIERRTD_CMD_DATA_LOGGER           "D"
#define EZOCARRIERRTD_CMD_EXPORT                "Export"
#define EZOCARRIERRTD_CMD_FACTORY               "Factory"
#define EZOCARRIERRTD_CMD_FIND                  "Find"
#define EZOCARRIERRTD_CMD_DEV_INFO              "i"
#define EZOCARRIERRTD_CMD_I2C                   "I2C"
#define EZOCARRIERRTD_CMD_IMPORT                "Import"
#define EZOCARRIERRTD_CMD_LED                   "L"
#define EZOCARRIERRTD_CMD_MEM_RECALL            "M"
#define EZOCARRIERRTD_CMD_NAME                  "Name"
#define EZOCARRIERRTD_CMD_PROTOCOL_LOCK         "Plock"
#define EZOCARRIERRTD_CMD_SINGLE_READ           "R"
#define EZOCARRIERRTD_CMD_SCALE                 "S"
#define EZOCARRIERRTD_CMD_SLEEP                 "Sleep"
#define EZOCARRIERRTD_CMD_STATUS                "Status"
#define EZOCARRIERRTD_CMD_RESP_CODES            "*OK"
#define EZOCARRIERRTD_CMD_END_COMMAND           "\r"

/**
 * @brief EZO Carrier RTD response codes.
 * @details Specified setting for response codes of EZO Carrier RTD Click driver.
 */
#define EZOCARRIERRTD_RSP_OK                    "*OK"
#define EZOCARRIERRTD_RSP_ERROR                 "*ER"
#define EZOCARRIERRTD_RSP_OVER_VOLT             "*OV"
#define EZOCARRIERRTD_RSP_UNDER_VOLT            "*UV"
#define EZOCARRIERRTD_RSP_RESET                 "*RS"
#define EZOCARRIERRTD_RSP_READY                 "*RE"
#define EZOCARRIERRTD_RSP_SLEEP                 "*SL"
#define EZOCARRIERRTD_RSP_WAKE_UP               "*WA"

/**
 * @brief EZO Carrier RTD driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define EZOCARRIERRTD_TX_DRV_BUFFER_SIZE        100
#define EZOCARRIERRTD_RX_DRV_BUFFER_SIZE        300

/*! @} */ // ezocarrierrtd_cmd

/**
 * @brief EZO Carrier RTD device address setting.
 * @details Specified setting for device slave address selection of
 * EZO Carrier RTD Click driver.
 */
#define EZOCARRIERRTD_DEVICE_ADDRESS            0x61

/**
 * @defgroup ezocarrierrtd_map EZO Carrier RTD MikroBUS Map
 * @brief MikroBUS pin mapping of EZO Carrier RTD Click driver.
 */

/**
 * @addtogroup ezocarrierrtd_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EZO Carrier RTD Click to the selected MikroBUS.
 */
#define EZOCARRIERRTD_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX )

/*! @} */ // ezocarrierrtd_map
/*! @} */ // ezocarrierrtd

/**
 * @brief EZO Carrier EC Click driver selector.
 * @details Selects target driver interface of EZO Carrier EC Click driver.
 */
typedef enum
{
    EZOCARRIERRTD_DRV_SEL_I2C,       /**< I2C driver descriptor. */
    EZOCARRIERRTD_DRV_SEL_UART       /**< UART driver descriptor. */

} ezocarrierrtd_drv_t;

/**
 * @brief EZO Carrier RTD Click context object.
 * @details Context object definition of EZO Carrier RTD Click driver.
 */
typedef struct
{
    // Modules
    uart_t uart;                                /**< UART driver object. */
    i2c_master_t i2c;                           /**< I2C driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ EZOCARRIERRTD_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ EZOCARRIERRTD_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

    ezocarrierrtd_drv_t drv_sel;                /**< Master driver interface selector. */

} ezocarrierrtd_t;

/**
 * @brief EZO Carrier RTD Click configuration object.
 * @details Configuration object definition of EZO Carrier RTD Click driver.
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
    ezocarrierrtd_drv_t drv_sel;                /**< Master driver interface selector. */

} ezocarrierrtd_cfg_t;

/**
 * @brief EZO Carrier RTD Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EZOCARRIERRTD_OK = 0,
    EZOCARRIERRTD_ERROR = -1,
    EZOCARRIERRTD_ERROR_TIMEOUT = -2

} ezocarrierrtd_return_value_t;

/*!
 * @addtogroup ezocarrierrtd EZO Carrier RTD Click Driver
 * @brief API for configuring and manipulating EZO Carrier RTD Click driver.
 * @{
 */

/**
 * @brief EZO Carrier RTD configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ezocarrierrtd_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ezocarrierrtd_cfg_setup ( ezocarrierrtd_cfg_t *cfg );

/**
 * @brief EZO Carrier EC driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #ezocarrierrtd_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #ezocarrierrtd_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void ezocarrierrtd_drv_interface_sel ( ezocarrierrtd_cfg_t *cfg, ezocarrierrtd_drv_t drv_sel );

/**
 * @brief EZO Carrier RTD initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ezocarrierrtd_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ezocarrierrtd_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierrtd_init ( ezocarrierrtd_t *ctx, ezocarrierrtd_cfg_t *cfg );

/**
 * @brief EZO Carrier RTD data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ezocarrierrtd_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierrtd_generic_write ( ezocarrierrtd_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief EZO Carrier RTD data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ezocarrierrtd_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierrtd_generic_read ( ezocarrierrtd_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #ezocarrierrtd_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierrtd_send_cmd ( ezocarrierrtd_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #ezocarrierrtd_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierrtd_send_cmd_with_par ( ezocarrierrtd_t *ctx, uint8_t *cmd, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ezocarrierrtd_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierrtd_send_cmd_check ( ezocarrierrtd_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // EZOCARRIERRTD_H

/*! @} */ // ezocarrierrtd

// ------------------------------------------------------------------------ END
