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
 * @file gnsszoe.h
 * @brief This file contains API for GNSS ZOE Click Driver.
 */

#ifndef GNSSZOE_H
#define GNSSZOE_H

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
 * @addtogroup gnsszoe GNSS ZOE Click Driver
 * @brief API for configuring and manipulating GNSS ZOE Click driver.
 * @{
 */

/**
 * @defgroup gnsszoe_set GNSS ZOE Registers Settings
 * @brief Settings for registers of GNSS ZOE Click driver.
 */

/**
 * @addtogroup gnsszoe_set
 * @{
 */

/**
 * @brief GNSS ZOE response buffer commands.
 * @details Specified response buffer commands of GNSS ZOE Click driver.
 */
#define GNSSZOE_RSP_START                               "$"
#define GNSSZOE_RSP_DELIMITER                           ","
#define GNSSZOE_RSP_GNGGA                               "$GNGGA"

/**
 * @brief GNSS ZOE GNGGA command elements.
 * @details Specified GNGGA command elements of GNSS ZOE Click driver.
 */
#define GNSSZOE_GNGGA_ELEMENT_SIZE                      15
#define GNSSZOE_GNGGA_TIME                              1
#define GNSSZOE_GNGGA_LATITUDE                          2
#define GNSSZOE_GNGGA_LATITUDE_SIDE                     3
#define GNSSZOE_GNGGA_LONGITUDE                         4
#define GNSSZOE_GNGGA_LONGITUDE_SIDE                    5
#define GNSSZOE_GNGGA_QUALITY_INDICATOR                 6
#define GNSSZOE_GNGGA_NUMBER_OF_SATELLITES              7
#define GNSSZOE_GNGGA_H_DILUTION_OF_POS                 8
#define GNSSZOE_GNGGA_ALTITUDE                          9
#define GNSSZOE_GNGGA_ALTITUDE_UNIT                     10
#define GNSSZOE_GNGGA_GEOIDAL_SEPARATION                11
#define GNSSZOE_GNGGA_GEOIDAL_SEPARATION_UNIT           12
#define GNSSZOE_GNGGA_TIME_SINCE_LAST_DGPS              13
#define GNSSZOE_GNGGA_DGPS_REFERENCE_STATION_ID         14

/**
 * @brief GNSS ZOE dummy data.
 * @details Definition of dummy data.
 */
#define GNSSZOE_DUMMY                                   0xFF

/**
 * @brief GNSS ZOE device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS ZOE Click driver.
 */
#define GNSSZOE_SET_DEV_ADDR                            0x42

/**
 * @brief GNSS ZOE driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSSZOE_DRV_TX_BUFFER_SIZE                      100
#define GNSSZOE_DRV_RX_BUFFER_SIZE                      600

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b gnsszoe_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GNSSZOE_SET_DATA_SAMPLE_EDGE                    SET_SPI_DATA_SAMPLE_EDGE
#define GNSSZOE_SET_DATA_SAMPLE_MIDDLE                  SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // gnsszoe_set

/**
 * @defgroup gnsszoe_map GNSS ZOE MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS ZOE Click driver.
 */

/**
 * @addtogroup gnsszoe_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS ZOE Click to the selected MikroBUS.
 */
#define GNSSZOE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl    = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda    = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso   = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi   = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck    = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs     = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.exi    = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_RST )

/*! @} */ // gnsszoe_map
/*! @} */ // gnsszoe

/**
 * @brief GNSS ZOE Click driver selector.
 * @details Selects target driver interface of GNSS ZOE Click driver.
 */
typedef enum
{
    GNSSZOE_DRV_SEL_UART,      /**< UART driver descriptor. */
    GNSSZOE_DRV_SEL_SPI,       /**< SPI driver descriptor. */
    GNSSZOE_DRV_SEL_I2C        /**< I2C driver descriptor. */

} gnsszoe_drv_t;

/**
 * @brief GNSS ZOE Click driver interface.
 * @details Definition of driver interface of GNSS ZOE Click driver.
 */
typedef err_t ( *gnsszoe_master_io_t )( struct gnsszoe_s*, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief GNSS ZOE Click context object.
 * @details Context object definition of GNSS ZOE Click driver.
 */
typedef struct gnsszoe_s
{
    digital_out_t rst;                      /**< Reset pin. */

    digital_in_t  exi;                      /**< EXI pin. */

    i2c_master_t  i2c;                      /**< I2C driver object. */
    spi_master_t  spi;                      /**< SPI driver object. */
    uart_t uart;                            /**< UART driver object. */

    // Buffers
    char uart_rx_buffer[ GNSSZOE_DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    char uart_tx_buffer[ GNSSZOE_DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */

    uint8_t     slave_address;              /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;                /**< Chip select pin descriptor (used for SPI driver). */
    gnsszoe_drv_t  drv_sel;                /**< Master driver interface selector. */

    gnsszoe_master_io_t  write_f;          /**< Master write function. */
    gnsszoe_master_io_t  read_f;           /**< Master read function. */

} gnsszoe_t;

/**
 * @brief GNSS ZOE Click configuration object.
 * @details Configuration object definition of GNSS ZOE Click driver.
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
    
    pin_name_t  exi;                /**< EXI pin. */
    pin_name_t  rst;                /**< Reset pin. */

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

    gnsszoe_drv_t  drv_sel;        /**< Master driver interface selector. */

} gnsszoe_cfg_t;

/**
 * @brief GNSS ZOE Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSSZOE_OK = 0,
    GNSSZOE_ERROR = -1

} gnsszoe_return_value_t;

/*!
 * @addtogroup gnsszoe GNSS ZOE Click Driver
 * @brief API for configuring and manipulating GNSS ZOE Click driver.
 * @{
 */

/**
 * @brief GNSS ZOE configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnsszoe_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnsszoe_cfg_setup ( gnsszoe_cfg_t *cfg );

/**
 * @brief GNSS ZOE driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnsszoe_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnsszoe_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnsszoe_drv_interface_selection ( gnsszoe_cfg_t *cfg, gnsszoe_drv_t drv_sel );

/**
 * @brief GNSS ZOE initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnsszoe_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnsszoe_init ( gnsszoe_t *ctx, gnsszoe_cfg_t *cfg );

/**
 * @brief GNSS ZOE data writing function.
 * @details This function writes a desired number of data bytes to the module.
 * @param[in] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success, or number of data bytes written in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnsszoe_generic_write ( gnsszoe_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS ZOE data reading function.
 * @details This function reads a desired number of data bytes from the module.
 * @param[in] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >=0 - Success, or number of data bytes read in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnsszoe_generic_read ( gnsszoe_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS ZOE set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnsszoe_set_rst_pin ( gnsszoe_t *ctx, uint8_t state );

/**
 * @brief GNSS ZOE get EXI pin function.
 * @details This function returns the EXI pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnsszoe_get_exi_pin ( gnsszoe_t *ctx );

/**
 * @brief GNSS ZOE reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnsszoe_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnsszoe_reset_device ( gnsszoe_t *ctx );

/**
 * @brief GNSS ZOE parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : GNGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnsszoe_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSSZOE_H

/*! @} */ // gnsszoe

// ------------------------------------------------------------------------ END
