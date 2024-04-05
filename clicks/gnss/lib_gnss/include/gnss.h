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
 * @file gnss.h
 * @brief This file contains API for GNSS Click Driver.
 */

#ifndef GNSS_H
#define GNSS_H

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
 * @addtogroup gnss GNSS Click Driver
 * @brief API for configuring and manipulating GNSS Click driver.
 * @{
 */

/**
 * @defgroup gnss_cmd GNSS Device Settings
 * @brief Settings for registers of GNSS Click driver.
 */

/**
 * @addtogroup gnss_cmd
 * @{
 */

/**
 * @brief GNSS response buffer commands.
 * @details Specified response buffer commands of GNSS Click driver.
 */
#define GNSS_RSP_START                              "$"
#define GNSS_RSP_DELIMITER                          ","
#define GNSS_RSP_END_SEQ                            "\r\n"
#define GNSS_RSP_GPGGA                              "$GPGGA"

/**
 * @brief GNSS GPGGA command elements.
 * @details Specified GPGGA command elements of GNSS Click driver.
 */
#define GNSS_GPGGA_ELEMENT_SIZE                     15
#define GNSS_GPGGA_TIME                             1
#define GNSS_GPGGA_LATITUDE                         2
#define GNSS_GPGGA_LATITUDE_SIDE                    3
#define GNSS_GPGGA_LONGITUDE                        4
#define GNSS_GPGGA_LONGITUDE_SIDE                   5
#define GNSS_GPGGA_QUALITY_INDICATOR                6
#define GNSS_GPGGA_NUMBER_OF_SATELLITES             7
#define GNSS_GPGGA_H_DILUTION_OF_POS                8
#define GNSS_GPGGA_ALTITUDE                         9
#define GNSS_GPGGA_ALTITUDE_UNIT                    10
#define GNSS_GPGGA_GEOIDAL_SEPARATION               11
#define GNSS_GPGGA_GEOIDAL_SEPARATION_UNIT          12
#define GNSS_GPGGA_TIME_SINCE_LAST_DGPS             13
#define GNSS_GPGGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GNSS driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS_DRV_TX_BUFFER_SIZE                     100
#define GNSS_DRV_RX_BUFFER_SIZE                     1000

/*! @} */ // gnss_cmd

/**
 * @defgroup gnss_map GNSS MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS Click driver.
 */

/**
 * @addtogroup gnss_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS Click to the selected MikroBUS.
 */
#define GNSS_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.fon = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // gnss_map
/*! @} */ // gnss
    
/**
 * @brief GNSS Click context object.
 * @details Context object definition of GNSS Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;
    digital_out_t fon;

    // Modules
    uart_t uart;        /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ GNSS_DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ GNSS_DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */

} gnss_t;

/**
 * @brief GNSS Click configuration object.
 * @details Configuration object definition of GNSS Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;
    pin_name_t fon;

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} gnss_cfg_t;

/**
 * @brief GNSS Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS_OK = 0,
    GNSS_ERROR = -1

} gnss_return_value_t;

/*!
 * @addtogroup gnss GNSS Click Driver
 * @brief API for configuring and manipulating GNSS Click driver.
 * @{
 */

/**
 * @brief GNSS configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss_cfg_setup ( gnss_cfg_t *cfg );

/**
 * @brief GNSS initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gnss_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss_init ( gnss_t *ctx, gnss_cfg_t *cfg );

/**
 * @brief GNSS data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss_generic_write ( gnss_t *ctx, char *data_in, uint16_t len );

/**
 * @brief GNSS data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss_generic_read ( gnss_t *ctx, char *data_out, uint16_t len );

/**
 * @brief GNSS clear ring buffers function.
 * @details This function clears UART tx and rx ring buffers.
 * @param[in] ctx : Click context object.
 * See #gnss_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss_clear_ring_buffers ( gnss_t *ctx );

/**
 * @brief GNSS set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss_set_rst_pin ( gnss_t *ctx, uint8_t state );

/**
 * @brief GNSS set FON pin function.
 * @details This function sets the FON pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss_set_fon_pin ( gnss_t *ctx, uint8_t state );

/**
 * @brief GNSS parse GPGGA function.
 * @details This function parses the GPGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gpgga_element : GPGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS_H

/*! @} */ // gnss

// ------------------------------------------------------------------------ END