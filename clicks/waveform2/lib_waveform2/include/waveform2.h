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
 * @file waveform2.h
 * @brief This file contains API for Waveform 2 Click Driver.
 */

#ifndef WAVEFORM2_H
#define WAVEFORM2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup waveform2 Waveform 2 Click Driver
 * @brief API for configuring and manipulating Waveform 2 Click driver.
 * @{
 */

/**
 * @defgroup waveform2_set Waveform 2 Registers Settings
 * @brief Settings for registers of Waveform 2 Click driver.
 */

/**
 * @addtogroup waveform2_set
 * @{
 */

/**
 * @brief Waveform 2 description setting.
 * @details Specified setting for description of Waveform 2 Click driver.
 */
#define WAVEFORM2_CFG_B28_MSK             0x2000
#define WAVEFORM2_CFG_HLB_MSK             0x1000
#define WAVEFORM2_CFG_FSEL_MSK            0x0800
#define WAVEFORM2_CFG_PSEK_MSK            0x0400
#define WAVEFORM2_CFG_PIN_SW_MSK          0x0200
#define WAVEFORM2_CFG_RESET_MSK           0x0100
#define WAVEFORM2_CFG_SLEEP1_MSK          0x0080
#define WAVEFORM2_CFG_SLEEP12_MSK         0x0040
#define WAVEFORM2_CFG_OPBITEN_MSK         0x0020
#define WAVEFORM2_CFG_SIGN_PIB_MSK        0x0010
#define WAVEFORM2_CFG_DIV2_MSK            0x0008
#define WAVEFORM2_CFG_MODE_MSK            0x0002

#define OUTPUT_TRIANGLE                   0x01
#define OUTPUT_SINUSOID                   0x00

/**
 * @brief Waveform 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Waveform 2 Click driver.
 */
#define WAVEFORM2_DEVICE_SLAVE_ADDR_GND   0x50
#define WAVEFORM2_DEVICE_SLAVE_ADDR_VCC   0x51

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b waveform2_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define WAVEFORM2_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define WAVEFORM2_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // waveform2_set

/**
 * @defgroup waveform2_map Waveform 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Waveform 2 Click driver.
 */

/**
 * @addtogroup waveform2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Waveform 2 Click to the selected MikroBUS.
 */
#define WAVEFORM2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // waveform2_map
/*! @} */ // waveform2

/**
 * @brief Waveform 2 Click context object.
 * @details Context object definition of Waveform 2 Click driver.
 */
typedef struct waveform2_s
{
    digital_out_t  rst;     /**< Reset. */
    digital_out_t  en;      /**< Enable. */
 
    i2c_master_t  i2c;                              /**< I2C driver object. */
    spi_master_t  spi;                              /**< SPI driver object. */

    uint8_t     slave_address;                      /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;                        /**< Chip select pin descriptor (used for SPI driver). */
   
    uint8_t mode_output; 

} waveform2_t;

/**
 * @brief Waveform 2 Click configuration object.
 * @details Configuration object definition of Waveform 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  rst;        /**< Reset. */
    pin_name_t  en;         /**< Enable. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} waveform2_cfg_t;

/**
 * @brief Waveform 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   WAVEFORM2_OK = 0,
   WAVEFORM2_ERROR = -1

} waveform2_return_value_t;

/*!
 * @addtogroup waveform2 Waveform 2 Click Driver
 * @brief API for configuring and manipulating Waveform 2 Click driver.
 * @{
 */

/**
 * @brief Waveform 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #waveform2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void waveform2_cfg_setup ( waveform2_cfg_t *cfg );

/**
 * @brief Waveform 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #waveform2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t waveform2_init ( waveform2_t *ctx, waveform2_cfg_t *cfg );

/**
 * @brief Waveform 2 default configuration function.
 * @details This function executes a default configuration of Waveform 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t waveform2_default_cfg ( waveform2_t *ctx );

/**
 * @brief Waveform 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t waveform2_i2c_write ( waveform2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Waveform 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t waveform2_i2c_read ( waveform2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Waveform 2 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t waveform2_spi_write ( waveform2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Waveform 2 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t waveform2_spi_read ( waveform2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Waveform 2 read byte function.
 * @details Finction for reading a byte from the on board EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] addr : EEPROM Address.
 * @return 8-bit read data.
 */
uint8_t waveform2_eeprom_read_byte ( waveform2_t *ctx, uint16_t addr );

/**
 * @brief Waveform 2 read word function.
 * @details Finction for reading a word from the on board EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] addr : EEPROM Address.
 * @return 16-bit read data.
 */
uint16_t waveform2_eeprom_read_word ( waveform2_t *ctx, uint16_t addr );

/**
 * @brief Waveform 2 read long function.
 * @details Finction for reading a long word from the on board EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] addr : EEPROM Address.
 * @return 32-bit read data.
 */
uint32_t waveform2_eeprom_read_long ( waveform2_t *ctx, uint16_t addr );

/**
 * @brief Waveform 2 read string function.
 * @details Finction for reading a string from the on board EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] addr : EEPROM Address.
 * @param[out] data_buf : Data buffer.
 * @param[in] len : Number of data in the buffer.
 * @return Nothing.
 */
void waveform2_eeprom_read_string ( waveform2_t *ctx, uint16_t addr, uint8_t *data_buf, uint16_t len );

/**
 * @brief Waveform 2 write bute function.
 * @details Function for writing a byte to the on board EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] addr : EEPROM Address.
 * @param[in] tx_data : (uint8_t) Data. 
 * @return Nothing.
 */
void waveform2_eeprom_write_byte ( waveform2_t *ctx, uint16_t addr, uint8_t tx_data );

/**
 * @brief Waveform 2 write word function.
 * @details Function for writing a word to the on board EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] addr : EEPROM Address.
 * @param[in] tx_data (uint16_t) Data.
 * @return Nothing.
 */
void waveform2_eeprom_write_word ( waveform2_t *ctx, uint16_t addr, uint16_t tx_data );

/**
 * @brief Waveform 2 write long function.
 * @details Function for writing a long word to the on board EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] addr : EEPROM Address.
 * @param[in] tx_data (uint32_t) Data.
 * @return Nothing.
 */
void waveform2_eeprom_write_long ( waveform2_t *ctx, uint16_t addr, uint32_t tx_data );

/**
 * @brief Waveform 2 write string function.
 * @details Function for writing a string to the on board EEPROM memory.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] addr : EEPROM Address.
 * @param[in] data_buf : Data buffer.
 * @param[in] len : Number of data for read.
 * @return Nothing.
 */
void waveform2_eeprom_write_string ( waveform2_t *ctx, uint16_t addr, uint8_t *data_buf, uint16_t len );

/**
 * @brief Waveform 2 enable oscilator function.
 * @details Function for enabling the on board main 50MHz oscilator.
 * @param[out] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @return Nothing.
 */
void waveform2_mclk_enable ( waveform2_t *ctx );

/**
 * @brief Waveform 2 disable oscilator function.
 * @details Function for disabling the on board main 50MHz oscilator.
 * @param[out] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @return Nothing.
 */
void waveform2_mclk_disable ( waveform2_t *ctx );

/**
 * @brief Waveform 2 hardware reset function.
 * @details Function for performing a hardware reset of the click board.
 * @param[out] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @return Nothing.
 */
void waveform2_hw_reset ( waveform2_t *ctx );

/**
 * @brief Waveform 2 set frequency function.
 * @details Function for setting the output frequency.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] freq : Frequency data.
 * @return Nothing.
 */
void waveform2_set_freq ( waveform2_t *ctx, uint32_t freq );

/**
 * @brief Waveform 2 configuration function.
 * @details Function for writing to the config register.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @param[in] cfg : Configuration.
 * @return Nothing.
 */
void waveform2_configuration ( waveform2_t *ctx, uint16_t cfg );

/**
 * @brief Waveform 2 set sine output function.
 * @details Function for setting the sine output.
 * @param[out] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @return Nothing.
 */
void waveform2_sine_output ( waveform2_t *ctx );

/**
 * @brief Waveform 2 set triangle output function.
 * @details Function for setting the triangle output.
 * @param[out] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @return Nothing.
 */
void waveform2_triangle_output ( waveform2_t *ctx );

/**
 * @brief Waveform 2 disable output function.
 * @details Function for disabling the output.
 * @param[in] ctx : Click context object.
 * See #waveform2_t object definition for detailed explanation.
 * @return Nothing.
 */
void waveform2_output_off ( waveform2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // WAVEFORM2_H

/*! @} */ // waveform2

// ------------------------------------------------------------------------ END
