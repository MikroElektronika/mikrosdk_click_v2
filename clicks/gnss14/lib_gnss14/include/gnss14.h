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
 * @file gnss14.h
 * @brief This file contains API for GNSS 14 Click Driver.
 */

#ifndef GNSS14_H
#define GNSS14_H

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
 * @addtogroup gnss14 GNSS 14 Click Driver
 * @brief API for configuring and manipulating GNSS 14 Click driver.
 * @{
 */

/**
 * @defgroup gnss14_set GNSS 14 Device Settings
 * @brief Settings for registers of GNSS 14 Click driver.
 */

/**
 * @addtogroup gnss14_set
 * @{
 */

 /**
 * @brief GNSS 14 response buffer commands.
 * @details Specified response buffer commands of GNSS 14 Click driver.
 */
#define GNSS14_RSP_START                                "$"
#define GNSS14_RSP_DELIMITER                            ","
#define GNSS14_RSP_GNGGA                                "$GNGGA"

/**
 * @brief GNSS 14 GNGGA command elements.
 * @details Specified GNGGA command elements of GNSS 14 Click driver.
 */
#define GNSS14_GNGGA_ELEMENT_SIZE                       15
#define GNSS14_GNGGA_TIME                               1
#define GNSS14_GNGGA_LATITUDE                           2
#define GNSS14_GNGGA_LATITUDE_SIDE                      3
#define GNSS14_GNGGA_LONGITUDE                          4
#define GNSS14_GNGGA_LONGITUDE_SIDE                     5
#define GNSS14_GNGGA_QUALITY_INDICATOR                  6
#define GNSS14_GNGGA_NUMBER_OF_SATELLITES               7
#define GNSS14_GNGGA_H_DILUTION_OF_POS                  8
#define GNSS14_GNGGA_ALTITUDE                           9
#define GNSS14_GNGGA_ALTITUDE_UNIT                      10
#define GNSS14_GNGGA_GEOIDAL_SEPARATION                 11
#define GNSS14_GNGGA_GEOIDAL_SEPARATION_UNIT            12
#define GNSS14_GNGGA_TIME_SINCE_LAST_DGPS               13
#define GNSS14_GNGGA_DGPS_REFERENCE_STATION_ID          14

/**
 * @brief GNSS 14 dummy data.
 * @details Specified dummy data of GNSS 14 Click driver.
 */
#define GNSS14_DUMMY                                    0xFF

/**
 * @brief GNSS 14 device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS 14 Click driver.
 */
#define GNSS14_SET_DEV_ADDR                             0x42

/**
 * @brief GNSS 14 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS14_DRV_BUFFER_SIZE                          200

/*! @} */ // gnss14_set

/**
 * @defgroup gnss14_map GNSS 14 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 14 Click driver.
 */

/**
 * @addtogroup gnss14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 14 Click to the selected MikroBUS.
 */
#define GNSS14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl    = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda    = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX );  \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX );  \
    cfg.io6    = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.eit    = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.tp     = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gnss14_map
/*! @} */ // gnss14

/**
 * @brief GNSS 14 Click driver selector.
 * @details Selects target driver interface of GNSS 14 Click driver.
 */
typedef enum
{
    GNSS14_DRV_SEL_UART,            /**< UART driver descriptor. */
    GNSS14_DRV_SEL_I2C              /**< I2C driver descriptor. */

} gnss14_drv_t;

/**
 * @brief GNSS 14 Click driver interface.
 * @details Definition of driver interface of GNSS 14 Click driver.
 */
typedef err_t ( *gnss14_master_io_t )( struct gnss14_s*, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief GNSS 14 Click context object.
 * @details Context object definition of GNSS 14 Click driver.
 */
typedef struct gnss14_s
{
    // Output pins
    digital_out_t io6;    /**< Digital I/O pin. */
    digital_out_t rst;    /**< Reset pin. */

    // Input pins
    digital_in_t eit;    /**< External interrupt pin. */
    digital_in_t tp;      /**< Time pulse signal pin. */

    // Modules
    i2c_master_t  i2c;    /**< I2C driver object. */
    uart_t uart;          /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSS14_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ GNSS14_DRV_BUFFER_SIZE ];  /**< Buffer size. */

    uint8_t       slave_address;    /**< Device slave address (used for I2C driver). */
    pin_name_t    chip_select;      /**< Chip select pin descriptor (used for SPI driver). */
    gnss14_drv_t  drv_sel;          /**< Master driver interface selector. */

    gnss14_master_io_t write_f;     /**< Master write function. */
    gnss14_master_io_t read_f;      /**< Master read function. */

} gnss14_t;

/**
 * @brief GNSS 14 Click configuration object.
 * @details Configuration object definition of GNSS 14 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rx_pin;                          /**< RX pin. */
    pin_name_t tx_pin;                          /**< TX pin. */

    // Additional gpio pins
    pin_name_t io6;    /**< Digital I/O pin. */
    pin_name_t rst;    /**< Reset pin. */
    pin_name_t eit;    /**< External interrupt pin. */
    pin_name_t tp;     /**< Time pulse signal pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

    gnss14_drv_t     drv_sel;       /**< Master driver interface selector. */

} gnss14_cfg_t;

/**
 * @brief GNSS 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS14_OK = 0,
    GNSS14_ERROR = -1

} gnss14_return_value_t;

/*!
 * @addtogroup gnss14 GNSS 14 Click Driver
 * @brief API for configuring and manipulating GNSS 14 Click driver.
 * @{
 */

/**
 * @brief GNSS 14 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss14_cfg_setup ( gnss14_cfg_t *cfg );

/**
 * @brief GNSS 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss14_init ( gnss14_t *ctx, gnss14_cfg_t *cfg );

/**
 * @brief GNSS 14 data writing function.
 * @details This function writes a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss14_generic_write ( gnss14_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 14 data reading function.
 * @details This function reads a desired number of data bytes by using UART serial interface.
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss14_generic_read ( gnss14_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS 14 set IO6 pin function.
 * @details This function ets the IO6 (AN) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @note None.
 */
void gnss14_set_io6_pin ( gnss14_t *ctx, uint8_t state );

/**
 * @brief GNSS 14 set RST pin function.
 * @details This function ets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @note None.
 */
void gnss14_set_rst_pin ( gnss14_t *ctx, uint8_t state );

/**
 * @brief GNSS 14 get external interrupt pin state function.
 * @details This function returns the EIT pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss14_get_eit_pin ( gnss14_t *ctx );

/**
 * @brief GNSS 14 get time pulse signal pin state function.
 * @details This function returns the TP pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss14_get_tp_pin ( gnss14_t *ctx );

/**
 * @brief GNSS 14 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnss14_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
void gnss14_reset_device ( gnss14_t *ctx );

/**
 * @brief GNSS 14 parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : GNGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss14_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS14_H

/*! @} */ // gnss14

// ------------------------------------------------------------------------ END
