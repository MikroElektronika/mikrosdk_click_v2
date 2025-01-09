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
 * @file gnss9.h
 * @brief This file contains API for GNSS 9 Click Driver.
 */

#ifndef GNSS9_H
#define GNSS9_H

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
 * @addtogroup gnss9 GNSS 9 Click Driver
 * @brief API for configuring and manipulating GNSS 9 Click driver.
 * @{
 */

/**
 * @defgroup gnss9_cmd GNSS 9 Device Settings
 * @brief Settings for registers of GNSS 9 Click driver.
 */

/**
 * @addtogroup gnss9_cmd
 * @{
 */

/**
 * @brief GNSS 9 response buffer commands.
 * @details Specified response buffer commands of GNSS 9 Click driver.
 */
#define GNSS9_RSP_START                             "$"
#define GNSS9_RSP_DELIMITER                         ","
#define GNSS9_RSP_END_SEQ                           "\r\n"
#define GNSS9_RSP_GPGGA                             "$GNGGA"
#define GNSS9_RSP_NO_FIX                            ""

/**
 * @brief GNSS 9 GPGGA command elements.
 * @details Specified GPGGA command elements of GNSS 9 Click driver.
 */
#define GNSS9_GPGGA_ELEMENT_SIZE                    15
#define GNSS9_GPGGA_TIME                            1
#define GNSS9_GPGGA_LATITUDE                        2
#define GNSS9_GPGGA_LATITUDE_SIDE                   3
#define GNSS9_GPGGA_LONGITUDE                       4
#define GNSS9_GPGGA_LONGITUDE_SIDE                  5
#define GNSS9_GPGGA_QUALITY_INDICATOR               6
#define GNSS9_GPGGA_NUMBER_OF_SATELLITES            7
#define GNSS9_GPGGA_H_DILUTION_OF_POS               8
#define GNSS9_GPGGA_ALTITUDE                        9
#define GNSS9_GPGGA_ALTITUDE_UNIT                   10
#define GNSS9_GPGGA_GEOIDAL_SEPARATION              11
#define GNSS9_GPGGA_GEOIDAL_SEPARATION_UNIT         12
#define GNSS9_GPGGA_TIME_SINCE_LAST_DGPS            13
#define GNSS9_GPGGA_DGPS_REFERENCE_STATION_ID       14

/**
 * @brief GNSS 9 dummy data.
 * @details Definition of dummy data.
 */
#define GNSS9_DUMMY                                 0xFF

/**
 * @brief GNSS 9 device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS 9 Click driver.
 */
#define GNSS9_DEVICE_ADDRESS                        0x3A

/**
 * @brief GNSS 9 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS9_DRV_TX_BUFFER_SIZE                    100
#define GNSS9_DRV_RX_BUFFER_SIZE                    500

/*! @} */ // gnss9_cmd

/**
 * @defgroup gnss9_map GNSS 9 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 9 Click driver.
 */

/**
 * @addtogroup gnss9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 9 Click to the selected MikroBUS.
 */
#define GNSS9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl     = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda     = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.aon     = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst     = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.wup     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pps     = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnss9_map
/*! @} */ // gnss9

/**
 * @brief GNSS 9 Click driver selector.
 * @details Selects target driver interface of GNSS 9 Click driver.
 */
typedef enum
{
    GNSS9_DRV_SEL_UART,      /**< UART driver descriptor. */
    GNSS9_DRV_SEL_I2C        /**< I2C driver descriptor. */

} gnss9_drv_t;

/**
 * @brief GNSS 9 Click driver interface.
 * @details Definition of driver interface of GNSS 9 Click driver.
 */
typedef err_t ( *gnss9_master_io_t )( struct gnss9_s*, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief GNSS 9 Click context object.
 * @details Context object definition of GNSS 9 Click driver.
 */
typedef struct gnss9_s
{
    // Output pins
    digital_out_t rst;      /**< Reset pin. */
    digital_out_t wup;      /**< Wake-up pin. */
    digital_out_t aon;      /**< Antenna power pin. */

    // Input pins
    digital_in_t pps;       /**< PPS pin. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */
    uart_t uart;            /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSS9_DRV_RX_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ GNSS9_DRV_TX_BUFFER_SIZE ];  /**< Buffer size. */
    
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    gnss9_drv_t drv_sel;    /**< Master driver interface selector. */
    
    gnss9_master_io_t  write_f;     /**< Master write function. */
    gnss9_master_io_t  read_f;      /**< Master read function. */

} gnss9_t;

/**
 * @brief GNSS 9 Click configuration object.
 * @details Configuration object definition of GNSS 9 Click driver.
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
    pin_name_t wup;         /**< Wake-up pin. */
    pin_name_t pps;         /**< PPS pin. */
    pin_name_t aon;         /**< Antenna power pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */
    
    
    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */
    
    gnss9_drv_t drv_sel;    /**< Master driver interface selector. */

} gnss9_cfg_t;

/**
 * @brief GNSS 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS9_OK = 0,
    GNSS9_ERROR = -1

} gnss9_return_value_t;

/*!
 * @addtogroup gnss9 GNSS 9 Click Driver
 * @brief API for configuring and manipulating GNSS 9 Click driver.
 * @{
 */

/**
 * @brief GNSS 9 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss9_cfg_setup ( gnss9_cfg_t *cfg );

/**
 * @brief GNSS 9 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnss9_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnss9_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnss9_drv_interface_selection ( gnss9_cfg_t *cfg, gnss9_drv_t drv_sel );

/**
 * @brief GNSS 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss9_init ( gnss9_t *ctx, gnss9_cfg_t *cfg );

/**
 * @brief GNSS 9 data writing function.
 * @details This function writes a desired number of data bytes to the module.
 * @param[in] ctx : Click context object.
 * See #gnss9_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  >=0 - Success, or number of data bytes written in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss9_generic_write ( gnss9_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief GNSS 9 data reading function.
 * @details This function reads a desired number of data bytes from the module.
 * @param[in] ctx : Click context object.
 * See #gnss9_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >=0 - Success, or number of data bytes read in the case of UART,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss9_generic_read ( gnss9_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief GNSS 9 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss9_set_rst_pin ( gnss9_t *ctx, uint8_t state );

/**
 * @brief GNSS 9 set WUP pin function.
 * @details This function sets the WUP pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss9_set_wup_pin ( gnss9_t *ctx, uint8_t state );

/**
 * @brief GNSS 9 set AON pin function.
 * @details This function sets the AON pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss9_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnss9_set_wup_pin ( gnss9_t *ctx, uint8_t state );

/**
 * @brief GNSS 9 get PPS pin function.
 * @details This function returns the PPS pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss9_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss9_get_pps_pin ( gnss9_t *ctx );

/**
 * @brief GNSS 9 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnss9_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnss9_reset_device ( gnss9_t *ctx );

/**
 * @brief GNSS 9 parse GPGGA function.
 * @details This function parses the GPGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gpgga_element : GPGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss9_parse_gpgga ( uint8_t *rsp_buf, uint8_t gpgga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS9_H

/*! @} */ // gnss9

// ------------------------------------------------------------------------ END
