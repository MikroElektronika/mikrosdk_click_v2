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
 * @file gnssrtk3ea.h
 * @brief This file contains API for GNSS RTK 3 EA Click Driver.
 */

#ifndef GNSSRTK3EA_H
#define GNSSRTK3EA_H

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
 * @addtogroup gnssrtk3ea GNSS RTK 3 EA Click Driver
 * @brief API for configuring and manipulating GNSS RTK 3 EA Click driver.
 * @{
 */

/**
 * @defgroup gnssrtk3ea_cmd GNSS RTK 3 EA Device Settings
 * @brief Settings for registers of GNSS RTK 3 EA Click driver.
 */

/**
 * @addtogroup gnssrtk3ea_cmd
 * @{
 */

/**
 * @brief GNSS RTK 3 EA response buffer commands.
 * @details Specified response buffer commands of GNSS RTK 3 EA Click driver.
 */
#define GNSSRTK3EA_RSP_START                              "$"
#define GNSSRTK3EA_RSP_DELIMITER                          ","
#define GNSSRTK3EA_RSP_END                                "\r\n"
#define GNSSRTK3EA_RSP_GGA                                "GGA"

/**
 * @brief GNSS RTK 3 EA GGA command elements.
 * @details Specified GGA command elements of GNSS RTK 3 EA Click driver.
 */
#define GNSSRTK3EA_GGA_ELEMENT_SIZE                       15
#define GNSSRTK3EA_GGA_TIME                               1
#define GNSSRTK3EA_GGA_LATITUDE                           2
#define GNSSRTK3EA_GGA_LATITUDE_SIDE                      3
#define GNSSRTK3EA_GGA_LONGITUDE                          4
#define GNSSRTK3EA_GGA_LONGITUDE_SIDE                     5
#define GNSSRTK3EA_GGA_QUALITY_INDICATOR                  6
#define GNSSRTK3EA_GGA_NUMBER_OF_SATELLITES               7
#define GNSSRTK3EA_GGA_H_DILUTION_OF_POS                  8
#define GNSSRTK3EA_GGA_ALTITUDE                           9
#define GNSSRTK3EA_GGA_ALTITUDE_UNIT                      10
#define GNSSRTK3EA_GGA_GEOIDAL_SEPARATION                 11
#define GNSSRTK3EA_GGA_GEOIDAL_SEPARATION_UNIT            12
#define GNSSRTK3EA_GGA_TIME_SINCE_LAST_DGPS               13
#define GNSSRTK3EA_GGA_DGPS_REFERENCE_STATION_ID          14

/**
 * @brief GNSS RTK 3 EA I2C settings.
 * @details Specified setting for I2C of GNSS RTK 3 EA Click driver.
 */
#define GNSSRTK3EA_I2C_SLAVE_CR_CMD                       0xAA51u
#define GNSSRTK3EA_I2C_SLAVE_CW_CMD                       0xAA53u
#define GNSSRTK3EA_I2C_SLAVE_CMD_LEN                      8
#define GNSSRTK3EA_I2C_SLAVE_RX_LEN                       4
#define GNSSRTK3EA_I2C_SLAVE_TX_LEN_REG_OFFSET            0x0008u
#define GNSSRTK3EA_I2C_SLAVE_TX_BUF_REG_OFFSET            0x2000u
#define GNSSRTK3EA_I2C_SLAVE_RX_LEN_REG_OFFSET            0x0004u
#define GNSSRTK3EA_I2C_SLAVE_RX_BUF_REG_OFFSET            0x1000u
#define GNSSRTK3EA_I2C_SLAVE_ADDRESS_CR_OR_CW             0x50
#define GNSSRTK3EA_I2C_SLAVE_ADDRESS_R                    0x54
#define GNSSRTK3EA_I2C_SLAVE_ADDRESS_W                    0x58
#define GNSSRTK3EA_I2C_SLAVE_MAX_ERRORS                   10

/**
 * @brief GNSS RTK 3 EA driver buffer size.
 * @details Specified size of driver ring buffer.
 * @note Increase buffer size if needed.
 */
#define GNSSRTK3EA_TX_DRV_BUFFER_SIZE                     100
#define GNSSRTK3EA_RX_DRV_BUFFER_SIZE                     1000u

/*! @} */ // gnssrtk3ea_cmd

/**
 * @defgroup gnssrtk3ea_map GNSS RTK 3 EA MikroBUS Map
 * @brief MikroBUS pin mapping of GNSS RTK 3 EA Click driver.
 */

/**
 * @addtogroup gnssrtk3ea_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of GNSS RTK 3 EA Click to the selected MikroBUS.
 */
#define GNSSRTK3EA_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl    = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda    = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tx_pin = MIKROBUS( mikrobus, MIKROBUS_TX ); \
    cfg.rx_pin = MIKROBUS( mikrobus, MIKROBUS_RX ); \
    cfg.rst    = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cen    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.wup    = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pps    = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // gnssrtk3ea_map
/*! @} */ // gnssrtk3ea

/**
 * @brief GNSS RTK 3 EA Click driver selector.
 * @details Selects target driver interface of GNSS RTK 3 EA Click driver.
 */
typedef enum
{
    GNSSRTK3EA_DRV_SEL_UART,            /**< UART driver descriptor. */
    GNSSRTK3EA_DRV_SEL_I2C              /**< I2C driver descriptor. */

} gnssrtk3ea_drv_t;

/**
 * @brief GNSS RTK 3 EA Click driver interface.
 * @details Definition of driver interface of GNSS RTK 3 EA Click driver.
 */
struct gnssrtk3ea_s;
typedef err_t ( *gnssrtk3ea_master_io_t )( struct gnssrtk3ea_s*, uint8_t*, uint16_t ); /**< Driver serial interface. */

/**
 * @brief GNSS RTK 3 EA Click context object.
 * @details Context object definition of GNSS RTK 3 EA Click driver.
 */
typedef struct gnssrtk3ea_s
{
    digital_out_t rst;              /**< Reset pin (Active low). */
    digital_out_t cen;              /**< Chip enable pin (Active high). */
    digital_out_t wup;              /**< Wake-up pin (Active high). */
    digital_in_t  pps;              /**< PPS pin. */

    uart_t        uart;             /**< UART driver object. */
    i2c_master_t  i2c;              /**< I2C driver object. */

    uint8_t uart_rx_buffer[ GNSSRTK3EA_RX_DRV_BUFFER_SIZE ];  /**< RX Buffer size. */
    uint8_t uart_tx_buffer[ GNSSRTK3EA_TX_DRV_BUFFER_SIZE ];  /**< TX Buffer size. */
    
    gnssrtk3ea_drv_t drv_sel;         /**< Master driver interface selector. */

    gnssrtk3ea_master_io_t write_f;   /**< Master write function. */
    gnssrtk3ea_master_io_t read_f;    /**< Master read function. */

} gnssrtk3ea_t;

/**
 * @brief GNSS RTK 3 EA Click configuration object.
 * @details Configuration object definition of GNSS RTK 3 EA Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t rx_pin;              /**< RX pin. */
    pin_name_t tx_pin;              /**< TX pin. */
    pin_name_t rst;                 /**< Reset pin (Active low). */
    pin_name_t cen;                 /**< Chip enable pin (Active high). */
    pin_name_t wup;                 /**< Wake-up pin (Active high). */
    pin_name_t pps;                 /**< PPS pin (Active high). */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */
    
    uint32_t         baud_rate;     /**< Clock speed. */
    bool             uart_blocking; /**< Wait for interrupt or not. */
    uart_data_bits_t data_bit;      /**< Data bits. */
    uart_parity_t    parity_bit;    /**< Parity bit. */
    uart_stop_bits_t stop_bit;      /**< Stop bits. */
    
    gnssrtk3ea_drv_t   drv_sel;       /**< Master driver interface selector. */

} gnssrtk3ea_cfg_t;

/**
 * @brief GNSS RTK 3 EA Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    GNSSRTK3EA_OK = 0,
    GNSSRTK3EA_ERROR = -1

} gnssrtk3ea_return_value_t;

/*!
 * @addtogroup gnssrtk3ea GNSS RTK 3 EA Click Driver
 * @brief API for configuring and manipulating GNSS RTK 3 EA Click driver.
 * @{
 */

/**
 * @brief GNSS RTK 3 EA configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #gnssrtk3ea_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void gnssrtk3ea_cfg_setup ( gnssrtk3ea_cfg_t *cfg );

/**
 * @brief GNSS RTK 3 EA driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #gnssrtk3ea_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #gnssrtk3ea_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void gnssrtk3ea_drv_interface_sel ( gnssrtk3ea_cfg_t *cfg, gnssrtk3ea_drv_t drv_sel );

/**
 * @brief GNSS RTK 3 EA initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #gnssrtk3ea_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #gnssrtk3ea_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk3ea_init ( gnssrtk3ea_t *ctx, gnssrtk3ea_cfg_t *cfg );

/**
 * @brief GNSS RTK 3 EA data writing function.
 * @details This function writes a desired number of data bytes by using UART or I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssrtk3ea_t object definition for detailed explanation.
 * @param[in] data_in : Data buffer for sending.
 * @param[in] len : Number of bytes for sending.
 * @return @li @c  >=0 - Success,
 *         @li @c   <0 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk3ea_generic_write ( gnssrtk3ea_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief GNSS RTK 3 EA data reading function.
 * @details This function reads a desired number of data bytes by using UART or I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gnssrtk3ea_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  >0 - Number of data bytes read,
 *         @li @c <=0 - Error/Empty Ring buffer.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk3ea_generic_read ( gnssrtk3ea_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief GNSS RTK 3 EA set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk3ea_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssrtk3ea_set_rst_pin ( gnssrtk3ea_t *ctx, uint8_t state );

/**
 * @brief GNSS RTK 3 EA set CEN pin function.
 * @details This function sets the CEN pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk3ea_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssrtk3ea_set_cen_pin ( gnssrtk3ea_t *ctx, uint8_t state );

/**
 * @brief GNSS RTK 3 EA set WUP pin function.
 * @details This function sets the WUP pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk3ea_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void gnssrtk3ea_set_wup_pin ( gnssrtk3ea_t *ctx, uint8_t state );

/**
 * @brief GNSS RTK 3 EA get PPS pin function.
 * @details This function returns the PPS pin logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk3ea_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t gnssrtk3ea_get_pps_pin ( gnssrtk3ea_t *ctx );

/**
 * @brief GNSS RTK 3 EA enable device function.
 * @details This function enables the device by setting the CEN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk3ea_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnssrtk3ea_enable_device ( gnssrtk3ea_t *ctx );

/**
 * @brief GNSS RTK 3 EA disable device function.
 * @details This function disables the device by setting the CEN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #gnssrtk3ea_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnssrtk3ea_disable_device ( gnssrtk3ea_t *ctx );

/**
 * @brief GNSS RTK 3 EA reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #gnssrtk3ea_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void gnssrtk3ea_reset_device ( gnssrtk3ea_t *ctx );

/**
 * @brief GNSS RTK 3 EA parse GGA function.
 * @details This function parses the GGA data from the read response buffer.
 * @param[in] rsp_buf : Response buffer.
 * @param[in] gga_element : GGA element position [1-14].
 * @param[out] element_data : Element data parsed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t gnssrtk3ea_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );

#ifdef __cplusplus
}
#endif
#endif // GNSSRTK3EA_H

/*! @} */ // gnssrtk3ea

// ------------------------------------------------------------------------ END
