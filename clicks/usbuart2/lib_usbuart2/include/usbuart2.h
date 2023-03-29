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
 * @file usbuart2.h
 * @brief This file contains API for USB UART 2 Click Driver.
 */

#ifndef USBUART2_H
#define USBUART2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"

/*!
 * @addtogroup usbuart2 USB UART 2 Click Driver
 * @brief API for configuring and manipulating USB UART 2 Click driver.
 * @{
 */

/**
 * @defgroup usbuart2_set USB UART 2 Device Settings
 * @brief Settings for registers of USB UART 2 Click driver.
 */

/**
 * @addtogroup usbuart2_set
 * @{
 */

/**
 * @brief USB UART 2 description setting.
 * @details Specified setting for description of USB UART 2 Click driver.
 */

#define USBUART2_MODE_SLEEP 1
#define USBUART2_MODE_NORMAL 0

#define USBUART2_CTS_ACTIVE  1
#define USBUART2_CTS_NO_ACTIVE 0

#define USBUART2_POWER_ON  1
#define USBUART2_POWER_OFF 0

/**
 * @brief USB UART 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                       500

/*! @} */ // usbuart2_set

/**
 * @defgroup usbuart2_map USB UART 2 MikroBUS Map
 * @brief MikroBUS pin mapping of USB UART 2 Click driver.
 */

/**
 * @addtogroup usbuart2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of USB UART 2 Click to the selected MikroBUS.
 */
#define USBUART2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwr = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // usbuart2_map
/*! @} */ // usbuart2

/**
 * @brief USB UART 2 Click context object.
 * @details Context object definition of USB UART 2 Click driver.
 */
typedef struct
{
    // Output pins
    
    digital_out_t cts;  
    digital_out_t slp;  
    digital_out_t pwr;   
    // Input pins
    
    digital_in_t rts;     

    // Modules
    uart_t uart;                                    /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ];         /**< Buffer size. */

} usbuart2_t;

/**
 * @brief USB UART 2 Click configuration object.
 * @details Configuration object definition of USB UART 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                                  /**< RX pin. */
    pin_name_t tx_pin;                                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t cts;        
    pin_name_t slp;      
    pin_name_t pwr;    
    pin_name_t rts;        

    // Static variable
    uint32_t          baud_rate;                        /**< Clock speed. */
    bool              uart_blocking;                    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                         /**< Data bits. */
    uart_parity_t     parity_bit;                       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                         /**< Stop bits. */

} usbuart2_cfg_t;

/**
 * @brief USB UART 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   USBUART2_OK = 0,
   USBUART2_ERROR = -1

} usbuart2_return_value_t;

/*!
 * @addtogroup usbuart2 USB UART 2 Click Driver
 * @brief API for configuring and manipulating USB UART 2 Click driver.
 * @{
 */

/**
 * @brief USB UART 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #usbuart2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void usbuart2_cfg_setup ( usbuart2_cfg_t *cfg );

/**
 * @brief USB UART 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #usbuart2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #usbuart2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t usbuart2_init ( usbuart2_t *ctx, usbuart2_cfg_t *cfg );

/**
 * @brief USB UART 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #usbuart2_t object definition for detailed explanation.
 * @param[in] data_buf : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
void usbuart2_generic_write ( usbuart2_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief USB UART 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #usbuart2_t object definition for detailed explanation.
 * @param[out] data_buf : Output read data.
 * @param[in] max_len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint32_t usbuart2_generic_read ( usbuart2_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Power control.
 * @details This function sets the click turns click on.
 * @param[out] ctx : Click context object.
 * See #usbuart2_t object definition for detailed explanation.
 * @param[in] state : PWR pin state
 * @return Nothing.
 */
void usbuart2_pwr_ctrl ( usbuart2_t *ctx, uint8_t state );

/**
 * @brief Set CTS (Clear to send)
 * @details This function sets CTS pin.
 * @param[out] ctx : Click context object.
 * See #usbuart2_t object definition for detailed explanation.
 * @param[in] state : CTS pin state
 * @return Nothing.
 */
void usbuart2_set_cts ( usbuart2_t *ctx, uint8_t state );

/**
 * @brief Set device mode
 * @details This function sets device mode.
 * @param[out] ctx : Click context object.
 * See #usbuart2_t object definition for detailed explanation.
 * @param[in] mode : Device mode (Sleep or Normal)
 * @return Nothing.
 */
void usbuart2_set_mode ( usbuart2_t *ctx, uint8_t mode );

/**
 * @brief Set device mode
 * @details This function reads RTS pin state.
 * @param[in] ctx : Click context object.
 * @return RTS (Request to send) pin state
 */
uint8_t usbuart2_get_rts ( usbuart2_t *ctx );

/**
 * @brief Function for send command
 * @details This function is used for sending commands.
 * @param[in] ctx : Click context object.
 * @param[in] command : Data to be send.
 * @return Nothing.
 */
void usbuart2_send_command ( usbuart2_t *ctx, char *command );
#ifdef __cplusplus
}
#endif
#endif // USBUART2_H

/*! @} */ // usbuart2

// ------------------------------------------------------------------------ END
