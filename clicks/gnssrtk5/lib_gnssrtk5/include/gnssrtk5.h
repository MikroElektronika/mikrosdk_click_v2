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
 * @file gnssrtk5.h
 * @brief This file contains API for GNSS RTK 5 Click Driver.
 */

#ifndef GNSSRTK5_H
#define GNSSRTK5_H

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
 * @addtogroup gnssrtk5 GNSS RTK 5 Click Driver
 * @brief API for configuring and manipulating GNSS RTK 5 Click driver.
 * @{
 */

/**
 * @defgroup gnssrtk5_cmd GNSS RTK 5 Device Settings
 * @brief Settings for registers of GNSS RTK 5 Click driver.
 */

/**
 * @addtogroup gnssrtk5_cmd
 * @{
 */

/**
 * @brief GNSS RTK 5 commands string.
 * @details Specified commands string of GNSS RTK 5 Click driver.
 */
#define GNSSRTK5_CMD_GET_VERSION                    "VERSION"
#define GNSSRTK5_CMD_GET_CONFIG                     "CONFIG"
#define GNSSRTK5_CMD_ENABLE_GGA                     "GNGGA 1"

/**
 * @brief GNSS RTK 5 response buffer commands.
 * @details Specified response buffer commands of GNSS RTK 5 Click driver.
 */
#define GNSSRTK5_RSP_RESET                          "$devicename"
#define GNSSRTK5_RSP_COMMAND                        "$command"
#define GNSSRTK5_RSP_START                          "$"
#define GNSSRTK5_RSP_DELIMITER                      ","
#define GNSSRTK5_RSP_END                            "\r\n"
#define GNSSRTK5_RSP_GGA                            "GGA"

/**
 * @brief GNSS RTK 5 GGA command elements.
 * @details Specified GGA command elements of GNSS RTK 5 Click driver.
 */
#define GNSSRTK5_GGA_ELEMENT_SIZE                   15
#define GNSSRTK5_GGA_TIME                           1
#define GNSSRTK5_GGA_LATITUDE                       2
#define GNSSRTK5_GGA_LATITUDE_SIDE                  3
#define GNSSRTK5_GGA_LONGITUDE                      4
#define GNSSRTK5_GGA_LONGITUDE_SIDE                 5
#define GNSSRTK5_GGA_QUALITY_INDICATOR              6
#define GNSSRTK5_GGA_NUMBER_OF_SATELLITES           7
#define GNSSRTK5_GGA_H_DILUTION_OF_POS              8
#define GNSSRTK5_GGA_ALTITUDE                       9
#define GNSSRTK5_GGA_ALTITUDE_UNIT                  10
#define GNSSRTK5_GGA_GEOIDAL_SEPARATION             11
#define GNSSRTK5_GGA_GEOIDAL_SEPARATION_UNIT        12
#define GNSSRTK5_GGA_TIME_SINCE_LAST_DGPS           13
#define GNSSRTK5_GGA_DGPS_REFERENCE_STATION_ID      14

/**
 * @brief GNSS RTK 5 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSSRTK5_TX_DRV_BUFFER_SIZE                 100
#define GNSSRTK5_RX_DRV_BUFFER_SIZE                 800

/*! @} */ // gnssrtk5_cmd

/**
 * @defgroup gnssrtk5_map GNSS RTK 5 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS RTK 5 Click driver.
 */

/**
 * @addtogroup gnssrtk5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS RTK 5 Click to the selected MikroBUS.
 */
#define GNSSRTK5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.pvt = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.evt = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.err = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnssrtk5_map
/*! @} */ // gnssrtk5

/**
 * @brief GNSS RTK 5 Click context object.
 * @details Context object definition of GNSS RTK 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t evt;              /**< Event pin. */

    // Input pins
    digital_in_t pvt;               /**< Positioning indicator pin (active high). */
    digital_in_t err;               /**< Abnormal indicator pin (active high). */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSSRTK5_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ GNSSRTK5_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ GNSSRTK5_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} gnssrtk5_t;

/**
 * @brief GNSS RTK 5 Click configuration object.
 * @details Configuration object definition of GNSS RTK 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t pvt;                 /**< Positioning indicator pin (active high). */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t evt;                 /**< Event pin. */
    pin_name_t err;                 /**< Abnormal indicator pin (active high). */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} gnssrtk5_cfg_t;

/**
 * @brief GNSS RTK 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSSRTK5_OK = 0,
    GNSSRTK5_ERROR = -1,
    GNSSRTK5_ERROR_TIMEOUT = -2

} gnssrtk5_return_value_t;

/*!
 * @addtogroup gnssrtk5 GNSS RTK 5 Click Driver
 * @brief API for configuring and manipulating GNSS RTK 5 Click driver.
 * @{
 */

/**
 * @brief GNSS RTK 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnssrtk5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnssrtk5_cfg_setup ( gnssrtk5_cfg_t *cfg );

/**
 * @brief GNSS RTK 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnssrtk5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnssrtk5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk5_init ( gnssrtk5_t *ctx, gnssrtk5_cfg_t *cfg );

/**
 * @brief GNSS RTK 5 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssrtk5_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk5_generic_write ( gnssrtk5_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS RTK 5 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssrtk5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk5_generic_read ( gnssrtk5_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS RTK 5 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssrtk5_set_rst_pin ( gnssrtk5_t *ctx, uint8_t state );

/**
 * @brief GNSS RTK 5 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnssrtk5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnssrtk5_reset_device ( gnssrtk5_t *ctx );

/**
 * @brief GNSS RTK 5 set EVT pin function.
 * @details This function sets the EVT pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk5_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssrtk5_set_evt_pin ( gnssrtk5_t *ctx, uint8_t state );

/**
 * @brief GNSS RTK 5 get PVT pin function.
 * @details This function returns the positioning indicator (PVT) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssrtk5_get_pvt_pin ( gnssrtk5_t *ctx );

/**
 * @brief GNSS RTK 5 get ERR pin function.
 * @details This function returns the abnormal indicator (ERR) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssrtk5_get_err_pin ( gnssrtk5_t *ctx );

/**
 * @brief GNSS RTK 5 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk5_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

/**
 * @brief GNSS RTK 5 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #gnssrtk5_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see GNSSRTK5_CMD_x definitions.
 * @return None.
 * @note None.
 */
void gnssrtk5_cmd_run ( gnssrtk5_t *ctx, uint8_t *cmd );

#ifdef __cplusplus
}
#endif
#endif // GNSSRTK5_H

/*! @} */ // gnssrtk5

// ------------------------------------------------------------------------ END
