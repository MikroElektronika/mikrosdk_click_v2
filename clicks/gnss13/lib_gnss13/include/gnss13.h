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
 * @file gnss13.h
 * @brief This file contains API for GNSS 13 Click Driver.
 */

#ifndef GNSS13_H
#define GNSS13_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup gnss13 GNSS 13 Click Driver
 * @brief API for configuring and manipulating GNSS 13 Click driver.
 * @{
 */

/**
 * @defgroup gnss13_cmd GNSS 13 Device Settings
 * @brief Settings for registers of GNSS 13 Click driver.
 */

/**
 * @addtogroup gnss13_cmd
 * @{
 */

/**
 * @brief GNSS 13 response buffer commands.
 * @details Specified response buffer commands of GNSS 13 Click driver.
 */
#define GNSS13_RSP_START                            "$"
#define GNSS13_RSP_DELIMITER                        ","
#define GNSS13_RSP_END_SEQ                          "\r\n"
#define GNSS13_RSP_GNGGA                            "$GNGGA"

/**
 * @brief GNSS 13 GNGGA command elements.
 * @details Specified GNGGA command elements of GNSS 13 Click driver.
 */
#define GNSS13_GNGGA_ELEMENT_SIZE                   15
#define GNSS13_GNGGA_TIME                           1
#define GNSS13_GNGGA_LATITUDE                       2
#define GNSS13_GNGGA_LATITUDE_SIDE                  3
#define GNSS13_GNGGA_LONGITUDE                      4
#define GNSS13_GNGGA_LONGITUDE_SIDE                 5
#define GNSS13_GNGGA_QUALITY_INDICATOR              6
#define GNSS13_GNGGA_NUMBER_OF_SATELLITES           7
#define GNSS13_GNGGA_H_DILUTION_OF_POS              8
#define GNSS13_GNGGA_ALTITUDE                       9
#define GNSS13_GNGGA_ALTITUDE_UNIT                  10
#define GNSS13_GNGGA_GEOIDAL_SEPARATION             11
#define GNSS13_GNGGA_GEOIDAL_SEPARATION_UNIT        12
#define GNSS13_GNGGA_TIME_SINCE_LAST_DGPS           13
#define GNSS13_GNGGA_DGPS_REFERENCE_STATION_ID      14

/**
 * @brief GNSS 13 device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS 13 Click driver.
 */
#define GNSS13_DEVICE_ADDRESS                       0x10

/**
 * @brief GNSS 13 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS13_DRV_TX_BUFFER_SIZE                   100
#define GNSS13_DRV_RX_BUFFER_SIZE                   1200

/*! @} */ // gnss13_cmd

/**
 * @defgroup gnss13_map GNSS 13 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 13 Click driver.
 */

/**
 * @addtogroup gnss13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 13 Click to the selected MikroBUS.
 */
#define GNSS13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // gnss13_map
/*! @} */ // gnss13

/**
 * @brief GNSS 13 Click driver selector.
 * @details Selects target driver interface of GNSS 13 Click driver.
 */
typedef enum
{
    GNSS13_DRV_SEL_UART,        /**< UART driver descriptor. */
    GNSS13_DRV_SEL_I2C          /**< I2C driver descriptor. */

} gnss13_drv_t;

/**
 * @brief GNSS 13 Click driver interface.
 * @details Definition of driver interface of GNSS 13 Click driver.
 */
typedef err_t ( *gnss13_master_io_t )( struct gnss13_s*, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief GNSS 13 Click context object.
 * @details Context object definition of GNSS 13 Click driver.
 */
typedef struct gnss13_s
{
    // Output pins
    digital_out_t rst;          /**< Reset pin (Active low). */
    digital_out_t wup;          /**< Wake up pin (Active high). */

    // Modules
    uart_t uart;                /**< UART driver object. */
    i2c_master_t i2c;           /**< I2C driver object. */

    // Buffers
    char uart_rx_buffer[ GNSS13_DRV_RX_BUFFER_SIZE ];   /**< Buffer size. */
    char uart_tx_buffer[ GNSS13_DRV_TX_BUFFER_SIZE ];   /**< Buffer size. */
    
    uint8_t      slave_address; /**< Device slave address (used for I2C driver). */
    gnss13_drv_t drv_sel;       /**< Master driver interface selector. */

    gnss13_master_io_t write_f; /**< Master write function. */
    gnss13_master_io_t read_f;  /**< Master read function. */

} gnss13_t;

/**
 * @brief GNSS 13 Click configuration object.
 * @details Configuration object definition of GNSS 13 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rx_pin;          /**< RX pin. */
    pin_name_t tx_pin;          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;             /**< Reset pin (Active low). */
    pin_name_t wup;             /**< Wake up pin (Active high). */

    // Static variable
    uint32_t          baud_rate;        /**< Clock speed. */
    bool              uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t  data_bit;         /**< Data bits. */
    uart_parity_t     parity_bit;       /**< Parity bit. */
    uart_stop_bits_t  stop_bit;         /**< Stop bits. */
    
    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */
    
    gnss13_drv_t drv_sel;       /**< Master driver interface selector. */

} gnss13_cfg_t;

/**
 * @brief GNSS 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS13_OK = 0,
    GNSS13_ERROR = -1

} gnss13_return_value_t;

/*!
 * @addtogroup gnss13 GNSS 13 Click Driver
 * @brief API for configuring and manipulating GNSS 13 Click driver.
 * @{
 */

/**
 * @brief GNSS 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss13_cfg_setup ( gnss13_cfg_t *cfg );

/**
 * @brief GNSS 13 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnss13_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnss13_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnss13_drv_interface_selection ( gnss13_cfg_t *cfg, gnss13_drv_t drv_sel );

/**
 * @brief GNSS 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gnss13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss13_init ( gnss13_t *ctx, gnss13_cfg_t *cfg );

/**
 * @brief GNSS 13 generic write function.
 * @details This function writes a desired number of data bytes to the module.
 * @param[in] ctx : Click context object.
 * See #gnss13_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c >=0 - Number of data bytes written,
 *         @li @c  -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss13_generic_write ( gnss13_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 13 generic read function.
 * @details This function reads a desired number of data bytes from the module.
 * @param[in] ctx : Click context object.
 * See #gnss13_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c >=0 - Number of data bytes read,
 *         @li @c  -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss13_generic_read ( gnss13_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS 13 clear ring buffers function.
 * @details This function clears UART tx and rx ring buffers.
 * @param[in] ctx : Click context object.
 * See #gnss13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss13_clear_ring_buffers ( gnss13_t *ctx );

/**
 * @brief GNSS 13 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss13_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss13_set_rst_pin ( gnss13_t *ctx, uint8_t state );

/**
 * @brief GNSS 13 set WUP pin function.
 * @details This function sets the WUP pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss13_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss13_set_wup_pin ( gnss13_t *ctx, uint8_t state );

/**
 * @brief GNSS 13 parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : GNGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss13_parse_gngga ( uint8_t *rsp_buf, uint8_t gngga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS13_H

/*! @} */ // gnss13

// ------------------------------------------------------------------------ END
