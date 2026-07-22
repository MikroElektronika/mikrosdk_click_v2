/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file gnssmax4.h
 * @brief This file contains API for GNSS MAX 4 Click Driver.
 */

#ifndef GNSSMAX4_H
#define GNSSMAX4_H

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
 * @addtogroup gnssmax4 GNSS MAX 4 Click Driver
 * @brief API for configuring and manipulating GNSS MAX 4 Click driver.
 * @{
 */

/**
 * @defgroup gnssmax4_cmd GNSS MAX 4 Device Settings
 * @brief Settings of GNSS MAX 4 Click driver.
 */

/**
 * @addtogroup gnssmax4_cmd
 * @{
 */

/**
 * @brief GNSS MAX 4 response buffer commands.
 * @details Specified response buffer commands of GNSS MAX 4 Click driver.
 */
#define GNSSMAX4_RSP_START                              "$"
#define GNSSMAX4_RSP_DELIMITER                          ","
#define GNSSMAX4_RSP_END                                "\r\n"
#define GNSSMAX4_RSP_GGA                                "GGA"

/**
 * @brief GNSS MAX 4 GGA command elements setting.
 * @details Specified setting for GGA command elements of GNSS MAX 4 Click driver.
 */
#define GNSSMAX4_GGA_ELEMENT_SIZE                       15
#define GNSSMAX4_GGA_TIME                               1 
#define GNSSMAX4_GGA_LATITUDE                           2 
#define GNSSMAX4_GGA_LATITUDE_SIDE                      3 
#define GNSSMAX4_GGA_LONGITUDE                          4 
#define GNSSMAX4_GGA_LONGITUDE_SIDE                     5 
#define GNSSMAX4_GGA_QUALITY_INDICATOR                  6 
#define GNSSMAX4_GGA_NUMBER_OF_SATELLITES               7 
#define GNSSMAX4_GGA_H_DILUTION_OF_POS                  8 
#define GNSSMAX4_GGA_ALTITUDE                           9 
#define GNSSMAX4_GGA_ALTITUDE_UNIT                      10
#define GNSSMAX4_GGA_GEOIDAL_SEPARATION                 11
#define GNSSMAX4_GGA_GEOIDAL_SEPARATION_UNIT            12
#define GNSSMAX4_GGA_TIME_SINCE_LAST_DGPS               13
#define GNSSMAX4_GGA_DGPS_REFERENCE_STATION_ID          14

/**
 * @brief GNSS MAX 4 dummy data setting.
 * @details Specified setting for dummy data of GNSS MAX 4 Click driver.
 */
#define GNSSMAX4_DUMMY                                  0xFF

/**
 * @brief GNSS MAX 4 pulse per second wait timeout setting.
 * @details Specified setting for pulse per second wait timeout of GNSS MAX 4 Click driver.
 */
#define GNSSMAX4_PPS_WAIT_TIMEOUT                       5000

/**
 * @brief GNSS MAX 4 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSSMAX4_TX_DRV_BUFFER_SIZE                     100
#define GNSSMAX4_RX_DRV_BUFFER_SIZE                     1000

/**
 * @brief GNSS MAX 4 device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS MAX 4 Click driver.
 */
#define GNSSMAX4_DEVICE_ADDRESS                         0x42

/*! @} */ // gnssmax4_cmd

/**
 * @defgroup gnssmax4_map GNSS MAX 4 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS MAX 4 Click driver.
 */

/**
 * @addtogroup gnssmax4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS MAX 4 Click to the selected MikroBUS.
 */
#define GNSSMAX4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.exi = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pps = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnssmax4_map
/*! @} */ // gnssmax4

/**
 * @brief GNSS MAX 4 Click driver selector.
 * @details Selects target driver interface of GNSS MAX 4 Click driver.
 */
typedef enum
{
    GNSSMAX4_DRV_SEL_UART,     /**< UART driver descriptor. */
    GNSSMAX4_DRV_SEL_I2C       /**< I2C driver descriptor. */

} gnssmax4_drv_t;

/**
 * @brief GNSS MAX 4 Click driver interface.
 * @details Definition of driver interface of GNSS MAX 4 Click driver.
 */
struct gnssmax4_s;
typedef err_t ( *gnssmax4_master_io_t )( struct gnssmax4_s*, uint8_t*, uint16_t ); /**< Driver serial interface. */

/**
 * @brief GNSS MAX 4 Click context object.
 * @details Context object definition of GNSS MAX 4 Click driver.
 */
typedef struct gnssmax4_s
{
    // Output pins
    digital_out_t rst;               /**< Reset pin(active low). */
    digital_out_t exi;               /**< Ext INT pin. */

    // Input pins
    digital_in_t pps;                /**< Pulse per second pin. */

    // Modules
    uart_t uart;                     /**< UART driver object. */
    i2c_master_t i2c;                /**< I2C driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSSMAX4_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ GNSSMAX4_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */

    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */
    gnssmax4_drv_t drv_sel;         /**< Master driver interface selector. */

    gnssmax4_master_io_t write_f;   /**< Master write function. */
    gnssmax4_master_io_t read_f;    /**< Master read function. */

} gnssmax4_t;

/**
 * @brief GNSS MAX 4 Click configuration object.
 * @details Configuration object definition of GNSS MAX 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;                             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;                             /**< Reset pin (Active low). */
    pin_name_t exi;                             /**< Ext INT pin. */
    pin_name_t pps;                             /**< Pulse per second pin. */

    uint32_t   i2c_speed;                       /**< I2C serial speed. */
    uint8_t    i2c_address;                     /**< I2C slave address. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

    gnssmax4_drv_t   drv_sel;                   /**< Master driver interface selector. */

} gnssmax4_cfg_t;

/**
 * @brief GNSS MAX 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSSMAX4_OK = 0,
    GNSSMAX4_ERROR = -1

} gnssmax4_return_value_t;

/*!
 * @addtogroup gnssmax4 GNSS MAX 4 Click Driver
 * @brief API for configuring and manipulating GNSS MAX 4 Click driver.
 * @{
 */

/**
 * @brief GNSS MAX 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnssmax4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnssmax4_cfg_setup ( gnssmax4_cfg_t *cfg );

/**
 * @brief GNSS MAX 4 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnssmax4_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnssmax4_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnssmax4_drv_interface_sel ( gnssmax4_cfg_t *cfg, gnssmax4_drv_t drv_sel );

/**
 * @brief GNSS MAX 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnssmax4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnssmax4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax4_init ( gnssmax4_t *ctx, gnssmax4_cfg_t *cfg );

/**
 * @brief GNSS MAX 4 data writing function.
 * @details This function writes a desired number of data bytes by using UART or I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax4_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax4_generic_write ( gnssmax4_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS MAX 4 data reading function.
 * @details This function reads a desired number of data bytes by using UART or I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssmax4_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax4_generic_read ( gnssmax4_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS MAX 4 get PPS pin function.
 * @details This function returns the pulse per second (PPS) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssmax4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssmax4_get_pps_pin ( gnssmax4_t *ctx );

/**
 * @brief GNSS MAX 4 set EXI pin function.
 * @details This function sets the EXI (EXTINT) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssmax4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssmax4_set_exi_pin ( gnssmax4_t *ctx, uint8_t state );

/**
 * @brief GNSS MAX 4 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssmax4_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssmax4_set_rst_pin ( gnssmax4_t *ctx, uint8_t state );

/**
 * @brief GNSS MAX 4 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnssmax4_t object definition for detailed explanation.
 * @return None.
 * @note performing a reset will delete RAM and BBR data which will lead
 * to a loss of configuration => COLD start will be done next time
 * the device is powered up instead of warm start which will require
 * significantly more time.
 */
void gnssmax4_reset_device ( gnssmax4_t *ctx );

/**
 * @brief GNSS MAX 4 parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssmax4_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSSMAX4_H

/*! @} */ // gnssmax4

// ------------------------------------------------------------------------ END
