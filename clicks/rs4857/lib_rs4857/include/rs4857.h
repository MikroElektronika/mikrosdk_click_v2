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
 * @file rs4857.h
 * @brief This file contains API for RS485 7 Click Driver.
 */

#ifndef RS4857_H
#define RS4857_H

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
#include "drv_uart.h"

/*!
 * @addtogroup rs4857 RS485 7 Click Driver
 * @brief API for configuring and manipulating RS485 7 Click driver.
 * @{
 */

/**
 * @defgroup rs4857_cmd RS485 7 Device Settings
 * @brief Settings for registers of RS485 7 Click driver.
 */

/**
 * @addtogroup rs4857_cmd
 * @{
 */

/**
 * @brief RS485 7 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define RS4857_TX_DRV_BUFFER_SIZE    100
#define RS4857_RX_DRV_BUFFER_SIZE    300

/*! @} */ // rs4857_cmd

/**
 * @defgroup rs4857_map RS485 7 MikroBUS Map
 * @brief MikroBUS pin mapping of RS485 7 Click driver.
 */

/**
 * @addtogroup rs4857_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RS485 7 Click to the selected MikroBUS.
 */
#define RS4857_MAP_MIKROBUS( cfg, mikrobus )         \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.de = MIKROBUS( mikrobus, MIKROBUS_AN );      \
    cfg.re = MIKROBUS( mikrobus, MIKROBUS_RST );     \
    cfg.ret = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.tet = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rs4857_map
/*! @} */ // rs4857

/**
 * @brief RS485 7 Click context object.
 * @details Context object definition of RS485 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t de;     /**< Driver enable/disable pin. */
    digital_out_t re;     /**< Receiver enable/disable pin. */
    digital_out_t ret;    /**< Termination control for A/B pins. */
    digital_out_t tet;    /**< Termination control for Y/Z pins. */
    
    // Modules
    uart_t uart;          /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ RS4857_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    char uart_tx_buffer[ RS4857_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */

} rs4857_t;

/**
 * @brief RS485 7 Click configuration object.
 * @details Configuration object definition of RS485 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                 /**< RX pin. */
    pin_name_t tx_pin;                 /**< TX pin. */

    // Additional gpio pins
    pin_name_t de;                     /**< Driver enable/disable pin. */
    pin_name_t re;                     /**< Receiver enable/disable pin. */
    pin_name_t ret;                    /**< Termination control for A/B pins. */
    pin_name_t tet;                    /**< Termination control for Y/Z pins. */

    // Static variable
    uint32_t         baud_rate;        /**< Clock speed. */
    bool             uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;         /**< Data bits. */
    uart_parity_t    parity_bit;       /**< Parity bit. */
    uart_stop_bits_t stop_bit;         /**< Stop bits. */

} rs4857_cfg_t;

/**
 * @brief RS485 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RS4857_OK = 0,
    RS4857_ERROR = -1

} rs4857_return_value_t;

/*!
 * @addtogroup rs4857 RS485 7 Click Driver
 * @brief API for configuring and manipulating RS485 7 Click driver.
 * @{
 */

/**
 * @brief RS485 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rs4857_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rs4857_cfg_setup ( rs4857_cfg_t *cfg );

/**
 * @brief RS485 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rs4857_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs4857_init ( rs4857_t *ctx, rs4857_cfg_t *cfg );

/**
 * @brief RS485 7 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs4857_generic_write ( rs4857_t *ctx, char *data_in, uint16_t len );

/**
 * @brief RS485 7 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rs4857_generic_read ( rs4857_t *ctx, char *data_out, uint16_t len );

/**
 * @brief RS485 7 enables the receiver function.
 * @details This function enables the receiver
 * of the THVD1424, RS-485 Transceiver With Slew Rate Control
 * on the RS485 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs4857_receiver_enable ( rs4857_t *ctx );

/**
 * @brief RS485 7 disable the receiver function.
 * @details This function disable the receiver
 * of the THVD1424, RS-485 Transceiver With Slew Rate Control
 * on the RS485 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs4857_receiver_disable ( rs4857_t *ctx );

/**
 * @brief RS485 7 enables the driver function.
 * @details This function enables the driver
 * of the THVD1424, RS-485 Transceiver With Slew Rate Control
 * on the RS485 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs4857_driver_enable ( rs4857_t *ctx );

/**
 * @brief RS485 7 disable the driver function.
 * @details This function disable the driver
 * of the THVD1424, RS-485 Transceiver With Slew Rate Control
 * on the RS485 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs4857_driver_disable ( rs4857_t *ctx );

/**
 * @brief RS485 7 Y-Z termination enable function.
 * @details This function enable Y-Z termination 
 * of the THVD1424, RS-485 Transceiver With Slew Rate Control
 * on the RS485 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs4857_termination_xy_enable ( rs4857_t *ctx );

/**
 * @brief RS485 7 Y-Z termination disable function.
 * @details This function disable Y-Z termination 
 * of the THVD1424, RS-485 Transceiver With Slew Rate Control
 * on the RS485 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs4857_termination_xy_disable ( rs4857_t *ctx );

/**
 * @brief RS485 7 A-B termination enable function.
 * @details This function enable A-B termination 
 * of the THVD1424, RS-485 Transceiver With Slew Rate Control
 * on the RS485 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs4857_termination_ab_enable ( rs4857_t *ctx );

/**
 * @brief RS485 7 A-B termination disable function.
 * @details This function disable A-B termination 
 * of the THVD1424, RS-485 Transceiver With Slew Rate Control
 * on the RS485 7 Click board™.
 * @param[in] ctx : Click context object.
 * See #rs4857_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rs4857_termination_ab_disable ( rs4857_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // RS4857_H

/*! @} */ // rs4857

// ------------------------------------------------------------------------ END
