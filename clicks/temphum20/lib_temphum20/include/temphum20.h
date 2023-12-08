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
 * @file temphum20.h
 * @brief This file contains API for TempHum 20 Click Driver.
 */

#ifndef TEMPHUM20_H
#define TEMPHUM20_H

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

/*!
 * @addtogroup temphum20 TempHum 20 Click Driver
 * @brief API for configuring and manipulating TempHum 20 Click driver.
 * @{
 */

/**
 * @defgroup temphum20_reg TempHum 20 Registers List
 * @brief List of registers of TempHum 20 Click driver.
 */

/**
 * @addtogroup temphum20_reg
 * @{
 */

/**
 * @brief TempHum 20 EEPROM Word Assignments.
 * @details Specified registers in EEPROM of TempHum 20 Click driver.
 */
#define TEMPHUM20_REG_PDM_CLIP_HIGH         0x16
#define TEMPHUM20_REG_PDM_CLIP_LOW          0x17
#define TEMPHUM20_REG_ALARM_HIGH_ON         0x18
#define TEMPHUM20_REG_ALARM_HIGH_OFF        0x19
#define TEMPHUM20_REG_ALARM_LOW_ON          0x1A
#define TEMPHUM20_REG_ALARM_LOW_OFF         0x1B
#define TEMPHUM20_REG_CUST_CONFIG           0x1C
#define TEMPHUM20_REG_RESERVED              0x1D
#define TEMPHUM20_REG_CUST_ID2              0x1E
#define TEMPHUM20_REG_CUST_ID3              0x1F
#define TEMPHUM20_CMD_START_NOM             0x80
#define TEMPHUM20_CMD_START_CM              0xA0

/*! @} */ // temphum20_reg

/**
 * @defgroup temphum20_set TempHum 20 Registers Settings
 * @brief Settings for registers of TempHum 20 Click driver.
 */

/**
 * @addtogroup temphum20_set
 * @{
 */

/**
 * @brief TempHum 20 Temperature and Humidity calculation values.
 * @details Specified setting for Temperature and Humidity calculation of TempHum 20 Click driver.
 */
#define TEMPHUM20_DATA_RESOLUTION           0x4000
#define TEMPHUM20_TEMP_MULTIPLIER           165.0
#define TEMPHUM20_HUM_MULTIPLIER            100.0
#define TEMPHUM20_TEMP_OFFSET               40.0

/**
 * @brief TempHum 20 Status bits values.
 * @details Specified Status bits values of TempHum 20 Click driver.
 */
#define TEMPHUM20_STATUS_BITS_MASK          0xC0
#define TEMPHUM20_STATUS_VALID_DATA         0x00
#define TEMPHUM20_STATUS_STALE_DATA         0x40
#define TEMPHUM20_STATUS_COMMAND_MODE       0x80

/**
 * @brief TempHum 20 operating mode values.
 * @details Specified operating mode values of TempHum 20 Click driver.
 */
#define TEMPHUM20_OPMODE_COMMAND            0x00
#define TEMPHUM20_OPMODE_NORMAL             0x01

/**
 * @brief TempHum 20 dummy value.
 * @details Specified dummy value of TempHum 20 Click driver.
 */
#define TEMPHUM20_DUMMY                     0x0000

/**
 * @brief TempHum 20 device address setting.
 * @details Specified setting for device slave address selection of
 * TempHum 20 Click driver.
 */
#define TEMPHUM20_SET_DEV_ADDR              0x28

/*! @} */ // temphum20_set

/**
 * @defgroup temphum20_map TempHum 20 MikroBUS Map
 * @brief MikroBUS pin mapping of TempHum 20 Click driver.
 */

/**
 * @addtogroup temphum20_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TempHum 20 Click to the selected MikroBUS.
 */
#define TEMPHUM20_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alh = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en  = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.all = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // temphum20_map
/*! @} */ // temphum20

/**
 * @brief TempHum 20 Click context object.
 * @details Context object definition of TempHum 20 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin. */
    
    // Input pins
    digital_in_t  alh;          /**< Alarm High pin. */
    digital_in_t  all;          /**< Alarm Low pin. */
    digital_in_t  int_pin;      /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} temphum20_t;

/**
 * @brief TempHum 20 Click configuration object.
 * @details Configuration object definition of TempHum 20 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;             /**< Enable pin. */
    pin_name_t  alh;            /**< Alarm High pin. */
    pin_name_t  all;            /**< Alarm Low pin. */
    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} temphum20_cfg_t;

/**
 * @brief TempHum 20 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TEMPHUM20_OK = 0,
    TEMPHUM20_ERROR = -1

} temphum20_return_value_t;

/*!
 * @addtogroup temphum20 TempHum 20 Click Driver
 * @brief API for configuring and manipulating TempHum 20 Click driver.
 * @{
 */

/**
 * @brief TempHum 20 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #temphum20_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void temphum20_cfg_setup ( temphum20_cfg_t *cfg );

/**
 * @brief TempHum 20 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #temphum20_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum20_init ( temphum20_t *ctx, temphum20_cfg_t *cfg );

/**
 * @brief TempHum 20 default configuration function.
 * @details This function executes a default configuration of TempHum 20
 * click board.
 * @param[in] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t temphum20_default_cfg ( temphum20_t *ctx );

/**
 * @brief TempHum 20 I2C writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum20_write_data ( temphum20_t *ctx, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief TempHum 20 I2C reading function.
 * @details This function reads a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum20_read_data ( temphum20_t *ctx, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief TempHum 20 set EN pin function.
 * @details This function sets the EN pin to a desired logic state.
 * @param[in] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void temphum20_set_en_pin ( temphum20_t *ctx, uint8_t state );

/**
 * @brief TempHum 20 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t temphum20_get_int_pin ( temphum20_t *ctx );

/**
 * @brief TempHum 20 get alarm high pin function.
 * @details This function returns the alarm high (ALH) pin logic state.
 * @param[in] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t temphum20_get_alarm_high_pin ( temphum20_t *ctx );

/**
 * @brief TempHum 20 get alarm low pin function.
 * @details This function returns the alarm low (ALL) pin logic state.
 * @param[in] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t temphum20_get_alarm_low_pin ( temphum20_t *ctx );

/**
 * @brief TempHum 20 reset device function.
 * @details This function resets the device by toggling the EN pin.
 * @param[in] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void temphum20_reset_device ( temphum20_t *ctx );

/**
 * @brief TempHum 20 write command function.
 * @details This function writes a desired command data to the selected command byte.
 * @param[in] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @param[in] cmd_byte : Command byte.
 * @param[in] cmd_data : Command data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum20_write_command ( temphum20_t *ctx, uint8_t cmd_byte, uint16_t cmd_data );

/**
 * @brief TempHum 20 get measurement function.
 * @details This function waits for the data to be ready, and then reads the temperature and humidity
 * data and converts them to Celsius and Percents, respectively.
 * @param[in] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @param[out] temp : Temperature data in Celsius.
 * @param[out] hum : Humidity data in Percents.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum20_get_measurement ( temphum20_t *ctx, float *temp, float *hum );

/**
 * @brief TempHum 20 set operating mode function.
 * @details This function sets the device operating mode.
 * @param[in] ctx : Click context object.
 * See #temphum20_t object definition for detailed explanation.
 * @param[in] op_mode : @li @c  0 - Command mode,
 *                      @li @c  1 - Normal operating mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t temphum20_set_operating_mode ( temphum20_t *ctx, uint8_t op_mode );

#ifdef __cplusplus
}
#endif
#endif // TEMPHUM20_H

/*! @} */ // temphum20

// ------------------------------------------------------------------------ END
