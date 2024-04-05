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
 * @file gnss15.h
 * @brief This file contains API for GNSS 15 Click Driver.
 */

#ifndef GNSS15_H
#define GNSS15_H

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
 * @addtogroup gnss15 GNSS 15 Click Driver
 * @brief API for configuring and manipulating GNSS 15 Click driver.
 * @{
 */

/**
 * @defgroup gnss15_cmd GNSS 15 Device Settings
 * @brief Settings for registers of GNSS 15 Click driver.
 */

/**
 * @addtogroup gnss15_cmd
 * @{
 */

/**
 * @brief GNSS 15 control commands.
 * @details Specified setting for control commands of GNSS 15 Click driver.
 */
#define GNSS15_RSP_START                             "$"
#define GNSS15_RSP_DELIMITER                         ","
#define GNSS15_RSP_END_SEQ                           "\r\n"
#define GNSS15_RSP_GPGGA                             "$GPGGA"
#define GNSS15_RSP_NO_FIX                            "0000.00000"

/**
 * @brief GNSS 15 GPGGA command elements.
 * @details Specified GPGGA command elements of GNSS 15 Click driver.
 */
#define GNSS15_GPGGA_ELEMENT_SIZE                    15
#define GNSS15_GPGGA_TIME                            1
#define GNSS15_GPGGA_LATITUDE                        2
#define GNSS15_GPGGA_LATITUDE_SIDE                   3
#define GNSS15_GPGGA_LONGITUDE                       4
#define GNSS15_GPGGA_LONGITUDE_SIDE                  5
#define GNSS15_GPGGA_QUALITY_INDICATOR               6
#define GNSS15_GPGGA_NUMBER_OF_SATELLITES            7
#define GNSS15_GPGGA_H_DILUTION_OF_POS               8
#define GNSS15_GPGGA_ALTITUDE                        9
#define GNSS15_GPGGA_ALTITUDE_UNIT                   10
#define GNSS15_GPGGA_GEOIDAL_SEPARATION              11
#define GNSS15_GPGGA_GEOIDAL_SEPARATION_UNIT         12
#define GNSS15_GPGGA_TIME_SINCE_LAST_DGPS            13
#define GNSS15_GPGGA_DGPS_REFERENCE_STATION_ID       14


/**
 * @brief GNSS 15 dummy data.
 * @details Definition of dummy data.
 */
#define GNSS15_DUMMY                                 0xFF

/**
 * @brief GNSS 15 device address setting.
 * @details Specified setting for device slave address selection of
 * GNSS 15 Click driver.
 */
#define GNSS15_DEVICE_ADDRESS                        0x3A

/**
 * @brief GNSS 15 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSS15_TX_DRV_BUFFER_SIZE                    100
#define GNSS15_RX_DRV_BUFFER_SIZE                    300

/*! @} */ // gnss15_cmd

/**
 * @defgroup gnss15_map GNSS 15 MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS 15 Click driver.
 */

/**
 * @addtogroup gnss15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS 15 Click to the selected MikroBUS.
 */
#define GNSS15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl    = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda    = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX );  \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX );  \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.irq = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // gnss15_map
/*! @} */ // gnss15

/**
 * @brief GNSS 15 Click driver selector.
 * @details Selects target driver interface of GNSS 15 Click driver.
 */
typedef enum
{
    GNSS15_DRV_SEL_UART,      /**< UART driver descriptor. */
    GNSS15_DRV_SEL_I2C        /**< I2C driver descriptor. */

} gnss15_drv_t;

/**
 * @brief GNSS 15 Click driver interface.
 * @details Definition of driver interface of GNSS 15 Click driver.
 */
typedef err_t ( *gnss15_master_io_t )( struct gnss15_s*, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief GNSS 15 Click context object.
 * @details Context object definition of GNSS 15 Click driver.
 */
typedef struct gnss15_s
{
    // Output pins
    digital_out_t rst;    /**< Reset pin. */
    digital_out_t wup;    /**< Wake-up pin. */

    // Input pins
    digital_in_t irq;     /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;     /**< I2C driver object. */
    uart_t uart;          /**< UART driver object. */

    // Buffers
    uint8_t uart_rx_buffer[ GNSS15_RX_DRV_BUFFER_SIZE ];  /**< Buffer size. */
    uint8_t uart_tx_buffer[ GNSS15_TX_DRV_BUFFER_SIZE ];  /**< Buffer size. */

    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */
    gnss15_drv_t drv_sel;    /**< Master driver interface selector. */
    
    gnss15_master_io_t  write_f;     /**< Master write function. */
    gnss15_master_io_t  read_f;      /**< Master read function. */

} gnss15_t;

/**
 * @brief GNSS 15 Click configuration object.
 * @details Configuration object definition of GNSS 15 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t rx_pin;    /**< RX pin. */
    pin_name_t tx_pin;    /**< TX pin. */
    pin_name_t scl;       /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;       /**< Bidirectional data pin descriptor for I2C driver. */

    // Additional gpio pins
    pin_name_t rst;    /**< Reset pin. */
    pin_name_t wup;    /**< Wake-up pin. */
    pin_name_t irq;    /**< Interrupt pin. */

    // Static variable
    uint32_t         baud_rate;                 /**< Clock speed. */
    bool             uart_blocking;             /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;                  /**< Data bits. */
    uart_parity_t    parity_bit;                /**< Parity bit. */
    uart_stop_bits_t stop_bit;                  /**< Stop bits. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */
    
    gnss15_drv_t drv_sel;    /**< Master driver interface selector. */

} gnss15_cfg_t;

/**
 * @brief GNSS 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSS15_OK = 0,
    GNSS15_ERROR = -1

} gnss15_return_value_t;

/*!
 * @addtogroup gnss15 GNSS 15 Click Driver
 * @brief API for configuring and manipulating GNSS 15 Click driver.
 * @{
 */

/**
 * @brief GNSS 15 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnss15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnss15_cfg_setup ( gnss15_cfg_t *cfg );

/**
 * @brief GNSS 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnss15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss15_init ( gnss15_t *ctx, gnss15_cfg_t *cfg );

/**
 * @brief GNSS 15 data writing function.
 * @details This function writes a desired number of data bytes to the module.
 * @param[in] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss15_generic_write ( gnss15_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS 15 data reading function.
 * @details reads a desired number of data bytes from the module.
 * @param[in] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss15_generic_read ( gnss15_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS 15 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @note None.
 */
void gnss15_set_rst_pin ( gnss15_t *ctx, uint8_t state );

/**
 * @brief GNSS 15 set WUP pin function.
 * @details This function sets the WUP (RWM) pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @note None.
 */
void gnss15_set_wup_pin ( gnss15_t *ctx, uint8_t state );

/**
 * @brief GNSS 15 get interrupt pin state function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnss15_get_interrupt ( gnss15_t *ctx );

/**
 * @brief GNSS 15 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnss15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
void gnss15_reset_device ( gnss15_t *ctx );

/**
 * @brief GNSS 15 parse GPGGA function.
 * @details This function parses the GPGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gpgga_element : GPGGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnss15_parse_gpgga ( uint8_t *rsp_buf, uint8_t gpgga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSS15_H

/*! @} */ // gnss15

// ------------------------------------------------------------------------ END
