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
 * @file gnss20.h
 * @brief This file contains API for GNSS 20 Click Driver.
 */

#ifndef GNSS20_H
#define GNSS20_H

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
 * @addtogroup gnss20 GNSS 20 Click Driver
 * @brief API for configuring and manipulating GNSS 20 Click driver.
 * @{
 */

/**
 * @defgroup gnss20_cmd GNSS 20 Device Settings
 * @brief Settings for registers of GNSS 20 Click driver.
 */

/**
 * @addtogroup gnss20_cmd
 * @{
 */

/**
 * @brief GNSS 20 response buffer commands.
 * @details Specified response buffer commands of GNSS 20 Click driver.
 */
#define GNSS20_RSP_START                            "$"
#define GNSS20_RSP_DELIMITER                        ","
#define GNSS20_RSP_END                              "\r\n"
#define GNSS20_RSP_GGA                              "GGA"

/**
 * @brief GNSS 20 dummy data.
 * @details Definition of dummy data.
 */
#define GNSS20_DUMMY                                0xFF

/**
 * @brief GNSS 20 GGA command elements.
 * @details Specified GGA command elements of GNSS 20 Click driver.
 */
#define GNSS20_GGA_ELEMENT_SIZE                     15
#define GNSS20_GGA_TIME                             1
#define GNSS20_GGA_LATITUDE                         2
#define GNSS20_GGA_LATITUDE_SIDE                    3
#define GNSS20_GGA_LONGITUDE                        4
#define GNSS20_GGA_LONGITUDE_SIDE                   5
#define GNSS20_GGA_QUALITY_INDICATOR                6
#define GNSS20_GGA_NUMBER_OF_SATELLITES             7
#define GNSS20_GGA_H_DILUTION_OF_POS                8
#define GNSS20_GGA_ALTITUDE                         9
#define GNSS20_GGA_ALTITUDE_UNIT                    10
#define GNSS20_GGA_GEOIDAL_SEPARATION               11
#define GNSS20_GGA_GEOIDAL_SEPARATION_UNIT          12
#define GNSS20_GGA_TIME_SINCE_LAST_DGPS             13
#define GNSS20_GGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GNSS 20 I2C settings.
 * @details Specified setting for I2C of GNSS 20 Click driver.
 */
#define GNSS20_I2C_SLAVE_CR_CMD                     0xAA51
#define GNSS20_I2C_SLAVE_CW_CMD                     0xAA53
#define GNSS20_I2C_SLAVE_CMD_LEN                    8
#define GNSS20_I2C_SLAVE_RX_LEN                     4
#define GNSS20_I2C_SLAVE_TX_LEN_REG_OFFSET          0x0008
#define GNSS20_I2C_SLAVE_TX_BUF_REG_OFFSET          0x2000
#define GNSS20_I2C_SLAVE_RX_LEN_REG_OFFSET          0x0004
#define GNSS20_I2C_SLAVE_RX_BUF_REG_OFFSET          0x1000
#define GNSS20_I2C_SLAVE_ADDRESS_CR_OR_CW           0x50
#define GNSS20_I2C_SLAVE_ADDRESS_R                  0x54
#define GNSS20_I2C_SLAVE_ADDRESS_W                  0x58
#define GNSS20_I2C_SLAVE_MAX_ERRORS                 10

/**
 * @brief GNSS 20 SPI settings.
 * @details Specified setting for SPI of GNSS 20 Click driver.
 */
#define GNSS20_SPI_SLAVE_CFG_RD_CMD                 0x0A
#define GNSS20_SPI_SLAVE_RD_CMD                     0x81
#define GNSS20_SPI_SLAVE_CFG_WR_CMD                 0x0C
#define GNSS20_SPI_SLAVE_WR_CMD                     0x0E
#define GNSS20_SPI_SLAVE_RS_CMD                     0x06
#define GNSS20_SPI_SLAVE_WS_CMD                     0x08
#define GNSS20_SPI_SLAVE_PWON_CMD                   0x04
#define GNSS20_SPI_SLAVE_PWOFF_CMD                  0x02
#define GNSS20_SPI_SLAVE_CMD_LEN                    9
#define GNSS20_SPI_SLAVE_RX_LEN                     4
#define GNSS20_SPI_SLAVE_TX_LEN_REG_OFFSET          0x00000008ul
#define GNSS20_SPI_SLAVE_TX_BUF_REG_OFFSET          0x00002000ul
#define GNSS20_SPI_SLAVE_RX_LEN_REG_OFFSET          0x00000004ul
#define GNSS20_SPI_SLAVE_RX_BUF_REG_OFFSET          0x00001000ul

/**
 * @brief GNSS 20 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS20_TX_DRV_BUFFER_SIZE                   100
#define GNSS20_RX_DRV_BUFFER_SIZE                   800

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b gnss20_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define GNSS20_SET_DATA_SAMPLE_EDGE                 SET_SPI_DATA_SAMPLE_EDGE
#define GNSS20_SET_DATA_SAMPLE_MIDDLE               SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // gnss20_set

/**
 * @defgroup gnss20_map GNSS 20 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 20 Click driver.
 */

/**
 * @addtogroup gnss20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 20 Click to the selected MikroBUS.
 */
#define GNSS20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst  = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pps  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gnss20_map
/*! @} */ // gnss20

/**
 * @brief GNSS 20 Click driver selector.
 * @details Selects target driver interface of GNSS 20 Click driver.
 */
typedef enum
{
    GNSS20_DRV_SEL_UART,            /**< UART driver descriptor. */
    GNSS20_DRV_SEL_SPI,             /**< SPI driver descriptor. */
    GNSS20_DRV_SEL_I2C              /**< I2C driver descriptor. */

} gnss20_drv_t;

/**
 * @brief GNSS 20 Click driver interface.
 * @details Definition of driver interface of GNSS 20 Click driver.
 */
struct gnss20_s;
typedef err_t ( *gnss20_master_io_t )( struct gnss20_s*, uint8_t*, uint16_t ); /**< Driver serial interface. */

/**
 * @brief GNSS 20 Click context object.
 * @details Context object definition of GNSS 20 Click driver.
 */
typedef struct gnss20_s
{
    digital_out_t rst;              /**< Reset pin (Active low). */

    digital_in_t pps;               /**< Pulse per second pin. */

    uart_t uart;                    /**< UART driver object. */
    i2c_master_t i2c;               /**< I2C driver object. */
    spi_master_t spi;               /**< SPI driver object. */

    uint8_t uart_rx_buffer[ GNSS20_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ GNSS20_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    pin_name_t chip_select;         /**< Chip select pin descriptor (used for SPI driver). */
    gnss20_drv_t drv_sel;           /**< Master driver interface selector. */

    gnss20_master_io_t write_f;     /**< Master write function. */
    gnss20_master_io_t read_f;      /**< Master read function. */

} gnss20_t;

/**
 * @brief GNSS 20 Click configuration object.
 * @details Configuration object definition of GNSS 20 Click driver.
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
    pin_name_t rst;                 /**< Reset pin (Active low). */
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

    gnss20_drv_t drv_sel;           /**< Master driver interface selector. */

} gnss20_cfg_t;

/**
 * @brief GNSS 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS20_OK = 0,
    GNSS20_ERROR = -1

} gnss20_return_value_t;

/*!
 * @addtogroup gnss20 GNSS 20 Click Driver
 * @brief API for configuring and manipulating GNSS 20 Click driver.
 * @{
 */

/**
 * @brief GNSS 20 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss20_cfg_setup ( gnss20_cfg_t *cfg );

/**
 * @brief GNSS 20 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnss20_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnss20_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnss20_drv_interface_sel ( gnss20_cfg_t *cfg, gnss20_drv_t drv_sel );

/**
 * @brief GNSS 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss20_init ( gnss20_t *ctx, gnss20_cfg_t *cfg );

/**
 * @brief GNSS 20 data writing function.
 * @details This function writes a desired number of data bytes by using the selected serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss20_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss20_generic_write ( gnss20_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 20 data reading function.
 * @details This function reads a desired number of data bytes by using the selected serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss20_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss20_generic_read ( gnss20_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS 20 get PPS pin function.
 * @details This function returns the pulse per second (PPS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss20_get_pps_pin ( gnss20_t *ctx );

/**
 * @brief GNSS 20 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss20_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss20_set_rst_pin ( gnss20_t *ctx, uint8_t state );

/**
 * @brief GNSS 20 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnss20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss20_reset_device ( gnss20_t *ctx );

/**
 * @brief GNSS 20 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss20_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS20_H

/*! @} */ // gnss20

// ------------------------------------------------------------------------ END
