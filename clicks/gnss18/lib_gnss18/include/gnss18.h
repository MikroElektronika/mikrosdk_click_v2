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
 * @file gnss18.h
 * @brief This file contains API for GNSS 18 Click Driver.
 */

#ifndef GNSS18_H
#define GNSS18_H

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
 * @addtogroup gnss18 GNSS 18 Click Driver
 * @brief API for configuring and manipulating GNSS 18 Click driver.
 * @{
 */

/**
 * @defgroup gnss18_cmd GNSS 18 Device Settings
 * @brief Settings for registers of GNSS 18 Click driver.
 */

/**
 * @addtogroup gnss18_cmd
 * @{
 */

/**
 * @brief GNSS 18 response buffer commands.
 * @details Specified response buffer commands of GNSS 18 Click driver.
 */
#define GNSS18_RSP_START                             "$"
#define GNSS18_RSP_DELIMITER                         ","
#define GNSS18_RSP_END_SEQ                           "\r\n"
#define GNSS18_RSP_GPGGA                             "$GNGGA"
#define GNSS18_RSP_NO_FIX                            ""

/**
 * @brief GNSS 18 GPGGA command elements.
 * @details Specified GPGGA command elements of GNSS 18 Click driver.
 */
#define GNSS18_GPGGA_ELEMENT_SIZE                    15
#define GNSS18_GPGGA_TIME                            1
#define GNSS18_GPGGA_LATITUDE                        2
#define GNSS18_GPGGA_LATITUDE_SIDE                   3
#define GNSS18_GPGGA_LONGITUDE                       4
#define GNSS18_GPGGA_LONGITUDE_SIDE                  5
#define GNSS18_GPGGA_QUALITY_INDICATOR               6
#define GNSS18_GPGGA_NUMBER_OF_SATELLITES            7
#define GNSS18_GPGGA_H_DILUTION_OF_POS               8
#define GNSS18_GPGGA_ALTITUDE                        9
#define GNSS18_GPGGA_ALTITUDE_UNIT                   10
#define GNSS18_GPGGA_GEOIDAL_SEPARATION              11
#define GNSS18_GPGGA_GEOIDAL_SEPARATION_UNIT         12
#define GNSS18_GPGGA_TIME_SINCE_LAST_DGPS            13
#define GNSS18_GPGGA_DGPS_REFERENCE_STATION_ID       14

/**
 * @brief GNSS 18 dummy data.
 * @details Definition of dummy data.
 */
#define GNSS18_DUMMY                                 0xFF

/**
 * @brief GNSS 18 device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS 18 Click driver.
 */
#define GNSS18_DEVICE_ADDRESS                        0x42

/**
 * @brief GNSS 18 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS18_DRV_TX_BUFFER_SIZE                    100
#define GNSS18_DRV_RX_BUFFER_SIZE                    500

/*! @} */ // gnss18_cmd

/**
 * @defgroup gnss18_map GNSS 18 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 18 Click driver.
 */

/**
 * @addtogroup gnss18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 18 Click to the selected MikroBUS.
 */
#define GNSS18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnss18_map
/*! @} */ // gnss18

/**
 * @brief GNSS 18 Click driver selector.
 * @details Selects target driver interface of GNSS 18 Click driver.
 */
typedef enum
{
    GNSS18_DRV_SEL_UART,      /**< UART driver descriptor. */
    GNSS18_DRV_SEL_I2C        /**< I2C driver descriptor. */

} gnss18_drv_t;

/**
 * @brief GNSS 18 Click driver interface.
 * @details Definition of driver interface of GNSS 18 Click driver.
 */
typedef err_t ( *gnss18_master_io_t )( struct gnss18_s*, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief GNSS 18 Click context object.
 * @details Context object definition of GNSS 18 Click driver.
 */
typedef struct gnss18_s
{
    // Output pins
    digital_out_t rst;      /**< Reset pin. */

    // Input pins
    digital_in_t int_pin;   /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSS18_DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ GNSS18_DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */
    
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    gnss18_drv_t drv_sel;    /**< Master driver interface selector. */
    
    gnss18_master_io_t  write_f;     /**< Master write function. */
    gnss18_master_io_t  read_f;      /**< Master read function. */

} gnss18_t;

/**
 * @brief GNSS 18 Click configuration object.
 * @details Configuration object definition of GNSS 18 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;         /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rx_pin;      /**< RX pin. */
    pin_name_t tx_pin;      /**< TX pin. */

    // Additional gpio pins
    pin_name_t rst;         /**< Reset pin. */
    pin_name_t int_pin;     /**< Interrupt pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */
    
    
    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */
    
    gnss18_drv_t drv_sel;    /**< Master driver interface selector. */

} gnss18_cfg_t;

/**
 * @brief GNSS 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS18_OK = 0,
    GNSS18_ERROR = -1

} gnss18_return_value_t;

/*!
 * @addtogroup gnss18 GNSS 18 Click Driver
 * @brief API for configuring and manipulating GNSS 18 Click driver.
 * @{
 */

/**
 * @brief GNSS 18 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss18_cfg_setup ( gnss18_cfg_t *cfg );

/**
 * @brief GNSS 18 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnss18_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnss18_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnss18_drv_interface_selection ( gnss18_cfg_t *cfg, gnss18_drv_t drv_sel );

/**
 * @brief GNSS 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss18_init ( gnss18_t *ctx, gnss18_cfg_t *cfg );

/**
 * @brief GNSS 18 data writing function.
 * @details This function writes a desired number of data bytes to the module.
 * @param[in] ctx : Click context object.
 * See #gnss18_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success, or number of data bytes written in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss18_generic_write ( gnss18_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 18 data reading function.
 * @details This function reads a desired number of data bytes from the module.
 * @param[in] ctx : Click context object.
 * See #gnss18_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >=0 - Success, or number of data bytes read in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss18_generic_read ( gnss18_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS 18 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss18_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss18_set_rst_pin ( gnss18_t *ctx, uint8_t state );

/**
 * @brief GNSS 18 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss18_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss18_get_int_pin ( gnss18_t *ctx );

/**
 * @brief GNSS 18 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnss18_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss18_reset_device ( gnss18_t *ctx );

/**
 * @brief GNSS 18 parse GPGGA function.
 * @details This function parses the GPGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gpgga_element : GPGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss18_parse_gpgga ( uint8_t *rsp_buf, uint8_t gpgga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS18_H

/*! @} */ // gnss18

// ------------------------------------------------------------------------ END
