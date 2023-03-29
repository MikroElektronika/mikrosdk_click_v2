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
 * @file diffpress2.h
 * @brief This file contains API for Diff Press 2 Click Driver.
 */

#ifndef DIFFPRESS2_H
#define DIFFPRESS2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup diffpress2 Diff Press 2 Click Driver
 * @brief API for configuring and manipulating Diff Press 2 Click driver.
 * @{
 */

/**
 * @defgroup diffpress2_reg Diff Press 2 Registers List
 * @brief List of registers of Diff Press 2 Click driver.
 */

/**
 * @addtogroup diffpress2_reg
 * @{
 */

/**
 * @brief Diff Press 2 description commands.
 * @details Specified commands for description of Diff Press 2 Click driver.
 */
#define DIFFPRESS2_CMD_START_CONT_MEAS_MASS_FLOW_AVG    0x3603
#define DIFFPRESS2_CMD_START_CONT_MEAS_MASS_FLOW_NONE   0x3608
#define DIFFPRESS2_CMD_START_CONT_MEAS_DIFF_PRESS_AVG   0x3615
#define DIFFPRESS2_CMD_START_CONT_MEAS_DIFF_PRESS_NONE  0x361E
#define DIFFPRESS2_CMD_STOP_CONT_MEAS                   0x3FF9
#define DIFFPRESS2_CMD_TRIGGER_MEAS_MASS_FLOW           0x3624
#define DIFFPRESS2_CMD_TRIGGER_MEAS_MASS_FLOW_STRETCH   0x3726
#define DIFFPRESS2_CMD_TRIGGER_MEAS_DIFF_PRESS          0x362F
#define DIFFPRESS2_CMD_TRIGGER_MEAS_DIFF_PRESS_STRETCH  0x372D
#define DIFFPRESS2_CMD_PRODUCT_ID_PT1                   0x367C
#define DIFFPRESS2_CMD_PRODUCT_ID_PT2                   0xE102

/*! @} */ // diffpress2_reg

/**
 * @defgroup diffpress2_set Diff Press 2 Registers Settings
 * @brief Settings for registers of Diff Press 2 Click driver.
 */

/**
 * @addtogroup diffpress2_set
 * @{
 */

/**
 * @brief Diff Press 2 description constants.
 * @details Specified constants for description of Diff Press 2 Click driver.
 */
#define DIFFPRESS2_PRODUCT_ID                           0x03010101
#define DIFFPRESS2_PRESSURE_SCALE_FACOTR                60.0
#define DIFFPRESS2_TEMPERATURE_SCALE_FACOTR             200.0

/**
 * @brief Diff Press 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Diff Press 2 Click driver.
 */
#define DIFFPRESS2_SET_DEV_ADDR_GND                     0x21
#define DIFFPRESS2_SET_DEV_ADDR_R4                      0x22
#define DIFFPRESS2_SET_DEV_ADDR                         DIFFPRESS2_SET_DEV_ADDR_R4

/*! @} */ // diffpress2_set

/**
 * @defgroup diffpress2_map Diff Press 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Diff Press 2 Click driver.
 */

/**
 * @addtogroup diffpress2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Diff Press 2 Click to the selected MikroBUS.
 */
#define DIFFPRESS2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // diffpress2_map
/*! @} */ // diffpress2

/**
 * @brief Diff Press 2 Click context object.
 * @details Context object definition of Diff Press 2 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;  /**< Interrupt. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    
    //ID's
    uint32_t product_id;
    uint32_t serial_id[ 2 ];

} diffpress2_t;

/**
 * @brief Diff Press 2 Click configuration object.
 * @details Configuration object definition of Diff Press 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;    /**< Interrupt. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} diffpress2_cfg_t;

/**
 * @brief Diff Press 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   DIFFPRESS2_OK = 0,
   DIFFPRESS2_ERROR = -1

} diffpress2_return_value_t;

/*!
 * @addtogroup diffpress2 Diff Press 2 Click Driver
 * @brief API for configuring and manipulating Diff Press 2 Click driver.
 * @{
 */

/**
 * @brief Diff Press 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #diffpress2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void diffpress2_cfg_setup ( diffpress2_cfg_t *cfg );

/**
 * @brief Diff Press 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #diffpress2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #diffpress2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress2_init ( diffpress2_t *ctx, diffpress2_cfg_t *cfg );

/**
 * @brief Diff Press 2 default configuration function.
 * @details This function executes a default configuration of Diff Press 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #diffpress2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t diffpress2_default_cfg ( diffpress2_t *ctx );

/**
 * @brief Command writing function.
 * @details This function sends a word of data to device.
 * @param[in] ctx : Click context object.
 * See #diffpress2_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress2_send_command ( diffpress2_t *ctx, uint16_t cmd );

/**
 * @brief Command reading function.
 * @details This function reads a desired number of data words from the selected command.
 * @param[in] ctx : Click context object.
 * See #diffpress2_t object definition for detailed explanation.
 * @param[in] cmd : Command.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress2_generic_read ( diffpress2_t *ctx, uint16_t cmd, uint16_t *rx_buf, uint8_t rx_len );

/**
 * @brief Reading function.
 * @details This function reads a desired number of data words.
 * @param[in] ctx : Click context object.
 * See #diffpress2_t object definition for detailed explanation.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress2_raw_read ( diffpress2_t *ctx, uint16_t *rx_buf, uint8_t rx_len );

/**
 * @brief Reads device ID's.
 * @details This function reads a product and serial id's from device. Checks if
 * product ID is correctly read and stores them in context object.
 * @param[in,out] ctx : Click context object.
 * See #diffpress2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress2_get_id ( diffpress2_t *ctx );

/**
 * @brief Reset device.
 * @details This function resets device with reset sequence command.
 * @param[in] ctx : Click context object.
 * See #diffpress2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress2_reset ( diffpress2_t *ctx );

/**
 * @brief Pressure and temperature reading.
 * @details This function reads a pressure and temperature for selected type of trigger
 * measurement and calculates value with scale factors for pressure and temperature.
 * @param[in] ctx : Click context object.
 * See #diffpress2_t object definition for detailed explanation.
 * @param[in] tigger_type : Trigger measurement type.
 * @param[out] diff_press : Output pressure data in Pasacl.
 * @param[out] temperature : Output temperature data in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t diffpress2_trigger_measurement ( diffpress2_t *ctx, uint16_t trigger_type, 
                                       float *diff_press, float *temperature );

#ifdef __cplusplus
}
#endif
#endif // DIFFPRESS2_H

/*! @} */ // diffpress2

// ------------------------------------------------------------------------ END
