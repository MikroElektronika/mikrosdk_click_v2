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
 * @file gnssantenna.h
 * @brief This file contains API for GNSS Antenna Board Driver.
 */

#ifndef GNSSANTENNA_H
#define GNSSANTENNA_H

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
 * @addtogroup gnssantenna GNSS Antenna Board Driver
 * @brief API for configuring and manipulating GNSS Antenna Board driver.
 * @{
 */

/**
 * @defgroup gnssantenna_cmd GNSS Antenna Device Settings
 * @brief Settings for registers of GNSS Antenna Board driver.
 */

/**
 * @addtogroup gnssantenna_cmd
 * @{
 */

/**
 * @brief GNSS Antenna response buffer commands.
 * @details Specified response buffer commands of GNSS Antenna Board driver.
 */
#define GNSSANTENNA_RSP_START                               "$"
#define GNSSANTENNA_RSP_DELIMITER                           ","
#define GNSSANTENNA_RSP_END                                 "\r\n"
#define GNSSANTENNA_RSP_GGA                                 "GGA"

/**
 * @brief GNSS Antenna GGA command elements.
 * @details Specified GGA command elements of GNSS Antenna Board driver.
 */
#define GNSSANTENNA_GGA_ELEMENT_SIZE                        15
#define GNSSANTENNA_GGA_TIME                                1
#define GNSSANTENNA_GGA_LATITUDE                            2
#define GNSSANTENNA_GGA_LATITUDE_SIDE                       3
#define GNSSANTENNA_GGA_LONGITUDE                           4
#define GNSSANTENNA_GGA_LONGITUDE_SIDE                      5
#define GNSSANTENNA_GGA_QUALITY_INDICATOR                   6
#define GNSSANTENNA_GGA_NUMBER_OF_SATELLITES                7
#define GNSSANTENNA_GGA_H_DILUTION_OF_POS                   8
#define GNSSANTENNA_GGA_ALTITUDE                            9
#define GNSSANTENNA_GGA_ALTITUDE_UNIT                       10
#define GNSSANTENNA_GGA_GEOIDAL_SEPARATION                  11
#define GNSSANTENNA_GGA_GEOIDAL_SEPARATION_UNIT             12
#define GNSSANTENNA_GGA_TIME_SINCE_LAST_DGPS                13
#define GNSSANTENNA_GGA_DGPS_REFERENCE_STATION_ID           14

/**
 * @brief GNSS Antenna driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSSANTENNA_TX_DRV_BUFFER_SIZE                      100
#define GNSSANTENNA_RX_DRV_BUFFER_SIZE                      1000

/*! @} */ // gnssantenna_cmd

/**
 * @defgroup gnssantenna_map GNSS Antenna MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS Antenna Board driver.
 */

/**
 * @addtogroup gnssantenna_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS Antenna Board to the selected MikroBUS.
 */
#define GNSSANTENNA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.tps = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnssantenna_map
/*! @} */ // gnssantenna

/**
 * @brief GNSS Antenna Board context object.
 * @details Context object definition of GNSS Antenna Board driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (Active high). */

    // Input pins
    digital_in_t tps;               /**< Time pulse signal pin. */
    digital_in_t int_pin;           /**< External interrupt pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSSANTENNA_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ GNSSANTENNA_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

} gnssantenna_t;

/**
 * @brief GNSS Antenna Board configuration object.
 * @details Configuration object definition of GNSS Antenna Board driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (Active high). */
    pin_name_t tps;                 /**< Time pulse signal pin. */
    pin_name_t int_pin;             /**< External interrupt pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} gnssantenna_cfg_t;

/**
 * @brief GNSS Antenna Board return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSSANTENNA_OK = 0,
    GNSSANTENNA_ERROR = -1

} gnssantenna_return_value_t;

/*!
 * @addtogroup gnssantenna GNSS Antenna Board Driver
 * @brief API for configuring and manipulating GNSS Antenna Board driver.
 * @{
 */

/**
 * @brief GNSS Antenna configuration object setup function.
 * @details This function initializes board configuration structure to initial
 * values.
 * @param[out] cfg : Board configuration structure.
 * See #gnssantenna_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnssantenna_cfg_setup ( gnssantenna_cfg_t *cfg );

/**
 * @brief GNSS Antenna initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this board.
 * @param[out] ctx : Board context object.
 * See #gnssantenna_t object definition for detailed explanation.
 * @param[in] cfg : Board configuration structure.
 * See #gnssantenna_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssantenna_init ( gnssantenna_t *ctx, gnssantenna_cfg_t *cfg );

/**
 * @brief GNSS Antenna data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Board context object.
 * See #gnssantenna_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssantenna_generic_write ( gnssantenna_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS Antenna data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Board context object.
 * See #gnssantenna_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssantenna_generic_read ( gnssantenna_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS Antenna get PPS pin function.
 * @details This function returns the time pulse signal (TPS) pin logic state.
 * @param[in] ctx : Board context object.
 * See #gnssantenna_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssantenna_get_tps_pin ( gnssantenna_t *ctx );

/**
 * @brief GNSS Antenna get INT pin function.
 * @details This function returns the external interrupt (INT) pin logic state.
 * @param[in] ctx : Board context object.
 * See #gnssantenna_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssantenna_get_int_pin ( gnssantenna_t *ctx );

/**
 * @brief GNSS Antenna set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Board context object.
 * See #gnssantenna_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssantenna_set_rst_pin ( gnssantenna_t *ctx, uint8_t state );

/**
 * @brief GNSS Antenna reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Board context object.
 * See #gnssantenna_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnssantenna_reset_device ( gnssantenna_t *ctx );

/**
 * @brief GNSS Antenna parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssantenna_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSSANTENNA_H

/*! @} */ // gnssantenna

// ------------------------------------------------------------------------ END
