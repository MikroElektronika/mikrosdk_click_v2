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
 * @file charger11.h
 * @brief This file contains API for Charger 11 Click Driver.
 */

#ifndef CHARGER11_H
#define CHARGER11_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup charger11 Charger 11 Click Driver
 * @brief API for configuring and manipulating Charger 11 Click driver.
 * @{
 */

/**
 * @defgroup charger11_reg Charger 11 Registers List
 * @brief List of registers of Charger 11 Click driver.
 */

/**
 * @addtogroup charger11_reg
 * @{
 */

/**
 * @brief Charger 11 description register.
 * @details Specified register for description of Charger 11 Click driver.
 */
#define CHARGER11_SPI_VOLATILE_WIPER_0       0x00
#define CHARGER11_SPI_VOLATILE_WIPER_1       0x01
#define CHARGER11_SPI_NON_VOLATILE_WIPER_0   0x02
#define CHARGER11_SPI_NON_VOLATILE_WIPER_1   0x03
#define CHARGER11_SPI_VOLATILE_TCON          0x04
#define CHARGER11_SPI_STATUS_REGISTER        0x05
#define CHARGER11_SPI_DATA_EEPROM_0          0x06
#define CHARGER11_SPI_DATA_EEPROM_1          0x07
#define CHARGER11_SPI_DATA_EEPROM_2          0x08
#define CHARGER11_SPI_DATA_EEPROM_3          0x09
#define CHARGER11_SPI_DATA_EEPROM_4          0x0A
#define CHARGER11_SPI_DATA_EEPROM_5          0x0B
#define CHARGER11_SPI_DATA_EEPROM_6          0x0C
#define CHARGER11_SPI_DATA_EEPROM_7          0x0D
#define CHARGER11_SPI_DATA_EEPROM_8          0x0E
#define CHARGER11_SPI_DATA_EEPROM_9          0x0F

/*! @} */ // charger11_reg

/**
 * @defgroup charger11_set Charger 11 Registers Settings
 * @brief Settings for registers of Charger 11 Click driver.
 */

/**
 * @addtogroup charger11_set
 * @{
 */

/**
 * @brief Charger 11 description setting.
 * @details Specified setting for description of Charger 11 Click driver.
 */
#define CHARGER11_PIN_ENABE                  0x01
#define CHARGER11_PIN_DISABLE                0x00

/**
 * @brief Charger 11 device address setting.
 * @details Specified setting for device slave address selection of
 * Charger 11 Click driver.
 */
#define CHARGER11_SET_DEV_ADDR  0x4D

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b charger11_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define CHARGER11_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define CHARGER11_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // charger11_set

/**
 * @defgroup charger11_map Charger 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 11 Click driver.
 */

/**
 * @addtogroup charger11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 11 Click to the selected MikroBUS.
 */
#define CHARGER11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.lr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.lg = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.st = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // charger11_map
/*! @} */ // charger11

/**
 * @brief Charger 11 Click context object.
 * @details Context object definition of Charger 11 Click driver.
 */
typedef struct charger11_s
{
    digital_out_t  lr;          /**< Red LED Indicator. */
    digital_out_t  lg;          /**< Green LED Indicator. */

    digital_in_t  st;           /**< Description. */

    i2c_master_t  i2c;          /**< I2C driver object. */
    spi_master_t  spi;          /**< SPI driver object. */

    uint8_t     slave_address;  /**< Device slave address (used for I2C driver). */
    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */
   
} charger11_t;

/**
 * @brief Charger 11 Click configuration object.
 * @details Configuration object definition of Charger 11 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */
    pin_name_t  lr;         /**< Red LED Indicator. */
    pin_name_t  lg;         /**< Green LED Indicator. */
    pin_name_t  st;         /**< Status Out. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

    uint32_t                           spi_speed;       /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;        /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;     /**< Chip select pin polarity. */

} charger11_cfg_t;

/**
 * @brief Charger 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   CHARGER11_OK = 0,
   CHARGER11_ERROR = -1

} charger11_return_value_t;

/*!
 * @addtogroup charger11 Charger 11 Click Driver
 * @brief API for configuring and manipulating Charger 11 Click driver.
 * @{
 */

/**
 * @brief Charger 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger11_cfg_setup ( charger11_cfg_t *cfg );

/**
 * @brief Charger 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t charger11_init ( charger11_t *ctx, charger11_cfg_t *cfg );

/**
 * @brief Charger 11 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t charger11_i2c_write ( charger11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Charger 11 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t charger11_i2c_read ( charger11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Charger 11 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t charger11_spi_write ( charger11_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Charger 11 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t charger11_spi_read ( charger11_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Charger 11 getting INT pin state
 * @details This function returns INT pin state.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @returns INT pin state.
 */
uint8_t charger11_get_int( charger11_t *ctx );

/**
 * @brief Charger 11 setting AN pin state
 * @details This function sets AN pin state.
 * @param[out] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @param[in] pin_state : AN pin state (0 for LOW or 1 for HIGH).
 * @return Nothing.
 */
void charger11_lr_set( charger11_t *ctx, uint8_t pin_state );

/**
 * @brief Charger 11 Setting PWM pin state
 * @details This function sets PWM pin state
 * @param[out] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @param[in] pin_state : PWM pin state (0 for LOW or 1 for HIGH).
 * @return Nothing.
 */
void charger11_lg_set( charger11_t *ctx, uint8_t pin_state );

/**
 * @brief Charger 11 transfering bytes via SPI.
 * @details This function transfers bytes via SPI to MCP4161 device.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to transfer.
 * @return Nothing.
 */
void charger11_spi_transfer( charger11_t *ctx, uint8_t *data_in, uint8_t *data_out, 
                             uint8_t len );

/**
 * @brief Charger 11 setting register.
 * @details This function sets register value, and sends commands to MCP4161 device.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @param[in] register_address : Register address.
 * @param[in] register_value : Data to be written.
 * @return Nothing.
 */
void charger11_spi_set_register( charger11_t *ctx, uint8_t register_address, 
                                 uint16_t register_value );

/**
 * @brief Charger 11 getting register value.
 * @details This function gets register value of MCP4161 device.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @param[in] register_address : Register address.
 * @param[out] register_value : Address of a variable to store register value.
 * @return Nothing.
 */
void charger11_spi_get_register( charger11_t *ctx, uint8_t register_address, 
                                 uint16_t * register_value );

/**
 * @brief Charger 11 incrementing wiper position.
 * @details This function increments wiper position by sending 8bit increment wiper command.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @return Nothing.
 */
void charger11_spi_increment_wiper( charger11_t *ctx );

/**
 * @brief Charger 11 decrementing wiper position.
 * @details This function decrements wiper position by sending 8bit decrement wiper command.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @return Nothing.
 */
void charger11_spi_decrement_wiper( charger11_t *ctx );

/**
 * @brief Charger 11 getting wiper position.
 * @details This function returns wiper position.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @returns Wiper position.
 */
uint8_t charger11_spi_get_wiper_position( charger11_t *ctx );

/**
 * @brief Charger 11 getting raw ADC data.
 * @details This function returns raw ADC data.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @returns ADC data.
 */
uint16_t charger11_i2c_get_raw_data( charger11_t *ctx );

/**
 * @brief Charger 11 getting output voltage.
 * @details This function gets raw ADC data and converts it to voltage based on reference voltage.
 * @param[in] ctx : Click context object.
 * See #charger11_t object definition for detailed explanation.
 * @param[in] reference_voltage : Voltage measured on 12bit ADC converter (MCP3221A5T) VDD pin.
 * @returns Output voltage in [V] or [mV].
 *
 * @note This function returns value in [V] if reference voltage is in [V].
 */
float charger11_i2c_get_volt( charger11_t *ctx, float reference_voltage );

#ifdef __cplusplus
}
#endif
#endif // CHARGER11_H

/*! @} */ // charger11

// ------------------------------------------------------------------------ END
