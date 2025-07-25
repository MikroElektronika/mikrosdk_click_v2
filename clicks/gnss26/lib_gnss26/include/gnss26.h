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
 * @file gnss26.h
 * @brief This file contains API for GNSS 26 Click Driver.
 */

#ifndef GNSS26_H
#define GNSS26_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup gnss26 GNSS 26 Click Driver
 * @brief API for configuring and manipulating GNSS 26 Click driver.
 * @{
 */

/**
 * @defgroup gnss26_cmd GNSS 26 Device Settings
 * @brief Settings for registers of GNSS 26 Click driver.
 */

/**
 * @addtogroup gnss26_cmd
 * @{
 */

/**
 * @brief GNSS 26 response buffer commands.
 * @details Specified response buffer commands of GNSS 26 Click driver.
 */
#define GNSS26_RSP_START                            "$"
#define GNSS26_RSP_DELIMITER                        ","
#define GNSS26_RSP_END                              "\r\n"
#define GNSS26_RSP_GGA                              "GGA"

/**
 * @brief GNSS 26 dummy data.
 * @details Definition of dummy data.
 */
#define GNSS26_DUMMY                                0xFF

/**
 * @brief GNSS 26 GGA command elements.
 * @details Specified GGA command elements of GNSS 26 Click driver.
 */
#define GNSS26_GGA_ELEMENT_SIZE                     15
#define GNSS26_GGA_TIME                             1
#define GNSS26_GGA_LATITUDE                         2
#define GNSS26_GGA_LATITUDE_SIDE                    3
#define GNSS26_GGA_LONGITUDE                        4
#define GNSS26_GGA_LONGITUDE_SIDE                   5
#define GNSS26_GGA_QUALITY_INDICATOR                6
#define GNSS26_GGA_NUMBER_OF_SATELLITES             7
#define GNSS26_GGA_H_DILUTION_OF_POS                8
#define GNSS26_GGA_ALTITUDE                         9
#define GNSS26_GGA_ALTITUDE_UNIT                    10
#define GNSS26_GGA_GEOIDAL_SEPARATION               11
#define GNSS26_GGA_GEOIDAL_SEPARATION_UNIT          12
#define GNSS26_GGA_TIME_SINCE_LAST_DGPS             13
#define GNSS26_GGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GNSS 26 I2C settings.
 * @details Specified setting for I2C of GNSS 26 Click driver.
 */
#define GNSS26_I2C_SLAVE_CR_CMD                     0xAA51u
#define GNSS26_I2C_SLAVE_CW_CMD                     0xAA53u
#define GNSS26_I2C_SLAVE_CMD_LEN                    8
#define GNSS26_I2C_SLAVE_RX_LEN                     4
#define GNSS26_I2C_SLAVE_TX_LEN_REG_OFFSET          0x0008u
#define GNSS26_I2C_SLAVE_TX_BUF_REG_OFFSET          0x2000u
#define GNSS26_I2C_SLAVE_RX_LEN_REG_OFFSET          0x0004u
#define GNSS26_I2C_SLAVE_RX_BUF_REG_OFFSET          0x1000u
#define GNSS26_I2C_SLAVE_ADDRESS_CR_OR_CW           0x50
#define GNSS26_I2C_SLAVE_ADDRESS_R                  0x54
#define GNSS26_I2C_SLAVE_ADDRESS_W                  0x58
#define GNSS26_I2C_SLAVE_MAX_ERRORS                 10

/**
 * @brief GNSS 26 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS26_TX_DRV_BUFFER_SIZE                   100
#define GNSS26_RX_DRV_BUFFER_SIZE                   800

/*! @} */ // gnss26_cmd

/**
 * @defgroup gnss26_map GNSS 26 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 26 Click driver.
 */

/**
 * @addtogroup gnss26_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 26 Click to the selected MikroBUS.
 */
#define GNSS26_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pps = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnss26_map
/*! @} */ // gnss26

/**
 * @brief GNSS 26 Click driver selector.
 * @details Selects target driver interface of GNSS 26 Click driver.
 */
typedef enum
{
    GNSS26_DRV_SEL_UART,     /**< UART driver descriptor. */
    GNSS26_DRV_SEL_I2C       /**< I2C driver descriptor. */

} gnss26_drv_t;

/**
 * @brief GNSS 26 Click driver interface.
 * @details Definition of driver interface of GNSS 26 Click driver.
 */
struct gnss26_s;
typedef err_t ( *gnss26_master_io_t )( struct gnss26_s*, uint8_t*, uint16_t ); /**< Driver serial interface. */

/**
 * @brief GNSS 26 Click context object.
 * @details Context object definition of GNSS 26 Click driver.
 */
typedef struct gnss26_s
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (Active low). */

    // Input pins
    digital_in_t pps;               /**< Pulse per second pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSS26_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ GNSS26_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    gnss26_drv_t drv_sel;           /**< Master driver interface selector. */

    gnss26_master_io_t write_f;     /**< Master write function. */
    gnss26_master_io_t read_f;      /**< Master read function. */

} gnss26_t;

/**
 * @brief GNSS 26 Click configuration object.
 * @details Configuration object definition of GNSS 26 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                 /**< Reset pin (Active low). */
    pin_name_t pps;                 /**< Pulse per second pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

    gnss26_drv_t drv_sel;           /**< Master driver interface selector. */

} gnss26_cfg_t;

/**
 * @brief GNSS 26 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS26_OK = 0,
    GNSS26_ERROR = -1

} gnss26_return_value_t;

/*!
 * @addtogroup gnss26 GNSS 26 Click Driver
 * @brief API for configuring and manipulating GNSS 26 Click driver.
 * @{
 */

/**
 * @brief GNSS 26 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss26_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss26_cfg_setup ( gnss26_cfg_t *cfg );

/**
 * @brief GNSS 26 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnss26_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnss26_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnss26_drv_interface_sel ( gnss26_cfg_t *cfg, gnss26_drv_t drv_sel );

/**
 * @brief GNSS 26 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss26_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss26_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss26_init ( gnss26_t *ctx, gnss26_cfg_t *cfg );

/**
 * @brief GNSS 26 data writing function.
 * @details This function writes a desired number of data bytes by using UART or I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss26_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss26_generic_write ( gnss26_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 26 data reading function.
 * @details This function reads a desired number of data bytes by using UART or I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss26_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss26_generic_read ( gnss26_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS 26 get PPS pin function.
 * @details This function returns the pulse per second (PPS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss26_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss26_get_pps_pin ( gnss26_t *ctx );

/**
 * @brief GNSS 26 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss26_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss26_set_rst_pin ( gnss26_t *ctx, uint8_t state );

/**
 * @brief GNSS 26 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnss26_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss26_reset_device ( gnss26_t *ctx );

/**
 * @brief GNSS 26 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss26_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS26_H

/*! @} */ // gnss26

// ------------------------------------------------------------------------ END
