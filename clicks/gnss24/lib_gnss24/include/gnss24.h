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
 * @file gnss24.h
 * @brief This file contains API for GNSS 24 Click Driver.
 */

#ifndef GNSS24_H
#define GNSS24_H

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
 * @addtogroup gnss24 GNSS 24 Click Driver
 * @brief API for configuring and manipulating GNSS 24 Click driver.
 * @{
 */

/**
 * @defgroup gnss24_cmd GNSS 24 Device Settings
 * @brief Settings of GNSS 24 Click driver.
 */

/**
 * @addtogroup gnss24_cmd
 * @{
 */

/**
 * @brief GNSS 24 commands string.
 * @details Specified commands string of GNSS 24 Click driver.
 */
#define GNSS24_CMD_AUTO_BACKUP_INTERVAL_SET             "@ABPT"
#define GNSS24_CMD_AUTO_BACKUP_SAVE_ON_OFF              "@ABUP"
#define GNSS24_CMD_OUT_SENTENCE_SEL                     "@BSSL"
#define GNSS24_CMD_BACKUP_SAVE                          "@BUP"
#define GNSS24_CMD_BACKUP_CLEAR                         "@BUPC"
#define GNSS24_CMD_UART0_BAUD_RATE_SET                  "@CSBR"
#define GNSS24_CMD_GPS_ALMANAC_ACQ                      "@GALG"
#define GNSS24_CMD_GPS_ALMANAC_INJ                      "@GALS"
#define GNSS24_CMD_COLD_START                           "@GCD"
#define GNSS24_CMD_GPS_EPHEMERIS_ACQ                    "@GEMG"
#define GNSS24_CMD_GPS_EPHEMERIS_INJ                    "@GEMS"
#define GNSS24_CMD_POS_SAT_SET                          "@GNS"
#define GNSS24_CMD_RECEIVER_POS_SET                     "@GPOE"
#define GNSS24_CMD_1PPS_OUT_SET                         "@GPPS"
#define GNSS24_CMD_OP_MODE_SET                          "@GSOP"
#define GNSS24_CMD_HOT_START_POS_ACC                    "@GSP"
#define GNSS24_CMD_HOT_START_TTFF                       "@GSR"
#define GNSS24_CMD_POS_STOP                             "@GSTP"
#define GNSS24_CMD_TIME_SET                             "@GTIM"
#define GNSS24_CMD_GPS_TEST_RES_OUT                     "@GTR"
#define GNSS24_CMD_GPS_TEST_START                       "@GTS"
#define GNSS24_CMD_POS_ALGO_SET                         "@GUSE"
#define GNSS24_CMD_GLONASS_ALMANAC_ACQ                  "@LALG"
#define GNSS24_CMD_GLONASS_ALMANAC_INJ                  "@LALS"
#define GNSS24_CMD_GLONASS_EPHEMERIS_ACQ                "@LEMG"
#define GNSS24_CMD_GLONASS_EPHEMERIS_INJ                "@LEMS"
#define GNSS24_CMD_QZSS_ALMANAC_ACQ                     "@QALG"
#define GNSS24_CMD_QZSS_ALMANAC_INJ                     "@QALS"
#define GNSS24_CMD_QZSS_EPHEMERIS_ACQ                   "@QEMG"
#define GNSS24_CMD_QZSS_EPHEMERIS_INJ                   "@QEMS"
#define GNSS24_CMD_SLEEP                                "@SLP"
#define GNSS24_CMD_FW_REV_NUM_ACQ                       "@VER"
#define GNSS24_CMD_WAKE_UP                              "@WUP"
#define GNSS24_CMD_AEP_FUNCTION_CTRL                    "@AEPS"
#define GNSS24_CMD_AEP_GEN_STAT_ACQ                     "@AEPG"

/**
 * @brief GNSS 24 response buffer commands.
 * @details Specified response buffer commands of GNSS 24 Click driver.
 */
#define GNSS24_RSP_DONE                                 "Done"
#define GNSS24_RSP_START                                "$"
#define GNSS24_RSP_DELIMITER                            ","
#define GNSS24_RSP_END                                  "\r\n"
#define GNSS24_RSP_GGA                                  "GGA"

/**
 * @brief GNSS 24 GGA command elements.
 * @details Specified GGA command elements of GNSS 24 Click driver.
 */
#define GNSS24_GGA_ELEMENT_SIZE                         15
#define GNSS24_GGA_TIME                                 1
#define GNSS24_GGA_LATITUDE                             2
#define GNSS24_GGA_LATITUDE_SIDE                        3
#define GNSS24_GGA_LONGITUDE                            4
#define GNSS24_GGA_LONGITUDE_SIDE                       5
#define GNSS24_GGA_QUALITY_INDICATOR                    6
#define GNSS24_GGA_NUMBER_OF_SATELLITES                 7
#define GNSS24_GGA_H_DILUTION_OF_POS                    8
#define GNSS24_GGA_ALTITUDE                             9
#define GNSS24_GGA_ALTITUDE_UNIT                        10
#define GNSS24_GGA_GEOIDAL_SEPARATION                   11
#define GNSS24_GGA_GEOIDAL_SEPARATION_UNIT              12
#define GNSS24_GGA_TIME_SINCE_LAST_DGPS                 13
#define GNSS24_GGA_DGPS_REFERENCE_STATION_ID            14

/**
 * @brief GNSS 24 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS24_TX_DRV_BUFFER_SIZE                       100
#define GNSS24_RX_DRV_BUFFER_SIZE                       1000

/*! @} */ // gnss24_cmd

/**
 * @defgroup gnss24_map GNSS 24 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 24 Click driver.
 */

/**
 * @addtogroup gnss24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 24 Click to the selected MikroBUS.
 */
#define GNSS24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnss24_map
/*! @} */ // gnss24

/**
 * @brief GNSS 24 Click context object.
 * @details Context object definition of GNSS 24 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (active low). */

    // Input pins
    digital_in_t irq;               /**< Interrupt pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSS24_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ GNSS24_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    uint8_t cmd_buffer[ GNSS24_TX_DRV_BUFFER_SIZE ];      /**< Command buffer. */

} gnss24_t;

/**
 * @brief GNSS 24 Click configuration object.
 * @details Configuration object definition of GNSS 24 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t irq;                 /**< Interrupt pin. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

} gnss24_cfg_t;

/**
 * @brief GNSS 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS24_OK = 0,
    GNSS24_ERROR = -1,
    GNSS24_ERROR_TIMEOUT = -2

} gnss24_return_value_t;

/*!
 * @addtogroup gnss24 GNSS 24 Click Driver
 * @brief API for configuring and manipulating GNSS 24 Click driver.
 * @{
 */

/**
 * @brief GNSS 24 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss24_cfg_setup ( gnss24_cfg_t *cfg );

/**
 * @brief GNSS 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss24_init ( gnss24_t *ctx, gnss24_cfg_t *cfg );

/**
 * @brief GNSS 24 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss24_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss24_generic_write ( gnss24_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 24 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss24_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss24_generic_read ( gnss24_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS 24 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss24_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss24_set_rst_pin ( gnss24_t *ctx, uint8_t state );

/**
 * @brief GNSS 24 set IRQ pin function.
 * @details This function returns the IRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss24_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss24_get_irq_pin ( gnss24_t *ctx );

/**
 * @brief GNSS 24 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnss24_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss24_reset_device ( gnss24_t *ctx );

/**
 * @brief GNSS 24 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss24_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

/**
 * @brief GNSS 24 cmd run function.
 * @details This function sends a specified command to the Click module.
 * @param[in] ctx : Click context object.
 * See #gnss24_t object definition for detailed explanation.
 * @param[in] cmd : Command string, see GNSS24_CMD_x definitions.
 * @return None.
 * @note None.
 */
void gnss24_cmd_run ( gnss24_t *ctx, uint8_t *cmd );

/**
 * @brief GNSS 24 cmd set function.
 * @details This function sets a value to a specified command of the Click module.
 * @param[in] ctx : Click context object.
 * See #gnss24_t object definition for detailed explanation.
 * @param[in] cmd : Command string.
 * @param[in] param : Parameters string.
 * @return None.
 * @note None.
 */
void gnss24_cmd_set ( gnss24_t *ctx, uint8_t *cmd, uint8_t *param );

#ifdef __cplusplus
}
#endif
#endif // GNSS24_H

/*! @} */ // gnss24

// ------------------------------------------------------------------------ END
