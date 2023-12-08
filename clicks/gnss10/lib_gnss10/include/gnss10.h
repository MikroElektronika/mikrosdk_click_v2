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
 * @file gnss10.h
 * @brief This file contains API for GNSS 10 Click Driver.
 */

#ifndef GNSS10_H
#define GNSS10_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "drv_uart.h"
#include "spi_specifics.h"

/*!
 * @addtogroup gnss10 GNSS 10 Click Driver
 * @brief API for configuring and manipulating GNSS 10 Click driver.
 * @{
 */

/**
 * @defgroup gnss10_set GNSS 10 Registers Settings
 * @brief Settings for registers of GNSS 10 Click driver.
 */

/**
 * @addtogroup gnss10_set
 * @{
 */

/**
 * @brief GNSS 10 response buffer commands.
 * @details Specified response buffer commands of GNSS 10 Click driver.
 */
#define GNSS10_RSP_START                                "$"
#define GNSS10_RSP_DELIMITER                            ","
#define GNSS10_RSP_GNGGA                                "$GNGGA"

/**
 * @brief GNSS 10 GNGGA command elements.
 * @details Specified GNGGA command elements of GNSS 10 Click driver.
 */
#define GNSS10_GNGGA_ELEMENT_SIZE                       15
#define GNSS10_GNGGA_TIME                               1
#define GNSS10_GNGGA_LATITUDE                           2
#define GNSS10_GNGGA_LATITUDE_SIDE                      3
#define GNSS10_GNGGA_LONGITUDE                          4
#define GNSS10_GNGGA_LONGITUDE_SIDE                     5
#define GNSS10_GNGGA_QUALITY_INDICATOR                  6
#define GNSS10_GNGGA_NUMBER_OF_SATELLITES               7
#define GNSS10_GNGGA_H_DILUTION_OF_POS                  8
#define GNSS10_GNGGA_ALTITUDE                           9
#define GNSS10_GNGGA_ALTITUDE_UNIT                      10
#define GNSS10_GNGGA_GEOIDAL_SEPARATION                 11
#define GNSS10_GNGGA_GEOIDAL_SEPARATION_UNIT            12
#define GNSS10_GNGGA_TIME_SINCE_LAST_DGPS               13
#define GNSS10_GNGGA_DGPS_REFERENCE_STATION_ID          14

/**
 * @brief GNSS 10 dummy data.
 * @details Definition of dummy data.
 */
#define GNSS10_DUMMY                                    0xFF

/**
 * @brief GNSS 10 device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS 10 Click driver.
 */
#define GNSS10_SET_DEV_ADDR                             0x42

/**
 * @brief GNSS 10 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_BUFFER_SIZE                                 200

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b gnss10_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GNSS10_SET_DATA_SAMPLE_EDGE                     SET_SPI_DATA_SAMPLE_EDGE
#define GNSS10_SET_DATA_SAMPLE_MIDDLE                   SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // gnss10_set

/**
 * @defgroup gnss10_map GNSS 10 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 10 Click driver.
 */

/**
 * @addtogroup gnss10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 10 Click to the selected MikroBUS.
 */
#define GNSS10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.eint_1  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gnss10_map
/*! @} */ // gnss10

/**
 * @brief GNSS 10 Click driver selector.
 * @details Selects target driver interface of GNSS 10 Click driver.
 */
typedef enum
{
    GNSS10_DRV_SEL_UART,     /**< UART driver descriptor. */
    GNSS10_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    GNSS10_DRV_SEL_I2C       /**< I2C driver descriptor. */

} gnss10_drv_t;

/**
 * @brief GNSS 10 Click driver interface.
 * @details Definition of driver interface of GNSS 10 Click driver.
 */
typedef err_t ( *gnss10_master_io_t )( struct gnss10_s*, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief GNSS 10 Click context object.
 * @details Context object definition of GNSS 10 Click driver.
 */
typedef struct gnss10_s
{
    digital_out_t  rst;                     /**< Reset pin. */

    digital_in_t   eint_1;                  /**< Ext INT 1 pin. */
    digital_in_t   int_pin;                 /**< Ext INT pin. */

    i2c_master_t  i2c;                      /**< I2C driver object. */
    spi_master_t  spi;                      /**< SPI driver object. */
    uart_t uart;                            /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_BUFFER_SIZE ]; /**< Buffer size. */
    char uart_tx_buffer[ DRV_BUFFER_SIZE ]; /**< Buffer size. */

    uint8_t     slave_address;              /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;                /**< Chip select pin descriptor (used for SPI driver). */
    gnss10_drv_t  drv_sel;                  /**< Master driver interface selector. */

    gnss10_master_io_t  write_f;            /**< Master write function. */
    gnss10_master_io_t  read_f;             /**< Master read function. */

} gnss10_t;

/**
 * @brief GNSS 10 Click configuration object.
 * @details Configuration object definition of GNSS 10 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;               /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;               /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;                /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;                 /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  rx_pin;             /**< RX pin. */
    pin_name_t  tx_pin;             /**< TX pin. */
    pin_name_t  eint_1;             /**< Ext INT 1 pin. */
    pin_name_t  rst;                /**< Reset pin. */
    pin_name_t  int_pin;            /**< Ext INT pin. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address;          /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */
    
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

    gnss10_drv_t  drv_sel;          /**< Master driver interface selector. */

} gnss10_cfg_t;

/**
 * @brief GNSS 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS10_OK = 0,
    GNSS10_ERROR = -1

} gnss10_return_value_t;

/*!
 * @addtogroup gnss10 GNSS 10 Click Driver
 * @brief API for configuring and manipulating GNSS 10 Click driver.
 * @{
 */

/**
 * @brief GNSS 10 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss10_cfg_setup ( gnss10_cfg_t *cfg );

/**
 * @brief GNSS 10 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnss10_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnss10_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnss10_drv_interface_selection ( gnss10_cfg_t *cfg, gnss10_drv_t drv_sel );

/**
 * @brief GNSS 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gnss10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss10_init ( gnss10_t *ctx, gnss10_cfg_t *cfg );

/**
 * @brief GNSS 10 data writing function.
 * @details This function writes a desired number of data bytes to the module.
 * @param[in] ctx : Click context object.
 * See #gnss10_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success, or number of data bytes written in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss10_generic_write ( gnss10_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 10 data reading function.
 * @details This function reads a desired number of data bytes from the module.
 * @param[in] ctx : Click context object.
 * See #gnss10_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >=0 - Success, or number of data bytes read in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss10_generic_read ( gnss10_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS 10 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss10_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss10_set_rst_pin ( gnss10_t *ctx, uint8_t state );

/**
 * @brief GNSS 10 get Ext INT 1 pin function.
 * @details This function returns the Ext INT 1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss10_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss10_get_eint_1_pin ( gnss10_t *ctx );

/**
 * @brief GNSS 10 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss10_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss10_get_int_pin ( gnss10_t *ctx );

/**
 * @brief GNSS 10 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnss10_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss10_reset_device ( gnss10_t *ctx );

/**
 * @brief GNSS 10 parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : GNGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss10_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS10_H

/*! @} */ // gnss10

// ------------------------------------------------------------------------ END
