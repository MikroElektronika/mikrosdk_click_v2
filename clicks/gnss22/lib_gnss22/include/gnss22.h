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
 * @file gnss22.h
 * @brief This file contains API for GNSS 22 Click Driver.
 */

#ifndef GNSS22_H
#define GNSS22_H

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
#include "drv_uart.h"

/*!
 * @addtogroup gnss22 GNSS 22 Click Driver
 * @brief API for configuring and manipulating GNSS 22 Click driver.
 * @{
 */

/**
 * @defgroup gnss22_set GNSS 22 Settings
 * @brief Settings of GNSS 22 Click driver.
 */

/**
 * @addtogroup gnss22_set
 * @{
 */

/**
 * @brief GNSS 22 response buffer commands.
 * @details Specified response buffer commands of GNSS 22 Click driver.
 */
#define GNSS22_RSP_START                            "$"
#define GNSS22_RSP_DELIMITER                        ","
#define GNSS22_RSP_END                              "\r\n"
#define GNSS22_RSP_GGA                              "GGA"

/**
 * @brief GNSS 22 dummy data.
 * @details Definition of dummy data.
 */
#define GNSS22_DUMMY                                0xFF
#define GNSS22_IDLE_DATA                            0x0A

/**
 * @brief GNSS 22 GGA command elements.
 * @details Specified GGA command elements of GNSS 22 Click driver.
 */
#define GNSS22_GGA_ELEMENT_SIZE                     15
#define GNSS22_GGA_TIME                             1
#define GNSS22_GGA_LATITUDE                         2
#define GNSS22_GGA_LATITUDE_SIDE                    3
#define GNSS22_GGA_LONGITUDE                        4
#define GNSS22_GGA_LONGITUDE_SIDE                   5
#define GNSS22_GGA_QUALITY_INDICATOR                6
#define GNSS22_GGA_NUMBER_OF_SATELLITES             7
#define GNSS22_GGA_H_DILUTION_OF_POS                8
#define GNSS22_GGA_ALTITUDE                         9
#define GNSS22_GGA_ALTITUDE_UNIT                    10
#define GNSS22_GGA_GEOIDAL_SEPARATION               11
#define GNSS22_GGA_GEOIDAL_SEPARATION_UNIT          12
#define GNSS22_GGA_TIME_SINCE_LAST_DGPS             13
#define GNSS22_GGA_DGPS_REFERENCE_STATION_ID        14

/**
 * @brief GNSS 22 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS22_TX_DRV_BUFFER_SIZE                   100
#define GNSS22_RX_DRV_BUFFER_SIZE                   800

/**
 * @brief GNSS 22 device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS 22 Click driver.
 */
#define GNSS22_DEVICE_ADDRESS                       0x10

/*! @} */ // gnss22_set

/**
 * @defgroup gnss22_map GNSS 22 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 22 Click driver.
 */

/**
 * @addtogroup gnss22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 22 Click to the selected MikroBUS.
 */
#define GNSS22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.fon = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fix = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pps = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gnss22_map
/*! @} */ // gnss22

/**
 * @brief GNSS 22 Click driver selector.
 * @details Selects target driver interface of GNSS 22 Click driver.
 */
typedef enum
{
    GNSS22_DRV_SEL_UART,            /**< UART driver descriptor. */
    GNSS22_DRV_SEL_I2C              /**< I2C driver descriptor. */

} gnss22_drv_t;

/**
 * @brief GNSS 22 Click driver interface.
 * @details Definition of driver interface of GNSS 22 Click driver.
 */
struct gnss22_s;
typedef err_t ( *gnss22_master_io_t )( struct gnss22_s*, uint8_t*, uint16_t ); /**< Driver serial interface. */

/**
 * @brief GNSS 22 Click context object.
 * @details Context object definition of GNSS 22 Click driver.
 */
typedef struct
{
    digital_out_t fon;              /**< Force ON pin (active high). */
    digital_out_t rst;              /**< Reset pin (active low). */
    digital_out_t stb;              /**< Standby enter/exit pin (edge-triggered). */

    digital_in_t fix;               /**< 3D fix indicator (active high). */
    digital_in_t pps;               /**< Pulse per second pin. */

    uart_t uart;                    /**< UART driver object. */
    i2c_master_t i2c;               /**< I2C driver object. */

    uint8_t uart_rx_buffer[ GNSS22_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ GNSS22_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    gnss22_drv_t drv_sel;           /**< Master driver interface selector. */

    gnss22_master_io_t write_f;     /**< Master write function. */
    gnss22_master_io_t read_f;      /**< Master read function. */

} gnss22_t;

/**
 * @brief GNSS 22 Click configuration object.
 * @details Configuration object definition of GNSS 22 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */
    pin_name_t fon;                 /**< Force ON pin (active high). */
    pin_name_t fix;                 /**< 3D fix indicator (active high). */
    pin_name_t rst;                 /**< Reset pin (active low). */
    pin_name_t stb;                 /**< Standby enter/exit pin (edge-triggered). */
    pin_name_t pps;                 /**< Pulse per second pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */

    gnss22_drv_t drv_sel;           /**< Master driver interface selector. */

} gnss22_cfg_t;

/**
 * @brief GNSS 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS22_OK = 0,
    GNSS22_ERROR = -1

} gnss22_return_value_t;

/*!
 * @addtogroup gnss22 GNSS 22 Click Driver
 * @brief API for configuring and manipulating GNSS 22 Click driver.
 * @{
 */

/**
 * @brief GNSS 22 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss22_cfg_setup ( gnss22_cfg_t *cfg );

/**
 * @brief GNSS 22 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnss22_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnss22_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnss22_drv_interface_sel ( gnss22_cfg_t *cfg, gnss22_drv_t drv_sel );

/**
 * @brief GNSS 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss22_init ( gnss22_t *ctx, gnss22_cfg_t *cfg );

/**
 * @brief GNSS 22 data writing function.
 * @details This function writes a desired number of data bytes by using the selected serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss22_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss22_generic_write ( gnss22_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 22 data reading function.
 * @details This function reads a desired number of data bytes by using the selected serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss22_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss22_generic_read ( gnss22_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS 22 get PPS pin function.
 * @details This function returns the pulse per second (PPS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss22_get_pps_pin ( gnss22_t *ctx );

/**
 * @brief GNSS 22 get FIX pin function.
 * @details This function returns the 3D fix indication (FIX) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss22_get_fix_pin ( gnss22_t *ctx );

/**
 * @brief GNSS 22 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss22_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss22_set_rst_pin ( gnss22_t *ctx, uint8_t state );

/**
 * @brief GNSS 22 set STB pin function.
 * @details This function sets the standby control (STB) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss22_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss22_set_stb_pin ( gnss22_t *ctx, uint8_t state );

/**
 * @brief GNSS 22 set FON pin function.
 * @details This function sets the force enable (FON) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss22_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss22_set_fon_pin ( gnss22_t *ctx, uint8_t state );

/**
 * @brief GNSS 22 reset device function.
 * @details This function resets the device by toggling the RST, STB, and FON pins.
 * @param[in] ctx : Click context object.
 * See #gnss22_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss22_reset_device ( gnss22_t *ctx );

/**
 * @brief GNSS 22 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss22_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS22_H

/*! @} */ // gnss22

// ------------------------------------------------------------------------ END
