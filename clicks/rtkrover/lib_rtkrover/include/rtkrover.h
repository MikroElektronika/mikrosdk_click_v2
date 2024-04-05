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
 * @file rtkrover.h
 * @brief This file contains API for RTK Rover Click Driver.
 */

#ifndef RTKROVER_H
#define RTKROVER_H

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
 * @addtogroup rtkrover RTK Rover Click Driver
 * @brief API for configuring and manipulating RTK Rover Click driver.
 * @{
 */

/**
 * @defgroup rtkrover_cmd RTK Rover Device Settings
 * @brief Settings for registers of RTK Rover Click driver.
 */

/**
 * @addtogroup rtkrover_cmd
 * @{
 */

/**
 * @brief RTK Rover response buffer commands.
 * @details Specified response buffer commands of RTK Rover Click driver.
 */
#define RTKROVER_RSP_START                              "$"
#define RTKROVER_RSP_DELIMITER                          ","
#define RTKROVER_RSP_END_SEQ                            "\r\n"
#define RTKROVER_RSP_GNGGA                              "$GNGGA"

/**
 * @brief RTK Rover GNGGA command elements.
 * @details Specified GNGGA command elements of RTK Rover Click driver.
 */
#define RTKROVER_GNGGA_ELEMENT_SIZE                     15
#define RTKROVER_GNGGA_TIME                             1
#define RTKROVER_GNGGA_LATITUDE                         2
#define RTKROVER_GNGGA_LATITUDE_SIDE                    3
#define RTKROVER_GNGGA_LONGITUDE                        4
#define RTKROVER_GNGGA_LONGITUDE_SIDE                   5
#define RTKROVER_GNGGA_QUALITY_INDICATOR                6
#define RTKROVER_GNGGA_NUMBER_OF_SATELLITES             7
#define RTKROVER_GNGGA_H_DILUTION_OF_POS                8
#define RTKROVER_GNGGA_ALTITUDE                         9
#define RTKROVER_GNGGA_ALTITUDE_UNIT                    10
#define RTKROVER_GNGGA_GEOIDAL_SEPARATION               11
#define RTKROVER_GNGGA_GEOIDAL_SEPARATION_UNIT          12
#define RTKROVER_GNGGA_TIME_SINCE_LAST_DGPS             13
#define RTKROVER_GNGGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief RTK Rover driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_TX_BUFFER_SIZE                              100
#define DRV_RX_BUFFER_SIZE                              1000

/*! @} */ // rtkrover_cmd

/**
 * @defgroup rtkrover_map RTK Rover MikroBUS Map
 * @brief MikroBUS pin mapping of RTK Rover Click driver.
 */

/**
 * @addtogroup rtkrover_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTK Rover Click to the selected MikroBUS.
 */
#define RTKROVER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.shd = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.bt = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // rtkrover_map
/*! @} */ // rtkrover

/**
 * @brief RTK Rover Click context object.
 * @details Context object definition of RTK Rover Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t shd;          /**< Shutdown pin (Active low). */
    digital_out_t rst;          /**< Reset pin (Active low). */
    digital_out_t wup;          /**< Wake up pin (Active high). */
    digital_out_t bt;           /**< Boot pin (Active high). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (TX1 ready) informs when transmission buffer is full. */

    // Modules
    uart_t uart;                /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */

} rtkrover_t;

/**
 * @brief RTK Rover Click configuration object.
 * @details Configuration object definition of RTK Rover Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t shd;             /**< Shutdown pin (Active low). */
    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t wup;             /**< Wake up pin (Active high). */
    pin_name_t bt;              /**< Boot pin (Active high). */
    pin_name_t int_pin;         /**< Interrupt pin (TX1 ready) informs when transmission buffer is full. */

    // Static variable
    uint32_t          baud_rate;                /**< Clock speed. */
    bool              uart_blocking;            /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;                 /**< Data bits. */
    uart_parity_t     parity_bit;               /**< Parity bit. */
    uart_stop_bits_t  stop_bit;                 /**< Stop bits. */

} rtkrover_cfg_t;

/**
 * @brief RTK Rover Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTKROVER_OK = 0,
    RTKROVER_ERROR = -1

} rtkrover_return_value_t;

/*!
 * @addtogroup rtkrover RTK Rover Click Driver
 * @brief API for configuring and manipulating RTK Rover Click driver.
 * @{
 */

/**
 * @brief RTK Rover configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtkrover_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtkrover_cfg_setup ( rtkrover_cfg_t *cfg );

/**
 * @brief RTK Rover initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rtkrover_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtkrover_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtkrover_init ( rtkrover_t *ctx, rtkrover_cfg_t *cfg );

/**
 * @brief RTK Rover data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rtkrover_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtkrover_generic_write ( rtkrover_t *ctx, char *data_in, uint16_t len );

/**
 * @brief RTK Rover data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #rtkrover_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtkrover_generic_read ( rtkrover_t *ctx, char *data_out, uint16_t len );

/**
 * @brief RTK Rover clear ring buffers function.
 * @details This function clears UART tx and rx ring buffers.
 * @param[in] ctx : Click context object.
 * See #rtkrover_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void rtkrover_clear_ring_buffers ( rtkrover_t *ctx );

/**
 * @brief RTK Rover set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtkrover_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtkrover_set_rst_pin ( rtkrover_t *ctx, uint8_t state );

/**
 * @brief RTK Rover set WUP pin function.
 * @details This function sets the WUP pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtkrover_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtkrover_set_wup_pin ( rtkrover_t *ctx, uint8_t state );

/**
 * @brief RTK Rover set BOOT pin function.
 * @details This function sets the BOOT pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtkrover_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtkrover_set_boot_pin ( rtkrover_t *ctx, uint8_t state );

/**
 * @brief RTK Rover set SHD pin function.
 * @details This function sets the SHD pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtkrover_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtkrover_set_shd_pin ( rtkrover_t *ctx, uint8_t state );

/**
 * @brief RTK Rover get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtkrover_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtkrover_get_int_pin ( rtkrover_t *ctx );

/**
 * @brief RTK Rover parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : GNGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtkrover_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // RTKROVER_H

/*! @} */ // rtkrover

// ------------------------------------------------------------------------ END
