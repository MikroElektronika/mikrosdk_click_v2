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
 * @file ezocarrierph.h
 * @brief This file contains API for EZO Carrier pH Click Driver.
 */

#ifndef EZOCARRIERPH_H
#define EZOCARRIERPH_H

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
 * @addtogroup ezocarrierph EZO Carrier pH Click Driver
 * @brief API for configuring and manipulating EZO Carrier pH Click driver.
 * @{
 */

/**
 * @defgroup ezocarrierph_cmd EZO Carrier pH Device Settings
 * @brief Settings for registers of EZO Carrier pH Click driver.
 */

/**
 * @addtogroup ezocarrierph_cmd
 * @{
 */

/**
 * @brief EZO Carrier pH control commands.
 * @details Specified setting for control commands of EZO Carrier pH Click driver.
 */
#define EZOCARRIERPH_CMD_BAUD                   "Baud"
#define EZOCARRIERPH_CMD_CONT_READ              "C"
#define EZOCARRIERPH_CMD_CAL                    "Cal"
#define EZOCARRIERPH_CMD_EXPORT                 "Export"
#define EZOCARRIERPH_CMD_FACTORY                "Factory"
#define EZOCARRIERPH_CMD_FIND                   "Find"
#define EZOCARRIERPH_CMD_DEV_INFO               "i"
#define EZOCARRIERPH_CMD_I2C                    "I2C"
#define EZOCARRIERPH_CMD_IMPORT                 "Import"
#define EZOCARRIERPH_CMD_LED                    "L"
#define EZOCARRIERPH_CMD_NAME                   "Name"
#define EZOCARRIERPH_CMD_EXTENDED_PH            "pHext"
#define EZOCARRIERPH_CMD_PROTOCOL_LOCK          "Plock"
#define EZOCARRIERPH_CMD_SINGLE_READ            "R"
#define EZOCARRIERPH_CMD_SLEEP                  "Sleep"
#define EZOCARRIERPH_CMD_SLOPE                  "Slope"
#define EZOCARRIERPH_CMD_STATUS                 "Status"
#define EZOCARRIERPH_CMD_TEMP_COMPENSATION      "T"
#define EZOCARRIERPH_CMD_RESP_CODES             "*OK"
#define EZOCARRIERPH_CMD_END_COMMAND            "\r"

/**
 * @brief EZO Carrier pH response codes.
 * @details Specified setting for response codes of EZO Carrier pH Click driver.
 */
#define EZOCARRIERPH_RSP_OK                     "*OK"
#define EZOCARRIERPH_RSP_ERROR                  "*ER"
#define EZOCARRIERPH_RSP_OVER_VOLT              "*OV"
#define EZOCARRIERPH_RSP_UNDER_VOLT             "*UV"
#define EZOCARRIERPH_RSP_RESET                  "*RS"
#define EZOCARRIERPH_RSP_READY                  "*RE"
#define EZOCARRIERPH_RSP_SLEEP                  "*SL"
#define EZOCARRIERPH_RSP_WAKE_UP                "*WA"

/**
 * @brief EZO Carrier pH driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define EZOCARRIERPH_TX_DRV_BUFFER_SIZE         100
#define EZOCARRIERPH_RX_DRV_BUFFER_SIZE         300

/*! @} */ // ezocarrierph_cmd

/**
 * @brief EZO Carrier pH device address setting.
 * @details Specified setting for device slave address selection of
 * EZO Carrier pH Click driver.
 */
#define EZOCARRIERPH_DEVICE_ADDRESS             0x61

/**
 * @defgroup ezocarrierph_map EZO Carrier pH MikroBUS Map
 * @brief MikroBUS pin mapping of EZO Carrier pH Click driver.
 */

/**
 * @addtogroup ezocarrierph_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of EZO Carrier pH Click to the selected MikroBUS.
 */
#define EZOCARRIERPH_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); 

/*! @} */ // ezocarrierph_map
/*! @} */ // ezocarrierph

/**
 * @brief EZO Carrier pH Click driver selector.
 * @details Selects target driver interface of EZO Carrier pH Click driver.
 */
typedef enum
{
    EZOCARRIERPH_DRV_SEL_I2C,       /**< I2C driver descriptor. */
    EZOCARRIERPH_DRV_SEL_UART       /**< UART driver descriptor. */

} ezocarrierph_drv_t;

/**
 * @brief EZO Carrier pH Click context object.
 * @details Context object definition of EZO Carrier pH Click driver.
 */
typedef struct
{
    // Modules
    uart_t uart;                                /**< UART driver object. */
    i2c_master_t i2c;                           /**< I2C driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ EZOCARRIERPH_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ EZOCARRIERPH_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

    uint8_t slave_address;                      /**< Device slave address (used for I2C driver). */

    ezocarrierph_drv_t drv_sel;                 /**< Master driver interface selector. */

} ezocarrierph_t;

/**
 * @brief EZO Carrier pH Click configuration object.
 * @details Configuration object definition of EZO Carrier pH Click driver.
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
    ezocarrierph_drv_t drv_sel;                 /**< Master driver interface selector. */

} ezocarrierph_cfg_t;

/**
 * @brief EZO Carrier pH Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    EZOCARRIERPH_OK = 0,
    EZOCARRIERPH_ERROR = -1,
    EZOCARRIERPH_ERROR_TIMEOUT = -2

} ezocarrierph_return_value_t;

/*!
 * @addtogroup ezocarrierph EZO Carrier pH Click Driver
 * @brief API for configuring and manipulating EZO Carrier pH Click driver.
 * @{
 */

/**
 * @brief EZO Carrier pH configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ezocarrierph_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ezocarrierph_cfg_setup ( ezocarrierph_cfg_t *cfg );

/**
 * @brief EZO Carrier pH driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #ezocarrierph_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #ezocarrierph_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void ezocarrierph_drv_interface_sel ( ezocarrierph_cfg_t *cfg, ezocarrierph_drv_t drv_sel );

/**
 * @brief EZO Carrier pH initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #ezocarrierph_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ezocarrierph_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierph_init ( ezocarrierph_t *ctx, ezocarrierph_cfg_t *cfg );

/**
 * @brief EZO Carrier pH data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ezocarrierph_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierph_generic_write ( ezocarrierph_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief EZO Carrier pH data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ezocarrierph_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ezocarrierph_generic_read ( ezocarrierph_t *ctx, uint8_t *data_out, uint16_t len );


/**
 * @brief Send command function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #ezocarrierph_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierph_send_cmd ( ezocarrierph_t *ctx, uint8_t *cmd );

/**
 * @brief Send command function with parameter.
 * @details This function sends a command with specified parameter to the Click module.
 * @param[in] ctx : Click context object.
 * See #ezocarrierph_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @param[in] param_buf : Parameter buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierph_send_cmd_with_par ( ezocarrierph_t *ctx, uint8_t *cmd, uint8_t *param_buf );

/**
 * @brief Check the sent command.
 * @details This function checks the command that is sent.
 * @param[in] ctx : Click context object.
 * See #ezocarrierph_t object definition for detailed explanation.
 * @param[in] cmd : Command buffer.
 * @return Nothing.
 * @note None.
 */
void ezocarrierph_send_cmd_check ( ezocarrierph_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // EZOCARRIERPH_H

/*! @} */ // ezocarrierph

// ------------------------------------------------------------------------ END
