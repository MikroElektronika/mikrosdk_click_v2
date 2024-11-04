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
 * @file gnss7.h
 * @brief This file contains API for GNSS 7 Click Driver.
 */

#ifndef GNSS7_H
#define GNSS7_H

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
 * @addtogroup gnss7 GNSS 7 Click Driver
 * @brief API for configuring and manipulating GNSS 7 Click driver.
 * @{
 */

/**
 * @defgroup gnss7_cmd GNSS 7 Device Settings
 * @brief Settings for registers of GNSS 7 Click driver.
 */

/**
 * @addtogroup gnss7_cmd
 * @{
 */

/**
 * @brief GNSS 7 response buffer commands.
 * @details Specified response buffer commands of GNSS 7 Click driver.
 */
#define GNSS7_RSP_START                              "$"
#define GNSS7_RSP_DELIMITER                          ","
#define GNSS7_RSP_END_SEQ                            "\r\n"
#define GNSS7_RSP_GNGGA                              "$GNGGA"

/**
 * @brief GNSS 7 GNGGA command elements.
 * @details Specified GNGGA command elements of GNSS 7 Click driver.
 */
#define GNSS7_GNGGA_ELEMENT_SIZE                     15
#define GNSS7_GNGGA_TIME                             1
#define GNSS7_GNGGA_LATITUDE                         2
#define GNSS7_GNGGA_LATITUDE_SIDE                    3
#define GNSS7_GNGGA_LONGITUDE                        4
#define GNSS7_GNGGA_LONGITUDE_SIDE                   5
#define GNSS7_GNGGA_QUALITY_INDICATOR                6
#define GNSS7_GNGGA_NUMBER_OF_SATELLITES             7
#define GNSS7_GNGGA_H_DILUTION_OF_POS                8
#define GNSS7_GNGGA_ALTITUDE                         9
#define GNSS7_GNGGA_ALTITUDE_UNIT                    10
#define GNSS7_GNGGA_GEOIDAL_SEPARATION               11
#define GNSS7_GNGGA_GEOIDAL_SEPARATION_UNIT          12
#define GNSS7_GNGGA_TIME_SINCE_LAST_DGPS             13
#define GNSS7_GNGGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GNSS 7 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS7_DRV_TX_BUFFER_SIZE                     100
#define GNSS7_DRV_RX_BUFFER_SIZE                     1000

/*! @} */ // gnss7_cmd

/**
 * @defgroup gnss7_map GNSS 7 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 7 Click driver.
 */

/**
 * @addtogroup gnss7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 7 Click to the selected MikroBUS.
 */
#define GNSS7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.sel = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.exi = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pls = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gnss7_map
/*! @} */ // gnss7
    
/**
 * @brief GNSS 7 Click context object.
 * @details Context object definition of GNSS 7 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t sel;
    digital_out_t rst;

    // Input pins
    digital_in_t exi;
    digital_in_t pls;

    // Modules
    uart_t uart;        /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ GNSS7_DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ GNSS7_DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */

} gnss7_t;

/**
 * @brief GNSS 7 Click configuration object.
 * @details Configuration object definition of GNSS 7 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;                  /**< RX pin. */
    pin_name_t tx_pin;                  /**< TX pin. */

    // Additional gpio pins
    pin_name_t sel;
    pin_name_t rst;
    pin_name_t exi;
    pin_name_t pls;

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */

} gnss7_cfg_t;

/**
 * @brief GNSS 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS7_OK = 0,
    GNSS7_ERROR = -1

} gnss7_return_value_t;

/*!
 * @addtogroup gnss7 GNSS 7 Click Driver
 * @brief API for configuring and manipulating GNSS 7 Click driver.
 * @{
 */

/**
 * @brief GNSS 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss7_cfg_setup ( gnss7_cfg_t *cfg );

/**
 * @brief GNSS 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss7_init ( gnss7_t *ctx, gnss7_cfg_t *cfg );

/**
 * @brief GNSS 7 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss7_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss7_generic_write ( gnss7_t *ctx, char *data_in, uint16_t len );

/**
 * @brief GNSS 7 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss7_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss7_generic_read ( gnss7_t *ctx, char *data_out, uint16_t len );

/**
 * @brief GNSS 7 clear ring buffers function.
 * @details This function clears UART tx and rx ring buffers.
 * @param[in] ctx : Click context object.
 * See #gnss7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss7_clear_ring_buffers ( gnss7_t *ctx );

/**
 * @brief GNSS 7 set SEL pin function.
 * @details This function sets the SEL pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss7_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss7_set_sel_pin ( gnss7_t *ctx, uint8_t state );

/**
 * @brief GNSS 7 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss7_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss7_set_rst_pin ( gnss7_t *ctx, uint8_t state );

/**
 * @brief GNSS 7 get EXI pin function.
 * @details This function returns the EXI pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss7_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss7_get_exi_pin ( gnss7_t *ctx );

/**
 * @brief GNSS 7 get PLS pin function.
 * @details This function returns the PLS pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss7_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss7_get_pls_pin ( gnss7_t *ctx );

/**
 * @brief GNSS 7 parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : GNGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss7_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS7_H

/*! @} */ // gnss7

// ------------------------------------------------------------------------ END