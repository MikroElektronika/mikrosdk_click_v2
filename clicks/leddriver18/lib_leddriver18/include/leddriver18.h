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
 * @file leddriver18.h
 * @brief This file contains API for LED Driver 18 Click Driver.
 */

#ifndef LEDDRIVER18_H
#define LEDDRIVER18_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup leddriver18 LED Driver 18 Click Driver
 * @brief API for configuring and manipulating LED Driver 18 Click driver.
 * @{
 */

/**
 * @defgroup leddriver18_reg LED Driver 18 Registers List
 * @brief List of registers of LED Driver 18 Click driver.
 */

/**
 * @addtogroup leddriver18_reg
 * @{
 */

/**
 * @brief LED Driver 18 description register.
 * @details Specified register for description of LED Driver 18 Click driver.
 */
#define LEDDRIVER18_WRITE_TO_RDAC           0x00
#define LEDDRIVER18_ONE_TIME_PROG           0x80

/*! @} */ // leddriver18_reg

/**
 * @defgroup leddriver18_set LED Driver 18 Registers Settings
 * @brief Settings for registers of LED Driver 18 Click driver.
 */

/**
 * @addtogroup leddriver18_set
 * @{
 */

/**
 * @brief LED Driver 18 description setting.
 * @details Specified setting for description of LED Driver 18 Click driver.
 */
#define LEDDRIVER18_PWM_MAX_VALUE           0x0FFF
#define LEDDRIVER18_MAX_OUTPUT_NUM          24
#define LEDDRIVER18_MAX_RES_BITS            12
#define LEDDRIVER18_CC_MASK                 0x3F
#define LEDDRIVER18_CC_ERROR                0x80

/**
 * @brief LED Driver 18 constant current values.
 * @details Specified values for constant current outputs of LED Driver 18 Click driver.
 */
#define LEDDRIVER18_CURRENT_30_mA           0x00
#define LEDDRIVER18_CURRENT_20_mA           0x01
#define LEDDRIVER18_CURRENT_15_mA           0x02
#define LEDDRIVER18_CURRENT_10_mA           0x04
#define LEDDRIVER18_CURRENT_5_mA            0x0B
#define LEDDRIVER18_CURRENT_2_mA            0x1E

/**
 * @brief LED Driver 18 device address setting.
 * @details Specified setting for device slave address selection of
 * LED Driver 18 Click driver.
 */
#define LEDDRIVER18_DEVICE_ADDRESS          0x2C

/*! @} */ // leddriver18_set

/**
 * @defgroup leddriver18_map LED Driver 18 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Driver 18 Click driver.
 */

/**
 * @addtogroup leddriver18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Driver 18 Click to the selected MikroBUS.
 */
#define LEDDRIVER18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM )
    
/*! @} */ // leddriver18_map
/*! @} */ // leddriver18

/**
 * @brief LED Driver 18 Click context object.
 * @details Context object definition of LED Driver 18 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t cs;       /**< Device select. */
    digital_out_t sck;      /**< Clock pin. */
    digital_out_t mosi;     /**< Master Out Slave In. */
    digital_out_t rst;      /**< Chip ID select. */
    digital_out_t en;       /**< Enable pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} leddriver18_t;

/**
 * @brief LED Driver 18 Click configuration object.
 * @details Configuration object definition of LED Driver 18 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t cs;              /**< Device select. */
    pin_name_t sck;             /**< Clock pin. */
    pin_name_t mosi;            /**< Master Out Slave In. */
    pin_name_t rst;             /**< Chip ID select. */
    pin_name_t en;              /**< Enable pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} leddriver18_cfg_t;

/**
 * @brief LED Driver 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDDRIVER18_OK = 0,
    LEDDRIVER18_ERROR = -1

} leddriver18_return_value_t;

/*!
 * @addtogroup leddriver18 LED Driver 18 Click Driver
 * @brief API for configuring and manipulating LED Driver 18 Click driver.
 * @{
 */

/**
 * @brief LED Driver 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #leddriver18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void leddriver18_cfg_setup ( leddriver18_cfg_t *cfg );

/**
 * @brief LED Driver 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #leddriver18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #leddriver18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver18_init ( leddriver18_t *ctx, leddriver18_cfg_t *cfg );

/**
 * @brief LED Driver 18 default configuration function.
 * @details This function executes a default configuration of LED Driver 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t leddriver18_default_cfg ( leddriver18_t *ctx );

/**
 * @brief LED Driver 18 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver18_generic_write ( leddriver18_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief LED Driver 18 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #leddriver18_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver18_generic_read ( leddriver18_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief LED Driver 18 set output channel PWM value function.
 * @details This function is used to set output PWM of selected channel of LED Driver 18
 * click board.
 * @param[in] out_num : Selected output number.
 * @param[in] pwm_val : PWM value.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note To update values after using this function you will 
 * need to call the leddriver18_write_config function.
 */
err_t leddriver18_set_output_pwm ( uint8_t out_num, float pwm_val );

/**
 * @brief LED Driver 18 get output channel PWM value function.
 * @details This function is used to get output PWM of selected channel of LED Driver 18
 * click board.
 * @param[in] out_num : Selected output number.
 * @return PWM value of the selected output
 * @note None.
 */
float leddriver18_get_output_pwm ( uint8_t out_num );

/**
 * @brief LED Driver 18 write config function.
 * @details This function is used to update output settings of LED Driver 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver18_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void leddriver18_write_config ( leddriver18_t *ctx );

/**
 * @brief LED Driver 18 enable output function.
 * @details This function is used to enable output of LED Driver 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver18_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void leddriver18_enable_output ( leddriver18_t *ctx );

/**
 * @brief LED Driver 18 disable output function.
 * @details This function is used to disable output of LED Driver 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver18_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void leddriver18_disable_output ( leddriver18_t *ctx );

/**
 * @brief LED Driver 18 set constant current output function.
 * @details This function is used to set constant current output of of LED Driver 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver18_t object definition for detailed explanation.
 * @param[in] current_limit : Constant current value to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver18_set_cc_output ( leddriver18_t *ctx, uint8_t current_limit );

/**
 * @brief LED Driver 18 get constant current output function.
 * @details This function is used to read constant current output of LED Driver 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver18_t object definition for detailed explanation.
 * @param[in] current_limit : Constant current value to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver18_get_cc_output ( leddriver18_t *ctx, uint8_t *current_limit );

#ifdef __cplusplus
}
#endif
#endif // LEDDRIVER18_H

/*! @} */ // leddriver18

// ------------------------------------------------------------------------ END
