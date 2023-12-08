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
 * @file gnssrtk2.h
 * @brief This file contains API for GNSS RTK 2 Click Driver.
 */

#ifndef GNSSRTK2_H
#define GNSSRTK2_H

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
 * @addtogroup gnssrtk2 GNSS RTK 2 Click Driver
 * @brief API for configuring and manipulating GNSS RTK 2 Click driver.
 * @{
 */

/**
 * @defgroup gnssrtk2_set GNSS RTK 2 Registers Settings
 * @brief Settings for registers of GNSS RTK 2 Click driver.
 */

/**
 * @addtogroup gnssrtk2_set
 * @{
 */

/**
 * @brief GNSS RTK 2 response buffer commands.
 * @details Specified response buffer commands of GNSS RTK 2 Click driver.
 */
#define GNSSRTK2_RSP_START                              "$"
#define GNSSRTK2_RSP_DELIMITER                          ","
#define GNSSRTK2_RSP_GNGGA                              "$GNGGA"

/**
 * @brief GNSS RTK 2 GNGGA command elements.
 * @details Specified GNGGA command elements of GNSS RTK 2 Click driver.
 */
#define GNSSRTK2_GNGGA_ELEMENT_SIZE                     15
#define GNSSRTK2_GNGGA_TIME                             1
#define GNSSRTK2_GNGGA_LATITUDE                         2
#define GNSSRTK2_GNGGA_LATITUDE_SIDE                    3
#define GNSSRTK2_GNGGA_LONGITUDE                        4
#define GNSSRTK2_GNGGA_LONGITUDE_SIDE                   5
#define GNSSRTK2_GNGGA_QUALITY_INDICATOR                6
#define GNSSRTK2_GNGGA_NUMBER_OF_SATELLITES             7
#define GNSSRTK2_GNGGA_H_DILUTION_OF_POS                8
#define GNSSRTK2_GNGGA_ALTITUDE                         9
#define GNSSRTK2_GNGGA_ALTITUDE_UNIT                    10
#define GNSSRTK2_GNGGA_GEOIDAL_SEPARATION               11
#define GNSSRTK2_GNGGA_GEOIDAL_SEPARATION_UNIT          12
#define GNSSRTK2_GNGGA_TIME_SINCE_LAST_DGPS             13
#define GNSSRTK2_GNGGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GNSS RTK 2 dummy data.
 * @details Definition of dummy data.
 */
#define GNSSRTK2_DUMMY                                  0xFF

/**
 * @brief GNSS RTK 2 device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS RTK 2 Click driver.
 */
#define GNSSRTK2_SET_DEV_ADDR                           0x42

/**
 * @brief GNSS RTK 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define DRV_TX_BUFFER_SIZE                              100
#define DRV_RX_BUFFER_SIZE                              300

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b gnssrtk2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GNSSRTK2_SET_DATA_SAMPLE_EDGE                   SET_SPI_DATA_SAMPLE_EDGE
#define GNSSRTK2_SET_DATA_SAMPLE_MIDDLE                 SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // gnssrtk2_set

/**
 * @defgroup gnssrtk2_map GNSS RTK 2 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS RTK 2 Click driver.
 */

/**
 * @addtogroup gnssrtk2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS RTK 2 Click to the selected MikroBUS.
 */
#define GNSSRTK2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl    = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda    = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso   = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi   = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck    = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs     = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rdy    = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rtk    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.tmp    = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gnssrtk2_map
/*! @} */ // gnssrtk2

/**
 * @brief GNSS RTK 2 Click driver selector.
 * @details Selects target driver interface of GNSS RTK 2 Click driver.
 */
typedef enum
{
    GNSSRTK2_DRV_SEL_UART,      /**< UART driver descriptor. */
    GNSSRTK2_DRV_SEL_SPI,       /**< SPI driver descriptor. */
    GNSSRTK2_DRV_SEL_I2C        /**< I2C driver descriptor. */

} gnssrtk2_drv_t;

/**
 * @brief GNSS RTK 2 Click driver interface.
 * @details Definition of driver interface of GNSS RTK 2 Click driver.
 */
typedef err_t ( *gnssrtk2_master_io_t )( struct gnssrtk2_s*, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief GNSS RTK 2 Click context object.
 * @details Context object definition of GNSS RTK 2 Click driver.
 */
typedef struct gnssrtk2_s
{
    digital_out_t rst;                      /**< Reset pin. */

    digital_in_t  rdy;                      /**< TX ready pin. */
    digital_in_t  rtk;                      /**< RTK stat pin. */
    digital_in_t  tmp;                      /**< Timepulse pin. */

    i2c_master_t  i2c;                      /**< I2C driver object. */
    spi_master_t  spi;                      /**< SPI driver object. */
    uart_t uart;                            /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */

    uint8_t     slave_address;              /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;                /**< Chip select pin descriptor (used for SPI driver). */
    gnssrtk2_drv_t  drv_sel;                /**< Master driver interface selector. */

    gnssrtk2_master_io_t  write_f;          /**< Master write function. */
    gnssrtk2_master_io_t  read_f;           /**< Master read function. */

} gnssrtk2_t;

/**
 * @brief GNSS RTK 2 Click configuration object.
 * @details Configuration object definition of GNSS RTK 2 Click driver.
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
    
    pin_name_t  rdy;                /**< TX ready pin. */
    pin_name_t  rtk;                /**< RTK stat pin. */
    pin_name_t  rst;                /**< Reset pin. */
    pin_name_t  tmp;                /**< Timepulse pin. */

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

    gnssrtk2_drv_t  drv_sel;        /**< Master driver interface selector. */

} gnssrtk2_cfg_t;

/**
 * @brief GNSS RTK 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSSRTK2_OK = 0,
    GNSSRTK2_ERROR = -1

} gnssrtk2_return_value_t;

/*!
 * @addtogroup gnssrtk2 GNSS RTK 2 Click Driver
 * @brief API for configuring and manipulating GNSS RTK 2 Click driver.
 * @{
 */

/**
 * @brief GNSS RTK 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnssrtk2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnssrtk2_cfg_setup ( gnssrtk2_cfg_t *cfg );

/**
 * @brief GNSS RTK 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnssrtk2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnssrtk2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnssrtk2_drv_interface_selection ( gnssrtk2_cfg_t *cfg, gnssrtk2_drv_t drv_sel );

/**
 * @brief GNSS RTK 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gnssrtk2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnssrtk2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk2_init ( gnssrtk2_t *ctx, gnssrtk2_cfg_t *cfg );

/**
 * @brief GNSS RTK 2 data writing function.
 * @details This function writes a desired number of data bytes to the module.
 * @param[in] ctx : Click context object.
 * See #gnssrtk2_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success, or number of data bytes written in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk2_generic_write ( gnssrtk2_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS RTK 2 data reading function.
 * @details This function reads a desired number of data bytes from the module.
 * @param[in] ctx : Click context object.
 * See #gnssrtk2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >=0 - Success, or number of data bytes read in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk2_generic_read ( gnssrtk2_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS RTK 2 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssrtk2_set_rst_pin ( gnssrtk2_t *ctx, uint8_t state );

/**
 * @brief GNSS RTK 2 get RDY pin function.
 * @details This function returns the RDY pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssrtk2_get_rdy_pin ( gnssrtk2_t *ctx );

/**
 * @brief GNSS RTK 2 get RTK pin function.
 * @details This function returns the RTK pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssrtk2_get_rtk_pin ( gnssrtk2_t *ctx );

/**
 * @brief GNSS RTK 2 get TMP pin function.
 * @details This function returns the TMP pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssrtk2_get_tmp_pin ( gnssrtk2_t *ctx );

/**
 * @brief GNSS RTK 2 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnssrtk2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnssrtk2_reset_device ( gnssrtk2_t *ctx );

/**
 * @brief GNSS RTK 2 parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : GNGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk2_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSSRTK2_H

/*! @} */ // gnssrtk2

// ------------------------------------------------------------------------ END
