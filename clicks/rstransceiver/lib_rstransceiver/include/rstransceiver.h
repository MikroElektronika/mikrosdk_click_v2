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
 * @file rstransceiver.h
 * @brief This file contains API for RS Transceiver Click Driver.
 */

#ifndef RSTRANSCEIVER_H
#define RSTRANSCEIVER_H

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
 * @addtogroup rstransceiver RS Transceiver Click Driver
 * @brief API for configuring and manipulating RS Transceiver Click driver.
 * @{
 */

/**
 * @defgroup rstransceiver_reg RS Transceiver Registers List
 * @brief List of registers of RS Transceiver Click driver.
 */

/**
 * @addtogroup rstransceiver_reg
 * @{
 */

/**
 * @brief RS Transceiver description register.
 * @details Specified register for description of RS Transceiver Click driver.
 */
#define RSTRANSCEIVER_REG_INPUT_PORT             0x00
#define RSTRANSCEIVER_REG_OUTPUT_PORT            0x01
#define RSTRANSCEIVER_REG_POLARITY_INV           0x02
#define RSTRANSCEIVER_REG_CONFIG                 0x03
#define RSTRANSCEIVER_REG_SPECIAL_FUNC           0x50

/*! @} */ // rstransceiver_reg

/**
 * @defgroup rstransceiver_set RS Transceiver Registers Settings
 * @brief Settings for registers of RS Transceiver Click driver.
 */

/**
 * @addtogroup rstransceiver_set
 * @{
 */

/**
 * @brief RS Transceiver pin bit mask values.
 * @details Specified pin bit mask values of RS Transceiver Click driver.
 */
#define RSTRANSCEIVER_NO_PIN_BIT_MASK            0x00
#define RSTRANSCEIVER_PIN_0_BIT_MASK             0x01
#define RSTRANSCEIVER_PIN_1_BIT_MASK             0x02
#define RSTRANSCEIVER_PIN_2_BIT_MASK             0x04
#define RSTRANSCEIVER_PIN_3_BIT_MASK             0x08
#define RSTRANSCEIVER_ALL_PINS_BIT_MASK          0x0F

/**
 * @brief RS Transceiver I/O pin direction values.
 * @details Specified I/O pin direction values of RS Transceiver Click driver.
 */
#define RSTRANSCEIVER_OUTPUT_DIRECTION           0x00
#define RSTRANSCEIVER_INPUT_DIRECTION            0x01

/**
 * @brief RS Transceiver special function values.
 * @details Specified special function values of RS Transceiver Click driver.
 */
#define RSTRANSCEIVER_SPECIAL_FUNC_P3_AS_INT     0x80
#define RSTRANSCEIVER_SPECIAL_FUNC_PU_DISABLED   0x40

/**
 * @brief RS Transceiver slew limiting values.
 * @details Specified slew limiting values of RS Transceiver Click driver.
 */
#define RSTRANSCEIVER_SLEW_DISABLE               0x00
#define RSTRANSCEIVER_SLEW_ENABLE                0x01

/**
 * @brief RS Transceiver operation mode selection values.
 * @details Specified operation mode selection values of RS Transceiver Click driver.
 */
#define RSTRANSCEIVER_OP_MODE_LOOPBACK           0x00
#define RSTRANSCEIVER_OP_MODE_RS232              0x01
#define RSTRANSCEIVER_OP_MODE_HALF_DUPLEX        0x02
#define RSTRANSCEIVER_OP_MODE_FULL_DUPLEX        0x03
#define RSTRANSCEIVER_OP_MODE_PIN_BIT_MASK       0x09

/**
 * @brief RS Transceiver DIR1 pin direction values.
 * @details Specified DIR1 pin direction values of RS Transceiver Click driver.
 */
#define RSTRANSCEIVER_DIR_DISABLE                0x00
#define RSTRANSCEIVER_DIR_T1_EN                  0x01
#define RSTRANSCEIVER_DIR_T1_EN_R1_DIS           0x01
#define RSTRANSCEIVER_DIR_PIN_BIT_MASK           0x0E

/**
 * @brief RS Transceiver receiver termination values.
 * @details Specified receiver termination values of RS Transceiver Click driver.
 */
#define RSTRANSCEIVER_TERM_DISABLE               0x00
#define RSTRANSCEIVER_TERM_ENABLE                0x01
#define RSTRANSCEIVER_TERM_DIS_PIN_BIT_MASK      0x07
#define RSTRANSCEIVER_TERM_EN_PIN_BIT_MASK       0x08

/**
 * @brief RS Transceiver driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define RSTRANSCEIVER_TX_DRV_BUFFER_SIZE         100
#define RSTRANSCEIVER_RX_DRV_BUFFER_SIZE         300

/**
 * @brief RS Transceiver device address setting.
 * @details Specified setting for device slave address selection of
 * RS Transceiver Click driver.
 */
#define RSTRANSCEIVER_DEVICE_ADDRESS              0x41

/*! @} */ // rstransceiver_set

/**
 * @defgroup rstransceiver_map RS Transceiver MikroBUS Map
 * @brief MikroBUS pin mapping of RS Transceiver Click driver.
 */

/**
 * @addtogroup rstransceiver_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RS Transceiver Click to the selected MikroBUS.
 */
#define RSTRANSCEIVER_MAP_MIKROBUS( cfg, mikrobus )  \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );    \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );    \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS );      \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.slw = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.cst = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rstransceiver_map
/*! @} */ // rstransceiver

/**
 * @brief RS Transceiver Click context object.
 * @details Context object definition of RS Transceiver Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cs;     /**< Request to send pin. */
    digital_out_t rst;    /**< Reset pin. */
    digital_out_t slw;    /**< Slew limiting pin. */

    // Input pins
    digital_in_t cst;    /**< Clear to send pin. */

    // Modules
    i2c_master_t i2c;    /**< I2C driver object. */
    uart_t uart;         /**< UART driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */
    
    // Buffers
    char uart_rx_buffer[ RSTRANSCEIVER_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    char uart_tx_buffer[ RSTRANSCEIVER_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */

} rstransceiver_t;

/**
 * @brief RS Transceiver Click configuration object.
 * @details Configuration object definition of RS Transceiver Click driver.
 */
typedef struct
{
    pin_name_t scl;       /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;       /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rx_pin;    /**< RX pin. */
    pin_name_t tx_pin;    /**< TX pin. */

    pin_name_t cs;     /**< Request to send pin. */
    pin_name_t rst;    /**< Reset pin. */
    pin_name_t slw;    /**< Slew limiting pin. */
    pin_name_t cst;    /**< Clear to send pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */
    
    // Static variable
    uint32_t         baud_rate;        /**< Clock speed. */
    bool             uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;         /**< Data bits. */
    uart_parity_t    parity_bit;       /**< Parity bit. */
    uart_stop_bits_t stop_bit;         /**< Stop bits. */

} rstransceiver_cfg_t;

/**
 * @brief RS Transceiver Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RSTRANSCEIVER_OK = 0,
    RSTRANSCEIVER_ERROR = -1

} rstransceiver_return_value_t;

/*!
 * @addtogroup rstransceiver RS Transceiver Click Driver
 * @brief API for configuring and manipulating RS Transceiver Click driver.
 * @{
 */

/**
 * @brief RS Transceiver configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rstransceiver_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rstransceiver_cfg_setup ( rstransceiver_cfg_t *cfg );

/**
 * @brief RS Transceiver initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rstransceiver_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rstransceiver_init ( rstransceiver_t *ctx, rstransceiver_cfg_t *cfg );

/**
 * @brief RS Transceiver default configuration function.
 * @details This function executes a default configuration of RS Transceiver
 * click board.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rstransceiver_default_cfg ( rstransceiver_t *ctx );

/**
 * @brief RS Transceiver enables the device function.
 * @details This function performs enables the device by config the RST pin logic high
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rstransceiver_device_enable ( rstransceiver_t *ctx );

/**
 * @brief RS Transceiver disable the device function.
 * @details This function performs shutdown the device by config the RST pin logic low
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rstransceiver_device_disable ( rstransceiver_t *ctx );

/**
 * @brief RS Transceiver sets the slew limit function.
 * @details This function sets the 250 kbps slew limiting
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[in] slew :
 *         @li @c 0x00 (RSTRANSCEIVER_SLEW_DISABLE) - Disable slew limiting,
 *         @li @c 0x01 (RSTRANSCEIVER_SLEW_ENABLE) - Enables 250 kbps slew limiting.
 * @return Nothing.
 * @note None.
 */
void rstransceiver_set_slew ( rstransceiver_t *ctx, uint8_t slew );

/**
 * @brief RS Transceiver request to send function.
 * @details This function RTS flow control uses the Request-to-Send
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[in] rts : Request to send.
 * @return Nothing.
 * @note None.
 */
void rstransceiver_set_rts ( rstransceiver_t *ctx, uint8_t rts );

/**
 * @brief RS Transceiver clear to send function.
 * @details This function CTS flow control uses the check the clear to send
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @return Check the clear to send (CTS).
 * @note None.
 */
uint8_t rstransceiver_get_cts ( rstransceiver_t *ctx );

/**
 * @brief RS Transceiver sets the operating mode function.
 * @details This function sets the desired operating mode
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[in] op_mode :
 *         @li @c 0x00 (RSTRANSCEIVER_OP_MODE_LOOPBACK)    - Loopback mode,
 *         @li @c 0x01 (RSTRANSCEIVER_OP_MODE_RS232)       - RS-232 mode.,
 *         @li @c 0x02 (RSTRANSCEIVER_OP_MODE_HALF_DUPLEX) - Half-Duplex RS-485,
 *         @li @c 0x03 (RSTRANSCEIVER_OP_MODE_FULL_DUPLEX) - Full-Duplex RS-485/422,
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rstransceiver_set_op_mode ( rstransceiver_t *ctx, uint8_t op_mode );

/**
 * @brief RS Transceiver sets the loopback mode function.
 * @details This function sets the loopback operating mode
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rstransceiver_mode_loopback ( rstransceiver_t *ctx );

/**
 * @brief RS Transceiver sets the RS-232 mode function.
 * @details This function sets the RS-232 operating mode
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[in] slew :
 *         @li @c 0x00 (RSTRANSCEIVER_SLEW_DISABLE) - Disable slew limiting,
 *         @li @c 0x01 (RSTRANSCEIVER_SLEW_ENABLE) - Enables 250 kbps slew limiting.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rstransceiver_mode_rs232 ( rstransceiver_t *ctx, uint8_t slew );

/**
 * @brief RS Transceiver sets the Half-Duplex mode function.
 * @details This function sets the Half-Duplex RS-485 operating mode
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[in] slew :
 *         @li @c 0x00 (RSTRANSCEIVER_SLEW_DISABLE) - Disable slew limiting,
 *         @li @c 0x01 (RSTRANSCEIVER_SLEW_ENABLE) - Enables 250 kbps slew limiting.
 * @param[in] dir1 :
 *         @li @c 0x00 (RSTRANSCEIVER_DIR_DISABLE) - Disable,
 *         @li @c 0x01 (RSTRANSCEIVER_DIR_T1_EN)   - RX (T1) enable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rstransceiver_mode_half_duplex ( rstransceiver_t *ctx, uint8_t slew, uint8_t dir1, uint8_t term );

/**
 * @brief RS Transceiver sets the Full-Duplex mode function.
 * @details This function sets the Full-Duplex RS-485/422 operating mode
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[in] slew :
 *         @li @c 0x00 (RSTRANSCEIVER_SLEW_DISABLE) - Disable slew limiting,
 *         @li @c 0x01 (RSTRANSCEIVER_SLEW_ENABLE) - Enables 250 kbps slew limiting.
 * @param[in] dir1 :
 *         @li @c 0x00 (RSTRANSCEIVER_DIR_DISABLE) - Disable,
 *         @li @c 0x01 (RSTRANSCEIVER_DIR_T1_EN_R1_DIS) - RX (T1) enable, TX (R1) disable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rstransceiver_mode_full_duplex ( rstransceiver_t *ctx, uint8_t slew, uint8_t dir1, uint8_t term );

/**
 * @brief RS Transceiver sets the DIR1 pin function.
 * @details This function configures TX/RX signals
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[in] dir1 :
 *         @li @c 0x00 (RSTRANSCEIVER_DIR_DISABLE) - Disable,
 *         @li @c 0x01 (RSTRANSCEIVER_DIR_T1_EN_R1_DIS) - Full-Duplex, RX (T1) enable, TX (R1) disable,
 *         @li @c 0x01 (RSTRANSCEIVER_DIR_T1_EN)   - Half-Duplex, RX (T1) enable.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rstransceiver_set_dir1 ( rstransceiver_t *ctx, uint8_t dir1 );

/**
 * @brief RS Transceiver term enable function.
 * @details This function enables the RS485/RS422 receiver termination
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rstransceiver_term_enable ( rstransceiver_t *ctx );

/**
 * @brief RS Transceiver term disable function.
 * @details This function disable the RS485/RS422 receiver termination
 * of the XR34350, RS-232/RS-485/RS-422 Serial Transceiver 
 * with Internal Termination and Wide Output Swing
 * on the RS Transceiver Click board™.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rstransceiver_term_disable ( rstransceiver_t *ctx );

/**
 * @brief RS Transceiver data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rstransceiver_generic_write ( rstransceiver_t *ctx, char *data_in, uint16_t len );

/**
 * @brief RS Transceiver data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rstransceiver_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rstransceiver_generic_read ( rstransceiver_t *ctx, char *data_out, uint16_t len );

#ifdef __cplusplus
}
#endif
#endif // RSTRANSCEIVER_H

/*! @} */ // rstransceiver

// ------------------------------------------------------------------------ END
