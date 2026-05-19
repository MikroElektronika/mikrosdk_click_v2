/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file pressure25.h
 * @brief This file contains API for Pressure 25 Click Driver.
 */

#ifndef PRESSURE25_H
#define PRESSURE25_H

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

/*!
 * @addtogroup pressure25 Pressure 25 Click Driver
 * @brief API for configuring and manipulating Pressure 25 Click driver.
 * @{
 */

/**
 * @defgroup pressure25_reg Pressure 25 Registers List
 * @brief List of registers of Pressure 25 Click driver.
 */

/**
 * @addtogroup pressure25_reg
 * @{
 */

/**
 * @brief Pressure 25 register map.
 * @details Specified register map of Pressure 25 Click driver.
 */
#define PRESSURE25_REG_CONV_STATUS                  0x20
#define PRESSURE25_REG_PDATA_23_16                  0x06
#define PRESSURE25_REG_PDATA_15_8                   0x07
#define PRESSURE25_REG_PDATA_7_0                    0x08
#define PRESSURE25_REG_TDATA_15_8                   0x09
#define PRESSURE25_REG_TDATA_7_0                    0x0A
#define PRESSURE25_REG_CTRL                         0x30

/*! @} */ // pressure25_reg

/**
 * @defgroup pressure25_set Pressure 25 Registers Settings
 * @brief Settings for registers of Pressure 25 Click driver.
 */

/**
 * @addtogroup pressure25_set
 * @{
 */

/**
 * @brief Pressure 25 command masks setting.
 * @details Specified setting for command masks of Pressure 25 Click driver.
 */
#define PRESSURE25_CMD_GET_RAW_PM                   0xA0
#define PRESSURE25_CMD_GET_RAW_AZPM                 0xA2
#define PRESSURE25_CMD_GET_RAW_TM                   0xA4
#define PRESSURE25_CMD_GET_RAW_AZTM                 0xA6
#define PRESSURE25_CMD_START_NOR                    0xA8
#define PRESSURE25_CMD_START_CMD                    0xA9
#define PRESSURE25_CMD_WRITE_CHECKSUM               0xAA
#define PRESSURE25_CMD_GET_CAL                      0xAC
#define PRESSURE25_CMD_GET_CAL_S                    0xB0

/**
 * @brief Pressure 25 status byte bit masks setting.
 * @details Specified setting for status byte bit masks of Pressure 25 Click driver.
 */
#define PRESSURE25_STATUS_POWER_BIT                 0x40
#define PRESSURE25_STATUS_BUSY_BIT                  0x20
#define PRESSURE25_STATUS_MODE_BIT                  0x08
#define PRESSURE25_STATUS_MEM_ERR_BIT               0x04
#define PRESSURE25_STATUS_BUSY_MASK                 0x60

/**
 * @brief Pressure 25 control register measurement modes setting.
 * @details Specified setting for control register measurement modes of Pressure 25 Click driver.
 */
#define PRESSURE25_CTRL_SINGLE_TEMP                 0x00
#define PRESSURE25_CTRL_SINGLE_PRESS                0x01
#define PRESSURE25_CTRL_COMBINED                    0x02
#define PRESSURE25_CTRL_SLEEP                       0x03

/**
 * @brief Pressure 25 pressure conversion constants setting.
 * @details Specified setting for pressure conversion constants of Pressure 25 Click driver.
 */
#define PRESSURE25_PMIN_KPA                         30.0f
#define PRESSURE25_PMAX_KPA                         120.0f
#define PRESSURE25_TF_A                             0.8f
#define PRESSURE25_TF_B                             0.1f

/**
 * @brief Pressure 25 temperature conversion constants setting.
 * @details Specified setting for temperature conversion constants of Pressure 25 Click driver.
 */
#define PRESSURE25_TEMP_MIN_C                    ( -40.0f )
#define PRESSURE25_TEMP_SPAN_C                      190.0f

/**
 * @brief Pressure 25 conversion timeout setting.
 * @details Specified setting for conversion timeout of Pressure 25 Click driver.
 */
#define PRESSURE25_CONVERSION_TIMEOUT_MS            250u

/**
 * @brief Pressure 25 temperature and pressure normalization divisors setting.
 * @details Specified setting for temperature and pressure normalization divisors of Pressure 25 Click driver.
 */
#define PRESSURE25_TEMP_RESOLUTION_DIV              65536.0f
#define PRESSURE25_PRESSURE_RESOLUTION_DIV          16777216.0f

/**
 * @brief Pressure 25 response length setting.
 * @details Specified setting for response length of Pressure 25 Click driver.
 */
#define PRESSURE25_RESPONSE_LEN                     6u

/**
 * @brief Pressure 25 I2C timeout setting.
 * @details Specified setting for I2C timeout of Pressure 25 Click driver.
 */
#define PRESSURE25_I2C_TIMEOUT                      100000ul

/**
 * @brief Pressure 25 device address setting.
 * @details Specified setting for device address of Pressure 25 Click driver.
 */
#define PRESSURE25_DEVICE_ADDRESS                   0x78

/*! @} */ // pressure25_set

/**
 * @defgroup pressure25_map Pressure 25 MikroBUS Map
 * @brief MikroBUS pin mapping of Pressure 25 Click driver.
 */

/**
 * @addtogroup pressure25_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Pressure 25 Click to the selected MikroBUS.
 */
#define PRESSURE25_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pressure25_map
/*! @} */ // pressure25

/**
 * @brief Pressure 25 Click context object.
 * @details Context object definition of Pressure 25 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;                       /**< Interrupt pin. */

    // Bit-bang I2C pins
    pin_name_t scl;                             /**< Clock pin. */
    pin_name_t sda;                             /**< Bidirectional data pin. */

    // I2C slave address
    uint8_t slave_address;                      /**< Device slave address. */
    
    // Bit-bang I2C state
    uint8_t i2c_started;                        /**< I2C started flag. */

} pressure25_t;

/**
 * @brief Pressure 25 Click configuration object.
 * @details Configuration object definition of Pressure 25 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin. */
    pin_name_t sda;             /**< Bidirectional data pin. */

    pin_name_t int_pin;         /**< Interrupt pin descriptor. */

    uint8_t    i2c_address;     /**< I2C slave address. */

} pressure25_cfg_t;

/**
 * @brief Pressure 25 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PRESSURE25_OK = 0,
    PRESSURE25_ERROR = -1

} pressure25_return_value_t;

/*!
 * @addtogroup pressure25 Pressure 25 Click Driver
 * @brief API for configuring and manipulating Pressure 25 Click driver.
 * @{
 */

/**
 * @brief Pressure 25 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pressure25_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pressure25_cfg_setup ( pressure25_cfg_t *cfg );

/**
 * @brief Pressure 25 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pressure25_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pressure25_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure25_init ( pressure25_t *ctx, pressure25_cfg_t *cfg );

/**
 * @brief Pressure 25 send command function.
 * @details This function sends a command byte over the I2C interface.
 * @param[in] ctx : Click context object.
 * See #pressure25_t object definition for detailed explanation.
 * @param[in] cmd : Command byte to be sent.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure25_send_cmd ( pressure25_t *ctx, uint8_t cmd );

/**
 * @brief Pressure 25 get INT pin state function.
 * @details This function reads the current logic level of the INT pin.
 * @param[in] ctx : Click context object.
 * See #pressure25_t object definition for detailed explanation.
 * @return @li @c 0 - Conversion not complete,
 *         @li @c 1 - Conversion complete, data ready.
 * @note None.
 */
uint8_t pressure25_get_int_pin ( pressure25_t *ctx );

/**
 * @brief Pressure 25 get pressure and temperature function.
 * @details This function triggers a compensated pressure and temperature acquisition 
 * and converts values to kPa and degC.
 * @param[in] ctx : Click context object.
 * See #pressure25_t object definition for detailed explanation.
 * @param[out] press : Pointer to output pressure value in kPa.
 * @param[out] temp  : Pointer to output temperature value in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pressure25_get_press_temp ( pressure25_t *ctx, float *press, float *temp );

#ifdef __cplusplus
}
#endif
#endif // PRESSURE25_H

/*! @} */ // pressure25

// ------------------------------------------------------------------------ END
