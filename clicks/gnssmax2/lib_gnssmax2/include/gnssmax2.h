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
 * @file gnssmax2.h
 * @brief This file contains API for GNSS MAX 2 Click Driver.
 */

#ifndef GNSSMAX2_H
#define GNSSMAX2_H

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
 * @addtogroup gnssmax2 GNSS MAX 2 Click Driver
 * @brief API for configuring and manipulating GNSS MAX 2 Click driver.
 * @{
 */

/**
 * @defgroup gnssmax2_cmd GNSS MAX 2 Device Settings
 * @brief Settings for registers of GNSS MAX 2 Click driver.
 */

/**
 * @addtogroup gnssmax2_cmd
 * @{
 */

/**
 * @brief GNSS MAX 2 response buffer commands.
 * @details Specified response buffer commands of GNSS MAX 2 Click driver.
 */
#define GNSSMAX2_RSP_START                              "$"
#define GNSSMAX2_RSP_DELIMITER                          ","
#define GNSSMAX2_RSP_END                                "\r\n"
#define GNSSMAX2_RSP_GGA                                "GGA"

/**
 * @brief GNSS MAX 2 GGA command elements.
 * @details Specified GGA command elements of GNSS MAX 2 Click driver.
 */
#define GNSSMAX2_GGA_ELEMENT_SIZE                       15
#define GNSSMAX2_GGA_TIME                               1
#define GNSSMAX2_GGA_LATITUDE                           2
#define GNSSMAX2_GGA_LATITUDE_SIDE                      3
#define GNSSMAX2_GGA_LONGITUDE                          4
#define GNSSMAX2_GGA_LONGITUDE_SIDE                     5
#define GNSSMAX2_GGA_QUALITY_INDICATOR                  6
#define GNSSMAX2_GGA_NUMBER_OF_SATELLITES               7
#define GNSSMAX2_GGA_H_DILUTION_OF_POS                  8
#define GNSSMAX2_GGA_ALTITUDE                           9
#define GNSSMAX2_GGA_ALTITUDE_UNIT                      10
#define GNSSMAX2_GGA_GEOIDAL_SEPARATION                 11
#define GNSSMAX2_GGA_GEOIDAL_SEPARATION_UNIT            12
#define GNSSMAX2_GGA_TIME_SINCE_LAST_DGPS               13
#define GNSSMAX2_GGA_DGPS_REFERENCE_STATION_ID          14

/**
 * @brief GNSS MAX 2 dummy data.
 * @details Definition of dummy data.
 */
#define GNSSMAX2_DUMMY                                  0xFF

/**
 * @brief GNSS MAX 2 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSSMAX2_TX_DRV_BUFFER_SIZE                     100
#define GNSSMAX2_RX_DRV_BUFFER_SIZE                     1000

/**
 * @brief GNSS MAX 2 device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS MAX 2 Click driver.
 */
#define GNSSMAX2_DEVICE_ADDRESS                         0x42

/*! @} */ // gnssmax2_cmd

/**
 * @defgroup gnssmax2_map GNSS MAX 2 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS MAX 2 Click driver.
 */

/**
 * @addtogroup gnssmax2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS MAX 2 Click to the selected MikroBUS.
 */
#define GNSSMAX2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.exi = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pps = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnssmax2_map
/*! @} */ // gnssmax2

/**
 * @brief GNSS MAX 2 Click driver selector.
 * @details Selects target driver interface of GNSS MAX 2 Click driver.
 */
typedef enum
{
    GNSSMAX2_DRV_SEL_UART,     /**< UART driver descriptor. */
    GNSSMAX2_DRV_SEL_I2C       /**< I2C driver descriptor. */

} gnssmax2_drv_t;

/**
 * @brief GNSS MAX 2 Click driver interface.
 * @details Definition of driver interface of GNSS MAX 2 Click driver.
 */
struct gnssmax2_s;
typedef err_t ( *gnssmax2_master_io_t )( struct gnssmax2_s*, uint8_t*, uint16_t ); /**< Driver serial interface. */

/**
 * @brief GNSS MAX 2 Click context object.
 * @details Context object definition of GNSS MAX 2 Click driver.
 */
typedef struct gnssmax2_s
{
    // Output pins
    digital_out_t rst;              /**< Reset pin (Active low). */
    digital_out_t exi;              /**< Ext INT pin. */

    // Input pins
    digital_in_t pps;               /**< Pulse per second pin. */

    // Modules
    uart_t uart;                    /**< UART driver object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSSMAX2_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ GNSSMAX2_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    gnssmax2_drv_t drv_sel;         /**< Master driver interface selector. */

    gnssmax2_master_io_t write_f;   /**< Master write function. */
    gnssmax2_master_io_t read_f;    /**< Master read function. */

} gnssmax2_t;

/**
 * @brief GNSS MAX 2 Click configuration object.
 * @details Configuration object definition of GNSS MAX 2 Click driver.
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
    pin_name_t exi;                 /**< Ext INT pin. */
    pin_name_t pps;                 /**< Pulse per second pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    // Static variable
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

    gnssmax2_drv_t   drv_sel;       /**< Master driver interface selector. */

} gnssmax2_cfg_t;

/**
 * @brief GNSS MAX 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSSMAX2_OK = 0,
    GNSSMAX2_ERROR = -1

} gnssmax2_return_value_t;

/*!
 * @addtogroup gnssmax2 GNSS MAX 2 Click Driver
 * @brief API for configuring and manipulating GNSS MAX 2 Click driver.
 * @{
 */

/**
 * @brief GNSS MAX 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnssmax2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnssmax2_cfg_setup ( gnssmax2_cfg_t *cfg );

/**
 * @brief GNSS MAX 2 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnssmax2_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnssmax2_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnssmax2_drv_interface_sel ( gnssmax2_cfg_t *cfg, gnssmax2_drv_t drv_sel );

/**
 * @brief GNSS MAX 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnssmax2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnssmax2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax2_init ( gnssmax2_t *ctx, gnssmax2_cfg_t *cfg );

/**
 * @brief GNSS MAX 2 data writing function.
 * @details This function writes a desired number of data bytes by using UART or I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax2_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax2_generic_write ( gnssmax2_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS MAX 2 data reading function.
 * @details This function reads a desired number of data bytes by using UART or I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax2_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax2_generic_read ( gnssmax2_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS MAX 2 get PPS pin function.
 * @details This function returns the pulse per second (PPS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssmax2_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssmax2_get_pps_pin ( gnssmax2_t *ctx );

/**
 * @brief GNSS MAX 2 set EXI pin function.
 * @details This function sets the EXI pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssmax2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssmax2_set_exi_pin ( gnssmax2_t *ctx, uint8_t state );

/**
 * @brief GNSS MAX 2 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssmax2_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssmax2_set_rst_pin ( gnssmax2_t *ctx, uint8_t state );

/**
 * @brief GNSS MAX 2 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnssmax2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnssmax2_reset_device ( gnssmax2_t *ctx );

/**
 * @brief GNSS MAX 2 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax2_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSSMAX2_H

/*! @} */ // gnssmax2

// ------------------------------------------------------------------------ END
