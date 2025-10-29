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
 * @file gnss27.h
 * @brief This file contains API for GNSS 27 Click Driver.
 */

#ifndef GNSS27_H
#define GNSS27_H

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
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "drv_uart.h"
#include "spi_specifics.h"

/*!
 * @addtogroup gnss27 GNSS 27 Click Driver
 * @brief API for configuring and manipulating GNSS 27 Click driver.
 * @{
 */

/**
 * @defgroup gnss27_set GNSS 27 Settings
 * @brief Settings of GNSS 27 Click driver.
 */

/**
 * @addtogroup gnss27_set
 * @{
 */

/**
 * @brief GNSS 27 response buffer commands.
 * @details Specified response buffer commands of GNSS 27 Click driver.
 */
#define GNSS27_RSP_START                            "$"
#define GNSS27_RSP_DELIMITER                        ","
#define GNSS27_RSP_END                              "\r\n"
#define GNSS27_RSP_GGA                              "GGA"

/**
 * @brief GNSS 27 dummy data.
 * @details Definition of dummy data.
 */
#define GNSS27_DUMMY                                0xFF
#define GNSS27_IDLE_DATA                            0x0A

/**
 * @brief GNSS 27 GGA command elements.
 * @details Specified GGA command elements of GNSS 27 Click driver.
 */
#define GNSS27_GGA_ELEMENT_SIZE                     15
#define GNSS27_GGA_TIME                             1
#define GNSS27_GGA_LATITUDE                         2
#define GNSS27_GGA_LATITUDE_SIDE                    3
#define GNSS27_GGA_LONGITUDE                        4
#define GNSS27_GGA_LONGITUDE_SIDE                   5
#define GNSS27_GGA_QUALITY_INDICATOR                6
#define GNSS27_GGA_NUMBER_OF_SATELLITES             7
#define GNSS27_GGA_H_DILUTION_OF_POS                8
#define GNSS27_GGA_ALTITUDE                         9
#define GNSS27_GGA_ALTITUDE_UNIT                    10
#define GNSS27_GGA_GEOIDAL_SEPARATION               11
#define GNSS27_GGA_GEOIDAL_SEPARATION_UNIT          12
#define GNSS27_GGA_TIME_SINCE_LAST_DGPS             13
#define GNSS27_GGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GNSS 27 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS27_TX_DRV_BUFFER_SIZE                   100
#define GNSS27_RX_DRV_BUFFER_SIZE                   800

/**
 * @brief GNSS 27 device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS 27 Click driver.
 */
#define GNSS27_DEVICE_ADDRESS                       0x10

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b gnss27_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GNSS27_SET_DATA_SAMPLE_EDGE                 SET_SPI_DATA_SAMPLE_EDGE
#define GNSS27_SET_DATA_SAMPLE_MIDDLE               SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // gnss27_set

/**
 * @defgroup gnss27_map GNSS 27 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 27 Click driver.
 */

/**
 * @addtogroup gnss27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 27 Click to the selected MikroBUS.
 */
#define GNSS27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.aon  = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.fon  = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pps  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gnss27_map
/*! @} */ // gnss27

/**
 * @brief GNSS 27 Click driver selector.
 * @details Selects target driver interface of GNSS 27 Click driver.
 */
typedef enum
{
    GNSS27_DRV_SEL_UART,            /**< UART driver descriptor. */
    GNSS27_DRV_SEL_SPI,             /**< SPI driver descriptor. */
    GNSS27_DRV_SEL_I2C              /**< I2C driver descriptor. */

} gnss27_drv_t;

/**
 * @brief GNSS 27 Click driver interface.
 * @details Definition of driver interface of GNSS 27 Click driver.
 */
struct gnss27_s;
typedef err_t ( *gnss27_master_io_t )( struct gnss27_s*, uint8_t*, uint16_t ); /**< Driver serial interface. */

/**
 * @brief GNSS 27 Click context object.
 * @details Context object definition of GNSS 27 Click driver.
 */
typedef struct gnss27_s
{
    digital_out_t aon;              /**< Antenna enable pin (Active high). */
    digital_out_t rst;              /**< Reset pin (Active low). */
    digital_out_t fon;              /**< Force ON pin (Active high). */

    digital_in_t pps;               /**< Pulse per second pin. */

    uart_t uart;                    /**< UART driver object. */
    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t uart_rx_buffer[ GNSS27_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ GNSS27_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */
    gnss27_drv_t drv_sel;           /**< Master driver interface selector. */

    gnss27_master_io_t write_f;     /**< Master write function. */
    gnss27_master_io_t read_f;      /**< Master read function. */

} gnss27_t;

/**
 * @brief GNSS 27 Click configuration object.
 * @details Configuration object definition of GNSS 27 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                  /**< Chip select pin descriptor for SPI driver. */
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */
    pin_name_t aon;                 /**< Antenna enable pin (Active high). */
    pin_name_t rst;                 /**< Reset pin (Active low). */
    pin_name_t fon;                 /**< Force ON pin (Active high). */
    pin_name_t pps;                 /**< Pulse per second pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    gnss27_drv_t drv_sel;           /**< Master driver interface selector. */

} gnss27_cfg_t;

/**
 * @brief GNSS 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS27_OK = 0,
    GNSS27_ERROR = -1

} gnss27_return_value_t;

/*!
 * @addtogroup gnss27 GNSS 27 Click Driver
 * @brief API for configuring and manipulating GNSS 27 Click driver.
 * @{
 */

/**
 * @brief GNSS 27 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss27_cfg_setup ( gnss27_cfg_t *cfg );

/**
 * @brief GNSS 27 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnss27_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnss27_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnss27_drv_interface_sel ( gnss27_cfg_t *cfg, gnss27_drv_t drv_sel );

/**
 * @brief GNSS 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss27_init ( gnss27_t *ctx, gnss27_cfg_t *cfg );

/**
 * @brief GNSS 27 data writing function.
 * @details This function writes a desired number of data bytes by using the selected serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss27_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss27_generic_write ( gnss27_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 27 data reading function.
 * @details This function reads a desired number of data bytes by using the selected serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss27_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss27_generic_read ( gnss27_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS 27 get PPS pin function.
 * @details This function returns the pulse per second (PPS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss27_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss27_get_pps_pin ( gnss27_t *ctx );

/**
 * @brief GNSS 27 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss27_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss27_set_rst_pin ( gnss27_t *ctx, uint8_t state );

/**
 * @brief GNSS 27 set AON pin function.
 * @details This function sets the antenna enable (AON) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss27_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss27_set_aon_pin ( gnss27_t *ctx, uint8_t state );

/**
 * @brief GNSS 27 set FON pin function.
 * @details This function sets the force enable (FON) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss27_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss27_set_fon_pin ( gnss27_t *ctx, uint8_t state );

/**
 * @brief GNSS 27 reset device function.
 * @details This function resets the device by toggling the RST, AON, and FON pins.
 * @param[in] ctx : Click context object.
 * See #gnss27_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss27_reset_device ( gnss27_t *ctx );

/**
 * @brief GNSS 27 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss27_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS27_H

/*! @} */ // gnss27

// ------------------------------------------------------------------------ END
