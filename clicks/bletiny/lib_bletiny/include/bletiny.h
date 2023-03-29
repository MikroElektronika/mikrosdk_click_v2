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
 * @file bletiny.h
 * @brief This file contains API for BLE TINY Click Driver.
 */

#ifndef BLETINY_H
#define BLETINY_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup bletiny BLE TINY Click Driver
 * @brief API for configuring and manipulating BLE TINY Click driver.
 * @{
 */

/**
 * @defgroup bletiny_reg BLE TINY Commands List
 * @brief List of commands of BLE TINY Click driver.
 */

/**
 * @addtogroup bletiny_reg
 * @{
 */

/**
 * @brief BLE TINY control commands.
 * @details Specified commands for control of BLE TINY Click driver.
 */
#define BLETINY_CMD_ATR             "ATr"
#define BLETINY_CMD_ATZ             "ATZ"
#define BLETINY_CMD_GAPDISCONNECT   "AT+GAPDISCONNECT"
#define BLETINY_CMD_ATI             "ATI"
#define BLETINY_CMD_ATRI            "ATrI"
#define BLETINY_CMD_BDADDR          "AT+BDADDR"
#define BLETINY_CMD_RSSI            "AT+RSSI"
#define BLETINY_CMD_CHECK_MEM       "AT+MEM=0"
#define BLETINY_CMD_CLEAR_MEM       "AT+MEM=0,"

/*! @} */ // bletiny_reg

/**
 * @defgroup bletiny_set BLE TINY Device Settings
 * @brief Settings for registers of BLE TINY Click driver.
 */

/**
 * @addtogroup bletiny_set
 * @{
 */

/**
 * @brief BLE Tiny device response for AT commands.
 * @details Device response after commands.
 */
#define BLETINY_RSP_OK              "OK"
#define BLETINY_RSP_ERROR           "ERROR"
#define BLETINY_CONNECTED           "+CONNECTED"
#define BLETINY_DISCONNECTED        "+DISCONNECTED"

/**
 * @brief BLE Tiny device SPI configuration.
 * @details SPI configuration parameters.
 */
#define BLETINY_SPI_CFG_SPEED_2MHZ  0
#define BLETINY_SPI_CFG_SPEED_4MHZ  1
#define BLETINY_SPI_CFG_SPEED_8MHZ  2
#define BLETINY_SPI_CFG_MODE0       0
#define BLETINY_SPI_CFG_MODE1       1
#define BLETINY_SPI_CFG_MODE2       2
#define BLETINY_SPI_CFG_MODE3       3

/**
 * @brief BLE Tiny device I2C configuration.
 * @details I2C configuration parameters.
 */
#define BLETINY_I2C_CFG_SPEED_100KHZ    100
#define BLETINY_I2C_CFG_SPEED_400KHZ    400
#define BLETINY_I2C_CFG_REG_LEN_1BYTE   8
#define BLETINY_I2C_CFG_REG_LEN_1BYTES  16

/**
 * @brief BLE TINY driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE             500

/*! @} */ // bletiny_set

/**
 * @defgroup bletiny_map BLE TINY MikroBUS Map
 * @brief MikroBUS pin mapping of BLE TINY Click driver.
 */

/**
 * @addtogroup bletiny_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BLE TINY Click to the selected MikroBUS.
 */
#define BLETINY_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // bletiny_map
/*! @} */ // bletiny

/**
 * @brief BLE TINY Click context object.
 * @details Context object definition of BLE TINY Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                      /**< Description. */

    // Modules
    uart_t uart;                            /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ]; /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ]; /**< Buffer size. */

} bletiny_t;

/**
 * @brief BLE TINY Click configuration object.
 * @details Configuration object definition of BLE TINY Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;        /**< Description. */

    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */                      /** Reference Voltage */

} bletiny_cfg_t;

/**
 * @brief BLE TINY Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BLETINY_OK = 0,
   BLETINY_ERROR = -1,
   BLETINY_ERROR_TIMEOUT = -2,
   BLETINY_ERROR_RETURN = -3,
   BLETINY_ERROR_UNKNOWN = -4

} bletiny_return_value_t;

/*!
 * @addtogroup bletiny BLE TINY Click Driver
 * @brief API for configuring and manipulating BLE TINY Click driver.
 * @{
 */

/**
 * @brief BLE TINY configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bletiny_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bletiny_cfg_setup ( bletiny_cfg_t *cfg );

/**
 * @brief BLE TINY initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bletiny_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletiny_init ( bletiny_t *ctx, bletiny_cfg_t *cfg );

/**
 * @brief BLE TINY default configuration function.
 * @details This function executes a default configuration of BLE TINY
 * click board.
 * @param[in] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t bletiny_default_cfg ( bletiny_t *ctx );

/**
 * @brief BLE TINY data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletiny_generic_write ( bletiny_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief BLE TINY data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bletiny_generic_read ( bletiny_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Send command function.
 * @details This function sends the specified command to the click module.
 * @param[in] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @param[in] cmd : Command variable.
 *
 * @return Nothing.
 */
void bletiny_send_cmd ( bletiny_t *ctx, char *cmd );

/**
 * @brief Configure Click board for SPI master communication.
 * @details Configure Click board pins for SPI communication and sets SPI communication parameters.
 * @param[in] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @param[in] speed : Clock speed.
 * @param[in] mode : SPI mode.
 *
 * @return Nothing.
 */
void bletiny_spi_config ( bletiny_t *ctx, uint8_t speed, uint8_t mode );

/**
 * @brief Send command to write data to slave device via SPI communication.
 * @details Send command over UART to write @b len bytes from @b data_buf to attached Click board.
 * @param[in] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @param[in] data_buf : Data to write.
 * @param[in] len : Number of bytes to write from @b data_buf.
 *
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t bletiny_spi_write ( bletiny_t *ctx, char *data_buf, uint8_t len );

/**
 * @brief Send command to read data from slave device via SPI communication.
 * @details Send command over UART to read @b len bytes of @b data_buf from attached Click board.
 * @param[in] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @param[out] data_buf : Read data.
 * @param[in] len : Number of bytes to read.
 *
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t bletiny_spi_read ( bletiny_t *ctx, char *data_buf, uint8_t len );

/**
 * @brief Send command to write data to and then read data from slave device via SPI communication.
 * @details Send command over UART to write @b write_len bytes from @b data_write,
 * and then to read @b read_len bytes of @b data_read from attached Click board.
 * @param[in] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @param[out] data_write : Data to write.
 * @param[in] write_len : Number of bytes to write from @b data_write.
 * @param[out] data_read : Read data.
 * @param[in] read_len : Number of bytes to read.
 *
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t bletiny_spi_write_then_read ( bletiny_t *ctx, uint8_t *data_write, uint8_t write_len, char *data_read, uint8_t read_len );

/**
 * @brief Configure Click board for I2C master communication.
 * @details Configure Click board pins for I2C communication and sets I2C communication parameters.
 * @param[in] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @param[in] speed : Clock speed.
 * @param[in] reg_len : I2C slave register length.
 *
 * @return Nothing.
 */
void bletiny_i2c_config ( bletiny_t *ctx, uint8_t speed, uint8_t reg_len );

/**
 * @brief Send command to write data to reg address of slave device via I2C communication.
 * @details Send command over UART to write @b reg_data to @b reg address of attached Click board.
 * @param[in] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @param[in] slave_address : Slave address to send.
 * @param[in] reg : Register address of slave.
 * @param[in] reg_data : Data to write to @b reg.
 *
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t bletiny_i2c_write ( bletiny_t *ctx, uint8_t slave_address, uint16_t reg, uint8_t reg_data );

/**
 * @brief Send command to read data from slave device via I2C communication.
 * @details Send command over UART to read @b len bytes of @b reg address from attached Click board.
 * @param[in] ctx : Click context object.
 * See #bletiny_t object definition for detailed explanation.
 * @param[in] slave_address : Slave address to send.
 * @param[in] reg : Register address of slave.
 * @param[out] data_buf : Read data.
 * @param[in] len : Number of bytes to read.
 *
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t bletiny_i2c_read ( bletiny_t *ctx,  uint8_t slave_address, uint16_t reg, uint8_t *data_buf, uint8_t len );

#ifdef __cplusplus
}
#endif
#endif // BLETINY_H

/*! @} */ // bletiny

// ------------------------------------------------------------------------ END
