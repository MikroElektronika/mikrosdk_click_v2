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
 * @file nanogps3.h
 * @brief This file contains API for Nano GPS 3 Click Driver.
 */

#ifndef NANOGPS3_H
#define NANOGPS3_H

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
 * @addtogroup nanogps3 Nano GPS 3 Click Driver
 * @brief API for configuring and manipulating Nano GPS 3 Click driver.
 * @{
 */

/**
 * @defgroup nanogps3_reg Nano GPS 3 Registers List
 * @brief List of registers of Nano GPS 3 Click driver.
 */

/**
 * @addtogroup nanogps3_reg
 * @{
 */

/**
 * @brief Nano GPS 3 description register.
 * @details Specified register for description of Nano GPS 3 Click driver.
 */


/*! @} */ // nanogps3_reg

/**
 * @defgroup nanogps3_set Nano GPS 3 Registers Settings
 * @brief Settings for registers of Nano GPS 3 Click driver.
 */

/**
 * @addtogroup nanogps3_set
 * @{
 */

/**
 * @brief Nano GPS 3 description setting.
 * @details Specified setting for description of Nano GPS 3 Click driver.
 */


/**
 * @brief Nano GPS 3 response buffer commands.
 * @details Specified response buffer commands of Nano GPS 3 Click driver.
 */
#define NANOGPS3_RSP_START                      "$"
#define NANOGPS3_RSP_DELIMITER                  ","
#define NANOGPS3_RSP_GNGGA                      "$GNGGA"
#define NANOGPS3_RSP_GPGLL                      "$GPGLL"

/**
 * @brief Nano GPS 3 current support NEMA command.
 * @details Specified current support NEMA command of Nano GPS 3 Click driver.
 */
#define NANOGPS3_NMEA_GNGGA                      1
#define NANOGPS3_NMEA_GPGLL                      3
#define NANOGPS3_NMEA_GNGGA_NUM_ELEMENT          15
#define NANOGPS3_NMEA_GPGLL_NUM_ELEMENT          5

/**
 * @brief Nano GPS 3 GPGGA command elements.
 * @details Specified GPGGA command elements of Nano GPS 3 Click driver.
 */
#define NANOGPS3_GNGGA_TIME                      1 
#define NANOGPS3_GNGGA_LATITUDE                  2
#define NANOGPS3_GNGGA_LATITUDE_SIDE             3
#define NANOGPS3_GNGGA_LONGITUDE                 4
#define NANOGPS3_GNGGA_LONGITUDE_SIDE            5
#define NANOGPS3_GNGGA_QUALITY_INDICATOR         6
#define NANOGPS3_GNGGA_NUMBER_OF_SATELLITES      7
#define NANOGPS3_GNGGA_H_DILUTION_OF_POS         8
#define NANOGPS3_GNGGA_ALTITUDE                  9
#define NANOGPS3_GNGGA_ALTITUDE_UNIT             10
#define NANOGPS3_GNGGA_GEOIDAL_SEPARATION        11
#define NANOGPS3_GNGGA_GEOIDAL_SEPARATION_UNIT   12
#define NANOGPS3_GNGGA_TIME_SINCE_LAST_DGPS      13
#define NANOGPS3_GNGGA_DGPS_REFERENCE_STATION_ID 14

/**
 * @brief Nano GPS 3 Dummy data.
 * @details Specified dummy data of Nano GPS 3 Click driver.
 */
#define NANOGPS3_DUMMY                           0xFF

/**
 * @brief Nano GPS 3 GPIO pin logic values.
 * @details Specified GPIO pin logic values of Nano GPS 3 Click driver.
 */
#define NANOGPS3_PIN_STATE_LOW                    0
#define NANOGPS3_PIN_STATE_HIGH                   1

/**
 * @brief Nano GPS 3 driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define NANOGPS3_TX_DRV_BUFFER_SIZE              100
#define NANOGPS3_RX_DRV_BUFFER_SIZE              600

/**
 * @brief Nano GPS 3 device address setting.
 * @details Specified setting for device slave address selection of
 * Nano GPS 3 Click driver.
 */
#define NANOGPS3_DEVICE_ADDRESS                  0x10

/*! @} */ // nanogps3_set

/**
 * @defgroup nanogps3_map Nano GPS 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Nano GPS 3 Click driver.
 */

/**
 * @addtogroup nanogps3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Nano GPS 3 Click to the selected MikroBUS.
 */
#define NANOGPS3_MAP_MIKROBUS( cfg, mikrobus )       \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL );    \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA );    \
    cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS );     \
    cfg.wup = MIKROBUS( mikrobus, MIKROBUS_AN );     \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.fon = MIKROBUS( mikrobus, MIKROBUS_PWM );    \
    cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nanogps3_map
/*! @} */ // nanogps3

/**
 * @brief Nano GPS 3 Click driver selector.
 * @details Selects target driver interface of Nano GPS 3 Click driver.
 */
typedef enum
{
    NANOGPS3_DRV_SEL_I2C,       /**< I2C driver descriptor. */
    NANOGPS3_DRV_SEL_UART       /**< UART driver descriptor. */

} nanogps3_drv_t;

/**
 * @brief Nano GPS 3 Click driver interface.
 * @details Definition of driver interface of Nano GPS 3 Click driver.
 */
typedef err_t ( *nanogps3_master_io_t )( struct nanogps3_s*, uint8_t*, uint8_t ); /**< Driver serial interface. */

/**
 * @brief Nano GPS 3 Click context object.
 * @details Context object definition of Nano GPS 3 Click driver.
 */
typedef struct nanogps3_s
{
    // Output pins
    digital_out_t rts;    /**< Request to send pin. */
    digital_out_t rst;    /**< Reset pin. */
    digital_out_t fon;    /**< Power state pin. */

    // Input pins
    digital_in_t wup;     /**< Wakeup pin. */
    digital_in_t cts;     /**< Clear to send pin. */

    // Modules
    i2c_master_t i2c;     /**< I2C driver object. */
    uart_t uart;          /**< UART driver object. */

    // I2C slave address
    uint8_t slave_address;    /**< Device slave address (used for I2C driver). */
    
    // Buffers
    char uart_rx_buffer[ NANOGPS3_RX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    char uart_tx_buffer[ NANOGPS3_TX_DRV_BUFFER_SIZE ];    /**< Buffer size. */
    
    nanogps3_drv_t drv_sel;          /**< Master driver interface selector. */
    nanogps3_master_io_t write_f;    /**< Master write function. */
    nanogps3_master_io_t read_f;     /**< Master read function. */

} nanogps3_t;

/**
 * @brief Nano GPS 3 Click configuration object.
 * @details Configuration object definition of Nano GPS 3 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;       /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;       /**< Bidirectional data pin descriptor for I2C driver. */
    
    pin_name_t rx_pin;    /**< RX pin. */
    pin_name_t tx_pin;    /**< TX pin. */

    pin_name_t rts;       /**< Reset pin. */
    pin_name_t wup;       /**< Wakeup pin. */
    pin_name_t rst;       /**< Request to send pin. */
    pin_name_t fon;       /**< Power state pin. */
    pin_name_t cts;       /**< Clear to send pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */
    
    // Static variable
    uint32_t         baud_rate;        /**< Clock speed. */
    bool             uart_blocking;    /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;         /**< Data bits. */
    uart_parity_t    parity_bit;       /**< Parity bit. */
    uart_stop_bits_t stop_bit;         /**< Stop bits. */
    
    nanogps3_drv_t drv_sel;            /**< Master driver interface selector. */

} nanogps3_cfg_t;

/**
 * @brief Nano GPS 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NANOGPS3_OK = 0,
    NANOGPS3_ERROR = -1

} nanogps3_return_value_t;

/*!
 * @addtogroup nanogps3 Nano GPS 3 Click Driver
 * @brief API for configuring and manipulating Nano GPS 3 Click driver.
 * @{
 */

/**
 * @brief Nano GPS 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nanogps3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nanogps3_cfg_setup ( nanogps3_cfg_t *cfg );

/**
 * @brief Nano GPS 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nanogps3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanogps3_init ( nanogps3_t *ctx, nanogps3_cfg_t *cfg );

/**
 * @brief Nano GPS 3 default configuration function.
 * @details This function executes a default configuration of Nano GPS 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void nanogps3_default_cfg ( nanogps3_t *ctx );

/**
 * @brief Nano GPS 3 data writing function.
 * @details This function writes a desired number of data to the module.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanogps3_generic_write ( nanogps3_t *ctx, uint8_t *data_in, uint8_t len );

/**
 * @brief Nano GPS 3 data reading function.
 * @details This function reads a desired number of data bytes from the module.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanogps3_generic_read ( nanogps3_t *ctx, uint8_t *data_out, uint8_t len );

/**
 * @brief Nano GPS 3 request to send function.
 * @details This function is flow control and uses to sets the request to send logic state
 * of the Nano GPS 3 click board™.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @param[in] cts : Request to send state.
 * @return Nothing.
 * @note None.
 */
void nanogps3_request_to_send ( nanogps3_t *ctx, uint8_t rts );

/**
 * @brief Nano GPS 3 clear to send function.
 * @details This function is flow control and uses to get the clear to send logic state
 * of the Nano GPS 3 click board™.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @return Status of the clear to send.
 * @note None.
 */
uint8_t nanogps3_clear_to_send ( nanogps3_t *ctx );

/**
 * @brief Nano GPS 3 set reset state function.
 * @details This function sets RST pin logic state 
 * of the Nano GPS 3 click board™.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @param[in] rst_state : Reset pin states.
 * @return Nothing.
 * @note None.
 */
void nanogps3_set_reset_state ( nanogps3_t *ctx, uint8_t rst_state );

/**
 * @brief Nano GPS 3 set force on state function.
 * @details This function controls the power states
 * of the Nano GPS 3 click board™.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @param[in] pwr_state : Power pin states.
 * @return Nothing.
 * @note None.
 */
void nanogps3_set_force_on_state ( nanogps3_t *ctx, uint8_t pwr_state );

/**
 * @brief Nano GPS 3 get wakeup pin function.
 * @details This function get logic states of the WUP pin
 * of the Nano GPS 3 click board™.
 * @param[in] ctx : Click context object.
 * See #nanogps3_t object definition for detailed explanation.
 * @return WUP pin logic state.
 * @note None.
 */
uint8_t nanogps3_get_wup_pin ( nanogps3_t *ctx );

/**
 * @brief Nano GPS 3 parse GNGGA function.
 * @details This function parses the GNGGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gngga_element : Element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nanogps3_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data );

#ifdef __cplusplus
}
#endif
#endif // NANOGPS3_H

/*! @} */ // nanogps3

// ------------------------------------------------------------------------ END
