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
 * @file gnss2.h
 * @brief This file contains API for GNSS 2 Click Driver.
 */

#ifndef GNSS2_H
#define GNSS2_H

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
 * @addtogroup gnss2 GNSS 2 Click Driver
 * @brief API for configuring and manipulating GNSS 2 Click driver.
 * @{
 */

/**
 * @defgroup gnss2_cmd GNSS 2 Device Settings
 * @brief Settings for registers of GNSS 2 Click driver.
 */

/**
 * @addtogroup gnss2_cmd
 * @{
 */

/**
 * @brief GNSS 2 response buffer commands.
 * @details Specified response buffer commands of GNSS 2 Click driver.
 */
#define GNSS2_RSP_START                              "$"
#define GNSS2_RSP_DELIMITER                          ","
#define GNSS2_RSP_END_SEQ                            "\r\n"
#define GNSS2_RSP_GPGGA                              "$GPGGA"

/**
 * @brief GNSS 2 GPGGA command elements.
 * @details Specified GPGGA command elements of GNSS 2 Click driver.
 */
#define GNSS2_GPGGA_ELEMENT_SIZE                     15
#define GNSS2_GPGGA_TIME                             1
#define GNSS2_GPGGA_LATITUDE                         2
#define GNSS2_GPGGA_LATITUDE_SIDE                    3
#define GNSS2_GPGGA_LONGITUDE                        4
#define GNSS2_GPGGA_LONGITUDE_SIDE                   5
#define GNSS2_GPGGA_QUALITY_INDICATOR                6
#define GNSS2_GPGGA_NUMBER_OF_SATELLITES             7
#define GNSS2_GPGGA_H_DILUTION_OF_POS                8
#define GNSS2_GPGGA_ALTITUDE                         9
#define GNSS2_GPGGA_ALTITUDE_UNIT                    10
#define GNSS2_GPGGA_GEOIDAL_SEPARATION               11
#define GNSS2_GPGGA_GEOIDAL_SEPARATION_UNIT          12
#define GNSS2_GPGGA_TIME_SINCE_LAST_DGPS             13
#define GNSS2_GPGGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GNSS 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS2_DRV_TX_BUFFER_SIZE                     100
#define GNSS2_DRV_RX_BUFFER_SIZE                     1000

/*! @} */ // gnss2_cmd

/**
 * @defgroup gnss2_map GNSS 2 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 2 Click driver.
 */

/**
 * @addtogroup gnss2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 2 Click to the selected MikroBUS.
 */
#define GNSS2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.fon = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // gnss2_map
/*! @} */ // gnss2
    
/**
 * @brief GNSS 2 Click context object.
 * @details Context object definition of GNSS 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;

    // Input pins
    digital_in_t fon;
    digital_in_t stb;

    // Modules
    uart_t uart;        /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ GNSS2_DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ GNSS2_DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */

} gnss2_t;

/**
 * @brief GNSS 2 Click configuration object.
 * @details Configuration object definition of GNSS 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;
    pin_name_t fon;
    pin_name_t stb;

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} gnss2_cfg_t;

/**
 * @brief GNSS 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS2_OK = 0,
    GNSS2_ERROR = -1

} gnss2_return_value_t;

/*!
 * @addtogroup gnss2 GNSS 2 Click Driver
 * @brief API for configuring and manipulating GNSS 2 Click driver.
 * @{
 */

/**
 * @brief GNSS 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss2_cfg_setup ( gnss2_cfg_t *cfg );

/**
 * @brief GNSS 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss2_init ( gnss2_t *ctx, gnss2_cfg_t *cfg );

/**
 * @brief GNSS 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss2_generic_write ( gnss2_t *ctx, char *data_in, uint16_t len );

/**
 * @brief GNSS 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss2_generic_read ( gnss2_t *ctx, char *data_out, uint16_t len );

/**
 * @brief GNSS 2 clear ring buffers function.
 * @details This function clears UART tx and rx ring buffers.
 * @param[in] ctx : Click context object.
 * See #gnss2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss2_clear_ring_buffers ( gnss2_t *ctx );

/**
 * @brief GNSS 2 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss2_set_rst_pin ( gnss2_t *ctx, uint8_t state );

/**
 * @brief GNSS 2 get FON pin function.
 * @details This function returns the FON pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss2_get_fon_pin ( gnss2_t *ctx );

/**
 * @brief GNSS 2 get STB pin function.
 * @details This function returns the STB pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss2_get_stb_pin ( gnss2_t *ctx );

/**
 * @brief GNSS 2 parse GPGGA function.
 * @details This function parses the GPGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gpgga_element : GPGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss2_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS2_H

/*! @} */ // gnss2

// ------------------------------------------------------------------------ END