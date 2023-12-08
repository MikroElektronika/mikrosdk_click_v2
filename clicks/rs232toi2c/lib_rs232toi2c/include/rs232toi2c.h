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
 * @file rs232toi2c.h
 * @brief This file contains API for RS232 to I2C Click Driver.
 */

#ifndef RS232TOI2C_H
#define RS232TOI2C_H

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

/*!
 * @addtogroup rs232toi2c RS232 to I2C Click Driver
 * @brief API for configuring and manipulating RS232 to I2C Click driver.
 * @{
 */

/**
 * @defgroup rs232toi2c_reg RS232 to I2C Registers List
 * @brief List of registers of RS232 to I2C Click driver.
 */

/**
 * @addtogroup rs232toi2c_reg
 * @{
 */

/**
 * @brief RS232 to I2C Command List.
 * @details Specified Command List of RS232 to I2C Click driver.
 */
#define RS232TOI2C_CMD_WRITE_EEPROM             0x00
#define RS232TOI2C_CMD_READ_EEPROM              0x01
#define RS232TOI2C_CMD_WRITE_CURRENT_EEPROM     0x02
#define RS232TOI2C_CMD_READ_CURRENT_EEPROM      0x03
#define RS232TOI2C_CMD_ERASE_EEPROM_PAGE        0x04
#define RS232TOI2C_CMD_SET_GPIO_OUT             0x06
#define RS232TOI2C_CMD_GET_GPIO_IN              0x07
#define RS232TOI2C_CMD_WRITE_GPIO_CFG           0x08
#define RS232TOI2C_CMD_READ_GPIO_CFG            0x09
#define RS232TOI2C_CMD_READ_GPIO_INT_STATUS     0x0F
#define RS232TOI2C_CMD_READ_UART_STATUS         0x21
#define RS232TOI2C_CMD_ENABLE_INT               0x22
#define RS232TOI2C_CMD_INT_STATUS               0x23
#define RS232TOI2C_CMD_WRITE_TX_FIFO            0x24
#define RS232TOI2C_CMD_READ_RX_FIFO             0x25
#define RS232TOI2C_CMD_WRITE_BAUD_RATE          0x26
#define RS232TOI2C_CMD_READ_BAUD_RATE           0x27
#define RS232TOI2C_CMD_WRITE_UART_CFG           0x28
#define RS232TOI2C_CMD_READ_UART_CFG            0x29
#define RS232TOI2C_CMD_WRITE_TRANSMIT_WATERMARK 0x2A
#define RS232TOI2C_CMD_READ_TRANSMIT_WATERMARK  0x2B
#define RS232TOI2C_CMD_WRITE_RECEIVE_WATERMARK  0x2C
#define RS232TOI2C_CMD_READ_RECIEVE_WATERMARK   0x2D
#define RS232TOI2C_CMD_ENABLE_UART              0x2E
#define RS232TOI2C_CMD_READ_RX_TX_FIFO_LEVEL    0x31
#define RS232TOI2C_CMD_READ_SYSTEM_STATUS       0xE1
#define RS232TOI2C_CMD_READ_LAST_OP_RESULT      0xE3
#define RS232TOI2C_CMD_READ_SYSTEM_VERSION      0xE5
#define RS232TOI2C_CMD_READ_INT_SOURCE          0xEF

/*! @} */ // rs232toi2c_reg

/**
 * @defgroup rs232toi2c_set RS232 to I2C Registers Settings
 * @brief Settings for registers of RS232 to I2C Click driver.
 */

/**
 * @addtogroup rs232toi2c_set
 * @{
 */

/**
 * @brief RS232 to I2C GPIO config.
 * @details Specified GPIO config of RS232 to I2C Click driver.
 */
#define RS232TOI2C_GPIO_SUB_CMD_DIR             0x01
#define RS232TOI2C_GPIO_SUB_CMD_PULL_UP         0x02
#define RS232TOI2C_GPIO_SUB_CMD_OPEN_DRAIN      0x03
#define RS232TOI2C_GPIO_SUB_CMD_DEBOUNCE        0x04
#define RS232TOI2C_GPIO_SUB_CMD_INTERRUPT       0x05
#define RS232TOI2C_GPIO_SUB_CMD_RESET_DEFAULT   0x0A

/**
 * @brief RS232 to I2C GPIO bit mask.
 * @details Specified GPIO bit mask of RS232 to I2C Click driver.
 */
#define RS232TOI2C_GPIO_MASK_NONE               0x00
#define RS232TOI2C_GPIO_0_MASK                  0x01
#define RS232TOI2C_GPIO_1_MASK                  0x02
#define RS232TOI2C_GPIO_2_MASK                  0x04
#define RS232TOI2C_GPIO_MASK_ALL                0x07

/**
 * @brief RS232 to I2C UART config sub cmd.
 * @details Specified UART config sub cmd of RS232 to I2C Click driver.
 */
#define RS232TOI2C_UART_SUB_CMD_DATABITS        0x01
#define RS232TOI2C_UART_SUB_CMD_PARITY          0x02
#define RS232TOI2C_UART_SUB_CMD_STOP_BITS       0x03
#define RS232TOI2C_UART_SUB_CMD_FLOW_CONTROL    0x04
#define RS232TOI2C_UART_SUB_CMD_RESET_FIFO      0x06
#define RS232TOI2C_UART_SUB_CMD_LOOPBACK        0x08
#define RS232TOI2C_UART_SUB_CMD_RESET_DEFAULT   0x0A

/**
 * @brief RS232 to I2C UART config databits.
 * @details Specified UART config databits of RS232 to I2C Click driver.
 */
#define RS232TOI2C_UART_DATABITS_5              0x00
#define RS232TOI2C_UART_DATABITS_6              0x01
#define RS232TOI2C_UART_DATABITS_7              0x02
#define RS232TOI2C_UART_DATABITS_8              0x03
#define RS232TOI2C_UART_DATABITS_9              0x07

/**
 * @brief RS232 to I2C UART config parity.
 * @details Specified UART config parity of RS232 to I2C Click driver.
 */
#define RS232TOI2C_UART_PARITY_NONE             0x00
#define RS232TOI2C_UART_PARITY_ODD              0x03
#define RS232TOI2C_UART_PARITY_EVEN             0x02

/**
 * @brief RS232 to I2C UART config stop bit.
 * @details Specified UART config stop bit of RS232 to I2C Click driver.
 */
#define RS232TOI2C_UART_STOP_BIT_1              0x00
#define RS232TOI2C_UART_STOP_BIT_2              0x01

/**
 * @brief RS232 to I2C UART config flow control.
 * @details Specified UART config flow control of RS232 to I2C Click driver.
 */
#define RS232TOI2C_UART_FLOW_CONTROL_NONE       0x00
#define RS232TOI2C_UART_FLOW_CONTROL_HARDWARE   0x01
#define RS232TOI2C_UART_FLOW_CONTROL_SOFTWARE   0x02

/**
 * @brief RS232 to I2C UART config reset fifo.
 * @details Specified UART config reset fifo of RS232 to I2C Click driver.
 */
#define RS232TOI2C_UART_RESET_TX_FIFO           0x01
#define RS232TOI2C_UART_RESET_RX_FIFO           0x02

/**
 * @brief RS232 to I2C UART config loopback.
 * @details Specified UART config loopback of RS232 to I2C Click driver.
 */
#define RS232TOI2C_UART_LOOPBACK_OFF            0x00
#define RS232TOI2C_UART_LOOPBACK_ON             0x01

/**
 * @brief RS232 to I2C UART enable bits.
 * @details Specified UART enable bits of RS232 to I2C Click driver.
 */
#define RS232TOI2C_UART_DISABLE_RX_TX           0x00
#define RS232TOI2C_UART_ENABLE_RX               0x01
#define RS232TOI2C_UART_ENABLE_TX               0x02
#define RS232TOI2C_UART_ENABLE_RX_TX            0x03

/**
 * @brief RS232 to I2C uart status bit mask.
 * @details Specified uart status bit mask of RS232 to I2C Click driver.
 */
#define RS232TOI2C_UART_STATUS_PARITY_ERROR     0x01
#define RS232TOI2C_UART_STATUS_FRAME_ERROR      0x02
#define RS232TOI2C_UART_STATUS_OVERRUN_ERROR    0x04
#define RS232TOI2C_UART_STATUS_BREAK_RECEIVED   0x08
#define RS232TOI2C_UART_STATUS_RX_EMPTY         0x20
#define RS232TOI2C_UART_STATUS_TX_FULL          0x40
#define RS232TOI2C_UART_STATUS_TX_EMPTY         0x80

/**
 * @brief RS232 to I2C enable interrupt bit mask.
 * @details Specified enable interrupt bit mask of RS232 to I2C Click driver.
 */
#define RS232TOI2C_INTERRUPT_TX_RX_ERROR        0x01
#define RS232TOI2C_INTERRUPT_RX_FULL            0x02
#define RS232TOI2C_INTERRUPT_RX_WATERMARK       0x04
#define RS232TOI2C_INTERRUPT_RX_DATA            0x08
#define RS232TOI2C_INTERRUPT_TX_FULL            0x20
#define RS232TOI2C_INTERRUPT_TX_WATERMARK       0x40
#define RS232TOI2C_INTERRUPT_TX_EMPTY           0x80

/**
 * @brief RS232 to I2C EEPROM range values.
 * @details Specified EEPROM range values of RS232 to I2C Click driver.
 */
#define RS232TOI2C_EEPROM_PAGE_SIZE             32
#define RS232TOI2C_EEPROM_PAGE_NUM              16
#define RS232TOI2C_EEPROM_SIZE                  512

/**
 * @brief RS232 to I2C CMD Access bit mask.
 * @details Specified command access bit mask of RS232 to I2C Click driver.
 */
#define RS232TOI2C_CMD_ACCESS_BIT               0x08

/**
 * @brief RS232 to I2C device address setting.
 * @details Specified setting for device slave address selection of
 * RS232 to I2C Click driver.
 */
#define RS232TOI2C_SET_DEV_ADDR_A2_GND          0x53
#define RS232TOI2C_SET_DEV_ADDR_A2_VCC          0x57

/*! @} */ // rs232toi2c_set

/**
 * @defgroup rs232toi2c_map RS232 to I2C MikroBUS Map
 * @brief MikroBUS pin mapping of RS232 to I2C Click driver.
 */

/**
 * @addtogroup rs232toi2c_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RS232 to I2C Click to the selected MikroBUS.
 */
#define RS232TOI2C_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rs232toi2c_map
/*! @} */ // rs232toi2c

/**
 * @brief RS232 to I2C Click context object.
 * @details Context object definition of RS232 to I2C Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  wp;          /**< Write Protect pin for EEPROM (Active High). */
    digital_out_t  rst;         /**< Active Low Reset pin. */

    // Input pins
    digital_in_t  int_pin;      /**< UART or GPIO interrupt pin depending on the INT SEL jumper position. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} rs232toi2c_t;

/**
 * @brief RS232 to I2C Click configuration object.
 * @details Configuration object definition of RS232 to I2C Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  wp;             /**< Write Protect pin for EEPROM. */
    pin_name_t  rst;            /**< Active Low Reset pin. */
    pin_name_t  int_pin;        /**< UART or GPIO interrupt pin depending on the INT SEL jumper position. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} rs232toi2c_cfg_t;

/**
 * @brief RS232 to I2C Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RS232TOI2C_OK = 0,
    RS232TOI2C_ERROR = -1

} rs232toi2c_return_value_t;

/*!
 * @addtogroup rs232toi2c RS232 to I2C Click Driver
 * @brief API for configuring and manipulating RS232 to I2C Click driver.
 * @{
 */

/**
 * @brief RS232 to I2C configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rs232toi2c_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rs232toi2c_cfg_setup ( rs232toi2c_cfg_t *cfg );

/**
 * @brief RS232 to I2C initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rs232toi2c_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_init ( rs232toi2c_t *ctx, rs232toi2c_cfg_t *cfg );

/**
 * @brief RS232 to I2C default configuration function.
 * @details This function executes a default configuration of RS232 to I2C
 * click board.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rs232toi2c_default_cfg ( rs232toi2c_t *ctx );

/**
 * @brief RS232 to I2C write command function.
 * @details This function writes a desired number of data bytes to the selected command
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] cmd : Command address.
 * @param[in] data_in : Data to be written.
 * @param[in] data_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_write_command ( rs232toi2c_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t data_len );

/**
 * @brief RS232 to I2C read command function.
 * @details This function reads a desired number of data bytes from the selected command 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] cmd : Command address.
 * @param[out] data_out : Output read data.
 * @param[in] data_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_read_command ( rs232toi2c_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t data_len );

/**
 * @brief RS232 to I2C write eeprom function.
 * @details This function writes a desired number of data bytes to the selected eeprom address
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] address : EEPROM address [0-511].
 * @param[in] data_in : Data to be written.
 * @param[in] data_len : Number of bytes to be written (up to 32 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_write_eeprom ( rs232toi2c_t *ctx, uint16_t address, uint8_t *data_in, uint8_t data_len );

/**
 * @brief RS232 to I2C read eeprom function.
 * @details This function reads a desired number of data bytes from the selected eeprom address 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] address : EEPROM address [0-511].
 * @param[out] data_out : Output read data.
 * @param[in] data_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_read_eeprom ( rs232toi2c_t *ctx, uint16_t address, uint8_t *data_out, uint8_t data_len );

/**
 * @brief RS232 to I2C erase eeprom page function.
 * @details This function erases the specified eeprom memory page.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] page_num : EEPROM page number [0-15].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_erase_eeprom_page ( rs232toi2c_t *ctx, uint8_t page_num );

/**
 * @brief RS232 to I2C set gpio out function.
 * @details This function sets the specified GPIO out pin logic state.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] mask : GPIO pin mask [3-bit].
 * @param[in] state : GPIO pin state [3-bit, 1-HIGH, 0-LOW].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The pins must be configured as OUTPUT.
 */
err_t rs232toi2c_set_gpio_out ( rs232toi2c_t *ctx, uint8_t mask, uint8_t state );

/**
 * @brief RS232 to I2C get gpio in function.
 * @details This function reads the GPIO in pins logic state.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[out] state : GPIO pin state [3-bit, 1-HIGH, 0-LOW].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The pins must be configured as INPUT.
 */
err_t rs232toi2c_get_gpio_in ( rs232toi2c_t *ctx, uint8_t *state );

/**
 * @brief RS232 to I2C write gpio config function.
 * @details This function writes a desired config to the selected GPIO config sub command.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] sub_cmd : GPIO pin config sub command.
 * @param[in] mask : GPIO pin mask [3-bit].
 * @param[in] config : GPIO pin config [3-bit].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_write_gpio_config ( rs232toi2c_t *ctx, uint8_t sub_cmd, uint8_t mask, uint8_t config );

/**
 * @brief RS232 to I2C read gpio config function.
 * @details This function reads a desired config from the selected GPIO config sub command.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] sub_cmd : GPIO pin config sub command.
 * @param[out] config : GPIO pin config [3-bit].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_read_gpio_config ( rs232toi2c_t *ctx, uint8_t sub_cmd, uint8_t *config );

/**
 * @brief RS232 to I2C write uart config function.
 * @details This function writes a desired config to the selected UART config sub command.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] sub_cmd : UART config sub command.
 * @param[in] config : Sub command config.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_write_uart_config ( rs232toi2c_t *ctx, uint8_t sub_cmd, uint8_t config );

/**
 * @brief RS232 to I2C read uart config function.
 * @details This function reads the UART config.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[out] config : UART config [2 bytes].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_read_uart_config ( rs232toi2c_t *ctx, uint8_t *config );

/**
 * @brief RS232 to I2C enable uart function.
 * @details This function enables the UART RX/TX features.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - disable RX/TX,
 *                    @li @c 1 - enable RX.
 *                    @li @c 2 - enable TX.
 *                    @li @c 3 - enable RX/TX.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_enable_uart ( rs232toi2c_t *ctx, uint8_t state );

/**
 * @brief RS232 to I2C set baud rate function.
 * @details This function sets the UART baud rate.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] baud_rate : Baud rate.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_set_baud_rate ( rs232toi2c_t *ctx, uint32_t baud_rate );

/**
 * @brief RS232 to I2C get baud rate function.
 * @details This function reads the actual UART baud rate.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[out] baud_rate : Baud rate.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_get_baud_rate ( rs232toi2c_t *ctx, uint32_t *baud_rate );

/**
 * @brief RS232 to I2C enable interrupts function.
 * @details This function enables the specified interrupts.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] int_mask : Interrupt enable mask.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_enable_interrupts ( rs232toi2c_t *ctx, uint8_t int_mask );

/**
 * @brief RS232 to I2C get interrupt status function.
 * @details This function reads the interrupt status register and clears it.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[out] int_status : Interrupt status register read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_get_interrupt_status ( rs232toi2c_t *ctx, uint8_t *int_status );

/**
 * @brief RS232 to I2C get uart status function.
 * @details This function reads the uart status register and clears it.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[out] uart_status : UART status register read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_get_uart_status ( rs232toi2c_t *ctx, uint8_t *uart_status );

/**
 * @brief RS232 to I2C get gpio status function.
 * @details This function reads the gpio status register and clears it.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[out] gpio_status : GPIO status register read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_get_gpio_status ( rs232toi2c_t *ctx, uint8_t *gpio_status );

/**
 * @brief RS232 to I2C write tx fifo function.
 * @details This function writes a desired number of data bytes to the TX fifo.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] data_len : Number of data bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_write_tx_fifo ( rs232toi2c_t *ctx, uint8_t *data_in, uint8_t data_len );

/**
 * @brief RS232 to I2C read rx fifo function.
 * @details This function reads all data from RX fifo.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[out] data_out : Output data read.
 * @param[out] data_len : Output number of data bytes read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_read_rx_fifo ( rs232toi2c_t *ctx, uint8_t *data_out, uint8_t *data_len );

/**
 * @brief RS232 to I2C read system version function.
 * @details This function reads the system version.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[out] system_version : System version [3 bytes].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs232toi2c_read_system_version ( rs232toi2c_t *ctx, uint32_t *system_version );

/**
 * @brief RS232 to I2C set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rs232toi2c_set_rst_pin ( rs232toi2c_t *ctx, uint8_t state );

/**
 * @brief RS232 to I2C set wp pin function.
 * @details This function sets the WP pin logic state.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rs232toi2c_set_wp_pin ( rs232toi2c_t *ctx, uint8_t state );

/**
 * @brief RS232 to I2C reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rs232toi2c_reset_device ( rs232toi2c_t *ctx );

/**
 * @brief RS232 to I2C get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #rs232toi2c_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rs232toi2c_get_int_pin ( rs232toi2c_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RS232TOI2C_H

/*! @} */ // rs232toi2c

// ------------------------------------------------------------------------ END
