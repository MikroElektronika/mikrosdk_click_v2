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
 * @file gnss17.h
 * @brief This file contains API for GNSS 17 Click Driver.
 */

#ifndef GNSS17_H
#define GNSS17_H

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
 * @addtogroup gnss17 GNSS 17 Click Driver
 * @brief API for configuring and manipulating GNSS 17 Click driver.
 * @{
 */

/**
 * @defgroup gnss17_cmd GNSS 17 Device Settings
 * @brief Settings for registers of GNSS 17 Click driver.
 */

/**
 * @addtogroup gnss17_cmd
 * @{
 */

/**
 * @brief GNSS 17 response buffer commands.
 * @details Specified response buffer commands of GNSS 17 Click driver.
 */
#define GNSS17_RSP_START                                "$"
#define GNSS17_RSP_DELIMITER                            ","
#define GNSS17_RSP_END                                  "\r\n"
#define GNSS17_RSP_GGA                                  "GGA"

/**
 * @brief GNSS 17 GGA command elements.
 * @details Specified GGA command elements of GNSS 17 Click driver.
 */
#define GNSS17_GGA_ELEMENT_SIZE                         15
#define GNSS17_GGA_TIME                                 1
#define GNSS17_GGA_LATITUDE                             2
#define GNSS17_GGA_LATITUDE_SIDE                        3
#define GNSS17_GGA_LONGITUDE                            4
#define GNSS17_GGA_LONGITUDE_SIDE                       5
#define GNSS17_GGA_QUALITY_INDICATOR                    6
#define GNSS17_GGA_NUMBER_OF_SATELLITES                 7
#define GNSS17_GGA_H_DILUTION_OF_POS                    8
#define GNSS17_GGA_ALTITUDE                             9
#define GNSS17_GGA_ALTITUDE_UNIT                        10
#define GNSS17_GGA_GEOIDAL_SEPARATION                   11
#define GNSS17_GGA_GEOIDAL_SEPARATION_UNIT              12
#define GNSS17_GGA_TIME_SINCE_LAST_DGPS                 13
#define GNSS17_GGA_DGPS_REFERENCE_STATION_ID            14

/**
 * @brief GNSS 17 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS17_TX_DRV_BUFFER_SIZE                       100
#define GNSS17_RX_DRV_BUFFER_SIZE                       1000

/*! @} */ // gnss17_cmd

/**
 * @defgroup gnss17_map GNSS 17 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 17 Click driver.
 */

/**
 * @addtogroup gnss17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 17 Click to the selected MikroBUS.
 */
#define GNSS17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.aon = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rtc = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // gnss17_map
/*! @} */ // gnss17

/**
 * @brief GNSS 17 Click context object.
 * @details Context object definition of GNSS 17 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t aon;      /**< Antenna enable pin (active high). */
    digital_out_t en;       /**< Chip enable pin (active high). */
    digital_out_t rts;      /**< GNSS data EINT, handshaking with host. */
    digital_out_t rtc;      /**< Wake up from RTC mode pin (active high). */

    // Modules
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSS17_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    uint8_t uart_tx_buffer[ GNSS17_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */

} gnss17_t;

/**
 * @brief GNSS 17 Click configuration object.
 * @details Configuration object definition of GNSS 17 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t aon;         /**< Antenna enable pin (active high). */
    pin_name_t en;          /**< Chip enable pin (active high). */
    pin_name_t rts;         /**< GNSS data EINT, handshaking with host. */
    pin_name_t rtc;         /**< Wake up from RTC mode pin (active high). */

    // Static variable
    uint32_t         baud_rate;         /**< Clock speed. */
    bool             uart_blocking;     /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;          /**< Data bits. */
    uart_parity_t    parity_bit;        /**< Parity bit. */
    uart_stop_bits_t stop_bit;          /**< Stop bits. */

} gnss17_cfg_t;

/**
 * @brief GNSS 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS17_OK = 0,
    GNSS17_ERROR = -1

} gnss17_return_value_t;

/*!
 * @addtogroup gnss17 GNSS 17 Click Driver
 * @brief API for configuring and manipulating GNSS 17 Click driver.
 * @{
 */

/**
 * @brief GNSS 17 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss17_cfg_setup ( gnss17_cfg_t *cfg );

/**
 * @brief GNSS 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss17_init ( gnss17_t *ctx, gnss17_cfg_t *cfg );

/**
 * @brief GNSS 17 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss17_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss17_generic_write ( gnss17_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 17 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss17_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss17_generic_read ( gnss17_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS 17 set EN pin function.
 * @details This function sets the EN pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss17_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss17_set_en_pin ( gnss17_t *ctx, uint8_t state );

/**
 * @brief GNSS 17 set AON pin function.
 * @details This function sets the AON pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss17_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss17_set_aon_pin ( gnss17_t *ctx, uint8_t state );

/**
 * @brief GNSS 17 set RTS pin function.
 * @details This function sets the RTS pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss17_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss17_set_rts_pin ( gnss17_t *ctx, uint8_t state );

/**
 * @brief GNSS 17 set RTC pin function.
 * @details This function sets the RTC pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss17_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss17_set_rtc_pin ( gnss17_t *ctx, uint8_t state );

/**
 * @brief GNSS 17 reset device function.
 * @details This function resets the device by toggling the EN and AON pins.
 * @param[in] ctx : Click context object.
 * See #gnss17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss17_reset_device ( gnss17_t *ctx );

/**
 * @brief GNSS 17 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss17_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS17_H

/*! @} */ // gnss17

// ------------------------------------------------------------------------ END
