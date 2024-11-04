/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file cxpi.h
 * @brief This file contains API for CXPI Click Driver.
 */

#ifndef CXPI_H
#define CXPI_H

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
 * @addtogroup cxpi CXPI Click Driver
 * @brief API for configuring and manipulating CXPI Click driver.
 * @{
 */

/**
 * @defgroup cxpi_cmd CXPI Device Settings
 * @brief Settings for registers of CXPI Click driver.
 */

/**
 * @addtogroup cxpi_cmd
 * @{
 */

/**
 * @brief CXPI control commands.
 * @details Specified setting for control commands of CXPI Click driver.
 */
#define CXPI_PIN_STATE_DISABLE                0x00
#define CXPI_PIN_STATE_ENABLE                 0x01

/**
 * @brief CXPI driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       200

/*! @} */ // cxpi_cmd

/**
 * @defgroup cxpi_map CXPI MikroBUS Map
 * @brief MikroBUS pin mapping of CXPI Click driver.
 */

/**
 * @addtogroup cxpi_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of CXPI Click to the selected MikroBUS.
 */
#define CXPI_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // cxpi_map
/*! @} */ // cxpi

/**
 * @brief CXPI Click context object.
 * @details Context object definition of CXPI Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable. */
    digital_out_t pwm;          /**< Master Mode: Clock Input. */

    // Input pins
    digital_in_t int_pin;       /**< Slave Mode: Clock Output. */

    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */

} cxpi_t;

/**
 * @brief CXPI Click configuration object.
 * @details Configuration object definition of CXPI Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t en;             /**< Enable. */
    pin_name_t pwm;            /**< Master Mode: Clock Input. */
    pin_name_t int_pin;        /**< Slave Mode: Clock Output. */

    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} cxpi_cfg_t;

/**
 * @brief CXPI Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   CXPI_OK = 0,
   CXPI_ERROR = -1

} cxpi_return_value_t;

/*!
 * @addtogroup cxpi CXPI Click Driver
 * @brief API for configuring and manipulating CXPI Click driver.
 * @{
 */

/**
 * @brief CXPI configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #cxpi_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void cxpi_cfg_setup ( cxpi_cfg_t *cfg );

/**
 * @brief CXPI initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #cxpi_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #cxpi_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t cxpi_init ( cxpi_t *ctx, cxpi_cfg_t *cfg );

/**
 * @brief CXPI default configuration function.
 * @details This function executes a default configuration of CXPI
 * Click board.
 * @param[in] ctx : Click context object.
 * See #cxpi_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t cxpi_default_cfg ( cxpi_t *ctx );

/**
 * @brief CXPI data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #cxpi_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t cxpi_generic_write ( cxpi_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief CXPI data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #cxpi_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 */
err_t cxpi_generic_read ( cxpi_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Write Single Byte.
 * @details Writes sinle byte.
 * @param[in] ctx : Click context object.
 * See #cxpi_t object definition for detailed explanation.
 * @param[in] input  Byte for sending.
 * @return Nothing.
 */
void cxpi_write_byte ( cxpi_t *ctx, uint8_t input );

/**
 * @brief Read Single Byte.
 * @details Read received byte.
 * @param[in] ctx : Click context object.
 * See #cxpi_t object definition for detailed explanation.
 * @return Received byte.
 */
uint8_t cxpi_read_byte ( cxpi_t *ctx );

/**
 * @brief Check for new byte received.
 * @details Checks is there a new byte received.
 * @param[in] ctx : Click context object.
 * See #cxpi_t object definition for detailed explanation.
 * @return Returns the number of bytes that are available for reading.
 */
uint8_t cxpi_byte_ready ( cxpi_t *ctx );

/**
 * @brief Send command.
 * @details This function sends a command by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #cxpi_t object definition for detailed explanation.
 * @param[in] command : Command to be sent.
 * @return Nothing.
 */
void cxpi_send_command ( cxpi_t *ctx, char *command );

/**
 * @brief Set NSLP pin state function.
 * @details This function set state of the NSLP ( CS ) pin
 * of CXPI Transceiver for Automotive on CXPI Click board.
 * @param[out] ctx : Click context object.
 * See #cxpi_t object definition for detailed explanation.
 * @param[in] pin_state : Disable or Enable. 
 * @return Nothing.
 */
void cxpi_set_nslp_pin_state ( cxpi_t *ctx, uint8_t pin_state );

/**
 * @brief Set PWM pin state function.
 * @details This function set state of the PWM ( CLK ) pin
 * of CXPI Transceiver for Automotive on CXPI Click board.
 * @param[out] ctx : Click context object.
 * See #cxpi_t object definition for detailed explanation.
 * @param[in] pin_state : Disable or Enable.
 * @return Nothing.
 * 
 */
void cxpi_set_pwm_pin_state ( cxpi_t *ctx, uint8_t pin_state );

/**
 * @brief Set through mode function.
 * @details This function set through mode does not process Coding/Decoding
 * and it only drives signals from TXD to BUS and from BUS to RXD directly
 * of CXPI Transceiver for Automotive on CXPI Click board.
 * @param[in] ctx : Click context object.
 * See #cxpi_t object definition for detailed explanation.
 * @return Nothing.
 */
void cxpi_set_through_mode ( cxpi_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CXPI_H

/*! @} */ // cxpi

// ------------------------------------------------------------------------ END
