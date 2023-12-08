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
 * @file ir.h
 * @brief This file contains API for IR Click Driver.
 */

#ifndef IR_H
#define IR_H

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
#include "drv_uart.h"
#include "drv_pwm.h"

/*!
 * @addtogroup ir IR Click Driver
 * @brief API for configuring and manipulating IR Click driver.
 * @{
 */

/**
 * @defgroup ir_cmd IR Device Settings
 * @brief Settings for registers of IR Click driver.
 */

/**
 * @addtogroup ir_cmd
 * @{
 */

/**
 * @brief IR control commands.
 * @details Specified setting for control commands of IR Click driver.
 */
#define IR_STATE_HIGH           0x01
#define IR_STATE_LOW            0x00

/**
 * @brief IR driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE         200

/**
 * @brief IR default PWM frequency.
 * @details Specified setting for setting default PWM frequency of IR Click driver.
 */
#define IR_DEF_FREQ             38000

/*! @} */ // ir_cmd

/**
 * @defgroup ir_map IR MikroBUS Map
 * @brief MikroBUS pin mapping of IR Click driver.
 */

/**
 * @addtogroup ir_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of IR Click to the selected MikroBUS.
 */
#define IR_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.an     = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pwm    = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // ir_map
/*! @} */ // ir

/**
 * @brief IR Click driver selector.
 * @details Selects target driver interface of IR Click driver.
 */
typedef enum
{
   IR_DRV_SEL_GPIO,      /**< GPIO driver descriptor. */
   IR_DRV_SEL_UART       /**< UART driver descriptor. */

} ir_drv_t;

/**
 * @brief IR Click context object.
 * @details Context object definition of IR Click driver.
 */
typedef struct
{

    // Input pins
    digital_in_t an;         /**< RX pin. */
    
    // Modules
    uart_t uart;             /**< UART driver object. */
    pwm_t pwm;               /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;       /**< PWM frequency value. */
    
    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */

    ir_drv_t  drv_sel;     /**< Master driver interface selector. */
    
} ir_t;

/**
 * @brief IR Click configuration object.
 * @details Configuration object definition of IR Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t an;              /**< RX pin. */
    pin_name_t pwm;             /**< TX pin. */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */
    
    uint32_t dev_pwm_freq;              /**< PWM frequency value. */

    ir_drv_t  drv_sel;                  /**< Master driver interface selector. */
    
} ir_cfg_t;

/**
 * @brief IR Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    IR_OK = 0,
    IR_ERROR = -1

} ir_return_value_t;

/*!
 * @addtogroup ir IR Click Driver
 * @brief API for configuring and manipulating IR Click driver.
 * @{
 */

/**
 * @brief IR configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ir_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ir_cfg_setup ( ir_cfg_t *cfg );

/**
 * @brief IR driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #ir_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #ir_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void ir_drv_interface_selection ( ir_cfg_t *cfg, ir_drv_t drv_sel );

/**
 * @brief IR initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ir_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ir_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ir_init ( ir_t *ctx, ir_cfg_t *cfg );

/**
 * @brief IR data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ir_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ir_generic_write ( ir_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief IR data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #ir_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 */
err_t ir_generic_read ( ir_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief IR get AN pin state function.
 * @details This function reads a state of the AN pin, when AN is low 
 * there is IR signal receaved by TSOP38338 IR receiver module.
 * @param[in] ctx : Click context object.
 * See #ir_t object definition for detailed explanation.
 * @return State of the AN pin.
 */
uint8_t ir_get_an_state ( ir_t *ctx );

/**
 * @brief IR NEC send data function.
 * @details This function sends a 8-bit command to a 8-bit address using NEC protocol.
 * @param[in] ctx : Click context object.
 * See #ir_t object definition for detailed explanation.
 * @param[in] address : Input address data.
 * @param[in] command : Input command data.
 * @return Nothing.
 * 
 * @note This function can only be used in GPIO mode.
 */
void ir_nec_send_command ( ir_t *ctx, uint8_t address, uint8_t command );

/**
 * @brief IR NEC data reading function.
 * @details This function reads a byte of address and command data by using NEC protocol.
 * @param[in] ctx : Click context object.
 * See #ir_t object definition for detailed explanation.
 * @param[out] address : Output read address data.
 * @param[out] command : Output read command data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can only be used in GPIO mode.
 */
err_t ir_nec_read_command ( ir_t *ctx, uint8_t *address, uint8_t *command );

#ifdef __cplusplus
}
#endif
#endif // IR_H

/*! @} */ // ir

// ------------------------------------------------------------------------ END
