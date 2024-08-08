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
 * @file bm78.h
 * @brief This file contains API for BM78 Click Driver.
 */

#ifndef BM78_H
#define BM78_H

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
#include "bm78_config.h"

/*!
 * @addtogroup bm78 BM78 Click Driver
 * @brief API for configuring and manipulating BM78 Click driver.
 * @{
 */

/**
 * @defgroup bm78_cmd BM78 Device Settings
 * @brief Settings for registers of BM78 Click driver.
 */

/**
 * @addtogroup bm78_cmd
 * @{
 */

/**
 * @brief BM78 HCI Packet Type commands.
 * @details Specified setting for HCI Packet Type commands of BM78 Click driver.
 */
#define BM78_HCI_COMMAND_PACKET             0x01
#define BM78_HCI_ACL_DATA_PACKET            0x02
#define BM78_HCI_SYNCHRONOUS_DATA_PACKET    0x03
#define BM78_HCI_EVENT_PACKET               0x04
#define BM78_HCI_ISO_DATA_PACKET            0x05
#define BM78_HCI_COMMAND_COMPLETE           0x0E
#define BM78_HCI_COMMAND_IND_SUCCESS        0x00

/**
 * @brief BM78 page write number.
 * @details Specified setting for page write number of BM78 Click driver.
 */
#define BM78_PAGE_WRITE_NUMBER              0x08

/**
 * @brief BM78 pin state settings.
 * @details Specified setting for pin state of BM78 Click driver.
 */
#define BM78_PIN_STATE_HIGH                 0x01
#define BM78_PIN_STATE_LOW                  0x00

/**
 * @brief BM78 HCI commands.
 * @details Specified HCI commands of BM78 Click driver.
 */
#define BM78_OPCODE_RESET_CMD               0x030C
#define BM78_HCI_EEPROM_WR_PG_NUM_CMD       0x2DFC
#define BM78_HCI_EEPROM_WRITE_CMD           0x27FC
#define BM78_HCI_EEPROM_READ_CMD            0x29FC

/**
 * @brief BM78 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define BM78_TX_DRV_BUFFER_SIZE             100
#define BM78_RX_DRV_BUFFER_SIZE             300

/*! @} */ // bm78_cmd

/**
 * @defgroup bm78_map BM78 MikroBUS Map
 * @brief MikroBUS pin mapping of BM78 Click driver.
 */

/**
 * @addtogroup bm78_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of BM78 Click to the selected MikroBUS.
 */
#define BM78_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.st1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.st2 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // bm78_map
/*! @} */ // bm78

/**
 * @brief BM78 Click context object.
 * @details Context object definition of BM78 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                          /**< Reset pin. */
    digital_out_t cts;                          /**< Clear to send pin. */

    // Input pins
    digital_in_t st1;                          /**< Status Indication 1. */
    digital_in_t st2;                          /**< Status Indication 2. */
    digital_in_t rts;                          /**< Ready to send pin. */

    // Modules
    uart_t uart;                                /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ BM78_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ BM78_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

} bm78_t;

/**
 * @brief BM78 Click configuration object.
 * @details Configuration object definition of BM78 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t st1;                             /**< Status Indication 1. */
    pin_name_t rst;                             /**< Reset pin. */
    pin_name_t cts;                             /**< Clear to send pin. */
    pin_name_t st2;                             /**< Status Indication 2. */
    pin_name_t rts;                             /**< Ready to send pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

} bm78_cfg_t;

/**
 * @brief BM78 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BM78_OK = 0,
    BM78_ERROR = -1

} bm78_return_value_t;

/*!
 * @addtogroup bm78 BM78 Click Driver
 * @brief API for configuring and manipulating BM78 Click driver.
 * @{
 */

/**
 * @brief BM78 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bm78_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bm78_cfg_setup ( bm78_cfg_t *cfg );

/**
 * @brief BM78 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bm78_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm78_init ( bm78_t *ctx, bm78_cfg_t *cfg );

/**
 * @brief BM78 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm78_generic_write ( bm78_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief BM78 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm78_generic_read ( bm78_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief BM78 set RST pin function.
 * @details This function is used to set RST pin state.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @param[in] pin_state : Selected pin state.
 * @return Nothing.
 * @note None.
 */
void bm78_set_rst_pin ( bm78_t *ctx, uint8_t pin_state );

/**
 * @brief BM78 set CTS pin function.
 * @details This function is used to set CTS pin state.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @param[in] pin_state : Selected pin state.
 * @return Nothing.
 * @note None.
 */
void bm78_set_cts_pin ( bm78_t *ctx, uint8_t pin_state );

/**
 * @brief BM78 get ST1 pin function.
 * @details This function is used to get ST1 pin state.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @return @li @c 1 - Pin state high,
 *         @li @c 0 - Pin state low.
 * @note None.
 */
uint8_t bm78_get_st1_pin ( bm78_t *ctx );

/**
 * @brief BM78 get ST2 pin function.
 * @details This function is used to get ST2 pin state.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @return @li @c 1 - Pin state high,
 *         @li @c 0 - Pin state low.
 * @note None.
 */
uint8_t bm78_get_st2_pin ( bm78_t *ctx );

/**
 * @brief BM78 get RTS pin function.
 * @details This function is used to get RTS pin state.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @return @li @c 1 - Pin state high,
 *         @li @c 0 - Pin state low.
 * @note None.
 */
uint8_t bm78_get_rts_pin ( bm78_t *ctx );

/**
 * @brief BM78 Hardware reset function.
 * @details This function is used to perform hardware reset.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void bm78_hw_reset ( bm78_t *ctx );

/**
 * @brief BM78 EEPROM send command function.
 * @details This function is used to send specific EEPROM command by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @param[in] op_code : Specific 16-bit operation code.
 * @param[in] param : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm78_eeprom_send_cmd ( bm78_t *ctx, uint16_t op_code, uint8_t *param, uint8_t len );

/**
 * @brief BM78 EEPROM get event function.
 * @details This function is used to get event data by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @param[out] ev_type : Event type.
 * @param[out] len : Number of bytes that are read.
 * @param[out] data_rx : Output read data.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm78_eeprom_get_event ( bm78_t *ctx, uint8_t *ev_type, uint8_t *len, uint8_t *data_rx );

/**
 * @brief BM78 reset function.
 * @details This function is used to reset device to enable the EEPROM operation.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm78_reset_cmd ( bm78_t *ctx );

/**
 * @brief BM78 write EEPROM number function.
 * @details This function is used to specify the size of the EEPROM write operation.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note For the BM78 module Write number parameter is fixed as 0x08.
 */
err_t bm78_eeprom_write_number ( bm78_t *ctx );

/**
 * @brief BM78 EEPROM write function.
 * @details This function is used to write data into 
 * the EEPROM location specified by the address parameter.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @param[in] address : Start writing address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm78_eeprom_write ( bm78_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len );

/**
 * @brief BM78 EEPROM read function.
 * @details This function is used to read back 
 * the data from the EEPROM location specified by
 * the address paramete.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @param[in] address : Start writing address.
 * @param[in] data_out : Read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm78_eeprom_read ( bm78_t *ctx, uint16_t address, uint8_t *data_out, uint8_t len );

/**
 * @brief BM78 EEPROM flash function.
 * @details This function is used write default configuration into the EEPROM.
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bm78_flash_eeprom ( bm78_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BM78_H

/*! @} */ // bm78

// ------------------------------------------------------------------------ END
