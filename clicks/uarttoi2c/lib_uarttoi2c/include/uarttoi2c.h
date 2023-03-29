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
 * @file uarttoi2c.h
 * @brief This file contains API for UART to I2C Click Driver.
 */

#ifndef UARTTOI2C_H
#define UARTTOI2C_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup uarttoi2c UART to I2C Click Driver
 * @brief API for configuring and manipulating UART to I2C Click driver.
 * @{
 */

/**
 * @defgroup uarttoi2c_cmd UART to I2C Device Settings
 * @brief Settings for registers of UART to I2C Click driver.
 */

/**
 * @addtogroup uarttoi2c_cmd
 * @{
 */

/**
 * @brief UART to I2C control commands.
 * @details Specified setting for control commands of UART to I2C Click driver.
 */
#define UARTTOI2C_CMD_START             'S'
#define UARTTOI2C_CMD_STOP              'P'
#define UARTTOI2C_CMD_READ_REG          'R'
#define UARTTOI2C_CMD_WRITE_REG         'W'
#define UARTTOI2C_CMD_READ_GPIO         'I'
#define UARTTOI2C_CMD_WRITE_GPIO        'O'
#define UARTTOI2C_CMD_READ_VERSION      'V'
#define UARTTOI2C_CMD_POWER_DOWN        'Z'

/**
 * @brief UART to I2C registers list.
 * @details Specified registers list of UART to I2C Click driver.
 */
#define UARTTOI2C_REG_BRG0              0x00
#define UARTTOI2C_REG_BRG1              0x01
#define UARTTOI2C_REG_PORT_CONF_1       0x02
#define UARTTOI2C_REG_PORT_CONF_2       0x03
#define UARTTOI2C_REG_IO_STATE          0x04
#define UARTTOI2C_REG_RESERVED          0x05
#define UARTTOI2C_REG_I2C_ADR           0x06
#define UARTTOI2C_REG_I2C_CLK_L         0x07
#define UARTTOI2C_REG_I2C_CLK_H         0x08
#define UARTTOI2C_REG_I2C_TO            0x09
#define UARTTOI2C_REG_I2C_STAT          0x0A

/**
 * @brief UART to I2C read timeout settings.
 * @details Specified read timeout settings of UART to I2C Click driver.
 */
#define UARTTOI2C_TIMEOUT_MS            3000

/**
 * @brief UART to I2C power up bytes (ASCII "OK").
 * @details Specified power up bytes of UART to I2C Click driver.
 */
#define UARTTOI2C_POWER_UP_BYTE_0       0x4F
#define UARTTOI2C_POWER_UP_BYTE_1       0x4B

/**
 * @brief UART to I2C pin mask values.
 * @details Specified pin mask values of UART to I2C Click driver.
 */
#define UARTTOI2C_NO_PIN_MASK           0x00
#define UARTTOI2C_PIN_0_MASK            0x01
#define UARTTOI2C_PIN_1_MASK            0x02
#define UARTTOI2C_PIN_2_MASK            0x04
#define UARTTOI2C_PIN_3_MASK            0x08
#define UARTTOI2C_PIN_4_MASK            0x10
#define UARTTOI2C_PIN_5_MASK            0x20
#define UARTTOI2C_PIN_6_MASK            0x40
#define UARTTOI2C_PIN_7_MASK            0x80
#define UARTTOI2C_ALL_PINS_MASK         0xFF

/**
 * @brief UART to I2C pin direction settings.
 * @details Specified pin direction settings of UART to I2C Click driver.
 */
#define UARTTOI2C_PIN_DIR_INPUT         0x00
#define UARTTOI2C_PIN_DIR_OUTPUT_PP     0x02
#define UARTTOI2C_PIN_DIR_OUTPUT_OD     0x03
#define UARTTOI2C_PIN_DIR_OUTPUT_MASK   0x03

/**
 * @brief UART to I2C driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define UARTTOI2C_TX_DRV_BUFFER_SIZE    100
#define UARTTOI2C_RX_DRV_BUFFER_SIZE    300

/*! @} */ // uarttoi2c_cmd

/**
 * @defgroup uarttoi2c_map UART to I2C MikroBUS Map
 * @brief MikroBUS pin mapping of UART to I2C Click driver.
 */

/**
 * @addtogroup uarttoi2c_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UART to I2C Click to the selected MikroBUS.
 */
#define UARTTOI2C_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );

/*! @} */ // uarttoi2c_map
/*! @} */ // uarttoi2c

/**
 * @brief UART to I2C Click context object.
 * @details Context object definition of UART to I2C Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                  /**< Reset pin (Active low). */

    // Modules
    uart_t uart;                        /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ UARTTOI2C_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    char uart_tx_buffer[ UARTTOI2C_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */

} uarttoi2c_t;

/**
 * @brief UART to I2C Click configuration object.
 * @details Configuration object definition of UART to I2C Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Reset pin (Active low). */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} uarttoi2c_cfg_t;

/**
 * @brief UART to I2C Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    UARTTOI2C_OK = 0,
    UARTTOI2C_ERROR = -1,
    UARTTOI2C_TIMEOUT_ERROR = -2

} uarttoi2c_return_value_t;

/*!
 * @addtogroup uarttoi2c UART to I2C Click Driver
 * @brief API for configuring and manipulating UART to I2C Click driver.
 * @{
 */

/**
 * @brief UART to I2C configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #uarttoi2c_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void uarttoi2c_cfg_setup ( uarttoi2c_cfg_t *cfg );

/**
 * @brief UART to I2C initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #uarttoi2c_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_init ( uarttoi2c_t *ctx, uarttoi2c_cfg_t *cfg );

/**
 * @brief UART to I2C default configuration function.
 * @details This function executes a default configuration of UART to I2C
 * click board.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t uarttoi2c_default_cfg ( uarttoi2c_t *ctx );

/**
 * @brief UART to I2C data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_generic_write ( uarttoi2c_t *ctx, char *data_in, uint16_t len );

/**
 * @brief UART to I2C data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_generic_read ( uarttoi2c_t *ctx, char *data_out, uint16_t len );

/**
 * @brief UART to I2C set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void uarttoi2c_set_rst_pin ( uarttoi2c_t *ctx, uint8_t state );

/**
 * @brief UART to I2C reset device function.
 * @details This function resets the device and checks the power up response.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_reset_device ( uarttoi2c_t *ctx );

/**
 * @brief UART to I2C write register function.
 * @details This function writes a desired data to the specified chip internal register.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[in] reg : Chip internal register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - unknown register.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_write_register ( uarttoi2c_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief UART to I2C read register function.
 * @details This function reads data from the specified chip internal register.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[in] reg : Chip internal register address.
 * @param[out] data_out : Output data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - unknown register or null pointer,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_read_register ( uarttoi2c_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief UART to I2C gpio write function.
 * @details This function writes a desired data to the gpio port.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[in] gpio_data : GPIO data to be written.
 * @return None.
 * @note The pins should be configured as output in order for this to take effect.
 */
void uarttoi2c_gpio_write ( uarttoi2c_t *ctx, uint8_t gpio_data );

/**
 * @brief UART to I2C gpio read function.
 * @details This function reads data from the gpio port.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[out] gpio_data : GPIO data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - null pointer,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_gpio_read ( uarttoi2c_t *ctx, uint8_t *gpio_data );

/**
 * @brief UART to I2C gpio config function.
 * @details This function sets the gpio direction config for the selected pins.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[in] direction : GPIO direction: @li @c 0 - Input,
 *                                        @li @c 2 - Output push-pull,
 *                                        @li @c 3 - Output open-drain.
 * @param[in] pin_mask : Mask for pins to configure.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - wrong direction parameter,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_gpio_config ( uarttoi2c_t *ctx, uint8_t direction, uint8_t pin_mask );

/**
 * @brief UART to I2C read version function.
 * @details This function reads the firmware version (16-bytes string ending with a null terminator).
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[out] version : Firmware version (16-bytes string ending with a null terminator).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - not enough bytes read,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_read_version ( uarttoi2c_t *ctx, uint8_t *version );

/**
 * @brief UART to I2C i2c write function.
 * @details This function writes a desired number of data bytes to the I2C target device.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[in] slave_addr : Target device slave address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - null pointer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_i2c_write ( uarttoi2c_t *ctx, uint8_t slave_addr, uint8_t *data_in, uint8_t len );

/**
 * @brief UART to I2C i2c read function.
 * @details This function reads a desired number of data bytes from the I2C target device.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[in] slave_addr : Target device slave address.
 * @param[out] data_out : Output data read.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - parameter error or not enough bytes read,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_i2c_read ( uarttoi2c_t *ctx, uint8_t slave_addr, uint8_t *data_out, uint8_t len );

/**
 * @brief UART to I2C i2c write then read function.
 * @details This function performs a write then read with a repeated start to the I2C target device.
 * @param[in] ctx : Click context object.
 * See #uarttoi2c_t object definition for detailed explanation.
 * @param[in] slave_addr : Target device slave address.
 * @param[in] data_in : Data to be written.
 * @param[in] in_len : Number of bytes to be written.
 * @param[out] data_out : Output data read.
 * @param[in] out_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error - null pointer or not enough bytes read,
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t uarttoi2c_i2c_write_then_read ( uarttoi2c_t *ctx, uint8_t slave_addr, 
                                      uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len );

#ifdef __cplusplus
}
#endif
#endif // UARTTOI2C_H

/*! @} */ // uarttoi2c

// ------------------------------------------------------------------------ END
