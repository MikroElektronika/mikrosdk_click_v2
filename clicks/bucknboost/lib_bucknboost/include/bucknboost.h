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
 * @file bucknboost.h
 * @brief This file contains API for Buck n Boost Click Driver.
 */

#ifndef BUCKNBOOST_H
#define BUCKNBOOST_H

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
 * @addtogroup bucknboost Buck n Boost Click Driver
 * @brief API for configuring and manipulating Buck n Boost Click driver.
 * @{
 */

/**
 * @defgroup bucknboost_reg Buck n Boost Registers List
 * @brief List of registers of Buck n Boost Click driver.
 */

/**
 * @addtogroup bucknboost_reg
 * @{
 */

/**
 * @brief Buck n Boost Status Register Map.
 * @details The list of Status Registers.
 */
#define BUCKNBOOST_REG_PGOOD1_6                        0x00
#define BUCKNBOOST_REG_STATUS                          0x01
#define BUCKNBOOST_REG_FAULT                           0x02

/**
 * @brief Buck n Boost Control Register Map.
 * @details The list of Control Registers.
 */
#define BUCKNBOOST_REG_STBY_CTRL                       0x03
#define BUCKNBOOST_REG_EN                              0x04
#define BUCKNBOOST_REG_OUT1                            0x05
#define BUCKNBOOST_REG_OUT2                            0x06
#define BUCKNBOOST_REG_OUT3                            0x07
#define BUCKNBOOST_REG_OUT4                            0x08
#define BUCKNBOOST_REG_OUT5                            0x09
#define BUCKNBOOST_REG_OUT6                            0x0A
#define BUCKNBOOST_REG_STBY_OUT1                       0x0B
#define BUCKNBOOST_REG_STBY_OUT2                       0x0C
#define BUCKNBOOST_REG_STBY_OUT3                       0x0D
#define BUCKNBOOST_REG_STBY_OUT4                       0x0E
#define BUCKNBOOST_REG_STBY_OUT5                       0x0F
#define BUCKNBOOST_REG_STBY_OUT6                       0x10
#define BUCKNBOOST_REG_SEQ1                            0x11
#define BUCKNBOOST_REG_SEQ2                            0x12
#define BUCKNBOOST_REG_SEQ3                            0x13
#define BUCKNBOOST_REG_SEQ4                            0x14
#define BUCKNBOOST_REG_SEQ5                            0x15
#define BUCKNBOOST_REG_SEQ6                            0x16
#define BUCKNBOOST_REG_DELAY_CTRL                      0x17
#define BUCKNBOOST_REG_SS1_2                           0x18
#define BUCKNBOOST_REG_SS3_4                           0x19
#define BUCKNBOOST_REG_SS5_6                           0x1A
#define BUCKNBOOST_REG_ILIMIT_1_2                      0x1B
#define BUCKNBOOST_REG_ILIMIT_3_4                      0x1C
#define BUCKNBOOST_REG_ILIMIT_5_6                      0x1D
#define BUCKNBOOST_REG_STBY_ILIMIT_1_2                 0x1E
#define BUCKNBOOST_REG_STBY_ILIMIT_3_4                 0x1F
#define BUCKNBOOST_REG_STBY_ILIMIT_5_6                 0x20
#define BUCKNBOOST_REG_PORUP_PGOOD_MASK123             0x21
#define BUCKNBOOST_REG_PORDN_PGOOD_MASK456             0x22
#define BUCKNBOOST_REG_PULLDN1_6                       0x23

/**
 * @brief Buck n Boost Command Register Map.
 * @details The list of Command Registers.
 */
#define BUCKNBOOST_CMD_SAVECONFIG                      0x66
#define BUCKNBOOST_CMD_RESET                           0x6A
#define BUCKNBOOST_CMD_RELOAD                          0x6B
#define BUCKNBOOST_CMD_REBOOT                          0x6C
#define BUCKNBOOST_CMD_SEQUENCE                        0x6D

/*! @} */ // bucknboost_reg

/**
 * @defgroup bucknboost_set Buck n Boost Registers Settings
 * @brief Settings for registers of Buck n Boost Click driver.
 */

/**
 * @addtogroup bucknboost_set
 * @{
 */

/**
 * @brief Buck n Boost Current limit setting.
 * @details Specified setting for Current limit of Buck n Boost Click driver.
 */
#define BUCKNBOOST_CURRENT_LIMIT_1100mA                0x0F
#define BUCKNBOOST_CURRENT_LIMIT_1600mA                0x0E
#define BUCKNBOOST_CURRENT_LIMIT_2100mA                0x0D
#define BUCKNBOOST_CURRENT_LIMIT_2600mA                0x0C
#define BUCKNBOOST_CURRENT_LIMIT_3100mA                0x0B
#define BUCKNBOOST_CURRENT_LIMIT_3600mA                0x0A
#define BUCKNBOOST_CURRENT_LIMIT_4100mA                0x09
#define BUCKNBOOST_CURRENT_LIMIT_4600mA                0x08
#define BUCKNBOOST_CURRENT_LIMIT_5100mA                0x07
#define BUCKNBOOST_CURRENT_LIMIT_5600mA                0x06
#define BUCKNBOOST_CURRENT_LIMIT_6100mA                0x05
#define BUCKNBOOST_CURRENT_LIMIT_6600mA                0x04
#define BUCKNBOOST_CURRENT_LIMIT_7100mA                0x03
#define BUCKNBOOST_CURRENT_LIMIT_7600mA                0x02
#define BUCKNBOOST_CURRENT_LIMIT_8100mA                0x01
#define BUCKNBOOST_CURRENT_LIMIT_8600mA                0x00

/**
 * @brief Buck n Boost Standby modes setting.
 * @details Specified setting for Standby modes of Buck n Boost Click driver.
 */
#define BUCKNBOOST_WAKE_UP                             0x00
#define BUCKNBOOST_STANDBY                             0x01

/**
 * @brief Buck n Boost Device states setting.
 * @details Specified setting for Device states of Buck n Boost Click driver.
 */
#define BUCKNBOOST_ENABLE                              0x01
#define BUCKNBOOST_DISABLE                             0x00

/**
 * @brief Buck n Boost Standby and Normal Mode setting.
 * @details Specified setting for Standby and Normal Mode of Buck n Boost Click driver.
 */
#define BUCKNBOOST_NORMAL_MODE_ALL                     0x40

/**
 * @brief Buck n Boost Output Channel setting.
 * @details Specified setting for Output Channel of Buck n Boost Click driver.
 */
#define BUCKNBOOST_OUTPUT_CH_1                         0x01
#define BUCKNBOOST_OUTPUT_CH_2                         0x02
#define BUCKNBOOST_OUTPUT_CH_3                         0x03
#define BUCKNBOOST_OUTPUT_CH_4                         0x04
#define BUCKNBOOST_OUTPUT_CH_5                         0x05
#define BUCKNBOOST_OUTPUT_CH_6                         0x06

/**
 * @brief Buck n Boost Buck Output Voltage setting.
 * @details Specified setting for Buck Output Voltage of Buck n Boost Click driver.
 */
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_800mV           0x32
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_850mV           0x31
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_900mV           0x30
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_950mV           0x2F
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1000mV          0x2E
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1050mV          0x2D
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1100mV          0x2C
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1150mV          0x2B
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1200mV          0x2A
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1250mV          0x29
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1300mV          0x28
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1350mV          0x27
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1400mV          0x26
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1450mV          0x25
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1500mV          0x24
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1550mV          0x23
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1600mV          0x22
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1650mV          0x21
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1700mV          0x20
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1750mV          0x1F
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1800mV          0x1E
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1850mV          0x1D
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1900mV          0x1C
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_1950mV          0x1B
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2000mV          0x1A
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2050mV          0x19
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2100mV          0x18
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2150mV          0x17
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2200mV          0x16
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2250mV          0x15
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2300mV          0x14
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2350mV          0x13
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2400mV          0x12
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2450mV          0x11
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2500mV          0x10
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2550mV          0x0F
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2600mV          0x0E
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2650mV          0x0D
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2700mV          0x0C
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2750mV          0x0B
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2800mV          0x0A
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2850mV          0x09
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2900mV          0x08
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_2950mV          0x07
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_3000mV          0x06
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_3050mV          0x05
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_3100mV          0x04
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_3150mV          0x03
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_3200mV          0x02
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_3250mV          0x01
#define BUCKNBOOST_BUCK_OUTPUT_VOLTAGE_3300mV          0x00

/**
 * @brief Buck n Boost Boost Output Voltage setting.
 * @details Specified setting for Boost Output Voltage of Buck n Boost Click driver.
 */
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_7000mV         0x23
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_7200mV         0x22
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_7400mV         0x21
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_7600mV         0x20
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_7800mV         0x1F
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_8000mV         0x1E
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_8200mV         0x1D
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_8400mV         0x1C
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_8600mV         0x1B
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_8800mV         0x1A
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_9000mV         0x19
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_9200mV         0x18
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_9400mV         0x17
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_9600mV         0x16
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_9800mV         0x15
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_10000mV        0x14
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_10200mV        0x13
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_10400mV        0x12
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_10600mV        0x11
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_10800mV        0x10
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_11000mV        0x0F
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_11200mV        0x0E
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_11400mV        0x0D
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_11600mV        0x0C
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_11800mV        0x0B
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_12000mV        0x0A
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_12200mV        0x09
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_12400mV        0x08
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_12600mV        0x07
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_12800mV        0x06
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_13000mV        0x05
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_13200mV        0x04
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_13400mV        0x03
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_13600mV        0x02
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_13800mV        0x01
#define BUCKNBOOST_BOOST_OUTPUT_VOLTAGE_14000mV        0x00

/**
 * @brief Buck n Boost Power Good status masks.
 * @details Specified Power Good status masks of Buck n Boost Click driver.
 */
#define BUCKNBOOST_PGOOD1_MASK                         0x01
#define BUCKNBOOST_PGOOD2_MASK                         0x02
#define BUCKNBOOST_PGOOD3_MASK                         0x04
#define BUCKNBOOST_PGOOD4_MASK                         0x08
#define BUCKNBOOST_PGOOD5_MASK                         0x10
#define BUCKNBOOST_PGOOD6_MASK                         0x20
#define BUCKNBOOST_PGOOD_ALL_MASK                      0x3F

/**
 * @brief Buck n Boost EEPROM status masks.
 * @details Specified EEPROM status masks of Buck n Boost Click driver.
 */
#define BUCKNBOOST_EEPROM_READY_MASK                   0x01
#define BUCKNBOOST_EEPROM_CONFIG_MASK                  0x02
#define BUCKNBOOST_EEPROM_CALIB_MASK                   0x04
#define BUCKNBOOST_EEPROM_READ_MASK                    0x40
#define BUCKNBOOST_EEPROM_WRITE_MASK                   0x80
#define BUCKNBOOST_EEPROM_ALL_MASK                     0xC7

/**
 * @brief Buck n Boost Overcurrent status fault masks.
 * @details Specified Overcurrent status fault masks of Buck n Boost Click driver.
 */
#define BUCKNBOOST_FAULT_REG1OC_MASK                   0x01
#define BUCKNBOOST_FAULT_REG2OC_MASK                   0x02
#define BUCKNBOOST_FAULT_REG3OC_MASK                   0x04
#define BUCKNBOOST_FAULT_REG4OC_MASK                   0x08
#define BUCKNBOOST_FAULT_REG5OC_MASK                   0x10
#define BUCKNBOOST_FAULT_REG6OC_MASK                   0x20
#define BUCKNBOOST_FAULT_OT_MASK                       0x80
#define BUCKNBOOST_FAULT_ALL_MASK                      0xBF

/**
 * @brief Buck n Boost device address setting.
 * @details Specified setting for device slave address selection of
 * Buck n Boost Click driver.
 */
#define BUCKNBOOST_DEV_ADDR                 0x30

/*! @} */ // bucknboost_set

/**
 * @defgroup bucknboost_map Buck n Boost MikroBUS Map
 * @brief MikroBUS pin mapping of Buck n Boost Click driver.
 */

/**
 * @addtogroup bucknboost_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Buck n Boost Click to the selected MikroBUS.
 */
#define BUCKNBOOST_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.por = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.stb = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.pg = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // bucknboost_map
/*! @} */ // bucknboost

/**
 * @brief Buck n Boost Click context object.
 * @details Context object definition of Buck n Boost Click driver.
 */
typedef struct
{
    // Output pins

    digital_out_t  en;       /**< Enable pin. */
    digital_out_t  stb;      /**< Standby pin. */

    // Input pins

    digital_in_t  por;       /**< Power-ON Reset pin. */
    digital_in_t  pg;        /**< Global Power Good pin. */

    // Modules

    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address

    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

} bucknboost_t;

/**
 * @brief Buck n Boost Click configuration object.
 * @details Configuration object definition of Buck n Boost Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;         /**< Enable pin. */
    pin_name_t  por;        /**< Power-ON Reset pin. */
    pin_name_t  stb;        /**< Standby pin. */
    pin_name_t  pg;         /**< Global Power Good pin. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} bucknboost_cfg_t;

/**
 * @brief Buck n Boost Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BUCKNBOOST_OK = 0,
    BUCKNBOOST_ERROR = -1

} bucknboost_return_value_t;

/**
 * @brief Buck n Boost Click status data structure.
 * @details Status object definition of Buck n Boost Click driver.
 */
typedef struct
{
    uint8_t power_good;
    uint8_t eeprom_status;
    uint8_t overcurrent_fault;
}
bucknboost_status_t;

/**
 * @brief Buck n Boost Click buck config data structure.
 * @details Buck config object definition of Buck n Boost Click driver.
 */
typedef struct
{
    uint8_t out_standby;
    uint8_t out_enable;
    uint8_t out_vol_normal_mode;
    uint8_t out_vol_stby_mode;
}
bucknboost_cfg_buck_t;

/*!
 * @addtogroup bucknboost Buck n Boost Click Driver
 * @brief API for configuring and manipulating Buck n Boost Click driver.
 * @{
 */

/**
 * @brief Buck n Boost configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #bucknboost_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void bucknboost_cfg_setup ( bucknboost_cfg_t *cfg );

/**
 * @brief Buck n Boost initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #bucknboost_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_init ( bucknboost_t *ctx, bucknboost_cfg_t *cfg );

/**
 * @brief Buck n Boost default configuration function.
 * @details This function executes a default configuration of Buck n Boost
 * click board.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t bucknboost_default_cfg ( bucknboost_t *ctx );

/**
 * @brief Buck n Boost I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_generic_write ( bucknboost_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Buck n Boost I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_generic_read ( bucknboost_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Buck n Boost send command function.
 * @details This function sends a desired command via I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] cmd : 8-bit command data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_send_cmd ( bucknboost_t *ctx, uint8_t cmd );

/**
 * @brief Buck n Boost Write single byte function.
 * @details This function writes a desired data to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_write_byte ( bucknboost_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Buck n Boost read single byte function.
 * @details This function reads a single data byte from the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] reg : 8-bit register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_read_byte ( bucknboost_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Buck n Boost set STB pin mode function.
 * @details This function sets standby mode via STB pin.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] state : - 0x00 : Disable.
 *                    - 0x01 : Enable.
 * @return None.
 * @note None.
 */
void bucknboost_pin_standby_mode ( bucknboost_t *ctx, uint8_t state );

/**
 * @brief Buck n Boost set standby mode function.
 * @details This function sets standby or wake up mode via registers.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] state : - 0x00 : Wake Up.
 *                    - 0x01 : Standby.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_reg_standby_mode ( bucknboost_t *ctx, uint8_t state );

/**
 * @brief Buck n Boost enable device function.
 * @details This function enables or disables device by setting EN pin state.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] state : - 0x00 : Disable.
 *                    - 0x01 : Enable.
 * @return None.
 * @note None.
 */
void bucknboost_device_enable ( bucknboost_t *ctx, uint8_t state );

/**
 * @brief Buck n Boost check power good function.
 * @details This function returns PG pin state.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @return PG pin state.
 * @note None.
 */
uint8_t bucknboost_check_power_good ( bucknboost_t *ctx );

/**
 * @brief Buck n Boost check power on reset function.
 * @details This function returns POR pin state.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @return POR pin state.
 * @note None.
 */
uint8_t bucknboost_check_por ( bucknboost_t *ctx );

/**
 * @brief Buck n Boost read overcurrent fault function.
 * @details This function reads the overcurrent status fault.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[out] data_out : Overcurrent status register content.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_read_oc_fault ( bucknboost_t *ctx, uint8_t *data_out );

/**
 * @brief Buck n Boost set buck output voltage function.
 * @details This function sets the output voltage of a desired buck channel.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] ch_num : Channel number.
 * @param[in] data_in : Buck output voltage data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_set_buck_out_voltage ( bucknboost_t *ctx, uint8_t ch_num, uint8_t data_in );

/**
 * @brief Buck n Boost set all bucks output voltage function.
 * @details This function sets the output voltage of all bucks channel.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] data_in : Buck output voltage data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_set_all_buck_out_voltage ( bucknboost_t *ctx, uint8_t data_in );

/**
 * @brief Buck n Boost set boost output voltage function.
 * @details This function sets the output voltage of the boost channel (CH6).
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] data_in : Boost output voltage data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_set_boost_out_voltage ( bucknboost_t *ctx, uint8_t data_in );

/**
 * @brief Buck n Boost get status data function.
 * @details This function reads Power Good, EEPROM, and Overcurrent status registers.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[out] st_data : Status structure output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_get_status ( bucknboost_t *ctx, bucknboost_status_t *st_data );

/**
 * @brief Buck n Boost update configuration of the output registers function.
 * @details This function updates configuration of the output Buck registers.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] ch_num : Buck output channel number [1-5].
 * @param[in] b_data : Buck structure that contains configuration data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_update_cfg_out ( bucknboost_t *ctx, uint8_t ch_num, bucknboost_cfg_buck_t b_data );

/**
 * @brief Buck n Boost get power good status function.
 * @details This function reads the power good status register.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[out] data_out : Power good status register content.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_get_power_good_status ( bucknboost_t *ctx, uint8_t *data_out );

/**
 * @brief Buck n Boost check power good status function.
 * @details This function checks the power good status of a desired channel.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] ch_num : Output channel number [1-6].
 * @param[out] data_out : Power good status flag.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_check_power_good_status ( bucknboost_t *ctx, uint8_t ch_num, uint8_t *data_out );

/**
 * @brief Buck n Boost get eeprom status function.
 * @details This function reads the eeprom status register.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[out] data_out : Eeprom register content.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_get_eeprom_status ( bucknboost_t *ctx, uint8_t *data_out );

/**
 * @brief Buck n Boost get overcurrent fault status function.
 * @details This function reads the overcurrent fault status register.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[out] data_out : Overcurrent fault register content.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_get_overcurrent_fault_status ( bucknboost_t *ctx, uint8_t *data_out );

/**
 * @brief Buck n Boost check overcurrent fault status function.
 * @details This function checks the overcurrent fault status of a desired channel.
 * @param[in] ctx : Click context object.
 * See #bucknboost_t object definition for detailed explanation.
 * @param[in] ch_num : Output channel number [1-6].
 * @param[out] data_out : Overcurrent fault status flag.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t bucknboost_check_overc_fault_status ( bucknboost_t *ctx, uint8_t ch_num, uint8_t *data_out );

#ifdef __cplusplus
}
#endif
#endif // BUCKNBOOST_H

/*! @} */ // bucknboost

// ------------------------------------------------------------------------ END
