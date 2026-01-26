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
 * @file norab266.h
 * @brief This file contains API for NORA-B266 Click Driver.
 */

#ifndef NORAB266_H
#define NORAB266_H

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
#include "drv_uart.h"

/*!
 * @addtogroup norab266 NORA-B266 Click Driver
 * @brief API for configuring and manipulating NORA-B266 Click driver.
 * @{
 */

/**
 * @defgroup norab266_cmd NORA-B266 Device Settings
 * @brief Settings of NORA-B266 Click driver.
 */

/**
 * @addtogroup norab266_cmd
 * @{
 */

/**
 * @brief NORA-B266 control commands.
 * @details Specified setting for control commands of NORA-B266 Click driver.
 */
#define NORAB266_CMD_AT                         "AT"
#define NORAB266_CMD_GET_SW_VERSION             "AT+CGMR"
#define NORAB266_CMD_FACTORY_RESET              "AT+USYFR"
#define NORAB266_CMD_SAVE_CONFIG                "AT&W"
#define NORAB266_CMD_REBOOT_DEVICE              "AT+CPWROFF"
#define NORAB266_CMD_BT_LOCAL_NAME              "AT+UBTLN"
#define NORAB266_CMD_SET_SPS_SERVICE_STATE      "AT+USPS"
#define NORAB266_CMD_SET_SPS_RECEIVE_MODE       "AT+USPSRM"
#define NORAB266_CMD_START_LEGACY_ADV           "AT+UBTAL"
#define NORAB266_CMD_SPS_WRITE_STRING           "AT+USPSWS"
#define NORAB266_CMD_CLOSE_CONNECTION           "AT+UBTDC"

/**
 * @brief NORA-B266 device response to AT commands.
 * @details Device response to commands.
 */
#define NORAB266_RSP_OK                         "OK"
#define NORAB266_RSP_ERROR                      "ERROR"

/**
 * @brief NORA-B266 device unsolicited response code (URC) settings.
 * @details Device unsolicited response code (URC) settings.
 */
#define NORAB266_URC_GREETING                   "+STARTUP"
#define NORAB266_URC_SPS_CONNECTED              "+UESPSC:"
#define NORAB266_URC_SPS_DISCONNECTED           "+UESPSDC:"
#define NORAB266_URC_READ_SPS_DATA              "+UESPSDS:"

/**
 * @brief NORA-B266 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NORAB266_TX_DRV_BUFFER_SIZE             200
#define NORAB266_RX_DRV_BUFFER_SIZE             600

/*! @} */ // norab266_cmd

/**
 * @defgroup norab266_map NORA-B266 MikroBUS Map
 * @brief MikroBUS pin mapping of NORA-B266 Click driver.
 */

/**
 * @addtogroup norab266_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NORA-B266 Click to the selected MikroBUS.
 */
#define NORAB266_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wds = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // norab266_map
/*! @} */ // norab266

/**
 * @brief NORA-B266 Click context object.
 * @details Context object definition of NORA-B266 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< System reset pin (active low). */
    digital_out_t cts;              /**< UART clear to send control signal. */
    digital_out_t wds;              /**< Wake-up from deep sleep pin (active low). */

    // Input pins
    digital_in_t rts;               /**< UART request to send control signal. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ NORAB266_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ NORAB266_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ NORAB266_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} norab266_t;

/**
 * @brief NORA-B266 Click configuration object.
 * @details Configuration object definition of NORA-B266 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< System reset pin (active low). */
    pin_name_t cts;                 /**< UART clear to send control signal. */
    pin_name_t wds;                 /**< Wake-up from deep sleep pin (active low). */
    pin_name_t rts;                 /**< UART request to send control signal. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} norab266_cfg_t;

/**
 * @brief NORA-B266 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NORAB266_OK = 0,
    NORAB266_ERROR = -1,
    NORAB266_ERROR_TIMEOUT = -2,
    NORAB266_ERROR_CMD = -3

} norab266_return_value_t;

/*!
 * @addtogroup norab266 NORA-B266 Click Driver
 * @brief API for configuring and manipulating NORA-B266 Click driver.
 * @{
 */

/**
 * @brief NORA-B266 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #norab266_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void norab266_cfg_setup ( norab266_cfg_t *cfg );

/**
 * @brief NORA-B266 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #norab266_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t norab266_init ( norab266_t *ctx, norab266_cfg_t *cfg );

/**
 * @brief NORA-B266 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t norab266_generic_write ( norab266_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NORA-B266 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t norab266_generic_read ( norab266_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NORA-B266 set RST pin function.
 * @details This function sets the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void norab266_set_rst_pin ( norab266_t *ctx, uint8_t state );

/**
 * @brief NORA-B266 reset device function.
 * @details This function resets the device by toggling the reset pin logic state.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void norab266_reset_device ( norab266_t *ctx );

/**
 * @brief NORA-B266 set CTS pin function.
 * @details This function sets the clear to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void norab266_set_cts_pin ( norab266_t *ctx, uint8_t state );

/**
 * @brief NORA-B266 get RTS pin function.
 * @details This function returns the ready to send pin logic state.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t norab266_get_rts_pin ( norab266_t *ctx );

/**
 * @brief NORA-B266 set WDS pin function.
 * @details This function sets the wake-up from deep sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void norab266_set_wds_pin ( norab266_t *ctx, uint8_t state );

/**
 * @brief NORA-B266 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see NORAB266_CMD_x definitions.
 * @return None.
 * @note None.
 */
void norab266_cmd_run ( norab266_t *ctx, uint8_t *cmd );

/**
 * @brief NORA-B266 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see NORAB266_CMD_x definitions.
 * @param[in] value : Value string.
 * @return None.
 * @note None.
 */
void norab266_cmd_set ( norab266_t *ctx, uint8_t *cmd, uint8_t *value );

/**
 * @brief NORA-B266 cmd get function.
 * @details This function is used to get the value of a given command from the Click module.
 * @param[in] ctx : Click context object.
 * See #norab266_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see NORAB266_CMD_x definitions.
 * @return None.
 * @note None.
 */
void norab266_cmd_get ( norab266_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // NORAB266_H

/*! @} */ // norab266

// ------------------------------------------------------------------------ END
