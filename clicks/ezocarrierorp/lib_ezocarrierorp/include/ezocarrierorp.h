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
 * @file ezocarrierorp.h
 * @brief This file contains API for EZO Carrier ORP Click Driver.
 */

#ifndef EZOCARRIERORP_H
#define EZOCARRIERORP_H

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
#include "drv_i2c_master.h"
#include "drv_uart.h"

/*!
 * @addtogroup ezocarrierorp EZO Carrier ORP Click Driver
 * @brief API for configuring and manipulating EZO Carrier ORP Click driver.
 * @{
 */

/**
 * @defgroup ezocarrierorp_cmd EZO Carrier ORP Device Settings
 * @brief Settings for registers of EZO Carrier ORP Click driver.
 */

/**
 * @addtogroup ezocarrierorp_cmd
 * @{
 */

/**
 * @brief EZO Carrier ORP control commands.
 * @details Specified setting for control commands of EZO Carrier ORP Click driver.
 */
#define EZOCARRIERORP_CMD_BAUD                  "Baud"
#define EZOCARRIERORP_CMD_CONT_READ             "C"
#define EZOCARRIERORP_CMD_CAL                   "Cal"
#define EZOCARRIERORP_CMD_EXPORT                "Export"
#define EZOCARRIERORP_CMD_FACTORY               "Factory"
#define EZOCARRIERORP_CMD_FIND                  "Find"
#define EZOCARRIERORP_CMD_DEV_INFO              "i"
#define EZOCARRIERORP_CMD_I2C                   "I2C"
#define EZOCARRIERORP_CMD_IMPORT                "Import"
#define EZOCARRIERORP_CMD_LED                   "L"
#define EZOCARRIERORP_CMD_NAME                  "Name"
#define EZOCARRIERORP_CMD_PROTOCOL_LOCK         "Plock"
#define EZOCARRIERORP_CMD_SINGLE_READ           "R"
#define EZOCARRIERORP_CMD_SLEEP                 "Sleep"
#define EZOCARRIERORP_CMD_STATUS                "Status"
#define EZOCARRIERORP_CMD_RESP_CODES            "*OK"
#define EZOCARRIERORP_CMD_END_COMMAND           "\r"

/**
 * @brief EZO Carrier ORP response codes.
 * @details Specified setting for response codes of EZO Carrier ORP Click driver.
 */
#define EZOCARRIERORP_RSP_OK                    "*OK"
#define EZOCARRIERORP_RSP_ERROR                 "*ER"
#define EZOCARRIERORP_RSP_OVER_VOLT             "*OV"
#define EZOCARRIERORP_RSP_UNDER_VOLT            "*UV"
#define EZOCARRIERORP_RSP_RESET                 "*RS"
#define EZOCARRIERORP_RSP_READY                 "*RE"
#define EZOCARRIERORP_RSP_SLEEP                 "*SL"
#define EZOCARRIERORP_RSP_WAKE_UP               "*WA"

/**
 * @brief EZO Carrier ORP driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define EZOCARRIERORP_TX_DRV_BUFFER_SIZE    100
#define EZOCARRIERORP_RX_DRV_BUFFER_SIZE    300

/*! @} */ // ezocarrierorp_cmd

/**
 * @brief EZO Carrier ORP device address setting.
 * @details Specified setting for device slave address selection of
 * EZO Carrier ORP Click driver.
 */
#define EZOCARRIERORP_DEVICE_ADDRESS            0x61

/**
 * @defgroup ezocarrierorp_map EZO Carrier ORP MikroBUS Map
 * @brief MikroBUS pin mapping of EZO Carrier ORP Click driver.
 */

/**
 * @addtogroup ezocarrierorp_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EZO Carrier ORP Click to the selected MikroBUS.
 */
#define EZOCARRIERORP_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX )

/*! @} */ // ezocarrierorp_map
/*! @} */ // ezocarrierorp

/**
 * @brief EZO Carrier EC Click driver selector.
 * @details Selects target driver interface of EZO Carrier EC Click driver.
 */
typedef enum
{
    EZOCARRIERORP_DRV_SEL_I2C,       /**< I2C driver descriptor. */
    EZOCARRIERORP_DRV_SEL_UART       /**< UART driver descriptor. */

} ezocarrierorp_drv_t;

/**
 * @brief EZO Carrier ORP Click context object.
 * @details Context object definition of EZO Carrier ORP Click driver.
 */
typedef struct
{
    // Modules
    uart_t uart;                                /**< UART driver object. */
    i2c_master_t i2c;                           /**< I2C driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ EZOCARRIERORP_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ EZOCARRIERORP_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

    ezocarrierorp_drv_t drv_sel;                /**< Master driver interface selector. */

} ezocarrierorp_t;

/**
 * @brief EZO Carrier ORP Click configuration object.
 * @details Configuration object definition of EZO Carrier ORP Click driver.
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
    ezocarrierorp_drv_t drv_sel;                /**< Master driver interface selector. */

} ezocarrierorp_cfg_t;

/**
 * @brief EZO Carrier ORP Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EZOCARRIERORP_OK = 0,
    EZOCARRIERORP_ERROR = -1,
    EZOCARRIERORP_ERROR_TIMEOUT = -2

} ezocarrierorp_return_value_t;

/*!
 * @addtogroup ezocarrierorp EZO Carrier ORP Click Driver
 * @brief API for configuring and manipulating EZO Carrier ORP Click driver.
 * @{
 */

/**
 * @brief EZO Carrier ORP configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ezocarrierorp_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ezocarrierorp_cfg_setup ( ezocarrierorp_cfg_t *cfg );

/**
 * @brief EZO Carrier EC driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #ezocarrierorp_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #ezocarrierorp_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void ezocarrierorp_drv_interface_sel ( ezocarrierorp_cfg_t *cfg, ezocarrierorp_drv_t drv_sel );

/**
 * @brief EZO Carrier ORP initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ezocarrierorp_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ezocarrierorp_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierorp_init ( ezocarrierorp_t *ctx, ezocarrierorp_cfg_t *cfg );

/**
 * @brief EZO Carrier ORP data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ezocarrierorp_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierorp_generic_write ( ezocarrierorp_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief EZO Carrier ORP data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ezocarrierorp_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierorp_generic_read ( ezocarrierorp_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief Send command function.
 * @details This function sends a specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #ezocarrierorp_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierorp_send_cmd ( ezocarrierorp_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the click module.
 * @param[in] ctx : Click context object.
 * See #ezocarrierorp_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierorp_send_cmd_with_par ( ezocarrierorp_t *ctx, uint8_t *cmd, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ezocarrierorp_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierorp_send_cmd_check ( ezocarrierorp_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // EZOCARRIERORP_H

/*! @} */ // ezocarrierorp

// ------------------------------------------------------------------------ END
