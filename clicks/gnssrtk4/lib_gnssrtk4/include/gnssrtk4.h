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
 * @file gnssrtk4.h
 * @brief This file contains API for GNSS RTK 4 Click Driver.
 */

#ifndef GNSSRTK4_H
#define GNSSRTK4_H

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
 * @addtogroup gnssrtk4 GNSS RTK 4 Click Driver
 * @brief API for configuring and manipulating GNSS RTK 4 Click driver.
 * @{
 */

/**
 * @defgroup gnssrtk4_cmd GNSS RTK 4 Device Settings
 * @brief Settings for registers of GNSS RTK 4 Click driver.
 */

/**
 * @addtogroup gnssrtk4_cmd
 * @{
 */

/**
 * @brief GNSS RTK 4 response buffer commands.
 * @details Specified response buffer commands of GNSS RTK 4 Click driver.
 */
#define GNSSRTK4_RSP_START                              "$"
#define GNSSRTK4_RSP_DELIMITER                          ","
#define GNSSRTK4_RSP_END                                "\r\n"
#define GNSSRTK4_RSP_GGA                                "GGA"

/**
 * @brief GNSS RTK 4 GGA command elements.
 * @details Specified GGA command elements of GNSS RTK 4 Click driver.
 */
#define GNSSRTK4_GGA_ELEMENT_SIZE                       15
#define GNSSRTK4_GGA_TIME                               1
#define GNSSRTK4_GGA_LATITUDE                           2
#define GNSSRTK4_GGA_LATITUDE_SIDE                      3
#define GNSSRTK4_GGA_LONGITUDE                          4
#define GNSSRTK4_GGA_LONGITUDE_SIDE                     5
#define GNSSRTK4_GGA_QUALITY_INDICATOR                  6
#define GNSSRTK4_GGA_NUMBER_OF_SATELLITES               7
#define GNSSRTK4_GGA_H_DILUTION_OF_POS                  8
#define GNSSRTK4_GGA_ALTITUDE                           9
#define GNSSRTK4_GGA_ALTITUDE_UNIT                      10
#define GNSSRTK4_GGA_GEOIDAL_SEPARATION                 11
#define GNSSRTK4_GGA_GEOIDAL_SEPARATION_UNIT            12
#define GNSSRTK4_GGA_TIME_SINCE_LAST_DGPS               13
#define GNSSRTK4_GGA_DGPS_REFERENCE_STATION_ID          14

/**
 * @brief GNSS RTK 4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSSRTK4_TX_DRV_BUFFER_SIZE                     100
#define GNSSRTK4_RX_DRV_BUFFER_SIZE                     1000

/*! @} */ // gnssrtk4_cmd

/**
 * @defgroup gnssrtk4_map GNSS RTK 4 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS RTK 4 Click driver.
 */

/**
 * @addtogroup gnssrtk4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS RTK 4 Click to the selected MikroBUS.
 */
#define GNSSRTK4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sta = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.evt = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pps = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnssrtk4_map
/*! @} */ // gnssrtk4

/**
 * @brief GNSS RTK 4 Click context object.
 * @details Context object definition of GNSS RTK 4 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active high). */
    digital_out_t evt;              /**< Event pin. */

    // Input pins
    digital_in_t sta;               /**< RTK Status pin (high - fixed point). */
    digital_in_t pps;               /**< Pulse per second pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSSRTK4_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ GNSSRTK4_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} gnssrtk4_t;

/**
 * @brief GNSS RTK 4 Click configuration object.
 * @details Configuration object definition of GNSS RTK 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t sta;                 /**< RTK Status pin (high - fixed point). */
    pin_name_t rst;                 /**< Reset pin (active high). */
    pin_name_t evt;                 /**< Event pin. */
    pin_name_t pps;                 /**< Pulse per second pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} gnssrtk4_cfg_t;

/**
 * @brief GNSS RTK 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSSRTK4_OK = 0,
    GNSSRTK4_ERROR = -1

} gnssrtk4_return_value_t;

/*!
 * @addtogroup gnssrtk4 GNSS RTK 4 Click Driver
 * @brief API for configuring and manipulating GNSS RTK 4 Click driver.
 * @{
 */

/**
 * @brief GNSS RTK 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnssrtk4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnssrtk4_cfg_setup ( gnssrtk4_cfg_t *cfg );

/**
 * @brief GNSS RTK 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnssrtk4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnssrtk4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk4_init ( gnssrtk4_t *ctx, gnssrtk4_cfg_t *cfg );

/**
 * @brief GNSS RTK 4 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssrtk4_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk4_generic_write ( gnssrtk4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS RTK 4 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssrtk4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk4_generic_read ( gnssrtk4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS RTK 4 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssrtk4_set_rst_pin ( gnssrtk4_t *ctx, uint8_t state );

/**
 * @brief GNSS RTK 4 set EVT pin function.
 * @details This function sets the EVT pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssrtk4_set_evt_pin ( gnssrtk4_t *ctx, uint8_t state );

/**
 * @brief GNSS RTK 4 get STA pin function.
 * @details This function returns the RTK Status (STA) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssrtk4_get_sta_pin ( gnssrtk4_t *ctx );

/**
 * @brief GNSS RTK 4 get PPS pin function.
 * @details This function returns the pulse per second (PPS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssrtk4_get_pps_pin ( gnssrtk4_t *ctx );

/**
 * @brief GNSS RTK 4 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnssrtk4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnssrtk4_reset_device ( gnssrtk4_t *ctx );

/**
 * @brief GNSS RTK 4 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk4_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSSRTK4_H

/*! @} */ // gnssrtk4

// ------------------------------------------------------------------------ END
