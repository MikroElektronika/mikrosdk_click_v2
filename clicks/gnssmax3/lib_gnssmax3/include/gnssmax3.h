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
 * @file gnssmax3.h
 * @brief This file contains API for GNSS MAX 3 Click Driver.
 */

#ifndef GNSSMAX3_H
#define GNSSMAX3_H

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
 * @addtogroup gnssmax3 GNSS MAX 3 Click Driver
 * @brief API for configuring and manipulating GNSS MAX 3 Click driver.
 * @{
 */

/**
 * @defgroup gnssmax3_cmd GNSS MAX 3 Device Settings
 * @brief Settings of GNSS MAX 3 Click driver.
 */

/**
 * @addtogroup gnssmax3_cmd
 * @{
 */

/**
 * @brief GNSS MAX 3 response buffer commands.
 * @details Specified response buffer commands of GNSS MAX 3 Click driver.
 */
#define GNSSMAX3_RSP_START                              "$"
#define GNSSMAX3_RSP_DELIMITER                          ","
#define GNSSMAX3_RSP_END                                "\r\n"
#define GNSSMAX3_RSP_GGA                                "GGA"

/**
 * @brief GNSS MAX 3 GGA command elements.
 * @details Specified GGA command elements of GNSS MAX 3 Click driver.
 */
#define GNSSMAX3_GGA_ELEMENT_SIZE                       15
#define GNSSMAX3_GGA_TIME                               1
#define GNSSMAX3_GGA_LATITUDE                           2
#define GNSSMAX3_GGA_LATITUDE_SIDE                      3
#define GNSSMAX3_GGA_LONGITUDE                          4
#define GNSSMAX3_GGA_LONGITUDE_SIDE                     5
#define GNSSMAX3_GGA_QUALITY_INDICATOR                  6
#define GNSSMAX3_GGA_NUMBER_OF_SATELLITES               7
#define GNSSMAX3_GGA_H_DILUTION_OF_POS                  8
#define GNSSMAX3_GGA_ALTITUDE                           9
#define GNSSMAX3_GGA_ALTITUDE_UNIT                      10
#define GNSSMAX3_GGA_GEOIDAL_SEPARATION                 11
#define GNSSMAX3_GGA_GEOIDAL_SEPARATION_UNIT            12
#define GNSSMAX3_GGA_TIME_SINCE_LAST_DGPS               13
#define GNSSMAX3_GGA_DGPS_REFERENCE_STATION_ID          14

/**
 * @brief GNSS MAX 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSSMAX3_TX_DRV_BUFFER_SIZE                     100
#define GNSSMAX3_RX_DRV_BUFFER_SIZE                     800

/*! @} */ // gnssmax3_cmd

/**
 * @defgroup gnssmax3_map GNSS MAX 3 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS MAX 3 Click driver.
 */

/**
 * @addtogroup gnssmax3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS MAX 3 Click to the selected MikroBUS.
 */
#define GNSSMAX3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.exi = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pps = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnssmax3_map
/*! @} */ // gnssmax3

/**
 * @brief GNSS MAX 3 Click context object.
 * @details Context object definition of GNSS MAX 3 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;                  /**< Reset pin (active low). */
    digital_out_t exi;                  /**< External interrupt pin. */

    // Input pins
    digital_in_t pps;                   /**< Pulse per second pin. */

    // Modules
    uart_t uart;                        /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSSMAX3_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ GNSSMAX3_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} gnssmax3_t;

/**
 * @brief GNSS MAX 3 Click configuration object.
 * @details Configuration object definition of GNSS MAX 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                     /**< Reset pin (active low). */
    pin_name_t exi;                     /**< External interrupt pin. */
    pin_name_t pps;                     /**< Pulse per second pin. */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} gnssmax3_cfg_t;

/**
 * @brief GNSS MAX 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSSMAX3_OK = 0,
    GNSSMAX3_ERROR = -1

} gnssmax3_return_value_t;

/*!
 * @addtogroup gnssmax3 GNSS MAX 3 Click Driver
 * @brief API for configuring and manipulating GNSS MAX 3 Click driver.
 * @{
 */

/**
 * @brief GNSS MAX 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnssmax3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnssmax3_cfg_setup ( gnssmax3_cfg_t *cfg );

/**
 * @brief GNSS MAX 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnssmax3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnssmax3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax3_init ( gnssmax3_t *ctx, gnssmax3_cfg_t *cfg );

/**
 * @brief GNSS MAX 3 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax3_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax3_generic_write ( gnssmax3_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS MAX 3 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax3_generic_read ( gnssmax3_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS MAX 3 get PPS pin function.
 * @details This function returns the PSS pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssmax3_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssmax3_get_pps_pin ( gnssmax3_t *ctx );

/**
 * @brief GNSS MAX 3 set EXI pin function.
 * @details This function sets the EXI pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssmax3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssmax3_set_exi_pin ( gnssmax3_t *ctx, uint8_t state );

/**
 * @brief GNSS MAX 3 set RST pin function.
 * @details This function sets the reset (RST) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssmax3_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssmax3_set_rst_pin ( gnssmax3_t *ctx, uint8_t state );

/**
 * @brief GNSS MAX 3 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnssmax3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnssmax3_reset_device ( gnssmax3_t *ctx );

/**
 * @brief GNSS MAX 3 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax3_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSSMAX3_H

/*! @} */ // gnssmax3

// ------------------------------------------------------------------------ END
